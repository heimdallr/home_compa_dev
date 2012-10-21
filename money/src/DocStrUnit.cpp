#include <vcl.h>
#pragma hdrstop
#include <math.h>
#include "DocStrUnit.h"
#include "Const.h"
#include "Options.h"
#include "GridUtils.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "MemTableDataEh"
#pragma link "MemTableEh"
#pragma link "DBCtrlsEh"
#pragma link "DBGridEh"
#pragma link "DBLookupEh"
#pragma link "DataDriverEh"
#pragma link "DBGridEhGrouping"
#pragma link "GridsEh"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

// Конструктор
__fastcall TfmDocStr::TfmDocStr(TClientDataSet *Doc, TDocStr::Ptr DocStr, bool NewStr) : TForm(static_cast<TComponent*>(0)),
_doc(Doc), _doc_str(DocStr),
_new_str(NewStr), _str_type_cat(static_cast<TCatalog*>(0)),
_safe_action(this),
_tsf_mode(Doc->FieldByName("id_doc_type")->AsInteger==TConst::Instance()->Get("tsf")->AsInteger),
_def_target(TConst::Instance()->Get("pay_target_def")->AsInteger)
{
  dsTarget->Data = TCatalog::GetDataSet(_tsf_mode ? "deposit" : "pay_target")->Data;
  gbTarget->Caption = _tsf_mode ? "Счет-получатель" : "\"Виновник\" финансового потока";
  if(_tsf_mode) {
    eQty->Enabled = false;
    if(dsTarget->Locate("id", Doc->FieldByName("id_deposit")->AsInteger, TLocateOptions()))
      dsTarget->Delete();
  }
  lcbTarget->KeyValue = _def_target;
  TDSPtr DS(static_cast<TClientDataSet*>(0));

  _str_type_cat = TCatalog::GetInstance(_doc->FieldByName("id_doc_type")->AsInteger);
  _str_type_cat->GetCatalogGrid()->Parent = pnlType;

  dsSumma->CreateDataSet();
  dsSumma->LogChanges = false;
  dsSumma->Append();
  dsSummaSumma->AsCurrency = 0;
  dsSummaQty->AsFloat = 1;
  dsSumma->Post();

  InitNewEdit();
}
void __fastcall TfmDocStr::FormPaint(TObject *Sender) {
  OnPaint = 0;
  TOptions::Instance->RestoreLayout(this);
}
void __fastcall TfmDocStr::FormResize(TObject *Sender) {
  pnlSumma->Width = pnlSumma->Parent->Width / 2;
}
void __fastcall TfmDocStr::actCancelExecute(TObject *Sender) {
  Close();
}
void __fastcall TfmDocStr::FormDestroy(TObject *Sender) {
  TOptions::Instance->SaveLayout(this);
}
//---------------------------------------------------------------------------

// Инициализация. Новая или редактируем?
void __fastcall TfmDocStr::InitNewEdit() {
  dsSumma->Append();
  if(_new_str) {
    Caption = "Новая строка";
    actOk->OnExecute = StrNew;
    dsSummaSumma->AsCurrency = 0;
    dsSummaQty->AsFloat = 1;
    if(Visible)
      eNote->SetFocus();
  }
  else {
    Caption = "Редактирование строки";
    actOk->OnExecute = StrEdit;
    eNote->Text = _doc_str->GetDataSet()->FieldByName("note")->AsString;
    dsSummaSumma->AsCurrency = _doc_str->GetDataSet()->FieldByName("summa")->AsCurrency * _doc->FieldByName("doc_type_coef")->AsFloat;
    dsSummaQty->AsFloat = _doc_str->GetDataSet()->FieldByName("qty")->AsFloat;
    lcbTarget->KeyValue = _tsf_mode ? _doc_str->GetDataSet()->FieldByName("id_deposit_to")->AsInteger : _doc_str->GetDataSet()->FieldByName("id_target_person")->AsInteger;
    _str_type_cat->Locate(_doc_str->GetDataSet()->FieldByName("id_str_type")->AsInteger);
  }
  dsSumma->Post();
}
//---------------------------------------------------------------------------

// Регулярный платеж? Сумма известна?
void __fastcall TfmDocStr::eSummaEnter(TObject *Sender) {
  if(_str_type_cat->FieldByName("qty")->AsFloat<0.01) return;
  dsSumma->Edit();
  dsSummaSumma->AsFloat = _str_type_cat->FieldByName("qty")->AsFloat;
  dsSumma->Post();
}
//---------------------------------------------------------------------------

void __fastcall TfmDocStr::GetTarget(int &IdTarget, int &IdDeposit) {
  IdTarget = _tsf_mode ? _def_target : dsTarget->FieldByName("id")->AsInteger;
  IdDeposit = _tsf_mode && lcbTarget->KeyValue==dsTarget->FieldByName("id")->AsInteger ? dsTarget->FieldByName("id")->AsInteger : 0;
}
//---------------------------------------------------------------------------

// Запоминаем сумму по умолчанию
void __fastcall TfmDocStr::actSetQtyExecute(TObject *Sender) {
  TCatalog::SetCatalogQty(_str_type_cat->FieldByName("id")->AsInteger, dsSummaSumma->AsFloat);
}
//---------------------------------------------------------------------------

// Вышли из поля с суммой - запомнили
void __fastcall TfmDocStr::eSummaExit(TObject *Sender) {
  if(dsSumma->State==dsEdit) dsSumma->Post();
}
//---------------------------------------------------------------------------

// Нажали Enter на сумме - пишем (если не ноль, конечно)
void __fastcall TfmDocStr::eSummaKeyPress(TObject *Sender, char &Key) {
  if(VK_RETURN==Key) {
    SelectNext(dynamic_cast<TWinControl*>(Sender), true, true);
    if(fabs(dsSummaSumma->AsFloat)<0.01) {
      SelectNext(ActiveControl, false, true);
      return;
    }
    return actOk->OnExecute(actOk);
  }
  if(','==Key || '.'==Key || '/'==Key || 'б'==Key || 'ю'==Key)
    Key=DecimalSeparator;
}
//---------------------------------------------------------------------------

// Нажали Enter - идем в следующий Control
void __fastcall TfmDocStr::eQtyKeyPress(TObject *Sender, char &Key) {
  if(VK_RETURN==Key) SelectNext(ActiveControl, true, true);
}
//---------------------------------------------------------------------------

// Пишем новую
void __fastcall TfmDocStr::actOkNewExecute(TObject *Sender) {
  if(dsSumma->State==dsEdit) dsSumma->Post();
  if(fabs(dsSummaSumma->AsFloat)<0.01) return;
  int IdTarget, IdDeposit;
  GetTarget(IdTarget, IdDeposit);
  if(eNote->Text.IsEmpty()) eNote->Text = _str_type_cat->FieldByName("name")->AsString;
  _doc_str->Add(_str_type_cat->FieldByName("id")->AsInteger, IdTarget, dsSummaSumma->AsFloat, dsSummaQty->AsFloat, eNote->Text, IdDeposit);
  InitNewEdit();
}
//---------------------------------------------------------------------------

// Пишем отредактированную
void __fastcall TfmDocStr::actOkEditExecute(TObject *Sender) {
  if(dsSumma->State==dsEdit) dsSumma->Post();
  if(fabs(dsSummaSumma->AsFloat)<0.01) return;
  int IdTarget, IdDeposit;
  GetTarget(IdTarget, IdDeposit);
  _doc_str->Set(_str_type_cat->FieldByName("id")->AsInteger, IdTarget, dsSummaSumma->AsFloat, dsSummaQty->AsFloat, eNote->Text, IdDeposit);
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TfmDocStr::actLeftExecute(TObject *Sender) {
  ns_GridUtils::LeftExecute(Sender, ActiveControl);
}
void __fastcall TfmDocStr::actRightExecute(TObject *Sender) {
  ns_GridUtils::RightExecute(Sender, ActiveControl);
}
//---------------------------------------------------------------------------

// Задуплить количество
void __fastcall TfmDocStr::actMulExecute(TObject *Sender) {
  dsSumma->Edit();
  dsSummaQty->AsInteger *= 2;
  dsSummaSumma->AsFloat *= 2.0;
  dsSumma->Post();

}
//---------------------------------------------------------------------------

