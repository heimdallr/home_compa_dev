#ifndef GridUtilsH
#define GridUtilsH
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include <DBClient.hpp>
#include <list>
#include <set>
//---------------------------------------------------------------------------
namespace ns_GridUtils {
enum ELeftRight {
  ELeft=0,
  ERight
};
class TPosKeeper {
  TClientDataSet *_data;
  String _id_field;
  Variant _id_value;
public:
  __fastcall TPosKeeper(TClientDataSet *data) : _data(data) {
    for(int i=0; i<_data->Fields->Count; ++i)
      if(_data->Fields->Fields[i]->FieldName.LowerCase().Pos("id")==1) {
        _id_field = _data->Fields->Fields[i]->FieldName;
        _id_value = _data->Fields->Fields[i]->Value;
        return;
      }
  }
  __fastcall ~TPosKeeper() {
    if(!_id_field.IsEmpty())
      _data->Locate(_id_field, _id_value, TLocateOptions());
  }
};

// Вспомогательный класс
class TSortFld {
typedef std::list<String> TFldList;
typedef std::set<String> TFldSet;
  TFldList _fld;
  TFldSet _fld_set;
  String _str;
  void __fastcall Init(const String &Str, char Delimiter);
public:
  __fastcall TSortFld() {}
  __fastcall TSortFld(const String &Str, char Delimiter=';') {Init(Str, Delimiter);}
  __fastcall TSortFld(const char *Str, char Delimiter=';') {Init(Str, Delimiter);}
  TSortFld& __fastcall Add(const String &Fld);
  TSortFld& __fastcall Add(const TSortFld &Src, const TSortFld &Excp=TSortFld());
  bool __fastcall Empty() const {return _fld.empty();}
  operator const String&() const {return _str;}
};
//---------------------------------------------------------------------------

// Функции сортировки
void __fastcall Sort(TObject *Sender, TColumnEh *Column, const TSortFld &FldLast=TSortFld(), const TSortFld &FldDesc=TSortFld(), const TSortFld &FldFirst=TSortFld());
void __fastcall Sort(TClientDataSet *Data, const TSortFld &S=TSortFld(), const TSortFld &D=TSortFld());
// Ищем колонку в гриде по имени поля
TColumnEh* __fastcall FindColumn(TDBGridEh *Grid, const String &FieldName, bool Required=true);
// Нажали влево
void __fastcall LeftExecute(TObject *Sender, TControl *ActiveControl);
// Нажали вправо
void __fastcall RightExecute(TObject *Sender, TControl *ActiveControl);
// Красим строки
void __fastcall DataGetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont, TColor &Background, TGridDrawState State);
void __fastcall DataDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol, TColumnEh *Column, TGridDrawState State);
//---------------------------------------------------------------------------
} // namespace ns_GridUtils
#endif
