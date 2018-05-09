#include <QStringList>

#include "Filter.h"

namespace HomeCompa { namespace sl {

class Filter::Impl
{
	int m_n, m_m;

	Data m_a;

	std::set<uint8_t> m_b;

	Item m_c;
	int m_cFrom, m_cTo;

	Item m_even;

	Data m_positionsValues;

public:
	Impl(int n, int m)
		: m_n(n), m_m(m)
	{
	}
	void AddA(const QString &fileName)
	{
		Read(fileName.toStdString()).swap(m_a);
	}
	void AddB(const QString &fileName)
	{
		for (const auto &d : Read(fileName.toStdString()))
		{
			for (const auto c : d)
			{
				m_b.insert(c);
				if (c > 1)
					m_b.insert(c - 1);
				if (c < m_m)
					m_b.insert(c + 1);
			}
		}

		if (m_b.size() == m_m)
			m_b.clear();
	}
	void AddC(const QString &fileName, int from, int to)
	{
		m_cFrom = from;
		m_cTo = to;

		for (const auto &d : Read(fileName.toStdString()))
		{
			if (d.front() >= m_c.size())
				m_c.resize(d.front() + 1);
			m_c[d.front()] = d.back();
		}
	}
	void AddEven(const QString &even)
	{
		const auto list = even.split(' ', QString::SplitBehavior::SkipEmptyParts);
		std::transform(list.cbegin(), list.cend(), std::back_inserter(m_even), [](const QString &item) {return item.toInt(); });
	}
	void AddPositionsValues(const QString &fileName)
	{
		Read(fileName.toStdString()).swap(m_positionsValues);
	}
	bool Check(const Item &item) const
	{
		if (!m_even.empty() && std::accumulate(m_even.cbegin(), m_even.cend(), 0, [&item](int s, uint8_t c) {return s + (c - 1 < item.size() ? (item[c - 1] & 1) : 0); }) > 0)
			return false;

		if (!m_c.empty())
		{
			const auto s = std::accumulate(item.cbegin(), item.cend(), 0, [&c = m_c](int s, uint8_t i) {return s + c[i]; });
			if (s < m_cFrom || s > m_cTo)
				return false;
		}

		for (const auto &d : m_positionsValues)
			if (d[0] - 1 < item.size())
			{
				const auto v = item[d[0] - 1];
				if ((v < d[1] || v > d[2]) && v != d[3])
					return false;
			}

		if (!m_b.empty() && std::count_if(item.cbegin(), item.cend(), [&b = m_b](uint8_t item) {return b.find(item) != b.cend(); }) < item.size())
			return false;

		for (const auto &a : m_a)
			if (std::count_if(item.cbegin(), item.cend(), [&a](uint8_t item) {return std::find(a.cbegin(), a.cend(), item) != a.cend(); }) >= 4)
				return false;

		return true;
	}
};

Filter::Filter(int n, int m)
	: m_impl(std::make_unique<Impl>(n, m))
{
}

Filter::~Filter() = default;

void Filter::AddA(const QString &fileName)
{
	m_impl->AddA(fileName);
}
void Filter::AddB(const QString &fileName)
{
	m_impl->AddB(fileName);
}
void Filter::AddC(const QString &fileName, int from, int to)
{
	m_impl->AddC(fileName, from, to);
}
void Filter::AddEven(const QString &even)
{
	m_impl->AddEven(even);
}
void Filter::AddPositionsValues(const QString &fileName)
{
	m_impl->AddPositionsValues(fileName);
}
bool Filter::Check(const Item &item) const
{
	return m_impl->Check(item);
}

} }
