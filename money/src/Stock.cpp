#pragma hdrstop
#include "Stock.h"
#include "Const.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------

const String TStock::SelectQuery="select * from sel_stock";
//---------------------------------------------------------------------------

__fastcall TStock::TStock() : TDataImpl(SelectQuery, String().sprintf("stock;catalog_%d", TConst::Instance()->Get("deposit")->AsInteger)) {
  Load();
  _data->IndexFieldNames="ord_num";
}
//---------------------------------------------------------------------------

