//---------------------------------------------------------------------------
#pragma hdrstop
#include "data.h"
#include "FilePtr.h"
#include <Dialogs.hpp>
#include <set>
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------

const char *EMoveCaption[] = {
  "Итого",
  "Влево",
  "Вправо",
  "Вниз",
  "Вверх",
  "Вращение по часовой",
  "Вращение против часовой",
  "Служебное действие, отсюда не логируем",
  "Стираем статистику"
};
//---------------------------------------------------------------------------

// Инициализация
__fastcall TTetris::TTetris(int n, TfmIndicator *ind)
: _n(n), _ind(ind), _fig(0), _fig0(0), _id_next_fig_cheat(-1) {
  _move_count.resize(e_MoveLast);
  _ind->pnlImg->Width = _ind->pnlImg->Height;
  _size = _ind->imMain->Width/_n;
  _N = _size*_n;
  _ind->pnlImg->ClientWidth = _N+6;
  _n0 = _n/2;
  _ind->imMain->Width = _N+1;
  _ind->imMain->Height = _N+1;
  _ind->imMain->Picture = new TPicture;
  _ind->imMain->Picture->Bitmap = new Graphics::TBitmap;
  _ind->imMain->Picture->Bitmap->Width = _ind->imMain->Width;
  _ind->imMain->Picture->Bitmap->Height = _ind->imMain->Width;
  _ind->imMain->Picture->Bitmap->PixelFormat = pf8bit;
  _cnv = _ind->imMain->Picture->Bitmap->Canvas;

  _ind->pnlImgNext->Height += ind->imNext->Width-ind->imNext->Height;
  _M = ind->imNext->Width;
  ind->imNext->Picture = new TPicture;
  ind->imNext->Picture->Bitmap = new Graphics::TBitmap;
  ind->imNext->Picture->Bitmap->Width = ind->imNext->Width;
  ind->imNext->Picture->Bitmap->Height = ind->imNext->Width;
  ind->imNext->Picture->Bitmap->PixelFormat = pf8bit;
  _nxt = ind->imNext->Picture->Bitmap->Canvas;

  _row = new int[_n];
  _data = new TItem*[_n];
  for(int i=0; i<_n; ++i)
    _data[i] = new TItem[_n];
  Reset();
}
//---------------------------------------------------------------------------

// Зачищаем стакан
void __fastcall TTetris::Reset() {
  _count = 0;
  _line.assign(1, 0);
  // Чистим данные
  memset(_row, 0, sizeof(_row[0])*_n);
  for(int i=0; i<_n; ++i)
    for(int j=0; j<_n; ++j)
      if(_data[i][j].first)
        Set(_data[i][j]);
  // Чистим экран
  _cnv->Brush->Color = clBlack;
  _cnv->FillRect(TRect(0, 0, _N, _N));
  _cnv->Pen->Color = clGray;
  for(int i=0; i<=_N; i+=_size) {
    _cnv->MoveTo(0, i);
    _cnv->LineTo(_N, i);
    _cnv->MoveTo(i, 0);
    _cnv->LineTo(i, _N);
  }
  // Делаем фигуры
  _fig.reset(FigGen->GetFigure(TPos(0, _n0), _id_next_fig_cheat));
  _fig0.reset(FigGen->GetFigure(TPos(0, _n0), _id_next_fig_cheat));
  SetView();
  Preview();
}
//---------------------------------------------------------------------------

// Деструкторъ
__fastcall TTetris::~TTetris() {
  delete[] _row;
  for(int i=0; i<_n; ++i)
    delete[] _data[i];
  delete[] _data;
  try {
    TFilePtr outp(_ind->strLog, "at");
    fprintf(outp, "Нажаты кнопки\n");
    for(int i=1; i<e_MoveLast; ++i) fprintf(outp, "%d\t\"%s\"\n", _move_count[i], EMoveCaption[i]);
    fprintf(outp, "%s\t%d\n\n", EMoveCaption[0], _move_count[0]);
    fprintf(outp, "Разбиты линии\n");
    for(unsigned int i=1; i<_line.size(); ++i) fprintf(outp, "%d\tпо %d\n", _line[i], i);
    fprintf(outp, "Итого\t%d\n---------------------------------------------------------------------------\n\n", _line[0]);
  }catch(...) {}
}
//---------------------------------------------------------------------------

// Выставляем значение элемента
void __fastcall TTetris::Set(TItem &Item, bool mode) {
  Item.first = mode;
}
//---------------------------------------------------------------------------

// Располагаем фигуру на поле
void __fastcall TTetris::Set(bool mode) {
  for(TPosIt i=_fig->GetItems().begin(); i!=_fig->GetItems().end(); ++i)
    Set(_data[_fig->GetPos().second+i->second][_fig->GetPos().first+i->first], mode);
}
//---------------------------------------------------------------------------

// Рисуем текущую позицию
void __fastcall TTetris::Paint() {
  for(int i=0; i<_n; ++i)
    for(int j=0; j<_n; ++j)
      if(_data[i][j].second!=_data[i][j].first) {
        if(_data[i][j].first) {
          _cnv->Brush->Color = clWhite;
          ++_row[j];
        }
        else {
          _cnv->Brush->Color = clBlack;
          --_row[j];
        }
        _cnv->Brush->Color = _data[i][j].first ? clWhite : clBlack;
        _cnv->FillRect(TRect(_size*i+1, _size*j+1, _size*(i+1), _size*(j+1)));
        _data[i][j].second = _data[i][j].first;
      }
}
//---------------------------------------------------------------------------

// Пересчитываем новую позицию
bool __fastcall TTetris::Recount() {
  switch(MoveFig(TPos(1, 0))) {
    case e_Moved: Paint(); return false;
    case e_Crash: return true;
    case e_Bottom:
      if(_fig->OnBottom(_n-1, _data, _count)) {
        Paint();
        return false;
      }
      Paint();
      if(unsigned int n=Blast()) {
        _count += _n*n*(n+1)/2;
        if(_line.size()<=n)
          _line.resize(n+1);
        _line[0] += n;
        ++_line[n];
        Paint();
      }
      SetView();
      _ind->SetInterval();
  }
  _fig.reset(_fig0.release());
  _fig0.reset(FigGen->GetFigure(TPos(0, _n0), _id_next_fig_cheat));
  Preview();
  MoveFig(TPos(0, 0));
  Paint();
  return false;
}
//---------------------------------------------------------------------------

// Показывем счет игры
void __fastcall TTetris::SetView() {
  _ind->eCount->Text = IntToStr(_count);
  TIntIt i=_line.begin();
  if(i==_line.end()) _ind->eLine->Text = "";
  else {
    String strText=String().sprintf("%d   ", *i);
    for(++i; i!=_line.end(); ++i)
      strText += String().sprintf("%d ", *i);
    _ind->eLine->Text = strText;
  }
}
//---------------------------------------------------------------------------

// Двигаем фигуру
EFigMove __fastcall TTetris::MoveFig(TPos &pos) {
  TPos new_pos(_fig->GetPos().first+pos.first, _fig->GetPos().second+pos.second);
  for(TPosIt i=_fig->GetItems().begin(); i!=_fig->GetItems().end(); ++i) {
    if(i->first+new_pos.first<0 || i->first+new_pos.first>=_n || i->second+new_pos.second<0 || i->second+new_pos.second>=_n) return e_Bottom;
    if(_fig->Exists(_fig->GetPos(), TPos(i->first+pos.first, i->second+pos.second))) continue;
    if(_data[new_pos.second+i->second][new_pos.first+i->first].first)
      return _fig->GetPos().first ? e_Bottom : e_Crash;
  }
  Set();
  _fig->SetPos(new_pos);
  Set(true);
  return e_Moved;
}
//---------------------------------------------------------------------------

// Команда извне
void __fastcall TTetris::Move(EMove move) {
  if(move<e_MoveLast) {
    ++_move_count[move];
    ++_move_count[0];
  }
  switch(move) {
    case e_Up:
      MoveFig(TPos(-1, 0));
      _ind->SetInterval();
    break;
    case e_Down:
      _ind->SetInterval(1);
    break;
    case e_Left:
      MoveFig(TPos(0, -1));
    break;
    case e_Right:
      MoveFig(TPos(0, 1));
    break;
    case e_Rotate:
      Rotate();
    break;
    case e_LRotate:
      Rotate(-1);
    break;
    case e_ClearStat:
      FigGen->ClearStat();
    break;
    default:
      ShowMessage(move);
  }
}
//---------------------------------------------------------------------------

// Сносим целые линии
unsigned int __fastcall TTetris::Blast() {
  int res=0;
  for(int j=_n-1; j>=0; --j) {
    if(_row[j]==_n) {
      ++res;
      continue;
    }
    if(res)
      for(int i=0; i<_n; ++i)
        Set(_data[i][j+res], _data[i][j].first);
  }
  return res;
}
//---------------------------------------------------------------------------

// Крутим фигуру
void __fastcall TTetris::Rotate(int dir) {
  std::auto_ptr<TFigure> fig(FigGen->GetFigure(_fig.get()));
  fig->Rotate(dir);
  for(TPosIt i=fig->GetItems().begin(); i!=fig->GetItems().end(); ++i) {
    if(fig->GetPos().first+i->first>=_n || fig->GetPos().second+i->second<0 || fig->GetPos().second+i->second>=_n) return;
    if(_fig->Exists(fig->GetPos(), TPos(i->first, i->second))) continue;
    if(_data[fig->GetPos().second+i->second][fig->GetPos().first+i->first].first)
      return;
  }
  Set();
  _fig.reset(fig.release());
  Set(true);
}
//---------------------------------------------------------------------------

// Предпросмотр следующей фигуры
void __fastcall TTetris::Preview() {
  _ind->eFig->Text = FigGen->GetInfo(_fig.get()).GetCaption();
  _ind->eFig0->Text = FigGen->GetInfo(_fig0.get()).GetCaption();
  _nxt->Brush->Color = clBlack;
  _nxt->FillRect(TRect(0, 0, _M, _M));
  int minx=1000, miny=1000, maxx=-1000, maxy=-1000;
  for(TPosIt i=_fig0->GetItems().begin(); i!=_fig0->GetItems().end(); ++i) {
    if(miny>i->first) miny=i->first;
    if(maxy<i->first) maxy=i->first;
    if(minx>i->second) minx=i->second;
    if(maxx<i->second) maxx=i->second;
  }
  int x=maxx-minx+1, y=maxy-miny+1, max=x>y?x:y, n=_M/(max+2), offx=(_M-n*x)/2-n*minx, offy=(_M-n*y)/2-n*miny;
  _nxt->Brush->Color = clWhite;
  for(TPosIt i=_fig0->GetItems().begin(); i!=_fig0->GetItems().end(); ++i)
    _nxt->FillRect(TRect(offx+n*i->second, offy+n*i->first, offx+n*(i->second+1)-1, offy+n*(i->first+1)-1));
}
//---------------------------------------------------------------------------

// Сохраняемся
void __fastcall TTetris::Save(const String &strFileName) {
  TFilePtr outp(strFileName, "w+b");
  int n=0;
  fwrite(&n, sizeof(n), 1, outp);
  fwrite(&_n, sizeof(_n), 1, outp);
  Set();
  for(int i=0; i<_n; ++i)
    for(int j=0; j<_n; ++j)
      fwrite(&_data[i][j].first, sizeof(_data[i][j].first), 1, outp);
  Set(true);
  fwrite(&_count, sizeof(_count), 1, outp);
  n=_line.size();
  fwrite(&n, sizeof(n), 1, outp);
  fwrite(&_line[0], sizeof(_line[0]), n, outp);
  n=_move_count.size();
  fwrite(&n, sizeof(n), 1, outp);
  fwrite(&_move_count[0], sizeof(_move_count[0]), n, outp);
  FigGen->Save(outp, _fig.get(), -1);
  FigGen->Save(outp, _fig0.get(), -2);
  FigGen->SaveStat(outp);
  n = GetCheckSum(outp);
  fwrite(&n, sizeof(n), 1, outp);
}
//---------------------------------------------------------------------------

// Загружаемся
void __fastcall TTetris::Load(const String &strFileName) {
  EStatMode stat_mode;
  {
    TFilePtr inp(strFileName, "r+b");
    int n=0;
    fread(&n, sizeof(n), 1, inp);
    if(n-GetCheckSum(inp, sizeof(n))) throw Exception("Сохраненный файл имеет неверный формат");
    fread(&n, sizeof(n), 1, inp);
    if(n-_n) throw Exception("Сохраненный файл не подходит к этой конфигурации игры");
    for(int i=0; i<_n; ++i) for(int j=0; j<_n; ++j) fread(&_data[i][j].first, sizeof(_data[i][j].first), 1, inp);
    fread(&_count, sizeof(_count), 1, inp);
    fread(&n, sizeof(n), 1, inp);
    _line.resize(n);
    fread(&_line[0], sizeof(_line[0]), n, inp);
    fread(&n, sizeof(n), 1, inp);
    fread(&_move_count[0], sizeof(_move_count[0]), n, inp);
    _fig.reset(FigGen->Load(inp));
    _fig0.reset(FigGen->Load(inp));
    stat_mode = FigGen->LoadStat(inp);
  }
  if(stat_mode>e_Old && ID_YES==Application->MessageBox(String().sprintf("Статистика в сохраненном файле, вероятно испорчена:\n%s\n\nСтереть испорченную сттистику?", e_BadCount==stat_mode?"изменилось количество фигур":"изменились наименования фигур").c_str(), "Внимание!", MB_YESNO|(e_BadCount==stat_mode?MB_ICONWARNING:MB_ICONINFORMATION|MB_DEFBUTTON2)))
    FigGen->ClearStat();
  Set(true);
  Preview();
  SetView();
  Paint();
}
//---------------------------------------------------------------------------

// Считаем контрольную сумму файла
int __fastcall GetCheckSum(FILE *f, int pos) {
  fflush(f);
  int res = -1;
  fseek(f, 0, 2);
  int len = ftell(f)-sizeof(res);
  fseek(f, sizeof(res), 0);
  char *data = new char[len];
  fread(data, len, 1, f);
  for(int i=0; i<len; ++i) {
    int c=res<0 ? 1 : 0;
    res <<= 1;
    res |= c;
    res ^= data[i];
  }
  delete[] data;
  fseek(f, pos, 0);
  return res & 0x7fffffff;
}
//---------------------------------------------------------------------------

