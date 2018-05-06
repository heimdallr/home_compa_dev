#pragma once
#include <vector>

namespace HomeCompa { namespace sl {

class GeneratorHandler
{
public:
	virtual void Handle(std::vector<std::vector<uint8_t>> &data) = 0;

protected:
	~GeneratorHandler() = default;
};

} }
