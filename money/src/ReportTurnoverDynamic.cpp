#include <vcl.h>
#pragma hdrstop
#include "ReportTurnoverDynamic.h"
#include "DataSetLayout.h"
#include "CatalogUnit.h"
#include "Options.h"
#include "Doc.h"
#include "DocStr.h"
#include "GridUtils.h"
#include "Const.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "DataDriverEh"
#pragma link "DBGridEh"
#pragma link "DBGridEhGrouping"
#pragma link "GridsEh"
#pragma link "MemTableDataEh"
#pragma link "MemTableEh"
#pragma link "ReportBaseTotal"
#pragma link "DBCtrlsEh"
#pragma link "DBLookupEh"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TReport::TReportListInserter TfmReportTurnoverDynamic::ReportListInserter("Динамика движения средств...", &TfmReportTurnoverDynamic::GetInstance);

// Конструктор
__fastcall TfmReportTurnoverDynamic::TfmReportTurnoverDynamic() : _person(ns_GridUtils::FindColumn(dbgStr, "TARGET_PERSON_NAME")) {
  NullLine->LinePen->Width = 4;
}
void __fastcall TfmReportTurnoverDynamic::FormPaint(TObject *Sender) {
  OnPaint = 0;
  TfmReportBaseTotal::FormPaint(Sender);
  TOptions::Instance->RestoreLayout(pnlData);
  TOptions::Instance->RestoreLayout(dbgData);
  TOptions::Instance->RestoreLayout(dbgDoc);
  TOptions::Instance->RestoreLayout(dbgStr);
}
void __fastcall TfmReportTurnoverDynamic::FormDestroy(TObject *Sender) {
  TOptions::Instance->SaveLayout(dbgStr);
  TOptions::Instance->SaveLayout(dbgDoc);
  TOptions::Instance->SaveLayout(dbgData);
  TOptions::Instance->SaveLayout(pnlData);
  TfmReportBaseTotal::FormDestroy(Sender);
}
//---------------------------------------------------------------------------

// Работаем
void __fastcall TfmReportTurnoverDynamic::Run() {
  NullLine->Clear();
  Ser->Clear();
  _search.clear();
  TDSPtr Data = TConnect::Instance->GetReadDataSet("select * from report_turnover_dynamic(:date_from, :date_to, :date_interval_type)", TQueryParams().Add(ftDate, "date_from", _from).Add(ftDate, "date_to", _to).Add(ftInteger, "date_interval_type", _id_interval), GetCatalogTransaction());
  for(; !Data->Eof; Data->Next()) {
    double Summa = Data->FieldByName("summa")->AsFloat;
    double X = (Data->FieldByName("interval_from")->AsFloat + Data->FieldByName("interval_to")->AsFloat)/2;
    _search.insert(TSearchList::value_type(Ser->AddXY(TDateTime(X), Summa, "", Summa>0 ? clBlue : clRed), Data->FieldByName("ord_num")->AsInteger));
    NullLine->AddXY(Data->FieldByName("interval_from")->AsFloat, 0);
  }
  NullLine->AddXY(Data->FieldByName("interval_to")->AsFloat, 0);
  dsData->Data = Data->Data;
}
//---------------------------------------------------------------------------

// Показываем список документов
void __fastcall TfmReportTurnoverDynamic::dbgDataRowDetailPanelShow(TCustomDBGridEh *Sender, bool &CanShow) {
  dsDoc->Data = TDoc::GetInstance(dsData->FieldByName("interval_from")->AsDateTime, dsData->FieldByName("interval_to")->AsDateTime, GetCatalogTransaction())->GetDataSet()->Data;
}
//---------------------------------------------------------------------------

// Показываем строки документов
void __fastcall TfmReportTurnoverDynamic::dbgDocRowDetailPanelShow( TCustomDBGridEh *Sender, bool &CanShow) {
  _person->FieldName = TConst::Instance()->Get("tsf")->AsInteger==dsDoc->FieldByName("id_doc_type")->AsInteger ? "DEPOSIT_TO_NAME" : "TARGET_PERSON_NAME";
  _person->Title->Caption = TConst::Instance()->Get("tsf")->AsInteger==dsDoc->FieldByName("id_doc_type")->AsInteger ? "Счет-приемник" : "Виновник";
  dsStr->Data = TDocStr::GetInstance(dsDoc->FieldByName("id")->AsInteger, GetCatalogTransaction())->GetDataSet()->Data;
}
//---------------------------------------------------------------------------

// Раскрашиваем строки документов на основании указанной фильтрации
void __fastcall TfmReportTurnoverDynamic::dbgStrGetCellParams( TObject *Sender, TColumnEh *Column, TFont *AFont, TColor &Background, TGridDrawState State) {
  if(dsStr->FieldByName("id_str_type_exists")->AsInteger && dsStr->FieldByName("id_target_person_exists")->AsInteger)
    AFont->Style = TFontStyles()<<fsBold;
  else AFont->Style = TFontStyles()<<fsItalic;
}
//---------------------------------------------------------------------------

// Ищем интервал дат по кликнутому столбику
void __fastcall TfmReportTurnoverDynamic::chrtMainClickSeries(TCustomChart *Sender, TChartSeries *Series, int ValueIndex, TMouseButton Button, TShiftState Shift, int X, int Y) {
  TSearchList::const_iterator I=_search.find(ValueIndex);
  if(_search.end()==I) return chrtMain->SetFocus();
  if(!dsData->Locate("ord_num", I->second, TLocateOptions()))
    return chrtMain->SetFocus();
  dbgData->SetFocus();
}
//---------------------------------------------------------------------------


