#ifndef CoInitH
#define CoInitH
#include <objbase.h>
class TCoInit {
public:
  __fastcall TCoInit() {CoInitialize(NULL);}
  __fastcall ~TCoInit() {}
};
#endif
