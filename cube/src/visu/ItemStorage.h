#pragma once
#include "../Item.h"
class ItemStorage
{
	Item::Storage _storage;
public:

	ItemStorage(const std::string &fileName);
	int GetSize() const;
	const Item::Items& GetComposition(int n) const;
};

