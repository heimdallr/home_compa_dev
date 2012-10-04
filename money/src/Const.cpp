//---------------------------------------------------------------------------


#pragma hdrstop

#include "Const.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

__fastcall TConst::TConst() : _data(TConnect::Instance->GetReadDataSet("select * from z_const")) {
}
//---------------------------------------------------------------------------

TConst* TConst::Instance() {
  static Ptr I(new TConst());
  return I.get();
}
//---------------------------------------------------------------------------

