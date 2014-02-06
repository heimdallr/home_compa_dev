//---------------------------------------------------------------------------

#pragma hdrstop

#include "Utils.h"
#include "Utils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

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
/*
template<typename Check>
void GetNext(const Array &maxval, Check check) {
  Array array;
  Array s;
  int i = 0;
  while (true) {
    for (; i<maxval[s.size()]; ++i) {
      if (!check.Check(s.size(), i))
        continue;

      check.Insert(s.size(), i);
      s.push_back(i);
      if (s.size() == maxval.size()) {
        std::copy(s.begin(), s.end(), array.begin());
        check.Ready(array);
        s.pop_back();
        check.Delete(s.size(), i);
        continue;
      }
      i = 0;
      break;
    }
    if (s.empty())
      return;

    i = s.back() + 1;
    s.pop_back();
  }
}
//---------------------------------------------------------------------------

*/