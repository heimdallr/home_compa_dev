#pragma once
#include <vector>

namespace HomeCompa { namespace sl {

class GeneratorHandler
{
public:
	virtual void Handle(std::vector<std::vector<uint8_t>> &data) = 0;
	virtual void Ready() = 0;
	virtual void Saved(size_t) = 0;
	virtual void SaveReady() = 0;

protected:
	~GeneratorHandler() = default;
};

} }
