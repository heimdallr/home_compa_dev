//---------------------------------------------------------------------------

#ifndef CatalogUnitH
#define CatalogUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DBGridEh.hpp"
#include "GridsEh.hpp"
#include "DBGridEhGrouping.hpp"
#include <DB.hpp>
#include <DBClient.hpp>
#include <ActnList.hpp>
#include <Menus.hpp>
//#include <memory>
//#include <list>
#include "Connect.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

namespace ns_Catalog {

// Инициализатор поля справочника
class TFieldInitItem {
friend class TInit;
friend class TfmCatalog;
  int _width;
  String _name;
  bool _hide_dup;
  __fastcall TFieldInitItem(const String &Name, int Width, bool HideDup=false) : _width(Width), _name(Name), _hide_dup(HideDup) {}
public:
  __fastcall ~TFieldInitItem() {}
  TFieldInitItem& __fastcall operator=(const TFieldInitItem &r) {if(&r!=this){_width=r._width; _name=r._name;} return *this;}
};
typedef std::list<TFieldInitItem> TFieldInitList;
typedef TFieldInitList::const_iterator TFieldInitIt;
//---------------------------------------------------------------------------

// Инициализатор справочника
class TInit {
friend class TfmCatalog;
  const String _caption, _id_field_name, _query;
  TQueryParams _params;
  TFieldInitList _field;
  const Variant _def;
  TDSPtr __fastcall GetDataSet() const;
public:
  __fastcall TInit(const String &IdField, const String &Query, const String &Caption="Укажите значение из списка", const Variant &Def=-1);
  __fastcall ~TInit() {}
  TQueryParams& __fastcall GetParams() {return _params;}
  TInit& __fastcall AddField(const String &Name, int Width, bool HideDup=false) {_field.push_back(TFieldInitItem(Name, Width, HideDup)); return *this;}
};
//---------------------------------------------------------------------------

// Простой справочник
class TfmCatalog : public TForm {
__published:	// IDE-managed Components
  TDBGridEh *dbgData;
  TDataSource *dsrcData;
  TActionList *alMain;
  TAction *actOk;
  TAction *actCancel;
  TPopupMenu *pmMain;
  TMenuItem *miOk;
  TMenuItem *miCancel;
  TClientDataSet *dsData;
  void __fastcall actOkExecute(TObject *Sender);
  void __fastcall actCancelExecute(TObject *Sender);
private:	// User declarations
  const String _id_field_name;
public:		// User declarations
  __fastcall TfmCatalog(const TInit&);
  TDSPtr __fastcall GetDataSet();
};
//---------------------------------------------------------------------------

typedef std::auto_ptr<TfmCatalog> TCatalogPtr;
TDSPtr __fastcall Get(const TInit&);
}
//---------------------------------------------------------------------------
#endif
