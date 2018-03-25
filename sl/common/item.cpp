#include "stdafx.h"

#include "item.h"

std::wstring utf8to16(const std::string &src)
{
	std::vector<wchar_t> buffer;
	buffer.resize(MultiByteToWideChar(CP_UTF8, 0, src.c_str(), -1, 0, 0));
	MultiByteToWideChar(CP_UTF8, 0, src.c_str(), -1, &buffer[0], (int)buffer.size());
	return &buffer[0];
}

// Выводим в поток
std::ostream& Out(std::ostream &outp, const Item &item, const std::string &end /*= "\n"*/)
{
	for (const auto & i : item)
		outp << std::setw(2) << static_cast<int>(i) << " ";
//	std::copy(item.cbegin(), item.cend(), std::ostream_iterator<int>(outp, " "));
	return outp << end;
}

template <typename T>
bool Grouper<T>::ItemComparer::operator()(const ItemType &a, const ItemType &b) const
{
	auto ia = a.cbegin(), ib = b.cbegin();
	for (; ia != a.cend() && ib != b.cend(); ++ia, ++ib)
		if (*ia != *ib)
			return *ia < *ib;

	return ib != b.cend();
}

template <typename T>
struct GrouperImpl
{
	static void Group(typename Grouper<T>::GroupCounter &groupCounter, typename Grouper<T>::ItemType result, size_t n, typename Grouper<T>::ItemType::const_iterator beg, typename Grouper<T>::ItemType::const_iterator end, int m)
	{
		result.push_back(0);
		while (beg != end)
		{
			result.back() = *beg++;
			if (result.size() == n)
			{
				groupCounter[result].push_back(m);
				//			Out(result);
			}
			else
			{
				Group(groupCounter, result, n, beg, end, m);
			}
		}
	}
};

// Собираем группы по n
template <typename T>
void Grouper<T>::Group(GroupCounter &groupCounter, const ItemType &item, size_t n, int m)
{
	GrouperImpl<T>::Group(groupCounter, ItemType(), n, item.cbegin(), item.cend(), m);
}

template <typename T>
typename Reader<T>::DataType Reader<T>::Read(const std::string &fileName, bool checkCount /*= true*/)
{
	std::ifstream inp(fileName);
	if (!inp)
		throw std::invalid_argument(std::string("Cannot read from \"") + fileName + "\"");

	DataType data;

	// читаем данные из файла
	while (!inp.eof())
	{
		std::string s;
		std::getline(inp, s);
		std::istringstream stream(s);

		data.push_back(ItemType());
		std::copy(std::istream_iterator<int>(stream), std::istream_iterator<int>(), std::back_inserter(data.back()));
		//		Out(std::cout, data.back());

		if (data.back().empty())
			data.pop_back();

		if (checkCount && data.back().size() != data.front().size())
			throw std::runtime_error(std::string("Incorrect string: #") + std::to_string(data.size()));
	}

	assert(!data.empty());

	return data;
}

Data Read(const std::string &fileName)
{
	return Reader<uint8_t>::Read(fileName);
}

template class Grouper<uint8_t>;
template class Grouper<int>;
template class Grouper<size_t>;

template class Reader<uint8_t>;
template class Reader<int>;
