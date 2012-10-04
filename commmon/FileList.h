//---------------------------------------------------------------------------

#ifndef FileListH
#define FileListH
#include <SysUtils.hpp>
#include <map>
//---------------------------------------------------------------------------
typedef std::pair<String, int> TFileItem;
typedef std::map<String, int> TFileList;
typedef TFileList::const_iterator TFileIt;
void __fastcall GetFileList(TFileList& lFiles, const String& strMask, bool recursively=false);
void __fastcall GetDirList(TFileList& lFiles, const String& strPath, bool recursively=false);
//---------------------------------------------------------------------------
#endif
