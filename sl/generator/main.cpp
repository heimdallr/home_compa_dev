#include <QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)

#include <QApplication>
#include <QMessageBox>

#include "Generator.h"

int main(int argc, char *argv[])
{
	try
	{
		QApplication a(argc, argv);

		HomeCompa::sl::Generator w;
		w.show();
		return a.exec();
	}
	catch (const std::exception &ex)
	{
		QMessageBox(QMessageBox::Icon::Critical, "Error", QString(ex.what()), QMessageBox::StandardButton::Ok).exec();
	}
}
