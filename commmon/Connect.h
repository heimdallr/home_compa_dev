//---------------------------------------------------------------------------

#ifndef ConnectH
#define ConnectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <memory>
#include <list>
#include <DBClient.hpp>
#include <DBLocal.hpp>
#include <DBLocalI.hpp>
#include <IBSQL.hpp>
#include "utilcls.h"
#include "TransactionPtr.h"
#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
// Параметр запроса
class TQueryParam {
  const String      _name;
  const TFieldType  _type;
  const Variant     _val;
public:
  __fastcall TQueryParam(TFieldType Type, const String &Name, const Variant &Val) : _name(Name), _type(Type), _val(Val) {}
  __fastcall ~TQueryParam() {}
  const String&   __fastcall GetName() const {return _name;}
  TFieldType      __fastcall GetType() const {return _type;}
  const Variant&  __fastcall GetVal()  const {return _val;}
};
//---------------------------------------------------------------------------

// Набор параметров запроса
class TQueryParams {
  typedef std::list<TQueryParam> TQueryParamList;
  typedef TQueryParamList::const_iterator TQueryParamIt;
  TQueryParamList _param;
public:
  __fastcall TQueryParams() {}
  __fastcall TQueryParams(TFieldType Type, const String &Name, const Variant &Val) {Add(Type, Name, Val);}
  __fastcall ~TQueryParams() {}
  TQueryParams& __fastcall Add(TFieldType Type, const String &Name, const Variant &Val) {_param.push_back(TQueryParam(Type, Name, Val)); return *this;}
  void __fastcall SetParams(TIBClientDataSet *dsData) const {
    for(TQueryParamIt i=_param.begin(); i!=_param.end(); ++i)
      dsData->Params->CreateParam(i->GetType(), i->GetName(), ptInput)->Value = i->GetVal();
  }
  TQueryParams&  __fastcall Clear() {_param.clear(); return *this;}
};
//---------------------------------------------------------------------------

typedef std::auto_ptr<TClientDataSet> TDSPtr;
typedef std::auto_ptr<TIBSQL> TSQLPtr;
//---------------------------------------------------------------------------

// Коннект-пустышка
class TdmConnect : public TDataModule {
__published:	// IDE-managed Components
private:	// User declarations
protected:
  __fastcall TdmConnect() : TDataModule(static_cast<TComponent*>(0)) {}
public:		// User declarations
class TEventMessage {
public:
class TEventList {
typedef std::list<String> Impl;
  Impl _l;
  void __fastcall Init(const String &Str);
public:
  __fastcall TEventList(const String &Str) {Init(Str);}
  __fastcall TEventList(const char *Str) {Init(Str);}
  int __fastcall Fill(TStrings *S) const;
};
typedef void __fastcall (__closure *TEventAlert)(TObject *Sender, AnsiString EventName, int EventCount, bool &CancelAlerts);
typedef std::list<TEventAlert> TAlertList;
  __fastcall TEventMessage() {}
  virtual __fastcall ~TEventMessage() {}
  virtual const TStrings* __fastcall GetEvents() const {return 0;}
  typedef std::auto_ptr<TEventMessage> Ptr;
};

typedef boost::shared_ptr<TdmConnect> Ptr;
static TdmConnect* Instance;
static Ptr GetInstance() {return Ptr(Instance=new TdmConnect());}
  static void __fastcall Execute(TIBSQL*);
  virtual bool __fastcall IsActive() {return false;}
  virtual TDSPtr __fastcall GetReadDataSet(const String&, const TQueryParams& =TQueryParams(), TIBTransaction *Tr=0) {throw Exception("Connection lost");}
  virtual TDSPtr __fastcall GetWriteDataSet(const String&, const TQueryParams& =TQueryParams(), TIBTransaction *Tr=0) {throw Exception("Connection lost");}
  virtual TSQLPtr __fastcall GetReadSQL(const String&, bool Run, TIBTransaction *Tr=0) {throw Exception("Connection lost");}
  virtual TSQLPtr __fastcall GetWriteSQL(const String&, bool Run, TIBTransaction *Tr=0) {throw Exception("Connection lost");}
  virtual TEventMessage::Ptr __fastcall SetEventHandler(const TEventMessage::TEventList&, TEventMessage::TEventAlert) {return TEventMessage::Ptr(new TEventMessage());}
};
//---------------------------------------------------------------------------

typedef TdmConnect TConnect;

#endif
