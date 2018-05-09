#include <Windows.h>

#include <algorithm>
#include <atomic>
#include <cassert>
#include <queue>
#include <thread>
#include <vector>

#include "Enumerator.h"
#include "GeneratorHandler.h"


namespace HomeCompa { namespace sl {

int GetCPUCount()
{
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	return sysinfo.dwNumberOfProcessors;
}

class Enumerator::Impl
{
private:
	GeneratorHandler & m_handler;
	const int m_n, m_m;
	const std::vector<std::vector<uint8_t>> m_head, m_tail;
	std::vector<std::thread> m_thread;
	std::atomic<size_t> m_i{ 0 }, m_readyCount{ 0 };

public:
	Impl(GeneratorHandler &handler, int n, int m)
		: m_handler(handler)
		, m_n(n)
		, m_m(m)
		, m_head(Generate(1, n / 2, m_m - n / 2))
		, m_tail(Generate(n / 2 + 1, n, m_m))
		, m_thread(std::max<int>(GetCPUCount() - 1, 1))
	{
	}

	~Impl()
	{
		m_i = m_head.size();
		for (auto &thread : m_thread)
			if (thread.joinable())
				thread.join();
	}

	size_t GetProgressMax() const
	{
		size_t res = 1;
		for (int i = 0; i < m_n; ++i)
			res *= (m_m - i);
		for (int i = 2; i <= m_n; ++i)
			res /= i;

		return res;
	}

	void Start()
	{
		for (auto &thread : m_thread)
			thread = std::thread(&Impl::Enumerate, this);
	}

private:
	void Enumerate()
	{
		while (m_i < m_head.size())
		{
			const auto i = m_i.fetch_add(1);
			if (i >= m_head.size())
				break;

			const auto &head = m_head[i];

			std::vector<std::vector<uint8_t>> buf;
			for (const auto &tail : m_tail)
			{
				if (head.back() >= tail.front())
					continue;

				buf.push_back(head);
				buf.back().reserve(head.size() + tail.size());
				std::copy(tail.cbegin(), tail.cend(), std::back_inserter(buf.back()));
			}

			if (!buf.empty())
				m_handler.Handle(buf);
		}

		if (++m_readyCount == m_thread.size())
			m_handler.Ready();
	}

	static std::vector<std::vector<uint8_t>> Generate(uint8_t from, uint8_t to, uint8_t m)
	{
		assert(from <= to && to < m);
		std::vector<std::vector<uint8_t>> result;
		if (from == to)
		{
			for (uint8_t i = from; i <= m; ++i)
				result.push_back({ i });
			return result;
		}

		std::queue<std::vector<uint8_t>> queue, buf;

		for (uint8_t i = from, sz = m - (to - from); i <= sz; ++i)
			queue.push({ i });

		while (!queue.empty())
		{
			auto item = queue.front();
			queue.pop();
			item.push_back(item.back() + 1);

			auto &s = item.size() == to - from + 1 ? buf : queue;
			s.push(item);

			for (uint8_t i = item.back() + 1, sz = m + item.size() - (to - from); i < sz; ++i)
			{
				item.back() = i;
				s.push(item);
			}
		}

		result.reserve(buf.size());
		while (!buf.empty())
		{
			result.push_back(buf.front());
			buf.pop();
		}

		return result;
	}
};

Enumerator::Enumerator(GeneratorHandler &handler, int n, int m)
	: m_impl(std::make_unique<Impl>(handler, n, m))
{
}

Enumerator::~Enumerator()
{
}

size_t Enumerator::GetProgressMax() const
{
	return m_impl->GetProgressMax();
}

void Enumerator::Start()
{
	m_impl->Start();
}

} }
