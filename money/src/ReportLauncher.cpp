#pragma hdrstop
#include <vcl.h>
#include "ReportLauncher.h"
#include "ReportBase.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

// Конструктор
__fastcall TdmReportLauncher::TdmReportLauncher()
  : TDataModule(static_cast<TComponent*>(0)), _id(-1), _safe_action(this)
{
}
//---------------------------------------------------------------------------

// Синглетон
TdmReportLauncher* __fastcall TdmReportLauncher::GetInstance() {
  static Ptr L(new TdmReportLauncher());
  return L.get();
}
//---------------------------------------------------------------------------

// Это мы отдаем на клик
void __fastcall TdmReportLauncher::OnClick(TObject *Sender) {
  _id = dynamic_cast<TComponent*>(Sender)->Tag;
  actRun->OnExecute(actRun);
}
//---------------------------------------------------------------------------

// Реальный запуск отчета
void __fastcall TdmReportLauncher::actRunExecute(TObject *Sender) {
  TReport::TReportList &R = TReport::GetReportList();
  if(_id>=R.size()) throw Exception(String().sprintf("Неожиданное значение Tag у пункта меню: %du", _id));
  R[_id].second()->Show();
}
//---------------------------------------------------------------------------

