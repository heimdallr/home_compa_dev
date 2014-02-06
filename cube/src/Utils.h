#ifndef UtilsH
#define UtilsH
#include "types.h"
//---------------------------------------------------------------------------

Array ToArray(int val);
int ToInt(const Array &array);

struct CheckBase {
  bool operator()(Array&) const {
    return true;
  }
  bool Check(int, int) const {
    return true;
  }
  void Insert(int, int) {}
  void Delete(int, int) {}
//  void Ready(const Array &array) {}
};
template<typename T>
void GetNext(const Array &maxval, T check) {
  Array array(maxval.size());
  Array s;
  int i = 0;
  while (true) {
beg:
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
      goto beg;
    }
    if (s.empty())
      return;

    i = s.back() + 1;
    s.pop_back();
  }
}
//---------------------------------------------------------------------------

#endif
