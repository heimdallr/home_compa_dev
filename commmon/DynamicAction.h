#ifndef DynamicActionH
#define DynamicActionH
#include <Menus.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
class TDynamicAction {
public:
  __fastcall TDynamicAction(TActionList *ActionList, const String &Catalog, TNotifyEvent OnExecute, TMenu *Menu=0);
};
#endif
