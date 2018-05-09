#pragma once

#include "item.h"

namespace HomeCompa { namespace sl {

class GeneratorHandler;

class ResultSaver
{
public:
	ResultSaver(GeneratorHandler &handler, const QString &fileName);
	~ResultSaver();

public:
	void Save(Data &&data);
	void Stop();

private:
	class Impl;
	std::unique_ptr<Impl> m_impl;
};

} }
