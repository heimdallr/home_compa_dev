
#ifndef OptionsH
#define OptionsH
#include <memory>
#include <Controls.hpp>
#include <SysUtils.hpp>
#include "DBGridEh.hpp"
#include "PropertyMap.h"
//---------------------------------------------------------------------------
class TOptions {
protected:
  __fastcall TOptions() {}
public:
typedef std::auto_ptr<TOptions> Ptr;
static Ptr GetInstance() {return Ptr(Instance = new TOptions());}
static TOptions* Instance;
  virtual __fastcall ~TOptions() {}
  virtual void      __fastcall Set(const String &NodeName, const String &AttrName, const String &Val) {};
  virtual String    __fastcall Get(const String &NodeName, const String &AttrName, const String &Def="") const {return Def;};
  virtual void      __fastcall SaveLayout(const TControl*)  {};
  virtual void      __fastcall SaveLayout(const TDBGridEh*) {};
  virtual void      __fastcall RestoreLayout(TControl*) const   {};
  virtual void      __fastcall RestoreLayout(TDBGridEh*) const  {};
  virtual TPropertyMap __fastcall GetPropMap(const String &NodeName) const {return TPropertyMap();}
};
//---------------------------------------------------------------------------
#endif
