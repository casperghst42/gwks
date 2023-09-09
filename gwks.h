//---------------------------------------------------------------------------
/*
  Author: Casper Pedersen
          casperghst42@fastmail.fm
  
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
//---------------------------------------------------------------------------
#ifndef gwksH
#define gwksH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
#include "data.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
// [HKEY_CLASSES_ROOT\CLSID\{11A1CCE0-D6EE-11CE-AFA5-00608C79BC42}\LocalServer32]
// @="C:\\Novell\\GroupWise\\GRPWISE.EXE"
#define GWREGKEY "\\CLSID\\{11A1CCE0-D6EE-11CE-AFA5-00608C79BC42}\\LocalServer32"

/*
   [HKEY_CLASSES_ROOT\inifile\shell\open\command]
   @=hex(2):25,53,79,73,74,65,6d,52,6f,6f,74,25,5c,53,79,73,74,65,6d,33,32,5c,4e,\
   4f,54,45,50,41,44,2e,45,58,45,20,25,31,00
*/
  
#define EDITINI  "\\inifile\\shell\\open\\command"
//---------------------------------------------------------------------------
#define timer_none 0
#define timer_abort 1
#define timer_launch 2
//---------------------------------------------------------------------------
class TForm1 : public TForm {
__published:	// IDE-managed Components
  TButton *btnConfigure;
  TComboBox *cList;
  TButton *btnLaunch;
  TButton *btnCancel;
  TButton *btnAbout;
  TTimer *tmTimer;
  void __fastcall btnLaunchClick(TObject *Sender);
  void __fastcall btnCancelClick(TObject *Sender);
  void __fastcall btnConfigureClick(TObject *Sender);
  void __fastcall btnNewClick(TObject *Sender);
  void __fastcall onFormCreate(TObject *Sender);
  void __fastcall cListChange(TObject *Sender);
  void __fastcall btnAboutClick(TObject *Sender);
  void __fastcall onTimer(TObject *Sender);
  void __fastcall cListKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
  cpTiniFile *inidata;
  cpTiniFile *confdata;
  int top_pos;
  int left_pos;
  int tmType;
  long tmTimeOut;


  void updateList( int );
  void getGWExe( void );
  void btnCheck( void );
  void getPos( void );
  AnsiString gwExe;
  AnsiString exePath;
  bool  gwInstalled;
  int   idxSelected;

public:		// User declarations
  __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
