#pragma hdrstop
#include "GridUtils.h"
#include "MemTableEh.hpp"
#include <memory>
#include <map>
#include <vector>
//---------------------------------------------------------------------------

#pragma package(smart_init)

using namespace ns_GridUtils;

// "Конструктор"
void __fastcall TSortFld::Init(const String &Str, char Delimiter) {
  std::auto_ptr<TStrings> pStr(new TStringList());
  pStr->Delimiter = Delimiter;
  pStr->DelimitedText = Str;
  for(int i=0; i<pStr->Count; ++i)
    Add(pStr->Strings[i]);
}
//---------------------------------------------------------------------------

// Добавляем строку
TSortFld& __fastcall TSortFld::Add(const String &FldStr) {
  String Fld = FldStr.UpperCase();
  if(_fld_set.insert(Fld).second) {
    _fld.push_back(Fld);
    _str += String().sprintf("%s%s", _str.IsEmpty()?"":";", Fld);
  }
  return *this;
}
//---------------------------------------------------------------------------

// "+=" кроме Excp
TSortFld& __fastcall TSortFld::Add(const TSortFld &Src, const TSortFld &Excp) {
  for(TFldList::const_iterator i=Src._fld.begin(); i!=Src._fld.end(); ++i)
    if(Excp._fld_set.find(*i)==Excp._fld_set.end())
      Add(*i);
  return *this;
}
//---------------------------------------------------------------------------

// Зачистка маркеров сортировки
void __fastcall ClearTitleSortMarker(TDBGridEh *Table, TColumnEh *Column){
  for(int i=0; i<Table->Columns->Count; ++i)
    if(Table->Columns->Items[i]!=Column)
      Table->Columns->Items[i]->Title->SortMarker = smNoneEh;
}
//---------------------------------------------------------------------------

// Собираем маркеры сортировки
void __fastcall GetTitleSortMarker(TDBGridEh *Grid, TSortFld &S, TSortFld &D) {
  for(int i=0; i<Grid->SortMarkedColumns->Count; ++i) {
    S.Add(Grid->SortMarkedColumns->Items[i]->FieldName);
    if(smDownEh==Grid->SortMarkedColumns->Items[i]->Title->SortMarker)
      D.Add(Grid->SortMarkedColumns->Items[i]->FieldName);
  }
}
//---------------------------------------------------------------------------

// Сортируем датасет
void __fastcall ns_GridUtils::Sort(TClientDataSet *Data, const TSortFld &S, const TSortFld &D) {
  TPosKeeper PK(Data);
  Data->IndexName = "";
  Data->IndexDefs->Update();
  if(int n=Data->IndexDefs->IndexOf("LocalSort")+1) {
    Data->DeleteIndex("LocalSort");
    Data->IndexDefs->Update();
  }
  if(S.Empty()) return;
  Data->AddIndex("LocalSort", S, TIndexOptions()<<ixCaseInsensitive, D);
  Data->IndexDefs->Update();
  Data->IndexName = "LocalSort";
}
//---------------------------------------------------------------------------

// Сортировка
void __fastcall ns_GridUtils::Sort(TObject *Sender, TColumnEh *Column, const TSortFld &FldLast, const TSortFld &FldDesc, const TSortFld &FldFirst) {
  // Нельзя сортировать по полям, которые не fkData
  if(!Sender || Column && fkData!=Column->Field->FieldKind)return;
  TDBGridEh *Grid = dynamic_cast<TDBGridEh*>(Sender);
  TClientDataSet *Data = dynamic_cast<TClientDataSet*>(Grid->DataSource->DataSet);
  if(!Data->Active) return;

  // Нажатые контрольные клавиши - режим мультисортировки
  if(GetKeyState(VK_SHIFT)<0 || GetKeyState(VK_CONTROL)<0 || GetKeyState(VK_MENU)<0) Grid->OptionsEh << dghMultiSortMarking;
  else if(Grid->OptionsEh.Contains(dghMultiSortMarking)) {
    ClearTitleSortMarker(Grid, Column);
    Grid->OptionsEh >> dghMultiSortMarking;
  }

  // Ставим значок сортировки
  if(Column)
    switch(Column->Title->SortMarker){
      case smNoneEh: Column->Title->SortMarker = smUpEh; break;
      case smUpEh: Column->Title->SortMarker = smDownEh; break;
      case smDownEh: Column->Title->SortMarker = smNoneEh; break;
    }

  TSortFld SG, D;
  GetTitleSortMarker(Grid, SG, D);
  D.Add(FldDesc, SG);
  TSortFld S=FldFirst;
  S.Add(SG).Add(FldLast);
  Sort(Data, S, D);
}
//---------------------------------------------------------------------------

TColumnEh* __fastcall ns_GridUtils::FindColumn(TDBGridEh *Grid, const String &FieldName, bool Required) {
  for(int i=0; i<Grid->Columns->Count; ++i)
    if(Grid->Columns->Items[i]->FieldName.LowerCase()==FieldName.LowerCase())
      return Grid->Columns->Items[i];
  if(Required)
    throw Exception(String().sprintf("В таблице %s поле %s не найдено", Grid->Name, FieldName));
  return 0;
}
//---------------------------------------------------------------------------

// Готовим вектор с Shift-Tab
std::vector<TInput>& __fastcall InitInputVector() {
  static std::vector<TInput> I;
  I.push_back();
  I[0].type = INPUT_KEYBOARD;
  I[0].ki.wVk = VK_SHIFT;
  I[0].ki.dwFlags = 0;
  I.push_back();
  I[1].type = INPUT_KEYBOARD;
  I[1].ki.wVk = VK_TAB;
  I[1].ki.dwFlags = 0;
  I.push_back();
  I[2].type = INPUT_KEYBOARD;
  I[2].ki.wVk = VK_TAB;
  I[2].ki.dwFlags = KEYEVENTF_KEYUP;
  I.push_back();
  I[3].type = INPUT_KEYBOARD;
  I[3].ki.wVk = VK_SHIFT;
  I[3].ki.dwFlags = KEYEVENTF_KEYUP;
  return I;
}
void __fastcall LeftRightExecute(TObject *Sender, TControl *ActiveControl, ns_GridUtils::ELeftRight Direction);
//---------------------------------------------------------------------------

// Нажали влево
void __fastcall ns_GridUtils::LeftExecute(TObject *Sender, TControl *ActiveControl) {
  LeftRightExecute(Sender, ActiveControl, ELeft);
}
void __fastcall LeftExecute(TDBGridEh *Grid, std::vector<TInput> &I) {
  if(Grid->RowDetailPanel->Active)
    if(Grid->RowDetailPanel->Visible) {
      Grid->RowDetailPanel->Visible = false;
      return;
    }
  if(TMemTableEh *MemData = dynamic_cast<TMemTableEh*>(Grid->DataSource->DataSet))
    if(MemData->TreeNode->NodesCount && MemData->TreeNode->NodeExpanded) {
      MemData->TreeNode->NodeExpanded = false;
      return;
    }
    else
      if(MemData->Locate("id", MemData->FieldByName("id_p")->AsInteger, TLocateOptions()))
        return;
  if(!Grid->DataSource->DataSet->Bof) return Grid->DataSource->DataSet->First();
  SendInput(I.size(), &I[0], sizeof(TInput));
}
//---------------------------------------------------------------------------

// Нажали вправо
void __fastcall ns_GridUtils::RightExecute(TObject *Sender, TControl *ActiveControl) {
  LeftRightExecute(Sender, ActiveControl, ERight);
}
void __fastcall RightExecute(TDBGridEh *Grid, std::vector<TInput> &I) {
  if(Grid->RowDetailPanel->Active)
    if(!Grid->RowDetailPanel->Visible) {
      Grid->RowDetailPanel->Visible = true;
      return;
    }
  if(TMemTableEh *MemData = dynamic_cast<TMemTableEh*>(Grid->DataSource->DataSet))
    if(MemData->TreeNode->NodesCount && !MemData->TreeNode->NodeExpanded) {
      MemData->TreeNode->NodeExpanded = true;
      return;
    }
  if(!Grid->DataSource->DataSet->Eof) return Grid->DataSource->DataSet->Last();
  SendInput(2, &I[1], sizeof(TInput));
}
//---------------------------------------------------------------------------

// Реализация отработки лево-право
void __fastcall LeftRightExecute(TObject *Sender, TControl *ActiveControl, ns_GridUtils::ELeftRight Direction) {
static std::vector<TInput> &I = InitInputVector();
  TDBGridEh *Grid = dynamic_cast<TDBGridEh*>(ActiveControl);
  if(!Grid) return;
  switch(Direction) {
    case ns_GridUtils::ELeft: return LeftExecute(Grid, I);
    case ns_GridUtils::ERight: return RightExecute(Grid, I);
  }
}
//---------------------------------------------------------------------------

// Красим строки
void __fastcall ns_GridUtils::DataGetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont, TColor &Background, TGridDrawState State) {
  TDBGridEh *Grid = dynamic_cast<TDBGridEh*>(Sender);
  TDataSet *Data = Grid->DataSource->DataSet;
  if(TField *F=Data->FindField("SYS"))
    if(F->AsInteger) AFont->Style = TFontStyles()<<fsBold;
  if(Column->FieldName=="COLOR")
    Background = static_cast<TColor>(Data->FieldByName("COLOR")->AsInteger);
}
void __fastcall ns_GridUtils::DataDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol, TColumnEh *Column, TGridDrawState State) {
  TDBGridEh *Grid = dynamic_cast<TDBGridEh*>(Sender);
  if(Column->FieldName!="COLOR")
    return Grid->DefaultDrawColumnCell(Rect, DataCol, Column, State);
  Grid->Canvas->Brush->Color = static_cast<TColor>(Column->Field->AsInteger);
  Grid->Canvas->FillRect(Rect);
}
//---------------------------------------------------------------------------

