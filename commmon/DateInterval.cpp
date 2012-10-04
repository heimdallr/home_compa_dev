//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "DateInterval.h"
#include <memory>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

// Возвращаем интервал дат
bool GetDateInterval(TDateTime &From, TDateTime &To, String FormCaption, TDateTime MinDate, TDateTime MaxDate){
  std::auto_ptr<TfmDates> fmDates(new TfmDates(From, To, FormCaption, MinDate, MaxDate));
  return mrOk==fmDates->ShowModal();
}
//---------------------------------------------------------------------------

__fastcall TfmDates::TfmDates(TDateTime &dtFrom, TDateTime &dtTo, String strTitle, TDateTime dtMinDate, TDateTime dtMaxDate) : TForm((TComponent*)NULL), m_dtTo(dtTo), m_dtFrom(dtFrom){
  Caption = strTitle;
  if(int(dtMinDate)){
    mcFrom->Date = dtMinDate;
    mcTo->Date = dtMinDate;
    mcFrom->MinDate = dtMinDate;
    mcTo->MinDate = dtMinDate;
  }
  if(int(dtMaxDate)){
    mcFrom->MaxDate = dtMaxDate;
    mcTo->MaxDate = dtMaxDate;
  }
  mcFrom->Date = int(m_dtFrom<dtMinDate ? dtMinDate : m_dtFrom>dtMaxDate ? dtMaxDate : m_dtFrom);
  mcTo->Date = int(m_dtTo<dtMinDate ? dtMinDate : m_dtTo>dtMaxDate ? dtMaxDate : m_dtTo);
  mcTo->MinDate = int(mcFrom->Date);
  mcFrom->MaxDate = int(mcTo->Date);
}
//---------------------------------------------------------------------------
void __fastcall TfmDates::actCancelExecute(TObject *Sender){
  Close();
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TfmDates::actOkExecute(TObject *Sender){
  m_dtFrom = int(mcFrom->Date);
  m_dtTo = int(mcTo->Date);
  Close();
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfmDates::mcFromClick(TObject *Sender){
  if(mcFrom->Date>mcFrom->MaxDate)
    mcFrom->Date=mcFrom->MaxDate;
  mcTo->MinDate = mcFrom->Date;
}
//---------------------------------------------------------------------------
void __fastcall TfmDates::mcToClick(TObject *Sender){
  if(mcTo->Date<mcTo->MinDate)
    mcTo->Date=mcTo->MinDate;
  mcFrom->MaxDate = mcTo->Date;
}
//---------------------------------------------------------------------------
void __fastcall TfmDates::FormShow(TObject *Sender){
  pnlFrom->BorderWidth = 0.5*btnOk->Height;
  mcFrom->Left = pnlFrom->BorderWidth+1;
  mcFrom->Top = pnlFrom->BorderWidth+1;
  pnlFrom->AutoSize = true;
  pnlTo->BorderWidth = pnlFrom->BorderWidth;
  mcTo->Left = pnlTo->BorderWidth+1;
  mcTo->Top = pnlTo->BorderWidth+1;
  pnlTo->AutoSize = true;
  pnlTo->Left = pnlFrom->Width;
  pnlDate->AutoSize = true;
  pnlButton->Top = pnlDate->Height;
  pnlButton->Width = pnlDate->Width;
  pnlButton->Height = 1.5*btnOk->Height;
  btnOk->Left = (pnlButton->Width-2*btnOk->Width)/3;
  btnCancel->Left = pnlButton->Width-btnCancel->Width-btnOk->Left;
  AutoSize = true;
}
//---------------------------------------------------------------------------

