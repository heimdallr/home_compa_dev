//---------------------------------------------------------------------------
#include <iterator>
#include <numeric>
#pragma hdrstop

#include "Item.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Item::Array Item::Matrix::ToArray(int val) {
  Array res;
  for (int i=0; i<Dim; ++i) {
    res.push_back(val % Dim);
    val /= Dim;
  }
  return res;
}
//---------------------------------------------------------------------------

int Item::Matrix::ToInt(const Item::Array &array) {
  Array::const_reverse_iterator it = array.rbegin();
  int res = *it;
  for (++it; it!=array.rend(); ++it) {
    res *= array.size();
    res += *it;
  }
  return res;
}
//---------------------------------------------------------------------------

Item::Array Item::Matrix::Multiply(const Array &array) const {
  Array res;
  Array::const_iterator it = _data.begin();
  for (int i=0; i<Dim; ++i, it+=Dim)
    res.push_back(std::inner_product(array.begin(), array.end(), it, 0));
  return res;
}
//---------------------------------------------------------------------------

void Item::Matrix::Normalize(Arrays &arrays) {
// todo
}
//---------------------------------------------------------------------------

void Item::Matrix::Multiply(const Elems &src, Elems &dst) const
{
  Arrays arrays;
  for (Elems::const_iterator it = src.begin(); it != src.end(); ++it)
    arrays.push_back(Multiply(ToArray(*it)));
  Normalize(arrays);
  for (Arrays::const_iterator it=arrays.begin(); it!=arrays.end(); ++it)
    dst.insert(ToInt(*it));
}
//---------------------------------------------------------------------------

Item::Matrix::Matrix(const int *data) : _data(data, data + Dim*Dim) {
}
//---------------------------------------------------------------------------

std::ostream& Item::operator>>(std::ostream &stream) const {
  std::ostream_iterator<int> oit(stream, " ");
  for (Elems::const_iterator it = _elems.begin(); it != _elems.end(); ++it) {
    stream << "{ ";
    Array array(Matrix::ToArray(*it));
    std::copy(array.begin(), array.end(), oit);
    stream << "} ";
  }
  stream << std::endl;
  return stream;
}
//---------------------------------------------------------------------------

Item& Item::operator<<(int elem) {
  _elems.insert(elem);
  return *this;
}
//---------------------------------------------------------------------------

Item Item::Round(const Matrix &matrix) const {
  Item res;
  matrix.Multiply(_elems, res._elems);
  return res;
};
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
    0, 0, 0,
    0, 0, 0,
    0, 0, 1
  };
  static const Matrix matrix(array);
  return Round(matrix);
}
Item Item::RoundRight() const {
  static const int array[] = {
    0, 0, 0,
    0, 0, 0,
    0, 0, 1
  };
  static const Matrix matrix(array);
  return Round(matrix);
}
Item Item::RoundClockwise() const {
  static const int array[] = {
    0, 0, 0,
    0, 1, 0,
    0, 0, 0
  };
  static const Matrix matrix(array);
  return Round(matrix);
}
Item Item::RoundCounterClockwise() const {
  static const int array[] = {
    0, 0, 0,
    0, 1, 0,
    0, 0, 0
  };
  static const Matrix matrix(array);
  return Round(matrix);
}

