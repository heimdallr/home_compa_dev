//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
#include <memory>
#include "data.h"
#include "fig_gen.h"
#include "indicator.h"

//---------------------------------------------------------------------------
class TfmMain : public TForm {
__published:	// IDE-managed Components
  TActionList *alMain;
  TAction *actExit;
  TAction *actLeft;
  TAction *actUp;
  TAction *actDown;
  TAction *actRight;
  TTimer *Timer;
  TAction *actRotate;
  TAction *actLRotate;
  TAction *actPause;
  TTimer *Time;
  TAction *actSave;
  TAction *actLoad;
  TPanel *pnlImg;
  TImage *imMain;
  TPanel *pnlBottom;
  TAction *actClearStat;
  void __fastcall actExitExecute(TObject *Sender);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall actMoveExecute(TObject *Sender);
  void __fastcall TimerTimer(TObject *Sender);
  void __fastcall actPauseExecute(TObject *Sender);
  void __fastcall TimeTimer(TObject *Sender);
  void __fastcall actSaveExecute(TObject *Sender);
  void __fastcall actLoadExecute(TObject *Sender);
  void __fastcall FormKeyPress(TObject *Sender, char &Key);
  void __fastcall actClearStatExecute(TObject *Sender);
private:	// User declarations
  std::auto_ptr<TTetris> _tetris;
  std::auto_ptr<TdmFigGen> _fig_gen;
  TfmIndicator* _indicator;
  String strIni, strXml, strDat, strLog;
public:		// User declarations
  __fastcall TfmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmMain *fmMain;
//---------------------------------------------------------------------------
#endif
