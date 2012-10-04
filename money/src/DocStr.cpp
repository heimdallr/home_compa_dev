//---------------------------------------------------------------------------


#pragma hdrstop

#include "DocStr.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

// Запросы для строк
const String
  TDocStr::SelectQuery = "select * from sel_doc_str(:id_doc)",
  TDocStr::AddQuery = "select * from add_doc_str(:id_doc, :id_type, :id_target, :summa, :qty, :note, :id_deposit)",
  TDocStr::SetQuery = "execute procedure set_doc_str(:id, :id_type, :id_target, :summa, :qty, :note, :id_deposit)",
  TDocStr::DelQuery = "execute procedure del_doc_str(:id)";
//---------------------------------------------------------------------------

// Конструктор
__fastcall TDocStr::TDocStr(int IdDoc, TIBTransaction *T) : TDataImpl(SelectQuery, "", T), _id_doc(IdDoc) {
  Reload(_id_doc);
}
//---------------------------------------------------------------------------

// Перезагрузка и переподписка на события (это другой документ)
void __fastcall TDocStr::Reload(int IdDoc) {
  _id_doc = IdDoc;
  _param.Clear();
  _param.Add(ftInteger, "id_doc", _id_doc);
  Load();
  _event.reset();
  _event = TConnect::Instance->SetEventHandler(String().sprintf("doc_%d", IdDoc), OnEvent);
}
//---------------------------------------------------------------------------

// Новая строка
int __fastcall TDocStr::Add(int IdType, int IdTarget, double Summa, double Qty, const String &Note, int IdDeposit) {
  TSQLPtr SQL = TConnect::Instance->GetWriteSQL(AddQuery, false);
  TTranPtr TR(SQL->Transaction);
  SQL->ParamByName("id_doc")->AsInteger = _id_doc;
  SetParam(SQL.get(), IdType, IdTarget, Summa, Qty, Note, IdDeposit);
  int IdStr = SQL->Fields[0]->AsInteger;
  _data->Append();
  _data->FieldByName("id")->AsInteger = IdStr;
  _data->Post();
  SQL->Transaction->Commit();
  return IdStr;
}
//---------------------------------------------------------------------------

// Редактируем строку
void __fastcall TDocStr::Set(int IdType, int IdTarget, double Summa, double Qty, const String &Note, int IdDeposit) const {
  TSQLPtr SQL = TConnect::Instance->GetWriteSQL(SetQuery, false);
  TTranPtr TR(SQL->Transaction);
  SQL->ParamByName("id")->AsInteger = _data->FieldByName("id")->AsInteger;
  SetParam(SQL.get(), IdType, IdTarget, Summa, Qty, Note, IdDeposit);
  SQL->Transaction->Commit();
}
//---------------------------------------------------------------------------

// Заполняем параметры добавляемой/редактируемой строки
void __fastcall TDocStr::SetParam(TIBSQL *SQL, int IdType, int IdTarget, double Summa, double Qty, const String &Note, int IdDeposit) const {
  SQL->ParamByName("id_type")->AsInteger = IdType;
  SQL->ParamByName("id_target")->AsInteger = IdTarget;
  SQL->ParamByName("summa")->AsDouble = Summa;
  SQL->ParamByName("qty")->AsDouble = Qty;
  SQL->ParamByName("note")->AsString = Note;
  if(IdDeposit) SQL->ParamByName("id_deposit")->AsInteger = IdDeposit;
  else SQL->ParamByName("id_deposit")->Clear();
  SQL->ExecQuery();
}
//---------------------------------------------------------------------------

void __fastcall TDocStr::Del() const {
  TSQLPtr SQL = TConnect::Instance->GetWriteSQL(DelQuery, false);
  TTranPtr TR(SQL->Transaction);
  SQL->ParamByName("id")->AsInteger = _data->FieldByName("id")->AsInteger;
  SQL->ExecQuery();
  SQL->Transaction->Commit();
}
//---------------------------------------------------------------------------

