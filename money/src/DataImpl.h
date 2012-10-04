#ifndef DataImplH
#define DataImplH
#include "Connect.h"
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
class TDataImpl {
protected:
  const String &_select_query;
  TQueryParams _param;
  TDSPtr _data;
  TConnect::TEventMessage::Ptr _event;
  TIBTransaction *_transaction;
  __fastcall TDataImpl(const String &SelectQuery, const String &EventName="", TIBTransaction *T=0);
  virtual void __fastcall OnEvent(TObject *Sender, AnsiString EventName, int EventCount, bool &CancelAlerts) {Load();}
public:
  TClientDataSet* __fastcall GetDataSet() const {return _data.get();}
  void __fastcall Load();
};
//---------------------------------------------------------------------------
#endif
