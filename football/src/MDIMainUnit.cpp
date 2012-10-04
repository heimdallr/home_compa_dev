//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MDIMainUnit.h"
#include "OptionsXML.h"
#include "ConnectImpl.h"
#include "Main.h"
#include "CatalogUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmMDIMain *fmMDIMain;
//---------------------------------------------------------------------------
__fastcall TfmMDIMain::TfmMDIMain(TComponent* Owner) : TForm(Owner),
_opt(TOptionsXML::GetInstance(ChangeFileExt(GetModuleName(0), ".xml"))),
_connect(TdmConnectImpl::GetInstance(_opt->GetPropMap("Connect"))),
_id_champ(TOptions::Instance->Get("Options", "IdChamp", "1").ToInt())
{
}
//---------------------------------------------------------------------------

void __fastcall TfmMDIMain::actExitExecute(TObject *Sender) {
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TfmMDIMain::FormClose(TObject *Sender, TCloseAction &Action) {
  TOptions::Instance->SaveLayout(this);
  for(int i=MDIChildCount-1; i>=0; --i) this->MDIChildren[i]->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfmMDIMain::TimerTimer(TObject *Sender) {
  sbMain->Panels->Items[1]->Text = Now().FormatString("dd.mm.yyyy hh:nn:ss");
}
//---------------------------------------------------------------------------

void __fastcall TfmMDIMain::FormResize(TObject *Sender) {
  sbMain->Panels->Items[0]->Width = sbMain->Width - 160*(sbMain->Panels->Count-1);
}
//---------------------------------------------------------------------------

void __fastcall TfmMDIMain::FormPaint(TObject *Sender) {
  OnPaint = 0;
  TOptions::Instance->RestoreLayout(this);
  (new TfmMain(_id_champ))->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfmMDIMain::actChangeChampExecute(TObject *Sender) {
  TDSPtr dsData = ns_Catalog::Get(ns_Catalog::TInit("ID", "select id, year_, description from get_champ", "Укажите чемпионат", _id_champ).AddField("", 0).AddField("Год", 10).AddField("Чемпионат", 100));
  if(!dsData.get()) return;
  for(int i=MDIChildCount-1; i>=0; --i) this->MDIChildren[i]->Close();
  TOptions::Instance->Set("Options", "IdChamp", dsData->FieldByName("id")->AsString);
  (new TfmMain(_id_champ = dsData->FieldByName("id")->AsInteger))->Show();
}
//---------------------------------------------------------------------------

