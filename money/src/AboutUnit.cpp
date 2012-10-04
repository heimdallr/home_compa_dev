#include <vcl.h>
#pragma hdrstop
#include "AboutUnit.h"
#include "functions.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
//---------------------------------------------------------------------

__fastcall TfmAbout::TfmAbout() : TForm(static_cast<TComponent*>(0)) {
  ProductName->Caption = String().sprintf("%s, %s", ns_Functions::GetFileVersion(Application->ExeName, "ProductName"), ns_Functions::GetFileVersion(Application->ExeName));
  LegalTrademarks->Caption = ns_Functions::GetFileVersion(Application->ExeName, "LegalTrademarks");
  LegalCopyright->Caption = ns_Functions::GetFileVersion(Application->ExeName, "LegalCopyright");
  Comments->Caption = ns_Functions::GetFileVersion(Application->ExeName, "Comments");
}
//---------------------------------------------------------------------


