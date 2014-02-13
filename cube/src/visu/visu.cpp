#include "visu.h"

visu::visu(const std::string &fileName)
	: _storage(fileName)
{
	ui.setupUi(this);
}

visu::~visu()
{

}
