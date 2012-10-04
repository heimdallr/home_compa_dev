//---------------------------------------------------------------------------

#ifndef OptionsXMLH
#define OptionsXMLH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <msxmldom.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
#include <memory>
#include "Options.h"
#include "CoInit.h"
//---------------------------------------------------------------------------

// Реализация настроек в виде XML-файла
class TdmOptionsXML : public TDataModule {
__published:	// IDE-managed Components
  TXMLDocument *XML;
  void __fastcall DataModuleDestroy(TObject *Sender);
private:	// User declarations
  TCoInit CoInit;
  bool _changed;
  String _file_name;

  _di_IXMLNode __fastcall AddNode(const String &NodeName);
  void __fastcall Set(_di_IXMLNode Node, const String &AttrName, const String &Val) {if(Node) {Node->SetAttribute(AttrName, Val); _changed=true;}}
  String __fastcall Get(_di_IXMLNode Node, const String &AttrName, const String &Def="") const {return Node && Node->HasAttribute(AttrName)? String(Node->GetAttribute(AttrName)) : Def;}
public:		// User declarations
  __fastcall TdmOptionsXML(const String &FileName);
  _di_IXMLNode __fastcall GetNode(const String &NodeName) const;
  void __fastcall Set(const String &NodeName, const String &AttrName, const String &Val) {Set(AddNode(NodeName), AttrName, Val);}
  String __fastcall Get(const String &NodeName, const String &AttrName, const String &Def="") const {return Get(GetNode(NodeName), AttrName, Def);}
  void __fastcall SaveLayout(const TControl*);
  void __fastcall SaveLayout(const TDBGridEh*);
  void __fastcall RestoreLayout(TControl*) const;
  void __fastcall RestoreLayout(TDBGridEh*) const;
};
//---------------------------------------------------------------------------

// Настройки в виде xml-файла
class TOptionsXML : public TOptions {
  std::auto_ptr<TdmOptionsXML> _data;
protected:
  __fastcall TOptionsXML(const String &FileName) : _data(new TdmOptionsXML(FileName)) {}
public:
static Ptr __fastcall GetInstance(const String& FileName="") {return Ptr(Instance=new TOptionsXML(FileName));}
  virtual __fastcall ~TOptionsXML() {}
  virtual void    __fastcall Set(const String &NodeName, const String &AttrName, const String &Val) {_data->Set(NodeName, AttrName, Val);}
  virtual String  __fastcall Get(const String &NodeName, const String &AttrName, const String &Def) const {return _data->Get(NodeName, AttrName, Def);}
  virtual void    __fastcall SaveLayout(const TControl *Control) {_data->SaveLayout(Control);}
  virtual void    __fastcall SaveLayout(const TDBGridEh *Grid) {_data->SaveLayout(Grid);}
  virtual void    __fastcall RestoreLayout(TControl *Control) const {_data->RestoreLayout(Control);}
  virtual void    __fastcall RestoreLayout(TDBGridEh *Grid) const {_data->RestoreLayout(Grid);}
  virtual TPropertyMap __fastcall GetPropMap(const String &NodeName) const {return TPropertyMap(GetNode(NodeName));}
  _di_IXMLNode __fastcall GetNode(const String &NodeName) const {return _data->GetNode(NodeName);}
};
//---------------------------------------------------------------------------
#endif
