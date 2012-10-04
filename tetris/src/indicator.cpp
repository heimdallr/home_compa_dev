//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "indicator.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfmIndicator::TfmIndicator(TComponent *Owner, TTimer *tm, TPanel *pnl, TImage *im)
: TForm(Owner), Timer(tm), pnlImg(pnl), imMain(im), Interval(tm->Interval) {
}
//---------------------------------------------------------------------------
