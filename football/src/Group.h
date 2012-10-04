//---------------------------------------------------------------------------

#ifndef GroupH
#define GroupH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <DB.hpp>
#include <DBClient.hpp>
#include <Menus.hpp>
#include <ImgList.hpp>
#include "DBGridEhGrouping.hpp"
#include <memory>
#include <map>
#include <boost/scoped_array.hpp>
#include "Connect.h"
//---------------------------------------------------------------------------
class TCountry {
public:
typedef std::pair<int, int> TGoal;
typedef std::map<int, TGoal> TGoalList;
private:
static int _max_num;
  int _play, _win, _deuce, _lose;
  TGoal _goal_total;
  TGoalList _goal;
public:
  static int __fastcall MaxNum() {return _max_num;}
  static void __fastcall MaxNum(int M) {_max_num=M;}
  const String Name;
  const int Id, Num, Place;
  __fastcall TCountry(const String &N, int I, int Nu, int P) :
    Id(I), Num(Nu), Name(N), Place(P),
    _play(0), _win(0), _deuce(0), _lose(0) {}
  void __fastcall SetRes(int Num, const TGoal& Goal, bool Ready) {
    if(_max_num<Num) _max_num=Num;
    if(_goal.find(Num)!=_goal.end()) return;
    if(Ready) {
      ++_play;
      if(Goal.first>Goal.second) ++_win;
      else if(Goal.first<Goal.second) ++_lose;
      else ++_deuce;
      _goal_total.first += Goal.first; _goal_total.second += Goal.second;
      _goal[Num] = Goal;
    }
  }
  int __fastcall GetPlay()  const {return _play;}
  int __fastcall GetWin()   const {return _win;}
  int __fastcall GetDeuce() const {return _deuce;}
  int __fastcall GetLose()  const {return _lose;}
  int __fastcall GetPoint()  const {return 3*_win+_deuce;}
  const TGoal& __fastcall GetGoalTotal() const {return _goal_total;}
  const TGoalList& __fastcall GetGoal() const {return _goal;}
};
//---------------------------------------------------------------------------

class TGroup {
public:
typedef std::map<int, TCountry> TCountryList;
private:
  TCountryList _country;
public:
  const String Name;
  __fastcall TGroup(const String &N) : Name(N) {}
  TCountry& __fastcall Add(const String &Name, int Id, int Num, int Place) {
    return _country.insert(std::make_pair(Num, TCountry(Name, Id, Num, Place))).first->second;
  }
  const TCountryList& __fastcall GetCountry() const {return _country;} 
};
//---------------------------------------------------------------------------

class TActionOwner {
typedef std::auto_ptr<TPanel> TPanelPtr;
typedef boost::scoped_array<TAction*> TActionList;
  TPanelPtr _panel;
  TActionList _act;
  TNotifyEvent _f;
  TPopupMenu *_menu;
public:
  __fastcall TActionOwner(TNotifyEvent F, TPopupMenu *Menu) : _panel(0), _f(F), _menu(Menu) {}
  void __fastcall Reset();
  void __fastcall Enabled(bool, int =0);
};
//---------------------------------------------------------------------------

class TfmGroup : public TForm {
__published:	// IDE-managed Components
  TActionList *ActionList1;
  TAction *actClose;
  TDBGridEh *dbgData;
  TDataSource *dsrcData;
  TClientDataSet *dsData;
  TAction *actLoad;
  TPopupMenu *pmMain;
  TMenuItem *N1;
  TAction *actDelPlace;
  TImageList *ilFlag;
  void __fastcall actCloseExecute(TObject *Sender);
  void __fastcall actLoadExecute(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall actSetPlaceExecute(TObject *Sender);
  void __fastcall dsDataAfterScroll(TDataSet *DataSet);
  void __fastcall dbgDataDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol, TColumnEh *Column, TGridDrawState State);
private:	// User declarations
typedef std::map<int, TGroup> TGroupList;
  TConnect::TEventMessage::Ptr _eventer;
  TGroupList _group;
  TActionOwner _action_owner;
  int _id_champ;
  void __fastcall MakeDataSet();
  void __fastcall MakeFlags();
  void __fastcall EventsEventAlert(TObject *Sender, AnsiString EventName, int EventCount, bool &CancelAlerts);
public:		// User declarations
  __fastcall TfmGroup(int IdChamp);
};
//---------------------------------------------------------------------------
extern TfmGroup *fmGroup;
#endif
