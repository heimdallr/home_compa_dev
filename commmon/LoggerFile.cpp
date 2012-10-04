#include <Dialogs.hpp>
#pragma hdrstop
#include "LoggerFile.h"
#include "Functions.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

TLoggerImpl::TGetInstanceInserter TLoggerFile::_inserter(TLoggerImpl::_get_instance_list, String("File"), &TLoggerFile::GetInstance);
__fastcall TLoggerFile::TLoggerFile(const TPropertyMap &Init) : _outp(0), _max_file_count(Init["MaxFileCount"].ToInt()), _file_name(Init["Name"]) {
  if(_file_name.IsEmpty())
    _file_name = ExtractFilePath(GetModuleName(0))+"log\\"+Now().FormatString("yyyymmdd")+".log";
  _path = ExtractFilePath(_file_name);
  if(!DirectoryExists(_path)) CreateDirectory(_path.c_str(), 0);
  Reset();
  Info(String().sprintf("%s запуск", GetModuleName(0)));
}
//---------------------------------------------------------------------------

void __fastcall TLoggerFile::Reset() {
  if(_outp) {
    Info("--------------------------------------------------------------------------------\nДо встречи в следующем файле!");
    fclose(_outp);
    _file_name = _path+Now().FormatString("yyyymmdd")+".log";
  }
  if(!bool(_outp = fopen(_file_name.c_str(), "at"))) throw Exception("");
  if(_max_file_count) {
    String Mask = ExtractFilePath(_file_name)+"*"+ExtractFileExt(_file_name);
    ns_Functions::TFileList FileList;
    ns_Functions::GetFileList(FileList, Mask);
    FileList.sort();
    while(FileList.size()>_max_file_count) {
      DeleteFile(FileList.front());
      FileList.pop_front();
    }
  }
}
//---------------------------------------------------------------------------


__fastcall TLoggerFile::~TLoggerFile() {
  Info("--------------------------------------------------------------------------------\n");
  fclose(_outp);
}
//---------------------------------------------------------------------------


const TLogger* __fastcall TLoggerFile::Info(const String &Mes) const {
  fprintf(_outp, "%lu. %s  %s\n", GetCurrentThreadId(), Now().FormatString("hh:nn:ss"), Mes);
  fflush(_outp);
  return this;
}
//---------------------------------------------------------------------------

