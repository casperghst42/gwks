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
#include <vcl.h>
#pragma hdrstop

#include "configure.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner )
  : TForm(Owner)
{
  isCancel = false;
  currentEdt = -1;
  isNew = true;

  edtParm->Text = "";
  edtName->Text = "";
}

//---------------------------------------------------------------------------
void TForm2::CurrentSelection( int current )
{
  currentEdt = current;
  isNew = ( current == -1 );
  if( isNew )
    btnDelete->Enabled = false;
}

//---------------------------------------------------------------------------
void __fastcall TForm2::btnCancelClick(TObject *Sender)
{
  this->Close( );
  isCancel = true;
  ModalResult = mrCancel;
  result = cancel;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnSaveClick(TObject *Sender)
{
  this->Close( );
  isCancel = false;
  ModalResult = mrOk;
  result = save_item;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::btnDeleteClick(TObject *Sender)
{
  this->Close( );
  isCancel = false;
  ModalResult = mrOk;
  result = delete_item;
}
//---------------------------------------------------------------------------



void __fastcall TForm2::onShow(TObject *Sender)
{
  edtName->Text = stName;
  edtParm->Text = stData;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::onClose(TObject *Sender, TCloseAction &Action)
{
  stName = edtName->Text;
  stData = edtParm->Text;
}
//---------------------------------------------------------------------------

