//---------------------------------------------------------------------------


#pragma hdrstop

#include "DataImpl.h"
#include "DataSetLayout.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

__fastcall TDataImpl::TDataImpl(const String &SelectQuery, const String &EventName, TIBTransaction *T) :
_select_query(SelectQuery),
_data(new TClientDataSet(0)),
_event(TConnect::Instance->SetEventHandler(EventName, OnEvent)),
_transaction(T)
{
}
//---------------------------------------------------------------------------

void __fastcall TDataImpl::Load() {
  TDataSetLayout DS(_data.get());
  _data->Data = TConnect::Instance->GetReadDataSet(_select_query, _param, _transaction)->Data;
}
//---------------------------------------------------------------------------
