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

// ������� ����� ��������
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
  // ����, ��� ����������� ��������
  Array s;
  s.reserve(maxval.size());
  int i = 0;
  while (true) {
    // ����� �� ��������� ����� ������� (����������� �� ��������� � ����)
    for (; i<maxval[s.size()]; ++i) {
      // ������� �� �������� - ����� ������
      if (!check.Check(s.size(), i))
        continue;

      // ������� �������� - � ���� ���
      check.Set(s.size(), i, true);
      s.push_back(i);

      // ������ ������ - ���� ��������
      if (s.size() == maxval.size()) {
        // �������� � ��������� ��������
        check.Ready(s);
        // ��� ������ �� ������� �������
        s.pop_back();
        check.Set(s.size(), i, false);
        continue;
      }
      // ����� � ������ �� ��������� �������
      i = -1;
    }
    // ��������� �� ���� ��������� �������
    // ��� ���� ������� ������� - �������
    if (s.empty())
      return;

    // ���������� ������ �� ���������� �������
    i = s.back() + 1;
    s.pop_back();
    check.Set(s.size(), i - 1, false);
  }
}
//---------------------------------------------------------------------------
