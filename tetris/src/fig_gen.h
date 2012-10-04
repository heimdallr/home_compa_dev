//---------------------------------------------------------------------------

#ifndef fig_genH
#define fig_genH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <msxmldom.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
#include "figure.h"
#include <map>
//---------------------------------------------------------------------------

// “ип указател€ на конструкторы форм
typedef TFigure* __fastcall (*TGetFigure) (int, const TPos&, const TPosList&);
//---------------------------------------------------------------------------

// Ёлемент фабрики форм
class TFactoryItem {
  String _class, _caption;
  TPosList _items;
public:
  TGetFigure GetFigure;
  __fastcall TFactoryItem() : _class(""), _caption(""), GetFigure(0) {}
  __fastcall TFactoryItem(const String &cl, const String &caption, const TPosList &items, const TGetFigure F) : _class(cl), _caption(caption), _items(items), GetFigure(F) {}
  const TFactoryItem& __fastcall operator=(const TFactoryItem &rh) {_class=rh._class; _caption=rh._caption; _items=rh._items; GetFigure=rh.GetFigure; return *this;}
  __fastcall ~TFactoryItem() {}
  const String& GetClass() const {return _class;}
  const String& GetCaption() const {return _caption;}
  const TPosList& GetItems() const {return _items;}
};
//---------------------------------------------------------------------------

typedef std::vector<TFactoryItem> TFactory;
typedef std::map<String, TGetFigure> TClassMap;
typedef TClassMap::iterator TClassIt;
typedef std::vector<int> TIntVector;
typedef TIntVector::iterator TIntIt;
//---------------------------------------------------------------------------

// –езультат загрузки статистики
enum EStatMode {
  e_New=0,
  e_Old,
  e_BadCount,
  e_BadCaption
};
//---------------------------------------------------------------------------

class TdmFigGen : public TDataModule {
__published:	// IDE-managed Components
  TXMLDocument *XML;
  void __fastcall DataModuleDestroy(TObject *Sender);
private:	// User declarations
  TFactory _factory, _loaded_factory;
  TClassMap _class;
  TIntVector _class_mapper, _stat;
  String strLog;
  EStatMode _stat_mode;
  TDateTime _stat_begin;
  void __fastcall CreateStandard();
  void __fastcall SetClassList();
  TClassIt __fastcall GetClass(const String &strClass) {TClassIt I=_class.find(strClass); return I==_class.end() ? _class.find("Simple") : I;}
public:		// User declarations
  __fastcall TdmFigGen(const String&, const String&);
  TFigure* __fastcall GetFigure(const TPos&, int &id_next_fig_cheat);
  TFigure* __fastcall GetFigure(const TFigure*);
  const TFactoryItem& __fastcall GetInfo(const TFigure *fig) const {return fig->GetId()<0 ? _loaded_factory[-fig->GetId()] : _factory[fig->GetId()];}
  void __fastcall Save(FILE*, const TFigure*, int n);
  TFigure* __fastcall Load(FILE*);
  void __fastcall SaveStat(FILE*);
  EStatMode __fastcall LoadStat(FILE*);
  void __fastcall ClearStat();
};
//---------------------------------------------------------------------------
extern PACKAGE TdmFigGen *FigGen;
//---------------------------------------------------------------------------
#endif
