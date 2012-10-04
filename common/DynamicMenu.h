#ifndef DynamicMenuH
#define DynamicMenuH
#include <Classes.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TDynamicMenu {
public:
  __fastcall TDynamicMenu(const String &strQuery, TMenuItem *miParent, TNotifyEvent OnClick);
  __fastcall ~TDynamicMenu() {}
};
#endif
 