#ifndef ItemH
#define ItemH
//---------------------------------------------------------------------------
#include <set>
#include <vector>
#include <iostream>

#include "Matrix.h"
#include "Utils.h"
//---------------------------------------------------------------------------

class Item {
typedef std::set<Item> UniqueItems;
  int _id;
  Elems _elems;
  Array _size;

  Item Round(const Matrix &matrix) const;
  void FillItemRound(UniqueItems &items) const;
  void FillItemMoves(UniqueItems &items) const;
  void CountSize();
  static bool True(const Array&) {return true;}

  struct CheckFillItemMoves : public CheckBase {
    const Item &_item;
    UniqueItems &_items;
    CheckFillItemMoves(const Item &item, UniqueItems &items) : _item(item), _items(items) {}
    void Ready(const Array &array) {
      _items.insert(_item.Move(array));
    }
  };

public:
typedef std::vector<Item> Items;
  explicit Item(int id);
  std::ostream& operator>>(std::ostream &stream) const;
  Item& operator<<(int elem);
  Item Move(const Array &offset) const;
  Item RoundUp() const;
  Item RoundDown() const;
  Item RoundLeft() const;
  Item RoundRight() const;
  Item RoundClockwise() const;
  Item RoundCounterClockwise() const;
  void FillItems(Items &items) const;
  bool Less(const Item &rh) const;
};

std::ostream& operator<<(std::ostream &stream, const Item &item) {
  return item >> stream;
}

bool operator<(const Item &lh, const Item &rh) {
  return lh.Less(rh);
}


//---------------------------------------------------------------------------
#endif
