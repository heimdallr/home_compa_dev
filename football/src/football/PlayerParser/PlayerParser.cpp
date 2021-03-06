#include <exception>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::experimental::filesystem;

std::pair<std::string, std::string> ParseCmdLine(int argc, char *argv[])
{
	if (argc < 3)
		throw std::invalid_argument("usage\nPlayerParser path_to_files output_script");

	return std::make_pair(std::string(argv[1]), std::string(argv[2]));
}

void Parse(const std::string &country, std::ifstream &in, std::ostream &out);

int main(int argc, char *argv[])
{
	try
	{
		auto[path, script] = ParseCmdLine(argc, argv);
		std::ofstream out(script);
		if (!out.is_open())
			throw std::invalid_argument("Cannot write to \"" + script + "\"");

		fs::path src(path);
		if (!fs::exists(src))
			throw std::invalid_argument("\"" + path + "\" not found");

		for (const auto& p : fs::directory_iterator(src))
		{
			std::ifstream in(p);
			if (!in.is_open())
				throw std::runtime_error("Cannot read from \"" + p.path().string() + "\"");

			Parse(p.path().filename().string(), in, out);
		}
	}
	catch (const::std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
		return 1;
	}
    return 0;
}

struct Player
{
	using List = std::vector<Player>;

	int Id;
	std::string Country, Type, Name, Birthday;

	Player(int id) : Id(id) {}

	void Write(std::ostream &out) const
	{
		out << "insert into t_player_buf(country, player_type, num, name, birthday) values('"
			<< Country << "', '"
			<< Type << "', "
			<< Id << ", '"
			<< Name << "', '"
			<< Birthday << "');"
			<< std::endl;
	}
};

void trim(std::string &s)
{
	const char space[] = " \t-";
	const auto isSpace = [space](char c) { return std::find(std::cbegin(space), std::cend(space), c) != std::cend(space); };
	s.erase(s.begin(), std::find_if_not(s.begin(), s.end(), [&isSpace](char c) { return isSpace(c); }));
	s.erase(std::find_if_not(s.rbegin(), s.rend(), [&isSpace](char c) { return isSpace(c); }).base(), s.end());
}

std::string Get(std::ifstream &in)
{
	while (true)
	{
		std::string s;
		std::getline(in, s);
		if (in.eof())
			return std::string();

		trim(s);
		if (!s.empty())
			return s;
	}
}

void Parse(const std::string &country, std::ifstream &in, std::ostream &out)
{
	std::cout << country;

	Player::List list;
	std::string type;

	while (true)
	{
		auto s = Get(in);
		if (s.empty())
			break;

		int n = std::atoi(s.c_str());
		if (n == 0)
		{
			type = s;
			continue;
		}

		list.emplace_back(n);
		list.back().Country = country;
		list.back().Type = type;
		list.back().Name = Get(in);
		list.back().Birthday = Get(in);
		Get(in);
		std::cout << ".";
	}

	std::sort(list.begin(), list.end(), [](const Player &item1, const Player &item2) { return item1.Id < item2.Id; });
	std::for_each(list.begin(), list.end(), std::bind(&Player::Write, std::placeholders::_1, std::ref(out)));

	std::cout << " done" << std::endl;
}
