//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CatalogUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "DBGridEhGrouping"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

using namespace ns_Catalog;

// Отдаем данные справочника
TDSPtr __fastcall ns_Catalog::Get(const TInit &Init) {
  TCatalogPtr Catalog(new TfmCatalog(Init));
  if(mrOk!=Catalog->ShowModal()) return TDSPtr(0);
  return Catalog->GetDataSet();
}
//---------------------------------------------------------------------------

// Тянем данные справочника
__fastcall TInit::TInit(const String &IdField, const String &Query, const String &Caption, const Variant &Def) : _id_field_name(IdField), _caption(Caption), _query(Query), _def(Def) {
}
TDSPtr __fastcall TInit::GetDataSet() const {
  return TConnect::Instance->GetReadDataSet(_query, _params);
}
//---------------------------------------------------------------------------

// Тянем данные, готовим отображение
__fastcall TfmCatalog::TfmCatalog(const TInit &Init) : TForm(static_cast<TComponent*>(0)), _id_field_name(Init._id_field_name) {
  Caption = Init._caption;
  dsData->Data = Init.GetDataSet()->Data;
  if(!dsData->Locate(_id_field_name, Init._def, TLocateOptions())) dsData->First();
  int n=0;
  for(TFieldInitIt i=Init._field.begin(); i!=Init._field.end(); ++i, ++n) {
    TColumnEh *Col = dbgData->Columns->Items[n];
    Col->Title->Caption = i->_name;
    Col->Width = 10*i->_width;
    Col->Visible = !i->_name.IsEmpty();
    Col->HideDuplicates = i->_hide_dup;
  }
  dbgData->AutoFitColWidths = true;
}
//---------------------------------------------------------------------------

// OK/Отмена
void __fastcall TfmCatalog::actOkExecute(TObject *Sender) {
  Close();
  ModalResult = mrOk;
}
void __fastcall TfmCatalog::actCancelExecute(TObject *Sender) {
  Close();
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

TDSPtr __fastcall TfmCatalog::GetDataSet() {
  if(dsData->IsEmpty()) return TDSPtr(0);
  TDSPtr Res(new TClientDataSet(0));
  Res->Data = dsData->Data;
  Res->Filter = String().sprintf("%s=%s", _id_field_name, dsData->FieldByName(_id_field_name)->AsString);
  Res->Filtered = true;
  return Res;
}
//---------------------------------------------------------------------------

