#pragma hdrstop
#include <vcl.h>
#include "ReportLauncher.h"
#include "ReportBase.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

// �����������
__fastcall TdmReportLauncher::TdmReportLauncher()
  : TDataModule(static_cast<TComponent*>(0)), _id(-1), _safe_action(this)
{
}
//---------------------------------------------------------------------------

// ���������
TdmReportLauncher* __fastcall TdmReportLauncher::GetInstance() {
  static Ptr L(new TdmReportLauncher());
  return L.get();
}
//---------------------------------------------------------------------------

// ��� �� ������ �� ����
void __fastcall TdmReportLauncher::OnClick(TObject *Sender) {
  _id = dynamic_cast<TComponent*>(Sender)->Tag;
  actRun->OnExecute(actRun);
}
//---------------------------------------------------------------------------

// �������� ������ ������
void __fastcall TdmReportLauncher::actRunExecute(TObject *Sender) {
  TReport::TReportList &R = TReport::GetReportList();
  if(_id>=R.size()) throw Exception(String().sprintf("����������� �������� Tag � ������ ����: %du", _id));
  R[_id].second()->Show();
}
//---------------------------------------------------------------------------

