#ifndef VISU_H
#define VISU_H

#include <QtGui/QMainWindow>
#include "ui_visu.h"
#include "ItemStorage.h"
#include "View.h"

class visu : public QMainWindow
{
	Q_OBJECT

public:
	visu(const std::string &fileName);

private:
	Ui::visuClass ui;
	ItemStorage _storage;
	View *_view;

private slots:
	void SlotCompositionChanged(int number);
};

#endif // VISU_H
