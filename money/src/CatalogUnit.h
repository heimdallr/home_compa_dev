#ifndef CatalogUnitH
#define CatalogUnitH
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
#include "DataDriverEh.hpp"
#include "MemTableDataEh.hpp"
#include "MemTableEh.hpp"
#include <DBClient.hpp>
#include <Provider.hpp>
#include "DBGridEhGrouping.hpp"
#include <DB.hpp>
#include <Db.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <memory>
#include <map>
#include "Connect.h"
#include "SafeAction.h"
//---------------------------------------------------------------------------

class TfmCatalog : public TForm {
__published:	// IDE-managed Components
  TPanel *pnlBottom;
  TPanel *pnlMain;
  TDBGridEh *dbgData;
  TBitBtn *btnOk;
  TBitBtn *btnCancel;
  TActionList *alMain;
  TAction *actOk;
  TAction *actCancel;
  TDataSetDriverEh *dsdData;
  TMemTableEh *mtData;
  TDataSource *dsrcData;
  TClientDataSet *dsData;
  TAction *actAdd;
  TAction *actEdit;
  TAction *actDel;
  TPopupMenu *pmCatalog;
  TMenuItem *N1;
  TMenuItem *N2;
  TMenuItem *N3;
  TAction *actAddChild;
  TMenuItem *N4;
  TMenuItem *N5;
  TAction *actCollapse;
  TAction *actExpand;
  TMenuItem *N6;
  TMenuItem *N7;
  TMenuItem *N8;
  TAction *actLeft;
  TAction *actRight;
  TAction *actSetColor;
  TMenuItem *N9;
  TMenuItem *N10;
  TAction *actUp;
  TAction *actDown;
  TMenuItem *N11;
  TMenuItem *N12;
  TMenuItem *N13;
  void __fastcall actOkExecute(TObject *Sender);
  void __fastcall actCancelExecute(TObject *Sender);
  void __fastcall actAddExecute(TObject *Sender);
  void __fastcall actEditExecute(TObject *Sender);
  void __fastcall actDelExecute(TObject *Sender);
  void __fastcall actAddChildExecute(TObject *Sender);
  void __fastcall actCollapseExecute(TObject *Sender);
  void __fastcall actExpandExecute(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall dbgDataGetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont, TColor &Background, TGridDrawState State);
  void __fastcall actLeftExecute(TObject *Sender);
  void __fastcall actRightExecute(TObject *Sender);
  void __fastcall actSetColorExecute(TObject *Sender);
  void __fastcall dbgDataDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol, TColumnEh *Column, TGridDrawState State);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall actUpExecute(TObject *Sender);
  void __fastcall actDownExecute(TObject *Sender);
public:
class TInit {
friend class TfmCatalog;
  String Query, Caption;
  bool Recursively;
  String __fastcall GetQuery(const String &Obj, bool Rec, bool AA);
  String __fastcall GetQuery(int IdParent, bool Rec, bool AA);
  void __fastcall Init(bool Rec, const String &C);
public:
  __fastcall TInit(const char *Obj, bool Rec=true, bool AA=false, const String &C="Справочник") : Query(GetQuery(Obj, Rec, AA)) {Init(Rec, C);}
  __fastcall TInit(const String &Obj, bool Rec=true, bool AA=false, const String &C="Справочник") : Query(GetQuery(Obj, Rec, AA)) {Init(Rec, C);}
  __fastcall TInit(int IdParent, bool Rec=true, bool AA=false, const String &C="Справочник") : Query(GetQuery(IdParent, Rec, AA)) {Init(Rec, C);}
};
private:	// User declarations
class TTreeKeeper {
typedef std::map<int, bool> TStorage;
  TMemTableEh *_data;
  int _id;
  TStorage _storage;
public:
  __fastcall TTreeKeeper(TMemTableEh *Data);
  __fastcall ~TTreeKeeper();
};
//-- TreeKeeper -------------------------------------------------------------
static TDSPtr GetRes(const TInit &I, TDSPtr Data);
static void __fastcall Set(int Id, const String &Name, const Variant &Value);
  TInit _init;
  TConnect::TEventMessage::Ptr _event;
  TSafeAction _safe_action;
  __fastcall TfmCatalog(const TInit &I, TClientDataSet *Data);
  void __fastcall Init(TClientDataSet *Data);
  void __fastcall OnEvent(TObject *Sender, AnsiString EventName, int EventCount, bool &CancelAlerts);
  void __fastcall Add(int IdParent);
public:		// User declarations
typedef std::auto_ptr<TfmCatalog> Ptr;
static TDSPtr Get(const TInit &I);
static TDSPtr GetDataSet(const TInit &I);
static Ptr GetInstance(const TInit &I);
static void __fastcall SetCatalogColor(int Id, int Color);
static void __fastcall SetCatalogName(int Id, String Caption);
static void __fastcall SetCatalogQty(int Id, double Qty);
static void __fastcall SetCatalogOrdNum(int Id, int Direction);
  TDBGridEh* __fastcall GetCatalogGrid() const {return dbgData;}
  void __fastcall Collapse();
  void __fastcall Expand();
  void __fastcall Locate(int Id);
  void __fastcall Hide(int Id);
  TField* __fastcall FieldByName(const String &) const;
};
typedef TfmCatalog TCatalog;
//---------------------------------------------------------------------------
#endif
