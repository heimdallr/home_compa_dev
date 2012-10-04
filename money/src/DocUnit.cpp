#include <vcl.h>
#pragma hdrstop
#include "DocUnit.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

// Конструктор
__fastcall TfmDoc::TfmDoc(String &Note, TDate &D, const String &C) : TForm(static_cast<TComponent*>(0)), _note(Note), _date(D) {
  Caption = C;
  eNote->Text = _note;
  dtDate->Date = _date;
}
//---------------------------------------------------------------------------

// Нажали отмену
void __fastcall TfmDoc::actCancelExecute(TObject *Sender) {
  Close();
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

// Нажали ОК
void __fastcall TfmDoc::actOkExecute(TObject *Sender) {
  _note = eNote->Text;
  _date = dtDate->Date;
  Close();
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------
