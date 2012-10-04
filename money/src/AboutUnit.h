//----------------------------------------------------------------------------
#ifndef AboutUnitH
#define AboutUnitH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include <memory>
//----------------------------------------------------------------------------
class TfmAbout : public TForm {
__published:
	TPanel *Panel1;
	TImage *ProgramIcon;
  TLabel *LegalCopyright;
	TButton *OKButton;
  TLabel *LegalTrademarks;
  TLabel *ProductName;
  TLabel *Comments;
private:
typedef std::auto_ptr<TfmAbout> Ptr;
	virtual __fastcall TfmAbout();
public:
static Ptr GetInstance() {return Ptr(new TfmAbout());}
};
//----------------------------------------------------------------------------
typedef TfmAbout TAboutForm;
#endif
