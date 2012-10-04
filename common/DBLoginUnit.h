#ifndef DBLoginUnitH
#define DBLoginUnitH
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <boost/shared_ptr.hpp>
#include "PropertyMap.h"
//---------------------------------------------------------------------------

class TfmLogin : public TForm {
__published:	// IDE-managed Components
  TPanel *pnlBtn;
  TBitBtn *btnOk;
  TActionList *alMain;
  TAction *actOk;
  TPanel *pnlConnectStr;
  TGroupBox *gbHost;
  TPanel *pnlHost;
  TEdit *eHost;
  TGroupBox *gbDatabaseName;
  TPanel *pnaDatabaseName;
  TEdit *eDatabaseName;
  TPanel *pnlUserPwdTop;
  TGroupBox *gbUser;
  TPanel *pnlUser;
  TEdit *eUser;
  TGroupBox *gbPwd;
  TPanel *pnlPwd;
  TEdit *ePwd;
  TPanel *pnlUserPwdBottom;
  TCheckBox *cbSavePwd;
  TGroupBox *gbCType;
  TPanel *pnlCType;
  TEdit *eCType;
  TAction *actCancel;
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall actOkExecute(TObject *Sender);
  void __fastcall actCancelExecute(TObject *Sender);
  void __fastcall eKeyPress(TObject *Sender, char &Key);
  void __fastcall eChange(TObject *Sender);
public:
enum EPropertyChanged {
  pc_Host=1,
  pc_DatabaseName=2,
  pc_User=4,
  pc_Password=8,
  pc_CType=16
};
private:	// User declarations
typedef std::pair<String, TEdit*> TParam;
typedef std::map<EPropertyChanged, TParam> TParamMap;
typedef std::auto_ptr<TParamMap> TParamMapPtr;
  TParamMapPtr __fastcall InitParamMap();
  const TParamMap& __fastcall GetParamMap();
  TParamMap _param_map;
  TNotifyEvent _on_change;
  TPropertyMap &_p;
  int _f;
  __fastcall TfmLogin(TPropertyMap&);
  void __fastcall OnChangeImpl(TObject *Sender) {_f |= dynamic_cast<TComponent*>(Sender)->Tag;}
public:		// User declarations
typedef boost::shared_ptr<TfmLogin> Ptr;
static Ptr GetInstance(TPropertyMap &P) {return Ptr(new TfmLogin(P));}
  bool __fastcall Changed(EPropertyChanged C) {return _f&C;}
};
typedef TfmLogin TDBLoginForm;
//---------------------------------------------------------------------------
#endif
