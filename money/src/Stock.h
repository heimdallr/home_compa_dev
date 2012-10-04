#ifndef StockH
#define StockH
#include "DataImpl.h"
//---------------------------------------------------------------------------
class TStock : public TDataImpl {
static const String SelectQuery;
  __fastcall TStock();
public:
typedef boost::shared_ptr<TStock> Ptr;
static Ptr GetInstance() {return Ptr(new TStock());}
};
//---------------------------------------------------------------------------
#endif
