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

void GetNext(const Array &maxval, CheckNext &check) {
  // стек, для организации рекурсии
  Array s;
  s.reserve(maxval.size());
  int i = 0;
  while (true) {
    // бежим по элементам одной позиции (кандидиатам на помещение в стек)
    for (; i<maxval[s.size()]; ++i) {
      // элемент не подходит - бежим дальше
      if (!check.Check(s.size(), i))
        continue;

      // элемент подходит - в стек его
      check.Set(s.size(), i, true);
      s.push_back(i);

      // особый случай - стек заполнен
      if (s.size() == maxval.size()) {
        // сообщаем о найденном переборе
        check.Ready(s);
        // идём дальше по младшей позиции
        s.pop_back();
        check.Set(s.size(), i, false);
        continue;
      }
      // бежим с начала по следующей позиции
      i = -1;
    }
    // пробежали по всем элементам позиции
    // это была старшая позиция - выходим
    if (s.empty())
      return;

    // продолжаем бежать по предыдущей позиции
    i = s.back() + 1;
    s.pop_back();
    check.Set(s.size(), i - 1, false);
  }
}
//---------------------------------------------------------------------------
