//---------------------------------------------------------------------------

#pragma hdrstop

#include "reg.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TReg::TReg(HKEY hKey, LPCTSTR lpSubKey, REGSAM samDesired) {
  if(ERROR_SUCCESS-RegOpenKeyEx(hKey, lpSubKey, 0, samDesired, &_key))
    throw 42;
}
//---------------------------------------------------------------------------

char* __fastcall TReg::Get(LPTSTR lpValueName) {
  DWORD lpType, lpcbData=max_len;
  if(ERROR_SUCCESS-RegQueryValueEx(_key, lpValueName, 0, &lpType, _str, &lpcbData))
    throw 42;
  return _str;
}
//---------------------------------------------------------------------------

void __fastcall TReg::Set(LPTSTR lpName, LPTSTR lpValue) {
  if(ERROR_SUCCESS-RegSetValueEx(_key, lpName, 0, REG_SZ, lpValue, strlen(lpValue)+1))
    throw 42;
}
//---------------------------------------------------------------------------
