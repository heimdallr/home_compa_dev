#include "stdafx.h"

#include "../common/item.h"

// Общая статистика: сколько раз выпадало число; сколько раз оно выпадало каким по счёту
void CountNumbers(const Data &data, const std::string &fileName)
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
		
	std::ofstream outp(utf8to16(fileName));
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

// Статистика чётных: всего тиражей; количества тиражей с 1, 2, и т.д. чётными; количество чётных, выпавших по счёту
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
		
	std::ofstream outp(utf8to16(fileName));
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

const std::string g_fileNames[] = {
	"",
	"",
	"пары",
	"тройки",
	"четвёрки",
	"пятёрки",
	"шестёрки",
};

std::string GetFileName(const std::string &prefix, size_t n)
{
	std::ostringstream fileName;
	fileName << prefix;
	if (n < std::size(g_fileNames))
		fileName << g_fileNames[n];
	else
		fileName << "_" << n;
	fileName << ".txt";

	return fileName.str();
}

// Статистика групп
void CountGroups(const Data &data)
{
	std::cout << "Groups statistics";

	for (size_t i = 2, sz = data.front().size(); i < sz; ++i)
	{
		const auto fileName = GetFileName("", i);
		std::ofstream outp(utf8to16(fileName));
		if (!outp)
			throw std::ios_base::failure(std::string("Cannot write to \"") + fileName + "\"");
		
		Grouper<uint8_t>::GroupCounter groupCounter;
			
		// собираем группы
		for (size_t j = 0, sz = data.size(); j < sz; ++j)
			Grouper<uint8_t>::Group(groupCounter, data[j], i, static_cast<int>(j + 1));
			
		std::vector<std::pair<decltype(groupCounter)::key_type, decltype(groupCounter)::mapped_type>> sorted;
		std::copy(groupCounter.cbegin(), groupCounter.cend(), std::back_inserter(sorted));

		Grouper<uint8_t>::ItemComparer comparer;
		std::sort(sorted.begin(), sorted.end(), [&comparer](const decltype(sorted)::value_type &item1, const decltype(sorted)::value_type &item2) -> bool
		{
			if (item1.second.size() != item2.second.size())
				return item1.second.size() > item2.second.size();

			return comparer(item1.first, item2.first);
		});

		for (const auto &g : sorted)
		{
			Out(outp, g.first, "\t") << g.second.size() << ": ";
			std::copy(g.second.cbegin(), g.second.cend(), std::ostream_iterator<int>(outp, " "));
			outp << std::endl;
		}

		std::cout << ".";
	}

	std::cout << " done" << std::endl;
}

// Статистика чётных групп
void CountEvenGroups(const Data &data)
{
	std::cout << "Even statistics";

	for (size_t i = 2, sz = data.front().size(); i < sz; ++i)
	{
		const auto fileName = GetFileName("чётные ", i);
		std::ofstream outp(utf8to16(fileName));
		if (!outp)
			throw std::ios_base::failure(std::string("Cannot write to \"") + fileName + "\"");
		
		Grouper<uint8_t>::GroupCounter groupCounter;
		Item index(data.front().size());
		std::iota(index.begin(), index.end(), 0);
		Grouper<uint8_t>::Group(groupCounter, index, i, 0);
		
		for (auto &g : groupCounter)
			g.second.clear();

		for (size_t j = 0, sz = data.size(); j < sz; ++j)
			for (auto &g : groupCounter)
				if (std::find_if(g.first.cbegin(), g.first.cend(), [&d = data[j]](auto i) {return (d[i] & 1) != 0; }) == g.first.cend())
					g.second.push_back(static_cast<int>(j + 1));

		for (const auto &g : groupCounter)
		{
			if (g.second.size() > 0)
			{
				Item group(g.first.size());
				std::transform(g.first.cbegin(), g.first.cend(), group.begin(), [](auto n) {return n + 1; });
				Out(outp, group, "\t") << g.second.size() << ": ";
				std::copy(g.second.cbegin(), g.second.cend(), std::ostream_iterator<int>(outp, " "));
				outp << std::endl;
			}
		}

		std::cout << ".";
	}

	std::cout << " done" << std::endl;
}

// Поехали
int main(int argc, char* argv[])
{
	try
	{
		if (argc < 2)
			throw std::invalid_argument("usage:\nstatistics input_file_name\n");
		
		Data data = Read(argv[1]);

		if (data.empty())
		{
			std::cerr << "File is empty";
			return 1;
		}
		
		// собираем простую статистику
		CountNumbers(data, "статистика по числам.txt");
		CountEven(data, "статистика по чётным числам.txt");
		
		// сортируем данные в элементах
		for (auto &d : data)
			std::sort(d.begin(), d.end());
	
		// собираем статистику по группам 
		CountGroups(data);
		
		// собираем статистику по группам чётных
		CountEvenGroups(data);
	}
	catch(const std::exception &ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	
	return 0;
}

