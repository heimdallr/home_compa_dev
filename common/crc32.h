#ifndef Crc32H
#define Crc32H
#include <SysUtils.hpp>
unsigned long crc_mem(unsigned char *p, unsigned long len, unsigned long crc=0xFFFFFFFF);
unsigned long crc_file(char* pszFileName, unsigned long =0xFFFFFFFF);
String GetFileVersion(const String &strFileName, const String &strDataType="FileVersion");
#endif