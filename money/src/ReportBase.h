#ifndef ReportBaseH
#define ReportBaseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
#include <DateUtils.hpp>
//---------------------------------------------------------------------------

#include "ReportLauncher.h"
#include "Connect.h"
#include <vector>
//---------------------------------------------------------------------------

class TfmReportBase : public TForm {
__published:	// IDE-managed Components
  TPanel *pnlFilter;
  TPanel *pnlMain;
  TActionList *alMain;
  TAction *actClose;
  TAction *actChangeDateInterval;
  TAction *actRunReport;
  TPanel *pnlDateInterval;
  TLabel *lDateInterval;
  TPanel *pnlDateIntervalType;
  TLabel *lDateIntervalType;
  TAction *actChangeDateIntervalType;
  void __fastcall actCloseExecute(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall lMouseEnter(TObject *Sender);
  void __fastcall lMouseLeave(TObject *Sender);
  void __fastcall lDateIntervalClick(TObject *Sender);
  void __fastcall actChangeDateIntervalExecute(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall dsCatalogAfterPost(TDataSet *DataSet);
  void __fastcall actChangeDateIntervalTypeExecute(TObject *Sender);
  void __fastcall lDateIntervalTypeClick(TObject *Sender);
  void __fastcall actRunReportExecute(TObject *Sender);
private:	// User declarations
friend void __fastcall TdmReportLauncher::actRunExecute(TObject *Sender);
protected:// User declarations
typedef TfmReportBase* __fastcall (*TReportGetInstanceFunc)();
typedef std::pair<String, TReportGetInstanceFunc> TReportItem;
typedef std::vector<TReportItem> TReportList;
static TReportList& __fastcall GetReportList();
static TColor __fastcall GetColor(int K=6);
static TIBTransaction* __fastcall GetCatalogTransaction();
static void __fastcall LoadCatalog(TClientDataSet *Data, const String &ParentName, bool AddAll=false);
static void __fastcall SaveCatalog(TClientDataSet *Data, const String &ParentName, bool FullMode);
class TReportListInserter {
public:
  TReportListInserter(const String &Caption, TReportGetInstanceFunc F);
};
friend TfmReportBase::TReportListInserter::TReportListInserter(const String &Caption, TReportGetInstanceFunc F);
  TDate _from, _to;
  TSafeAction _safe_action;
  int _id_interval;
  __fastcall TfmReportBase(TDate From=StartOfTheMonth(Date()), TDate To=EndOfTheMonth(Date()));
  void __fastcall ChangeDateIntervalTypeExecute(TClientDataSet *Data, bool R=true);
  virtual void __fastcall Run() =0;
  virtual void __fastcall LoadCatalog() =0;
  virtual void __fastcall SaveCatalog(bool FullMode=false) =0;
public:		// User declarations
static void __fastcall SetMenu(TMenuItem*);
};
typedef TfmReportBase TReport;

//---------------------------------------------------------------------------
#endif
