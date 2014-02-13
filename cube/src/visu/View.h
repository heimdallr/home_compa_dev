#ifndef VIEW_H
#define VIEW_H

#include <QGLWidget>
#include "ui_View.h"

class View : public QGLWidget
{
	Q_OBJECT

public:
	View(QWidget *parent = 0);
	~View();

private:
	Ui::View ui;
};

#endif // VIEW_H
