//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "MatchPlayer.h"
#include "GetStringUnit.h"
#include "ActivePtr.h"
#include "DynamicMenu.h"
#include "DataSetLayout.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "DBGridEhGrouping"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TfmPlayer *fmPlayer=0;

// Конструктор
__fastcall TfmPlayer::TfmPlayer(int id_match, int id1, int id2) : TForm(static_cast<TComponent*>(0)),
_connect(TConnect::Instance), _id_match(id_match), _id1(id1), _id2(id2), _minute_mask("[0-9]{1,3}"),
_eventer(_connect->SetEventHandler(String().sprintf("match_player_%d;match_player_%d;match_%d", _id1, _id2, _id_match), &EventAlertPlayer))
{
  TDynamicMenu("select id, name from get_goal_type", miGoal, &actGoalExecute);
  TDynamicMenu("select id, name from get_card_type", miCardChamp, &actCardChampExecute);
  TDynamicMenu("select id, name from get_card_type", miCardMatch, &actCardMatchExecute);
  _id_array[0]    = _id1;     _id_array[1]    = _id2;
  dsChampArray[0] = dsChamp1; dsChampArray[1] = dsChamp2;
  dsMatchArray[0] = dsMatch1; dsMatchArray[1] = dsMatch2;
  dbgChampMatchEnter(dbgChamp1);
  actLoadExecute(actLoad);
  actGetInfoExecute(actGetInfo);
}
//---------------------------------------------------------------------------

// Закрываем форму
void __fastcall TfmPlayer::actCloseExecute(TObject *Sender) {
  Close();
}
//---------------------------------------------------------------------------

// Размеры контролов
void __fastcall TfmPlayer::FormResize(TObject *Sender) {
  pnlPlayer1->Height = (pnlPlayer1->Height+pnlPlayer2->Height)/2;
  dbgChamp1->Width = (dbgChamp1->Width+dbgMatch1->Width)/2;
  dbgChamp2->Width = dbgChamp1->Width;
  SetColWidth(dbgChamp1);
  SetColWidth(dbgChamp2);
  SetColWidth(dbgMatch1);
  SetColWidth(dbgMatch2);
}
//---------------------------------------------------------------------------

void __fastcall TfmPlayer::SetColWidth(TDBGridEh *Grid) {
  for(int i=0; i<Grid->Columns->Count; ++i) {
    if(Grid->Columns->Items[i]->FieldName=="NUMBER") {
      Grid->Columns->Items[i]->Width = Grid->Width / 10;
      if(Grid->Columns->Items[i]->Width>40) Grid->Columns->Items[i]->Width=40;
    }
    else if(Grid->Columns->Items[i]->FieldName=="GOAL_COUNT") Grid->Columns->Items[i]->Width = Grid->Width / 10;
    else if(Grid->Columns->Items[i]->FieldName=="GOAL_MINUTE") Grid->Columns->Items[i]->Width = Grid->Width / 7;
  }
  Grid->AutoFitColWidths = true;
}
//---------------------------------------------------------------------------

// Фильтруем "главный" датасет
OleVariant __fastcall TfmPlayer::dspDataDataRequest(TObject *Sender, OleVariant &Input) {
  dsData->Filter = Input;
  dsData->Filtered = !dsData->Filter.IsEmpty();
  return dspData->Data;
}
//---------------------------------------------------------------------------

// Переходы между гридами
void __fastcall TfmPlayer::dbgChampMatchEnter(TObject *Sender) {
  int n = dynamic_cast<TDBGridEh*>(Sender)->Tag;
  _id = _id_array[n];
  dsChamp = dsChampArray[n];
  dsMatch = dsMatchArray[n];
  actAdd->Enabled = dsMatch->Active && dsMatch->RecordCount<11;
}
//---------------------------------------------------------------------------

// Добавляем игрока в стартовый состав
void __fastcall TfmPlayer::actAddExecute(TObject *Sender) {
  TSQLPtr SQL=_connect->GetWriteSQL("select id from add_match_player(:id_match, :id_player)", false);
  TTranPtr T(SQL->Transaction);
  SQL->ParamByName("id_match")->AsInteger   = _id;
  SQL->ParamByName("id_player")->AsInteger  = dsChamp->FieldByName("id_champ_player")->AsInteger;
  SQL->ExecQuery();
  SQL->Transaction->Commit();
}
//---------------------------------------------------------------------------

// Выносим игрока (исправляем ошибку внесения)
void __fastcall TfmPlayer::actDelExecute(TObject *Sender) {
  TSQLPtr SQL=_connect->GetWriteSQL("execute procedure del_match_player(:id_player)", false);
  TTranPtr T(SQL->Transaction);
  SQL->ParamByName("id_player")->AsInteger  = dsMatch->FieldByName("id_match_player")->AsInteger;
  SQL->ExecQuery();
  SQL->Transaction->Commit();
}
//---------------------------------------------------------------------------

// Проводим замену
void __fastcall TfmPlayer::actSubstExecute(TObject *Sender) {
  String strVal="";
  if(!GetString(strVal, "Укажите минуту матча", _minute_mask))
    return;
  TSQLPtr SQL=_connect->GetWriteSQL("select id from add_substitute(:id_from, :id_to, :minute)", false);
  TTranPtr T(SQL->Transaction);
  SQL->ParamByName("id_from")->AsInteger  = dsMatch->FieldByName("id_match_player")->AsInteger;
  SQL->ParamByName("id_to")->AsInteger    = dsChamp->FieldByName("id_champ_player")->AsInteger;
  SQL->ParamByName("minute")->AsString    = strVal;
  SQL->ExecQuery();
  SQL->Transaction->Commit();
}
//---------------------------------------------------------------------------

// Гол!
void __fastcall TfmPlayer::actGoalExecute(TObject *Sender) {
  int tag = dynamic_cast<TMenuItem*>(Sender)->Tag;
  int default_time = tag % 1000;
  String strVal=default_time?IntToStr(default_time):String("");
  if(!default_time)
    if(!GetString(strVal, "Укажите минуту матча", _minute_mask))
      return;
  TSQLPtr SQL=_connect->GetWriteSQL("select id from add_goal(:id_player, :id_type, :minute)", false);
  TTranPtr T(SQL->Transaction);
  SQL->ParamByName("id_player")->AsInteger  = dsMatch->FieldByName("id_match_player")->AsInteger;
  SQL->ParamByName("id_type")->AsInteger    = tag/1000;
  SQL->ParamByName("minute")->AsString      = strVal;
  SQL->ExecQuery();
  SQL->Transaction->Commit();
}
//---------------------------------------------------------------------------

// Карточка
void __fastcall TfmPlayer::actCardChampExecute(TObject *Sender) {
  String strVal="";
  if(!GetString(strVal, "Укажите минуту матча", _minute_mask))
    return;
  TSQLPtr SQL=_connect->GetWriteSQL("select id from add_card(:id_match, :id_player, :id_type, :minute)", false);
  TTranPtr T(SQL->Transaction);
  SQL->ParamByName("id_match")->AsInteger  = _id;
  SQL->ParamByName("id_player")->AsInteger  = dsChamp->FieldByName("id_champ_player")->AsInteger;
  SQL->ParamByName("id_type")->AsInteger    = dynamic_cast<TMenuItem*>(Sender)->Tag;
  SQL->ParamByName("minute")->AsString      = strVal;
  SQL->ExecQuery();
  SQL->Transaction->Commit();
}
void __fastcall TfmPlayer::actCardMatchExecute(TObject *Sender) {
  String strVal="";
  if(!GetString(strVal, "Укажите минуту матча", _minute_mask))
    return;
  TSQLPtr SQL=_connect->GetWriteSQL("select id from add_card(:id_match, :id_player, :id_type, :minute)", false);
  TTranPtr T(SQL->Transaction);
  SQL->ParamByName("id_match")->AsInteger  = _id;
  SQL->ParamByName("id_player")->AsInteger  = dsMatch->FieldByName("id_champ_player")->AsInteger;
  SQL->ParamByName("id_type")->AsInteger    = dynamic_cast<TMenuItem*>(Sender)->Tag;
  SQL->ParamByName("minute")->AsString      = strVal;
  SQL->ExecQuery();
  SQL->Transaction->Commit();
}
//---------------------------------------------------------------------------

// Ловим события
void __fastcall TfmPlayer::EventAlertPlayer(TObject *Sender, AnsiString EventName, int EventCount, bool &CancelAlerts) {
  if(EventName.Pos("match_player_")==1)
    actLoadExecute(actLoad);
  else actGetInfoExecute(actGetInfo);
}
//---------------------------------------------------------------------------

// Выбираем информацию для шапки формы
void __fastcall TfmPlayer::actGetInfoExecute(TObject *Sender) {
  TSQLPtr SQL=_connect->GetReadSQL("select * from get_match_country_info(:id)", false);
  SQL->ParamByName("id")->AsInteger = _id1;
  SQL->ExecQuery();
  String strCountry1 = SQL->FieldByName("name")->AsString;
  pnlPlayer1->Caption = strCountry1;
  int Goal1 = SQL->FieldByName("goal_count")->AsInteger;
  int Penalty1 = SQL->FieldByName("penalty_count")->AsInteger;
  SQL->Close();
  SQL->ParamByName("id")->AsInteger = _id2;
  SQL->ExecQuery();
  String strCountry2 = SQL->FieldByName("name")->AsString;
  pnlPlayer2->Caption = strCountry2;
  int Goal2 = SQL->FieldByName("goal_count")->AsInteger;
  int Penalty2 = SQL->FieldByName("penalty_count")->AsInteger;
  Caption = String().sprintf("%s - %s, %d:%d%s", strCountry1.c_str(), strCountry2.c_str(), Goal1, Goal2, (Penalty1+Penalty2>0?String().sprintf("(%d:%d)", Penalty1, Penalty2): String()).c_str());
}
//---------------------------------------------------------------------------

// Загружаем игроков
void __fastcall TfmPlayer::actLoadExecute(TObject *Sender) {
  Load(_id1, dbgChamp1, dbgMatch1);
  Load(_id2, dbgChamp2, dbgMatch2);
}
void __fastcall TfmPlayer::Load(int Id, TDBGridEh *dbgChamp, TDBGridEh *dbgMatch) {
  TClientDataSet *dsChamp = dynamic_cast<TClientDataSet*>(dbgChamp->DataSource->DataSet), *dsMatch = dynamic_cast<TClientDataSet*>(dbgMatch->DataSource->DataSet);
  TDataSetLayout LC(dsChamp, "id_champ_player"), LM(dsMatch, "id_match_player");
  TActivePtr<TDBGridEhSumList> Act(dbgMatch->SumList, false);
  { // Игроки
    dsData->Data = _connect->GetReadDataSet("select * from get_match_player(:id_c)", TQueryParams(ftInteger, "id_c", Id))->Data;
    dsChamp->Data = dsChamp->DataRequest(String("id_match_player is null or subst_min is not null"));
    dsMatch->Data = dsMatch->DataRequest(String("id_match_player is not null and subst_min is null"));
  }
  // Считаем замены
  dbgChamp->Columns->Items[1]->Footer->Value = String().sprintf("Замены: %d", _connect->GetReadSQL(String().sprintf("select count(42) from get_substitute(%d)", Id), true)->Fields[0]->AsInteger);
  actAdd->Enabled = dsMatch->RecordCount<11;
}
//---------------------------------------------------------------------------

// Красим ячейки
void __fastcall TfmPlayer::dbgGetCellParams(TObject *Sender, TColumnEh *Column, TFont *AFont, TColor &Background, TGridDrawState State) {
  TDBGridEh *dbgSender = dynamic_cast<TDBGridEh*>(Sender);
  TDataSet *dsSender = dbgSender->DataSource->DataSet;
  if(Column->Index==0)
    Background = static_cast<TColor>(dsSender->FieldByName("card_color")->AsInteger);
  if(dsSender->FieldByName("ord_num")->AsInteger<1000000)
    AFont->Style = AFont->Style >> fsItalic;
  else AFont->Style = AFont->Style << fsItalic;
}
//---------------------------------------------------------------------------

void __fastcall TfmPlayer::FormClose(TObject *Sender, TCloseAction &Action) {
  dsData->Close();
  Action = caFree;
  fmPlayer=0;
}
//---------------------------------------------------------------------------

