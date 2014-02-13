#include <fstream>
#include <string>

#include "ItemStorage.h"


ItemStorage::ItemStorage(const std::string &fileName)
{
	std::ifstream inp(fileName, std::ifstream::in);
	if (!inp.is_open())
		throw std::ios_base::failure(std::string("Cannot open \"") + fileName + "\"");
	while (!inp.eof())
	{
		std::string str;
		std::getline(inp, str);
		if (str.empty())
			continue;

		if (str.find(':') == std::string::npos)
			_storage.push_back(Item::Items());
		else
			_storage.back().push_back(Item(str));
	}
}

int ItemStorage::GetSize() const
{
	return _storage.size();
}

const Item::Items& ItemStorage::GetComposition(int n) const
{
	return _storage[n];
}
