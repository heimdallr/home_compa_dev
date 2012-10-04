#include <vcl.h>
#pragma hdrstop
#include "DocUnit.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

// �����������
__fastcall TfmDoc::TfmDoc(String &Note, TDate &D, const String &C) : TForm(static_cast<TComponent*>(0)), _note(Note), _date(D) {
  Caption = C;
  eNote->Text = _note;
  dtDate->Date = _date;
}
//---------------------------------------------------------------------------

// ������ ������
void __fastcall TfmDoc::actCancelExecute(TObject *Sender) {
  Close();
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

// ������ ��
void __fastcall TfmDoc::actOkExecute(TObject *Sender) {
  _note = eNote->Text;
  _date = dtDate->Date;
  Close();
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------
