#ifndef VIEW_H
#define VIEW_H

#include <QGLWidget>
#include <QListWidget.h>
#include "../Item.h"
#include "ui_View.h"

class View : public QGLWidget
{
	Q_OBJECT

public:
	View();
	void Prepare(const Item::Items &items);
	void Paint(const Elems &items);

public slots:
	void SlotItemChanged(QListWidgetItem *item);

protected:
	void initializeGL() override;
	void resizeGL(int width, int height) override;
	void paintGL() override;
	void mousePressEvent(QMouseEvent *ev) override;
	void mouseMoveEvent(QMouseEvent *ev) override;
	void Paint();
	GLuint Prepare(const Item &item) const;
	void Prepare(int n) const;

signals:
	void initialized(int);

private:
typedef std::map<int, QColor> ColorMap;
typedef std::vector<GLuint> IdList;
	Ui::View ui;
	ColorMap _colorMap;
	IdList _ids;
	Elems _toPaint;
	GLfloat _xRotate, _yRotate;
	QPoint _ptPosition;
};

#endif // VIEW_H
