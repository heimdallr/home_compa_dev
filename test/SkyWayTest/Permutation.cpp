#include <chrono>		// system_clock
#include <functional>	// bind

#include <iostream>
#include <iterator>		// istream_iterator, ostream_iterator
#include <random>
#include <string>

#include "Deque.h"
#include "RandomizedQueue.h"

using namespace MyContainer;

void DequePermutationTest(int k, std::ostream& out)
{
	std::vector<size_t> counters(10, 0);

	std::default_random_engine ramdonEngine;

	for (size_t i = 0, itersCount = 1000000; i < itersCount; ++i)
	{
		Deque<int> deque;
		for (int n = 0; n < 10; ++n)
			deque.addLast(n);

		std::shuffle(deque.begin(), deque.end(), ramdonEngine);

		for (int n = 0; n < k; ++n)
			++counters[deque.removeLast()];
	}

	std::copy(std::cbegin(counters), std::cend(counters), std::ostream_iterator<size_t>(out, "\n"));
}

void RandomizedQueuePermutationTest(int k, std::ostream& out)
{
	std::vector<size_t> counters(10, 0);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

	for (size_t i = 0, itersCount = 1000000; i < itersCount; ++i)
	{
		RandomizedQueue<int> queue;

		for (int n = 0; n < k; ++n)
			queue.enqueue(n);

		for (int n = k; n < 10; ++n)
			if (dis(gen) < 1.0 * k / (n + 1))
			{
				queue.dequeue();
				queue.enqueue(n);
			}

		for (auto& n : queue)
			++counters[n];
	}

	std::copy(std::cbegin(counters), std::cend(counters), std::ostream_iterator<size_t>(out, "\n"));
}

template<typename Item>
void DequePermutation(int k, std::istream& in, std::ostream& out)
{
	Deque<Item> deque;
	std::for_each(std::istream_iterator<Item>(in), std::istream_iterator<Item>(), std::bind(&Deque<Item>::addLast, std::ref(deque), std::placeholders::_1));

	std::shuffle(deque.begin(), deque.end(), std::default_random_engine(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count())));

	while (k-- > 0 && !deque.isEmpty())
		out << deque.removeLast() << std::endl;
}

template<typename Item>
void RandomizedQueuePermutation(int k, std::istream& in, std::ostream& out)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

	RandomizedQueue<Item> queue;

	// scope for it, end
	{
		auto it = std::istream_iterator<Item>(in), end = std::istream_iterator<Item>();
		for (int i = 0; i < k && it != end; ++i, ++it)
			queue.enqueue(*it);

		for (size_t counter = k + 1; it != end; ++counter, ++it)
		{
			if (dis(gen) < 1.0 * k / counter)
			{
				queue.dequeue();
				queue.enqueue(*it);
			}
		}
	}

	assert(queue.size() <= k);

	while (k-- > 0 && !queue.isEmpty())
		out << queue.dequeue() << std::endl;
}

int main(int argc, char *argv[])
{
	try
	{
		if (argc < 2)
			throw std::invalid_argument("Usage:\nPermutation k\nwhere k is size of permutation result");

//		research
//		DequePermutationTest(std::atoi(argv[1]), std::cout);
//		RandomizedQueuePermutationTest(std::atoi(argv[1]), std::cout);

//		DequePermutation<std::string>(std::atoi(argv[1]), std::cin, std::cout);
		RandomizedQueuePermutation<std::string>(std::atoi(argv[1]), std::cin, std::cout);

		return 0;
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Unknown error" << std::endl;
	}

	return 1;
}
