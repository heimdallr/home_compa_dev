#ifndef DocStrH
#define DocStrH
#include "DataImpl.h"
//---------------------------------------------------------------------------

class TDocStr : public TDataImpl {
static const String SelectQuery, AddQuery, SetQuery, DelQuery;
  int _id_doc;
  __fastcall TDocStr(int IdDoc, TIBTransaction *T=0);
  void __fastcall SetParam(TIBSQL *SQL, int IdType, int IdTarget, double Summa, double Qty, const String &Note, int IdDeposit) const;
public:
typedef boost::shared_ptr<TDocStr> Ptr;
static Ptr GetInstance(int IdDoc, TIBTransaction *T=0) {return Ptr(new TDocStr(IdDoc, T));}
  void __fastcall Delete();
  void __fastcall Reload(int IdDoc);
  int __fastcall Add(int IdType, int IdTarget, double Summa, double Qty, const String &Note, int IdDeposit);
  void __fastcall Set(int IdType, int IdTarget, double Summa, double Qty, const String &Note, int IdDeposit) const;
  void __fastcall Del() const;
};
//---------------------------------------------------------------------------
#endif
