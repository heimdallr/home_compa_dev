//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "OptionsXML.h"
#include "Functions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

/*// Фабрика
TOptions* __fastcall TOptions::GetInstance(const String &FileName) {
  return new TOptionsXML(FileName);
} */
//---------------------------------------------------------------------------

TOptions *TOptions::Instance=0;
// Конструктор
__fastcall TdmOptionsXML::TdmOptionsXML(const String &FileName) : TDataModule(static_cast<TComponent*>(0)), _file_name(FileName), _changed(false) {
  if(_file_name.IsEmpty()) _file_name = ChangeFileExt(GetModuleName(0), ".xml");
  try {
    XML->LoadFromFile(_file_name);
  } catch(Exception &E) {
    throw Exception(String().sprintf("Не удалось загрузить %s:\n%s", _file_name, E.Message));
  }
}
//---------------------------------------------------------------------------

// Деструктор
void __fastcall TdmOptionsXML::DataModuleDestroy(TObject *Sender) {
  if(_changed && XML->Active)
    XML->SaveToFile(_file_name);
}
//---------------------------------------------------------------------------

// Добавляем узел
_di_IXMLNode __fastcall TdmOptionsXML::AddNode(const String &NodeName) {
  ns_Functions::TStrListPtr pList(Split(NodeName, '\\'));
  _di_IXMLNode Res=XML->DocumentElement;
  for(int i=0; i<pList->Count; ++i) {
    _di_IXMLNode Node=Res->ChildNodes->GetNode(pList->Strings[i]);
    if(!Node)
      Res->ChildNodes->Add(Node=XML->CreateNode(pList->Strings[i]));
    Res = Node;
  }
  return Res;
}
//---------------------------------------------------------------------------

// Тянем узел
_di_IXMLNode __fastcall TdmOptionsXML::GetNode(const String &NodeName) const {
  ns_Functions::TStrListPtr pList(Split(NodeName, '\\'));
  _di_IXMLNode Res=XML->DocumentElement;
  for(int i=0; i<pList->Count; ++i) {
    _di_IXMLNode Node=Res->ChildNodes->FindNode(pList->Strings[i]);
    if(!Node) return 0;
    Res = Node;
  }
  return Res;
}
//---------------------------------------------------------------------------

// Сохраняем состояник контрола
void __fastcall TdmOptionsXML::SaveLayout(const TControl *Control) {
  _di_IXMLNode Node=AddNode(String().sprintf("Layout\\%s", GetFullComponentName(Control)));
  Set(Node, "Top", Control->Top);
  Set(Node, "Left", Control->Left);
  Set(Node, "Height", Control->Height);
  Set(Node, "Width", Control->Width);
}
//---------------------------------------------------------------------------

// Восстанавливаем состояние контрола
void __fastcall TdmOptionsXML::RestoreLayout(TControl *Control) const {
  if(_di_IXMLNode Node=GetNode(String().sprintf("Layout\\%s", GetFullComponentName(Control)))) {
    String Val=Get(Node, "Top");
    if(!Val.IsEmpty()) Control->Top = Val.ToInt();
    if(!(Val = Get(Node, "Left")).IsEmpty()) Control->Left = Val.ToInt();
    if(!(Val = Get(Node, "Height")).IsEmpty()) Control->Height = Val.ToInt();
    if(!(Val = Get(Node, "Width")).IsEmpty()) Control->Width = Val.ToInt();
  }
}
//---------------------------------------------------------------------------

// Сохраняем состояник грида
void __fastcall TdmOptionsXML::SaveLayout(const TDBGridEh *Grid) {
  SaveLayout(dynamic_cast<const TControl*>(Grid));
//  Set(GetNode(String().sprintf("Layout\\%s", GetFullComponentName(Grid))), "AutoWidth", Grid->AutoFitColWidths ? "True" : "False");
  for(int i=0; i<Grid->Columns->Count; ++i) {
    if(Grid->Columns->Items[i]->FieldName.IsEmpty()) continue;
    _di_IXMLNode Node=AddNode(String().sprintf("Layout\\%s\\%s", GetFullComponentName(Grid), Grid->Columns->Items[i]->FieldName.UpperCase()));
    Set(Node, "Visible", Grid->Columns->Items[i]->Visible ? "True" : "False");
    Set(Node, "Index", Grid->Columns->Items[i]->Index);
    Set(Node, "Width", Grid->Columns->Items[i]->Width);
    if(clWindow==Grid->Columns->Items[i]->Color)
      Node->AttributeNodes->Delete(L"Color");
    else Set(Node, "Color", Grid->Columns->Items[i]->Color);
  }
}
//---------------------------------------------------------------------------

// Восстанавливаем состояние грида
void __fastcall TdmOptionsXML::RestoreLayout(TDBGridEh *Grid) const {
  std::list<_di_IXMLNode> ToDel;
  RestoreLayout(dynamic_cast<TControl*>(Grid));
  if(_di_IXMLNode Node=GetNode(String().sprintf("Layout\\%s", GetFullComponentName(Grid)))) {
    bool AutoWidth = Grid->AutoFitColWidths;
    Grid->AutoFitColWidths = false;
    for(_di_IXMLNode SubNode=Node->ChildNodes->First(); SubNode; SubNode=SubNode->NextSibling()) {
      for(int i=0; i<Grid->Columns->Count; ++i)
        if(Grid->Columns->Items[i]->FieldName.UpperCase()==SubNode->NodeName) try {
          Grid->Columns->Items[i]->Width = String(SubNode->GetAttribute(L"Width")).ToInt();
          Grid->Columns->Items[i]->Visible = String(SubNode->GetAttribute(L"Visible")) == "True";
          Grid->Columns->Items[i]->Index = String(SubNode->GetAttribute(L"Index")).ToInt();
          if(SubNode->HasAttribute(L"Color"))
            Grid->Columns->Items[i]->Color = static_cast<TColor>(String(SubNode->GetAttribute(L"Color")).ToInt());
          goto found;
        } catch(...) {}
      ToDel.push_back(SubNode);
found:
    }
    Grid->AutoFitColWidths = AutoWidth;
  }
  for(std::list<_di_IXMLNode>::iterator i=ToDel.begin(); i!=ToDel.end(); ++i)
    (*i)->ParentNode->ChildNodes->Delete((*i)->NodeName);
}
//---------------------------------------------------------------------------
