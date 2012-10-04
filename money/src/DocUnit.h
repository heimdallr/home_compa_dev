#ifndef DocUnitH
#define DocUnitH
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <memory>
//---------------------------------------------------------------------------

class TfmDoc : public TForm {
__published:	// IDE-managed Components
  TGroupBox *gbNote;
  TPanel *pnlNote;
  TEdit *eNote;
  TMonthCalendar *dtDate;
  TPanel *pnlBtn;
  TBitBtn *btnOk;
  TBitBtn *btnCancel;
  TActionList *ActionList1;
  TAction *actOk;
  TAction *actCancel;
  void __fastcall actCancelExecute(TObject *Sender);
  void __fastcall actOkExecute(TObject *Sender);
private:	// User declarations
  String &_note;
  TDate &_date;
  __fastcall TfmDoc(String &Note, TDate &D, const String &C);
public:		// User declarations
static TModalResult __fastcall Get(String &Note, TDate &D, const String &C) {return std::auto_ptr<TfmDoc>(new TfmDoc(Note, D, C))->ShowModal();}
};
typedef TfmDoc TDocEditForm;
//---------------------------------------------------------------------------

#endif
