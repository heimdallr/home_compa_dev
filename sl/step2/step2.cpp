#include "stdafx.h"
#include "item.h"

class Timer
{
public:
	Timer() : m_begin(std::chrono::steady_clock::now()) {}
	~Timer()
	{
		std::cerr << "The time: " << double((*this)()) / 1000 << " s\n";
	}
	long long operator()() const
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_begin).count();
	}
private:
	std::chrono::time_point<std::chrono::steady_clock> m_begin;
};

int main(int argc, char* argv[])
{
	try
	{
		if (argc < 3)
			throw std::invalid_argument("usage:\nstep2 input_file_name start_position labels_file_name\n");

		const auto data = Read(argv[1]);
		const auto pos = std::atoi(argv[2]) - 1;
		const auto nMax = data.front().size() == 5 ? 36 : data.front().size() == 6 ? 49 : 0;
		assert(nMax > 0);

		std::vector<int> label;
		if (argc < 4)
		{
			label.resize(12);
			label[0] = 1;
			label[1] = 2;
			for (size_t i = 2, sz = label.size(); i < sz; ++i)
				label[i] = label[i - 1] + label[i - 2];
		}
		else
		{
			const auto rr = Reader<int>::Read(argv[3], false);
			for (const auto &r : rr)
				std::copy(r.cbegin(), r.cend(), std::back_inserter(label));
		}

		const std::string fileName = "статистика второго шага.txt";
		std::ofstream outp(utf8to16(fileName));
		if (!outp)
			throw std::ios_base::failure(std::string("Cannot write to \"") + fileName + "\"");


		for (size_t labelCount = 7, sz = label.size(); labelCount <= sz; ++labelCount)
		{
			std::cout << labelCount << "...";
			std::map<int, std::vector<size_t>> matchCounter;
			for (size_t currentPos = pos, sz = data.size(); currentPos < sz; ++currentPos)
			{
				Grouper<uint8_t>::GroupCounter groupCounter2;
				{
					Grouper<uint8_t>::GroupCounter groupCounter;
					for (auto it = label.cbegin(), end = std::next(label.cbegin(), labelCount); it != end; ++it)
					{
						const int pos = static_cast<int>(currentPos) - *it;
						if (pos >= 0 && pos < static_cast<int>(data.size()))
							Grouper<uint8_t>::Group(groupCounter, data[pos], 2, pos);
					}

					for (const auto &p : groupCounter)
					{
						if (p.second.size() < 2)
							continue;

						for (uint8_t i = p.first.front() > 1 ? p.first.front() - 1 : 1, in = p.first.front() < nMax ? p.first.front() + 1 : nMax; i < in; ++i)
						{
							for (uint8_t j = p.first.back() > 1 ? p.first.back() - 1 : 1, jn = p.first.back() < nMax ? p.first.back() + 1 : nMax; j < jn; ++j)
							{
								groupCounter2.emplace(Item({ i, j }), decltype(groupCounter2)::mapped_type());
							}
						}
					}
				}

				Grouper<uint8_t>::GroupCounter currentGroupCounter;
				Grouper<uint8_t>::Group(currentGroupCounter, data[currentPos], 2, static_cast<int>(currentPos));
				const auto matched = std::accumulate(currentGroupCounter.cbegin(), currentGroupCounter.cend(), 0, [&groupCounter2](int init, const decltype(currentGroupCounter)::value_type &item) {return init + (groupCounter2.find(item.first) != groupCounter2.end()); });
				matchCounter[matched].push_back(currentPos + 1);
			}

			outp << labelCount << std::endl;
			for (auto it = matchCounter.crbegin(), end = matchCounter.crend(); it != end; ++it)
			{
				outp << it->first << ": ";
				std::copy(it->second.cbegin(), it->second.cend(), std::ostream_iterator<size_t>(outp, " "));
				outp << std::endl;
			}
			outp << std::endl;
			outp.flush();
			std::cout << " done" << std::endl;
		}

	}
	catch (const std::exception &ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}

	return 0;
}
