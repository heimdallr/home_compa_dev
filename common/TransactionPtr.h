#ifndef TransactionPtrH
#define TransactionPtrH
class TTranPtr {
  TIBTransaction *_t;
public:  
  __fastcall TTranPtr(TIBTransaction *T) : _t(T) {if(!_t->Active) _t->StartTransaction();}
  __fastcall ~TTranPtr() {if(_t->Active) _t->Rollback();}
};
#endif
