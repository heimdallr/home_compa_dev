#include <vcl.h>
#pragma hdrstop
#include "MainUnit.h"
#include "OptionsXML.h"
#include "ConnectImpl.h"
#include "Functions.h"
#include "DataSetLayout.h"
#include "DateUtils.hpp"
#include "DateInterval.h"
#include "GetStringUnit.h"
#include "DocUnit.h"
#include "DocStrUnit.h"
#include "GridUtils.h"
#include "AboutUnit.h"
#include "CatalogUnit.h"
#include "DBLoginUnit.h"
#include "ReportBase.h"
#include "Const.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "DBGridEhGrouping"
#pragma resource "*.dfm"
TfmMain *fmMain;
//---------------------------------------------------------------------------

// Конструктор
__fastcall TfmMain::TfmMain(TComponent* Owner) : TForm(Owner),
_to(IncDay(Today(), 7)), _from(IncMonth(Today(), -1)),
_opt(TOptionsXML::GetInstance(ChangeFileExt(GetModuleName(0), ".xml"))),
_con(TdmConnectImpl::GetInstance(GetConnectProperty(_opt.get()))),
_stock_action(alMain, "operation", &StockActionExecute, pmStock),
_doc(TDoc::GetInstance(_from, _to)), dsDoc(_doc->GetDataSet()),
_doc_str(TDocStr::GetInstance(dsDoc->FieldByName("id")->AsInteger)), dsDocStr(_doc_str->GetDataSet()),
_stock(TStock::GetInstance()), dsStock(_stock->GetDataSet()),
_safe_action(this), _person(ns_GridUtils::FindColumn(dbgStr, "TARGET_PERSON_NAME"))
{
  ActivateKeyboardLayout(LoadKeyboardLayout(IntToHex(MAKELANGID(LANG_RUSSIAN, SUBLANG_DEFAULT), 8).c_str(), 0), 0);
  dsrcDoc->DataSet = dsDoc;
  dsrcStock->DataSet = dsStock;
  dsrcStr->DataSet = dsDocStr;
  SetCaption();
  dsDoc->AfterScroll = dsDocAfterScroll;
  dbgDocTitleBtnClick(dbgDoc, 0, 0);
  dsDoc->First();
  dbgStrTitleBtnClick(dbgStr, 0, 0);
  dsDocStr->First();
  TReport::SetMenu(mmReport);
}
void __fastcall TfmMain::FormPaint(TObject *Sender) {
  OnPaint = 0;
  _opt->RestoreLayout(pnlRight);
  _opt->RestoreLayout(this);
  _opt->RestoreLayout(dbgDoc);
  _opt->RestoreLayout(dbgStr);
  _opt->RestoreLayout(dbgStock);
}
void __fastcall TfmMain::SetCaption() {
  lDateInterval->Caption = String().sprintf("Период с %s по %s", _from.FormatString("dd.mm.yyyy"), _to.FormatString("dd.mm.yyyy"));
  Caption = String().sprintf("Домашняя бухгалтерия. %s", lDateInterval->Caption);
}
TPropertyMap TfmMain::GetConnectProperty(TOptions *Opt) {
  TPropertyMap P(Opt->GetPropMap("Connect"));
  TDBLoginForm::Ptr LoginForm=TDBLoginForm::GetInstance(P);
  TModalResult Res=LoginForm->ShowModal();
  if(mrCancel==Res) throw Exception("");
  if(LoginForm->Changed(TDBLoginForm::pc_Host)) Opt->Set("Connect", "Host", P["Host"]);
  if(LoginForm->Changed(TDBLoginForm::pc_DatabaseName)) Opt->Set("Connect", "DatabaseName", P["DatabaseName"]);
  if(LoginForm->Changed(TDBLoginForm::pc_User)) Opt->Set("Connect", "User", P["User"]);
  if(LoginForm->Changed(TDBLoginForm::pc_Password) && mrYes==Res) Opt->Set("Connect", "Password", P["Password"]);
  if(LoginForm->Changed(TDBLoginForm::pc_CType)) Opt->Set("Connect", "CType", P["CType"]);
  P.Set("Role", "MONEY_OPER");
  return P;
}
//---------------------------------------------------------------------------

// О программе
void __fastcall TfmMain::actAboutExecute(TObject *Sender) {
  TAboutForm::GetInstance()->ShowModal();
}
//---------------------------------------------------------------------------

// Выход из программы
void __fastcall TfmMain::actExitExecute(TObject *Sender) {
  Close();
  _opt->SaveLayout(dbgDoc);
  _opt->SaveLayout(dbgStr);
  _opt->SaveLayout(dbgStock);
  _opt->SaveLayout(this);
  _opt->SaveLayout(pnlRight);
}
void __fastcall TfmMain::FormDestroy(TObject *Sender) {
  dsDoc->AfterScroll = 0;
  dsrcDoc->DataSet = 0;
  dsrcStock->DataSet = 0;
  dsrcStr->DataSet = 0;
}
//---------------------------------------------------------------------------

// Грузим данные
void __fastcall TfmMain::actLoadExecute(TObject *Sender) {
  _doc->Load();
}
//---------------------------------------------------------------------------

// Работаем с шапкой документа
void __fastcall TfmMain::StockActionExecute(TObject *Sender) {
  String Note="";
  TDate D=Date();
  if(mrOk!=TDocEditForm::Get(Note, D, dsStock->FieldByName("name")->AsString)) return;
  _doc->Add(dynamic_cast<TAction*>(Sender)->Tag, dsStock->FieldByName("id")->AsInteger, D, Note);
}
void __fastcall TfmMain::actEditDocExecute(TObject *Sender) {
  String Note=dsDoc->FieldByName("note")->AsString;
  TDate D=dsDoc->FieldByName("date_doc")->AsDateTime;
  if(mrOk!=TDocEditForm::Get(Note, D, String().sprintf("№%d, %s", dsDoc->FieldByName("id")->AsInteger, dsStock->FieldByName("name")->AsString))) return;
  _doc->Set(D, Note);
}
void __fastcall TfmMain::actAcceptExecute(TObject *Sender) {
  if(!dsDoc->FieldByName("state")->AsInteger || ID_YES==Application->MessageBox("Действительно отменить документ?", "Внимание!", MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2))
    _doc->Accept();
}
void __fastcall TfmMain::actDelDocExecute(TObject *Sender) {
  if(ID_YES==Application->MessageBox("Действительно удалить документ?", "Внимание!", MB_ICONWARNING|MB_YESNO|MB_DEFBUTTON2))
    _doc->Delete();
}
//---------------------------------------------------------------------------

// Крутим датасет с документами
void __fastcall TfmMain::dsDocAfterScroll(TDataSet *DataSet) {
  if(dsDoc->FieldByName("state")->AsInteger) ActionsEnable();
  else ActionsDisable();
}
void __fastcall TfmMain::ActionsEnable() {
  actAddStr->Enabled = false;
  actEditStr->Enabled = false;
  actEditDoc->Enabled = false;
  actDelDoc->Enabled = false;
  actDelStr->Enabled = false;
  actAccept->Caption = "Отмена проводки документа";
}
void __fastcall TfmMain::ActionsDisable() {
  actAddStr->Enabled = true;
  actEditStr->Enabled = true;
  actEditDoc->Enabled = true;
  actDelDoc->Enabled = true;
  actDelStr->Enabled = true;
  actAccept->Caption = "Проводка документа";
}
//---------------------------------------------------------------------------

// Показываем/прячем строки
void __fastcall TfmMain::dbgDocRowDetailPanelShow(TCustomDBGridEh *Sender, bool &CanShow) {
  _doc_str->Reload(dsDoc->FieldByName("id")->AsInteger);
  _person->FieldName = TConst::Instance()->Get("tsf")->AsInteger==dsDoc->FieldByName("id_doc_type")->AsInteger ? "DEPOSIT_TO_NAME" : "TARGET_PERSON_NAME";
  _person->Title->Caption = TConst::Instance()->Get("tsf")->AsInteger==dsDoc->FieldByName("id_doc_type")->AsInteger ? "Счет-приемник" : "Виновник";
}
void __fastcall TfmMain::actLeftExecute(TObject *Sender) {
  ns_GridUtils::LeftExecute(Sender, ActiveControl);
}
void __fastcall TfmMain::actRightExecute(TObject *Sender) {
  ns_GridUtils::RightExecute(Sender, ActiveControl);
}
//---------------------------------------------------------------------------

// Работаем со строками документов
void __fastcall TfmMain::actAddStrExecute(TObject *Sender) {
  if(!dbgDoc->RowDetailPanel->Visible) {
    dbgDoc->RowDetailPanel->Visible = true;
    dbgStr->SetFocus();
  }
  TDocStrEditForm::GetInstance(dsDoc, _doc_str)->ShowModal();
}
void __fastcall TfmMain::actEditStrExecute(TObject *Sender) {
  TDocStrEditForm::GetInstance(dsDoc, _doc_str, false)->ShowModal();
}
void __fastcall TfmMain::actDelStrExecute(TObject *Sender) {
  if(ID_YES == Application->MessageBox("Действительно удалить строку?", "Внимание!", MB_ICONWARNING|MB_YESNO|MB_DEFBUTTON2))
    _doc_str->Del();
}
//---------------------------------------------------------------------------

// Сортировка гридов
void __fastcall TfmMain::dbgDocTitleBtnClick(TObject *Sender, int ACol, TColumnEh *Column) {
  ns_GridUtils::Sort(Sender, Column, "date_doc;id", "date_doc;id");
}
void __fastcall TfmMain::dbgStrTitleBtnClick(TObject *Sender, int ACol, TColumnEh *Column) {
  ns_GridUtils::Sort(Sender, Column, "id");
}
//---------------------------------------------------------------------------

// Раскраска отрицательных сумм
void __fastcall TfmMain::dbgStockGetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont, TColor &Background, TGridDrawState State) {
  if(Column->FieldName=="SUMMA" && Column->Field->AsFloat<0) AFont->Color = clRed;
}
void __fastcall TfmMain::dbgGetFooterParams(TObject *Sender, int DataCol, int Row, TColumnEh *Column, TFont *AFont, TColor &Background, TAlignment &Alignment, TGridDrawState State, AnsiString &Text) {
  if(Column->FieldName=="SUMMA" && atof(StringReplace(StringReplace(Text, ",", ".", TReplaceFlags()<<rfReplaceAll), " ", "", TReplaceFlags()<<rfReplaceAll).c_str())<0.0) AFont->Color = clRed;
}
//---------------------------------------------------------------------------

// Меняем интервал дат
void __fastcall TfmMain::actChangeDateIntervalExecute(TObject *Sender) {
  if(!Sender || GetDateInterval(_from, _to, "Укажите интервал дат")) {
    _doc->Reload(_from, _to);
    SetCaption();
  }
}
void __fastcall TfmMain::lDateIntervalMouseEnter(TObject *Sender) {
  lDateInterval->Font->Style = TFontStyles()<<fsUnderline;
}
void __fastcall TfmMain::lDateIntervalMouseLeave(TObject *Sender) {
  lDateInterval->Font->Style = TFontStyles();
}
void __fastcall TfmMain::lDateIntervalClick(TObject *Sender) {
  actChangeDateInterval->OnExecute(actChangeDateInterval);
}
//---------------------------------------------------------------------------

// Показываем справочник
void __fastcall TfmMain::actShowCatalogExecute(TObject *Sender) {
  TCatalog::Ptr Cat=TCatalog::GetInstance("catalog_all");
  Cat->Collapse();
  Cat->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::FormActivate(TObject *Sender) {
  actLeft->Enabled = true;
  actRight->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::FormDeactivate(TObject *Sender) {
  actLeft->Enabled = false;
  actRight->Enabled = false;
}
//---------------------------------------------------------------------------

// Задуплить строку
void __fastcall TfmMain::actMulExecute(TObject *Sender) {
  if(!dbgDoc->RowDetailPanel->Visible) return;
  if(_doc->GetDataSet()->FieldByName("state")->AsInteger) return;
  if(!dbgStr->Focused()) return;
  if(!_doc_str->GetDataSet()->RecordCount) return;
  _doc_str->Duplicate();
}
//---------------------------------------------------------------------------

