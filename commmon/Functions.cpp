#include <string.h>
#include <math.h>
#include <windows.h>
#include <memory>
#include <boost/scoped_array.hpp>
#pragma hdrstop
#include "Functions.h"
#include "FilePtr.h"
#include "log.h"
//---------------------------------------------------------------------------

String ReadDataKeyRegedit(HKEY hKey, const String &SubKey, const String &KeyName, bool Required) {
  TRegistryPtr Reg(hKey, SubKey, true);
  String Res=Reg->ReadString(KeyName);
  if(Res.IsEmpty() && Required) {
    Reg->WriteString(KeyName, "");
    throw Exception(String().sprintf("Value of \"%s@%s\" not exists or empty", SubKey, KeyName));
  }
  return Res;
}
//---------------------------------------------------------------------------

void RemoveFiles(String Mask, bool Recursively) {
  TSearchRec F;
  if(!FindFirst(Mask, faAnyFile, F)) {
    String Path = ExtractFilePath(Mask), MaskOnly = ExtractFileName(Mask);
    do {
      if(F.Attr&faDirectory) {
        if(Recursively && F.Name!="." && F.Name!="..") {
          RemoveFiles(Path+F.Name+"\\"+MaskOnly);
          RemoveDir(Path+F.Name);
        }
      }
      else DeleteFile(Path+F.Name);
    } while(!FindNext(F));
    FindClose(F);
  }
}
//---------------------------------------------------------------------------

bool DelDir(const String &dirname) {
  RemoveFiles(dirname+"\\*.*", true);
  if(!DirectoryExists(dirname)) return true;
  return RemoveDir(dirname);
//  return true;
}
//---------------------------------------------------------------------------


String DateToLongString(TDateTime DT){
  char *months[]={
    " января ", " февраля ", " марта ", " апреля ", " мая ", " июня ", " июля ", " августа ", " сентября ", " октября ", " ноября ", " декабря "
  };
  unsigned short year, month, day;
  DT.DecodeDate(&year, &month, &day);
  String Res = IntToStr(day) + months[month-1] + IntToStr(year) + " года";
  return Res;
}
//---------------------------------------------------------------------------

char* MyDateToLongString(TDateTime D){
  char *Months[] = {
    "января", "февраля", "марта", "апреля", "мая", "июня", "июля", "августа", "сентября", "октября", "ноября", "декабря"
  };
  unsigned short Year, Month, Day;
  D.DecodeDate(&Year, &Month, &Day);
  static char Res[50];
  memset(Res, 0, 50);
  sprintf(Res, "\"%02d\" %s %d года", Day, Months[Month-1], Year);
  return Res;
}
//---------------------------------------------------------------------------

String FloatToStrF1(double Value){
  String Res=FloatToStrF(Value, ffFixed, 15, 2);
  const n = 100;
  char buf[n];
  buf[n-1] = 0;
  int j=n-2;
  for(int i=Res.Length(), k=-2; i>0; j--, k++){
    if(k>3 && !(k%4)){
      buf[j] = ' ';
      continue;
    }
    buf[j] = Res[i];
    i--;
  }
  Res = buf+j+1;
  return Res;
}
//---------------------------------------------------------------------------

static double vseg[] = { 1e9, 1e6, 1e3, 1};
static char dsot[][11] = {
    "",          "сто ",       "двести ",   "триста ",     "четыреста ",
    "пятьсот ",  "шестьсот ",  "семьсот ",  "восемьсот ",  "девятьсот "
};
static char ddec[][13] = {
    "",          "десять ",    "двадцать ", "тридцать ",   "сорок ",
    "пятьдесят ","шестьдесят ","семьдесят ","восемьдесят ","девяносто "
};
static char dde [][14] = {
    "одиннадцать ", "двенадцать ",  "тринадцать ",
    "четырнадцать ","пятнадцать ",  "шестнадцать ",
    "семнадцать ",  "восемнадцать ","девятнадцать " };
static char ded [][8] = {
    "",          "один ",      "два ",      "три ",        "четыре ",
    "пять ",     "шесть ",     "семь ",     "восемь ",     "девять "
};
static char dedt[][6]    = {
    "одна ", "две "
};
static char dseg[][9]    = { "миллиард", "миллион", "тысяч", "рубл" };
static char dsem[][3][5] = {{ " ",  "а ", "ов " },  // миллиард
                            { " ",  "а ", "ов " },  // миллион
                            { "а ", "и ", " "   },  // тысяч
                            { "ь ", "я ", "ей " },  // рублей
                            { "йка","йки","ек"  }}; // копеек

static int HowTell (long n){
  n %= 100;
  if (n >= 10  &&  n <= 20) return  3;
  n %= 10;
  return  n == 1? 1: n <= 4  &&  n > 0? 2: 3;
}

static double Round (double op){
  return  floor(op + 0.5);
}

static double Round (double op,double pow){
  if (pow <= 0.)  return  op;
  if (op>0. && op<pow || op<0. && op>pow) return 0.;
  op = floor(op/pow + 0.5) * pow;
  return  op>0. && op<pow || op<0. && op>pow? 0.: op;
}

char* WriteSum (double v, char *buf, bool kop, bool up, bool need_rub){
  buf[0] = 0;
  if (v >= 1e12  ||  v <= 0.009) return buf;
  v = Round(v,0.01);
  for (int seg=0; seg<4; seg++) {
    int vt = int(v / vseg[seg]);
    v -= vseg[seg] * vt;
    if (vt  ||  seg == 3) {
      int how = HowTell(vt);
           // 1 - миллиард   миллион   тысяча рубль  копейка
           // 2 - миллиарда  миллиона  тысячи рубля  копейки
           // 3 - миллиардов миллионов тысяч  рублей копеек
      if (vt) {
        strcat(buf,dsot[vt/100]);  vt %= 100;
        if (vt >= 20  ||  vt <= 10) {
          strcat(buf,ddec[vt/10]);  vt %= 10;
          if (seg == 2  &&  (vt == 1  ||  vt == 2))
            strcat(buf,dedt[vt-1]);
          else  strcat(buf,ded[vt]);
        }
        else  strcat(buf,dde[vt-11]);
      }
      else if (buf[0] == 0)  strcat(buf,"ноль ");
      if(need_rub || seg<3){
        strcat(buf,dseg[seg]);
        strcat(buf,dsem[seg][how-1]);
      }
    }
  }
  if (kop)
      sprintf(buf+strlen(buf),"%02.0lf копе%s",
                              v*100,
                              dsem[4][HowTell((long)Round(v*100))-1]);
    if (up) CharUpper(buf);
  else    CharUpperBuff(buf,1);
  return  buf;
}
//---------------------------------------------------------------------------

void __fastcall Split(const String &Src, char Delimiter, TStrings *Dst){
  if(!Dst || Src.IsEmpty()) return;
  Dst->Clear();
  TCharPtr str(Src.c_str());
  char *p=str;
  while(p){
    char *q=p;
    if((bool)(p=strchr(q, Delimiter))) *p++=0;
    Dst->Add(q);
  }
}
//---------------------------------------------------------------------------

TStrings* __fastcall Split(const String &Src, char Delimiter) {
  TStringList *Res = new TStringList();
  Split(Src, Delimiter, Res);
  return Res;
}
//---------------------------------------------------------------------------

// Тянем имя компонента до его самого старшего владельца
String __fastcall GetFullComponentName(const TComponent *Component){
  if(!Component) return String();
  String Res = Component->Name;
  for(TComponent *p=Component->Owner; p; p=p->Owner)
    if(!p->Name.IsEmpty())
      Res = p->Name + "\\" + Res;
  return Res;
}
//---------------------------------------------------------------------------

void __fastcall SplitComponentName(const String &FullName, String &Parent, String &Component) {
  int n = FullName.LastDelimiter("\\");
  Component = FullName.SubString(n+1, FullName.Length()-n);
  Parent = n ? FullName.SubString(1, n-1) : String("");
}
//---------------------------------------------------------------------------

// Отрезаем справа слеши с цифрами
bool __fastcall Leave(char *p) {
  for(;*p;++p) if(*p<',' || *p>'9') return true;
  return false;
}
char* __fastcall TrimRightSlashes(char *src) {
  while(1) {
    if(char *p=strrchr(src, '/')) {
      if(*(p+1) && Leave(p+1)) return src;
      *p=0;
    }
    else return src;
  }
}
//---------------------------------------------------------------------------
// Ошибка WinAPI
String __fastcall GetStrLastError()
{
  LPVOID lpMsgBuf;
  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
  String res = (char*)lpMsgBuf;
  LocalFree(lpMsgBuf);
  return res;
}
//---------------------------------------------------------------------------
// Копировшик файлов
TCopyFileExResult __fastcall CopyFileEx(String MaskSrc, String DirDst, const TCopyFileExOptions& opts)
{
  TCopyFileExResult result;
  TSearchRec F;

  if (FindFirst(MaskSrc, faAnyFile, F)) return result;
  if (DirDst[DirDst.Length()] != '\\') DirDst += '\\';

  String Path = ExtractFilePath(MaskSrc), MaskOnly = ExtractFileName(MaskSrc);
  do {
    String SrcName = Path+F.Name;
    String DstName = DirDst+F.Name;

    if (F.Attr & faDirectory) {
      if (opts.Contains(cfoRecursively) && F.Name!="." && F.Name!="..") {
        bool is_ok = CreateDir(DstName);
        if (!is_ok) throw Exception("Невозможно создать папку:\n"+DstName+"\nПричина: "+GetStrLastError());
        TCopyFileExResult files = CopyFileEx(SrcName+"\\"+MaskOnly, DstName, opts);
        for (TCopyFileExResultIt it = files.begin(); it != files.end(); ++it)
          result.push_back(*it);
      }
    }
    else {
      bool is_ok = CopyFile(SrcName.c_str(), DstName.c_str(), !opts.Contains(cfoOverWrite));
      if (!is_ok) throw Exception("Невозможно скопировать файл:\n"+SrcName+" в папку "+DirDst+"\nПричина: "+GetStrLastError());
      result.push_back(DstName);
      if (opts.Contains(cfoReplace))
        DeleteFile(SrcName);
    }
  } while(!FindNext(F));
  FindClose(F);
  return result;
}
//---------------------------------------------------------------------------
// Запуск процесса
int __fastcall ExecProcess(const String& cmd_line, String work_dir, bool f_wait, unsigned short ShowWindow) {
  STARTUPINFO SI;
  ZeroMemory(&SI, sizeof(SI));
  SI.cb = sizeof(SI);
  SI.dwFlags |= STARTF_USESHOWWINDOW;
  SI.wShowWindow = ShowWindow;
  PROCESS_INFORMATION PI = {0,0,0,0};
  DWORD dwExitCode(0);
  if (work_dir == "") {
    work_dir = cmd_line.Pos(":") ? ExtractFileDir(cmd_line) : GetCurrentDir();
  } else if (work_dir == "system") {
    char buf[255];
    GetSystemDirectory(buf, 255);
    work_dir = buf;
  }
/*  TLoggerPtr Log(TLogger::GetInstance(TLoggerWinInit()));
  Log->Info(cmd_line);*/
  if (CreateProcess(0, cmd_line.c_str(), 0, 0, 0, NORMAL_PRIORITY_CLASS, 0, work_dir.c_str(), &SI, &PI)) {
    if(f_wait) {
      WaitForSingleObject(PI.hProcess, INFINITE);
      if (!GetExitCodeProcess(PI.hProcess, &dwExitCode))
        throw Exception(GetStrLastError());
    }
  }
  else throw Exception("Невозможно выполнить программу:\n"+cmd_line+"\nПричина:\n"+GetStrLastError());
  return dwExitCode;
}
//---------------------------------------------------------------------------

// Генерим GUID
String __fastcall GetGUID() {
  GUID gGUID;
  CreateGUID(gGUID);
  String asGUID=Sysutils::GUIDToString(gGUID);
  return asGUID.SubString(2, asGUID.Length()-2);
}
//---------------------------------------------------------------------------

String __fastcall GetDayOfWeek(TDateTime dsDate) {
  char *str[] = {"Воскресенье", "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота"};
  return str[DayOfWeek(dsDate)-1];
}
//---------------------------------------------------------------------------

String __fastcall GetDayOfWeekShort(TDateTime dsDate) {
  char *str[] = {"ВС", "ПН", "ВТ", "СР", "ЧТ", "ПТ", "СБ"};
  return str[DayOfWeek(dsDate)-1];
}
//---------------------------------------------------------------------------

String& __fastcall AddFilter(String &strFilter, const String &strNew) {
  if(strFilter.IsEmpty()) strFilter=strNew;
  else strFilter = String().sprintf("(%s) and %s", strFilter, strNew);
  return strFilter;
}
//---------------------------------------------------------------------------

char* IPConvert(char *str){
  static char IP[20];
  strset(IP, 0);
  itoa((unsigned char)str[0], IP, 10);
  strcat(IP, ".");
  itoa((unsigned char)str[1], IP+strlen(IP), 10);
  strcat(IP, ".");
  itoa((unsigned char)str[2], IP+strlen(IP), 10);
  strcat(IP, ".");
  itoa((unsigned char)str[3], IP+strlen(IP), 10);
  return IP;
}
//---------------------------------------------------------------------------

// Вытаскиваем параметры запустившего программу
void __fastcall GetUserParam(String &ComputerName, String &IP, String &UserName) {
  char HostName[1024];
  WORD wVersionRequested;
  WSADATA wsaData;
  wVersionRequested = MAKEWORD(1, 0);
  int err = WSAStartup(wVersionRequested, &wsaData);
  if(!err && gethostname(HostName, 1024)) err = 1;
  if(err) strcpy(HostName, "unknown");
  ComputerName = HostName;
  hostent *HostEnt = gethostbyname(HostName);
  IP = IPConvert(HostEnt->h_addr_list[0]);
  for(int i=1; HostEnt->h_addr_list[i]; ++i)
    IP += String().sprintf(";%s", IPConvert(HostEnt->h_addr_list[i]));
  unsigned long t=1024;
  GetUserName(HostName, &t);
  UserName = HostName;
}
//---------------------------------------------------------------------------
String GetModuleFileName(HANDLE hmodule)
{
  char str[256];
  if (!GetModuleFileName(hmodule, str, 256))
    throw Exception(GetStrLastError());
  return String(str);
}
//---------------------------------------------------------------------------

const String& __fastcall MakeDir(const String &strDirName) {
  if(DirectoryExists(strDirName)) return strDirName;
  if(!CreateDirectory(strDirName.c_str(), 0))
    throw Exception(String().sprintf("Не удалось создать папку \"%s\":\n%s", strDirName, GetStrLastError()));
  return strDirName;
}
//---------------------------------------------------------------------------

void __fastcall Copy(const String &strSrc, const String &strDst) {
  if(!CopyFile(strSrc.c_str(), strDst.c_str(), false))
    throw Exception(String().sprintf("Не удалось скопировать \"%s\" в \"%s\":\n%s", strSrc, strDst, GetStrLastError()));
}
//---------------------------------------------------------------------------

using namespace ns_Functions;

int __fastcall ns_Functions::GetFileList(TFileList &FileList, const String &Mask, bool Recursive, int Size) {
  String PathMask=ExtractFilePath(Mask), FileMask=ExtractFileName(Mask);
  TSearchRec F;
  if(!FindFirst(Mask, faAnyFile&~faDirectory, F)) {
    do {
      FileList.push_back((PathMask+F.Name).LowerCase());
      Size += F.Size;
    }
    while(!FindNext(F));
    FindClose(F);
  }
  if(!Recursive) return Size;
  if(!FindFirst(PathMask+"*", faAnyFile, F)) {
    do
      if(F.Attr&faDirectory && F.Name!="." && F.Name!="..")
        Size += GetFileList(FileList, PathMask+F.Name+"\\"+FileMask, Recursive, Size);
    while(!FindNext(F));
    FindClose(F);
  }
  return Size;
}
//---------------------------------------------------------------------------

int __fastcall ns_Functions::GetFileList(TFileDescList &FileList, const String &Mask, bool Recursive, int Size) {
  String PathMask=ExtractFilePath(Mask), FileMask=ExtractFileName(Mask);
  TSearchRec F;
  if(!FindFirst(Mask, faAnyFile&~faDirectory, F)) {
    do {
      FileList.push_back(TFileDesc((PathMask+F.Name).LowerCase(), F.Size, F.Attr, FileDateToDateTime(F.Time)));
      Size += F.Size;
    }
    while(!FindNext(F));
    FindClose(F);
  }
  if(!Recursive) return Size;
  if(!FindFirst(PathMask+"*", faAnyFile, F)) {
    do
      if(F.Attr&faDirectory && F.Name!="." && F.Name!="..")
        Size += GetFileList(FileList, PathMask+F.Name+"\\"+FileMask, Recursive, Size);
    while(!FindNext(F));
    FindClose(F);
  }
  return Size;
}
//---------------------------------------------------------------------------

int __fastcall ns_Functions::GetDirList(TFileList &FileList, const String &Mask, bool Recursive, int Size) {
  String PathMask=ExtractFilePath(Mask), FileMask=ExtractFileName(Mask);
  TSearchRec F;
  if(!FindFirst(Mask, faAnyFile, F)) {
    do {
      if(F.Attr&faDirectory && F.Name!="." && F.Name!="..") {
        FileList.push_back((PathMask+F.Name+"\\").LowerCase());
        Size += F.Size;
      }
    }
    while(!FindNext(F));
    FindClose(F);
  }
  if(!Recursive) return Size;
  if(!FindFirst(PathMask+"*", faAnyFile, F)) {
    do
      if(F.Attr&faDirectory && F.Name!="." && F.Name!="..")
        Size += GetFileList(FileList, PathMask+F.Name+"\\"+FileMask, Recursive, Size);
    while(!FindNext(F));
    FindClose(F);
  }
  return Size;
}
//---------------------------------------------------------------------------

int __fastcall ns_Functions::GetDirList(TFileDescList &FileList, const String &Mask, bool Recursive, int Size) {
  String PathMask=ExtractFilePath(Mask), FileMask=ExtractFileName(Mask);
  TSearchRec F;
  if(!FindFirst(Mask, faAnyFile, F)) {
    do {
      if(F.Attr&faDirectory && F.Name!="." && F.Name!="..") {
        FileList.push_back(TFileDesc((PathMask+F.Name+"\\").LowerCase(), F.Size, F.Attr, FileDateToDateTime(F.Time)));
        Size += F.Size;
      }
    }
    while(!FindNext(F));
    FindClose(F);
  }
  if(!Recursive) return Size;
  if(!FindFirst(PathMask+"*", faAnyFile, F)) {
    do
      if(F.Attr&faDirectory && F.Name!="." && F.Name!="..")
        Size += GetFileList(FileList, PathMask+F.Name+"\\"+FileMask, Recursive, Size);
    while(!FindNext(F));
    FindClose(F);
  }
  return Size;
}
//---------------------------------------------------------------------------

HANDLE    __fastcall  ns_Functions::GetMetaDataDllHandle() {
  static HANDLE dll=0;
  if(dll) return dll;

  String DllPath=ExtractFilePath(GetModuleName(0))+"ARMMAGMetaData.dll";
  if(!(bool)(dll = LoadLibrary(DllPath.c_str())))
    throw Exception(String().sprintf("Cannot load %s", DllPath));
  return dll;
}
//---------------------------------------------------------------------------

// Создаем подпапки
const String& __fastcall ns_Functions::CreateSubDirs(const String &Path) throw(Exception) {
  std::auto_ptr<TStringList> pList(new TStringList);
  pList->Delimiter = '\\';
  pList->DelimitedText = Path;
  String subPath = "";
  for(int i=0; i<pList->Count; ++i) {
    subPath += pList->Strings[i] + "\\";
    if(!DirectoryExists(subPath) && !CreateDir(subPath))
      throw(Exception(String().sprintf("Не удалось создать каталог \"%s\"", subPath)));
  }
  return Path;
}
//---------------------------------------------------------------------------

// Тянем информацию о файле
String __fastcall ns_Functions::GetFileVersion(const String &strFileName, const String &strDataType) {
  char pszVerBuf[1024], pszLangBuf[1024];
  unsigned long ul, info_size = GetFileVersionInfoSize(strFileName.c_str(), &ul);
  if(!info_size) return "";
  boost::scoped_array<unsigned char> info(new unsigned char[info_size]);
  memset(info.get(), 0, info_size);
  if(!GetFileVersionInfo (strFileName.c_str(), 0, info_size, info.get())) return "";
  char *pszVersion(0);
  if(!VerQueryValue(info.get(), String().sprintf("\\StringFileInfo\\041904E3\\%s", strDataType).c_str(), (void**)(&pszVersion), (unsigned*)&ul)) return "";
//  String Res(pszVersion);
  return pszVersion;
}
//---------------------------------------------------------------------------

