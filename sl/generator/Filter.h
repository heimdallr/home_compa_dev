#pragma once
#include <memory>
#include <QString>

#include "item.h"

namespace HomeCompa { namespace sl {

class Filter
{
public:
	Filter(int n, int m);
	~Filter();

public:
	void AddA(const QString &fileName);
	void AddB(const QString &fileName);
	void AddC(const QString &fileName, int from, int to);
	void AddEven(const QString &even);
	void AddPositionsValues(const QString &fileName);

	bool Check(const Item &item) const;

private:
	class Impl;
	std::unique_ptr<Impl> m_impl;
};

} }
