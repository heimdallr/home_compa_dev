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
struct CheckBase {
  // можно ли это использовать число в этой позиции (для ограничения перебора)?
  bool Check(int position, int value) const { return true; }
  // число в этой позиции будет использовано
  void Set(int position, int value, bool enabled) {}
  // один из результатов перебора (коллбек)
  void Ready(const Array &array) {}
};

// Шаблон, рекурсивно перебирает все допустимые значения в векторе.
// Принимает вектор с максимальными значениями
// и класс с методами, вызываемыми по разным событиям, см. выше
template<typename T>
void GetNext(const Array &maxval, T check) {
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

#endif
