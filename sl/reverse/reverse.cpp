#include "stdafx.h"

int main(int argc, char* argv[])
{
	try
	{
		if (argc < 3)
			throw std::invalid_argument("usage:\nreverse input_file_name output_file_name");

		std::ifstream inp(argv[1]);
		if (!inp)
			throw std::invalid_argument(std::string("Cannot read from \"") + argv[1] + "\"");

		std::ofstream outp(argv[2]);
		if (!outp)
			throw std::invalid_argument(std::string("Cannot write to \"") + argv[2] + "\"");

		std::stack<std::string> data;
		std::string buf;

		std::cout << "Reading";
		while (std::getline(inp, buf))
		{
			data.push(buf);
			if ((data.size() % 100) == 0)
				std::cout << ".";
		}
		std::cout << " done" << std::endl;

		std::cout << "Writing";
		while (!data.empty())
		{
			outp << data.top() << std::endl;
			data.pop();
			if ((data.size() % 100) == 0)
				std::cout << ".";
		}
		std::cout << " done" << std::endl;
	}
	catch (const std::exception &ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}

	return 0;
}

