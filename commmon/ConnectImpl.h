//---------------------------------------------------------------------------

#ifndef ConnectImplH
#define ConnectImplH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "PropertyMap.h"
#include "Connect.h"
#include <DB.hpp>
#include <DBClient.hpp>
#include <DBLocal.hpp>
#include <DBLocalI.hpp>
#include <IBDatabase.hpp>
#include <IBEvents.hpp>
#include <IBSQL.hpp>
#include <Provider.hpp>
//---------------------------------------------------------------------------



class TdmConnectImpl : public TdmConnect {
__published:	// IDE-managed Components
  TIBDatabase *Database;
  TIBTransaction *trRead;
  TIBSQL *sqlRead;
  TIBClientDataSet *dsRead;
  TIBEvents *Events;
  TIBClientDataSet *dsWrite;
  TIBTransaction *trWrite;
  void __fastcall DataModuleDestroy(TObject *Sender);
private:	// User declarations
  TCOMCriticalSection _lock;
protected:
  __fastcall TdmConnectImpl(const TPropertyMap&);
public:		// User declarations
class TEventMessageImpl : public TEventMessage {
  std::auto_ptr<TIBEvents> _event;
public:
  __fastcall TEventMessageImpl(const TEventList &EventList, TEventAlert F, TIBDatabase *DB);
  virtual __fastcall ~TEventMessageImpl();
  virtual const TStrings* __fastcall GetEvents() const {return _event->Events;} 
};

  static Ptr GetInstance(const TPropertyMap&);
  virtual bool __fastcall IsActive();
  virtual TDSPtr __fastcall GetReadDataSet(const String&, const TQueryParams& =TQueryParams(), TIBTransaction *Tr=0);
  virtual TDSPtr __fastcall GetWriteDataSet(const String&, const TQueryParams& =TQueryParams(), TIBTransaction *Tr=0);
  virtual TSQLPtr __fastcall GetReadSQL(const String&, bool Run, TIBTransaction *Tr=0);
  virtual TSQLPtr __fastcall GetWriteSQL(const String&, bool Run, TIBTransaction *Tr=0);
  virtual TEventMessage::Ptr __fastcall SetEventHandler(const TEventMessage::TEventList &L, TEventMessage::TEventAlert F) {return TEventMessage::Ptr(new TEventMessageImpl(L, F, Database));}
};
typedef TdmConnectImpl TConnectImpl;
//---------------------------------------------------------------------------
#endif
