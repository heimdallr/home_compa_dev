#include <sstream>

#include "Item.h"
#include "Utils.h"

// Конструктор
Item::Item(int id) : _id(id), _elems(), _size(Dimensions, 0) {
}
//---------------------------------------------------------------------------

Item::Item(const std::string &str) : _id(0), _elems(), _size(Dimensions, 0) {
	std::istringstream stream(str);
	stream >> _id;
	char c('\0');
	while (!stream.eof())
	{
		while(c != '{' && !stream.eof())
			stream >> c;
		if (stream.eof())
			break;
		Array array;
		for (int i=0; i<Dimensions; ++i)
		{
			int n;
			stream >> n;
			array.push_back(n);
		}
		while(c != '}' && !stream.eof())
			stream >> c;
		_elems.insert(ToInt(array));
	}
	CountSize();
}
//---------------------------------------------------------------------------

int Item::GetId() const
{
	return _id;
}
const Elems& Item::GetElems() const
{
	return _elems;
}

// сравнивалка элементов
bool Item::Less(const Item &rh) const {
  return std::lexicographical_compare(_elems.begin(), _elems.end(), rh._elems.begin(), rh._elems.end());
}
//---------------------------------------------------------------------------

// порождаем набор элементов посредством вращения в одной плоскости и всевозможных параллельных переносов
void Item::FillItemRound(UniqueItems &uitems) const {
  Items items;
  FillItemMoves(items);
  Item item = RoundClockwise();
  for (int i=0; i<3; ++i, item = item.RoundClockwise())
    item.FillItemMoves(items);
  std::copy(items.begin(), items.end(), std::inserter(uitems, uitems.end()));
}
//---------------------------------------------------------------------------

// заполняем контейнер всеми возможными сдвигами элемента в фигуре
void Item::FillItemMoves(Items &items) const {
  Array offset(Dimensions, 0), mx(Dimensions, 0);
  for (int i=0; i<Dimensions; ++i)
    mx[i] = Dimensions - _size[i];
  CheckFillItemMoves check(*this, items);
  GetNext(mx, check);
}
//---------------------------------------------------------------------------

// заполняем контейнер всеми возможными положениями элемента в фигуре
void Item::FillItems(Items &items) const {
  UniqueItems u;
  FillItemRound(u);

  Item item = RoundLeft();
  for (int i=0; i<3; ++i, item = item.RoundLeft())
    item.FillItemRound(u);

  RoundUp().FillItemRound(u);
  RoundDown().FillItemRound(u);

  std::copy(u.begin(), u.end(), std::back_inserter(items));
}
//---------------------------------------------------------------------------

// Вычисляем размеры элемента
void Item::CountSize() {
  Array mn(Dimensions, std::numeric_limits<int>::max()), mx(Dimensions, std::numeric_limits<int>::min());
  for (Elems::const_iterator it = _elems.begin(); it != _elems.end(); ++it) {
    Array e = ToArray(*it);
    for (int i=0; i<Dimensions; ++i) {
      if (mn[i] > e[i])
        mn[i] = e[i];
      if (mx[i] < e[i])
        mx[i] = e[i];
    }
  }
  for (int i=0; i<Dimensions; ++i)
    _size[i] = mx[i] - mn[i];
}
//---------------------------------------------------------------------------

// добавляем точку в элемент
Item& Item::operator<<(int elem) {
  _elems.insert(elem);
  CountSize();
  return *this;
}
//---------------------------------------------------------------------------

// порождаем новый элемент умножением подэлементов на указанную матрицу
Item Item::Round(const Matrix &matrix) const {
  Item res(_id);
  matrix.Multiply(_elems, res._elems);
  res.CountSize();
  return res;
};
//---------------------------------------------------------------------------

// сдвиг
Item Item::Move(const Array &offset) const {
  Item res(_id);
  res._size = _size;
  ::Move(_elems, res._elems, offset);
  return res;
}
//---------------------------------------------------------------------------

// всякие вращения, не все даже и нужны
Item Item::RoundUp() const {
  static const int array[] = {
    1,  0, 0,
    0,  0, 1,
    0, -1, 0
  };
  static const Matrix matrix(array);
  return Round(matrix);
}
Item Item::RoundDown() const {
  static const int array[] = {
    1, 0,  0,
    0, 0, -1,
    0, 1,  0
  };
  static const Matrix matrix(array);
  return Round(matrix);
}
Item Item::RoundLeft() const {
  static const int array[] = {
     0, 1, 0,
    -1, 0, 0,
     0, 0, 1
  };
  static const Matrix matrix(array);
  return Round(matrix);
}
Item Item::RoundRight() const {
  static const int array[] = {
    0, -1, 0,
    1,  0, 0,
    0,  0, 1
  };
  static const Matrix matrix(array);
  return Round(matrix);
}
Item Item::RoundClockwise() const {
  static const int array[] = {
    0,  0, 1,
    0,  1, 0,
    -1, 0, 0
  };
  static const Matrix matrix(array);
  return Round(matrix);
}
Item Item::RoundCounterClockwise() const {
  static const int array[] = {
    0, 0, -1,
    0, 1,  0,
    1, 0,  0
  };
  static const Matrix matrix(array);
  return Round(matrix);
}
//---------------------------------------------------------------------------

// пишем элемент в поток
std::ostream& Item::operator>>(std::ostream &stream) const {
  std::ostream_iterator<int> oit(stream, " ");
  stream << _id << ":";
  for (Elems::const_iterator it = _elems.begin(); it != _elems.end(); ++it) {
    stream << " { ";
    Array array(ToArray(*it));
    std::copy(array.begin(), array.end(), oit);
    stream << "} ";
  }
  stream << std::endl;
  return stream;
}
//---------------------------------------------------------------------------

// проверяем элемент на возможность добавить его в (частично уже занятый) куб
bool Item::Check(const Array &cube) const {
  for (Elems::const_iterator it = _elems.begin(); it != _elems.end(); ++it)
    if (cube[*it])
      return false;
  return true;
}
//---------------------------------------------------------------------------

// добавдобавляем (удаляем) элемент в куб
void Item::SetToCube(Array &cube, int n) const {
  for (Elems::const_iterator it = _elems.begin(); it != _elems.end(); ++it)
    cube[*it] = n;
}
//---------------------------------------------------------------------------

// пишем элемент в поток
std::ostream& operator<<(std::ostream &stream, const Item &item) {
  return item >> stream;
}
//---------------------------------------------------------------------------

// сравнивалка элементов
bool operator<(const Item &lh, const Item &rh) {
  return lh.Less(rh);
}
//---------------------------------------------------------------------------
