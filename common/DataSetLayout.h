//---------------------------------------------------------------------------

#ifndef DataSetLayoutH
#define DataSetLayoutH
#include <DB.hpp>
#include "MemTableEh.hpp"
//---------------------------------------------------------------------------

// Храним позицию в датасете
class TDataSetLayout {
  TDataSet *_data;
  String _id_name;
  Variant _id_val;
  int _rec_no;
  bool _active;
public:
  __fastcall TDataSetLayout(TDataSet *Data, const String &IdName="id");
  __fastcall ~TDataSetLayout();
};
//---------------------------------------------------------------------------

// Храним фильтр
template <typename T>
class TDataSetFilter {
  T *_data;
  const String _filter;
public:
static T* __fastcall Filter(T *Data, const String &Filter=String()) {
  Data->Filtered = false;
  Data->Filter = Filter;
  Data->Filtered = !Filter.IsEmpty();
  return Data;
}
  __fastcall TDataSetFilter(T *Data, const String &Filter=String())  : _data(Data), _filter(_data->Filter) {TDataSetFilter::Filter(_data, Filter);}
  __fastcall ~TDataSetFilter() {TDataSetFilter::Filter(_data, _filter);}
};
//---------------------------------------------------------------------------

// Храним BeforePost, AfterPost
template <typename T>
class TPostPtr {
  T *_p;
  TDataSetNotifyEvent _b, _a;
public:
  __fastcall TPostPtr(T *P, TDataSetNotifyEvent A=0, TDataSetNotifyEvent B=0) : _p(P), _b(P->BeforePost), _a(P->AfterPost) {_p->BeforePost=B; _p->AfterPost=A;}
  __fastcall ~TPostPtr() {_p->BeforePost=_b; _p->AfterPost=_a;}
};
//---------------------------------------------------------------------------

// Расставляем галки вниз по дереву
void __fastcall SetChecked(TMemTableEh *Data, TClientDataSet *DSData, const String &FlagFieldName="checked", const String &IdFieldName="id", const String &IdParentFieldName="id_p");
//---------------------------------------------------------------------------

#endif
