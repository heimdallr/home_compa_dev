//---------------------------------------------------------------------------
#pragma hdrstop
#include "CmdLineImpl.h"
#include "typeinfo.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TCmdLine* __fastcall TCmdLine::GetInstance(const TCmdLineInit &Init) {
  if(const TCmdLineWinInit *pInit=dynamic_cast<const TCmdLineWinInit*>(&Init))
    return new TCmdLineWin(*pInit);
  if(const TCmdLineConsoleInit *pInit=dynamic_cast<const TCmdLineConsoleInit*>(&Init))
    return new TCmdLineConsole(*pInit);
  if(const TCmdLineVclInit *pInit=dynamic_cast<const TCmdLineVclInit*>(&Init))
    return new TCmdLineVcl(*pInit);
  throw Exception(String().sprintf("Unknown initialiser type: ", typeid(Init).name()));
}
//---------------------------------------------------------------------------

// Конструктор
String TCmdLineImpl::Empty="";
void __fastcall TCmdLineImpl::Initialize(TStrListPtr lStr) {
  for(int i=0; i<lStr->Count; ++i) {
    String strParam = lStr->Strings[i], strValue;
    if(strParam[1]!='-')
      _param.push_back(strParam);
    else {
      strParam = strParam.SubString(2, strParam.Length()-1);
      strValue = i<lStr->Count-1 ? lStr->Strings[i+1] : String();
      if(strValue.IsEmpty() || strValue[1]=='-')
        _key[strParam] = String();
      else {
        _key[strParam] = strValue;
        ++i;
      }
    }
  }
}
//---------------------------------------------------------------------------

// Командная строка в стиле WinMain
__fastcall TCmdLineWin::TCmdLineWin(const TCmdLineWinInit &Init) {
  TStrListPtr lStr(new TStringList);
  lStr->DelimitedText = Init.GetCmdLine();
  Initialize(lStr);
}
//---------------------------------------------------------------------------

// Консольная командная строка
__fastcall TCmdLineConsole::TCmdLineConsole(const TCmdLineConsoleInit &Init) {
  TStrListPtr lStr(new TStringList);
  for(int i=1; i<Init.GetParamCount(); ++i) lStr->Add(Init.GetParam(i));
  Initialize(lStr);
}
//---------------------------------------------------------------------------

// Командная строка VCL
__fastcall TCmdLineVcl::TCmdLineVcl(const TCmdLineVclInit &Init) {
  TStrListPtr lStr(new TStringList);
  int n=ParamCount()+1;
  for(int i=1; i<n; ++i) lStr->Add(ParamStr(i));
  Initialize(lStr);
}
//---------------------------------------------------------------------------

