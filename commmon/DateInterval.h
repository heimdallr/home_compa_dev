//---------------------------------------------------------------------------

#ifndef DateIntervalH
#define DateIntervalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfmDates : public TForm
{
__published:	// IDE-managed Components
    TPanel *pnlButton;
    TPanel *pnlDate;
    TPanel *pnlFrom;
    TMonthCalendar *mcFrom;
    TPanel *pnlTo;
    TMonthCalendar *mcTo;
    TActionList *ActionList1;
    TBitBtn *btnOk;
    TBitBtn *btnCancel;
    TAction *actOk;
    TAction *actCancel;
    void __fastcall actCancelExecute(TObject *Sender);
    void __fastcall actOkExecute(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall mcFromClick(TObject *Sender);
    void __fastcall mcToClick(TObject *Sender);
private:	// User declarations
    TDateTime &m_dtFrom, &m_dtTo;
public:		// User declarations
    __fastcall TfmDates(TDateTime &dtFrom, TDateTime &dtTo, String strTitle, TDateTime dtMinDate, TDateTime dtMaxDate);
};
//---------------------------------------------------------------------------
bool GetDateInterval(TDateTime &From, TDateTime &To, String FormCaption="Укажите интервал дат", TDateTime MinDate=0, TDateTime MaxDate=99999);
#endif
