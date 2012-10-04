#include <vcl.h>
#pragma hdrstop
#include "CatalogUnit.h"
#include "TransactionPtr.h"
#include "GetStringUnit.h"
#include "DataSetLayout.h"
#include "GridUtils.h"
#include "Options.h"
#include "ActivePtr.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "DataDriverEh"
#pragma link "MemTableDataEh"
#pragma link "MemTableEh"
#pragma link "DBGridEhGrouping"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

__fastcall TfmCatalog::TTreeKeeper::TTreeKeeper(TMemTableEh *Data) : _data(Data), _id(Data->FieldByName("id")->AsInteger) {
  for(_data->First(); !_data->Eof; _data->Next())
    _storage.insert(TStorage::value_type(_data->FieldByName("id")->AsInteger, _data->TreeNode->NodeExpanded));
}
__fastcall TfmCatalog::TTreeKeeper::~TTreeKeeper() {
  for(_data->First(); !_data->Eof; _data->Next())
    _data->TreeNode->NodeExpanded = _storage[_data->FieldByName("id")->AsInteger];
  if(!_data->Locate("id", _id, TLocateOptions()))
    _data->First();
}
void __fastcall TfmCatalog::FormPaint(TObject *Sender) {
  OnPaint = 0;
  TOptions::Instance->RestoreLayout(this);
  TOptions::Instance->RestoreLayout(dbgData);
}
//---------------------------------------------------------------------------

String __fastcall TfmCatalog::TInit::GetQuery(const String &Obj, bool Rec, bool AA) {
  return String().sprintf(
    "select c.* "
    "from z_const z "
    "left join sel_catalog(z.%s, %d, %d) c on 1=1", Obj, (Rec?1:0), (AA?1:0));
}
String __fastcall TfmCatalog::TInit::GetQuery(int IdParent, bool Rec, bool AA) {
  return String().sprintf("select * from sel_catalog(%d, %d, %d)", IdParent, (Rec?1:0), (AA?1:0));
}
void __fastcall TfmCatalog::TInit::Init(bool Rec, const String &C) {
  Recursively = Rec;
  Caption = C;
}
//---------------------------------------------------------------------------

// Конструктор
__fastcall TfmCatalog::TfmCatalog(const TInit &I, TClientDataSet *Data) :
TForm(static_cast<TComponent*>(0)), _init(I),
_event(TConnect::Instance->SetEventHandler("catalog", OnEvent)),
_safe_action(this)
{
  Caption = _init.Caption;
  Init(Data);
}
void __fastcall TfmCatalog::Init(TClientDataSet *Data) {
  dsData->Data = Data->Data;
  dsData->IndexFieldNames = "ord_num";
  dsData->First();
  mtData->Active = true;
  if(_init.Recursively) {
    mtData->TreeList->Active = true;
    mtData->Last();
    mtData->First();
  }
}
void __fastcall TfmCatalog::FormDestroy(TObject *Sender) {
  dbgData->Parent = pnlMain;
  TOptions::Instance->SaveLayout(dbgData);
  TOptions::Instance->SaveLayout(this);
}

// Словили событие - перезагружаемся
void __fastcall TfmCatalog::OnEvent(TObject *Sender, AnsiString EventName, int EventCount, bool &CancelAlerts) {
  TTreeKeeper PK(mtData);
  TDSPtr Data = GetDataSet(_init);
  mtData->TreeList->Active = false;
  mtData->Active = false;
  Init(Data.get());
}
//---------------------------------------------------------------------------

// Отдаем справочник
TfmCatalog::Ptr TfmCatalog::GetInstance(const TfmCatalog::TInit &I) {
  TDSPtr Data = GetDataSet(I);
  return Ptr(new TCatalog(I, Data.get()));
}
//---------------------------------------------------------------------------

// Выбираем запись из справочника
TDSPtr TfmCatalog::Get(const TfmCatalog::TInit &I) {
  TDSPtr Data = GetDataSet(I);
  return GetRes(I, Data);
}
//---------------------------------------------------------------------------

// Тащим данные справочника
TDSPtr TfmCatalog::GetDataSet(const TfmCatalog::TInit &I) {
  TDSPtr Res=TConnect::Instance->GetReadDataSet(I.Query);
  Res->IndexFieldNames = "ord_num";
  Res->First();
  return Res;
}
//---------------------------------------------------------------------------

// Тащим данные по готовому датасету, который вернется отфильтованным
TDSPtr TfmCatalog::GetRes(const TInit &I, TDSPtr Data) {
  Ptr Catalog(new TCatalog(I, Data.get()));
  if(Catalog->ShowModal()<0) return TDSPtr(0);
  Data->Filter = String().sprintf("id=%d", Catalog->mtData->FieldByName("id")->AsInteger);
  Data->Filtered = true;
  return Data;
}
//---------------------------------------------------------------------------

// Нажали Ок
void __fastcall TfmCatalog::actOkExecute(TObject *Sender) {
  Close();
  ModalResult = mtData->IsEmpty() ? -1 : mtData->FieldByName("id")->AsInteger;
}
//---------------------------------------------------------------------------

// Нажали отмену
void __fastcall TfmCatalog::actCancelExecute(TObject *Sender) {
  Close();
  ModalResult = -1;
}
//---------------------------------------------------------------------------

// Модификации справочника
void __fastcall TfmCatalog::Add(int IdParent) {
  String Caption="";
  if(!GetString(Caption, "Укажите наименование")) return;
  TSQLPtr SQL = TConnect::Instance->GetWriteSQL("select * from add_catalog(:id_p, :name)", false);
  TTranPtr TR(SQL->Transaction);
  SQL->ParamByName("id_p")->AsInteger = IdParent;
  SQL->ParamByName("name")->AsString = Caption;
  SQL->ExecQuery();
  SQL->Transaction->Commit();
}
void __fastcall TfmCatalog::actAddExecute(TObject *Sender) {
  Add(mtData->FieldByName("id_p")->AsInteger);
}
void __fastcall TfmCatalog::actAddChildExecute(TObject *Sender) {
  Add(mtData->FieldByName("id")->AsInteger);
}
void __fastcall TfmCatalog::Set(int Id, const String &Name, const Variant &Value) {
  TSQLPtr SQL = TConnect::Instance->GetWriteSQL(String().sprintf("execute procedure set_catalog_%s(:id, :%s)", Name, Name), false);
  TTranPtr TR(SQL->Transaction);
  SQL->ParamByName("id")->AsInteger = Id;
  SQL->ParamByName(Name)->AsString = Value;
  SQL->ExecQuery();
  SQL->Transaction->Commit();
}
void __fastcall TfmCatalog::SetCatalogColor(int Id, int Color) {
  std::auto_ptr<TColorDialog> dlgColor(new TColorDialog(0));
  dlgColor->Color = static_cast<TColor>(Color);
  if(!dlgColor->Execute()) return;
  Set(Id, "color", static_cast<int>(dlgColor->Color));
}
void __fastcall TfmCatalog::SetCatalogName(int Id, String Caption) {
  if(!GetString(Caption, "Укажите наименование")) return;
  Set(Id, "name", Caption);
}
void __fastcall TfmCatalog::SetCatalogQty(int Id, double Qty) {
  Set(Id, "qty", Qty);
}
void __fastcall TfmCatalog::SetCatalogOrdNum(int Id, int Direction) {
  Set(Id, "ord_num", Direction);
}
void __fastcall TfmCatalog::actEditExecute(TObject *Sender) {
  SetCatalogName(mtData->FieldByName("id")->AsInteger, mtData->FieldByName("name")->AsString);
}
void __fastcall TfmCatalog::actSetColorExecute(TObject *Sender) {
  SetCatalogColor(mtData->FieldByName("id")->AsInteger, mtData->FieldByName("color")->AsInteger);
}
void __fastcall TfmCatalog::actDelExecute(TObject *Sender) {
  if(ID_YES != Application->MessageBox("Действительно удалить строку из справочника?", "Внимание", MB_ICONWARNING|MB_YESNO|MB_DEFBUTTON2)) return;
  TSQLPtr SQL = TConnect::Instance->GetWriteSQL("execute procedure del_catalog(:id)", false);
  TTranPtr TR(SQL->Transaction);
  SQL->ParamByName("id")->AsInteger = mtData->FieldByName("id")->AsInteger;
  SQL->ExecQuery();
  SQL->Transaction->Commit();
}
//---------------------------------------------------------------------------

// Свернули/развернули
void __fastcall TfmCatalog::actCollapseExecute(TObject *Sender) {
  mtData->TreeList->FullCollapse();
}
void __fastcall TfmCatalog::actExpandExecute(TObject *Sender) {
  mtData->TreeList->FullExpand();
}
//---------------------------------------------------------------------------

// Свернули
void __fastcall TfmCatalog::Collapse() {
  {
    TActiveSet<TMemTableTreeListEh> APTL(mtData->TreeList);
    TActiveSet<TMemTableEh> APMT(mtData);
    mtData->TreeList->DefaultNodeExpanded = false;
  }
  mtData->Last();
  mtData->First();
}
//---------------------------------------------------------------------------

// Развернули
void __fastcall TfmCatalog::Expand() {
  TDataSetLayout DSL(mtData);
  {
    TActiveSet<TMemTableTreeListEh> APTL(mtData->TreeList);
    TActiveSet<TMemTableEh> APMT(mtData);
    mtData->TreeList->DefaultNodeExpanded = true;
  }
  mtData->Last();
  mtData->First();
}
//---------------------------------------------------------------------------

// Встаём куда просят
void __fastcall TfmCatalog::Locate(int Id) {
  if(!mtData->Locate("id", Id, TLocateOptions()))
    mtData->First();
}
//---------------------------------------------------------------------------

// Прячем кого надо
void __fastcall TfmCatalog::Hide(int Id) {
  if(mtData->Locate("id", Id, TLocateOptions()))
    mtData->Delete();
  mtData->First();
}
//---------------------------------------------------------------------------

// Отдаем поле по имени
TField* __fastcall TfmCatalog::FieldByName(const String &FieldName) const {
  return mtData->FieldByName(FieldName);
}
//---------------------------------------------------------------------------

// Нажали влево/вправо
void __fastcall TfmCatalog::actLeftExecute(TObject *Sender) {
  ns_GridUtils::LeftExecute(Sender, ActiveControl);
}
void __fastcall TfmCatalog::actRightExecute(TObject *Sender) {
  ns_GridUtils::RightExecute(Sender, ActiveControl);
}
//---------------------------------------------------------------------------

// Красим строки
void __fastcall TfmCatalog::dbgDataGetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont, TColor &Background, TGridDrawState State) {
  ns_GridUtils::DataGetCellParams(Sender, Column, AFont, Background, State);
}
void __fastcall TfmCatalog::dbgDataDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol, TColumnEh *Column, TGridDrawState State) {
  ns_GridUtils::DataDrawColumnCell(Sender, Rect, DataCol, Column, State);
}
//---------------------------------------------------------------------------

void __fastcall TfmCatalog::actUpExecute(TObject *Sender) {
  SetCatalogOrdNum(mtData->FieldByName("id")->AsInteger, dynamic_cast<TComponent*>(Sender)->Tag);
}
void __fastcall TfmCatalog::actDownExecute(TObject *Sender) {
  SetCatalogOrdNum(mtData->FieldByName("id")->AsInteger, dynamic_cast<TComponent*>(Sender)->Tag);
}
//---------------------------------------------------------------------------

