#ifndef ItemH
#define ItemH
//---------------------------------------------------------------------------
#include <set>
#include <vector>
#include <iostream>

#include "Matrix.h"
#include "Utils.h"
//---------------------------------------------------------------------------

// ����� �������
class Item {
public:
typedef std::vector<Item> Items;
typedef std::vector<Items> Storage;
typedef std::set<Item> UniqueItems;

private:
  int _id;      // ����� ��������
  Elems _elems; // ������ ��������
  Array _size;  // ������� �������� �� ������������

  // ��������� ����� ������� ���������� ������������ �� ��������� �������
  Item Round(const Matrix &matrix) const;
  // ��������� ����� ��������� ����������� �������� � ����� ��������� � ������������ ������������ ���������
  void FillItemRound(UniqueItems &items) const;
  // ��������� ������� �������� (������������� _size)
  void CountSize();

  // ������-������� ��� ��������� ����� �������� ��������� ���� �������� �������
  // ��� ��������� ���������, ����������� �� �����
  struct CheckFillItemMoves : public CheckBase {
    const Item &_item;
    Items &_items;
    // ��������� �������� ���� ������ � ���������
    CheckFillItemMoves(const Item &item, Items &items) : _item(item), _items(items) {}
    void Ready(const Array &array) {
      _items.push_back(_item.Move(array));
    }
  };

public:
  // �����������
  explicit Item(int id);
  // ����� ������� � �����
  std::ostream& operator>>(std::ostream &stream) const;
  // ��������� ����� � �������
  Item& operator<<(int elem);

  // ��������� ����� �������� ���������������
  // �����
  Item Move(const Array &offset) const;
  // ������ ��������
  Item RoundUp() const;
  Item RoundDown() const;
  Item RoundLeft() const;
  Item RoundRight() const;
  Item RoundClockwise() const;
  Item RoundCounterClockwise() const;
  // ��������� ��������� ����� ���������� ����������� �������� � ������
  void FillItems(Items &items) const;
  // ��������� ��������� ����� ���������� �������� �������� � ������
  void FillItemMoves(Items &items) const;
  // ����������� ���������
  bool Less(const Item &rh) const;
  // ��������� ������� �� ����������� �������� ��� � (�������� ��� �������) ���
  bool Check(const Array &cube) const;
  // �������������� (�������) ������� � ���
  void SetToCube(Array &cube, int n) const;
};
//---------------------------------------------------------------------------

// ����� ������� � �����
std::ostream& operator<<(std::ostream &stream, const Item &item) {
  return item >> stream;
}
//---------------------------------------------------------------------------

// ����������� ���������
bool operator<(const Item &lh, const Item &rh) {
  return lh.Less(rh);
}
//---------------------------------------------------------------------------
#endif
