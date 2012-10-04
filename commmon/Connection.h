//---------------------------------------------------------------------------

#ifndef ConnectionH
#define ConnectionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <IBDatabase.hpp>
#include <DBClient.hpp>
#include <DBLocal.hpp>
#include <DBLocalI.hpp>
#include <Provider.hpp>
#include <IBSQL.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>
#include <IBEvents.hpp>
#include <memory>
#include <list>
#include <map>
//---------------------------------------------------------------------------
#include "TransactionPtr.h"
//---------------------------------------------------------------------------
typedef std::auto_ptr<TClientDataSet> TDataSetPtr;
typedef std::auto_ptr<TIBSQL> TSQLPtr;
typedef std::list<String> TStrList;
typedef TStrList::const_iterator TStrIt;

typedef std::multimap<String, TEventAlert> TEventList;
typedef TEventList::iterator TEventIt;
/*
typedef std::multimap<int, TEventAlert> TEventAlertList;
typedef TEventAlertList::iterator TEventAlertIt;
*/
//---------------------------------------------------------------------------

class TdmConnect : public TDataModule {
friend class TEventer;
__published:	// IDE-managed Components
  TIBDatabase *Database;
  TIBTransaction *trRead;
  TIBSQL *sqlRead;
  TIBQuery *Query;
  TIBEvents *Events;
  TClientDataSet *dsEvent;
  TStringField *dsEventName;
  TIntegerField *dsEventAlert;
  void __fastcall DataModuleDestroy(TObject *Sender);
  void __fastcall EventsEventAlert(TObject *Sender, AnsiString EventName, int EventCount, bool &CancelAlerts);
private:	// User declarations
  TEventList _event;
//  TEventAlertList _event_alert;
  TClientDataSet* __fastcall DataSetExec(TIBSQL*);
  void __fastcall RegisterEvent(TEventAlert Alert, const TStrList &lEventName);
  void __fastcall UnRegisterEvent(TEventAlert Alert, const TStrList &lEventName);
  void __fastcall ResetEvents();
public:		// User declarations
  __fastcall TdmConnect(const String &strHost, const String &strBase, const String &strUser, const String &strPassword);

  void __fastcall ReadDataSetInit(const String &strQuery) {sqlRead->Close(); sqlRead->SQL->Text=strQuery;}
  TIBXSQLVAR* __fastcall ReadDataSetParam(const String &strParam) {return sqlRead->ParamByName(strParam);}
  TDataSetPtr __fastcall ReadDataSetExec() {return TDataSetPtr(DataSetExec(sqlRead));}

  TSQLPtr __fastcall GetReadSQL(const String &strQuery="");
  TSQLPtr __fastcall GetWriteSQL(const String &strQuery="", TIBTransaction *T=0);
};
//---------------------------------------------------------------------------

class TEventer {
  TdmConnect *_connect;
  TStrList _event_name;
  TEventAlert _alert;
public:
  __fastcall TEventer(TdmConnect *connect, TEventAlert Alert, const TStrList &EventName) : _connect(connect), _alert(Alert), _event_name(EventName) {_connect->RegisterEvent(_alert, _event_name);}
  __fastcall TEventer(TdmConnect *connect, TEventAlert Alert, const String &strEventName) : _connect(connect), _alert(Alert) {_event_name.push_back(strEventName); _connect->RegisterEvent(_alert, _event_name);}
  __fastcall ~TEventer() {_connect->UnRegisterEvent(_alert, _event_name);}
};
typedef std::auto_ptr<TEventer> TEventerPtr;
//---------------------------------------------------------------------------
#endif
