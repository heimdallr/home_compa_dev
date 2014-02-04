#ifndef ItemH
#define ItemH
//---------------------------------------------------------------------------
#include <set>
#include <vector>
#include <iostream>

class Item {
  typedef std::set<int> Elems;
  Elems _elems;

  typedef std::vector<int> Array;
  typedef std::vector<Array> Arrays;
  class Matrix {
    static const int Dim = 3;
    Array _data;

    Array Multiply(const Array &array) const;
    static void Normalize(Arrays &arrays);
  public:
    static Array ToArray(int val);
    static int ToInt(const Array &array);
    Matrix(const int *data);
    void Multiply(const Elems &src, Elems &dst) const;
  };

  Item Round(const Matrix &matrix) const;

public:
  std::ostream& operator>>(std::ostream &stream) const;
  Item& operator<<(int elem);
  Item RoundUp() const;
  Item RoundDown() const;
  Item RoundLeft() const;
  Item RoundRight() const;
  Item RoundClockwise() const;
  Item RoundCounterClockwise() const;
};

std::ostream& operator<<(std::ostream &stream, const Item &item) {
  return item >> stream;
}

//---------------------------------------------------------------------------
#endif
