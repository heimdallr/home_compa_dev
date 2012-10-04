#include <vcl.h>
#pragma hdrstop
#include <limits>
#include "ReportStock.h"
#include "Options.h"
#include "DataSetLayout.h"
#include "GridUtils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ReportBase"
#pragma link "DBGridEh"
#pragma link "DBGridEhGrouping"
#pragma link "GridsEh"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

// Конструктор/деструктор
TReport::TReportListInserter TfmReportStock::ReportListInserter("Остатки на счетах...", TfmReportStock::GetInstance);
__fastcall TfmReportStock::TfmReportStock() {
  SaveCatalog(true);
  LoadCatalog();
  for(dsDeposit->First(); !dsDeposit->Eof; dsDeposit->Next())
    _color.insert(TColorMap::value_type(dsDeposit->FieldByName("id")->AsInteger, static_cast<TColor>(dsDeposit->FieldByName("color")->AsInteger)));
}
void __fastcall TfmReportStock::FormPaint(TObject *Sender) {
  OnPaint = 0;
  TOptions::Instance->RestoreLayout(dbgDeposit);
  TfmReportBase::FormPaint(Sender);
}
void __fastcall TfmReportStock::FormDestroy(TObject *Sender) {
  TOptions::Instance->SaveLayout(dbgDeposit);
  TfmReportBase::FormDestroy(Sender);
}
//---------------------------------------------------------------------------

// Работаем с датасетами настроек
void __fastcall TfmReportStock::LoadCatalog() {
  TDataSetLayout DSLD(dsDeposit);
  TReport::LoadCatalog(dsDeposit, "deposit");
}
void __fastcall TfmReportStock::SaveCatalog(bool FullMode) {
  TIBTransaction *T=GetCatalogTransaction();
  if(T->Active) T->Commit();
  T->StartTransaction();
  TReport::SaveCatalog(dsDeposit, "deposit", FullMode);
}
//---------------------------------------------------------------------------

// Костыль. Настроечные датасеты в статусе Edit не задерживаем
void __fastcall TfmReportStock::dbgDepositMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y) {
  Timer->Enabled = true;
}
void __fastcall TfmReportStock::TimerTimer(TObject *Sender) {
  Timer->Enabled = false;
  if(dsEdit==dsDeposit->State) dsDeposit->Post();
}
//---------------------------------------------------------------------------

// Рисуем
__fastcall TfmReportStock::TSer::TSer(TChart *Chart, TDateTime X, double V, TColor C) : _ser(new TLineSeries(0)), _val(V), _color(C) {
  _ser->LinePen->Width=2;
  _ser->XValues->DateTime=true; Chart->AddSeries(_ser);
  _ser->AddXY(X, V, "", _color);
}
void __fastcall TfmReportStock::TSer::Add(TDateTime X1, TDateTime X2, double V) {
  _ser->AddXY(X1, _val, "", _color);
  _ser->AddXY(X2, _val+=V, "", _color);
}
//---------------------------------------------------------------------------

// Работаем
void __fastcall TfmReportStock::Run() {
  for(int i=0; i<chrtMain->SeriesList->Count; ++i) delete chrtMain->SeriesList->operator [](i);
  chrtMain->SeriesList->Clear();

  TSer::List Ser;
  TDateTime MaxTo=std::numeric_limits<TDateTime>::min();
  TDSPtr Data = TConnect::Instance->GetReadDataSet("select * from report_stock(:date_from, :date_to, :date_interval_type)", TQueryParams().Add(ftDate, "date_from", _from).Add(ftDate, "date_to", _to).Add(ftInteger, "date_interval_type", _id_interval), GetCatalogTransaction());
  Data->IndexFieldNames = "ord_num";
  for(Data->First(); !Data->Eof; Data->Next()) {
    if(MaxTo<Data->FieldByName("interval_to")->AsDateTime) MaxTo=Data->FieldByName("interval_to")->AsDateTime;
    if(Data->FieldByName("ord_num")->AsInteger)
      Ser.find(Data->FieldByName("id_deposit")->AsInteger)->second->Add(Data->FieldByName("interval_from")->AsDateTime, Data->FieldByName("interval_to")->AsDateTime, Data->FieldByName("summa")->AsFloat);
    else
      Ser.insert(TSer::List::value_type(Data->FieldByName("id_deposit")->AsInteger, TSer::Ptr(new TSer(chrtMain, Data->FieldByName("interval_to")->AsDateTime, Data->FieldByName("summa")->AsFloat, _color[Data->FieldByName("id_deposit")->AsInteger]))));
  }
  for(TSer::List::iterator i=Ser.begin(); i!=Ser.end(); ++i)
    i->second->Add(MaxTo, MaxTo, 0);
  TSer::Ptr(new TSer(chrtMain, _from, 0, clBlack))->Add(MaxTo, MaxTo, 0);
}
//---------------------------------------------------------------------------




void __fastcall TfmReportStock::dbgDepositDrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumnEh *Column,
      TGridDrawState State)
{
  ns_GridUtils::DataDrawColumnCell(Sender, Rect, DataCol, Column, State);
}
//---------------------------------------------------------------------------

void __fastcall TfmReportStock::dbgDepositGetCellParams(TObject *Sender,
      TColumnEh *Column, TFont *AFont, TColor &Background,
      TGridDrawState State)
{
  ns_GridUtils::DataGetCellParams(Sender, Column, AFont, Background, State);
}
//---------------------------------------------------------------------------

