//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Connection.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

// Конструктор
__fastcall TdmConnect::TdmConnect(const String &strHost, const String &strBase, const String &strUser, const String &strPassword) : TDataModule(Application->MainForm) {
  Database->DatabaseName = strHost.IsEmpty() ? strHost+":"+strBase : strBase;
  Database->Params->Clear();
  Database->Params->Add(String().sprintf("user_name=%s", strUser));
  Database->Params->Add(String().sprintf("password=%s", strPassword));
  if(!strHost.IsEmpty())
    Database->Params->Add("lc_ctype=WIN1251");
  Database->Open();
  trRead->StartTransaction();
}
//---------------------------------------------------------------------------

// Деструктор
void __fastcall TdmConnect::DataModuleDestroy(TObject *Sender) {
  try {
    if(trRead->Active) trRead->Commit();
    if(Database->Connected) Database->ForceClose();
  } catch(...) {}
}
//---------------------------------------------------------------------------

// Возвращаем датасет
TClientDataSet* __fastcall TdmConnect::DataSetExec(TIBSQL *SQL) {
  Query->Close();
  Query->SQL->Text = SQL->SQL->Text;
  Query->Open();

  // создаем поля датасета
  TClientDataSet *Res = new TClientDataSet(0);
  TFieldDefs *pDefs=Res->FieldDefs;
  for(int i=0; i<Query->FieldCount; ++i) {
    TField *Field=Query->Fields->Fields[i];
    TFieldDef *pDef=pDefs->AddFieldDef();
    pDef->Name      = Field->FieldName;
    pDef->DataType  = Field->DataType;
    pDef->Size      = Field->Size;
  }
  Query->Close();

  // тянем данные
  Res->CreateDataSet();
  Res->LogChanges = false;
  for(SQL->ExecQuery(); !SQL->Eof; SQL->Next()) {
    Res->Append();
    for(int i=0; i<Res->FieldCount; ++i)
      Res->Fields->Fields[i]->Value = SQL->Fields[i]->Value;
    Res->Post();
  }
  SQL->Close();
  Res->First();
  return Res;
}
//---------------------------------------------------------------------------

// Возвращаем читающий sql
TSQLPtr __fastcall TdmConnect::GetReadSQL(const String &strQuery) {
  TSQLPtr SQL(new TIBSQL(0));
  SQL->Database = Database;
  SQL->Transaction = trRead;
  SQL->SQL->Text = strQuery;
  return SQL;
}
//---------------------------------------------------------------------------

// Возвращаем пишущий sql
TSQLPtr __fastcall TdmConnect::GetWriteSQL(const String &strQuery, TIBTransaction *T) {
  TSQLPtr SQL(new TIBSQL(0));
  SQL->Database = Database;
  SQL->SQL->Text = strQuery;
  if(T) SQL->Transaction = T;
  else {
    SQL->Transaction = new TIBTransaction(SQL.get());
    SQL->Transaction->DefaultDatabase = Database;
    SQL->Transaction->Params->Add("read_committed");
    SQL->Transaction->Params->Add("rec_version");
    SQL->Transaction->Params->Add("nowait");
  }
  return SQL;
}
//---------------------------------------------------------------------------

// Словили событие, оповещаем подписчиков
void __fastcall TdmConnect::EventsEventAlert(TObject *Sender, AnsiString EventName, int EventCount, bool &CancelAlerts) {
  for(TEventIt j=_event.lower_bound(EventName); j!=_event.upper_bound(EventName); ++j)
    j->second(Sender, EventName, EventCount, CancelAlerts);
}
//---------------------------------------------------------------------------

// Рестарт подписчика с новым набором событий-подписчиков
void __fastcall TdmConnect::ResetEvents() {
  TStrList events;
  for(TEventIt j=_event.begin(); j!=_event.end(); ++j)
    events.push_back(j->first);
  events.unique();
  if(Events->Registered) Events->UnRegisterEvents();
  Events->Events->Clear();
  for(TStrIt i=events.begin(); i!=events.end(); ++i)
    Events->Events->Add(*i);
  if(Events->Events->Count)
    Events->RegisterEvents();
}
//---------------------------------------------------------------------------

// Подписываемся на набор событий
void __fastcall TdmConnect::RegisterEvent(TEventAlert Alert, const TStrList &EventName) {
  for(TStrIt i=EventName.begin(); i!=EventName.end(); ++i) {
    try {
      for(TEventIt j=_event.lower_bound(*i); j!=_event.upper_bound(*i); ++j)
        if(j->second==Alert)
          throw Exception("");
      _event.insert(std::make_pair(*i, Alert));
    }
    catch(Exception&) {}
  }
  ResetEvents();
}
//---------------------------------------------------------------------------

// Отписываемся от набора событий
void __fastcall TdmConnect::UnRegisterEvent(TEventAlert Alert, const TStrList &EventName) {
  std::list<TEventIt> EventList;
  for(TStrIt i=EventName.begin(); i!=EventName.end(); ++i)
    for(TEventIt j=_event.lower_bound(*i); j!=_event.upper_bound(*i); ++j)
      if(j->second==Alert)
        EventList.push_back(j);
  for(std::list<TEventIt>::const_iterator i=EventList.begin(); i!=EventList.end(); ++i)
    _event.erase(*i);
  ResetEvents();
}
//---------------------------------------------------------------------------

