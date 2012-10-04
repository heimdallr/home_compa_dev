#ifndef LoggerFileH
#define LoggerFileH
#include "LoggerImpl.h"
#include <stdio>
//---------------------------------------------------------------------------

class TLoggerFile : public TLoggerImpl {
static TLoggerImpl::TGetInstanceInserter _inserter;
static TLogger* __fastcall GetInstance(const TPropertyMap &I) {return new TLoggerFile(I);}
  FILE *_outp;
  String _path, _file_name;
  unsigned int _max_file_count;
  __fastcall TLoggerFile(const TPropertyMap&);
  const TLogger* __fastcall Info(const String &) const;
  void __fastcall Reset();
  __fastcall ~TLoggerFile();
};
//---------------------------------------------------------------------------
#endif
