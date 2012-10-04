#ifndef DataSetScrollH
#define DataSetScrollH
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Connect.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------

class TdmDataSetScroll : public TDataModule {
__published:	// IDE-managed Components
  TTimer *Timer;
  void __fastcall TimerTimer(TObject *Sender);
private:	// User declarations
  __fastcall TdmDataSetScroll(TConnect*);
public:		// User declarations

class TDataSetScroller {
class TDataSetOpener {
  TConnect *_con;
  TClientDataSet *_data;
  const String _query, _id_field;
public:
typedef std::auto_ptr<TDataSetOpener> Ptr;
  __fastcall TDataSetOpener(TConnect *Con, TClientDataSet *Data, const String &Query, const String &IdFieldName) : _con(Con), _data(Data), _query(Query), _id_field(IdFieldName) {}
  void Open(int Id) {
    Variant Key=String("-96678686");
    if(_data->Active && !_id_field.IsEmpty()) Key=_data->FieldByName(_id_field)->Value;
    _data->Data = _con->GetReadDataSet(String().sprintf(_query.c_str(), Id))->Data;
    if(Key.IsEmpty() || !_data->Locate(_id_field, Key, TLocateOptions()))
      _data->First();
//    if(_data->AfterScroll) _data->AfterScroll(_data);
  }
  void Close() {_data->Close();}
};
  TConnect *_con;
  TClientDataSet *_data;
  TDataSetNotifyEvent _after_scroll;
  const String _id_field_name;
  int _count;
  std::list<TDataSetOpener*> _children;
  std::list<TDataSetOpener::Ptr> _children_ptr;
  void __fastcall Reset(TDataSet *dsData) {_count=3; _after_scroll(dsData);}
public:
typedef std::auto_ptr<TDataSetScroller> Ptr;
  __fastcall TDataSetScroller(TConnect *Con, TClientDataSet *Data, const String &IdFieldName) : _con(Con), _data(Data), _id_field_name(IdFieldName), _after_scroll(_data->AfterScroll) {
    _data->AfterScroll = Reset;
    Reset(_data);
  }
  TDataSetScroller* __fastcall Add(TClientDataSet *Data, const String &Query, const String &IdFieldName) {_children.push_back(new TDataSetOpener(_con, Data, Query, IdFieldName)); _children_ptr.push_back(TDataSetOpener::Ptr(_children.back())); return this;}
  void Run(TConnect*);
  void RunForce(TConnect*);
};
private:	// User declarations
  TConnect *_con;
  std::list<TDataSetScroller*> _data;
  std::list<TDataSetScroller::Ptr> _data_ptr;

public:
static TdmDataSetScroll* __fastcall GetInstance(TConnect *Con) {return new TdmDataSetScroll(Con);}
typedef std::auto_ptr<TdmDataSetScroll> Ptr;
  TDataSetScroller* __fastcall Add(TClientDataSet *Data, const String &IdFieldName) {_data.push_back(new TDataSetScroller(_con, Data, IdFieldName)); _data_ptr.push_back(TDataSetScroller::Ptr(_data.back())); return _data.back();}
  void __fastcall UpdateForce();
};
typedef TdmDataSetScroll TDataSetScrollDirector;
//---------------------------------------------------------------------------
#endif
