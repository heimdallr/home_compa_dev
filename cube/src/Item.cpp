//---------------------------------------------------------------------------
#pragma hdrstop

#include "Item.h"
#include "Utils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------

Item::Item(int id) : _id(id), _size(Dimensions, 0) {
}
//---------------------------------------------------------------------------

bool Item::Less(const Item &rh) const {
  return std::lexicographical_compare(_elems.begin(), _elems.end(), rh._elems.begin(), rh._elems.end());
}
//---------------------------------------------------------------------------

void Item::FillItemRound(UniqueItems &items) const {
  FillItemMoves(items);
  Item item = RoundClockwise();
  for (int i=0; i<3; ++i, item = item.RoundClockwise())
    item.FillItemMoves(items);
}
//---------------------------------------------------------------------------

void Item::FillItemMoves(UniqueItems &items) const {
  Array offset(Dimensions, 0), mx(Dimensions, 0);
  for (int i=0; i<Dimensions; ++i)
    mx[i] = Dimensions - _size[i];
  GetNext(mx, CheckFillItemMoves(*this, items));
}
//---------------------------------------------------------------------------

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

Item& Item::operator<<(int elem) {
  _elems.insert(elem);
  CountSize();
  return *this;
}
//---------------------------------------------------------------------------

Item Item::Round(const Matrix &matrix) const {
  Item res(_id);
  matrix.Multiply(_elems, res._elems);
  res.CountSize();
  return res;
};
//---------------------------------------------------------------------------

Item Item::Move(const Array &offset) const {
  Item res(_id);
  res._size = _size;
  for (Elems::const_iterator it = _elems.begin(); it != _elems.end(); ++it) {
    Array e = ToArray(*it);
    for (int i=0; i<Dimensions; ++i)
      e[i] += offset[i];
    res << ToInt(e);
  }
  return res;
}
//---------------------------------------------------------------------------

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

