#include <vcl.h>
#pragma hdrstop
#include <math>
#include <queue>
#include "ReportTurnover.h"
#include "DataSetLayout.h"
#include "CatalogUnit.h"
#include "GridUtils.h"
#include "Options.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "DataDriverEh"
#pragma link "DBGridEh"
#pragma link "DBGridEhGrouping"
#pragma link "GridsEh"
#pragma link "MemTableDataEh"
#pragma link "MemTableEh"
#pragma link "ReportBaseTotal"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TReport::TReportListInserter TfmReportTurnover::ReportListInserter("Обороты...", &TfmReportTurnover::GetInstance);
const double Pi2=M_PI*2;
__fastcall TfmReportTurnover::TfmReportTurnover() {}
void __fastcall TfmReportTurnover::FormPaint(TObject *Sender) {
  OnPaint = 0;
  TfmReportBaseTotal::FormPaint(Sender);
  TOptions::Instance->RestoreLayout(pnlData);
}
void __fastcall TfmReportTurnover::FormDestroy(TObject *Sender) {
  TOptions::Instance->SaveLayout(pnlData);
  TfmReportBaseTotal::FormDestroy(Sender);
}
//---------------------------------------------------------------------------

// Работаем
void __fastcall TfmReportTurnover::Run() {
  {
    TActiveSet<TMemTableTreeListEh> APTL(mtData->TreeList);
    TActiveSet<TMemTableEh> APMT(mtData);
    dsData->Data = TConnect::Instance->GetReadDataSet("select * from report_total(:date_from, :date_to)", TQueryParams().Add(ftDate, "date_from", _from).Add(ftDate, "date_to", _to), GetCatalogTransaction())->Data;
    BuildData();
  }
  mtData->Last();
  mtData->First();
  MakeChart();
}
//---------------------------------------------------------------------------

// Элемент изображения
__fastcall TfmReportTurnover::TDataItem::TDataItem(double S, TColor C) : Id(0), IdParent(-1), Summa(S), Name(), Color(C) {}
__fastcall TfmReportTurnover::TDataItem::TDataItem(TClientDataSet *S) :
Id(S->FieldByName("id")->AsInteger), IdParent(S->FieldByName("id_p")->AsInteger),
Summa(S->FieldByName("summa")->AsFloat), Name(S->FieldByName("name")->AsString), Color(static_cast<TColor>(S->FieldByName("color")->AsInteger)) {}
//---------------------------------------------------------------------------

// Строим данные в мозгах
void __fastcall TfmReportTurnover::BuildData() {
typedef std::vector<TDataList> TData;
  // дербаним датасет с результатом сюда (дерево, кстати)
  TData Data;
  double Total=0;
  for(unsigned int i=0; ; ++i) {
    TDataSetFilter<TClientDataSet>::Filter(dsData, String().sprintf("lvl=%d", i));
    if(!dsData->RecordCount) break;
    Data.push_back();
    for(dsData->First(); !dsData->Eof; dsData->Next()) {
      TDataItem::Ptr Item=Data[i].insert(TDataList::value_type(dsData->FieldByName("id")->AsInteger, TDataItem::Get(dsData))).first->second;
      if(!i) Total = Item->Summa;
      else {
        TDataList::const_iterator I=Data[i-1].find(Item->IdParent);
        if(Data[i-1].end()==I)
          throw Exception(String().sprintf("Кривой расчет - для %d не найдены родительские данные", Item->Id, Item->IdParent));
        I->second->Children.push_back(Item);
      }
    }
  }
  dsData->Filtered = false;
  // разбираем дерево с результатом по слоям
  _search.clear();
  if(Data.empty()) return;
  unsigned int i=1;
  while(i<Data.size() && Data[i].size()==1)
    ++i;
  _search.push_back();
  _search[0].insert(TDataItemList::value_type(Pi2, Data[i-1].begin()->second));
  for(unsigned int m=1; i<Data.size(); ++i, ++m) {
    _search.push_back();
    double T=0, ET=0;
    for(TDataItemList::iterator j=_search[m-1].begin(); j!=_search[m-1].end(); ++j) {
      TDataItem &rItem=*j->second.get();
      double TP = rItem.Summa;
      for(TDataItem::ChildrenList::const_iterator k=rItem.Children.begin(); k!=rItem.Children.end(); ++k){
        TDataItem::Ptr Child = k->lock();
        TDataItem &rChild = *Child.get();
        if(ET>0.005) {
          _search[m].insert(TDataItemList::value_type(T+=ET/Total*Pi2, TDataItem::Get(ET, chrtMain->Color)));
          ET = 0;
        }
        _search[m].insert(TDataItemList::value_type(T+=rChild.Summa/Total*Pi2, Child));
        TP -= rChild.Summa;
      }
      if(TP>0.005) ET += TP;
    }
    if(ET>0.005)
      _search[m].insert(TDataItemList::value_type(T+ET/Total*Pi2, TDataItem::Get(ET, chrtMain->Color)));
  }
}
//---------------------------------------------------------------------------

// Рисуем
void __fastcall TfmReportTurnover::chrtMainResize(TObject *Sender) {
  MakeChart();
}
void __fastcall TfmReportTurnover::MakeChart() {
  for(int i=0; i<chrtMain->SeriesList->Count; ++i) delete chrtMain->SeriesList->operator [](i);
  chrtMain->SeriesList->Clear();
  if(!_search.size()) return;

  _radius_list.clear();
  int R=std::min(chrtMain->ClientHeight, chrtMain->ClientWidth)/2;
  int K=R/_search.size();
  R -= K/2;
  for(int i=_search.size()-1; i>=0; --i, R -= K) {
    TPieSeries *Ser = new TPieSeries(0);
    Ser->PiePen->Color = chrtMain->Color;
    Ser->Marks->Visible = actSwitchMark->Checked;
    Ser->CustomXRadius = R;
    Ser->CustomYRadius = R;
    chrtMain->AddSeries(Ser);
    _radius_list[R] = i;
    for(TDataItemList::iterator j=_search[i].begin(); j!=_search[i].end(); ++j)
      Ser->Add(j->second->Summa, j->second->Name, j->second->Color);
  }
  dsData->Filtered = false;
}
//---------------------------------------------------------------------------

// Играемся с раскраской
void __fastcall TfmReportTurnover::dbgDataDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol, TColumnEh *Column, TGridDrawState State) {
  ns_GridUtils::DataDrawColumnCell(Sender, Rect, DataCol, Column, State);
}
void __fastcall TfmReportTurnover::dbgDataGetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont, TColor &Background, TGridDrawState State) {
  ns_GridUtils::DataGetCellParams(Sender, Column, AFont, Background, State);
}
void __fastcall TfmReportTurnover::actChangeColorExecute(TObject *Sender) {
  TCatalog::SetCatalogColor(mtData->FieldByName("id")->AsInteger, mtData->FieldByName("color")->AsInteger);
  actRunReport->OnExecute(actRunReport);
}
//---------------------------------------------------------------------------

// Показываем/прячем метки
void __fastcall TfmReportTurnover::actSwitchMarkExecute(TObject *Sender) {
  for(int i=0; i<chrtMain->SeriesList->Count; ++i)
    chrtMain->SeriesList->operator [](i)->Marks->Visible = actSwitchMark->Checked;
}
//---------------------------------------------------------------------------

// Водим/кликаем по графику
TfmReportTurnover::TDataItem::Ptr __fastcall TfmReportTurnover::Search(int X, int Y) {
  X -= chrtMain->Width/2;
  Y = chrtMain->Height/2-Y;
  int R = sqrt(X*X + Y*Y);
  TRadiusList::const_iterator I=_radius_list.lower_bound(R);
  if(_radius_list.end()==I) return TDataItem::Get(0.0, chrtMain->Color);
  if(!Y) return _search[I->second].begin()->second;
  else {
    double P = X||Y ? atan2(Y, X) : 0.0;
    if(P<0) P = Pi2 + P;
    TDataItemList::iterator J=_search[I->second].lower_bound(P);
    if(_search[I->second].end()==J) return TDataItem::Get(0.0, chrtMain->Color);
    return J->second;
  }
}
void __fastcall TfmReportTurnover::chrtMainMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y) {
  TDataItem::Ptr Item=Search(X, Y);
  if(!Item->Id) return chrtMain->SetFocus();
  if(mtData->Locate("id", Item->Id, TLocateOptions()))
    dbgData->SetFocus();
  else chrtMain->SetFocus();
}
void __fastcall TfmReportTurnover::chrtMainMouseMove(TObject *Sender, TShiftState Shift, int X, int Y) {
  chrtMain->ShowHint = false;
  TDataItem::Ptr Item=Search(X, Y);
  if(!Item->Id) return;
  chrtMain->Hint = Item->Name;
  chrtMain->ShowHint = true;
}
//---------------------------------------------------------------------------

