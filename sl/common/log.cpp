#include <fstream>
#include "log.h"

namespace {
std::ofstream g_log;
}

std::ofstream& log(const std::string &fileName)
{
	g_log.open(fileName, std::ofstream::out | std::ofstream::app);
	if (!g_log.is_open())
		throw std::ios_base::failure("Cannot open " + fileName);

	return g_log;
}

std::ofstream& log()
{
	return g_log;
}
