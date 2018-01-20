#include "stdafx.h"

// ��������������� ���� ������
using Item = std::vector<uint8_t>;
using Data = std::vector<Item>;

struct ItemComparer
{
	bool operator()(const Item &a, const Item &b) const
	{
		auto ia = a.cbegin(), ib = b.cbegin();
		for (; ia != a.cend() && ib != b.cend(); ++ia, ++ib)
			if (*ia != *ib)
				return *ia < *ib;
		
		return ib != b.cend();
	}
};

using GroupCounter = std::map<Item, size_t, ItemComparer>;

// ������� � �����
std::ostream& Out(std::ostream &outp, const Item &item, const std::string &end = "\n")
{
	std::copy(item.cbegin(), item.cend(), std::ostream_iterator<int>(outp, " "));
	return outp << end;		
}

// ����� ����������: ������� ��� �������� �����; ������� ��� ��� �������� ����� �� �����
void CountNumbers(const Data &data, const std::string fileName)
{
	std::cout << "Simple statistics... ";
	using NumberCounter = std::map<uint8_t, std::pair<size_t, std::vector<size_t>>>;
	NumberCounter numberCounter;
	
	for (const auto &d : data)
	{
		for (size_t i = 0, sz = d.size(); i < sz; ++i)
		{
			auto &t = numberCounter.insert({d[i], {0, std::vector<size_t>(sz)}}).first->second;
			++t.first;
			++t.second[i];
		}
	}
		
	std::ofstream outp(fileName);
	if (!outp)
		throw std::ios_base::failure(std::string("Cannot write to \"") + fileName + "\"");
	
	for (const auto &t : numberCounter)
	{
		outp << (int)t.first << "  ";
		std::copy(t.second.second.cbegin(), t.second.second.cend(), std::ostream_iterator<size_t>(outp, " "));
		outp << " " << t.second.first << std::endl;
	}

	std::cout << "done" << std::endl;
}

// ���������� ������: ����� �������; ���������� ������� � 1, 2, � �.�. �������; ���������� ������, �������� �� �����
void CountEven(const Data &data, const std::string fileName)
{
	std::cout << "Simple even statistics... ";

	std::vector<size_t> placeCount(data[0].size()), stat(placeCount.size() + 1);
	
	for (const auto &d : data)
	{
		for (size_t i = 0, sz = d.size(); i < sz; ++i)
		{
			if (d[i] % 2 == 0)
			{
				++placeCount[i];
			}
		}
		
		++stat[std::accumulate(d.cbegin(), d.cend(), size_t(0), [](size_t init, uint8_t item){ return init + ((item + 1) & 1); })];
	}
		
	std::ofstream outp(fileName);
	if (!outp)
		throw std::ios_base::failure(std::string("Cannot write to \"") + fileName + "\"");
	
	outp << data.size() << std::endl << std::endl;
	for (size_t i = 0, sz = stat.size(); i < sz; ++i)
		outp << i << "  "<< stat[i] << std::endl;
	outp << std::endl;
		
	for (size_t i = 0, sz = placeCount.size(); i < sz; ++i)
		outp << i + 1 << "  " << placeCount[i] << std::endl;

	std::cout << "done" << std::endl;
}

// �������� ������ �� n
void Group(GroupCounter &groupCounter, Item result, size_t n, Item::const_iterator beg, Item::const_iterator end)
{
	result.push_back(0);
	while (beg != end)
	{
		result.back() = *beg++;
		if (result.size() == n)
		{
			++groupCounter[result];
//			Out(result);
		}
		else
		{
			Group(groupCounter, result, n, beg, end);
		}
	}
}

std::string GetFileName(const std::string &prefix, size_t n)
{
	std::ostringstream fileName;
	fileName << prefix << n << ".txt";
	return fileName.str();
}

// ���������� �����
void CountGroups(const Data &data)
{
	std::cout << "Groups statistics";

	for (size_t i = 2, sz = data.front().size(); i < sz; ++i)
	{
		const auto fileName = GetFileName("group", i);
		std::ofstream outp(fileName);
		if (!outp)
			throw std::ios_base::failure(std::string("Cannot write to \"") + fileName + "\"");
		
		GroupCounter groupCounter;
			
		// �������� ������
		for (auto &d : data)
			Group(groupCounter, Item(), i, d.cbegin(), d.cend());
			
		for (const auto &g : groupCounter)
			Out(outp, g.first, " ") << g.second << std::endl;

		std::cout << ".";
	}

	std::cout << " done" << std::endl;
}

// ���������� ������ �����
void CountEvenGroups(const Data &data)
{
	std::cout << "Even statistics";

	for (size_t i = 2, sz = data.front().size(); i < sz; ++i)
	{
		const auto fileName = GetFileName("EvenGroups", i);
		std::ofstream outp(fileName);
		if (!outp)
			throw std::ios_base::failure(std::string("Cannot write to \"") + fileName + "\"");
		
		GroupCounter groupCounter;
		Item index(data.front().size());
		std::iota(index.begin(), index.end(), 0);
		Group(groupCounter, std::vector<uint8_t>(), i, index.cbegin(), index.cend());
		
		for (auto &g : groupCounter)
			g.second = 0;

		for (const auto &d : data)
			for (auto &g : groupCounter)
				if (std::find_if(g.first.cbegin(), g.first.cend(), [&d](auto i) {return (d[i] & 1) != 0; }) == g.first.cend())
					++g.second;

		for (const auto &g : groupCounter)
		{
			if (g.second > 0)
			{
				Item group(g.first.size());
				std::transform(g.first.cbegin(), g.first.cend(), group.begin(), [](auto n) {return n + 1; });
				Out(outp, group, " ") << g.second << std::endl;
			}
		}

		std::cout << ".";
	}

	std::cout << " done" << std::endl;
}

// �������
int main(int argc, char* argv[])
{
	try
	{
		if (argc < 2)
			throw std::invalid_argument("usage:\nstatistics input_file_name\n");
		
		std::ifstream inp(argv[1]);
		if (!inp)
			throw std::invalid_argument(std::string("Cannot read from \"") + argv[1] + "\"");
		
		Data data;
		
		// ������ ������ �� �����
		while (!inp.eof())
		{
			std::string s(100, 0);
			inp.getline(&s[0], 100);
			std::istringstream stream(s);
	
			data.push_back(Item());
			std::copy(std::istream_iterator<int>(stream), std::istream_iterator<int>(), std::back_inserter(data.back()));
	//		Out(std::cout, data.back());
	
			if (data.back().empty())
				data.pop_back();
			
			if (data.back().size() != data.front().size())
				throw std::runtime_error(std::string("Incorrect string: #") + std::to_string(data.size()));
		}
		
		if (data.empty())
		{
			std::cerr << "File is empty";
			return 1;
		}
		
		// �������� ������� ����������
		CountNumbers(data, "NumberCount.txt");
		CountEven(data, "EvenStat.txt");
		
		// ��������� ������ � ���������
		for (auto &d : data)
			std::sort(d.begin(), d.end());
	
		// �������� ���������� �� ������� 
		CountGroups(data);
		
		// �������� ���������� �� ������� ������
		CountEvenGroups(data);
	}
	catch(const std::exception &ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	
	return 0;
}

