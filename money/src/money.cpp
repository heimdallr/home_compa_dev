//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("..\..\Common\Connect.cpp", dmConnect); /* TDataModule: File Type */
USEFORM("..\..\Common\ConnectImpl.cpp", dmConnectImpl); /* TDataModule: File Type */
USEFORM("..\..\Common\OptionsXML.cpp", dmOptionsXML); /* TDataModule: File Type */
USEFORM("..\..\Common\DateInterval.cpp", fmDates);
USEFORM("..\..\Common\GetStringUnit.cpp", fmGetString);
USEFORM("..\..\Common\DBLoginUnit.cpp", fmLogin);
USEFORM("CatalogUnit.cpp", fmCatalog);
USEFORM("AboutUnit.cpp", fmAbout);
USEFORM("DocUnit.cpp", fmDoc);
USEFORM("DocStrUnit.cpp", fmDocStr);
USEFORM("ReportBase.cpp", fmReportBase);
USEFORM("ReportLauncher.cpp", dmReportLauncher); /* TDataModule: File Type */
USEFORM("ReportBaseTotal.cpp", fmReportBaseTotal);
USEFORM("ReportTurnover.cpp", fmReportTurnover);
USEFORM("ReportTurnoverDynamic.cpp", fmReportTurnoverDynamic);
USEFORM("ReportStock.cpp", fmReportStock);
USEFORM("MainUnit.cpp", fmMain);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
  try {
    Application->Initialize();
    Application->CreateForm(__classid(TfmMain), &fmMain);
     Application->Run();
  }
  catch (Exception &exception) {
    if(exception.Message.IsEmpty()) return -1;
    Application->ShowException(&exception);
  }
  catch (...) {}
  return 0;
/*
  try {
    Application->Initialize();
    Application->CreateForm(__classid(TfmMain), &fmMain);
    Application->Run();
  }
  catch (Exception &exception) {
    if(exception.Message.IsEmpty()) return -1;
    Application->ShowException(&exception);
  }
  catch (...) {}
  return 0;
*/  
}
//---------------------------------------------------------------------------
