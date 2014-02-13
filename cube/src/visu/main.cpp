#include "visu.h"
#include <QtGui/QApplication>
#include <QtGui/qmessagebox.h>

#include "ItemStorage.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	try 
	{
		if (argc < 2)
			throw std::invalid_argument("Name of file with items description required!");

		visu w(argv[1]);
		w.show();
		return a.exec();
	}
	catch(const std::exception &ex)
	{
		QMessageBox::critical(nullptr, "Error!", ex.what());
	}
}
