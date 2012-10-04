#include "DynamicAction.h"
#include "Connect.h"
#pragma hdrstop
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall TDynamicAction::TDynamicAction(TActionList *ActionList, const String &Catalog, TNotifyEvent OnExecute, TMenu *Menu) {
  bool Rec=false, AddAll=false;
  String Query=String().sprintf(
    "select c.* "
    "from z_const z "
    "left join sel_catalog(z.%s, %d, %d) c on 1=1", Catalog, (Rec?1:0), (AddAll?1:0));
  for(TDSPtr dsData = TConnect::Instance->GetReadDataSet(Query); !dsData->Eof; dsData->Next()) {
    TAction *Action = new TAction(ActionList);
    Action->ActionList = ActionList;
    Action->OnExecute = OnExecute;
    Action->Tag = dsData->FieldByName("id")->AsInteger;
    Action->Caption = dsData->FieldByName("name")->AsString;
    if(Menu) {
      TMenuItem *Item = new TMenuItem(Menu);
      Item->Action = Action;
      Menu->Items->Add(Item);
    }
  }
}
//---------------------------------------------------------------------------
