// +-------------------------------------------------------------------------+
// | xFarDic Multilingual Dictionary                                         |
// | Copyright (C) 2004-2009 by the xFarDic Development Team.                |
// | http://www.xfardic.org/                                                 |
// +-------------------------------------------------------------------------+
// | License:                                                                |
// |                                                                         |
// | xFarDic is free software; you can redistribute it and/or modify         |
// | it under the terms of the GNU General Public License as published by    |
// | the Free Software Foundation; either version 2 of the License, or       |
// | (at your option) any later version.                                     |
// |                                                                         |
// | xFarDic is distributed in the hope that it will be useful,              |
// | but WITHOUT ANY WARRANTY; without even the implied warranty of          |
// | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            |
// | GNU General Public License for more details.                            |
// |                                                                         |
// | You should have received a copy of the GNU General Public License       |
// | along with xFarDic; if not, write to the Free Software                  |
// | Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA|
// |                                                                         |
// +-------------------------------------------------------------------------+
// | Authors: Alan Baghumian <alan@technotux.org                             |
// |          Armen Baghumian <armen@OpenSourceClub.org>                     |
// +-------------------------------------------------------------------------+

#ifndef __ABOUT_H
#define __ABOUT_H

#include "xfardic.h"

class xFarDicApp;

/// xFarDic About Dialog Class
class xFarDicAbout : public wxFrame
{
public:
    /// ctor(s)
    xFarDicAbout(wxWindow *parent, const wxString& title, const wxPoint& pos, const wxSize& size, wxLocale& m_locale,
            long style = wxDEFAULT_FRAME_STYLE);

    /// OK click handler
    void OnClose(wxCommandEvent& event);   
    /// Abount window constructor
    ~xFarDicAbout(); 

    wxLocale& m_locale;
private:
    void CreateLayout();

private:
    // any class wishing to process wxWindows events must use this macro
    wxStaticBitmap *staticBitmap;
    wxStaticText   *m_autlabel,
                   *m_titlabel,
                   *m_infolabel,
                   *m_liclabel;
    wxButton       *m_ok;
    wxStaticBox    *m_abbox;
    wxPanel        *infopanel, 
                   *autpanel,
                   *licpanel;

    wxNotebook*     layout;
    wxFont          m_font;    
   
    DECLARE_EVENT_TABLE()
};

#endif

