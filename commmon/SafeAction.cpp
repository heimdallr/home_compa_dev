#include <Forms.hpp>
#include <IB.hpp>
#pragma hdrstop
#include "SafeAction.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------


__fastcall TSafeAction::TSafeAction(TComponent *C) {
  Load(C);
}
//---------------------------------------------------------------------------

__fastcall TSafeAction::~TSafeAction() {
  for(TActionMap::const_iterator i=_actions.begin(); i!=_actions.end(); ++i)
    reinterpret_cast<TContainedAction*>(i->first)->OnExecute = i->second;
}
//---------------------------------------------------------------------------

void __fastcall TSafeAction::Load(TComponent *C) {
  if(TContainedAction *Action = dynamic_cast<TContainedAction*>(C)) {
    _actions.insert(TActionMap::value_type(reinterpret_cast<unsigned long>(Action), Action->OnExecute));
    Action->OnExecute = OnExecute;
  }
  else
    for(int i=0; i<C->ComponentCount; ++i)
      Load(C->Components[i]);
}
//---------------------------------------------------------------------------

void __fastcall TSafeAction::OnExecute(TObject *Action) {
  TActionMap::const_iterator I = _actions.find(reinterpret_cast<unsigned long>(Action));
  try {
    if(_actions.end()==I)
      throw Exception("Системная ошибка");
    if(!I->second)
      return;
    I->second(Action);
  }
  catch(EIBError &E) {
    int N=E.Message.Pos("#"), M=E.Message.LastDelimiter("$");
    String Message = N>0&&M>0 ? E.Message.SubString(N+1, M-N-1) : E.Message;
    Application->MessageBox(Message.c_str(), "Внимание!", MB_ICONERROR);
  }
  catch(Exception &E) {
    Application->MessageBox(E.Message.c_str(), "Внимание!", MB_ICONERROR);
  }
  catch(...) {
    Application->MessageBox("Системная ошибка", "Внимание!", MB_ICONERROR);
  }
}
//---------------------------------------------------------------------------

