//---------------------------------------------------------------------------
#pragma hdrstop

//---------------------------------------------------------------------------

#include "Item.h"

#pragma argsused

class CheckStack {
  std::vector<int> _cube;
  const Item::Storage &_storage;
  Arrays &_res;
public:
  CheckStack(const Item::Storage &storage, Arrays &res) : _cube(BoxSize*BoxSize*BoxSize, 0), _storage(storage), _res(res) {
  }
  bool Check(int figure, int position) const {
    return _storage[figure][position].Check(_cube);
  }
  void Set(int figure, int position, bool enabled) {
    _storage[figure][position].SetToCube(_cube, (enabled? 1: 0));
  }
  void Ready(const Array &array) {
    _res.push_back(array);
    std::copy(array.begin(), array.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
  }
};

int main(int argc, char* argv[])
{
  Item::Items items;

  // ������ ����� �����
  items.push_back(Item(1)); items.back() << 0 << 1 << 2 << 3;
  items.push_back(Item(2)); items.back() << 0 << 1 << 3;
  items.push_back(Item(3)); items.back() << 0 << 1 << 2 << 4;
  items.push_back(Item(4)); items.back() << 0 << 1 << 4 << 5;
  items.push_back(Item(5)); items.back() << 0 << 1 << 3 << 9;
  items.push_back(Item(6)); items.back() << 0 << 1 << 3 << 10;
  items.push_back(Item(7)); items.back() << 0 << 1 << 3 << 12;

  // ��������� ��� ���� ��������� ��������� ���� ����� ������ ����
  Item::Storage storage;
  {
    // ������ ������ ������������ � ��������� ��� ��������, ����� �� �������
    // �� ����������� ���������� (���������� ��������� ���� �� �����) �������
    // ��������! ������ ������ �� ������ ���� ������������!
    Item::Items::const_iterator it = items.begin();
    storage.push_back();
    it->FillItemMoves(storage.back());
    // ��������� ������ - �� ������ ���������, � ����������
    for (++it; it != items.end(); ++it) {
      storage.push_back();
      it->FillItems(storage.back());
    }
  }

  // ������� ���������
  for (Item::Storage::const_iterator it = storage.begin(); it != storage.end(); ++it) {
    std::copy(it->begin(), it->end(), std::ostream_iterator<const Item>(std::cout));
    std::cout << it->size() << std::endl;
  }

  // ����������. ������� �������� � ��������� �� �������
  Array mx;
  for (Item::Storage::const_iterator it = storage.begin(); it != storage.end(); ++it)
    mx.push_back(it->size());

  // �������
  Arrays res;
  GetNext(mx, CheckStack(storage, res));

  // ������� ���������
  for (int i=0, size_i=res.size(); i<size_i; ++i) {
    // �������������� ���������, ����� ������� ����������
    Item::UniqueItems uitems;
    for (int j=0, size_j=storage.size(); j<size_j; ++j)
      uitems.insert(storage[j][res[i][j]]);
    std::cout << i << std::endl;
    std::copy(uitems.begin(), uitems.end(), std::ostream_iterator<const Item>(std::cout));
  }

  return 0;
}
//---------------------------------------------------------------------------

