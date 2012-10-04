//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "fig_gen.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

// Заполняем словарь конструкторов фигур, пополняем при добавлении новых классов
void __fastcall TdmFigGen::SetClassList() {
  _class["Simple"] = _class[""] = GetTFigure;
  _class["Crash"] = GetTFigureCrash;
}
//---------------------------------------------------------------------------

// Хранилище фигур, инициализация
TdmFigGen *FigGen=0;
__fastcall TdmFigGen::TdmFigGen(const String &strX, const String &strL) : TDataModule(static_cast<TComponent*>(0)), strLog(strL), _stat_mode(e_New), _stat_begin(Now()) {
  SetClassList();
  _loaded_factory.push_back();
  try {
    XML->LoadFromFile(strX);
    for(_di_IXMLNode fig=XML->DocumentElement->ChildNodes->First(); fig; fig=fig->NextSibling()) {
      if(fig->HasAttribute(String("Disable")) && String(fig->GetAttribute(String("Disable")))=="1") continue;
      if(int n = fig->HasAttribute(String("Repeat")) ? String(fig->GetAttribute(String("Repeat"))).ToInt() : 1) {
        String strClass = fig->HasAttribute(String("Class")) ? String(fig->GetAttribute(String("Class"))) : String("Simple");
        String strCaption = fig->HasAttribute(String("Caption")) ? String(fig->GetAttribute(String("Caption"))) : String("");
        TPosList items;
        for(_di_IXMLNode item=fig->ChildNodes->GetNode(String("Items"))->ChildNodes->First(); item; item=item->NextSibling()) {
          if(item->HasAttribute(String("Disable")) && String(item->GetAttribute(String("Disable")))=="1") continue;
          items.push_back(TPos(String(item->GetAttribute("Y")).ToInt(), String(item->GetAttribute("X")).ToInt()));
        }
        TClassIt I = GetClass(strClass);
        _factory.push_back(TFactoryItem(I->first, strCaption, items, I->second));
        for(int i=0; i<n; ++i)
          _class_mapper.push_back(_factory.size()-1);
      }
    }
    _stat.resize(_factory.size()+1);
    XML->Active = false;
  }
  catch(...) {
//    Application->MessageBox(String().sprintf("Не удалось считать данные \"%s\"\nБудут доступен только стандартный набор фигур", strFileName).c_str(), "Внимание!", MB_ICONWARNING);
    CreateStandard();
  }
}
//---------------------------------------------------------------------------

// Делаем новую фигуру
TFigure* __fastcall TdmFigGen::GetFigure(const TPos &pos, int &id_next_fig_cheat) {
  int n = id_next_fig_cheat>=0 && id_next_fig_cheat<signed(_factory.size()) ? id_next_fig_cheat : _class_mapper[random(_class_mapper.size())];
  id_next_fig_cheat = -1;
  ++_stat[n+1];
  ++_stat[0];
  TFigure *res=_factory[n].GetFigure(n, pos, _factory[n].GetItems());
  for(int i=random(4); i>0; --i)
    res->Rotate();
  return res;
}
//---------------------------------------------------------------------------

// Копируем фигуру
TFigure* __fastcall TdmFigGen::GetFigure(const TFigure *fig) {
  return GetInfo(fig).GetFigure(fig->GetId(), fig->GetPos(), fig->GetItems());
}
//---------------------------------------------------------------------------

// Делаем стандартный набор фигур
void __fastcall TdmFigGen::CreateStandard() {
  int data[] = {
    0, 0, 1, 0, 2, 0, 3, 0,
    0, 0, 1, 0, 0, 1, 1, 1,
    0, 0, 1, 0, 2, 0, 2, 1,
    0, 0, 1, 0, 2, 0, 2, -1,
    0, 0, 1, -1, 1, 0, 1, 1,
    0, 0, 0, -1, 1, 0, 1, 1,
    0, 0, 0, 1, 1, 0, 1, -1
  };
  char *caption[] = {"Палка", "Квадрат", "Буква Г", "Не буква Г", "Горка", "Лесенка вверх", "Лесенка вниз"};
  int n = sizeof(data) / sizeof(data[0]);
  for(int i=0; i<n;) {
    TPosList items;
    items.push_back(TPos(data[i++], data[i++]));
    items.push_back(TPos(data[i++], data[i++]));
    items.push_back(TPos(data[i++], data[i++]));
    items.push_back(TPos(data[i++], data[i++]));
    _factory.push_back(TFactoryItem("Simple", caption[i>>3-1], items, GetTFigure));
    _class_mapper.push_back(_factory.size()-1);
  }
}
//---------------------------------------------------------------------------

// Мегакодировщик
char* __fastcall codec(char *src, int len) {
  static char dst[256];
  char pwd[] = "Александр Чирятьев из Новосибирска написал этот тетрис просто так, а эта строка - чистый стеб";
  for(int i=0; i<len; ++i)
    dst[i] = src[i]^pwd[i%sizeof(pwd)];
  dst[len] = 0;
  return dst;
}
//---------------------------------------------------------------------------

// Сохраняем фигуру в файл
void __fastcall TdmFigGen::Save(FILE *outp, const TFigure *fig, int id) {
  fwrite(&id, sizeof(id), 1, outp);
  const TFactoryItem &item=GetInfo(fig);
  String strClass=item.GetClass(), strCaption=item.GetCaption();
  id = strClass.Length();
  fwrite(&id, sizeof(id), 1, outp);
  fwrite(codec(strClass.c_str(), id), id, 1, outp);
  id = strCaption.Length();
  fwrite(&id, sizeof(id), 1, outp);
  fwrite(codec(strCaption.c_str(), id), id, 1, outp);
  fwrite(&fig->GetPos().first, sizeof(fig->GetPos().first), 1, outp);
  fwrite(&fig->GetPos().second, sizeof(fig->GetPos().second), 1, outp);
  id = fig->GetItems().size();
  fwrite(&id, sizeof(id), 1, outp);
  for(TPosIt i=fig->GetItems().begin(); i!=fig->GetItems().end(); ++i) {
    fwrite(&i->first, sizeof(i->first), 1, outp);
    fwrite(&i->second, sizeof(i->second), 1, outp);
  }
}
//---------------------------------------------------------------------------

// Подымаем фигуру из сохраненки
TFigure* __fastcall TdmFigGen::Load(FILE *inp) {
  int t, id;
  char buf[256];
  String strClass, strCaption;
  fread(&id, sizeof(id), 1, inp);
  fread(&t, sizeof(t), 1, inp);
  fread(buf, t, 1, inp); strClass = codec(buf, t);
  fread(&t, sizeof(t), 1, inp);
  fread(buf, t, 1, inp); strCaption = codec(buf, t);
  TPos pos;
  fread(&pos.first, sizeof(pos.first), 1, inp);
  fread(&pos.second, sizeof(pos.second), 1, inp);
  fread(&t, sizeof(t), 1, inp);
  TPosList items;
  for(int i=0; i<t; ++i) {
    TPos pos;
    fread(&pos.first, sizeof(pos.first), 1, inp);
    fread(&pos.second, sizeof(pos.second), 1, inp);
    items.push_back(pos);
  }
  TClassIt I=GetClass(strClass);
  _loaded_factory.push_back(TFactoryItem(I->first, strCaption, items, I->second));
  return _loaded_factory.back().GetFigure(id, pos, items);
}
//---------------------------------------------------------------------------

// Деструктор
void __fastcall TdmFigGen::DataModuleDestroy(TObject *Sender) {
  try {
    // Пишем статистику по фигурам
    TFilePtr outp(strLog, "at");
    String strStatBegin=_stat_begin.FormatString("dd.mm.yyyy hh:nn:ss");
    fprintf(outp, "%s\n", Now().FormatString("dd.mm.yyyy hh:nn:ss"));
    switch(_stat_mode) {
      case e_New: fprintf(outp, "Статистика новой сессии, начата %s\n\n", strStatBegin); break;
      case e_Old: fprintf(outp, "Статистика начатой ранее (%s) сессии\n\n", strStatBegin); break;
      case e_BadCount: fprintf(outp, "Статистика начатой ранее (%s) сессии,\nвероятно испорчена (неправильное количество фигур)\n\n", strStatBegin); break;
      case e_BadCaption: fprintf(outp, "Статистика начатой ранее (%s) сессии,\nвероятно испорчена (неправильные наименования фигур)\n\n", strStatBegin); break;
    }
    fprintf(outp, "Выданы фигуры\n");
    for(unsigned int i=1; i<_factory.size(); ++i)
      fprintf(outp, "%d\t(%.3f)\t\t\"%s\"\n", _stat[i], double(_stat[i])*_class_mapper.size()/_stat[0], _factory[i-1].GetCaption());
    fprintf(outp, "Итого\t\%d\t(%d)\n\n", _stat[0], _class_mapper.size());
  }catch(...){}
}
//---------------------------------------------------------------------------

// Сохраняем статистику
void __fastcall TdmFigGen::SaveStat(FILE *outp) {
  fwrite(&_stat_begin, sizeof(_stat_begin), 1, outp);
  unsigned int n=_stat.size();
  fwrite(&n, sizeof(n), 1, outp);
  fwrite(&_stat[0], sizeof(_stat[0]), n, outp);
  for(unsigned int i=0; i<n-1; ++i) {
    String strCaption = i<_factory.size() ? _factory[i].GetCaption() : String("");
    int k=strCaption.Length();
    fwrite(&k, sizeof(k), 1, outp);
    fwrite(codec(strCaption.c_str(), k), k, 1, outp);
  }
}
//---------------------------------------------------------------------------

// Загружаем статистику
EStatMode __fastcall TdmFigGen::LoadStat(FILE *inp) {
  fread(&_stat_begin, sizeof(_stat_begin), 1, inp);
  unsigned int n=0;
  fread(&n, sizeof(n), 1, inp);
  if(_stat.size()==n) _stat_mode = e_Old;
  else {
    _stat_mode = e_BadCount;
    if(_stat.size()<n)
      _stat.resize(n);
  }
  fread(&_stat[0], sizeof(_stat[0]), n, inp);
  for(unsigned int i=0; i<n-1; ++i) {
    char buf[256];
    int k;
    fread(&k, sizeof(k), 1, inp);
    fread(buf, k, 1, inp);
    if(_stat_mode<e_BadCount && i<_factory.size() && _factory[i].GetCaption()!=codec(buf, k))
      _stat_mode = e_BadCaption;
  }
  return _stat_mode;
}
//---------------------------------------------------------------------------

// Чистим статистику
void __fastcall TdmFigGen::ClearStat() {
  _stat_mode = e_New;
  _stat_begin = Now();
  _stat.assign(_factory.size()+1, 0);
}
//---------------------------------------------------------------------------

