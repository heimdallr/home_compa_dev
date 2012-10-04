#ifndef CmdLineImplH
#define CmdLineImplH
#include <Classes.hpp>
#include <vector>
#include <map>
#include <memory>
#include "CmdLine.h"
//---------------------------------------------------------------------------


// Базовый класс для работы с командной строкой
class TCmdLineImpl : TCmdLine {

  typedef std::vector<String> TParamList;
  typedef std::map<String, String> TKeyList;
  typedef TParamList::const_iterator TParamIt;
  typedef TKeyList::const_iterator TKeyIt;
  typedef std::auto_ptr<TStringList> TStrListPtr;

  TParamList _param;
  TKeyList _key;
  static String Empty;
protected:
  __fastcall TCmdLineImpl() {}
  virtual __fastcall ~TCmdLineImpl() {}
  void __fastcall Initialize(TStrListPtr);
public:
  unsigned int  __fastcall GetParamCount()              const {return _param.size();}
  const String& __fastcall GetParam(unsigned int n)     const {return n<_param.size() ? _param[n] : Empty;}
  unsigned int  __fastcall GetKeyCount()                const {return _key.size();}
  bool          __fastcall KeyExists(const String &key) const {return _key.find(key)!=_key.end();}
  const String& __fastcall GetKey(const String &key)    const {TKeyIt I=_key.find(key); return I!=_key.end() ? I->second : Empty;}
};
//---------------------------------------------------------------------------

// Командная строка виндовых программ в стиле WinMain
class TCmdLineWin : public TCmdLineImpl {
public:
  __fastcall TCmdLineWin(const TCmdLineWinInit&);
};
//---------------------------------------------------------------------------

// Командная строка консольных программ
class TCmdLineConsole : public TCmdLineImpl {
public:
  __fastcall TCmdLineConsole(const TCmdLineConsoleInit&);
};
//---------------------------------------------------------------------------

// Командная строка в vcl
class TCmdLineVcl : public TCmdLineImpl {
public:
  __fastcall TCmdLineVcl(const TCmdLineVclInit&);
};
//---------------------------------------------------------------------------


#endif
