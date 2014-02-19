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
struct CheckNext {
  // ����� �� ��� ������������ ����� � ���� ������� (��� ����������� ��������)?
  virtual bool Check(int position, int value) const { return true; }
  // ����� � ���� ������� ����� ������������
  virtual void Set(int position, int value, bool enabled) {}
  // ���� �� ����������� �������� (�������)
  virtual void Ready(const Array &array) {}
  virtual ~CheckNext() {}
};

// ���������� ���������� ��� ���������� �������� � �������.
// ��������� ������ � ������������� ����������
// � ����� � ��������, ����������� �� ������ ��������, ��. ����
void GetNext(const Array &maxval, CheckNext &check);
//---------------------------------------------------------------------------

#endif
