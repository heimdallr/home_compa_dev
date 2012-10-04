//---------------------------------------------------------------------------

#ifndef ConnectKeeperH
#define ConnectKeeperH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <boost/shared_ptr.hpp>
#include "log.h"
#include "ConnectImpl.h"
//---------------------------------------------------------------------------

class TdmConnectKeeper : public TDataModule {
__published:	// IDE-managed Components
  TTimer *Timer;
  void __fastcall DataModuleDestroy(TObject *Sender);
  void __fastcall TimerTimer(TObject *Sender);
private:	// User declarations
  bool _connected;
  typedef std::list<TNotifyEvent> TNotifyEventList;
  typedef TNotifyEventList::const_iterator TNotifyEventIt;
  TNotifyEventList _on_connect, _on_disconnect;
  TPropertyMap _con_param;
  TLoggerPtr _log;
  TConnectionPtr _con, _keep_alive;
  TApplication *_app;
protected:
  __fastcall TdmConnectKeeper(const String &Reg, TLoggerPtr L);
public:		// User declarations
  void __fastcall AddReconnectCallback(TNotifyEvent C, TNotifyEvent D) {_on_connect.push_back(C), _on_disconnect.push_back(D);}
  TDSPtr __fastcall GetReadDataSet(const String &Query, const TQueryParams &Param=TQueryParams()) {return _con->GetReadDataSet(Query, Param);}
  TSQLPtr __fastcall GetReadSQL(const String &Query, const TQueryParams &Param=TQueryParams(), bool Run=true) {return _con->GetReadSQL(Query, Param, Run);}
  static TdmConnectKeeper* __fastcall GetInstance(const String &Reg, TLoggerPtr L) {return new TdmConnectKeeper(Reg, L);}
  void __fastcall SetApp(TApplication *app) {_app=app;}
  TApplication* __fastcall GetApp() const {return _app;}
  TLoggerPtr __fastcall GetLogger() {return _log;}
};
//---------------------------------------------------------------------------
typedef TdmConnectKeeper TConnectKeeper;
typedef boost::shared_ptr<TdmConnectKeeper> TConnectKeeperPtr;
extern TConnectKeeper *ConnectKeeper;
#endif
