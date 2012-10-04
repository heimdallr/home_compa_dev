#ifndef ReportLauncherH
#define ReportLauncherH
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------

#include <memory>
#include "SafeAction.h"
//---------------------------------------------------------------------------

class TdmReportLauncher : public TDataModule {
__published:	// IDE-managed Components
  TActionList *alMain;
  TAction *actRun;
  void __fastcall actRunExecute(TObject *Sender);
private:	// User declarations
typedef std::auto_ptr<TdmReportLauncher> Ptr;
  unsigned int _id;
  TSafeAction _safe_action;
  __fastcall TdmReportLauncher();
public:		// User declarations
static TdmReportLauncher* __fastcall GetInstance();
  void __fastcall OnClick(TObject *Sender);
};
typedef TdmReportLauncher TReportLauncher;
//---------------------------------------------------------------------------
#endif
