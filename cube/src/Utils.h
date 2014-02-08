#ifndef UtilsH
#define UtilsH
#include "types.h"
//---------------------------------------------------------------------------
// ��������������� �������

// �� ����� ������ ������
Array ToArray(int val);

// �� ������� ������ �����
int ToInt(const Array &array);

// ������� ����� ��������
void Move(const Elems &src, Elems &dst, const Array &offset);

// ������� ����� ��� �������-������� ����. ������ �� ������
struct CheckBase {
  // ����� �� ��� ������������ ����� � ���� ������� (��� ����������� ��������)?
  bool Check(int position, int value) const { return true; }
  // ����� � ���� ������� ����� ������������
  void Set(int position, int value, bool enabled) {}
  // ���� �� ����������� �������� (�������)
  void Ready(const Array &array) {}
};

// ������, ���������� ���������� ��� ���������� �������� � �������.
// ��������� ������ � ������������� ����������
// � ����� � ��������, ����������� �� ������ ��������, ��. ����
template<typename T>
void GetNext(const Array &maxval, T check) {
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

#endif
