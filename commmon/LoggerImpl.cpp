#pragma hdrstop
#include "LoggerImpl.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)

TLoggerImpl::TGetInstanceList TLoggerImpl::_get_instance_list;

__fastcall TLoggerImpl::TGetInstanceInserter::TGetInstanceInserter(TLoggerImpl::TGetInstanceList &L, const String &Type, TGetInstance F) {
  L.insert(std::make_pair(Type, F));
}
//---------------------------------------------------------------------------


TLogger::Ptr __fastcall TLogger::GetInstance(const TPropertyMap &Init) {
  TLoggerImpl::TGetInstanceList::const_iterator It=TLoggerImpl::_get_instance_list.find(Init["Type"]);
  if(TLoggerImpl::_get_instance_list.end()==It) throw Exception(String().sprintf("Неизвестный тип логгера: \"%s\"", Init["Type"]));
  return TLogger::Ptr(It->second(Init));
}
//---------------------------------------------------------------------------

