#include <vcl.h>
#pragma hdrstop
#include "DBLoginUnit.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

// Конструктор
__fastcall TfmLogin::TfmLogin(TPropertyMap &P) : TForm(static_cast<TComponent*>(0)), _p(P), _on_change(0) {
  const TfmLogin::TParamMap &PM = GetParamMap();
  for(TParamMap::const_iterator i=PM.begin(); i!=PM.end(); ++i)
    i->second.second->Text = _p[i->second.first];
  _on_change = OnChangeImpl;
}
void __fastcall TfmLogin::FormPaint(TObject *Sender) {
  OnPaint=0;
  gbHost->Width = gbHost->Parent->Width/2;
  gbUser->Width = gbUser->Parent->Width/2;
  gbCType->Width = gbCType->Parent->Width/2;
  btnOk->Left = (btnOk->Parent->Width - btnOk->Width)/2;
}
//---------------------------------------------------------------------------

TfmLogin::TParamMapPtr __fastcall TfmLogin::InitParamMap() {
  TParamMapPtr P(new TParamMap());
  P->insert(TParamMap::value_type(pc_Host,          TParam("Host",          eHost)));
  P->insert(TParamMap::value_type(pc_DatabaseName,  TParam("DatabaseName",  eDatabaseName)));
  P->insert(TParamMap::value_type(pc_User,          TParam("User",          eUser)));
  P->insert(TParamMap::value_type(pc_Password,      TParam("Password",      ePwd)));
  P->insert(TParamMap::value_type(pc_CType,         TParam("CType",         eCType)));
  return P;
}
const TfmLogin::TParamMap& __fastcall TfmLogin::GetParamMap() {
  static TParamMapPtr pParamMap = InitParamMap();
  return *pParamMap.get();
}
//---------------------------------------------------------------------------


// Нажали Ok
void __fastcall TfmLogin::actOkExecute(TObject *Sender) {
  Close();
  const TfmLogin::TParamMap &P = GetParamMap();
  for(TParamMap::const_iterator i=P.begin(); i!=P.end(); ++i)
    if(_f&i->first)
      _p.Set(i->second.first, i->second.second->Text);
  ModalResult = cbSavePwd->Checked ? mrYes : mrNo;
}
//---------------------------------------------------------------------------

// Выход
void __fastcall TfmLogin::actCancelExecute(TObject *Sender) {
  Close();
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

// Нажатие на Enter - движемся в следующий Control
void __fastcall TfmLogin::eKeyPress(TObject *Sender, char &Key) {
  if(VK_RETURN==Key)
    SelectNext(ActiveControl, true, true);
}
//---------------------------------------------------------------------------

void __fastcall TfmLogin::eChange(TObject *Sender) {
  if(_on_change)
    _on_change(Sender);
}
//---------------------------------------------------------------------------

