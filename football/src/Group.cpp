//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Group.h"
#include "Connect.h"
#include "DataSetLayout.h"
#include "Options.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma link "GridsEh"
#pragma link "DBGridEhGrouping"
#pragma resource "*.dfm"
TfmGroup *fmGroup=0;
int TCountry::_max_num=0;
//---------------------------------------------------------------------------

void __fastcall TActionOwner::Reset() {
  _panel.reset(new TPanel(static_cast<TComponent*>(0)));
  _act.reset(new TAction*[TCountry::MaxNum()]);
  for(int i=0; i<TCountry::MaxNum(); ++i) {
    _act[i] = new TAction(_panel.get());
    _act[i]->Caption = String().sprintf("Установить место %d", i+1);
    _act[i]->Tag = i+1;
    _act[i]->OnExecute = _f;
    if(i<9) _act[i]->ShortCut = ShortCut((i+1)|0x30, TShiftState()<<ssAlt);
    TMenuItem *mi = new TMenuItem(_panel.get());
    mi->Action = _act[i];
    _menu->Items->Add(mi);
  }
}
//---------------------------------------------------------------------------

void __fastcall TActionOwner::Enabled(bool E, int N) {
  for(int i=0; i<TCountry::MaxNum(); ++i)
    _act[i]->Enabled = E;
  if(N) _act[N-1]->Enabled = !E;
}
//---------------------------------------------------------------------------

__fastcall TfmGroup::TfmGroup(int IdChamp) :
TForm(static_cast<TComponent*>(0)),
_id_champ(IdChamp),
_action_owner(&actSetPlaceExecute, pmMain),
_eventer(TConnect::Instance->SetEventHandler("match;place", &EventsEventAlert))
 {
  actLoadExecute(0);
}
//---------------------------------------------------------------------------

// Закрываем форму
void __fastcall TfmGroup::actCloseExecute(TObject *Sender) {
  Close();
}
//---------------------------------------------------------------------------

// Делаем датасет, грид
void __fastcall TfmGroup::MakeDataSet() {
  _action_owner.Reset();
  dsData->Close();
  TFieldDefs *Defs=dsData->FieldDefs;
  if(!Defs->Count) {
    Defs->Add("Id", ftInteger);
    Defs->Add("Group", ftString, 63);
    Defs->Add("Num", ftInteger);
    Defs->Add("Country", ftString, 63);
    for(int i=1; i<=TCountry::MaxNum(); ++i) {
      String F=String().sprintf("M%d", i);
      Defs->Add(F, ftString, 10);
      TColumnEh *C=dbgData->Columns->Add();
      C->FieldName = F;
      C->Title->Caption = i;
      C->Width = 40;
      C->AutoFitColWidth = false;
      C->Alignment = taCenter;
      C->Index = i+4;
    }
    Defs->Add("Game", ftInteger);
    Defs->Add("Win", ftInteger);
    Defs->Add("Deuce", ftInteger);
    Defs->Add("Lose", ftInteger);
    Defs->Add("Goal", ftString, 10);
    Defs->Add("Point", ftInteger);
    Defs->Add("Place", ftString, 10);
    MakeFlags();
    TOptions::Instance->RestoreLayout(dbgData);
  }
  dsData->CreateDataSet();
}
//---------------------------------------------------------------------------

// Выбираем флаги
void __fastcall TfmGroup::MakeFlags() {
  std::auto_ptr<Graphics::TBitmap> pBitmap(new Graphics::TBitmap);
  std::auto_ptr<TStream> pStream(new TMemoryStream);
  for(TSQLPtr SQL=TConnect::Instance->GetReadSQL(String().sprintf("select id, flag from get_champ_country(%d)", _id_champ), true); !SQL->Eof; SQL->Next()) if(!SQL->FieldByName("flag")->IsNull) {
    SQL->FieldByName("flag")->SaveToStream(pStream.get());
    pStream->Seek(0, soFromBeginning);
    pBitmap->LoadFromStream(pStream.get());
    pStream->Seek(0, soFromBeginning);
    ilFlag->Add(pBitmap.get(), 0);
    dbgData->Columns->Items[2]->KeyList->Add(SQL->FieldByName("id")->AsString);
  }
}
//---------------------------------------------------------------------------

// Тянем данные
void __fastcall TfmGroup::actLoadExecute(TObject *Sender) {
  TDataSetLayout L(dsData, "id");
  TCountry::MaxNum(0);
  _group.clear();
  for(TSQLPtr SQL=TConnect::Instance->GetReadSQL(String().sprintf("select * from get_match_detail(%d) where id_group is not null", _id_champ), true); !SQL->Eof; SQL->Next()) {
    TGroup &Group=_group.insert(std::make_pair(SQL->FieldByName("id_group")->AsInteger, TGroup(SQL->FieldByName("group_name")->AsString))).first->second;
    Group.Add(SQL->FieldByName("country_name1")->AsString, SQL->FieldByName("id_country1")->AsInteger, SQL->FieldByName("num1")->AsInteger, SQL->FieldByName("place1")->AsInteger).SetRes(SQL->FieldByName("num2")->AsInteger, TCountry::TGoal(SQL->FieldByName("goal1")->AsInteger, SQL->FieldByName("goal2")->AsInteger), SQL->FieldByName("ready")->AsInteger);
    Group.Add(SQL->FieldByName("country_name2")->AsString, SQL->FieldByName("id_country2")->AsInteger, SQL->FieldByName("num2")->AsInteger, SQL->FieldByName("place2")->AsInteger).SetRes(SQL->FieldByName("num1")->AsInteger, TCountry::TGoal(SQL->FieldByName("goal2")->AsInteger, SQL->FieldByName("goal1")->AsInteger), SQL->FieldByName("ready")->AsInteger);
  }
  MakeDataSet();
  for(TGroupList::const_iterator i=_group.begin(); i!=_group.end(); ++i) {
    if(i!=_group.begin()) {
      dsData->Append();
      dsData->FieldByName("Id")->Clear();
      dsData->Post();
    }
    for(TGroup::TCountryList::const_iterator j=i->second.GetCountry().begin(); j!=i->second.GetCountry().end(); ++j) {
      dsData->Append();
      dsData->FieldByName("Id")->AsInteger = j->second.Id;
      dsData->FieldByName("Group")->AsString = i->second.Name;
      dsData->FieldByName("Num")->AsInteger = j->second.Num;
      dsData->FieldByName("Country")->AsString = j->second.Name;
      dsData->FieldByName("Game")->AsInteger = j->second.GetPlay();
      dsData->FieldByName("Win")->AsInteger = j->second.GetWin();
      dsData->FieldByName("Deuce")->AsInteger = j->second.GetDeuce();
      dsData->FieldByName("Lose")->AsInteger = j->second.GetLose();
      dsData->FieldByName("Goal")->AsString =  j->second.GetPlay() ? String().sprintf("%d-%d", j->second.GetGoalTotal().first, j->second.GetGoalTotal().second) : String(":");
      dsData->FieldByName("Point")->AsInteger = j->second.GetPoint();
      if(j->second.Place) dsData->FieldByName("Place")->AsString = IntToStr(j->second.Place);
      dsData->FieldByName(String().sprintf("M%d", j->second.Num))->AsString = "z";
      for(TCountry::TGoalList::const_iterator k=j->second.GetGoal().begin(); k!=j->second.GetGoal().end(); ++k)
        dsData->FieldByName(String().sprintf("M%d", k->first))->AsString = String().sprintf("%d:%d", k->second.first, k->second.second);
      dsData->Post();
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TfmGroup::FormClose(TObject *Sender, TCloseAction &Action) {
  dsData->Close();
  Action = caFree;
  fmGroup = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfmGroup::actSetPlaceExecute(TObject *Sender) {
  int N = dynamic_cast<TAction*>(Sender)->Tag;
  TSQLPtr SQL = TConnect::Instance->GetWriteSQL("execute procedure set_group_place(:id, :place)", false);
  TTranPtr T(SQL->Transaction);
  SQL->ParamByName("id")->AsInteger = dsData->FieldByName("Id")->AsInteger;
  SQL->ParamByName("place")->AsInteger = N;
  SQL->ExecQuery();
  SQL->Transaction->Commit();
}
//---------------------------------------------------------------------------

void __fastcall TfmGroup::EventsEventAlert(TObject *Sender, AnsiString EventName, int EventCount, bool &CancelAlerts) {
  actLoadExecute(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfmGroup::dsDataAfterScroll(TDataSet *DataSet) {
/*  if(dsData->FieldByName("Game")->AsInteger!=TCountry::MaxNum()+1) {
    actDelPlace->Enabled = false;
    _action_owner.Enabled(false);
  }
  else {
    actDelPlace->Enabled = !dsData->FieldByName("Place")->IsNull;
    _action_owner.Enabled(true, dsData->FieldByName("Place")->IsNull?0:dsData->FieldByName("Place")->AsInteger);
  }*/
}
//---------------------------------------------------------------------------

void __fastcall TfmGroup::dbgDataDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol, TColumnEh *Column, TGridDrawState State) {
  if(dsData->FieldByName("Id")->IsNull) {
    dbgData->Canvas->Pen->Color = clWindow;
    dbgData->Canvas->MoveTo(Rect.Right, Rect.Top);
    dbgData->Canvas->LineTo(Rect.Right, Rect.Bottom);
    dbgData->Canvas->MoveTo(Rect.Left-1, Rect.Top);
    dbgData->Canvas->LineTo(Rect.Left-1, Rect.Bottom);
    dbgData->Canvas->Brush->Color = clWindow;
    dbgData->Canvas->FillRect(Rect);
  }
  else if(Column->Field->AsString=="z") {
    dbgData->Canvas->Brush->Color = clBtnFace;
    dbgData->Canvas->FillRect(Rect);
  }
  else if(Column->FieldName=="Group" && dsData->FieldByName("Num")->AsInteger-1) {
    dbgData->Canvas->Brush->Color = clWindow;
    dbgData->Canvas->FillRect(Rect);
  }
  else dbgData->DefaultDrawColumnCell(Rect, DataCol, Column, State);
}
//---------------------------------------------------------------------------


void __fastcall TfmGroup::FormPaint(TObject *Sender) {
/*  OnPaint = 0;
  TOptions::Instance->RestoreLayout(dbgData);
*/
}
//---------------------------------------------------------------------------

void __fastcall TfmGroup::FormDestroy(TObject *Sender) {
  TOptions::Instance->SaveLayout(dbgData);
}
//---------------------------------------------------------------------------

