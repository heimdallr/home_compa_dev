//---------------------------------------------------------------------------

#ifndef regH
#define regH
#include "windows.h"
//---------------------------------------------------------------------------
const int max_len=1024;
class TReg {
  HKEY _key;
  char _str[max_len];
public:
  __fastcall TReg(
    HKEY hKey,	      // ������ ������� {HKEY_CLASSES_ROOT | HKEY_CURRENT_USER | HKEY_LOCAL_MACHINE | HKEY_USERS}
    LPCTSTR lpSubKey,	// ����
    REGSAM samDesired	// ����� �������, �� Help � RegOpenKeyEx
  );
  __fastcall ~TReg() {RegCloseKey(_key);}
  char* __fastcall Get(LPTSTR lpValueName);
  void __fastcall Set(LPTSTR lpName, LPTSTR lpValue);
};
//---------------------------------------------------------------------------
#endif
