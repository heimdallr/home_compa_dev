//---------------------------------------------------------------------------

#ifndef ReportBaseTotalH
#define ReportBaseTotalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ReportBase.h"
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
#include "DataDriverEh.hpp"
#include "DBGridEh.hpp"
#include "DBGridEhGrouping.hpp"
#include "GridsEh.hpp"
#include "MemTableDataEh.hpp"
#include "MemTableEh.hpp"
#include <DB.hpp>
#include <Db.hpp>
#include <DBClient.hpp>
#include <IBDatabase.hpp>
//---------------------------------------------------------------------------
class TfmReportBaseTotal : public TfmReportBase {
__published:	// IDE-managed Components
  TPanel *pnlOpts;
  TSplitter *splPerson;
  TDBGridEh *dbgPerson;
  TSplitter *splOpt;
  TPanel *pnlRes;
  TTimer *Timer;
  TDataSource *dsrcState;
  TMemTableEh *mtState;
  TDataSetDriverEh *dsdState;
  TClientDataSet *dsState;
  TDataSource *dsrcDeposit;
  TClientDataSet *dsDeposit;
  TDataSource *dsrcPerson;
  TClientDataSet *dsPerson;
  TPanel *pnlOptClient;
  TDBGridEh *dbgDeposit;
  TSplitter *splDeposit;
  TDBGridEh *dbgState;
  TAction *actLeft;
  TAction *actRight;
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall mtStateAfterPost(TDataSet *DataSet);
  void __fastcall dbgStateMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall TimerTimer(TObject *Sender);
  void __fastcall actLeftExecute(TObject *Sender);
  void __fastcall actRightExecute(TObject *Sender);
private:	// User declarations
  void __fastcall LoadCatalog();
  void __fastcall SaveCatalog(bool FullMode=false);
protected:
  __fastcall TfmReportBaseTotal(TDate From=StartOfTheMonth(Date()), TDate To=EndOfTheMonth(Date()));
};
//---------------------------------------------------------------------------
#endif
