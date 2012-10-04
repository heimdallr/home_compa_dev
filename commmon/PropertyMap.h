//---------------------------------------------------------------------------

#ifndef PropertyMapH
#define PropertyMapH
#include <map>
#include <SysUtils.hpp>
#include <XMLDoc.hpp>
//---------------------------------------------------------------------------
class TPropertyMap {
  static String _empty;
  std::map<String, String> _map;
  String _str;
public:
  typedef void __fastcall (__closure *TForEachClosure)(void*, const String&, const String&);
  typedef void __fastcall (*TForEach)(void*, const String&, const String&);
  __fastcall TPropertyMap() {}
  __fastcall TPropertyMap(const _di_IXMLNode&);
  __fastcall TPropertyMap(const String &PropertyString, char PropertyDelimiter=';', char IdValDelimiter='=');
  __fastcall ~TPropertyMap() {}
  const String& __fastcall Get (const String &id) const;
  const String& __fastcall Get () const {return _str;}
  const String& __fastcall operator[](const String &id) const {return Get(id);}
  const int __fastcall Size() const {return _map.size();}
  const bool __fastcall Empty() const {return _map.empty();}
  void __fastcall ForEach(TForEachClosure, void* =0) const;
  void __fastcall ForEach(TForEach, void* =0) const;
  void __fastcall Set(const String &Id, const String &Val) {_map[Id]=Val;}
  TPropertyMap& __fastcall operator+=(const TPropertyMap &r);

  friend TPropertyMap __fastcall operator+(const TPropertyMap &l, const TPropertyMap &r);
};
//---------------------------------------------------------------------------

#endif
