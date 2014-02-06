//---------------------------------------------------------------------------
#pragma hdrstop

#include "Matrix.h"
#include "Utils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Matrix::Matrix(const int *data) : _data(data, data + Dimensions*Dimensions) {
}
//---------------------------------------------------------------------------

Array Matrix::Multiply(const Array &array) const {
  Array res;
  Array::const_iterator it = _data.begin();
  for (int i=0; i<Dimensions; ++i, it+=Dimensions)
    res.push_back(std::inner_product(array.begin(), array.end(), it, 0));
  return res;
}
//---------------------------------------------------------------------------

void Matrix::Normalize(Arrays &arrays) {
  Array array(Dimensions, std::numeric_limits<int>::max());
  for (Arrays::const_iterator it = arrays.begin(); it != arrays.end(); ++it)
    for (int i=0; i<Dimensions; ++i)
      if (array[i] > (*it)[i])
        array[i] = (*it)[i];
  for (Arrays::iterator it = arrays.begin(); it != arrays.end(); ++it)
    for (int i=0; i<Dimensions; ++i)
      (*it)[i] -= array[i];
}
//---------------------------------------------------------------------------

void Matrix::Multiply(const Elems &src, Elems &dst) const
{
  Arrays arrays;
  for (Elems::const_iterator it = src.begin(); it != src.end(); ++it)
    arrays.push_back(Multiply(ToArray(*it)));
  Normalize(arrays);
  for (Arrays::const_iterator it=arrays.begin(); it!=arrays.end(); ++it)
    dst.insert(ToInt(*it));
}
//---------------------------------------------------------------------------

