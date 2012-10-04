//---------------------------------------------------------------------------

#ifndef dataH
#define dataH
#include <ExtCtrls.hpp>
#include <memory>
#include "indicator.h"
#include "fig_gen.h"
//---------------------------------------------------------------------------

// Команды стакану
enum EMove {
  e_Left=1,
  e_Right,
  e_Down,
  e_Up,
  e_Rotate,
  e_LRotate,
  e_MoveLast,
  e_ClearStat
};

//---------------------------------------------------------------------------

// Результат сдвига фигуры
enum EFigMove {
  e_Moved=0,
  e_Bottom,
  e_Crash
};
//---------------------------------------------------------------------------

// Стакан
class TTetris {
  TfmIndicator *_ind;
  TCanvas *_cnv, *_nxt;
  int _n, _N, _M, _n0, _count, *_row, _size, _id_next_fig_cheat;
  TItem **_data;
  std::auto_ptr<TFigure> _fig, _fig0;
  TIntVector _line, _move_count;
  void __fastcall Set(TItem&, bool mode=false);
  void __fastcall Set(bool mode=false);
  EFigMove __fastcall MoveFig(TPos&);
  unsigned int __fastcall Blast();
  void __fastcall Rotate(int dir=1);
  void __fastcall Preview();
  void __fastcall SetView();
  void __fastcall Paint();
public:
  __fastcall TTetris(int, TfmIndicator*);
  __fastcall ~TTetris();
  bool __fastcall Recount();
  void __fastcall Move(EMove);
  void __fastcall Reset();
  void __fastcall Save(const String&);
  void __fastcall Load(const String&);
  void __fastcall SetNextFigCheat(int id) {_id_next_fig_cheat=id;}
};
//---------------------------------------------------------------------------
int __fastcall GetCheckSum(FILE*, int pos=0);
#endif
