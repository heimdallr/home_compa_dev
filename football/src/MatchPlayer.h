//---------------------------------------------------------------------------
#ifndef MatchPlayerH
#define MatchPlayerH
//---------------------------------------------------------------------------

#include "Connect.h"
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <ActnList.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <DB.hpp>
#include <DBClient.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Provider.hpp>
#include <StdCtrls.hpp>
#include "DBGridEhGrouping.hpp"
#include <map>
//---------------------------------------------------------------------------

class TfmPlayer : public TForm {
__published:	// IDE-managed Components
  TActionList *alMain;
  TAction *actClose;
  TDataSource *dsrcChamp1;
  TClientDataSet *dsChamp1;
  TDataSource *dsrcChamp2;
  TClientDataSet *dsChamp2;
  TDataSource *dsrcMatch1;
  TClientDataSet *dsMatch1;
  TDataSource *dsrcMatch2;
  TClientDataSet *dsMatch2;
  TClientDataSet *dsData;
  TAction *actLoad;
  TDataSetProvider *dspData;
  TAction *actAdd;
  TPopupMenu *pmChamp;
  TMenuItem *pmChamp1N1;
  TAction *actGetInfo;
  TAction *actSubst;
  TPopupMenu *pmMatch;
  TMenuItem *miGoal;
  TMenuItem *miSubst;
  TMenuItem *N4;
  TGroupBox *pnlPlayer2;
  TDBGridEh *dbgChamp2;
  TDBGridEh *dbgMatch2;
  TGroupBox *pnlPlayer1;
  TDBGridEh *dbgChamp1;
  TDBGridEh *dbgMatch1;
  TPanel *pnlBottom1;
  TPanel *pnlLeft1;
  TPanel *pnlMiddle1;
  TPanel *pnlRight1;
  TPanel *pnlBottom2;
  TPanel *pnlLeft2;
  TPanel *pnlMiddle2;
  TPanel *pnlRight2;
  TAction *actDel;
  TMenuItem *N6;
  TPanel *pnlMiddle;
  TPanel *Panel1;
  TPanel *pnlTop1;
  TPanel *pnlTop2;
  TMenuItem *N10;
  TMenuItem *miCardMatch;
  TMenuItem *miCardChamp;
  void __fastcall actCloseExecute(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
  void __fastcall actLoadExecute(TObject *Sender);
  OleVariant __fastcall dspDataDataRequest(TObject *Sender, OleVariant &Input);
  void __fastcall actAddExecute(TObject *Sender);
  void __fastcall dbgChampMatchEnter(TObject *Sender);
  void __fastcall actGetInfoExecute(TObject *Sender);
  void __fastcall actSubstExecute(TObject *Sender);
  void __fastcall actGoalExecute(TObject *Sender);
  void __fastcall actDelExecute(TObject *Sender);
  void __fastcall dbgGetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont, TColor &Background, TGridDrawState State);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
  TConnect *_connect;
  const int _id1, _id2, _id_match;
  int _id_array[2], _id;
  TConnect::TEventMessage::Ptr _eventer;
  TClientDataSet *dsChamp, *dsMatch, *dsChampArray[2], *dsMatchArray[2];
  void __fastcall Load(int Id, TDBGridEh *dbgChamp, TDBGridEh *dbgMatch);
  void __fastcall EventAlertPlayer(TObject *Sender, AnsiString EventName, int EventCount, bool &CancelAlerts);
  void __fastcall actCardChampExecute(TObject *Sender);
  void __fastcall actCardMatchExecute(TObject *Sender);
  void __fastcall SetColWidth(TDBGridEh *Grid);
public:		// User declarations
  __fastcall TfmPlayer(int id_match, int id1, int id2);
  int __fastcall GetIdMatch() const {return _id_match;}
};
//---------------------------------------------------------------------------
extern TfmPlayer *fmPlayer;
#endif
