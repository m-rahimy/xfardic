// +-------------------------------------------------------------------------+
// | xFarDic Multilingual Dictionary                                         |
// | Copyright (C) 2004-2007 by the xFarDic Development Team.                |
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
#include "about.h"

BEGIN_EVENT_TABLE(xFarDicAbout, wxFrame)
    EVT_BUTTON(wxID_CLOSE, xFarDicAbout::OnClose)    
END_EVENT_TABLE()

bool showAbout = true;

/// OK Button Click event handler.
void xFarDicAbout::OnClose(wxCommandEvent& WXUNUSED(event))
{
    Close(TRUE);
}

xFarDicAbout::~xFarDicAbout()
{ 
  showAbout = true;
}

/// About Windows creation function
xFarDicAbout::xFarDicAbout(wxWindow *parent, const wxString& title, const wxPoint& pos, const wxSize& size, wxLocale& locale, long style)
       : wxFrame(parent, -1, title, pos, size, style), m_locale(locale)
{    
    // set the frame icon    
    wxBitmap  micon(_T("/usr/share/xfardic/pixmaps/xfardic32.png"), wxBITMAP_TYPE_PNG);

    if(!micon.Ok()){
        micon.LoadFile(_T("/usr/local/share/xfardic/pixmaps/xfardic32.png"), wxBITMAP_TYPE_PNG);
    }

    wxIcon wicon;
    wicon.CopyFromBitmap(micon);
    SetIcon(wicon);  

    layout = new wxNotebook(this, xFarDic_ChangeTab, wxPoint(5,113), wxSize(390,200));

    infopanel =  new wxPanel(layout);
    autpanel =  new wxPanel(layout);
    licpanel =  new wxPanel(layout);
    
    //xFarDic Logo
    wxBitmap logo(_T("/usr/share/xfardic/pixmaps/xfardic-logo.png"), wxBITMAP_TYPE_PNG);   

    if (!logo.Ok()){
        logo.LoadFile(_T("/usr/local/share/xfardic/pixmaps/xfardic-logo.png"), wxBITMAP_TYPE_PNG);       
    }        

    (void)new wxStaticBitmap (this, -1, logo, wxPoint(155, 8));
  
    m_ok = new wxButton(this, wxID_CLOSE, _("&Close"), wxPoint(315,315), wxSize(80,36) );

    //Set Default button
    m_ok->SetDefault();

    wxString autmsg, infomsg, titmsg, licmsg;
    
    autmsg.Printf( _T("%s"),_("Alan Baghumian <alan@technotux.org>\n\nArmen Baghumian <armen@opensourceclub.org>"));

    titmsg.Printf( _T("%s%s"),
           _("xFarDic "),
           XVERSION);

    infomsg.Printf(_T("%s"),_("Latest News and Updates: http://www.xfardic.org\n\nBug Report/Feature Request: alan@technotux.org\n\nIMPORTANT NOTICE:\nYou can get required XDB word databases from project home page at http://sf.net/projects/xfardic. Without word databases, xFarDic *will not* work."));

    licmsg.Printf(_T("%s"),_("xFarDic is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.\n\nxFarDic is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details."));

    m_autlabel = new wxStaticText(autpanel, -1, autmsg, wxPoint(5, 10), wxSize(380,390));
    m_infolabel = new wxStaticText(infopanel, -1, infomsg, wxPoint(5, 10), wxSize(380,390));
    m_liclabel = new wxStaticText(licpanel, -1, licmsg, wxPoint(5, 10), wxSize(380,390));
    m_titlabel = new wxStaticText(this, -1, titmsg, wxPoint(31, 84), wxSize(340,390), wxALIGN_CENTRE);
    m_abbox = new wxStaticBox(this, -1, wxT(""), wxPoint(5, 5), wxSize(390,105), wxALIGN_CENTRE);	

    // Setting Label Font
    m_font.SetPointSize(15);
    m_font.SetWeight(wxBOLD);

    m_titlabel->SetFont(m_font);

    layout->AddPage(infopanel, _("Information"));
    layout->AddPage(licpanel, _("License"));    
    layout->AddPage(autpanel, _("Authors"));
        
}
