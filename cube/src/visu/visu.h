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

private:
	Ui::visuClass ui;
	ItemStorage _storage;

private slots:
	void SlotCompositionChanged(int number);
};

#endif // VISU_H
