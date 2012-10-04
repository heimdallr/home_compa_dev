#ifndef FunctionsH
#define FunctionsH
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <list>
#include <memory>
#include <Registry.hpp>

enum e_CopyFileExOption { cfoOverWrite, cfoRecursively, cfoReplace };
typedef Set<e_CopyFileExOption, cfoOverWrite, cfoReplace>  TCopyFileExOptions;
typedef std::list<String> TCopyFileExResult;
typedef TCopyFileExResult::iterator TCopyFileExResultIt;

TCopyFileExResult __fastcall CopyFileEx(String MaskSrc, String DirDst, const TCopyFileExOptions& opts);

//функция для чтения ключа рееестра
String ReadDataKeyRegedit( HKEY hKey,             //указатель на ветку, например HKEY_LOCAL_MACHINE
                           const String &SubKey,  //путь к подключу, например Software\\SendToOffice\\
                           const String &KeyName, //Наименование ключа, например Patch
                           bool Required=true
                           );
//---------------------------------------------------------------------------

class TRegistryPtr {
  TRegistry *_reg;
public:
  __fastcall TRegistryPtr(HKEY Root, const String& Key, bool CanCreate) : _reg(new TRegistry(KEY_ALL_ACCESS)) {
    _reg->RootKey=Root;
    if(!_reg->OpenKey(Key, CanCreate))
      throw Exception(String().sprintf("Cannot open \"%s\"", Key));}
  __fastcall ~TRegistryPtr() {try{_reg->CloseKey(); delete _reg;}catch(...){}}
  TRegistry* __fastcall operator->() {return _reg;}
};
//---------------------------------------------------------------------------

class TCharPtr {
  char *ptr;
  void __fastcall alloc(char *src) {if(ptr) free(ptr); ptr=strdup(src); if(!ptr) throw("Не удалось выделить память");}
public:
  __fastcall TCharPtr(char *src) : ptr(0) {alloc(src);}
  __fastcall TCharPtr(TCharPtr& src) : ptr(0) {alloc(src);}
  __fastcall ~TCharPtr() {if(ptr) free(ptr);}
  __fastcall operator char*() {return ptr;}
  char* __fastcall get() {return ptr;}
  TCharPtr& __fastcall operator=(char *src) {alloc(src); return *this;}
  TCharPtr& __fastcall operator=(TCharPtr &src) {alloc(src); return *this;}
};
//---------------------------------------------------------------------------



void      __fastcall  RemoveTempFiles(const String &Mask="*", bool Recursively=false);
void                  RemoveFiles(String Mask="*", bool Recursively=false);
bool                  DelDir(const String &dirname);
String                DateToLongString(TDateTime DT);
String                FloatToStrF1(double Value);
char*                 WriteSum (double v, char *buf, bool kop, bool up, bool need_rub=true);
char*                 MyDateToLongString(TDateTime D);
void      __fastcall  Split(const String &Src, char Delimiter, TStrings *Dst);
TStrings* __fastcall  Split(const String &Src, char Delimiter);
String    __fastcall  GetFullComponentName(const TComponent *Component);
void      __fastcall  SplitComponentName(const String &FullName, String &Parent, String &Component);
char*     __fastcall  TrimRightSlashes(char*);
String    __fastcall  GetStrLastError();
int       __fastcall  ExecProcess(const String &cmd_line, String work_dir = "system", bool f_wait=true, unsigned short ShowWindow=SW_HIDE);
String    __fastcall  GetGUID();
String    __fastcall  GetDayOfWeek(TDateTime);
String    __fastcall  GetDayOfWeekShort(TDateTime);
String&   __fastcall  AddFilter(String&, const String&);
void      __fastcall  GetUserParam(String &ComputerName, String &IP, String &UserName);
String                GetModuleFileName(HANDLE hmodule = 0);
String&   __fastcall  AddSlash(String &s) {if(!s.IsEmpty() && '\\'-s[s.Length()])s+="\\"; return s;}
void      __fastcall  Copy(const String &strSrc, const String &strDst);
const String&  __fastcall  MakeDir(const String&);

namespace ns_Functions {
class TFileDesc {
  const String _name;
  const int _size, _attr;
  const TDateTime _time;
public:
  __fastcall TFileDesc(const String &N, int S, int A, TDateTime T) : _name(N), _size(S), _attr(A), _time(T) {}
  String        __fastcall GetInfo() const {return String().sprintf("%s\t%s\t%d\t%d", _name, _time.FormatString("yyyy.mm.dd hh:nn:ss"), _size, _attr);}
  const String& __fastcall GetName() const {return _name;}
  int           __fastcall GetSize() const {return _size;}
  int           __fastcall GetAttr() const {return _attr;}
  TDateTime     __fastcall GetTime() const {return _time;}
};
typedef std::list<TFileDesc> TFileDescList;
typedef TFileDescList::const_iterator TFileDescIt;

typedef std::list<String> TFileList;
typedef TFileList::const_iterator TFileIt;
typedef std::auto_ptr<TStrings> TStrListPtr;
int         __fastcall  GetFileList(TFileList&, const String &Mask, bool Recursive=false, int Size=0);
int         __fastcall  GetFileList(TFileDescList&, const String &Mask, bool Recursive=false, int Size=0);
int         __fastcall  GetDirList(TFileList&, const String &Mask, bool Recursive=false, int Size=0);
int         __fastcall  GetDirList(TFileDescList&, const String &Mask, bool Recursive=false, int Size=0);
HANDLE      __fastcall  GetMetaDataDllHandle();
const String&  __fastcall  CreateSubDirs(const String &Path) throw(Exception);
String __fastcall GetFileVersion(const String &strFileName, const String &strDataType="FileVersion");
} // namespace ns_Functions


#endif
