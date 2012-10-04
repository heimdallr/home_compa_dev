//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Connect.h"
#include "Functions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TdmConnect *TConnect::Instance=0;
void __fastcall TdmConnect::Execute(TIBSQL *SQL) {
  try {
    SQL->ExecQuery();
    SQL->Transaction->Commit();
  } catch(...) {
    SQL->Transaction->Rollback();
    throw;
  }
}
//---------------------------------------------------------------------------

void __fastcall TConnect::TEventMessage::TEventList::Init(const String &Str) {
  ns_Functions::TStrListPtr pStr(Split(Str, ';'));
  for(int i=0; i<pStr->Count; ++i)
    _l.push_back(pStr->Strings[i]);
}
//---------------------------------------------------------------------------

int __fastcall TConnect::TEventMessage::TEventList::Fill(TStrings *S) const {
  for(Impl::const_iterator i=_l.begin(); i!=_l.end(); ++i)
    if(!i->IsEmpty())
      S->Add(*i);
  return _l.size();
}
//---------------------------------------------------------------------------

