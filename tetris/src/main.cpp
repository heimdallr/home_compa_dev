//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "FilePtr.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmMain *fmMain;
//---------------------------------------------------------------------------

// Преинициализация
__fastcall TfmMain::TfmMain(TComponent* Owner) : TForm(Owner), _tetris(0), _fig_gen(0), _indicator(new TfmIndicator(this, Timer, pnlImg, imMain)) {
  _indicator->pnlRight->Parent = this;
  TDateTime dtNow=Now();
  srand(static_cast<unsigned int>(24*60*600*(dtNow-int(dtNow))));
  actUp->Tag = e_Up;
  actDown->Tag = e_Down;
  actLeft->Tag = e_Left;
  actRight->Tag = e_Right;
  actRotate->Tag = e_Rotate;
  actLRotate->Tag = e_LRotate;
  pnlImg->DoubleBuffered = true;
  imMain->Cursor = crNone;
  String strFile=ChangeFileExt(Application->ExeName, ".").LowerCase();
  strIni = strFile+"ini";
  strXml = strFile+"xml";
  strDat = strFile+"dat";
  strLog = strFile+"log";
  for(int i=ParamCount(); i>0; --i) {
    String strExt = ExtractFileExt(ParamStr(i)).LowerCase();
    if(strExt==".ini") strIni = ParamStr(i).LowerCase();
    else if(strExt==".xml") strXml = ParamStr(i).LowerCase();
    else if(strExt==".dat") strDat = ParamStr(i).LowerCase();
    else if(strExt==".log") strLog = ParamStr(i).LowerCase();
  }
  _indicator->strLog = strLog;
  _fig_gen.reset(FigGen = new TdmFigGen(strXml, strLog));
}
//---------------------------------------------------------------------------

// Постинициализация
void __fastcall TfmMain::FormPaint(TObject *Sender) {
  Visible = false;
  OnPaint = 0;
  int size=20, delay=500, cheat_enabled=0;
  try {
    TFilePtr inp(strIni, "rt");
    fscanf(inp, "%d %d %d", &size, &delay, &cheat_enabled);
  }
  catch(...){}
  Timer->Interval = delay;
  if(cheat_enabled) OnKeyPress = FormKeyPress;
  _tetris.reset(new TTetris(size, _indicator));
  pnlBottom->Height = pnlImg->ClientHeight-imMain->Height+6;
  Visible = true;
  actLoadExecute(Sender);
  TimeTimer(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfmMain::actExitExecute(TObject *Sender) {
  Timer->Enabled = false;
  if(ID_YES==Application->MessageBox("Сохранить игру?", "Подтверждение", MB_ICONQUESTION|MB_YESNO))
    actSaveExecute(Sender);
  Close();
}
//---------------------------------------------------------------------------

// Кажем время
void __fastcall TfmMain::TimeTimer(TObject *Sender) {
  Caption = String().sprintf("Just Another Tetris %s", Now().FormatString("dd.mm.yyyy hh:nn"));
}
//---------------------------------------------------------------------------

// Действия игрока
void __fastcall TfmMain::actMoveExecute(TObject *Sender) {
  Timer->Enabled = true;
  _tetris->Move(static_cast<EMove>(dynamic_cast<TAction*>(Sender)->Tag));
}
//---------------------------------------------------------------------------

// Действие по таймеру
void __fastcall TfmMain::TimerTimer(TObject *Sender) {
  if(_tetris->Recount()) {
    Timer->Enabled = false;
    switch(Application->MessageBox("Увы, вы проиграли! Начать заново?", "Внимание!", MB_ICONQUESTION|MB_YESNO)) {
      case ID_YES:
        _tetris->Reset();
        Timer->Enabled = true;
      break;
      case ID_NO:
        Close();
      return;
    }
  }
}
//---------------------------------------------------------------------------

// Пауза
void __fastcall TfmMain::actPauseExecute(TObject *Sender) {
  Timer->Enabled = !Timer->Enabled;
}
//---------------------------------------------------------------------------

// Сохраняемся
void __fastcall TfmMain::actSaveExecute(TObject *Sender) {
  try {
    _tetris->Save(strDat);
  }
  catch(Exception &E) {
    Application->ShowException(&E);
  }
}
//---------------------------------------------------------------------------

// Загружаемся
void __fastcall TfmMain::actLoadExecute(TObject *Sender) {
  try {
    if(FileExists(strDat) && ID_YES==Application->MessageBox("Загрузить сохраненную игру?", "Подтверждение", MB_ICONQUESTION|MB_YESNO))
      _tetris->Load(strDat);
    else
      Timer->Enabled = true;
  }
  catch(Exception &E) {
    Application->ShowException(&E);
    Timer->Enabled = true;
  }
}
//---------------------------------------------------------------------------

// Работаем нажатия кнопок, читы
void __fastcall TfmMain::FormKeyPress(TObject *Sender, char &Key) {
  if(Key>='0' && Key<='9') _tetris->SetNextFigCheat(Key-'0');
}
//---------------------------------------------------------------------------

// Чистим статистику
void __fastcall TfmMain::actClearStatExecute(TObject *Sender) {
  Timer->Enabled = false;
  if(ID_YES==Application->MessageBox("Действительно начать статистику фигур заново?", "Подтверждение", MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2))
    _tetris->Move(e_ClearStat);
  Timer->Enabled = true;
}
//---------------------------------------------------------------------------

