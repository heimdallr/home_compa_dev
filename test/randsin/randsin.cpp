#include "stdafx.h"

int main(int argc, char *argv[])
{
	int N = 100;
	if (argc > 1)
		N = std::atoi(argv[1]);

	float sigma = 0.1f;
	if (argc > 2)
		sigma = static_cast<float>(std::atof(argv[2]));

	std::mt19937 gen;
	std::uniform_real_distribution<float> u(0.0f, 2.0f * std::acos(-1.0f));

	std::vector<float> x(N);
	std::generate(x.begin(), x.end(), [&gen, &u]() {return u(gen); });
	std::sort(x.begin(), x.end());

	std::normal_distribution<float> n(0.0f, sigma);

	std::vector<float> y;
	y.reserve(x.size());
	std::transform(x.cbegin(), x.cend(), std::back_inserter(y), [&gen, &n](float x) { return n(gen) + std::sin(x); });

	std::copy(x.cbegin(), x.cend(), std::ostream_iterator<float>(std::cout, ","));
	std::cout << std::endl;

	std::copy(y.cbegin(), y.cend(), std::ostream_iterator<float>(std::cout, ","));
	std::cout << std::endl;

    return 0;
}
