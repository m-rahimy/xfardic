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
    EVT_CHECKBOX(ID_CHK_SRCHSIM,   xFarDicSettings::EnableApply)
    EVT_CHECKBOX(ID_CHK_SPELL,  xFarDicSettings::EnableApply)
    EVT_CHECKBOX(ID_CHK_WATCHER,  xFarDicSettings::EnableApply)
    EVT_CHECKBOX(ID_CHK_SCANNER,  xFarDicSettings::EnableApply)
    EVT_CHECKBOX(ID_CHK_HIDE,  xFarDicSettings::EnableApply)
    EVT_CHECKBOX(ID_CHK_REVSRCH,  xFarDicSettings::EnableApply)
    EVT_SPINCTRL(ID_SPIN_TIMEOUT,  xFarDicSettings::OnScanTimeOut)
    EVT_SPINCTRL(ID_SPIN_ENTRY, xFarDicSettings::OnNumEntry)
    EVT_CHOICE(ID_CHOICE, xFarDicSettings::EnableApply)
    EVT_LISTBOX(ID_DB_PATH, xFarDicSettings::OnPathUpdate)
END_EVENT_TABLE()

bool showSettings = true;

/// Settings window creation function
xFarDicSettings::xFarDicSettings(wxWindow *parent, const wxString& title, const wxPoint& pos, const wxSize& size, wxLocale& locale, long style)
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

    layout = new wxNotebook(this, xFarDic_ChangeTab, wxPoint(5,60), wxSize(489,290));

    setpanel =  new wxPanel(layout);
    dbpanel =  new wxPanel(layout);

     size_t copies =1;
     langlist.Add(_("Persian"), copies);
     langlist.Add(_("English (U.S)"),copies);
     langlist.Add(_("System default"),copies);
     //langlist.Add(_("Azeri"),copies);
    
    m_setbox = new wxStaticBox(this, ID_SETBOX, _T(""), wxPoint(0,4), wxSize(500,396) );

    wxArtClient client;

    wxBitmap  logo = wxArtProvider::GetBitmap(wxT("gtk-preferences"), client, wxSize(32,35));

    (void)new wxStaticBitmap (this, -1, logo, wxPoint(20, 10));

    m_ok = new wxButton(this, wxID_OK, _("&OK"), wxPoint(250,356), wxSize(80,36) );
    m_apply = new wxButton(this, wxID_APPLY, _("&Apply"), wxPoint(331,356), wxSize(80,36) );
    m_cancel = new wxButton(this, wxID_CANCEL, _("&Cancel"), wxPoint(411,356), wxSize(80,36) );

    chk_select = new wxCheckBox(setpanel, ID_CHK_SELECT, _("Enable Auto &Select Word After Translation"), wxPoint(2,115));
    chk_hide  = new wxCheckBox(setpanel, ID_CHK_HIDE,  _("&Hide On Window Minimize and close"), wxPoint(2,137));  
    chk_revsrch  = new wxCheckBox(setpanel, ID_CHK_REVSRCH,  _("Enable Inexact &Reverse Searching"), wxPoint(2,159)); 
    chk_winpos = new wxCheckBox(setpanel, ID_CHK_WINPOS, _("Save Program Window P&ositions"), wxPoint(2,181));
    chk_cache  = new wxCheckBox(setpanel, ID_CHK_CACHE,  _("Save Wor&d Cache On Exit"), wxPoint(2,203));
    chk_watcher  = new wxCheckBox(setpanel, ID_CHK_WATCHER,  _("Enable Clipboard &Watcher"), wxPoint(300,115));
    chk_scanner  = new wxCheckBox(setpanel, ID_CHK_SCANNER,  _("Enable Clipboard Sca&nner"), wxPoint(300,137));        
    chk_srchsim   = new wxCheckBox(setpanel, ID_CHK_SRCHSIM,   _("Return Si&milar Words"), wxPoint(300,159));
    chk_spell  = new wxCheckBox(setpanel, ID_CHK_SPELL,  _("Enable S&pell Checker"), wxPoint(300,181));
   
    // Set Default button
    m_ok->SetDefault();
    m_apply->Enable(FALSE);

    wxConfigBase *pConfig = wxConfigBase::Get();

    // we could write Read("/Controls/Text") as well, it's just to show SetPath()
    pConfig->SetPath(_T("/Options"));

    if ( pConfig->Read(_T("Auto-Select"), 1) != 0 ) {
      chk_select->SetValue(TRUE);
    }else{
      chk_select->SetValue(FALSE);
    }
    
    if ( pConfig->Read(_T("Srch-Similar"), 0l) != 0 ) {
      chk_srchsim->SetValue(TRUE);
    }else{
      chk_srchsim->SetValue(FALSE);
    }

    if ( pConfig->Read(_T("Hide"), 0l) != 0 ) {
      chk_hide->SetValue(TRUE);
    }else{
      chk_hide->SetValue(FALSE);
    }

    if ( pConfig->Read(_T("Spell"), 1) != 0 ) {
      chk_spell->SetValue(TRUE);
    }else{
      chk_spell->SetValue(FALSE);
    }

    if ( pConfig->Read(_T("RevSrch"), 0l) != 0 ) {
      chk_revsrch->SetValue(TRUE);
    }else{
      chk_revsrch->SetValue(FALSE);
    }

    if ( pConfig->Read(_T("Watcher"), 1) != 0 ) {
      chk_watcher->SetValue(TRUE);
    }else{
      chk_watcher->SetValue(FALSE);
    }

    if ( pConfig->Read(_T("Scanner"), 1) != 0 ) {
      chk_scanner->SetValue(TRUE);
    }else{
      chk_scanner->SetValue(FALSE);
    }

    if ( pConfig->Read(_T("Win-Pos"), 1) != 0 ) {
      chk_winpos->SetValue(TRUE);
    }else{
      chk_winpos->SetValue(FALSE);
    }

    if ( pConfig->Read(_T("Save-Cache"), 1) != 0 ) {
      chk_cache->SetValue(TRUE);
    }else{
      chk_cache->SetValue(FALSE);
    }

    numEntry = new wxSpinCtrl(setpanel, ID_SPIN_ENTRY, _T(""), wxPoint(300, 42), wxSize(50, 20) );      
    numEntry->SetRange(3,15);

    int entry = pConfig->Read(_T("Num-Entries"), 10);  
    numEntry->SetValue(entry);

    scantimeout = new wxSpinCtrl(setpanel, ID_SPIN_TIMEOUT, _T(""), wxPoint(300, 68), wxSize(50, 20) );      
    scantimeout->SetRange(0,10);

    int timeout = pConfig->Read(_T("Scan-Timeout"), 5);  
    scantimeout->SetValue(timeout);
    
    wxStaticText *effecttext;
    effecttext = new wxStaticText(this, -1, _("Here you can configure your desired options. Changes will take effect after xFarDic restart."), wxPoint(65, 16), wxSize(380, 80));

    wxStaticText *langtext;
    langtext = new wxStaticText(setpanel, -1, _("Choose default &language:"), wxPoint(5, 12), wxSize(170, 30));

    lang = new wxChoice(setpanel, ID_CHOICE, wxPoint(300,10), wxSize(150,wxDefaultCoord), langlist);

    lang->SetSelection(pConfig->Read(_T("GUI-Lang"), 2));  

    wxStaticText *settext;
    settext = new wxStaticText(setpanel, -1, _("Number of Entries in History Box:"), wxPoint(5, 43), wxSize(218, 30));

    wxStaticText *timeouttext;
    timeouttext = new wxStaticText(setpanel, -1, _("Scan window timeout (Sec):"), wxPoint(5, 72), wxSize(218, 30));
       
    wxString path = pConfig->Read(_T("DB-Path"), _T(""));    
   
    wxString Part;

    if(path.Len()!=0){
    for(int x=1; x <= path.Len(); x++){	
	Part = path.GetChar(x);
	if(Part.CmpNoCase(_T(";"))==0){
		seppos.Add(x);		
	}
    }

   if(seppos.GetCount()>0){    
	   for(int x=0; x <= seppos.GetCount(); x++){
		if(x == 0){
			tmppath = path.Mid(0,seppos[x]);
			if(tmppath.Len()!=0){
				dbs.Add(path.Mid(0,seppos[x]));
			}
		}else if(x == seppos.GetCount()){
			tmppath = path.Mid(seppos[x-1]+1,path.Len());
			if(tmppath.Len()!=0){
				dbs.Add(path.Mid(seppos[x-1]+1,path.Len()));
			}
		}else{
			tmppath = path.Mid(seppos[x-1]+1,seppos[x]-seppos[x-1]-1);
			if(tmppath.Len()!=0){
				dbs.Add(path.Mid(seppos[x-1]+1,seppos[x]-seppos[x-1]-1));
			}
		}
	    }	  
     }else{
	dbs.Add(path);
     }	
   }

    dbpath = new wxListBox(dbpanel, ID_DB_PATH, wxPoint(115, 13), wxSize(340, 120),dbs,wxLB_EXTENDED |wxLB_NEEDED_SB);

    wxBitmap  notelogo = wxArtProvider::GetBitmap(wxART_TIP, client, wxSize(32,35));

    (void)new wxStaticBitmap (dbpanel, -1, notelogo, wxPoint(110, 175));

    wxStaticText *dbnote;
    dbnote = new wxStaticText(dbpanel, -1, _("Ctrl+Click to enable or disable available database(s)."), wxPoint(141, 188), wxSize(380, 80));

    if(path.Len()!=0){
	for(int x=0; x < dbs.GetCount(); x++){
			dbpath->SetSelection(x);	
		}
    }        
           
    wxStaticText *dbtext;
    dbtext = new wxStaticText(dbpanel, -1, _("XML DB Path:"), wxPoint(10, 15), wxSize(93, 29));    
    
    dbdir = new wxButton(dbpanel, wxID_ADD, _("Add"), wxPoint(115,135), wxSize(80,30) );
    dbinfo = new wxButton(dbpanel, wxID_HELP, _("DB info"), wxPoint(205,135), wxSize(80,30) );
    
    if(path.Len()==0){
	dbinfo->Enable(FALSE);
    }

    layout->AddPage(setpanel, _("Options"));    
    layout->AddPage(dbpanel, _("Databases"));    
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
      wxConfigBase *pConfig = wxConfigBase::Get();
      if ( pConfig == NULL )
      return;

     wxString path,att;
     dbpath->GetSelections(dbcount);
     
      if(dbcount.GetCount()>0){      	
		for(int x=0; x < dbcount.GetCount(); x++){
			if(path.Len()==0){att = _T(";");}
			if(x+1 < dbcount.GetCount()){
				path = path + dbpath->GetString(dbcount[x]) + att;
			}else{
				path = path + dbpath->GetString(dbcount[x]);
			}
		}
      }

     if(path.Len()==0){
	wxString msg;
	msg = _("XML DB path is empty.\nxFarDic will now work without a valid database.");
         wxMessageBox(msg, _("Warning"), wxOK | wxICON_WARNING, this);
     }
           
      pConfig->SetPath(_T("/"));

      // save the control's values to the config
      if(chk_select->GetValue()){
          pConfig->Write(_T("/Options/Auto-Select"), 1);
      }else{
          pConfig->Write(_T("/Options/Auto-Select"), 0);
      }
      
      if(chk_srchsim->GetValue()){
          pConfig->Write(_T("/Options/Auto-Srch"), 1);
      }else{
          pConfig->Write(_T("/Options/Auto-Srch"), 0);
      }

      if(chk_spell->GetValue()){
          pConfig->Write(_T("/Options/Spell"), 1);
      }else{
          pConfig->Write(_T("/Options/Spell"), 0);
      }

      if(chk_hide->GetValue()){
          pConfig->Write(_T("/Options/Hide"), 1);
      }else{
          pConfig->Write(_T("/Options/Hide"), 0);
      }

      if(chk_revsrch->GetValue()){
          pConfig->Write(_T("/Options/RevSrch"), 1);
      }else{
          pConfig->Write(_T("/Options/RevSrch"), 0);
      }

      if(chk_watcher->GetValue()){
          pConfig->Write(_T("/Options/Watcher"), 1);
      }else{
          pConfig->Write(_T("/Options/Watcher"), 0);
      }

      if(chk_scanner->GetValue()){
          pConfig->Write(_T("/Options/Scanner"), 1);
      }else{
          pConfig->Write(_T("/Options/Scanner"), 0);
      }

      if(chk_cache->GetValue()){
          pConfig->Write(_T("/Options/Save-Cache"), 1);
      }else{
          pConfig->Write(_T("/Options/Save-Cache"), 0);
      }

      if(chk_winpos->GetValue()){
          pConfig->Write(_T("/Options/Win-Pos"), 1);
          int x, y;
          GetPosition(&x, &y);
          pConfig->Write(_T("/Options/x"), (long) x);
          pConfig->Write(_T("/Options/y"), (long) y);
      }else{
          pConfig->Write(_T("/Options/Win-Pos"), 0);
          pConfig->Write(_T("/Options/x"), 0);
          pConfig->Write(_T("/Options/y"), 0);
      }

    pConfig->Write(_T("/Options/Num-Entries"), numEntry->GetValue()); 

    pConfig->Write(_T("/Options/Scan-Timeout"), scantimeout->GetValue()); 

    pConfig->Write(_T("/Options/GUI-Lang"), lang->GetSelection()); 
          
    pConfig->Write(_T("/Options/DB-Path"), path);        
      
    delete wxConfigBase::Set((wxConfigBase *) NULL);      
    Close(TRUE);
}

/// Cancel button click handler
void xFarDicSettings::OnCancel(wxCommandEvent& WXUNUSED(event))
{
     Close(TRUE);
}

/// Apply button click handler
void xFarDicSettings::OnApply(wxCommandEvent& WXUNUSED(event))
{
     wxConfigBase *pConfig = wxConfigBase::Get();
     if ( pConfig == NULL )
     	return;
	
     wxString path,att;
     dbpath->GetSelections(dbcount);
     
     if(dbcount.GetCount()>0){      	
		for(int x=0; x < dbcount.GetCount(); x++){
				if(path.Len()==0){att = _T(";");}
				if(x+1 < dbcount.GetCount()){
					path = path + dbpath->GetString(dbcount[x]) + att;
				}else{
					path = path + dbpath->GetString(dbcount[x]);
				}
		}
      }

     if(path.Len()==0){
	wxString msg;
	msg = _("XML DB path is empty.\nxFarDic will now work without a valid database.");
         wxMessageBox(msg, _("Warning"), wxOK | wxICON_WARNING, this);
     }
      
      pConfig->SetPath(_T("/"));

  // save the control's values to the config
      if(chk_select->GetValue()){
          pConfig->Write(_T("/Options/Auto-Select"), 1);
      }else{
          pConfig->Write(_T("/Options/Auto-Select"), 0);
      }
      
      if(chk_srchsim->GetValue()){
          pConfig->Write(_T("/Options/Auto-Srch"), 1);
      }else{
          pConfig->Write(_T("/Options/Auto-Srch"), 0);
      }

      if(chk_spell->GetValue()){
          pConfig->Write(_T("/Options/Spell"), 1);
      }else{
          pConfig->Write(_T("/Options/Spell"), 0);
      }

      if(chk_watcher->GetValue()){
          pConfig->Write(_T("/Options/Watcher"), 1);
      }else{
          pConfig->Write(_T("/Options/Watcher"), 0);
      }

      if(chk_scanner->GetValue()){
          pConfig->Write(_T("/Options/Scanner"), 1);
      }else{
          pConfig->Write(_T("/Options/Scanner"), 0);
      }

      if(chk_hide->GetValue()){
          pConfig->Write(_T("/Options/Hide"), 1);
      }else{
          pConfig->Write(_T("/Options/Hide"), 0);
      }

      if(chk_revsrch->GetValue()){
          pConfig->Write(_T("/Options/RevSrch"), 1);
      }else{
          pConfig->Write(_T("/Options/RevSrch"), 0);
      }

      if(chk_cache->GetValue()){
          pConfig->Write(_T("/Options/Save-Cache"), 1);
      }else{
          pConfig->Write(_T("/Options/Save-Cache"), 0);
      }

      if(chk_winpos->GetValue()){
          pConfig->Write(_T("/Options/Win-Pos"), 1);
          int x, y;
          GetPosition(&x, &y);
          pConfig->Write(_T("/Options/x"), (long) x);
          pConfig->Write(_T("/Options/y"), (long) y);
      }else{
          pConfig->Write(_T("/Options/Win-Pos"), 0);
          pConfig->Write(_T("/Options/x"), 0);
          pConfig->Write(_T("/Options/y"), 0);
      }

      pConfig->Write(_T("/Options/Num-Entries"), numEntry->GetValue());    

      pConfig->Write(_T("/Options/Scan-Timeout"), scantimeout->GetValue()); 

      pConfig->Write(_T("/Options/GUI-Lang"), lang->GetSelection());            
              
      pConfig->Write(_T("/Options/DB-Path"), path);     
      
      delete wxConfigBase::Set((wxConfigBase *) NULL);
      m_apply->Enable(FALSE);     
}

/// Setting DB dialog
void xFarDicSettings::OnSetDB(wxCommandEvent& WXUNUSED(event))
{
    wxString path = dbpath->GetStringSelection();
    exist = FALSE;
    
    if(path.Len() == 0){
        path = wxGetHomeDir();
    }

    wxFileDialog dialog(this, _("Choose a XML DataBase"), wxEmptyString, path, _("XML DataBase files (*.xdb)|*.xdb"),wxOPEN);        

    if (dialog.ShowModal() == wxID_OK)
    {       
	   path = dialog.GetPath().c_str();
           dbpath->GetSelections(dbcount);
	   if(dbcount.GetCount()>0){      	
		for(int x=0; x < dbcount.GetCount(); x++){						
			if(path.IsSameAs(dbpath->GetString(x))){			           
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
         }
    }
	
}

void xFarDicSettings::EnableApply(wxCommandEvent& WXUNUSED(event))
{
     m_apply->Enable(TRUE);
}

void xFarDicSettings::OnPathUpdate(wxCommandEvent& WXUNUSED(event))
{
     wxString path;
     m_apply->Enable(TRUE);
     
     path = dbpath->GetStringSelection();
   
     if(path.Len() > 0){	
	  dbinfo->Enable(TRUE);
     }else{
	  dbinfo->Enable(FALSE);
     }

     // DEBUGGING
     //fprintf(stderr, "%s\n", (const char *)path.mb_str(wxConvUTF8));
}

void xFarDicSettings::OnNumEntry(wxSpinEvent& WXUNUSED(event))
{
     m_apply->Enable(TRUE);
}

void xFarDicSettings::OnScanTimeOut(wxSpinEvent& WXUNUSED(event))
{
     m_apply->Enable(TRUE);
}

/// Get DB information
void xFarDicSettings::OnDBinfo(wxCommandEvent& WXUNUSED(event))
{
	wxString msg, path;
	
	dbpath->GetSelections(dbcount);
	msg =_T("");
     
      if(dbcount.GetCount()>0){      	
		for(int x=0; x < dbcount.GetCount(); x++){						
				path = dbpath->GetString(x);								    
				DB((const char *)path.mb_str(wxConvUTF8));
				if(dbname.Len()!=0 || author.Len()!=0 || version.Len()!=0 || inputlang.Len()!=0){
					msg += _("DB Name  : ")+dbname+_T("\n\n");
				        msg += _("DB Author : ")+author+_T("\n\n");
					msg += _("DB Version: ")+version+_T("\n\n");
					msg += _("Input Lang: ")+inputlang+_T("\n\n\n");
				}else{
					msg = _("No information found.");
				}
		}
      }else{
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
        do{
	    if(xmlTextReaderNodeType(reader) == 3)           
	   {
		counter++;            
		//DEBUG
		//printf("%s\n", (const char*)xmlTextReaderValue(reader));  	
		switch (counter)
		{
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
        }while (ret == 1 && counter <4);
         
        xmlFreeTextReader(reader);               
        xmlCleanupParser();
	return true;
    } else {
	wxString msg;
   	msg.Printf( _("Parse Error. Invalid Document.\n"));
	wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_STOP, this);
	return false;
        fprintf(stderr, "Unable to open %s\n", filename);
    }
}
