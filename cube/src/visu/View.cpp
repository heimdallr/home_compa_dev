#include <assert.h>
#include <QMouseEvent>
#include "View.h"

View::View()
	: _xRotate(0.0)
	, _yRotate(0.0)
{
	ui.setupUi(this);
	_colorMap.insert(ColorMap::value_type(1, QColor(0xEE4000)));
	_colorMap.insert(ColorMap::value_type(2, QColor(0xFFD000)));
	_colorMap.insert(ColorMap::value_type(3, Qt::white));
	_colorMap.insert(ColorMap::value_type(4, QColor(0x78329B)));
	_colorMap.insert(ColorMap::value_type(5, QColor(0x000080)));
	_colorMap.insert(ColorMap::value_type(6, QColor(0xEE0000)));
	_colorMap.insert(ColorMap::value_type(7, QColor(0x008B45)));

}

void View::initializeGL()
{
	qglClearColor(Qt::black);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);

	emit initialized(1);
}

void View::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);;
	glLoadIdentity();
	glFrustum(-1.5, 1.5,  -1.5, 1.5,  0.5, 5.0);
}

void View::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -3.0);

	glRotatef(_xRotate, 1.0, 0.0, 0.0);
	glRotatef(_yRotate, 0.0, 1.0, 0.0);

	Paint();
}

void View::mousePressEvent(QMouseEvent *ev)
{
	_ptPosition = ev->pos();
}

void View::mouseMoveEvent(QMouseEvent *ev)
{
	_xRotate += 180 * static_cast<GLfloat>(ev->y() - _ptPosition.y()) / height();
	_yRotate += 180 * static_cast<GLfloat>(ev->x() - _ptPosition.x()) / width();
	updateGL();
	_ptPosition = ev->pos();
}

void View::Paint(const Elems &items)
{
	_toPaint = items;
	Paint();
}

void View::Paint()
{
	std::for_each(_toPaint.begin(), _toPaint.end(), [this](int n) {
		glCallList(_ids[n]);
	});
}

void View::Prepare(const Item::Items &items)
{
	_toPaint.clear();
	_ids.clear();
	_ids.resize(items.size(), -1);

	std::for_each(items.begin(), items.end(), [this](const Item &item) {
		_ids[item.GetId()-1] = Prepare(item);
	});

}

GLuint View::Prepare(const Item &item) const
{
	ColorMap::const_iterator it = _colorMap.find(item.GetId());
	assert (it != _colorMap.end());

	GLuint id = glGenLists(1);
	glNewList(id, GL_COMPILE);
	glBegin(GL_QUADS);
	qglColor(it->second);

	std::for_each(item.GetElems().begin(), item.GetElems().end(), [this](int n){
		Prepare(n);
	});

	glEnd();
	glEndList();

	return id;
}

void View::Prepare(int n) const
{
	Array offset = ToArray(n);
	std::for_each(offset.begin(), offset.end(), [](int &n){--n;});

	glVertex3f(offset[0]-0.5, offset[1]-0.5, offset[2]-0.5);
	glVertex3f(offset[0]+0.5, offset[1]-0.5, offset[2]-0.5);
	glVertex3f(offset[0]+0.5, offset[1]-0.5, offset[2]+0.5);
	glVertex3f(offset[0]-0.5, offset[1]-0.5, offset[2]+0.5);

	glVertex3f(offset[0]-0.5, offset[1]-0.5, offset[2]-0.5);
	glVertex3f(offset[0]-0.5, offset[1]+0.5, offset[2]-0.5);
	glVertex3f(offset[0]-0.5, offset[1]+0.5, offset[2]+0.5);
	glVertex3f(offset[0]-0.5, offset[1]-0.5, offset[2]+0.5);

	glVertex3f(offset[0]-0.5, offset[1]-0.5, offset[2]-0.5);
	glVertex3f(offset[0]+0.5, offset[1]-0.5, offset[2]-0.5);
	glVertex3f(offset[0]+0.5, offset[1]+0.5, offset[2]-0.5);
	glVertex3f(offset[0]-0.5, offset[1]+0.5, offset[2]-0.5);

	glVertex3f(offset[0]-0.5, offset[1]+0.5, offset[2]-0.5);
	glVertex3f(offset[0]+0.5, offset[1]+0.5, offset[2]-0.5);
	glVertex3f(offset[0]+0.5, offset[1]+0.5, offset[2]+0.5);
	glVertex3f(offset[0]-0.5, offset[1]+0.5, offset[2]+0.5);

	glVertex3f(offset[0]+0.5, offset[1]-0.5, offset[2]-0.5);
	glVertex3f(offset[0]+0.5, offset[1]+0.5, offset[2]-0.5);
	glVertex3f(offset[0]+0.5, offset[1]+0.5, offset[2]+0.5);
	glVertex3f(offset[0]+0.5, offset[1]-0.5, offset[2]+0.5);

	glVertex3f(offset[0]-0.5, offset[1]-0.5, offset[2]+0.5);
	glVertex3f(offset[0]+0.5, offset[1]-0.5, offset[2]+0.5);
	glVertex3f(offset[0]+0.5, offset[1]+0.5, offset[2]+0.5);
	glVertex3f(offset[0]-0.5, offset[1]+0.5, offset[2]+0.5);

}

void View::SlotItemChanged(QListWidgetItem *item)
{
	int id = item->data(Qt::UserRole).toInt() - 1;
	Elems::const_iterator it = _toPaint.find(id);
	if (item->checkState() == Qt::Checked)
	{
		if (it == _toPaint.end())
		{
			_toPaint.insert(id);
			updateGL();
		}
	}
	else
		if (it != _toPaint.end())
		{
			_toPaint.erase(id);
			updateGL();
		}
}