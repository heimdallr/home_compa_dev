//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <algorithm>
#include <function>
#include "ConnectImpl.h"
#include "ConnectPtr.h"
#include "TransactionPtr.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Connect"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

// Фабрика
TConnect::Ptr TdmConnectImpl::GetInstance(const TPropertyMap &Prop) {
  return Ptr(Instance = new TdmConnectImpl(Prop));
}
//---------------------------------------------------------------------------

// Подписка/отписка на события
__fastcall TdmConnectImpl::TEventMessageImpl::TEventMessageImpl(const TEventList &EventList, TEventAlert F, TIBDatabase *DB) :
TEventMessage(),
_event(new TIBEvents(0))
{
  _event->Database = DB;
  _event->OnEventAlert = F;
  if(EventList.Fill(_event->Events))
    _event->RegisterEvents();
}
__fastcall TdmConnectImpl::TEventMessageImpl::~TEventMessageImpl() {
  try {
    if(_event->Registered)
      _event->UnRegisterEvents();
  } catch(...) {}
}
//---------------------------------------------------------------------------

// Конструктор, коннект
__fastcall TdmConnectImpl::TdmConnectImpl(const TPropertyMap &Prop) : TdmConnect() {
  String H=Prop["Host"];
  Database->DatabaseName = String().sprintf("%s%s%s", H.c_str(), (H.IsEmpty()?"":":"), Prop["DatabaseName"].c_str());
  Database->Params->Add("user_name="+Prop["User"]);
  Database->Params->Add("password="+Prop["Password"]);
  Database->Params->Add("lc_ctype="+Prop["CType"]);
  if(!Prop["Role"].IsEmpty())
    Database->Params->Add("sql_role_name="+Prop["Role"]);
  Database->Open();
  trRead->StartTransaction();
}
//---------------------------------------------------------------------------

// Деструктор, дисконнект
void __fastcall TdmConnectImpl::DataModuleDestroy(TObject *Sender) {
  try {
    if(trRead->Active) trRead->Commit();
    if(Database->Connected) Database->ForceClose();
  } catch(...) {}
}
//---------------------------------------------------------------------------

// Проверяем наличие коннекта
bool __fastcall TdmConnectImpl::IsActive() {
  try {
    GetReadSQL("select 42 from rdb$database", true);
    return true;
  } catch(...) {}
  return false;
}
//---------------------------------------------------------------------------

// Тянем читающий датасет из базы
TDSPtr __fastcall TdmConnectImpl::GetReadDataSet(const String &Query, const TQueryParams &Param, TIBTransaction *T) {
  TCOMCriticalSection::Lock Lock(_lock);
  dsRead->DBTransaction = T ? T : trRead;
  dsRead->Params->Clear();
  dsRead->CommandText = Query;
  Param.SetParams(dsRead);
  TOpenPtr<TIBClientDataSet> dsReadOpen(dsRead);
  TDSPtr Res(new TClientDataSet(0));
  Res->Data = dsRead->Data;
  Res->First();
  return Res;
}
//---------------------------------------------------------------------------

// Тянем читающий TIBSQL
TSQLPtr __fastcall TdmConnectImpl::GetReadSQL(const String &Query, bool Run, TIBTransaction *T) {
  TSQLPtr Res(new TIBSQL(0));
  Res->Database = Database;
  Res->Transaction = T ? T : trRead;
  Res->SQL->Text = Query;
  if(Run) Res->ExecQuery();
  return Res;
}
//---------------------------------------------------------------------------

// Тянем пишущий датасет из базы
TDSPtr __fastcall TdmConnectImpl::GetWriteDataSet(const String &Query, const TQueryParams &Param, TIBTransaction *T) {
  TCOMCriticalSection::Lock Lock(_lock);
  dsWrite->DBTransaction = T ? T : trWrite;
  TTranPtr TP(dsWrite->DBTransaction);
  dsWrite->Params->Clear();
  dsWrite->CommandText = Query;
  Param.SetParams(dsWrite);
  TOpenPtr<TIBClientDataSet> dsWriteOpen(dsWrite);
  dsWrite->DBTransaction->Commit();
  TDSPtr Res(new TClientDataSet(0));
  Res->Data = dsWrite->Data;
  Res->First();
  return Res;
}
//---------------------------------------------------------------------------

// Тянем пишущий TIBSQL
TSQLPtr __fastcall TdmConnectImpl::GetWriteSQL(const String &Query, bool Run, TIBTransaction *T) {
  TCOMCriticalSection::Lock Lock(_lock);
  TSQLPtr Res(new TIBSQL(0));
  Res->Database = Database;
  if(T) Res->Transaction = T;
  else {
    Res->Transaction = new TIBTransaction(Res.get());
    Res->Transaction->DefaultDatabase = Database;
  }
  Res->SQL->Text = Query;
  if(Run) {
    if(!Res->Transaction->Active) Res->Transaction->StartTransaction();
    try {
      Res->ExecQuery();
      Res->Transaction->Commit();
    } catch(...) {
      Res->Transaction->Rollback();
      throw;
    }
  }
  return Res;
}
//---------------------------------------------------------------------------


