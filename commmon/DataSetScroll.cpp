//---------------------------------------------------------------------------
#include <vcl.h>
#include <algorithm>
#include <function>
#pragma hdrstop

#include "DataSetScroll.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TdmDataSetScroll::TdmDataSetScroll(TConnect *Con) : TDataModule(static_cast<TComponent*>(0)), _con(Con) {
  Timer->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TdmDataSetScroll::TimerTimer(TObject *Sender) {
  std::for_each(_data.begin(), _data.end(), std::bind2nd(std::mem_fun(&TDataSetScroller::Run), _con));
}
//---------------------------------------------------------------------------

void TdmDataSetScroll::TDataSetScroller::Run(TConnect *Con) {
  if(!(_data->Active && _data->RecordCount)) {
    std::for_each(_children.begin(), _children.end(), std::mem_fun(&TDataSetOpener::Close));
    return;
  }
  if(_count<0) return;
  if(--_count) return;
  std::for_each(_children.begin(), _children.end(), std::bind2nd(std::mem_fun(&TDataSetOpener::Open), _data->FieldByName(_id_field_name)->AsInteger));
}
//---------------------------------------------------------------------------

void __fastcall TdmDataSetScroll::UpdateForce() {
  std::for_each(_data.begin(), _data.end(), std::bind2nd(std::mem_fun(&TDataSetScroller::RunForce), _con));
}
//---------------------------------------------------------------------------

void TdmDataSetScroll::TDataSetScroller::RunForce(TConnect *Con) {
  if(!(_data->Active && _data->RecordCount)) {
    std::for_each(_children.begin(), _children.end(), std::mem_fun(&TDataSetOpener::Close));
    return;
  }
  std::for_each(_children.begin(), _children.end(), std::bind2nd(std::mem_fun(&TDataSetOpener::Open), _data->FieldByName(_id_field_name)->AsInteger));
}
//---------------------------------------------------------------------------


