#include <DBClient.hpp>
#pragma hdrstop
#include <queue>
#include "DataSetLayout.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall TDataSetLayout::TDataSetLayout(TDataSet *Data, const String &IdName) :_data(Data), _id_name(IdName), _id_val(0), _rec_no(0), _active(false) {
  if(!(_data && static_cast<int>(_active=_data->Active))) return;
//  _data->DisableControls();
  _id_val = _data->FieldByName(_id_name)->Value;
  _rec_no = _data->RecNo;
}
//---------------------------------------------------------------------------

__fastcall TDataSetLayout::~TDataSetLayout() {
  if(!(_data && _data->Active)) return;
  if(!_data->Locate(_id_name, _id_val, TLocateOptions()<<loCaseInsensitive)) {
    if(!_rec_no) _data->First();
    else
    try {
      _data->RecNo = _rec_no;
    } catch(...) {
      try {
        _data->RecNo = _rec_no-1;
      } catch(...) {
        _data->First();
      }
    }
  }
//  _data->EnableControls();
}
//---------------------------------------------------------------------------

// Расставляем галки вниз по дереву
int __fastcall SetChecked(TClientDataSet *DSData, const String &FlagFieldName, const String &IdFieldName, int Id, int Checked) {
  if(!DSData->Locate(IdFieldName, Id, TLocateOptions())) return Checked;
  DSData->Edit();
  DSData->FieldByName(FlagFieldName)->AsInteger = Checked;
  DSData->Post();
  return Checked;
}
void __fastcall SetChecked(TMemTableEh *Data, TClientDataSet *DSData, const String &FlagFieldName, const String &IdFieldName, const String &IdParentFieldName) {
  TDataSetLayout DSL(Data);
  TDataSetFilter<TMemTableEh> DSF(Data);
  TPostPtr<TMemTableEh> PP(Data);
  int Checked = SetChecked(DSData, FlagFieldName, IdFieldName, Data->FieldByName(IdFieldName)->AsInteger, Data->FieldByName(FlagFieldName)->AsInteger);
  std::queue<int> S;
  if(Data->TreeNode->NodeHasChildren)
    S.push(Data->FieldByName(IdFieldName)->AsInteger);
  while(!S.empty()) {
    int Id=S.front();
    S.pop();
    if(!Data->TreeNode->NodeExpanded) Data->TreeNode->NodeExpanded = true;
    TDataSetFilter<TMemTableEh>::Filter(Data, String().sprintf("%s=%d", IdParentFieldName, Id));
    for(Data->First(); !Data->Eof; Data->Next()) {
      if(Data->FieldByName(FlagFieldName)->AsInteger == Checked || Data->FieldByName(IdParentFieldName)->AsInteger!=Id) continue;
      if(Data->TreeNode->NodeHasChildren)
        S.push(Data->FieldByName(IdFieldName)->AsInteger);
      Data->Edit();
      Data->FieldByName(FlagFieldName)->AsInteger = SetChecked(DSData, FlagFieldName, IdFieldName, Data->FieldByName(IdFieldName)->AsInteger, Checked);
      Data->Post();
    }
  }
}
//---------------------------------------------------------------------------

