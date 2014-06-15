#ifndef MainH
#define MainH
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "DBGridEhGrouping.hpp"
#include <ActnList.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <DB.hpp>
#include <DBClient.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------

#include <map>
#include "Connect.h"

class TfmMain : public TForm {
__published:	// IDE-managed Components
  TActionList *alMain;
  TDBGridEh *dbgData;
  TDataSource *dsrcData;
  TAction *actLoad;
  TClientDataSet *dsData;
  TAction *actOpen;
  TAction *actReady;
  TPopupMenu *pmMain;
  TMenuItem *N1;
  TMenuItem *N2;
  TAction *actSetCountry1;
  TAction *actSetCountry2;
  TMenuItem *N3;
  TMenuItem *N11;
  TMenuItem *N21;
  TMenuItem *N12;
  TMenuItem *N22;
  TAction *actSetCountry1ByGroup;
  TAction *actSetCountry2ByGroup;
  TMenuItem *N4;
  TMenuItem *N5;
  TAction *actGroup;
  TTimer *Timer;
  void __fastcall actLoadExecute(TObject *Sender);
  void __fastcall actOpenExecute(TObject *Sender);
  void __fastcall actReadyExecute(TObject *Sender);
  void __fastcall dsDataAfterScroll(TDataSet *DataSet);
  void __fastcall actSetCountryExecute(TObject *Sender);
  void __fastcall dbgDataGetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont, TColor &Background, TGridDrawState State);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall actSetCountryByGroupExecute(TObject *Sender);
  void __fastcall dbgDataMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall dbgDataMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall actGroupExecute(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall TimerTimer(TObject *Sender);

private:	// User declarations
  void __fastcall EventsEventAlert(TObject *Sender, AnsiString EventName, int EventCount, bool &CancelAlerts);

private:	// User declarations
typedef std::multimap<TDateTime, int> TDateTimeList;
  TConnect *_connect;
  TConnect::TEventMessage::Ptr _eventer;
  int _id_champ, _nearest, _id_match_buf, _rank_buf, _match_num_buf;
  String _group_place_regex;
  TDateTimeList _date_time_list;

public:		// User declarations
  __fastcall TfmMain(int IdChamp);
};
//---------------------------------------------------------------------------
#endif
