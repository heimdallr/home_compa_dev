#pragma once

#include <memory>

namespace HomeCompa { namespace sl {

class GeneratorHandler;

class Enumerator
{
public:
	Enumerator(GeneratorHandler &handler, int n, int m);
	~Enumerator();
	size_t GetProgressMax() const;
	void Start();

private:
	class Impl;
	std::unique_ptr<Impl> m_impl;
};

} }
