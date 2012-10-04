#ifndef LoggerWinH
#define LoggerWinH
#include "LoggerImpl.h"
//---------------------------------------------------------------------------

class TLoggerWin : public TLoggerImpl {
static TLoggerImpl::TGetInstanceInserter _inserter;
static TLogger* __fastcall GetInstance(const TPropertyMap &I) {return new TLoggerWin(I);}
enum LogType {
  l_info=0,
  l_warning,
  l_error
};
  HANDLE _hndl;
  const TLogger* __fastcall Write(const String &, WORD =EVENTLOG_INFORMATION_TYPE) const;
  __fastcall TLoggerWin(const TPropertyMap&);
  __fastcall ~TLoggerWin();
  const TLogger* __fastcall Info(const String &Mes) const {return Write(Mes);}
  const TLogger* __fastcall Warn(const String &Mes) const {return Write(Mes, EVENTLOG_WARNING_TYPE);}
  const TLogger* __fastcall Err(const String &Mes) const {return Write(Mes, EVENTLOG_ERROR_TYPE);}
};
//---------------------------------------------------------------------------
#endif
