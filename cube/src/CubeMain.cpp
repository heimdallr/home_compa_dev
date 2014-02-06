//---------------------------------------------------------------------------
#pragma hdrstop

//---------------------------------------------------------------------------

#include "Item.h"

#pragma argsused
int main(int argc, char* argv[])
{
  Item::Items items;
  items.push_back(Item(1)); items.back() << 0 << 1 << 2 << 3;
  items.push_back(Item(2)); items.back() << 0 << 1 << 3;
  items.push_back(Item(3)); items.back() << 0 << 1 << 2 << 4;
  items.push_back(Item(4)); items.back() << 0 << 1 << 4 << 5;
  items.push_back(Item(4)); items.back() << 0 << 1 << 4 << 9;
//  std::cout << items[0];
//  std::cout << items[0].RoundClockwise();

  typedef std::vector<Item::Items> Storage;
  Storage storage;

  for (Item::Items::const_iterator it = items.begin(); it != items.end(); ++it) {
    storage.push_back();
    it->FillItems(storage.back());
  }

  for (Storage::const_iterator it = storage.begin(); it != storage.end(); ++it) {
    for (Item::Items::const_iterator jt = it->begin(); jt != it->end(); ++jt)
      std::cout << *jt;
    std::cout << it->size() << std::endl;
  }

  return 0;
}
//---------------------------------------------------------------------------

