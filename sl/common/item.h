#pragma once

// ��������������� ���� ������
using Item = std::vector<uint8_t>;
using Data = std::vector<Item>;

std::wstring utf8to16(const std::string &src);

// ������� � �����
std::ostream& Out(std::ostream &outp, const Item &item, const std::string &end = "\n");

template <typename T>
class Grouper
{
public:
	using ItemType = std::vector<T>;

	struct ItemComparer
	{
		bool operator()(const ItemType &a, const ItemType &b) const;
	};
	using GroupCounter = std::map<ItemType, std::vector<int>, ItemComparer>;

	// �������� ������ �� n
	static void Group(GroupCounter &groupCounter, const ItemType &item, size_t n, int m);
};

// ������� �� �����
template <typename T>
class Reader
{
public:
	using ItemType = std::vector<T>;
	using DataType = std::vector<ItemType>;
	static DataType Read(const std::string &fileName, bool checkCount = true);
};

Data Read(const std::string &fileName);
