//---------------------------------------------------------------------------

#pragma hdrstop

#include "Item.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Item::Array Item::Matrix::ToArray(int val) {
  Array res;
  for (int i=0; i<_dim; ++i) {
    res.push_back(val % _dim);
    val /= _dim;
  }

  return res;
}
//---------------------------------------------------------------------------

int Item::Matrix::ToInt(const Item::Array &array){
}
//---------------------------------------------------------------------------

void Item::Matrix::Multiply(const Elems &src, Elems &dst) const
{
}
//---------------------------------------------------------------------------

Item::Matrix::Matrix(int dim, int *data) : _dim(dim) {
  for (int i=0, size=dim*dim; i<size; ++i)
    _data.push_back(data[i]);
}
//---------------------------------------------------------------------------

