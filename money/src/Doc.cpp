#pragma hdrstop
#include "Doc.h"
#include "TransactionPtr.h"
#include "DataSetLayout.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

const String
  TDoc::SelectQuery = "select * from sel_doc(:date_from, :date_to, :flag)",
  TDoc::AcceptQuery = "execute procedure accept_doc(:id_doc, :state)",
  TDoc::AddQuery = "select id from add_doc(:id_type, :id_deposit, :date_doc, :note)",
  TDoc::SetQuery = "execute procedure set_doc(:id_doc, :date_doc, :note)",
  TDoc::DeleteQuery = "execute procedure del_doc(:id_doc)";
//---------------------------------------------------------------------------

// Конструктор
__fastcall TDoc::TDoc(TDate From, TDate To, TIBTransaction *T) : TDataImpl(SelectQuery, "doc", T), _flag(T)
{
  Reload(From, To);
}
//---------------------------------------------------------------------------

void __fastcall TDoc::Reload(TDate From, TDate To) {
  _param.Clear();
  _param.Add(ftDate, "date_from", From);
  _param.Add(ftDate, "date_to", To);
  _param.Add(ftInteger, "flag", _flag?1:0);
  Load();
}
//---------------------------------------------------------------------------

// Проводим документ
void __fastcall TDoc::Accept() {
  TSQLPtr SQL = TConnect::Instance->GetWriteSQL(AcceptQuery, false);
  TTranPtr T(SQL->Transaction);
  SQL->ParamByName("id_doc")->AsInteger = _data->FieldByName("id")->AsInteger;
  SQL->ParamByName("state")->AsInteger = _data->FieldByName("state")->AsInteger ? 0 : 1;
  SQL->ExecQuery();
  SQL->Transaction->Commit();
}
//---------------------------------------------------------------------------

// Новый документ
int __fastcall TDoc::Add(int IdDocType, int IdDeposit, TDate DateDoc, const String &Note) {
  TSQLPtr SQL = TConnect::Instance->GetWriteSQL(AddQuery, false);
  TTranPtr TR(SQL->Transaction);
  SQL->ParamByName("id_type")->AsInteger = IdDocType;
  SQL->ParamByName("id_deposit")->AsInteger = IdDeposit;
  SQL->ParamByName("date_doc")->AsDate = DateDoc;
  SQL->ParamByName("note")->AsString = Note;
  SQL->ExecQuery();
  int IdDoc = SQL->Fields[0]->AsInteger;
  _data->Append();
  _data->FieldByName("id")->AsInteger = IdDoc;
  _data->Post();
  SQL->Transaction->Commit();
  return IdDoc;
}
//---------------------------------------------------------------------------

// Редактируем документ
void __fastcall TDoc::Set(TDate DateDoc, const String &Note) {
  TSQLPtr SQL = TConnect::Instance->GetWriteSQL(SetQuery, false);
  TTranPtr TR(SQL->Transaction);
  SQL->ParamByName("id_doc")->AsInteger = _data->FieldByName("id")->AsInteger;
  SQL->ParamByName("date_doc")->AsDate = DateDoc;
  SQL->ParamByName("note")->AsString = Note;
  SQL->ExecQuery();
  SQL->Transaction->Commit();
}
//---------------------------------------------------------------------------

// Удаляем документ
void __fastcall TDoc::Delete() {
  TSQLPtr SQL = TConnect::Instance->GetWriteSQL(DeleteQuery, false);
  TTranPtr T(SQL->Transaction);
  SQL->ParamByName("id_doc")->AsInteger = _data->FieldByName("id")->AsInteger;
  SQL->ExecQuery();
  SQL->Transaction->Commit();
}
//---------------------------------------------------------------------------

