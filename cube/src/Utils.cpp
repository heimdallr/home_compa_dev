#include "Utils.h"

Array ToArray(int val) {
  Array res;
  for (int i=0; i<Dimensions; ++i) {
    res.push_back(val % BoxSize);
    val /= BoxSize;
  }
  return res;
}
//---------------------------------------------------------------------------

int ToInt(const Array &array) {
  Array::const_reverse_iterator it = array.rbegin();
  int res = *it;
  for (++it; it!=array.rend(); ++it) {
    res *= BoxSize;
    res += *it;
  }
  return res;
}
//---------------------------------------------------------------------------

// Двигаем точки элемента
void Move(const Elems &src, Elems &dst, const Array &offset) {
  for (Elems::const_iterator it = src.begin(); it != src.end(); ++it) {
    Array e = ToArray(*it);
    for (int i=0; i<Dimensions; ++i)
      e[i] += offset[i];
    dst.insert(ToInt(e));
  }
}
//---------------------------------------------------------------------------

