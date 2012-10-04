#ifndef LoggerImplH
#define LoggerImplH
#include "Logger.h"
#include <map>
//---------------------------------------------------------------------------

class TLoggerImpl : public TLogger {
friend TLogger::Ptr __fastcall TLogger::GetInstance(const TPropertyMap &);
  const TLogger* __fastcall Warn(const String &Val) const {return Info(String().sprintf("Warning: %s", Val));}
  const TLogger* __fastcall Err(const String &Val)  const {return Info(String().sprintf("Error: %s", Val));}
  void __fastcall Reset() {}
protected:
typedef TLogger* __fastcall (*TGetInstance)(const TPropertyMap&);
typedef std::map<String, TGetInstance> TGetInstanceList;
static TGetInstanceList _get_instance_list;
  class TGetInstanceInserter {
  public:
    __fastcall TGetInstanceInserter(TGetInstanceList &L, const String &Type, TGetInstance F);
  };
};
//---------------------------------------------------------------------------
#endif
