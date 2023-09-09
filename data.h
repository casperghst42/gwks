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
#ifndef dataH
#define dataH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <Registry.hpp>
//---------------------------------------------------------------------------
typedef struct cpTiniData {
  cpTiniData( ) { key = key; name = ""; data = ""; }

  AnsiString key;
  AnsiString name;
  AnsiString data;
} cpATiniData;
typedef cpTiniData* cpPTiniData;

//---------------------------------------------------------------------------
class cpTiniFile {
  public:
    cpTiniFile( AnsiString a_file, AnsiString a_section ) {
      file = a_file;
      section = a_section;
      Initialize( );
    }

    ~cpTiniFile( ) {
      int count = alist->Count;
      for( int i = 0; i < count; i++ )
      {
        cpPTiniData d = (cpPTiniData)alist->Items[i];
        delete d;
      }
      delete alist;
    }

    void ReadFile( );
    void WriteFile( );
    bool GetName( int idx, AnsiString& name );
    bool GetData( AnsiString key, AnsiString& data );
    bool GetData( int idx, AnsiString& data );
    bool SetData( int idx, AnsiString& name, AnsiString& data );
    bool SetData( AnsiString key, AnsiString data );
    bool DelData( int idx );

  protected:
  private:
    void Initialize( )
    {
      alist = new TList( );
    }

    TList *alist;
    AnsiString file;
    AnsiString section;
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif
