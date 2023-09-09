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
#ifndef aboutH
#define aboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TdlgAbout : public TForm
{
__published:	// IDE-managed Components
  TButton *btnOk;
  TMemo *mInfo;
  void __fastcall btnOkClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TdlgAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TdlgAbout *dlgAbout;
//---------------------------------------------------------------------------
#endif
