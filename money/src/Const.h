#ifndef ConstH
#define ConstH
#include "Connect.h"
#include <memory>
//---------------------------------------------------------------------------
class TConst {
  TDSPtr _data;
public:
typedef std::auto_ptr<TConst> Ptr;
static TConst* Instance();
  __fastcall TConst();
  TField* __fastcall Get(const String &FieldName) const {return _data->FieldByName(FieldName);}
};
//---------------------------------------------------------------------------
#endif
