#ifndef ReportTurnoverDynamicH
#define ReportTurnoverDynamicH
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DataDriverEh.hpp"
#include "DBGridEh.hpp"
#include "DBGridEhGrouping.hpp"
#include "GridsEh.hpp"
#include "MemTableDataEh.hpp"
#include "MemTableEh.hpp"
#include "ReportBaseTotal.h"
#include <ActnList.hpp>
#include <DB.hpp>
#include <Db.hpp>
#include <DBClient.hpp>
#include <ExtCtrls.hpp>
#include "DBCtrlsEh.hpp"
#include "DBLookupEh.hpp"
#include <Mask.hpp>
#include <Chart.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Series.hpp>
//---------------------------------------------------------------------------

class TfmReportTurnoverDynamic : public TfmReportBaseTotal {
__published:	// IDE-managed Components
  TPanel *pnlData;
  TSplitter *Splitter1;
  TChart *chrtMain;
  TDBGridEh *dbgData;
  TDataSource *dsrcData;
  TClientDataSet *dsData;
  TDBGridEh *dbgDoc;
  TDBGridEh *dbgStr;
  TDataSource *dsrcDoc;
  TClientDataSet *dsDoc;
  TDataSource *dsrcStr;
  TClientDataSet *dsStr;
  TBarSeries *Ser;
  TLineSeries *NullLine;
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall dbgDataRowDetailPanelShow(TCustomDBGridEh *Sender, bool &CanShow);
  void __fastcall dbgDocRowDetailPanelShow(TCustomDBGridEh *Sender, bool &CanShow);
  void __fastcall dbgStrGetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont, TColor &Background, TGridDrawState State);
  void __fastcall chrtMainClickSeries(TCustomChart *Sender, TChartSeries *Series, int ValueIndex, TMouseButton Button, TShiftState Shift, int X, int Y);
private:	// User declarations
typedef std::map<int, int> TSearchList;
static TReportListInserter ReportListInserter;
static TReport* __fastcall GetInstance() {return new TfmReportTurnoverDynamic();}
  TColumnEh *_person;
  TSearchList _search;
  __fastcall TfmReportTurnoverDynamic();
  void __fastcall Run();
};
//---------------------------------------------------------------------------
#endif
