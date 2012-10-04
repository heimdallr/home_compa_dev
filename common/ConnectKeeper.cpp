//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ConnectKeeper.h"
#include "Functions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

// �����������
TConnectKeeper *ConnectKeeper=0;
__fastcall TdmConnectKeeper::TdmConnectKeeper(const String &Reg, TLoggerPtr L) : TDataModule(static_cast<TComponent*>(0)), _log(L), _con(TdmConnect::GetInstance()), _keep_alive(TdmConnect::GetInstance()), _connected(false) {
  _log->Info("��������� ���������� ������");
  _con_param.Set("Host",          ReadDataKeyRegedit(HKEY_LOCAL_MACHINE, Reg+"CONNECTED\\SERVER", "VALUE"));
  _con_param.Set("DatabaseName",  ReadDataKeyRegedit(HKEY_LOCAL_MACHINE, Reg+"CONNECTED\\DATABASE", "VALUE"));
  _con_param.Set("User",          ReadDataKeyRegedit(HKEY_LOCAL_MACHINE, Reg+"CONNECTED\\user_name", "VALUE"));
  _con_param.Set("Password",      ReadDataKeyRegedit(HKEY_LOCAL_MACHINE, Reg+"CONNECTED\\password", "VALUE"));
  _con_param.Set("CType",         ReadDataKeyRegedit(HKEY_LOCAL_MACHINE, Reg+"CONNECTED\\lc_ctype", "VALUE"));
  Timer->Enabled = true;
}
//---------------------------------------------------------------------------

// ����������
void __fastcall TdmConnectKeeper::DataModuleDestroy(TObject *Sender) {
  _log->Info("��������� ���������� ���������");
}
//---------------------------------------------------------------------------

// ��������� �������
void __fastcall TdmConnectKeeper::TimerTimer(TObject *Sender) {
  // �������� ���, �������� �������
  if(!_keep_alive->IsActive()) {
    try {
      if(_connected)
        _log->Warning("���������� �������");
      _log->Info("������� ���������� ����������");
      _keep_alive.reset(TdmConnectImpl::GetInstance(_con_param));
      _con.reset(TdmConnectImpl::GetInstance(_con_param));
      // ������� ������� �������, ��������� �����������
      if(!_connected) {
        _connected = true;
        _log->Info("���������� �����������");
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
      // ������� ������� �� �������, ��������� �����������
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
