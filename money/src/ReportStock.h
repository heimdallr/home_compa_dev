#ifndef ReportStockH
#define ReportStockH
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ReportBase.h"
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
#include <Chart.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include "DBGridEh.hpp"
#include "DBGridEhGrouping.hpp"
#include "GridsEh.hpp"
#include <DB.hpp>
#include <DBClient.hpp>
#include <Series.hpp>
//---------------------------------------------------------------------------

class TfmReportStock : public TfmReportBase {
__published:	// IDE-managed Components
  TAction *actChangeDeposit;
  TDBGridEh *dbgDeposit;
  TSplitter *Splitter1;
  TDataSource *dsrcDeposit;
  TClientDataSet *dsDeposit;
  TTimer *Timer;
  TChart *chrtMain;
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall TimerTimer(TObject *Sender);
  void __fastcall dbgDepositMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall dbgDepositDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol, TColumnEh *Column, TGridDrawState State);
  void __fastcall dbgDepositGetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont, TColor &Background, TGridDrawState State);
private:	// User declarations
typedef std::map<int, TColor> TColorMap;
static TReportListInserter ReportListInserter;
static TReport* __fastcall GetInstance() {return new TfmReportStock();}
class TSer {
  TLineSeries *_ser;
  double _val;
  TColor _color;
public:
typedef boost::shared_ptr<TSer> Ptr;
typedef std::map<int, Ptr> List;
  __fastcall TSer(TChart *Chart, TDateTime X, double V, TColor C);
  void __fastcall Add(TDateTime X1, TDateTime X2, double V);
};
  TColorMap _color;
  __fastcall TfmReportStock();
  void __fastcall LoadCatalog();
  void __fastcall SaveCatalog(bool FullMode=false);
  void __fastcall Run();
};
//---------------------------------------------------------------------------
#endif
