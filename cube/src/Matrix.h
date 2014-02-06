#ifndef MatrixH
#define MatrixH

#include "types.h"
//---------------------------------------------------------------------------
class Matrix {
  Array _data;

  static void Normalize(Arrays &arrays);
  Array Multiply(const Array &array) const;
public:
  Matrix(const int *data);
  void Multiply(const Elems &src, Elems &dst) const;
};

#endif
 