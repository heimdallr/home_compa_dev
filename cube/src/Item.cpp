//---------------------------------------------------------------------------
#pragma hdrstop

#include "Item.h"
#include "Utils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------

//  онструктор
Item::Item(int id) : _id(id), _size(Dimensions, 0) {
}
//---------------------------------------------------------------------------

// сравнивалка элементов
bool Item::Less(const Item &rh) const {
  return std::lexicographical_compare(_elems.begin(), _elems.end(), rh._elems.begin(), rh._elems.end());
}
//---------------------------------------------------------------------------

// порождаем набор элементов посредством вращени€ в одной плоскости и всевозможных параллельных переносов
void Item::FillItemRound(UniqueItems &uitems) const {
  Items items;
  FillItemMoves(items);
  Item item = RoundClockwise();
  for (int i=0; i<3; ++i, item = item.RoundClockwise())
    item.FillItemMoves(items);
  std::copy(items.begin(), items.end(), std::inserter(uitems, uitems.end()));
}
//---------------------------------------------------------------------------

// заполн€ем контейнер всеми возможными сдвигами элемента в фигуре
void Item::FillItemMoves(Items &items) const {
  Array offset(Dimensions, 0), mx(Dimensions, 0);
  for (int i=0; i<Dimensions; ++i)
    mx[i] = Dimensions - _size[i];
  GetNext(mx, CheckFillItemMoves(*this, items));
}
//---------------------------------------------------------------------------

// заполн€ем контейнер всеми возможными положени€ми элемента в фигуре
void Item::FillItems(Items &items) const {
  UniqueItems u;
  FillItemRound(u);

  Item item = RoundLeft();
  for (int i=0; i<3; ++i, item = item.RoundLeft())
    item.FillItemRound(u);

  RoundUp().FillItemRound(u);
  RoundDown().FillItemRound(u);

  std::copy(u.begin(), u.end(), std::back_inserter(items));
}
//---------------------------------------------------------------------------

// ¬ычисл€ем размеры элемента
void Item::CountSize() {
  Array mn(Dimensions, std::numeric_limits<int>::max()), mx(Dimensions, std::numeric_limits<int>::min());
  for (Elems::const_iterator it = _elems.begin(); it != _elems.end(); ++it) {
    Array e = ToArray(*it);
    for (int i=0; i<Dimensions; ++i) {
      if (mn[i] > e[i])
        mn[i] = e[i];
      if (mx[i] < e[i])
        mx[i] = e[i];
    }
  }
  for (int i=0; i<Dimensions; ++i)
    _size[i] = mx[i] - mn[i];
}
//---------------------------------------------------------------------------

// добавл€ем точку в элемент
Item& Item::operator<<(int elem) {
  _elems.insert(elem);
  CountSize();
  return *this;
}
//---------------------------------------------------------------------------

// порождаем новый элемент умножением подэлементов на указанную матрицу
Item Item::Round(const Matrix &matrix) const {
  Item res(_id);
  matrix.Multiply(_elems, res._elems);
  res.CountSize();
  return res;
};
//---------------------------------------------------------------------------

// сдвиг
Item Item::Move(const Array &offset) const {
  Item res(_id);
  res._size = _size;
  ::Move(_elems, res._elems, offset);
  return res;
}
//---------------------------------------------------------------------------

// вс€кие вращени€, не все даже и нужны
Item Item::RoundUp() const {
  static const int array[] = {
    1,  0, 0,
    0,  0, 1,
    0, -1, 0
  };
  static const Matrix matrix(array);
  return Round(matrix);
}
Item Item::RoundDown() const {
  static const int array[] = {
    1, 0,  0,
    0, 0, -1,
    0, 1,  0
  };
  static const Matrix matrix(array);
  return Round(matrix);
}
Item Item::RoundLeft() const {
  static const int array[] = {
     0, 1, 0,
    -1, 0, 0,
     0, 0, 1
  };
  static const Matrix matrix(array);
  return Round(matrix);
}
Item Item::RoundRight() const {
  static const int array[] = {
    0, -1, 0,
    1,  0, 0,
    0,  0, 1
  };
  static const Matrix matrix(array);
  return Round(matrix);
}
Item Item::RoundClockwise() const {
  static const int array[] = {
    0,  0, 1,
    0,  1, 0,
    -1, 0, 0
  };
  static const Matrix matrix(array);
  return Round(matrix);
}
Item Item::RoundCounterClockwise() const {
  static const int array[] = {
    0, 0, -1,
    0, 1,  0,
    1, 0,  0
  };
  static const Matrix matrix(array);
  return Round(matrix);
}
//---------------------------------------------------------------------------

// пишем элемент в поток
std::ostream& Item::operator>>(std::ostream &stream) const {
  std::ostream_iterator<int> oit(stream, " ");
  stream << _id;
  for (Elems::const_iterator it = _elems.begin(); it != _elems.end(); ++it) {
    stream << ": { ";
    Array array(ToArray(*it));
    std::copy(array.begin(), array.end(), oit);
    stream << "} ";
  }
  stream << std::endl;
  return stream;
}
//---------------------------------------------------------------------------

// провер€ем элемент на возможность добавить его в (частично уже зан€тый) куб
bool Item::Check(const Array &cube) const {
  for (Elems::const_iterator it = _elems.begin(); it != _elems.end(); ++it)
    if (cube[*it])
      return false;
  return true;
}
//---------------------------------------------------------------------------

// добавдобавл€ем (удал€ем) элемент в куб
void Item::SetToCube(Array &cube, int n) const {
  for (Elems::const_iterator it = _elems.begin(); it != _elems.end(); ++it)
    cube[*it] = n;
}
//---------------------------------------------------------------------------

