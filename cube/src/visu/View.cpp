#include "View.h"

View::View(QWidget *parent)
	: QGLWidget(parent)
{
	ui.setupUi(this);
}

View::~View()
{

}
