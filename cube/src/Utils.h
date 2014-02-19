#ifndef UtilsH
#define UtilsH
#include "types.h"
//---------------------------------------------------------------------------
// Вспомогательные функции

// Из числа делаем массив
Array ToArray(int val);

// Из массива делаем число
int ToInt(const Array &array);

// Двигаем точки элемента
void Move(const Elems &src, Elems &dst, const Array &offset);

// Простой класс для функции-шаблона ниже. Ничего не делает
struct CheckNext {
  // можно ли это использовать число в этой позиции (для ограничения перебора)?
  virtual bool Check(int position, int value) const { return true; }
  // число в этой позиции будет использовано
  virtual void Set(int position, int value, bool enabled) {}
  // один из результатов перебора (коллбек)
  virtual void Ready(const Array &array) {}
  virtual ~CheckNext() {}
};

// Рекурсивно перебирает все допустимые значения в векторе.
// Принимает вектор с максимальными значениями
// и класс с методами, вызываемыми по разным событиям, см. выше
void GetNext(const Array &maxval, CheckNext &check);
//---------------------------------------------------------------------------

#endif
