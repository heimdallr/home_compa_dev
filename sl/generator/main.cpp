#include <QApplication>

#include "Generator.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	HomeCompa::sl::Generator w;
	w.show();
	return a.exec();
}
