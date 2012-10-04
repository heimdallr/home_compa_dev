//---------------------------------------------------------------------------

#ifndef logH
#define logH
#include <list>
#include <stdio>
#include <SysUtils.hpp>
//---------------------------------------------------------------------------
String __fastcall IntervalToString(TDateTime);
//---------------------------------------------------------------------------
// Логгер
class TLogEvent;
class TLogger {
friend class TLog;
typedef std::list<String> TStrList;
typedef TStrList::const_iterator TStrIt;
  FILE *_outp;
  TStrList _event;
  mutable int _warn, _error;
public:
  __fastcall TLogger(String strFileName="", bool fOverride=false);
  __fastcall ~TLogger() {if(_outp) {fprintf(_outp, "--------------------------------------------------------------------------------\n\n"); fclose(_outp);}}
  TDateTime __fastcall Write(const String &strMessage="")   const;
  TDateTime __fastcall Warning(const String &strMessage="") const {++_warn;   return Write(String().sprintf("ВНИМАНИЕ: %s", strMessage));}
  TDateTime __fastcall Error(const String &strMessage="")   const {++_error;  return Write(String().sprintf("ОШИБКА: %s", strMessage));}
  int __fastcall GetWarningCount() const {return _warn;}
  int __fastcall GetErrorCount() const {return _error;}
};
extern TLogger *Log;
//---------------------------------------------------------------------------

// Работаем с логгером через это, ибо удобно
class TLog {
  TDateTime _beg;
public:
  __fastcall TLog(const String &strEvent) {Log->_event.push_back(strEvent); _beg=Log->Write();}
  __fastcall ~TLog() {Log->Write(String().sprintf("Завершено за %s", IntervalToString(Now()-_beg))); Log->_event.pop_back();}
  TDateTime __fastcall Write(const String &strMessage="")   const {return Log->Write(strMessage);}
  TDateTime __fastcall Warning(const String &strMessage="") const {return Log->Warning(strMessage);}
  TDateTime __fastcall Error(const String &strMessage="")   const {return Log->Error(strMessage);}
};
//---------------------------------------------------------------------------

#endif
