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

#include "data.h"
//---------------------------------------------------------------------------
void cpTiniFile::ReadFile( ) {
  alist->Clear( );
  TStringList *strlst = new TStringList( );
  TIniFile *tfile = new TIniFile( file );
  tfile->ReadSectionValues( section, strlst );
  if( strlst->Count != 0 )
  {
    int cnt = strlst->Count;
    for( int i = 0; i < cnt; i++ )
    {
      cpPTiniData d = new cpTiniData;
      AnsiString str = (AnsiString)strlst->Strings[i];
      int idx = str.AnsiPos("=");
      AnsiString st = str.SubString( idx + 1, str.Length( ) - idx );
      idx = st.AnsiPos(",");
      AnsiString name = st.SubString( 0, idx - 1 );
      AnsiString data = st.SubString( idx + 1, st.Length( ) - idx );
      d->key = str.SubString( 0, str.AnsiPos("=") - 1 );
      d->name = name;
      d->data = data;
      alist->Add( d );
      }
    }
}

//---------------------------------------------------------------------------
void cpTiniFile::WriteFile( ) {
  TIniFile *tfile = new TIniFile( file );
  tfile->EraseSection( section );

  for( int i = 0; i < alist->Count; i++ )
  {
    cpPTiniData d = (cpPTiniData)alist->Items[i];
    if( d->name.Length( ) )
      tfile->WriteString( section, d->key, d->name + "," + d->data );
    else
      tfile->WriteString( section, d->key, d->data );
  }
}

//---------------------------------------------------------------------------
bool cpTiniFile::GetName( int idx, AnsiString& name ) {
  if( idx >= alist->Count )
    return false;

  cpPTiniData d = (cpPTiniData)alist->Items[idx];
  name = d->name;

  return true;
}

//---------------------------------------------------------------------------
bool cpTiniFile::GetData( AnsiString key, AnsiString& data ) {
  for( int i = 0; i < alist->Count; i++ )
  {
    cpPTiniData d = (cpPTiniData)alist->Items[i];
    if( d->key == key )
    {
      data = d->data;
      return true;
    }
  }

  return false;
}

//---------------------------------------------------------------------------
bool cpTiniFile::GetData( int idx, AnsiString& data ) {
  if( idx >= alist->Count )
    return false;

  cpPTiniData d = (cpPTiniData)alist->Items[idx];
  data = d->data;

  return true;
}


//---------------------------------------------------------------------------
bool cpTiniFile::SetData( AnsiString key, AnsiString data ) {
  for( int i = 0; i < alist->Count; i++ )
  {
    cpPTiniData d = (cpPTiniData)alist->Items[i];
    if( d->key == key )
    {
      d->data = data;
      return true;
    }
  }

  return false;
}

//---------------------------------------------------------------------------
bool cpTiniFile::SetData( int idx, AnsiString& name, AnsiString& data ) {
  int cnt = alist->Count;
  if( idx >= cnt )
  {
    cnt++;
    cpPTiniData d = new cpTiniData;
    d->key = cnt;
    d->name = name;
    d->data = data;
    alist->Add( d );
  }
  else
  {
    cpPTiniData d = (cpPTiniData)alist->Items[idx];
    d->name = name;
    d->data = data;
  }
  return true;
}

//---------------------------------------------------------------------------
bool cpTiniFile::DelData( int idx ) {
  if( ( idx >= 0 ) && ( idx <= alist->Count ) )
  {
    alist->Delete( idx );
    return true;
  }
  return false;
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
