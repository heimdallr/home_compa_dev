//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <set>
#include <queue>
#include "ReportBase.h"
#include "CatalogUnit.h"
#include "DateInterval.h"
#include "Options.h"
#include "Const.h"
#include "DataSetLayout.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"

TfmReportBase::TReportListInserter::TReportListInserter(const String &Caption, TReportGetInstanceFunc F) {
  TfmReportBase::TReportList &R = TfmReportBase::GetReportList();
  R.push_back(TReportItem(Caption, F));
}
//---------------------------------------------------------------------------

// Конструктор базовой формы отчетов
__fastcall TfmReportBase::TfmReportBase(TDate From, TDate To)
  : TForm(static_cast<TComponent*>(0)), _from(From), _to(To), _safe_action(this), _id_interval(0)
{
  lDateInterval->Caption = String().sprintf("Период с %s по %s", _from.FormatString("dd.mm.yyyy"), _to.FormatString("dd.mm.yyyy"));
  ChangeDateIntervalTypeExecute(TCatalog::GetDataSet("date_interval_type").get(), false);
}
void __fastcall TfmReportBase::FormPaint(TObject *Sender) {
  OnPaint = 0;
  TOptions::Instance->RestoreLayout(this);
  actRunReport->OnExecute(actRunReport);
}
TfmReportBase::TReportList& __fastcall TfmReportBase::GetReportList() {
  static TReportList ReportList;
  return ReportList;
}
void __fastcall TfmReportBase::actCloseExecute(TObject *Sender) {
  Close();
}
void __fastcall TfmReportBase::FormClose(TObject *Sender, TCloseAction &Action) {
  Action = caFree;
}
void __fastcall TfmReportBase::FormDestroy(TObject *Sender) {
  TOptions::Instance->SaveLayout(this);
}
//---------------------------------------------------------------------------

// Генерим случайный цвет
TColor __fastcall TfmReportBase::GetColor(int K) {
  int N=255/(K-1);
  TColor Res = TColor((random(K)*N) | ((random(K)*N)<<8) | ((random(K)*N)<<16));
  return static_cast<int>(Res)&&static_cast<int>(Res)!=0xffffff ? Res : GetColor();
}
//---------------------------------------------------------------------------

// Работаем с датами
void __fastcall TfmReportBase::lMouseEnter(TObject *Sender) {
  dynamic_cast<TLabel*>(Sender)->Font->Style = TFontStyles()<<fsUnderline;
}
void __fastcall TfmReportBase::lMouseLeave(TObject *Sender) {
  dynamic_cast<TLabel*>(Sender)->Font->Style = TFontStyles();
}
void __fastcall TfmReportBase::lDateIntervalClick(TObject *Sender) {
  actChangeDateInterval->OnExecute(actChangeDateInterval);
}
void __fastcall TfmReportBase::actChangeDateIntervalExecute(TObject *Sender) {
  if(!GetDateInterval(_from, _to, "Укажите интервал дат")) return;
  lDateInterval->Caption = String().sprintf("Период с %s по %s", _from.FormatString("dd.mm.yyyy"), _to.FormatString("dd.mm.yyyy"));
  actRunReport->OnExecute(actRunReport);
}
//---------------------------------------------------------------------------

// Меняем тип интервала дат
void __fastcall TfmReportBase::actChangeDateIntervalTypeExecute(TObject *Sender) {
  ChangeDateIntervalTypeExecute(TCatalog::Get("date_interval_type").get());
}
void __fastcall TfmReportBase::ChangeDateIntervalTypeExecute(TClientDataSet *Data, bool R) {
  if(!Data) return;
  _id_interval = Data->FieldByName("id")->AsInteger;
  lDateIntervalType->Caption = String().sprintf("Группировка в интервале: %s", Data->FieldByName("name")->AsString);
  if(R) Run();
}
void __fastcall TfmReportBase::lDateIntervalTypeClick(TObject *Sender) {
  actChangeDateIntervalType->OnExecute(actChangeDateIntervalType);
}
//---------------------------------------------------------------------------

// Заполняем присланное извне меню
void __fastcall TfmReportBase::SetMenu(TMenuItem *ReportMenuParentItem) {
  TReportList &R=GetReportList();
  for(unsigned int i=0; i<R.size(); ++i) {
    TMenuItem *Item = new TMenuItem(ReportMenuParentItem);
    Item->Tag = i;
    Item->Caption = R[i].first;
    Item->OnClick = TReportLauncher::GetInstance()->OnClick;
    ReportMenuParentItem->Add(Item);
  }
}
//---------------------------------------------------------------------------

// Отдаем простую читающую транзакцию
TIBTransaction* __fastcall InitCatalogTransaction() {
  static std::auto_ptr<TIBTransaction> T(new TIBTransaction(0));
  T->Params->Clear();
  T->Params->Add("read");
  T->Params->Add("read_committed");
  T->Params->Add("rec_version");
  T->DefaultDatabase = TConnect::Instance->GetReadSQL("", false)->Database;
  return T.get();
}
TIBTransaction* __fastcall TfmReportBase::GetCatalogTransaction() {
  static TIBTransaction *T=InitCatalogTransaction();
  return T;
}
//---------------------------------------------------------------------------


// Работаем со справочниками
void __fastcall TfmReportBase::dsCatalogAfterPost(TDataSet *DataSet) {
  actRunReport->OnExecute(actRunReport);
}
void __fastcall TfmReportBase::LoadCatalog(TClientDataSet *Data, const String &ParentName, bool AddAll) {
  TQueryParams P(ftInteger, "id_p", TConst::Instance()->Get(ParentName)->AsInteger);
  P.Add(ftInteger, "add_all", AddAll ? 1 : 0);
  Data->Data = TConnect::Instance->GetReadDataSet("select * from sel_catalog_gtt(:id_p, :add_all)", P, GetCatalogTransaction())->Data;
}
void __fastcall TfmReportBase::SaveCatalog(TClientDataSet *Data, const String &ParentName, bool FullMode) {
  TSQLPtr SQL = TConnect::Instance->GetReadSQL("execute procedure add_catalog_gtt(:id_p, :id)", false, GetCatalogTransaction());
  SQL->ParamByName("id_p")->AsInteger = TConst::Instance()->Get(ParentName)->AsInteger;
  if(FullMode) {
    SQL->ParamByName("id")->Clear();
    SQL->ExecQuery();
  }
  else {
    TDataSetLayout DSL(Data);
    TDataSetFilter<TClientDataSet> DSF(Data, "checked=1");
    std::set<int> Set;
    std::queue<int> Queue;
    for(Data->First(); !Data->Eof; Data->Next()) {
      SQL->ParamByName("id")->AsInteger = Data->FieldByName("id")->AsInteger;
      SQL->ExecQuery();
      Set.insert(Data->FieldByName("id")->AsInteger);
      Queue.push(Data->FieldByName("id")->AsInteger);
    }
    Data->Filtered = false;
    while(!Queue.empty()) {
      int Id=Queue.front();
      Queue.pop();
       if(Data->Locate("id", Id, TLocateOptions())) {
        if(Set.end()==Set.find(Data->FieldByName("id_p")->AsInteger)) {
          SQL->ParamByName("id")->AsInteger = Data->FieldByName("id_p")->AsInteger;
          SQL->ExecQuery();
          Set.insert(Data->FieldByName("id_p")->AsInteger);
          Queue.push(Data->FieldByName("id_p")->AsInteger);
        }
      }
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmReportBase::actRunReportExecute(TObject *Sender) {
  SaveCatalog();
  Run();
  LoadCatalog();
}
//---------------------------------------------------------------------------

