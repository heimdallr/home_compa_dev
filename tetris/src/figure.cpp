//---------------------------------------------------------------------------
#include <stdlib>
#pragma hdrstop
#include "figure.h"
//---------------------------------------------------------------------------

// Конструктор фигуры
__fastcall TFigure::TFigure(int id, const TPos &pos, const TPosList &items) : _id(id), _pos(pos), _items(items) {
}
//---------------------------------------------------------------------------

// Деструктор
__fastcall TFigure::~TFigure() {
}
//---------------------------------------------------------------------------

// Крутим фигуру
void __fastcall TFigure::Rotate(int dir) {
  int min=0, sum=0;
  for(TPosList::iterator i=_items.begin(); i!=_items.end(); ++i) {
    sum += i->second;
    *i = TPos(dir*i->second, -dir*i->first);
    if(min>i->first) min=i->first;
    sum -= i->second;
  }
  _pos.second += sum/static_cast<signed int>(_items.size());
  for(TPosList::iterator i=_items.begin(); i!=_items.end(); ++i) {
    i->first -= min;
  }
}
//---------------------------------------------------------------------------

// Ищем в фигуре присланный элементик
bool __fastcall TFigure::Exists(const TPos &pos, const TPos &item) {
  for(TPosIt i=_items.begin(); i!=_items.end(); ++i)
    if(_pos.first+i->first==pos.first+item.first && _pos.second+i->second==pos.second+item.second) return true;
  return false;
}
//---------------------------------------------------------------------------

// Особое поведение для пробивной фигуры
bool __fastcall TFigureCrash::OnBottom(int size, TItem **data, int &count) {
  for(TPosIt i=_items.begin(); i!=_items.end(); ++i)
    if(_pos.first+i->first==size) {
      for(TPosIt j=_items.begin(); j!=_items.end(); ++j)
        data[_pos.second+j->second][_pos.first+j->first].first = false;
      return false;
    }
  for(TPosIt i=_items.begin(); i!=_items.end(); ++i)
    if(data[_pos.second+i->second][_pos.first+i->first+1].first && !Exists(_pos, TPos(_pos.first+i->first+1, _pos.second+i->second))) {
      data[_pos.second+i->second][_pos.first+i->first+1].first = false;
      ++count;
    }
  return true;
}
//---------------------------------------------------------------------------

