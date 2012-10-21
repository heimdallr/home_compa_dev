#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <ActnList.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <DB.hpp>
#include <DBClient.hpp>
#include "DBGridEhGrouping.hpp"
//---------------------------------------------------------------------------

#include "Options.h"
#include "Connect.h"
#include "Doc.h"
#include "Stock.h"
#include "DocStr.h"
#include "SafeAction.h"
#include "DynamicAction.h"

class TfmMain : public TForm {
__published:	// IDE-managed Components
  TMainMenu *mmMain;
  TMenuItem *N1;
  TPanel *pnlRight;
  TPanel *pnlMain;
  TSplitter *splMain;
  TActionList *alMain;
  TAction *actExit;
  TDBGridEh *dbgStock;
  TDataSource *dsrcStock;
  TAction *actLoad;
  TMenuItem *N3;
  TDataSource *dsrcDoc;
  TAction *actChangeDateInterval;
  TPanel *pnlDoc;
  TDBGridEh *dbgDoc;
  TDataSource *dsrcStr;
  TAction *actAddStr;
  TMenuItem *N5;
  TMenuItem *N7;
  TMenuItem *N8;
  TPopupMenu *pmDoc;
  TPopupMenu *pmStr;
  TMenuItem *N9;
  TMenuItem *N10;
  TAction *actAccept;
  TAction *actDelDoc;
  TPopupMenu *pmStock;
  TAction *actEditStr;
  TMenuItem *N11;
  TAction *actDelStr;
  TMenuItem *N12;
  TMenuItem *N13;
  TAction *actAbout;
  TMenuItem *N14;
  TMenuItem *actAccept1;
  TMenuItem *actDelDoc1;
  TMenuItem *N6;
  TMenuItem *N15;
  TMenuItem *N16;
  TPanel *pnlFilter;
  TLabel *lDateInterval;
  TAction *actShowCatalog;
  TMenuItem *N2;
  TMenuItem *N4;
  TDBGridEh *dbgStr;
  TAction *actLeft;
  TAction *actRight;
  TMenuItem *mmReport;
  TAction *actEditDoc;
  TMenuItem *actEditDoc1;
  TAction *actMul;
  void __fastcall actExitExecute(TObject *Sender);
  void __fastcall actLoadExecute(TObject *Sender);
  void __fastcall actChangeDateIntervalExecute(TObject *Sender);
  void __fastcall dsDocAfterScroll(TDataSet *DataSet);
  void __fastcall actAddStrExecute(TObject *Sender);
  void __fastcall actAcceptExecute(TObject *Sender);
  void __fastcall actDelDocExecute(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall actEditStrExecute(TObject *Sender);
  void __fastcall actDelStrExecute(TObject *Sender);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall dbgDocTitleBtnClick(TObject *Sender, int ACol, TColumnEh *Column);
  void __fastcall actAboutExecute(TObject *Sender);
  void __fastcall dbgStrTitleBtnClick(TObject *Sender, int ACol, TColumnEh *Column);
  void __fastcall dbgStockGetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont, TColor &Background, TGridDrawState State);
  void __fastcall dbgGetFooterParams(TObject *Sender, int DataCol, int Row, TColumnEh *Column, TFont *AFont, TColor &Background, TAlignment &Alignment, TGridDrawState State, AnsiString &Text);
  void __fastcall lDateIntervalMouseEnter(TObject *Sender);
  void __fastcall lDateIntervalMouseLeave(TObject *Sender);
  void __fastcall lDateIntervalClick(TObject *Sender);
  void __fastcall actShowCatalogExecute(TObject *Sender);
  void __fastcall dbgDocRowDetailPanelShow(TCustomDBGridEh *Sender, bool &CanShow);
  void __fastcall actLeftExecute(TObject *Sender);
  void __fastcall actRightExecute(TObject *Sender);
  void __fastcall FormActivate(TObject *Sender);
  void __fastcall FormDeactivate(TObject *Sender);
  void __fastcall actEditDocExecute(TObject *Sender);
  void __fastcall actMulExecute(TObject *Sender);
private:	// User declarations
typedef std::map<String, int> TAlertEventCount;
static TPropertyMap GetConnectProperty(TOptions *Opt);
  TDateTime _to, _from;
  TOptions::Ptr _opt;
  TConnect::Ptr _con;
  TDynamicAction _stock_action;
  TDoc::Ptr _doc;
  TClientDataSet *dsDoc;
  TDocStr::Ptr _doc_str;
  TClientDataSet *dsDocStr;
  TStock::Ptr _stock;
  TClientDataSet *dsStock;
  TSafeAction _safe_action;
  TColumnEh *_person;
  void __fastcall StockActionExecute(TObject *Sender);
  void __fastcall SetCaption();
  void __fastcall ActionsEnable();
  void __fastcall ActionsDisable();
public:		// User declarations
  __fastcall TfmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmMain *fmMain;
//---------------------------------------------------------------------------
#endif
