//---------------------------------------------------------------------------
#include <memory>
#include <vcl.h>
#pragma hdrstop

#include "GetStringUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

bool __fastcall GetString(String &Val, const String &Capt, const String &Condition) {
  std::auto_ptr<TfmGetString> fmGetString(new TfmGetString(Val, Capt, Condition));
  return mrOk==fmGetString->ShowModal();
}
//---------------------------------------------------------------------------
__fastcall TfmGetString::TfmGetString(String &Val, const String &Capt, const String &Condition) : TForm(static_cast<TComponent*>(0)), _val(Val), _condition(Condition.c_str()) {
  Caption = Capt;
  eVal->Text = Val;
}
//---------------------------------------------------------------------------

void __fastcall TfmGetString::actCancelExecute(TObject *Sender) {
  Close();
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TfmGetString::actOkExecute(TObject *Sender) {
  if(!boost::regex_match(eVal->Text.c_str(), _what, _condition)) {
    Application->MessageBox("Указанное значение некорректно", "Внимание!", MB_ICONWARNING);
    return;
  }
  _val = eVal->Text;
  Close();
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------

