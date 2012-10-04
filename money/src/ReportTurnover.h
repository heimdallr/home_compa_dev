//---------------------------------------------------------------------------

#ifndef ReportTurnoverH
#define ReportTurnoverH
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
#include <Chart.hpp>
#include <Db.hpp>
#include <DB.hpp>
#include <DBClient.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Series.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
//---------------------------------------------------------------------------
class TfmReportTurnover : public TfmReportBaseTotal {
__published:	// IDE-managed Components
  TPanel *pnlData;
  TDBGridEh *dbgData;
  TSplitter *Splitter4;
  TDataSource *dsrcData;
  TMemTableEh *mtData;
  TDataSetDriverEh *dsdData;
  TClientDataSet *dsData;
  TChart *chrtMain;
  TPopupMenu *pmChart;
  TMenuItem *N2;
  TPopupMenu *pmData;
  TMenuItem *N1;
  TAction *actChangeColor;
  TAction *actSwitchMark;
  void __fastcall chrtMainResize(TObject *Sender);
  void __fastcall dbgDataGetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont, TColor &Background, TGridDrawState State);
  void __fastcall actChangeColorExecute(TObject *Sender);
  void __fastcall actSwitchMarkExecute(TObject *Sender);
  void __fastcall chrtMainMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall chrtMainMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall dbgDataDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol, TColumnEh *Column, TGridDrawState State);
private:	// User declarations
struct TDataItem {
typedef boost::shared_ptr<TDataItem> Ptr;
typedef boost::weak_ptr<TDataItem> WPtr;
typedef std::vector<WPtr> ChildrenList;
static Ptr Get(TClientDataSet *S) {return Ptr(new TDataItem(S));}
static Ptr Get(double S, TColor C) {return Ptr(new TDataItem(S, C));}
  __fastcall TDataItem(TClientDataSet*);
  __fastcall TDataItem(double S, TColor C);
  int Id, IdParent;
  double Summa;
  const String Name;
  TColor Color;
  ChildrenList Children;
};
typedef std::map<int, TDataItem::Ptr> TDataList;
typedef std::map<double, TDataItem::Ptr> TDataItemList;
typedef std::vector<TDataItemList> TSearch;
typedef std::map<int, unsigned int> TRadiusList;
static TReportListInserter ReportListInserter;
static TReport* __fastcall GetInstance() {return new TfmReportTurnover();}
  TSearch _search;
  TRadiusList _radius_list;
  __fastcall TfmReportTurnover();
  void __fastcall Run();
  void __fastcall MakeChart();
  TDataItem::Ptr __fastcall Search(int X, int Y);
  void __fastcall BuildData();
};
//---------------------------------------------------------------------------
#endif
