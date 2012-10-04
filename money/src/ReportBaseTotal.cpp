#include <vcl.h>
#pragma hdrstop
#include <set>
#include <queue>
#include "ReportBaseTotal.h"
#include "CatalogUnit.h"
#include "Const.h"
#include "DataSetLayout.h"
#include "Options.h"
#include "GridUtils.h"
#include "ActivePtr.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "ReportBase"
#pragma link "DataDriverEh"
#pragma link "DBGridEh"
#pragma link "DBGridEhGrouping"
#pragma link "GridsEh"
#pragma link "MemTableDataEh"
#pragma link "MemTableEh"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

// Конструктор/деструктор
__fastcall TfmReportBaseTotal::TfmReportBaseTotal(TDate From, TDate To)
  : TfmReportBase(From, To)
{
  SaveCatalog(true);
  LoadCatalog();
  mtState->TreeList->FullCollapse();
}
void __fastcall TfmReportBaseTotal::FormPaint(TObject *Sender) {
  OnPaint = 0;
  TOptions::Instance->RestoreLayout(pnlOpts);
  TOptions::Instance->RestoreLayout(dbgPerson);
  TOptions::Instance->RestoreLayout(dbgDeposit);
  TOptions::Instance->RestoreLayout(dbgState);
  TfmReportBase::FormPaint(Sender);
}
void __fastcall TfmReportBaseTotal::FormDestroy(TObject *Sender) {
  TOptions::Instance->SaveLayout(dbgState);
  TOptions::Instance->SaveLayout(dbgDeposit);
  TOptions::Instance->SaveLayout(dbgPerson);
  TOptions::Instance->SaveLayout(pnlOpts);
  TfmReportBase::FormDestroy(Sender);
}
//---------------------------------------------------------------------------

// Работаем с датасетами настроек
void __fastcall TfmReportBaseTotal::mtStateAfterPost(TDataSet *DataSet) {
  SetChecked(mtState, dsState);
  actRunReport->OnExecute(actRunReport);
}
void __fastcall TfmReportBaseTotal::LoadCatalog() {
  TDataSetLayout DSLS(mtState);
  TDataSetLayout DSLD(dsDeposit);
  TDataSetLayout DSLP(dsPerson);
  {
    TActiveSet<TMemTableTreeListEh> APTL(mtState->TreeList);
    TActiveSet<TMemTableEh> APMT(mtState);
    TReport::LoadCatalog(dsState, "operation", true);
  }
  mtState->Last();
  mtState->First();
  TReport::LoadCatalog(dsDeposit, "deposit");
  TReport::LoadCatalog(dsPerson, "pay_target");
}
void __fastcall TfmReportBaseTotal::SaveCatalog(bool FullMode) {
  TIBTransaction *T=GetCatalogTransaction();
  if(T->Active) T->Commit();
  T->StartTransaction();
  TReport::SaveCatalog(dsState, FullMode?"operation_out":"operation", FullMode);
  TReport::SaveCatalog(dsDeposit, "deposit", FullMode);
  TReport::SaveCatalog(dsPerson, "pay_target", FullMode);
}
//---------------------------------------------------------------------------

// Костыль. Настроечные датасеты в статусе Edit не задерживаем
void __fastcall TfmReportBaseTotal::dbgStateMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y) {
  Timer->Enabled = true;
}
void __fastcall TfmReportBaseTotal::TimerTimer(TObject *Sender) {
  Timer->Enabled = false;
  if(dsEdit==mtState->State) mtState->Post();
  if(dsEdit==dsDeposit->State) dsDeposit->Post();
  if(dsEdit==dsPerson->State) dsPerson->Post();

}
//---------------------------------------------------------------------------

// Работаем лево-право
void __fastcall TfmReportBaseTotal::actLeftExecute(TObject *Sender) {
  ns_GridUtils::LeftExecute(Sender, ActiveControl);
}
void __fastcall TfmReportBaseTotal::actRightExecute(TObject *Sender){
  ns_GridUtils::RightExecute(Sender, ActiveControl);
}
//---------------------------------------------------------------------------


