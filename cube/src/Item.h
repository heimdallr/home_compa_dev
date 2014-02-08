#ifndef ItemH
#define ItemH
//---------------------------------------------------------------------------
#include <set>
#include <vector>
#include <iostream>

#include "Matrix.h"
#include "Utils.h"
//---------------------------------------------------------------------------

// Класс элемент
class Item {
public:
typedef std::vector<Item> Items;
typedef std::vector<Items> Storage;
typedef std::set<Item> UniqueItems;

private:
  int _id;      // номер элемента
  Elems _elems; // состав элемента
  Array _size;  // размеры элемента по направлениям

  // порождаем новый элемент умножением подэлементов на указанную матрицу
  Item Round(const Matrix &matrix) const;
  // порождаем набор элементов посредством вращения в одной плоскости и всевозможных параллельных переносов
  void FillItemRound(UniqueItems &items) const;
  // Вычисляем размеры элемента (устанавливаем _size)
  void CountSize();

  // объект-коллбек для генерации новых объектов перебором всех линейных сдвигов
  // все положения разрешены, уведомления не нужны
  struct CheckFillItemMoves : public CheckBase {
    const Item &_item;
    Items &_items;
    // найденные элементы тупо кладем в контейнер
    CheckFillItemMoves(const Item &item, Items &items) : _item(item), _items(items) {}
    void Ready(const Array &array) {
      _items.push_back(_item.Move(array));
    }
  };

public:
  // конструктор
  explicit Item(int id);
  // пишем элемент в поток
  std::ostream& operator>>(std::ostream &stream) const;
  // добавляем точку в элемент
  Item& operator<<(int elem);

  // порождаем новые элементы преобразованием
  // сдвиг
  Item Move(const Array &offset) const;
  // всякие вращения
  Item RoundUp() const;
  Item RoundDown() const;
  Item RoundLeft() const;
  Item RoundRight() const;
  Item RoundClockwise() const;
  Item RoundCounterClockwise() const;
  // заполняем контейнер всеми возможными положениями элемента в фигуре
  void FillItems(Items &items) const;
  // заполняем контейнер всеми возможными сдвигами элемента в фигуре
  void FillItemMoves(Items &items) const;
  // сравнивалка элементов
  bool Less(const Item &rh) const;
  // проверяем элемент на возможность добавить его в (частично уже занятый) куб
  bool Check(const Array &cube) const;
  // добавдобавляем (удаляем) элемент в куб
  void SetToCube(Array &cube, int n) const;
};
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
#endif
