//---------------------------------------------------------------------------
#include <memory>
#include <classes.hpp>
#pragma hdrstop

#include "PropertyMap.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

String TPropertyMap::_empty="";
//---------------------------------------------------------------------------

// Подымаем все аттрибуты узла
__fastcall TPropertyMap::TPropertyMap(const _di_IXMLNode &Node) : _str("") {
  int n=Node->GetAttributeNodes()->Count;
  for(int i=0; i<n; ++i) {
    _di_IXMLNode Attr=Node->GetAttributeNodes()->Get(i);
    String Id=Attr->NodeName, Val="";
    try {
      Val=Attr->GetNodeValue();
    } catch(...) {}
    _map[Id] = Val;
    _str += String().sprintf("\"%s\"=\"%s\" ", Id.c_str(), Val.c_str());
  }
}
//---------------------------------------------------------------------------

// Разбираем строку с делимитерами
__fastcall TPropertyMap::TPropertyMap(const String &PropertyString, char PropertyDelimiter, char IdValDelimiter) : _str("") {
  std::auto_ptr<TStringList> pOut(new TStringList), pIn(new TStringList);
  pOut->Delimiter     = PropertyDelimiter;
  pOut->DelimitedText = PropertyString;
  pIn->Delimiter      = IdValDelimiter;
  for(int i=0; i<pOut->Count; ++i) {
    pIn->DelimitedText = pOut->Strings[i];
    _map[pIn->Strings[0]] = pIn->Strings[1];
    _str += String().sprintf("\"%s\"=\"%s\" ", pIn->Strings[0].c_str(), pIn->Strings[1].c_str());
  }
}
//---------------------------------------------------------------------------

// Отдаем параметр
const String& __fastcall TPropertyMap::Get(const String &id) const {
  std::map<String, String>::const_iterator I=_map.find(id);
  return I==_map.end() ? _empty : I->second;
}
//---------------------------------------------------------------------------

// Пробегаем по всем
void __fastcall TPropertyMap::ForEach(TForEach F, void *Param) const {
  for(std::map<String, String>::const_iterator i=_map.begin(); i!=_map.end(); ++i)
    F(Param, i->first, i->second);
}
//---------------------------------------------------------------------------

// Пробегаем по всем
void __fastcall TPropertyMap::ForEach(TForEachClosure F, void *Param) const {
  for(std::map<String, String>::const_iterator i=_map.begin(); i!=_map.end(); ++i)
    F(Param, i->first, i->second);
}
//---------------------------------------------------------------------------

TPropertyMap& __fastcall TPropertyMap::operator+=(const TPropertyMap &r) {
  for(std::map<String, String>::const_iterator i=r._map.begin(); i!=r._map.end(); ++i)
    this->_map[i->first] = i->second;
  return *this;
}


TPropertyMap __fastcall operator+(const TPropertyMap &l, const TPropertyMap &r) {
  TPropertyMap Res(l);
  for(std::map<String, String>::const_iterator i=r._map.begin(); i!=r._map.end(); ++i)
    Res._map[i->first] = i->second;
  return Res;
}
//---------------------------------------------------------------------------

