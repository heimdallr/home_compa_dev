//---------------------------------------------------------------------------

#ifndef indicatorH
#define indicatorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfmIndicator : public TForm {
__published:	// IDE-managed Components
  TPanel *pnlRight;
  TPanel *pnlInfo;
  TLabeledEdit *eCount;
  TLabeledEdit *eLine;
  TLabeledEdit *eFig;
  TLabeledEdit *eFig0;
  TPanel *pnlImgNext;
  TImage *imNext;
private:	// User declarations
public:		// User declarations
  TTimer *Timer;
  TPanel *pnlImg;
  TImage *imMain;
  String strLog;
  int Interval;
  __fastcall TfmIndicator(TComponent *Owner, TTimer *tm, TPanel *pnl, TImage *im);
  void __fastcall SetInterval(int interval=0) {if(interval) Timer->Interval=interval; else Timer->Interval=Interval;}
};
//---------------------------------------------------------------------------
#endif
