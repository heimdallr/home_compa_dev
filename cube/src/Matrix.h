#ifndef MatrixH
#define MatrixH

#include "types.h"
//---------------------------------------------------------------------------

// матрица, используется для генерации новых фигур (вращением)
// работает не с элементом, а с множеством его точек
class Matrix {
  Array _data;  // данные

  // нормализация элемента
  static void Normalize(Arrays &arrays);
  // умножение на вектор
  Array Multiply(const Array &array) const;
public:
  // конструктор
  Matrix(const int *data);
  // умножение на множество точек
  void Multiply(const Elems &src, Elems &dst) const;
};

#endif
 