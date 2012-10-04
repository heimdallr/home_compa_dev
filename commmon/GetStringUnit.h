//---------------------------------------------------------------------------

#ifndef GetStringUnitH
#define GetStringUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <boost/regex.hpp>
//---------------------------------------------------------------------------
class TfmGetString : public TForm {
__published:	// IDE-managed Components
  TEdit *eVal;
  TActionList *alMain;
  TAction *actOk;
  TAction *actCancel;
  void __fastcall actCancelExecute(TObject *Sender);
  void __fastcall actOkExecute(TObject *Sender);
private:	// User declarations
  String &_val;
  const boost::regex _condition;
  boost::cmatch _what;
public:		// User declarations
  __fastcall TfmGetString(String &Val, const String &Capt, const String &Condition);
};
//---------------------------------------------------------------------------
bool __fastcall GetString(String &Val, const String &Capt, const String &Condition=".*?");
#endif
