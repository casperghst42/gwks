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
#ifndef configureH
#define configureH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
#include "data.h"
//---------------------------------------------------------------------------
typedef enum { cancel = 0, delete_item, save_item } conf_return;
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
  TLabel *lbParam;
  TLabel *lbName;
  TEdit *edtParm;
  TEdit *edtName;
  TButton *btnSave;
  TButton *btnDelete;
  TButton *btnCancel;
  void __fastcall btnCancelClick(TObject *Sender);
  void __fastcall btnSaveClick(TObject *Sender);
  void __fastcall btnDeleteClick(TObject *Sender);
  void __fastcall onShow(TObject *Sender);
  void __fastcall onClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
  int currentEdt;
  bool isNew;

  AnsiString stName;
  AnsiString stData;

public:		// User declarations
  __fastcall TForm2(TComponent* Owner);
  bool  isCancel;
  void CurrentSelection( int );
  conf_return result;

  void SetData( AnsiString name, AnsiString data )   { stName = name; stData = data; }
  void GetData( AnsiString& name, AnsiString& data ) { name = stName; data = stData; }
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
