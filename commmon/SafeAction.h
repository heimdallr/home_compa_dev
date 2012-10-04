#ifndef SafeActionH
#define SafeActionH
#include <Classes.hpp>
#include <ActnList.hpp>
#include <map>
//---------------------------------------------------------------------------
class TSafeAction {
typedef std::map<unsigned long, TNotifyEvent> TActionMap;
  TActionMap _actions;
  void __fastcall Load(TComponent *C);
  void __fastcall OnExecute(TObject*);
public:
  __fastcall TSafeAction(TComponent*);
  __fastcall ~TSafeAction();
};
//---------------------------------------------------------------------------
#endif
