#ifndef DocH
#define DocH
#include "DataImpl.h"
//---------------------------------------------------------------------------
class TDoc : public TDataImpl {
static const String SelectQuery, AcceptQuery, AddQuery, SetQuery, DeleteQuery;
  bool _flag;
  __fastcall TDoc(TDate From, TDate To, TIBTransaction *T=0);
public:
typedef boost::shared_ptr<TDoc> Ptr;
static Ptr GetInstance(TDate From, TDate To, TIBTransaction *T=0) {return Ptr(new TDoc(From, To, T));}
  void __fastcall Accept();
  void __fastcall Delete();
  int __fastcall Add(int IdDocType, int IdDeposit, TDate DateDoc, const String &Note);
  void __fastcall Set(TDate DateDoc, const String &Note);
  void __fastcall Reload(TDate From, TDate To);
};
//---------------------------------------------------------------------------
#endif
