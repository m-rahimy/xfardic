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

#include "settings.h"

wxMBConv *CharsetConvII = &wxConvUTF8;
#define UTF8_STR(s) (wxString(s, *CharsetConvII))

BEGIN_EVENT_TABLE(xFarDicSettings, wxFrame)
    EVT_BUTTON(wxID_OK, xFarDicSettings::OnOK)
    EVT_BUTTON(wxID_APPLY, xFarDicSettings::OnApply)
    EVT_BUTTON(wxID_CANCEL, xFarDicSettings::OnCancel)
    EVT_BUTTON(wxID_ADD, xFarDicSettings::OnSetDB)
    EVT_BUTTON(wxID_HELP, xFarDicSettings::OnDBinfo)
    EVT_CHECKBOX(ID_CHK_SELECT, xFarDicSettings::EnableApply)
    EVT_CHECKBOX(ID_CHK_WINPOS, xFarDicSettings::EnableApply)
    EVT_CHECKBOX(ID_CHK_CACHE,  xFarDicSettings::EnableApply)
    EVT_CHECKBOX(ID_CHK_SRCHSIM, xFarDicSettings::EnableApply)
    EVT_CHECKBOX(ID_CHK_SPELL, xFarDicSettings::EnableApply)
    EVT_CHECKBOX(ID_CHK_SWAP, xFarDicSettings::EnableApply)
    EVT_CHECKBOX(ID_CHK_SPEAK, xFarDicSettings::EnableApply)
    EVT_CHECKBOX(ID_CHK_WATCHER, xFarDicSettings::EnableApply)
    EVT_CHECKBOX(ID_CHK_SCANNER,  xFarDicSettings::EnableScanner)
    EVT_CHECKBOX(ID_CHK_TTS,  xFarDicSettings::EnableTTS)
    EVT_CHECKBOX(ID_CHK_HIDE,  xFarDicSettings::EnableApply)
    EVT_CHECKBOX(ID_CHK_REVSRCH,  xFarDicSettings::EnableApply)
    EVT_SPINCTRL(ID_SPIN_TIMEOUT,  xFarDicSettings::EnableSpApply)
    EVT_SPINCTRL(ID_SPIN_ENTRY, xFarDicSettings::EnableSpApply)
    EVT_SPINCTRL(ID_SPIN_LEITNER, xFarDicSettings::EnableSpApply)
    EVT_CHOICE(ID_CHOICE, xFarDicSettings::EnableApply)
    EVT_LISTBOX(ID_DB_PATH, xFarDicSettings::OnPathUpdate)
END_EVENT_TABLE()

bool showSettings = true;

/// Settings window creation function
xFarDicSettings::xFarDicSettings(wxWindow *parent, const wxString& title, const wxPoint& pos, const wxSize& size, wxLocale& locale, long style)
       : wxFrame(parent, -1, title, pos, size, style), m_locale(locale)
{
    // set the frame icon    
    wxBitmap  micon(wxT("/usr/share/xfardic/pixmaps/xfardic32.png"), wxBITMAP_TYPE_PNG);

    if (!micon.Ok()) {
        micon.LoadFile(wxT("/usr/local/share/xfardic/pixmaps/xfardic32.png"), wxBITMAP_TYPE_PNG);
    }

    wxIcon wicon;
    wicon.CopyFromBitmap(micon);
    SetIcon(wicon);     

    m_setbox = new wxStaticBox(this, ID_SETBOX, _T(""));

    wxArtClient client;

    wxBitmap  logo = wxArtProvider::GetBitmap(wxT("gtk-preferences"), client, wxSize(32,35));
    wxBitmap  notelogo = wxArtProvider::GetBitmap(wxART_TIP, client, wxSize(32,35));

    settingsBitmap = new wxStaticBitmap (this, -1, logo);
   
    effecttext = new wxStaticText(this, -1, _("Here you can configure your desired options. Changes will take effect after xFarDic restart."));

    layout = new wxNotebook(this, xFarDic_ChangeTab);

    setpanel =  new wxPanel(layout);
    dbpanel =  new wxPanel(layout);

    submit = false;
    swapupdate = false;

    size_t copies =1;
    langlist.Add(_("Persian"), copies);
    langlist.Add(_("English (U.S)"),copies);
    langlist.Add(_("System default"),copies);
    //langlist.Add(_("Azeri"),copies);

   
    langtext = new wxStaticText(setpanel, -1, _("Choose default &language:"));
    lang = new wxChoice(setpanel, ID_CHOICE, wxDefaultPosition, wxDefaultSize, langlist);

    settext = new wxStaticText(setpanel, -1, _("Number of Entries in History Box:"));
    numEntry = new wxSpinCtrl(setpanel, ID_SPIN_ENTRY, _T(""));
    numEntry->SetRange(3,15);

    timeouttext = new wxStaticText(setpanel, -1, _("Scan window timeout (Sec):"));
    scantimeout = new wxSpinCtrl(setpanel, ID_SPIN_TIMEOUT, _T(""));
    scantimeout->SetRange(0,10);

    leitnertext = new wxStaticText(setpanel, -1, _("Leitner box base capacity:"));
    leitner = new wxSpinCtrl(setpanel, ID_SPIN_LEITNER, _T(""));
    leitner->SetRange(0,50);

    chk_select = new wxCheckBox(setpanel, ID_CHK_SELECT, _("Enable Auto &Select Word After Translation"));
    chk_hide  = new wxCheckBox(setpanel, ID_CHK_HIDE,  _("&Hide On Window Minimize and close"));  
    chk_revsrch  = new wxCheckBox(setpanel, ID_CHK_REVSRCH,  _("Enable Inexact &Reverse Searching")); 
    chk_winpos = new wxCheckBox(setpanel, ID_CHK_WINPOS, _("Save Program Window P&ositions"));
    chk_cache  = new wxCheckBox(setpanel, ID_CHK_CACHE,  _("Save Wor&d Cache On Exit"));
    chk_watcher  = new wxCheckBox(setpanel, ID_CHK_WATCHER,  _("Enable Clipboard &Watcher"));
    chk_scanner  = new wxCheckBox(setpanel, ID_CHK_SCANNER,  _("Enable Clipboard Sca&nner"));
    chk_speak  = new wxCheckBox(setpanel, ID_CHK_SPEAK,  _("Spea&k With Clipboard Scanner"));        
    chk_srchsim   = new wxCheckBox(setpanel, ID_CHK_SRCHSIM,   _("Return Si&milar Words"));
    chk_spell  = new wxCheckBox(setpanel, ID_CHK_SPELL,  _("Enable S&pell Checker"));
    chk_swap  = new wxCheckBox(setpanel, ID_CHK_SWAP,  _("Enable S&wap file"));
    chk_tts  = new wxCheckBox(setpanel, ID_CHK_TTS,  _("Enable Text to Speech En&gine"));

    m_ok = new wxButton(this, wxID_OK, _("&OK"), wxDefaultPosition,wxSize(80,36));
    m_apply = new wxButton(this, wxID_APPLY, _("&Apply"), wxDefaultPosition,wxSize(80,36));
    m_cancel = new wxButton(this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition,wxSize(80,36));
  
    // Set Default button
    m_ok->SetDefault();
    m_apply->Enable(FALSE);

    wxConfigBase *pConfig = wxConfigBase::Get();

    // we could write Read("/Controls/Text") as well, it's just to show SetPath()
    pConfig->SetPath(wxT("/Options"));

    if ( pConfig->Read(_T("Auto-Select"), 1) != 0 ) {
      chk_select->SetValue(TRUE);
    } else {
      chk_select->SetValue(FALSE);
    }
    
    if ( pConfig->Read(_T("Srch-Similar"), 0l) != 0 ) {
      chk_srchsim->SetValue(TRUE);
    } else {
      chk_srchsim->SetValue(FALSE);
    }

    if ( pConfig->Read(_T("Hide"), 0l) != 0 ) {
      chk_hide->SetValue(TRUE);
    } else {
      chk_hide->SetValue(FALSE);
    }

    if ( pConfig->Read(_T("Spell"), 1) != 0 ) {
      chk_spell->SetValue(TRUE);
    } else {
      chk_spell->SetValue(FALSE);
    }

    if ( pConfig->Read(_T("RevSrch"), 0l) != 0 ) {
      chk_revsrch->SetValue(TRUE);
    } else {
      chk_revsrch->SetValue(FALSE);
    }

    if ( pConfig->Read(_T("Watcher"), 1) != 0 ) {
      chk_watcher->SetValue(TRUE);
    } else {
      chk_watcher->SetValue(FALSE);
    }

    if ( pConfig->Read(_T("TTS"), 0l) != 0 ) {
      chk_tts->SetValue(TRUE);
    } else {
      chk_tts->SetValue(FALSE);
    }  

    if ( pConfig->Read(_T("Speak"), 0l) != 0 ) {
      chk_speak->SetValue(TRUE);
    } else {
      chk_speak->SetValue(FALSE);
    }    

    if ( pConfig->Read(_T("Scanner"), 1) != 0 ) {
      chk_scanner->SetValue(TRUE);
      if(!chk_tts->GetValue()){
          chk_speak->Enable(FALSE);
      }
    } else {
      chk_scanner->SetValue(FALSE);
      chk_speak->Enable(FALSE);
    }    

    if ( pConfig->Read(_T("Win-Pos"), 1) != 0 ) {
      chk_winpos->SetValue(TRUE);
    } else {
      chk_winpos->SetValue(FALSE);
    }

    if ( pConfig->Read(_T("Save-Cache"), 1) != 0 ) {
      chk_cache->SetValue(TRUE);
    } else {
      chk_cache->SetValue(FALSE);
    }

    if ( pConfig->Read(_T("Swap"), 0l) != 0 ) {
      chk_swap->SetValue(TRUE);
    } else {
      chk_swap->SetValue(FALSE);
    }  

    int entry = pConfig->Read(_T("Num-Entries"), 10);  
    numEntry->SetValue(entry);

    int timeout = pConfig->Read(_T("Scan-Timeout"), 5);  
    scantimeout->SetValue(timeout);

    int ltbasecap = pConfig->Read(_T("Leitner-Base"), 10);  
    leitner->SetValue(ltbasecap); 
   
    lang->SetSelection(pConfig->Read(_T("GUI-Lang"), 2));  
           
    wxString path = pConfig->Read(_T("DB-Path"), _T(""));    
   
    wxString Part;

    if (path.Len()!=0) {
        for (int x=1; x <= path.Len(); x++) {
            Part = path.GetChar(x);
            if (Part.CmpNoCase(_T(";"))==0) {
                seppos.Add(x);
            }
        }

        if (seppos.GetCount()>0) {    
            for (int x=0; x <= seppos.GetCount(); x++) {
                if (x == 0) {
                    tmppath = path.Mid(0,seppos[x]);
                    if (tmppath.Len()!=0) {
                        if (CheckPath(path.Mid(0,seppos[x]))) {
                            dbs.Add(path.Mid(0,seppos[x]));
                        } else {
                            submit = true;
                        }
                    }
                } else if (x == seppos.GetCount()) {
                    tmppath = path.Mid(seppos[x-1]+1,path.Len());
                    if (tmppath.Len()!=0) {
                        if (CheckPath(path.Mid(seppos[x-1]+1,path.Len()))) {
                            dbs.Add(path.Mid(seppos[x-1]+1,path.Len()));
                        } else {
                            submit = true;
                        }
                    }
                } else {
                    tmppath = path.Mid(seppos[x-1]+1,seppos[x]-seppos[x-1]-1);
                    if (tmppath.Len()!=0) {
                        if (CheckPath(path.Mid(seppos[x-1]+1,seppos[x]-seppos[x-1]-1))) {
                            dbs.Add(path.Mid(seppos[x-1]+1,seppos[x]-seppos[x-1]-1));
                        } else {
                            submit = true;
                        }
                    }
                }
            }      
        } else {
            if (CheckPath(path)) {
                dbs.Add(path);
            } else {
                submit = true;
            }
        }    
    }

    dbtext = new wxStaticText(dbpanel, -1, _("XML DB Path:"));

    dbpath = new wxListBox(dbpanel, ID_DB_PATH, wxDefaultPosition, wxDefaultSize, dbs, wxLB_EXTENDED |wxLB_NEEDED_SB);    

    dbdir = new wxButton(dbpanel, wxID_ADD, _("Add"), wxDefaultPosition,wxSize(80,36));
    dbinfo = new wxButton(dbpanel, wxID_HELP, _("DB info"), wxDefaultPosition,wxSize(80,36));
   
    notelogoBitmap1 = new wxStaticBitmap (dbpanel, -1, notelogo, wxPoint(110, 175));

    dbnote = new wxStaticText(dbpanel, -1, _("Ctrl+Click to enable or disable available database(s)."));

    notelogoBitmap2 = new wxStaticBitmap (dbpanel, -1, notelogo, wxPoint(110, 215));

    swapnote = new wxStaticText(dbpanel, -1, _("Enabling swap reduces memory usage by 55% and performance by 15%."));

    if (path.Len()!=0) {
        for (int x=0; x < dbs.GetCount(); x++) {
            dbpath->SetSelection(x);    
        }
    }        
           
    if (path.Len()==0) {
        dbinfo->Enable(FALSE);
    }

    layout->AddPage(setpanel, _("Options"));    
    layout->AddPage(dbpanel, _("Databases")); 

    //if there are changes on DBs, auto-submit changes
    if (submit == true) {
        SubmitChanges();
    } 
 
    CreateLayout();   
}

/// Settings window destructor.
xFarDicSettings::~xFarDicSettings()
{
    langlist.Clear();
    showSettings = true;
}

/// OK button click event handler.
void xFarDicSettings::OnOK(wxCommandEvent& WXUNUSED(event))
{
    SubmitChanges();  
    Close(TRUE);
}

/// Cancel button click handler
void xFarDicSettings::OnCancel(wxCommandEvent& WXUNUSED(event))
{
     Close(TRUE);
}

/// Submit config changes to the config file
void xFarDicSettings::SubmitChanges()
{
    wxConfigBase *pConfig = wxConfigBase::Get();
    if ( pConfig == NULL ) {
        return;
    }

    wxString path,att;
    dbpath->GetSelections(dbcount);
     
    if (dbcount.GetCount()>0) {          
        for (int x=0; x < dbcount.GetCount(); x++) {
            if (path.Len()==0) {
                att = _T(";");
            }

            if (x+1 < dbcount.GetCount()) {
               path = path + dbpath->GetString(dbcount[x]) + att;
            } else {
               path = path + dbpath->GetString(dbcount[x]);
            }
        }
    }

    if (path.Len()==0) {
       wxString msg;
       msg = _("XML DB path is empty.\nxFarDic will now work without a valid database.");
       wxMessageBox(msg, _("Warning"), wxOK | wxICON_WARNING, this);
    }
      
    pConfig->SetPath(wxT("/"));

    // save the control's values to the config
    if (chk_select->GetValue()) {
        pConfig->Write(wxT("/Options/Auto-Select"), 1);
    } else {
        pConfig->Write(wxT("/Options/Auto-Select"), 0);
    }
      
    if (chk_srchsim->GetValue()) {
        pConfig->Write(wxT("/Options/Auto-Srch"), 1);
    } else {
        pConfig->Write(wxT("/Options/Auto-Srch"), 0);
    }

    if (chk_spell->GetValue()) {
        pConfig->Write(wxT("/Options/Spell"), 1);
    } else {
        pConfig->Write(wxT("/Options/Spell"), 0);
    }

    if (chk_watcher->GetValue()) {
        pConfig->Write(wxT("/Options/Watcher"), 1);
    } else {
        pConfig->Write(wxT("/Options/Watcher"), 0);
    }

    if (chk_scanner->GetValue()) {
        pConfig->Write(wxT("/Options/Scanner"), 1);
    } else {
        pConfig->Write(wxT("/Options/Scanner"), 0);
    }

    if (chk_tts->GetValue()) {
        pConfig->Write(wxT("/Options/TTS"), 1);
    } else {
        pConfig->Write(wxT("/Options/TTS"), 0);
    }

    if (chk_speak->GetValue()) {
        pConfig->Write(wxT("/Options/Speak"), 1);
    } else {
        pConfig->Write(wxT("/Options/Speak"), 0);
    }

    if (chk_hide->GetValue()) {
        pConfig->Write(wxT("/Options/Hide"), 1);
    } else {
        pConfig->Write(wxT("/Options/Hide"), 0);
    }

    if (chk_revsrch->GetValue()) {
        pConfig->Write(wxT("/Options/RevSrch"), 1);
    } else {
        pConfig->Write(wxT("/Options/RevSrch"), 0);
    }

    if (chk_cache->GetValue()) {
        pConfig->Write(wxT("/Options/Save-Cache"), 1);
    } else {
        pConfig->Write(wxT("/Options/Save-Cache"), 0);
    }

    if (chk_swap->GetValue()) {
        pConfig->Write(wxT("/Options/Swap"), 1);
    } else {
        pConfig->Write(wxT("/Options/Swap"), 0);
    }

    if (chk_winpos->GetValue()) {
        pConfig->Write(wxT("/Options/Win-Pos"), 1);
        int x, y;
        GetPosition(&x, &y);
        pConfig->Write(wxT("/Options/x"), (long) x);
        pConfig->Write(wxT("/Options/y"), (long) y);
    } else {
        pConfig->Write(wxT("/Options/Win-Pos"), 0);
        pConfig->Write(wxT("/Options/x"), 0);
        pConfig->Write(wxT("/Options/y"), 0);
    }

    pConfig->Write(wxT("/Options/Num-Entries"), numEntry->GetValue());    

    pConfig->Write(wxT("/Options/Scan-Timeout"), scantimeout->GetValue()); 

    pConfig->Write(wxT("/Options/Leitner-Base"), leitner->GetValue());

    pConfig->Write(wxT("/Options/GUI-Lang"), lang->GetSelection());            
            
    pConfig->Write(wxT("/Options/DB-Path"), path);

    if (swapupdate) {     
        pConfig->Write(wxT("/Options/Swap-Update"), 1);     
    }
    
    delete wxConfigBase::Set((wxConfigBase *) NULL);
}

/// Apply button click handler
void xFarDicSettings::OnApply(wxCommandEvent& WXUNUSED(event))
{
    SubmitChanges();
    m_apply->Enable(FALSE);     
}

/// Setting DB dialog
void xFarDicSettings::OnSetDB(wxCommandEvent& WXUNUSED(event))
{
    wxString path = dbpath->GetStringSelection();
    exist = FALSE;
    
    if (path.Len() == 0) {
        path = wxGetHomeDir();
    }

    wxFileDialog dialog(this, _("Choose a XML DataBase"), wxEmptyString, path, _("XML DataBase files (*.xdb)|*.xdb"),
                        wxOPEN);        

    if (dialog.ShowModal() == wxID_OK) {       
        path = dialog.GetPath().c_str();
        dbpath->GetSelections(dbcount);
        if (dbcount.GetCount()>0) {          
           for (int x=0; x < dbcount.GetCount(); x++) {                        
               if (path.IsSameAs(dbpath->GetString(x))) {                       
                   exist = TRUE;                
               }
           }
        }
        if (DB((const char *)path.mb_str(wxConvUTF8)) && exist == FALSE) {                   
                           dbs.Clear();  
                           dbs.Add(path);
                           dbpath->InsertItems(dbs,0);
                           dbpath->SetSelection(0,0);
                           dbpath->SetStringSelection(path);
                           dbinfo->Enable(TRUE);
                            m_apply->Enable(TRUE);    
                           swapupdate = true;
        }
    }
}

void xFarDicSettings::EnableApply(wxCommandEvent& WXUNUSED(event))
{
    m_apply->Enable(TRUE);
}

void xFarDicSettings::EnableScanner(wxCommandEvent& WXUNUSED(event))
{
    m_apply->Enable(TRUE);
   
    if (chk_scanner->GetValue()) {
        if(chk_tts->GetValue()){
           chk_speak->Enable(TRUE);
        }
    }else{
        chk_speak->Enable(FALSE);
    }
}

void xFarDicSettings::EnableTTS(wxCommandEvent& WXUNUSED(event))
{
    m_apply->Enable(TRUE);
   
    if (chk_tts->GetValue()) {
        if(chk_scanner->GetValue()){
           chk_speak->Enable(TRUE);
        }
    }else{
        chk_speak->Enable(FALSE);
    }
}

void xFarDicSettings::OnPathUpdate(wxCommandEvent& WXUNUSED(event))
{     
    wxString path;
    m_apply->Enable(TRUE);
    
    path = dbpath->GetStringSelection();
   
    if (path.Len() > 0) {    
        dbinfo->Enable(TRUE);
    } else {
        dbinfo->Enable(FALSE);
    }

    swapupdate = true;   

    // DEBUGGING
    //fprintf(stderr, "%s\n", (const char *)path.mb_str(wxConvUTF8));
}

void xFarDicSettings::EnableSpApply(wxSpinEvent& WXUNUSED(event))
{
    m_apply->Enable(TRUE);
}

/// Get DB information
void xFarDicSettings::OnDBinfo(wxCommandEvent& WXUNUSED(event))
{
    wxString msg, path;
    
    dbpath->GetSelections(dbcount);
    msg =_T("");
     
    if (dbcount.GetCount()>0) {          
        for (int x=0; x < dbcount.GetCount(); x++) {                        
            path = dbpath->GetString(x);                                    
            DB((const char *)path.mb_str(wxConvUTF8));
            if (dbname.Len()!=0 || author.Len()!=0 || version.Len()!=0 || inputlang.Len()!=0) {
                msg += _("DB Name  : ")+dbname+_T("\n\n");
                msg += _("DB Author : ")+author+_T("\n\n");
                msg += _("DB Version: ")+version+_T("\n\n");
                msg += _("Input Lang: ")+inputlang+_T("\n\n\n");
            } else {
                msg = _("No information found.");
            }
        }
    } else {
        msg = _("No information found or no databse is selected.");
    }    

    wxMessageBox(msg, _("XML Database information"), wxOK | wxICON_INFORMATION, this);
}

/// Validate XML Database
bool xFarDicSettings::DB(const char *filename) {    
    int ret, counter;
   
    counter =0;         

    reader = xmlReaderForFile(filename, NULL, 0);
    if (reader != NULL) {
        ret = xmlTextReaderRead(reader);
        do {
            if (xmlTextReaderNodeType(reader) == 3) {
                counter++;            
                //DEBUG
                //printf("%s\n", (const char*)xmlTextReaderValue(reader));      
                switch (counter) {
                      case 1:
                          dbname = UTF8_STR((char *)xmlTextReaderValue(reader));
                          break;
                      case 2:                  
                          author = UTF8_STR((char *)xmlTextReaderValue(reader));
                          break;
                      case 3:
                          inputlang = UTF8_STR((char *)xmlTextReaderValue(reader));
                          break;
                      case 4:           
                          version = UTF8_STR((char *)xmlTextReaderValue(reader));       
                          break;
                };
            }
            ret = xmlTextReaderRead(reader);
        } while (ret == 1 && counter <4);
         
        xmlFreeTextReader(reader);               
        xmlCleanupParser();
        return true;

    } else {

        wxString msg;
        msg.Printf( _("Parse Error. Invalid Document.\n"));
        //fprintf(stderr, "Unable to open %s\n", filename);
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_STOP, this);
        return false;
    }
}

bool xFarDicSettings::CheckPath(wxString dbpath)
{
    wxFile xmldb;
    
    // Check if xdb file exists before parsing
    if (xmldb.Exists(dbpath)) {
        return true;
    } else {
        return false;
    }
}

void xFarDicSettings::CreateLayout() {

	wxBoxSizer *logoandtextSizer = new wxBoxSizer(wxHORIZONTAL);
	logoandtextSizer->Add(settingsBitmap, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	logoandtextSizer->Add(effecttext, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);

	wxStaticBoxSizer *staticBoxSizer = new wxStaticBoxSizer(m_setbox,wxVERTICAL);
	staticBoxSizer->Add(logoandtextSizer,0,wxEXPAND|wxALL,2);
	staticBoxSizer->Add(layout,1,wxEXPAND|wxALL,2);

	wxGridSizer *setpanelSizer = new wxGridSizer(9,2,0,0);
	setpanelSizer->Add(langtext , 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	setpanelSizer->Add(lang , 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	setpanelSizer->Add(settext , 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	setpanelSizer->Add(numEntry , 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	setpanelSizer->Add(timeouttext , 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	setpanelSizer->Add(scantimeout , 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	setpanelSizer->Add(leitnertext , 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	setpanelSizer->Add(leitner , 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	setpanelSizer->Add(chk_select , 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	setpanelSizer->Add(chk_watcher , 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	setpanelSizer->Add(chk_hide , 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	setpanelSizer->Add(chk_speak , 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	setpanelSizer->Add(chk_scanner , 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	setpanelSizer->Add(chk_revsrch , 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	setpanelSizer->Add(chk_srchsim , 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	setpanelSizer->Add(chk_winpos , 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	setpanelSizer->Add(chk_spell , 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	setpanelSizer->Add(chk_cache , 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	setpanelSizer->Add(chk_swap , 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	setpanelSizer->Add(chk_tts , 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);

	wxBoxSizer *dbpanelSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *dbpanelrightSizer = new wxBoxSizer(wxVERTICAL);
	dbpanelrightSizer->Add(dbpath, 1, wxEXPAND|wxALL, 2);
	wxBoxSizer *dbpanelrightSizerbuttons = new wxBoxSizer(wxHORIZONTAL);
	dbpanelrightSizerbuttons->Add(dbdir, 0, wxEXPAND|wxALL, 2);
	dbpanelrightSizerbuttons->Add(dbinfo, 0, wxEXPAND|wxALL, 2);
	wxBoxSizer *dbpanelrightSizerfirsttext = new wxBoxSizer(wxHORIZONTAL);
	dbpanelrightSizerfirsttext->Add(notelogoBitmap1, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	dbpanelrightSizerfirsttext->Add(dbnote, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	wxBoxSizer *dbpanelrightSizersecondtext = new wxBoxSizer(wxHORIZONTAL);
	dbpanelrightSizersecondtext->Add(notelogoBitmap2, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	dbpanelrightSizersecondtext->Add(swapnote, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
	dbpanelrightSizer->Add(dbpanelrightSizerbuttons, 0, wxEXPAND|wxALL, 2);
	dbpanelrightSizer->Add(dbpanelrightSizerfirsttext, 0, wxEXPAND|wxALL, 2);
	dbpanelrightSizer->Add(dbpanelrightSizersecondtext, 0, wxEXPAND|wxALL, 2);
	dbpanelSizer->Add(dbtext, 0, wxEXPAND|wxALL, 2);
	dbpanelSizer->Add(dbpanelrightSizer, 1, wxEXPAND|wxALL, 2);

	setpanel->SetAutoLayout(true);
	setpanel->SetSizer( setpanelSizer );
	dbpanel->SetAutoLayout(true);
	dbpanel->SetSizer( dbpanelSizer );

	wxBoxSizer *bottomSizer = new wxBoxSizer(wxHORIZONTAL);
	bottomSizer->AddStretchSpacer(1);
	bottomSizer->Add(m_ok, 0, wxALIGN_RIGHT, 2);
	bottomSizer->Add(m_apply, 0, wxALIGN_RIGHT, 2);
	bottomSizer->Add(m_cancel, 0, wxALIGN_RIGHT, 2);	
	
	staticBoxSizer->Add(bottomSizer,0,wxEXPAND|wxALL,2);

	wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(staticBoxSizer,
			1, //make vertically stretchable
			wxEXPAND|wxALL,
			5);

	SetSizer(topSizer);
	topSizer->Fit(this);
	topSizer->SetSizeHints(this);
}

