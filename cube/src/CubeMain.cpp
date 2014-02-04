//---------------------------------------------------------------------------
#pragma hdrstop

//---------------------------------------------------------------------------

#include "Item.h"

#pragma argsused
int main(int argc, char* argv[])
{
  const int ItemsCount = 7;
  Item items[ItemsCount];
  items[0] << 0 << 1 << 2 << 3;
  std::cout << items[0];
  std::cout << items[0].RoundUp();
  return 0;
}
//---------------------------------------------------------------------------

