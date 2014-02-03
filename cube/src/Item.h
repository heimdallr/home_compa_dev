#ifndef ItemH
#define ItemH
//---------------------------------------------------------------------------
#include <set>
#include <vector>

class Item {
  typedef std::set<int> Elems;
  Elems _elems;

  typedef std::vector<int> Array;
  typedef std::vector<Array> Arrays;
  class Matrix {
    int _dim;
    Array _data;
  public:
    Matrix(int dim, int *data);
    void Multiply(const Elems &src, Elems &dst) const;
    Array ToArray(int);
    static int ToInt(const Array &array);
  };

public:
  Item& operator<<(int elem) {_elems.insert(elem); return *this;}
  Item RoundUp() const;
  Item RoundDown() const;
  Item RoundLeft() const;
  Item RoundRight() const;
  Item RoundClockwise() const;
  Item RoundCounterClockwise() const;
};
//---------------------------------------------------------------------------
#endif
