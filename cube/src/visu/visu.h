#ifndef VISU_H
#define VISU_H

#include <QtGui/QMainWindow>
#include "ui_visu.h"
#include "ItemStorage.h"

class visu : public QMainWindow
{
	Q_OBJECT

public:
	visu(const std::string &fileName);
	~visu();

private:
	Ui::visuClass ui;
	ItemStorage _storage;
};

#endif // VISU_H
