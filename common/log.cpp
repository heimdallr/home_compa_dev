//---------------------------------------------------------------------------


#pragma hdrstop

#include "log.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TLogger *Log=0;

// Открываем лог-файл, пишем первую запись
__fastcall TLogger::TLogger(String strFileName, bool fOverride) : _outp(0), _warn(0), _error(0) {
  TDateTime dtNow = Now();
  if(strFileName.IsEmpty()) strFileName = String().sprintf("%s-%s.log", ChangeFileExt(GetModuleName(0), ""), dtNow.FormatString("yyyymmdd"));
  else if(ExtractFilePath(strFileName).IsEmpty()) strFileName = ExtractFilePath(GetModuleName(0))+strFileName; 
  if(!strFileName.Pos(":"))
    strFileName = ExtractFilePath(GetModuleName(0)) + strFileName;
  _outp = fopen(strFileName.c_str(), fOverride?"wt":"at");
  if(_outp) fprintf(_outp, "%s\n", dtNow.FormatString("yyyy.mm.dd hh:nn"));
  fflush(_outp);
}
//---------------------------------------------------------------------------

// Пишем сообщение
TDateTime __fastcall TLogger::Write(const String &strMessage) const {
 TDateTime dtRes = Now();
 if(!_outp) return dtRes;
 fprintf(_outp, "%lu. %s  ", GetCurrentThreadId(), dtRes.FormatString("hh:nn:ss"));
 for(TStrIt i=_event.begin(); i!=_event.end(); ++i)
   fprintf(_outp, "%s. ", *i);
 fprintf(_outp, "%s\n", strMessage.c_str());
 fflush(_outp);
 return dtRes;
}
//---------------------------------------------------------------------------

// Конвертим интервал в понятную людям строку
String __fastcall IntervalToString(TDateTime dtInterval) {
  String res;
  double d=dtInterval;
  if(d>1.0) {
    res += String().sprintf("%d дн. ", int(d));
    d -= int(d);
  }
  if(d>1.0/24.0) {
    int t = 24.0*d;
    res += String().sprintf("%d ч. ", t);
    d -= double(t)/24.0;
  }
  if(d>1.0/24.0/60.0) {
    int t = 24.0*60.0*d;
    res += String().sprintf("%d м. ", t);
    d -= double(t)/24.0/60.0;
  }
  res += String().sprintf("%.3f с. ", 24.0*60.0*60.0*d);
  return res;
}
//---------------------------------------------------------------------------

