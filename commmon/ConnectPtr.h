#ifndef ConnectPtrH
#define ConnectPtrH
//---------------------------------------------------------------------------

template <class T>
class TConnectPtr {
  T *_p;
public:
  __fastcall template<class T> TConnectPtr(T *p) : _p(p) {_p->Connect();}
  __fastcall ~TConnectPtr() {_p->Disconnect();}
};
//---------------------------------------------------------------------------

template <class T>
class TOpenPtr {
  T *_p;
public:
  __fastcall template<class T> TOpenPtr(T *p) : _p(p) {_p->Open();}
  __fastcall ~TOpenPtr() {_p->Close();}
};
//---------------------------------------------------------------------------

template <class T>
class TExecQueryPtr {
  T *_p;
public:
  __fastcall template<class T> TExecQueryPtr(T *p) : _p(p) {_p->ExecQuery();}
  __fastcall ~TExecQueryPtr() {_p->Close();}
};
//---------------------------------------------------------------------------
#endif