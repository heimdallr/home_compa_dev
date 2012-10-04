#ifndef FilePtrH
#define FilePtrH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <stdio>
#pragma hdrstop
//---------------------------------------------------------------------------
class TFilePtr {
  FILE *_f;
public:
  __fastcall ~TFilePtr() {fclose(_f);}
  __fastcall TFilePtr(const String &strName, const String &strMode) : _f(fopen(strName.c_str(), strMode.c_str())) {if(!_f) throw Exception(String().sprintf("Cannot open \"%s\" for \"%s\"", strName, strMode));}
  __fastcall operator FILE*() {return _f;}
  FILE* __fastcall operator->() {return _f;}
  FILE* __fastcall get() {return _f;}
};
//---------------------------------------------------------------------------
#endif
