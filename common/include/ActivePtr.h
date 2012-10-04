#ifndef ActivePtrH
#define ActivePtrH
//---------------------------------------------------------------------------

// Храним признак активности
template<class T>
class TActivePtr{
  T *_p;
  bool _active;
public:
  __fastcall TActivePtr(T *P, bool Active) : _p(P) {_active=_p->Active; _p->Active=Active;}
  __fastcall ~TActivePtr() {_p->Active=_active;}
};
//---------------------------------------------------------------------------
template <typename T>
class TActiveSet {
  T *_p;
  bool _a;
public:
  __fastcall TActiveSet(T *P, bool A=false) : _p(P), _a(A) {_p->Active=A;}
  __fastcall ~TActiveSet() {_p->Active=!_a;}
};
//---------------------------------------------------------------------------
#endif