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
       : wxFrame(parent, -1, title, pos, size, style|wxMAXIMIZE_BOX), m_locale(locale)
{    
    // set the frame icon    
    wxBitmap  micon(_T("/usr/share/xfardic/pixmaps/xfardic32.png"), wxBITMAP_TYPE_PNG);

    if (!micon.Ok()) {
        micon.LoadFile(_T("/usr/local/share/xfardic/pixmaps/xfardic32.png"), wxBITMAP_TYPE_PNG);
    }

    wxIcon wicon;
    wicon.CopyFromBitmap(micon);
    SetIcon(wicon);  

    //xFarDic Logo
    wxBitmap logo(_T("/usr/share/xfardic/pixmaps/xfardic-logo.png"), wxBITMAP_TYPE_PNG);   

    if (!logo.Ok()) {
        logo.LoadFile(_T("/usr/local/share/xfardic/pixmaps/xfardic-logo.png"), wxBITMAP_TYPE_PNG);       
    }

    staticBitmap = new wxStaticBitmap (this, -1, logo);

    layout = new wxNotebook(this, xFarDic_ChangeTab);

    infopanel =  new wxPanel(layout);
    autpanel =  new wxPanel(layout);
    licpanel =  new wxPanel(layout);
    
    m_ok = new wxButton(this, wxID_CLOSE, _("&Close"));

    //Set Default button
    m_ok->SetDefault();

    wxString autmsg, infomsg, titmsg, licmsg;
    
    autmsg.Printf( _T("%s"),_("Alan Baghumian <alan@technotux.org>\n\nArmen Baghumian <armen@opensourceclub.org>"));

    titmsg.Printf( _T("%s%s"),
           _("xFarDic "),
           XVERSION);

    infomsg.Printf(_T("%s"),_("Latest News and Updates: http://www.xfardic.org\n\nBug Report/Feature Request: alan@technotux.org\n\nIMPORTANT NOTICE:\nYou can get required XDB word databases from project\nhome page at http://sf.net/projects/xfardic. Without word\ndatabases, xFarDic *will not* work."));

    licmsg.Printf(_T("%s"),_("xFarDic is free software; you can redistribute it and/or\nmodify it under the terms of the GNU General Public License\nas published by the Free Software Foundation; either\nversion 2 of the License, or (at your option) any later\nversion.\n\nxFarDic is distributed in the hope that it will be useful, but\nWITHOUT ANY WARRANTY; without even the implied warranty\nof MERCHANTABILITY or FITNESS FOR A PARTICULAR\nPURPOSE. See the GNU General Public License for more\ndetails."));

    m_autlabel = new wxStaticText(autpanel, -1, autmsg);
    m_infolabel = new wxStaticText(infopanel, -1, infomsg);
    m_liclabel = new wxStaticText(licpanel, -1, licmsg);
    m_titlabel = new wxStaticText(this, -1, titmsg);
    m_abbox = new wxStaticBox(this, -1, wxT(""));

    // Setting Label Font
    m_font.SetPointSize(15);
    m_font.SetWeight(wxBOLD);

    m_titlabel->SetFont(m_font);

    layout->AddPage(infopanel, _("Information"));
    layout->AddPage(licpanel, _("License"));    
    layout->AddPage(autpanel, _("Authors"));
    CreateLayout();
}

void xFarDicAbout::CreateLayout() {
     wxBoxSizer *topsizer = new wxBoxSizer( wxVERTICAL );

     topsizer->Add(staticBitmap, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);
     topsizer->Add(m_titlabel, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);
     
     topsizer->Add(layout, 1, wxALL|wxEXPAND, 5);

     wxSizer *infopanelsizer = new wxBoxSizer(wxVERTICAL);
     infopanelsizer->Add( m_infolabel, 1, wxEXPAND|wxALL, 5);
     wxSizer *autpanelsizer = new wxBoxSizer(wxVERTICAL);
     autpanelsizer->Add( m_autlabel, 1, wxEXPAND|wxALL, 5);
     wxSizer *licpanelsizer = new wxBoxSizer(wxVERTICAL);
     licpanelsizer->Add( m_liclabel, 1, wxEXPAND|wxALL, 5);

     infopanel->SetAutoLayout( true );
     infopanel->SetSizer( infopanelsizer );
     autpanel->SetAutoLayout( true );
     autpanel->SetSizer( autpanelsizer );
     licpanel->SetAutoLayout( true );
     licpanel->SetSizer( licpanelsizer );

     topsizer->Add(m_ok, 0, wxALIGN_RIGHT|wxALL, 5);

     SetSizer( topsizer );
     topsizer->SetSizeHints( this );
}

