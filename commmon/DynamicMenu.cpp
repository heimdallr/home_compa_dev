//---------------------------------------------------------------------------


#pragma hdrstop

#include "DynamicMenu.h"
#include "Connect.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
__fastcall TDynamicMenu::TDynamicMenu(const String &strQuery, TMenuItem *miParent, TNotifyEvent OnClick) {
  for(TSQLPtr SQL=TConnect::Instance->GetReadSQL(strQuery, true); !SQL->Eof; SQL->Next()) {
    TMenuItem *miNew = new TMenuItem(miParent);
    miNew->Tag      = SQL->FieldByName("id")->AsInteger;
    miNew->Caption  = SQL->FieldByName("name")->AsString;
    miNew->OnClick  = OnClick;
    miParent->Add(miNew);
  }
}
//---------------------------------------------------------------------------

