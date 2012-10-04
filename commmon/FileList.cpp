//---------------------------------------------------------------------------


#pragma hdrstop

#include "FileList.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

// Тянем список файлов
void __fastcall GetFileList(TFileList& lFiles, const String& strFullMask, bool recursively) {
  String strPath=ExtractFilePath(strFullMask);
  TSearchRec F;
  if(!FindFirst(strFullMask, faAnyFile&~faDirectory, F)) {
    do lFiles[strPath+F.Name] = F.Size;
    while(!FindNext(F));
    FindClose(F);
  }
  if(!recursively) return;
  if(!FindFirst(strPath+"*", faDirectory, F)) {
    do
      if(F.Attr&faDirectory && F.Name!="." && F.Name!="..")
        GetFileList(lFiles, strPath+F.Name+"\\"+ExtractFileName(strFullMask), recursively);
    while(!FindNext(F));
    FindClose(F);
  }
}
//---------------------------------------------------------------------------

// Тянем список папок
void __fastcall GetDirList(TFileList& lFiles, const String& strPath, bool recursively) {
  lFiles[strPath] = 0;
  if(!recursively) return;
  TSearchRec F;
  if(!FindFirst(strPath+"\\"+"*", faDirectory, F)) {
    do
      if(F.Attr&faDirectory && F.Name!="." && F.Name!="..")
        GetDirList(lFiles, strPath+"\\"+F.Name, recursively);
    while(!FindNext(F));
    FindClose(F);
  }
}
//---------------------------------------------------------------------------

