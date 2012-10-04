//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ConnectKeeper.h"
#include "Functions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

// Конструктор
TConnectKeeper *ConnectKeeper=0;
__fastcall TdmConnectKeeper::TdmConnectKeeper(const String &Reg, TLoggerPtr L) : TDataModule(static_cast<TComponent*>(0)), _log(L), _con(TdmConnect::GetInstance()), _keep_alive(TdmConnect::GetInstance()), _connected(false) {
  _log->Info("Хранитель соединения создан");
  _con_param.Set("Host",          ReadDataKeyRegedit(HKEY_LOCAL_MACHINE, Reg+"CONNECTED\\SERVER", "VALUE"));
  _con_param.Set("DatabaseName",  ReadDataKeyRegedit(HKEY_LOCAL_MACHINE, Reg+"CONNECTED\\DATABASE", "VALUE"));
  _con_param.Set("User",          ReadDataKeyRegedit(HKEY_LOCAL_MACHINE, Reg+"CONNECTED\\user_name", "VALUE"));
  _con_param.Set("Password",      ReadDataKeyRegedit(HKEY_LOCAL_MACHINE, Reg+"CONNECTED\\password", "VALUE"));
  _con_param.Set("CType",         ReadDataKeyRegedit(HKEY_LOCAL_MACHINE, Reg+"CONNECTED\\lc_ctype", "VALUE"));
  Timer->Enabled = true;
}
//---------------------------------------------------------------------------

// Деструктор
void __fastcall TdmConnectKeeper::DataModuleDestroy(TObject *Sender) {
  _log->Info("Хранитель соединения уничтожен");
}
//---------------------------------------------------------------------------

// Проверяем коннект
void __fastcall TdmConnectKeeper::TimerTimer(TObject *Sender) {
  // Коннекта нат, пытаемся поднять
  if(!_keep_alive->IsActive()) {
    try {
      if(_connected)
        _log->Warning("Соединение утеряно");
      _log->Info("Попытка установить соединение");
      _keep_alive.reset(TdmConnectImpl::GetInstance(_con_param));
      _con.reset(TdmConnectImpl::GetInstance(_con_param));
      // Удалось поднять коннект, рассылаем уведомления
      if(!_connected) {
        _connected = true;
        _log->Info("Соединение установлено");
        for(TNotifyEventIt i=_on_connect.begin(); i!=_on_connect.end(); ++i) {
          try {
            (*i)(Sender);
          }
          catch (Exception &E) {
            _log->Error(E.Message);
          }
        }
      }
    }
    catch(Exception &E) {
      _log->Error(E.Message);
      _keep_alive.reset(TdmConnect::GetInstance());
      _con.reset(TdmConnect::GetInstance());
      // Коннект поднять не удалось, рассылаем уведомления
      if(_connected) {
        _connected = false;
        for(TNotifyEventIt i=_on_disconnect.begin(); i!=_on_disconnect.end(); ++i) {
          try {
            (*i)(Sender);
          }
          catch (Exception &E) {
            _log->Error(E.Message);
          }
        }
      }
    }
  }
}
//---------------------------------------------------------------------------
