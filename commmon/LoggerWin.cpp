#pragma hdrstop
#include "LoggerWin.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

TLoggerImpl::TGetInstanceInserter TLoggerWin::_inserter(TLoggerImpl::_get_instance_list, String("Win"), &TLoggerWin::GetInstance);
__fastcall TLoggerWin::TLoggerWin(const TPropertyMap &Init) {
  if(!reinterpret_cast<int>(_hndl = RegisterEventSource(NULL, TEXT(ChangeFileExt(ExtractFileName(GetModuleName(0)), "").c_str()))))
    throw Exception("Не удалось создать журнал в Windows Event");
}
//---------------------------------------------------------------------------

const TLogger* __fastcall TLoggerWin::Write(const String &Message, WORD wType) const{
  LPCTSTR msg = Message.c_str();
  if(!ReportEvent(
        _hndl,                    // event log handle
        wType,                    // event type
        0,                        // category zero
        0,                        // event identifier
        NULL,                     // no user security identifier
        1,                        // one substitution string
        0,                        // no data
        &msg,                     // pointer to string array
        NULL                      // pointer to data
      )
  )
  throw Exception("Ошибка записи в Windows Event");
  return this;
}
//---------------------------------------------------------------------------

__fastcall TLoggerWin::~TLoggerWin() {
  try { DeregisterEventSource(_hndl);}
  catch(...) {}
}
//---------------------------------------------------------------------------

