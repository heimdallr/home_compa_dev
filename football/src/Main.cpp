//---------------------------------------------------------------------------
#include <DateUtils.hpp>
#include <vcl.h>
#include <algorithm>
#pragma hdrstop

#include "Main.h"
#include "DataSetLayout.h"
#include "MatchPlayer.h"
#include "CatalogUnit.h"
#include "GetStringUnit.h"
#include "Group.h"
#include "Options.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "DBGridEhGrouping"
#pragma resource "*.dfm"
TfmMain *fmMain;
//---------------------------------------------------------------------------

// Конструктор
__fastcall TfmMain::TfmMain(int IdChamp) : TForm(static_cast<TComponent*>(0)), _connect(TConnect::Instance),
_eventer(_connect->SetEventHandler("match", &EventsEventAlert)),
_nearest(0), _id_champ(IdChamp),
_group_place_regex(String().sprintf("[%s][0-9]", _connect->GetReadSQL(String().sprintf("select * from get_group_list(%d)", _id_champ), true)->FieldByName("group_list")->AsString))
{
  Caption = _connect->GetReadSQL(String().sprintf("select info from get_champ_info(%d)", _id_champ), true)->Fields[0]->AsString;
  actLoadExecute(actLoad);
}
//---------------------------------------------------------------------------


// Перегрузка
void __fastcall TfmMain::actLoadExecute(TObject *Sender) {
  bool first=!dsData->Active;
  {
    TDataSetLayout L(dsData, "id");
    dsData->Data = _connect->GetReadDataSet("select * from get_match(:id_champ)", TQueryParams(ftInteger, "id_champ", _id_champ))->Data;
    _date_time_list.clear();
    for(dsData->First(); !dsData->Eof; dsData->Next())
      _date_time_list.insert(TDateTimeList::value_type(dsData->FieldByName("play_at")->AsDateTime, dsData->FieldByName("id")->AsInteger));
  }
  Timer->Enabled = true;
  Timer->OnTimer(Sender);
  if(first && !dsData->Locate("id", _nearest, TLocateOptions()))
    dsData->First();
}
//---------------------------------------------------------------------------

// Игроки
void __fastcall TfmMain::actOpenExecute(TObject *Sender) {
  if(dsData->FieldByName("all_exists")->AsInteger-3) return;
  if(fmPlayer && fmPlayer->GetIdMatch()!=dsData->FieldByName("id")->AsInteger) fmPlayer->Close();
  if(!fmPlayer)
    fmPlayer = new TfmPlayer(dsData->FieldByName("id")->AsInteger, dsData->FieldByName("id_c1")->AsInteger, dsData->FieldByName("id_c2")->AsInteger);
  fmPlayer->Show();
  fmPlayer->BringToFront();
}
//---------------------------------------------------------------------------

// Ловим события
void __fastcall TfmMain::EventsEventAlert(TObject *Sender, AnsiString EventName, int EventCount, bool &CancelAlerts) {
  actLoadExecute(actLoad);
}
//---------------------------------------------------------------------------

// Меняем признак окончания игры
void __fastcall TfmMain::actReadyExecute(TObject *Sender) {
  if(dsData->FieldByName("all_exists")->AsInteger-3) return;
  TSQLPtr SQL=_connect->GetWriteSQL("execute procedure switch_match_ready(:id)", false);
  TTranPtr T(SQL->Transaction);
  SQL->ParamByName("id")->AsInteger  = dsData->FieldByName("id")->AsInteger;
  SQL->ExecQuery();
  SQL->Transaction->Commit();
}
//---------------------------------------------------------------------------

// Управляем контролами
void __fastcall TfmMain::dsDataAfterScroll(TDataSet *DataSet) {
  int exists = dsData->FieldByName("all_exists")->AsInteger;
  actOpen->Enabled = exists==3;
  actReady->Enabled = exists==3;
  actSetCountry1->Caption = String().sprintf("%s", exists&1 ? "Стереть" : "Явно");
  actSetCountry2->Caption = String().sprintf("%s", exists&2 ? "Стереть" : "Явно");
}
//---------------------------------------------------------------------------

// Красим ячейки
void __fastcall TfmMain::dbgDataGetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont, TColor &Background, TGridDrawState State) {
  if(dsData->FieldByName("id")->AsInteger==_nearest) Background = clHighlightText;
  else Background = clWindow;
}
//---------------------------------------------------------------------------

// Инициализация
void __fastcall TfmMain::FormPaint(TObject *Sender) {
  OnPaint = 0;
  TOptions::Instance->RestoreLayout(dbgData);
}
//---------------------------------------------------------------------------

// Сохраняемся
void __fastcall TfmMain::FormDestroy(TObject *Sender) {
  TOptions::Instance->SaveLayout(dbgData);
}
//---------------------------------------------------------------------------

// Устанавливаем участника матча
void __fastcall TfmMain::actSetCountryExecute(TObject *Sender) {
  int t=dynamic_cast<TAction*>(Sender)->Tag;
  // Если участник установлен - стираем, иначе - спрашиваем
  int IdCountry=0;
  if(!(dsData->FieldByName("all_exists")->AsInteger & (t+1))) {
    ns_Catalog::TInit Init("id", "select id, group_name, name from get_champ_country(:id_champ, :id_group)", "Укажите сборную - участника матча");
    Init.GetParams().Add(ftInteger, "id_champ", _id_champ).Add(ftInteger, "id_group", dsData->FieldByName("id_group")->AsInteger);
    Init.AddField("", 1);
    Init.AddField("Группа", 1, true);
    Init.AddField("Сборная", 10);
    TDSPtr Data(ns_Catalog::Get(Init));
    if(!Data.get()) return;
    IdCountry = Data->FieldByName("id")->AsInteger;
  }
  TSQLPtr SQL=_connect->GetWriteSQL("select id from set_match_country(:id_match, :id_country, :ord_num)", false);
  TTranPtr T(SQL->Transaction);
  SQL->ParamByName("id_match")->AsInteger    = dsData->FieldByName("id")->AsInteger;
  SQL->ParamByName("id_country")->AsInteger  = IdCountry;
  SQL->ParamByName("ord_num")->AsInteger     = t;
  SQL->ExecQuery();
  SQL->Transaction->Commit();
}
//---------------------------------------------------------------------------

// Устанавливаем участника матча автомат по результатам игр в подгруппах
void __fastcall TfmMain::actSetCountryByGroupExecute(TObject *Sender) {
  int t=dynamic_cast<TAction*>(Sender)->Tag;
  String Data="";
  if(!GetString(Data, "Укажите группу и место", _group_place_regex)) return;
  TSQLPtr SQL=_connect->GetWriteSQL("select id from set_match_country_group_place(:id_match, :ord_num, :group_name, :place)", false);
  TTranPtr T(SQL->Transaction);
  SQL->ParamByName("id_match")->AsInteger    = dsData->FieldByName("id")->AsInteger;
  SQL->ParamByName("ord_num")->AsInteger     = t;
  SQL->ParamByName("group_name")->AsString   = Data.SubString(1, 1);
  SQL->ParamByName("place")->AsInteger       = Data.SubString(2, Data.Length()-1).ToInt();
  SQL->ExecQuery();
  SQL->Transaction->Commit();
}
//---------------------------------------------------------------------------



void __fastcall TfmMain::dbgDataMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y) {
  if(mbLeft!=Button) return;
  _id_match_buf = dsData->FieldByName("id")->AsInteger;
  _rank_buf = dsData->FieldByName("ranking")->AsInteger;
  _match_num_buf = dsData->FieldByName("ord_num")->AsInteger;
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::dbgDataMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y) {
  if(mbLeft!=Button || _id_match_buf == dsData->FieldByName("id")->AsInteger || _rank_buf-1-dsData->FieldByName("ranking")->AsInteger) return;
  int Id=Application->MessageBox(String().sprintf("В матче №%d примет участие победитель матча №%d?", dsData->FieldByName("ord_num")->AsInteger, _match_num_buf).c_str(), "Внимание!", MB_ICONQUESTION|MB_YESNOCANCEL);
  if(ID_CANCEL==Id) return;
  if(ID_NO==Id) _id_match_buf=-_id_match_buf;
  TSQLPtr SQL=_connect->GetWriteSQL("select id from set_match_country_id_match(:id_match, :id_match_by)", false);
  TTranPtr T(SQL->Transaction);
  SQL->ParamByName("id_match")->AsInteger    = dsData->FieldByName("id")->AsInteger;
  SQL->ParamByName("id_match_by")->AsInteger = _id_match_buf;
  SQL->ExecQuery();
  SQL->Transaction->Commit();
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::actGroupExecute(TObject *Sender) {
  if(!fmGroup) fmGroup = new TfmGroup(_id_champ);
  fmGroup->Show();
  fmGroup->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::FormClose(TObject *Sender, TCloseAction &Action) {
  Action = caFree;
}
//---------------------------------------------------------------------------


void __fastcall TfmMain::TimerTimer(TObject *Sender)
{
  // Смотрим, сколько сейчас времени, минус сдвиг (вдруг матчи заданы по Москве), минус 2 чвса на длительность матча
  TDateTime now=IncHour(Now(), -TOptions::Instance->Get("Options", "HoursShift", "0").ToInt() - 2);
  TDateTimeList::const_iterator nearest = _date_time_list.upper_bound(now);
  _nearest = nearest == _date_time_list.end()? 0: nearest->second;
  if(_nearest != dsData->FieldByName("id")->AsInteger)
    dbgData->Repaint();
}
//---------------------------------------------------------------------------

