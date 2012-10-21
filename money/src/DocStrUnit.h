#ifndef DocStrUnitH
#define DocStrUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
#include "MemTableDataEh.hpp"
#include "MemTableEh.hpp"
#include <DB.hpp>
#include <Db.hpp>
#include "DBCtrlsEh.hpp"
#include "DBGridEh.hpp"
#include "DBLookupEh.hpp"
#include <Mask.hpp>
#include <Buttons.hpp>
#include <DBClient.hpp>
#include "DataDriverEh.hpp"
#include "DBGridEhGrouping.hpp"
#include "GridsEh.hpp"
//---------------------------------------------------------------------------

#include "Doc.h"
#include "DocStr.h"
#include "CatalogUnit.h"
//---------------------------------------------------------------------------

class TfmDocStr : public TForm {
__published:	// IDE-managed Components
  TActionList *alMain;
  TAction *actOk;
  TAction *actCancel;
  TGroupBox *gbNote;
  TPanel *pnlNote;
  TEdit *eNote;
  TGroupBox *gbQty;
  TGroupBox *gbType;
  TPanel *pnlType;
  TGroupBox *gbTarget;
  TPanel *pnlTarget;
  TDBLookupComboboxEh *lcbTarget;
  TPanel *pnlBtn;
  TBitBtn *btnOk;
  TBitBtn *btnCancel;
  TDataSource *dsrcTarget;
  TClientDataSet *dsTarget;
  TDataSource *dsrcSumma;
  TClientDataSet *dsSumma;
  TCurrencyField *dsSummaSumma;
  TFloatField *dsSummaQty;
  TPanel *pnlBtnSaveSumma;
  TSpeedButton *SpeedButton1;
  TPanel *pnlQtySumma;
  TPanel *pnlQty;
  TDBEditEh *eQty;
  TPanel *pnlSumma;
  TDBEditEh *eSumma;
  TAction *actSetQty;
  TAction *actOkEdit;
  TAction *actOkNew;
  TAction *actLeft;
  TAction *actRight;
  TAction *actMul;
  void __fastcall actCancelExecute(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
  void __fastcall eSummaEnter(TObject *Sender);
  void __fastcall actSetQtyExecute(TObject *Sender);
  void __fastcall eSummaExit(TObject *Sender);
  void __fastcall eSummaKeyPress(TObject *Sender, char &Key);
  void __fastcall eQtyKeyPress(TObject *Sender, char &Key);
  void __fastcall actOkNewExecute(TObject *Sender);
  void __fastcall actOkEditExecute(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall actLeftExecute(TObject *Sender);
  void __fastcall actRightExecute(TObject *Sender);
  void __fastcall actMulExecute(TObject *Sender);
private:	// User declarations
static TClientDataSet* __fastcall GetTargetDataSet();
  TClientDataSet *_doc;
  TDocStr::Ptr _doc_str;
  TCatalog::Ptr _str_type_cat;
  TSafeAction _safe_action;
  bool _new_str, _tsf_mode;
  int _def_target;
  __fastcall TfmDocStr(TClientDataSet *Doc, TDocStr::Ptr DocStr, bool NewStr=true);
  void __fastcall StrNew(TObject *Sender) {actOkNew->OnExecute(actOkNew);}
  void __fastcall StrEdit(TObject *Sender) {actOkEdit->OnExecute(actOkEdit);}
  void __fastcall InitNewEdit();
  void __fastcall GetTarget(int &IdTarget, int &IdDeposit);
public:		// User declarations
typedef boost::shared_ptr<TfmDocStr> Ptr;
static Ptr GetInstance(TClientDataSet *Doc, TDocStr::Ptr DocStr, bool NewStr=true) {return Ptr(new TfmDocStr(Doc, DocStr, NewStr));}
};
typedef TfmDocStr TDocStrEditForm;
//---------------------------------------------------------------------------
#endif
