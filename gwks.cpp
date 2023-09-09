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

#include "gwks.h"
#include "configure.h"
#include "about.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner)
{
  gwExe = "";
  exePath = "";
  gwInstalled = false;
  idxSelected = -1;
  tmType = 0;
  tmTimeOut = 0;
}
//---------------------------------------------------------------------------
void TForm1::getPos( void )
{
  top_pos = this->Top;
  left_pos = this->Left;

  confdata->SetData("Top", AnsiString( top_pos ) );
  confdata->SetData("Left", AnsiString( left_pos ) );
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnLaunchClick(TObject *Sender)
{
// UINT WINAPI WinExec( LPCSTR lpCmdLine, UINT uCmdShow );
  if( idxSelected < 0 )
    return;

  AnsiString app = gwExe;
  AnsiString data;
  long ret = -1;
  if( inidata->GetData( idxSelected, data ) )
  {
    confdata->SetData( "LastUsed", AnsiString( idxSelected ) );
    app += " " + data;
    ret = WinExec( app.c_str( ), SW_SHOW );
    if( ret > 32 )
    {
      getPos( );
      confdata->WriteFile( );
      inidata->WriteFile( );
      Application->Terminate( );
    }
    else
      Application->MessageBoxA( "Cannot load GRPWISE.EXE", "Error", MB_OK | MB_ICONASTERISK );
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnCancelClick(TObject *Sender)
{
  Application->Terminate( );
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnConfigureClick(TObject *Sender)
{
  TRegistry *treg = new TRegistry( );
  treg->RootKey =  HKEY_CLASSES_ROOT;
  if( treg->OpenKey( EDITINI, false ) )
  {
    AnsiString sysroot = AnsiString( getenv( "SystemRoot" ) );
    AnsiString regstr = treg->ReadString("");
    int s_pos = regstr.AnsiPos("\\");
    AnsiString iniEdit = sysroot + regstr.SubString( s_pos, regstr.AnsiPos(" ") - s_pos );
    iniEdit += " " + exePath + "gwks.ini";

    getPos( );
    confdata->WriteFile( );
    inidata->WriteFile( );    

    long ret = WinExec( iniEdit.c_str(), SW_SHOW );
    if( ret > 32 )
      Application->Terminate( );
    else
      Application->MessageBoxA( "Cannot load NOTEPAD.EXE", "Error", MB_OK | MB_ICONASTERISK );
  }

  // Application->Terminate( );

/*  if( idxSelected < 0 )
    return;


  TForm2 *confForm = new TForm2( this );
  confForm->CurrentSelection( 0 );

  AnsiString name;
  AnsiString data;
  inidata->GetName( idxSelected, name );
  inidata->GetData( idxSelected, data );

  confForm->SetData( name, data );

  int ret = confForm->ShowModal( );

  if( ret )
  {
    if( confForm->result == delete_item )
    {
      inidata->DelData( idxSelected );
      updateList( 0 );
    }
    else if( confForm->result == save_item )
    {
      confForm->GetData( name, data );
      inidata->SetData( idxSelected, name, data );
      updateList( idxSelected );
      cList->ItemIndex = idxSelected;
    }
  }
*/
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnNewClick(TObject *Sender)
{
  TForm2 *confForm = new TForm2( this );
  confForm->CurrentSelection( -1 );
  int ret = confForm->ShowModal( );

  if( ret && ( confForm->result == save_item ) )
  {
  }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::onFormCreate(TObject *Sender)
{
  getGWExe( );
  exePath = ExtractFilePath(Application->ExeName);

  inidata = new cpTiniFile( exePath + "\\" + "gwks.ini", "Groupwise KickStart Targets" );
  inidata->ReadFile( );

  confdata = new cpTiniFile( exePath + "\\" + "gwks.ini", "Groupwise KickStart Configuration" );
  confdata->ReadFile( );
  
  AnsiString data = "";

  if( confdata->GetData( "Top", data ) )
    top_pos = atoi( data.c_str( ) );
  else
    top_pos = this->Top;

  if( confdata->GetData( "Left", data ) )
    left_pos = atoi( data.c_str( ) );
  else
    left_pos = this->Left;

  this->Top = top_pos;
  this->Left = left_pos;

  tmTimer->Enabled = false;

  if( confdata->GetData( "TimerMode", data ) )
  {
    tmType = atoi( data.c_str( ) );
    if( tmType < 0 && tmType > 2 )
      tmType = 0;
  }

  if( tmType != timer_none )
    if( confdata->GetData( "TimerDelayInSeconds", data ) );
    {
      tmTimeOut = atoi( data.c_str( ) ) * 1000;
      tmTimer->Interval = tmTimeOut;
      tmTimer->Enabled = true;
    }


  int last = 0;
  if( confdata->GetData( "LastUsed", data ) )
    last = atoi( data.c_str( ) );

  updateList( last );
  btnCheck( );
}
//---------------------------------------------------------------------------
void TForm1::getGWExe( void )
{
  TRegistry *treg = new TRegistry( );
  treg->RootKey = HKEY_CLASSES_ROOT;
  if( treg->OpenKey( GWREGKEY, false ) )
  {
    gwExe = treg->ReadString("");
    gwExe.Trim( );
    if( gwExe.Length( ) )
     gwInstalled = true;
  }
  else
    gwInstalled = false;
}
//---------------------------------------------------------------------------
void TForm1::updateList( int idx )
{
  AnsiString data;
  idxSelected = idx;
  int i = 0;
  int count = 0;
  cList->Clear( );
  while( inidata->GetName( i++, data ) )
  {
    cList->Items->Add( data );
    count++;
  }

  if( count )
    idxSelected = ( idx < cList->Items->Count ) ? idx : 0;
  else if( count <= 0 )
    idxSelected = -1;

  cList->ItemIndex = idxSelected;

  btnCheck( );
}

//---------------------------------------------------------------------------
void TForm1::btnCheck( )
{
  if( gwInstalled && ( idxSelected >= 0 ) )
    btnLaunch->Enabled = true;
  else
    btnLaunch->Enabled = false;

/*  if( idxSelected >= 0 )
    btnConfigure->Enabled = true;
  else
    btnConfigure->Enabled = false;
*/
}

//---------------------------------------------------------------------------
void __fastcall TForm1::cListChange(TObject *Sender)
{
  idxSelected = cList->ItemIndex;
  if( idxSelected >= 0 )
    btnCheck( );

  Application->MessageBoxA( "xx", "xx", MB_OK);

  tmTimer->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnAboutClick(TObject *Sender)
{
  TdlgAbout *about = new TdlgAbout( this );
  about->ShowModal( );
}

//---------------------------------------------------------------------------
void __fastcall TForm1::onTimer(TObject *Sender)
{
  if( tmType == timer_abort )
    Application->Terminate( );

  if( tmType == timer_launch )
  {
    if( idxSelected < 0 )
      return;

    AnsiString app = gwExe;
    AnsiString data;
    long ret = -1;
    if( inidata->GetData( idxSelected, data ) )
    {
      confdata->SetData( "LastUsed", AnsiString( idxSelected ) );
      app += " " + data;
      ret = WinExec( app.c_str( ), SW_SHOW );
      if( ret > 32 )
      {
        getPos( );
        confdata->WriteFile( );
        inidata->WriteFile( );
        Application->Terminate( );
      }
      else
        Application->MessageBoxA( "Cannot load GRPWISE.EXE", "Error", MB_OK | MB_ICONASTERISK );
    }
  }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::cListKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
//
  idxSelected = cList->ItemIndex;
  if( idxSelected >= 0 )
    btnCheck( );

  tmTimer->Enabled = false;

}
//---------------------------------------------------------------------------

