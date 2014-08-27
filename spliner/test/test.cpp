#include <numeric>

#include <boost/assign.hpp>
#include <boost/timer/timer.hpp>

#include "../spliner/spliner.h"

int main(int argc, char* argv[])
{
	const size_t dim = 256;
	Spliner::ValueListType x(dim), y(dim), z(dim);

	for (size_t i = 0; i < dim; ++i)
	{
		x[i] = Spliner::ValueListType::value_type(i) / 20;
		y[i] = sin(x[i]) * 10;
	}

	Spliner spliner(x, 10);

	boost::timer::auto_cpu_timer t;
	for (int i = 0; i < 100000; ++i)
	{
		spliner.Initialize(y);
		spliner.Compute(x, z);
	}
	return 0;
}

