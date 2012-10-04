//---------------------------------------------------------------------------

#ifndef MDIMainUnitH
#define MDIMainUnitH
//---------------------------------------------------------------------------
#include "Connect.h"
#include "Options.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfmMDIMain : public TForm {
__published:	// IDE-managed Components
  TActionList *alMain;
  TAction *actExit;
  TStatusBar *sbMain;
  TTimer *Timer;
  TAction *actChangeChamp;
  void __fastcall actExitExecute(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall TimerTimer(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall actChangeChampExecute(TObject *Sender);
private:	// User declarations
  TOptions::Ptr _opt;
  TConnect::Ptr _connect;
  int _id_champ;
public:		// User declarations
  __fastcall TfmMDIMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmMDIMain *fmMDIMain;
//---------------------------------------------------------------------------
#endif
