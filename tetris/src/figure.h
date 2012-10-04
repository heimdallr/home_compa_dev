//---------------------------------------------------------------------------
#ifndef figureH
#define figureH
//---------------------------------------------------------------------------
#include <list>
#include <vector>
#include "FilePtr.h"

typedef std::pair<bool, bool> TItem;
typedef std::pair<int, int> TPos;
typedef std::list<TPos> TPosList;
typedef TPosList::const_iterator TPosIt;
//---------------------------------------------------------------------------

// ������ �������
class TFigure {
protected:
  TPos _pos;
  TPosList _items;
  int _id;
public:
  // ���������������
  __fastcall TFigure(int id, const TPos&, const TPosList&);
  virtual __fastcall ~TFigure();

  // Get-set ������
  int __fastcall GetId() const {return _id;}
  const TPos& __fastcall GetPos() const {return _pos;}
  const TPosList& __fastcall GetItems() const {return _items;}
  void __fastcall SetPos(const TPos &pos) {_pos=pos;}

  // ��������� ������
  bool __fastcall Exists(const TPos&, const TPos&);
  void __fastcall Rotate(int dir=1);

  // ����������� ������
  virtual bool __fastcall OnBottom(int size, TItem**, int&) {return false;}
};
//---------------------------------------------------------------------------

// ������ ���������
class TFigureCrash : public TFigure {
public:
  __fastcall TFigureCrash(int id, const TPos &pos, const TPosList &items) : TFigure(id, pos, items) {}
  virtual __fastcall ~TFigureCrash(){}
  virtual bool __fastcall OnBottom(int size, TItem**, int&);
};
//---------------------------------------------------------------------------

TFigure* __fastcall GetTFigure(int id, const TPos &pos, const TPosList &items) {return new TFigure(id, pos, items);}
TFigure* __fastcall GetTFigureCrash(int id, const TPos &pos, const TPosList &items) {return new TFigureCrash(id, pos, items);}
//---------------------------------------------------------------------------

#endif
