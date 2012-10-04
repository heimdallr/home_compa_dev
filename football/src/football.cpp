//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("MDIMainUnit.cpp", fmMDIMain);
USEFORM("MatchPlayer.cpp", fmPlayer);
USEFORM("Group.cpp", fmGroup);
USEFORM("..\..\Common\GetStringUnit.cpp", fmGetString);
USEFORM("..\..\Common\CatalogUnit.cpp", fmCatalog);
USEFORM("..\..\Common\Connect.cpp", dmConnect); /* TDataModule: File Type */
USEFORM("..\..\Common\ConnectImpl.cpp", dmConnectImpl); /* TDataModule: File Type */
USEFORM("..\..\Common\OptionsXML.cpp", dmOptionsXML); /* TDataModule: File Type */
USEFORM("Main.cpp", fmMain);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
     Application->Initialize();
     Application->CreateForm(__classid(TfmMDIMain), &fmMDIMain);
     Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  catch (...)
  {
     try
     {
       throw Exception("");
     }
     catch (Exception &exception)
     {
       Application->ShowException(&exception);
     }
  }
  return 0;
}
//---------------------------------------------------------------------------
