// +-------------------------------------------------------------------------+
// | xFarDic Multilingual Dictionary                                         |
// | Copyright (C) 2004-2008 by the xFarDic Development Team.                |
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

#include "xfardic_app.h"

wxMBConv *CharsetConv = &wxConvUTF8;
#define UTF8_STR(s) (wxString(s, *CharsetConv))

#define ART_CLIENT(id) \
    choice->Append(_T(#id), (void*)id);
#define ART_ICON(id) \
    { \
        int ind; \
        wxIcon icon = wxArtProvider::GetIcon(id, client, size); \
        if ( icon.Ok() ) \
            ind = images->Add(icon); \
        else \
            ind = 0; \
        list->InsertItem(index, _T(#id), ind); \
        list->SetItemData(index, (long)id); \
        index++; \
    }

BEGIN_EVENT_TABLE(xFarDicApp, wxFrame)    
    EVT_MENU(xFarDic_Translate,  xFarDicApp::OnTranslate)
    EVT_MENU(xFarDic_AddLeitner, xFarDicApp::OnLeitnerBox)
    EVT_MENU(xFarDic_Pronounce,  xFarDicApp::OnTexttoSpeech)
    EVT_MENU(xFarDic_Quit,  xFarDicApp::OnQuit)
    EVT_MENU(xFarDic_About, xFarDicApp::OnAbout)
    EVT_MENU(xFarDic_Back, xFarDicApp::OnBack)
    EVT_MENU(xFarDic_First, xFarDicApp::OnFirst)
    EVT_MENU(xFarDic_Last, xFarDicApp::OnLast)
    EVT_MENU(xFarDic_Forward, xFarDicApp::OnForward)
    EVT_MENU(xFarDic_Select, xFarDicApp::OnSelect)
    EVT_MENU(xFarDic_Settings, xFarDicApp::OnSettings)
    EVT_MENU(xFarDic_Copy, xFarDicApp::OnCopy)
    EVT_MENU(xFarDic_Paste, xFarDicApp::OnPaste)
    EVT_MENU(xFarDic_Cut, xFarDicApp::OnCut)
    EVT_MENU(xFarDic_Trash, xFarDicApp::OnTrash)
    EVT_MENU(xFarDic_Setfont, xFarDicApp::OnSetFont)
    EVT_MENU(xFarDic_Srch, xFarDicApp::OnSrch)
    EVT_MENU(xFarDic_Spell, xFarDicApp::OnSpell)
    EVT_MENU(xFarDic_RevSrch, xFarDicApp::OnRevSrch)
    EVT_MENU(xFarDic_Watcher, xFarDicApp::OnWatcher)
    EVT_MENU(xFarDic_Scanner, xFarDicApp::OnScanner)
    EVT_MENU(xFarDic_Notification, xFarDicApp::OnNotification)
    EVT_MENU(xFarDic_Hide, xFarDicApp::OnHide)
    EVT_MENU(xFarDic_ViewToolBar, xFarDicApp::ViewToolbar)
    EVT_MENU(xFarDic_Leitner, xFarDicApp::OnLeitner)
    EVT_BUTTON(ID_BUTTON_TRANSLATE, xFarDicApp::OnTranslate)
    EVT_BUTTON(ID_BTN_LT, xFarDicApp::OnLeitnerBox)
    EVT_BUTTON(ID_BUTTON_TTOS, xFarDicApp::OnTexttoSpeech)
    EVT_TOOL(ID_SPELL, xFarDicApp::OnSpell)
    EVT_TOOL(ID_REVSRCH, xFarDicApp::OnRevSrch)
    EVT_TOOL(ID_SRCH, xFarDicApp::OnSrch)
    EVT_TOOL(ID_QUIT, xFarDicApp::OnQuit)
    EVT_TOOL(ID_BACK, xFarDicApp::OnBack)
    EVT_TOOL(ID_FORWARD, xFarDicApp::OnForward)
    EVT_TOOL(ID_SELECT, xFarDicApp::OnSelect)
    EVT_TOOL(ID_SETTINGS, xFarDicApp::OnSettings)
    EVT_TOOL(ID_COPY, xFarDicApp::OnCopy)
    EVT_TOOL(ID_CUT, xFarDicApp::OnCut)
    EVT_TOOL(ID_PASTE, xFarDicApp::OnPaste)
    EVT_TOOL(ID_TRASH, xFarDicApp::OnTrash)
    EVT_TOOL(ID_TOOL_LT, xFarDicApp::OnLeitner)
    EVT_COMBOBOX(ID_COMBO, xFarDicApp::AutoTrans)
    //EVT_TEXT(ID_COMBO, xFarDicApp::UpdateText)
    EVT_SET_FOCUS(xFarDicApp::OnFocus)
    EVT_ACTIVATE(xFarDicApp::OnActivate) 
    EVT_CLOSE(xFarDicApp::OnClose)        
    EVT_TIMER(ID_TIMER, xFarDicApp::Watcher)
    EVT_ICONIZE(xFarDicApp::Hide)
END_EVENT_TABLE()

/// Main window creation function
xFarDicApp::xFarDicApp(const wxString& title, const wxPoint& pos, const wxSize& size, wxLocale& locale, long style, bool fit)
       : wxFrame(NULL, -1, title, pos, size, style), m_locale(locale), m_timer(this, ID_TIMER)
{
    // set the frame icon    
    wxBitmap  micon(wxT("/usr/share/xfardic/pixmaps/xfardic32.png"), wxBITMAP_TYPE_PNG);

    if (!micon.Ok()) {
        micon.LoadFile(wxT("/usr/local/share/xfardic/pixmaps/xfardic32.png"), wxBITMAP_TYPE_PNG);
    }

    wxIcon wicon;
    wicon.CopyFromBitmap(micon);
    SetIcon(wicon);

    m_smallToolbar = TRUE;
    m_horzToolbar = TRUE;
    m_rows = 1;
    m_text =  (wxComboBox *)NULL;
    n = NULL;    

    // Starting main timer 
    m_timer.Start(500);       

    wxArtClient client;    
    
    //Load The leitner box content
    LoadLeitnerBox();
   
    wxIcon taskicon = wxArtProvider::GetIcon(wxART_FIND, client, wxDefaultSize);
    ticon.SetIcon(taskicon, _T("xFarDic Multilingual Dictionary"));    
     
    wxBitmap  bcut = wxArtProvider::GetBitmap(wxART_CUT, client, wxDefaultSize);
    wxBitmap  bcut16 = wxArtProvider::GetBitmap(wxART_CUT, client, wxSize(16,16));
    wxBitmap  bquit = wxArtProvider::GetBitmap(wxART_QUIT, client, wxDefaultSize);
    wxBitmap  bquit16 = wxArtProvider::GetBitmap(wxART_QUIT, client, wxSize(16,16));
    wxBitmap  bpaste = wxArtProvider::GetBitmap(wxART_PASTE, client, wxDefaultSize);
    wxBitmap  bpaste16 = wxArtProvider::GetBitmap(wxART_PASTE, client, wxSize(16,16));
    wxBitmap  bcopy = wxArtProvider::GetBitmap(wxART_COPY, client, wxDefaultSize);
    wxBitmap  bcopy16 = wxArtProvider::GetBitmap(wxART_COPY, client, wxSize(16,16));
    wxBitmap  bsettings = wxArtProvider::GetBitmap(wxT("gtk-preferences"), client, wxDefaultSize);
    wxBitmap  bsettings16 = wxArtProvider::GetBitmap(wxT("gtk-preferences"), client, wxSize(16,16));
    wxBitmap  btrash = wxArtProvider::GetBitmap(wxT("gtk-clear"), client, wxDefaultSize);
    wxBitmap  btrash16 = wxArtProvider::GetBitmap(wxT("gtk-clear"), client, wxSize(16,16));
    wxBitmap  bselect = wxArtProvider::GetBitmap(wxART_REDO, client, wxDefaultSize);
    wxBitmap  btranslate = wxArtProvider::GetBitmap(wxART_FIND, client, wxDefaultSize);
    wxBitmap  btranslate16 = wxArtProvider::GetBitmap(wxART_FIND, client, wxSize(16,16));
    wxBitmap  bback = wxArtProvider::GetBitmap(wxART_GO_BACK, client, wxDefaultSize);
    wxBitmap  bback16 = wxArtProvider::GetBitmap(wxART_GO_BACK, client, wxSize(16,16));
    wxBitmap  bforward = wxArtProvider::GetBitmap(wxART_GO_FORWARD, client, wxDefaultSize);
    wxBitmap  bforward16 = wxArtProvider::GetBitmap(wxART_GO_FORWARD, client, wxSize(16,16));
    wxBitmap  spellb = wxArtProvider::GetBitmap(wxT("gtk-spell-check"), client, wxDefaultSize);
    wxBitmap  bfont = wxArtProvider::GetBitmap(wxT("gtk-select-font"), client, wxSize(16,16));
    wxBitmap  babout = wxArtProvider::GetBitmap(wxT("gtk-about"), client, wxSize(16,16));
    wxBitmap  bleitner = wxArtProvider::GetBitmap(wxT("gnome-devel"), client, wxSize(16,16));
    wxBitmap  bfirst = wxArtProvider::GetBitmap(wxT("gtk-goto-first"), client, wxSize(16,16));
    wxBitmap  blast = wxArtProvider::GetBitmap(wxT("gtk-goto-last"), client, wxSize(16,16));
    wxBitmap  bttos = wxArtProvider::GetBitmap(wxT("sound"), client, wxSize(16,16));
    wxBitmap  bsplash(wxT("/usr/share/xfardic/pixmaps/splash.png"), wxBITMAP_TYPE_PNG);

    if (!bsplash.Ok()) {
        bsplash.LoadFile(wxT("/usr/local/share/xfardic/pixmaps/splash.png"), wxBITMAP_TYPE_PNG);
    }
        
#if wxUSE_MENUS
    // create a menu bar
    menuFile = new wxMenu;

    // the "About" item should be in the help menu
    helpMenu = new wxMenu;

    wxMenuItem *about = new wxMenuItem(helpMenu,xFarDic_About, _("&About...\tF1"), _("Show about dialog"));
    about->SetBitmap(babout);
    helpMenu->Append(about);

    toolsMenu = new wxMenu;

    wxMenuItem *tools = new wxMenuItem(toolsMenu,xFarDic_Leitner, _("Leitner box\tCtrl+B"), _("Show Leitner box"));
    tools->SetBitmap(bleitner);
    toolsMenu->Append(tools);

    vimenu = new wxMenu;
    vimenu->Append(xFarDic_ViewToolBar, _("View Toolbar\tCtrl-T"), _("Toggle toolbar On/Off"), wxITEM_CHECK);        
    
    wxMenuItem *translate = new wxMenuItem(menuFile,xFarDic_Translate, _("Translate\tAlt-T"), _("Translate word"));
    translate->SetBitmap(btranslate16);
    menuFile->Append(translate);

    wxMenuItem *addleitner = new wxMenuItem(menuFile,xFarDic_AddLeitner, _("Add to leitner box\tAlt-X"), _("Add word to the leitner box"));
    addleitner->SetBitmap(bleitner);
    menuFile->Append(addleitner);

    wxMenuItem *pronounce = new wxMenuItem(menuFile,xFarDic_Pronounce, _("Pronounce\tAlt-P"), _("Add word to the leitner box"));
    pronounce->SetBitmap(bttos);
    menuFile->Append(pronounce);
    menuFile->AppendSeparator();

    wxMenuItem *fwd = new wxMenuItem(menuFile,xFarDic_Forward, _("For&ward\tAlt-W"), _("Next word"));
    fwd->SetBitmap(bforward16);
    menuFile->Append(fwd);

    wxMenuItem *back = new wxMenuItem(menuFile,xFarDic_Back, _("&Back\tAlt-B"), _("Previous word"));
    back->SetBitmap(bback16);
    menuFile->Append(back);

    menuFile->AppendSeparator();

    wxMenuItem *first = new wxMenuItem(menuFile,xFarDic_First, _("Fi&rst Word\tAlt+R"), _("First word"));
    first->SetBitmap(bfirst);
    menuFile->Append(first);

    wxMenuItem *last = new wxMenuItem(menuFile,xFarDic_Last, _("&Last Word\tAlt+L"), _("Last word"));
    last->SetBitmap(blast);   
    menuFile->Append(last);

    menuFile->Enable(xFarDic_Forward, FALSE);
    menuFile->Enable(xFarDic_Back, FALSE);
    menuFile->Enable(xFarDic_First, FALSE);
    menuFile->Enable(xFarDic_Last, FALSE); 

    menuFile->AppendSeparator();   

    wxMenuItem *quit = new wxMenuItem(menuFile,xFarDic_Quit, _("&Quit\tCtrl+Q"), _("Quit this program"));
    quit->SetBitmap(bquit16);
    menuFile->Append(quit);

    opmenu = new wxMenu;
    opmenu->Append(xFarDic_Select, _("Auto &Select\tAlt-S"), _("Auto select word"), wxITEM_CHECK);
    opmenu->Append(xFarDic_Watcher, _("Enable Clipboard &Watcher\tCtrl-W"), _("Enable clipboard watcher"), wxITEM_CHECK);
    opmenu->Append(xFarDic_Scanner, _("Enable Selection Sca&nner\tCtrl-N"), _("Enable selection scanner"), wxITEM_CHECK);
    opmenu->Append(xFarDic_Srch, _("Return Similar Words\tCtrl-S"), _("Return similar words"), wxITEM_CHECK);
    opmenu->Append(xFarDic_Hide, _("Enable &Hide On Minimize and Close\tCtrl-H"), _("Enable hide on minimize and close"), wxITEM_CHECK);
    opmenu->Append(xFarDic_Spell, _("Enable S&pell Checking\tCtrl-P"), _("Enable spell checking"), wxITEM_CHECK);
    opmenu->Append(xFarDic_RevSrch, _("Enable Inexact &Reverse Searching\tCtrl-R"), _("Enable inexact reverse searchning"), wxITEM_CHECK);
    opmenu->Append(xFarDic_Notification, _("Enable N&otification Window\tCtrl-O"), _("Enable notification window"), wxITEM_CHECK);

    opmenu->AppendSeparator();
    
    wxMenuItem *setfont = new wxMenuItem(opmenu,xFarDic_Setfont, _("Set Result Box Font\tCtrl-F"), _("Set result box font"));
    setfont->SetBitmap(bfont);
    opmenu->Append(setfont);
        
    edmenu = new wxMenu;
      
    wxMenuItem *cut = new wxMenuItem(edmenu,xFarDic_Cut, _("C&ut\tCtrl-X"), _("Cut input text"));
    cut->SetBitmap(bcut16);
    edmenu->Append(cut);

    wxMenuItem *copy = new wxMenuItem(edmenu,xFarDic_Copy, _("&Copy\tCtrl-C"), _("Copy result to clipboard"));
    copy->SetBitmap(bcopy16);
    edmenu->Append(copy);    

    wxMenuItem *paste = new wxMenuItem(edmenu,xFarDic_Paste, _("&Paste and Translate\tCtrl-V"), _("Paste from clipboard"));
    paste->SetBitmap(bpaste16);
    edmenu->Append(paste);
    edmenu->AppendSeparator();

    wxMenuItem *trash = new wxMenuItem(edmenu,xFarDic_Trash, _("Clear History\tCtrl-D"), _("Clear history"));
    trash->SetBitmap(btrash16);
    edmenu->Append(trash);
    edmenu->AppendSeparator();

    edmenu->Append(xFarDic_Options, _T("&Options"), opmenu);  

    wxMenuItem *settings = new wxMenuItem(edmenu,xFarDic_Settings, _("Preferences"), _("Configure settings"));
    settings->SetBitmap(bsettings16);
    edmenu->Append(settings);
  

    // now append the freshly created menu to the menu bar...
    menuBar = new wxMenuBar();
    menuBar->Append(menuFile, _("&File"));
    menuBar->Append(edmenu, _("&Edit"));
    menuBar->Append(vimenu, _("&View"));
    menuBar->Append(toolsMenu, _("Too&ls"));
    menuBar->Append(helpMenu, _("&Help"));    

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);             
        
#endif // wxUSE_MENUS

    m_label = new wxTextCtrl(this, ID_RES_CTRL, _T(""), wxDefaultPosition,
                    wxSize(505, 190), 
                    wxTE_MULTILINE | wxTE_READONLY);   

    //Get Configuration From Config File
    wxConfigBase *pConfig = wxConfigBase::Get();

    pConfig->SetPath(wxT("/Options"));

    db_sort_order = pConfig->Read(_T("DB-Sort"), 0l);
    swap = pConfig->Read(_T("Swap"), 0l);
    swapupdate = pConfig->Read(_T("Swap-Update"), 0l); 

    if (!swap && swapupdate) {
        swapupdate = FALSE;
    }

    // Check if swap file exists
    wxFile swapfile;
    wxString swappath = wxGetHomeDir()+wxT("/.xfardic.swap");

    if (!swapfile.Exists(swappath) && swap) {
        swapupdate = TRUE;
    }      

    ltbaselimit = pConfig->Read(_T("Leitner-Base"), 10);
  
    if ( pConfig->Read(_T("View-Toolbar"), 1) == 0 ) {     
        RecreateToolbar(FALSE);    
        // Nasty hack to delete that stupid line!
        wxToolBar *tbar = GetToolBar();
        delete tbar;
        // End Nasty hack
        vimenu->Check( xFarDic_ViewToolBar, FALSE );      
        vtool = FALSE;
    } else {    
        RecreateToolbar();    
        vimenu->Check( xFarDic_ViewToolBar, TRUE );      
        vtool = TRUE;
    } 

    wxString fontface = pConfig->Read(_T("Font-Face"));        
    int fontsize = pConfig->Read(_T("Font-Size"), 10);
    //fprintf(stderr, "font-size:%d\n",fontsize);
    int fontstyle = pConfig->Read(_T("Font-Style"), 90);
    //fprintf(stderr, "font-style:%d\n",fontstyle);
    int fontfamily = pConfig->Read(_T("Font-Family"), 0l);
    int fontwgt = pConfig->Read(_T("Font-Wgt"), 0l);
        
    m_font.SetPointSize(fontsize);
    m_font.SetStyle(fontstyle);
    m_font.SetFaceName(fontface);
    m_font.SetFamily(fontfamily);
    m_font.SetWeight(fontwgt);
       
    m_label->SetFont(m_font);
    
    path = pConfig->Read(_T("DB-Path"), _T(""));
    //inputlang = pConfig->Read(_T("DB-ILang"), _T(""));

    path = path.Trim(TRUE);
    path = path.Trim(FALSE);

    // First initialize Espeak engine
#ifdef HAVE_SPEAKLIB
    tts = pConfig->Read(_T("TTS"), 0l);

    if (tts) {
        pron = new xFarDicPronounce();
        pron->Init();        
    }else {
        menuFile->Enable(xFarDic_Pronounce, FALSE); 
    }
#else
    menuFile->Enable(xFarDic_Pronounce, FALSE);
    tts = FALSE;
#endif
 
    // if there are defined xdbs     
    if (path.Len() > 0) {
        for (int x=1; x <= path.Len(); x++) {    
            Part = path.GetChar(x);
            if (Part.CmpNoCase(_T(";"))==0) {
                seppos.Add(x);        
            }
        } // End For
   
        splash = new wxSplashScreen(bsplash,wxSPLASH_CENTRE_ON_SCREEN,0, this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
                                    wxFRAME_NO_TASKBAR|wxSTAY_ON_TOP);
         
        if (seppos.GetCount()>0) {    
            for (int x=0; x <= seppos.GetCount(); x++) {
                if (x == 0) {
                    tmppath = path.Mid(0,seppos[x]);
                    if (tmppath.Len()!=0) {
                        paths.Add(path.Mid(0,seppos[x]));
                    }
                } else if (x == seppos.GetCount()) {
                    tmppath = path.Mid(seppos[x-1]+1,path.Len());
                    if (tmppath.Len()!=0) {
                        paths.Add(path.Mid(seppos[x-1]+1,path.Len()));
                    }
                } else {
                    tmppath = path.Mid(seppos[x-1]+1,seppos[x]-seppos[x-1]-1);
                    if (tmppath.Len()!=0) {
                        paths.Add(path.Mid(seppos[x-1]+1,seppos[x]-seppos[x-1]-1));
                    }
                }
            }

            // Sort DB list
            paths.Sort(db_sort_order);

            for (int x=0; x < paths.GetCount(); x++) {            
                if (paths.Item(x).Len()!=0) {
                   initDB((const char *)paths.Item(x).mb_str(wxConvUTF8));        
                }        
            }           
      
        } else {
            initDB((const char *)path.mb_str(wxConvUTF8));        
        }
        delete splash;
        wxYield();       
        // if there is no defined xdb, Database Auto-Load system
    } else {
        wxFileSystem fs;
        wxString tmpstr, att, longpath, tmpfname;
        wxArrayString filenames;

        splash = new wxSplashScreen(bsplash,wxSPLASH_CENTRE_ON_SCREEN,0, this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFRAME_NO_TASKBAR|wxSTAY_ON_TOP);
        
        fs.ChangePathTo(wxGetHomeDir(), TRUE);

        tmpstr = fs.FindFirst(_T("*.xdb"),wxFILE);
        tmpfname = tmpstr;
        tmpfname.Replace(wxGetHomeDir()+wxT("/"), _T(""));
        //DEBUGGING
        //fprintf(stderr, "%s\n", (const char *)tmpfname.mb_str(wxConvUTF8));

        if (tmpstr.Len() > 0) {        
            if (filenames.Index(tmpfname,FALSE) == wxNOT_FOUND) {
                if (tmpfname.Len()>0) {    
                    filenames.Add(tmpfname);            
                }
                paths.Add(tmpstr);
            }
            
            while (tmpstr.Len() >0) {
                tmpstr = fs.FindNext();
                       tmpfname = tmpstr;
                       tmpfname.Replace(wxGetHomeDir()+wxT("/"), _T(""));
                      //DEBUGGING
                       //fprintf(stderr, "%s\n", (const char *)tmpfname.mb_str(wxConvUTF8));

                if (filenames.Index(tmpfname,FALSE) == wxNOT_FOUND) {
                    if (tmpstr.Len() > 0) {    
                        if (tmpfname.Len()>0) {    
                            filenames.Add(tmpfname);            
                        }
                        paths.Add(tmpstr);
                    }
                }
            }
        }

        fs.ChangePathTo(wxT("/usr/share/xfardic-xdb/"), TRUE);

        tmpstr = fs.FindFirst(_T("*.xdb"),wxFILE);
        tmpfname = tmpstr;
        tmpfname.Replace(wxT("/usr/share/xfardic-xdb/"), _T(""));
        //DEBUGGING
        //fprintf(stderr, "%s\n", (const char *)tmpfname.mb_str(wxConvUTF8));

        if (tmpstr.Len() > 0) {        
            if (filenames.Index(tmpfname,FALSE) == wxNOT_FOUND) {
                if (tmpfname.Len()>0) {    
                    filenames.Add(tmpfname);            
                }
                paths.Add(tmpstr);
            }
            while (tmpstr.Len() >0) {
                tmpstr = fs.FindNext();
                       tmpfname = tmpstr;
                       tmpfname.Replace(wxT("/usr/share/xfardic-xdb/"), _T(""));
                //DEBUGGING
                //fprintf(stderr, "%s\n", (const char *)tmpfname.mb_str(wxConvUTF8));

                if (filenames.Index(tmpfname,FALSE) == wxNOT_FOUND) {
                    if (tmpstr.Len() > 0) {    
                        if (tmpfname.Len()>0) {    
                            filenames.Add(tmpfname);            
                        }
                        paths.Add(tmpstr);
                    }
                }
            }
        }

        fs.ChangePathTo(wxT("/usr/local/share/xfardic-xdb/"), TRUE);

        tmpstr = fs.FindFirst(_T("*.xdb"),wxFILE);
        tmpfname = tmpstr;
        tmpfname.Replace(wxT("/usr/local/share/xfardic-xdb/"), _T(""));
        //DEBUGGING
        //fprintf(stderr, "%s\n", (const char *)tmpfname.mb_str(wxConvUTF8));

        if (tmpstr.Len() > 0) {        
            if (filenames.Index(tmpfname,FALSE) == wxNOT_FOUND) {
                if (tmpfname.Len()>0) {    
                    filenames.Add(tmpfname);            
                }
                paths.Add(tmpstr);
            }
            while (tmpstr.Len() >0) {
                tmpstr = fs.FindNext();
                       tmpfname = tmpstr;
                       tmpfname.Replace(wxT("/usr/local/share/xfardic-xdb/"), _T(""));
                //DEBUGGING
                //fprintf(stderr, "%s\n", (const char *)tmpfname.mb_str(wxConvUTF8));

                if (filenames.Index(tmpfname,FALSE) == wxNOT_FOUND) {
                    if (tmpstr.Len() > 0) {
                        if (tmpfname.Len()>0) {    
                            filenames.Add(tmpfname);            
                        }
                        paths.Add(tmpstr);
                    }
                }
            }
        }
           
        for (int x=0; x < paths.GetCount(); x++) {            
            if (paths.Item(x).Len()!=0) {
                initDB((const char *)paths.Item(x).mb_str(wxConvUTF8));                
            }

            att = _T(";");
            if (x+1 < paths.GetCount()) {
                    longpath += paths.Item(x) + att;
            } else {
                    longpath += paths.Item(x);
            }        
        }
        
        // Write detected path to config file
        pConfig->SetPath(wxT("/"));
        pConfig->Write(wxT("/Options/DB-Path"), longpath);              
       
        delete splash;
        wxYield();               
    }

    // Translation toolbar
    RecreateTrToolbar();      
  
    if (wordList.GetCount() >0) {
        menuFile->Enable(xFarDic_First, TRUE);
        menuFile->Enable(xFarDic_Last, TRUE);
    }

    if ( pConfig->Read(wxT("Auto-Select"), 1) != 0 ) {
        select = TRUE;
        opmenu->Check( xFarDic_Select, TRUE );
        if (vtool) {
            wxToolBarBase *tb = GetToolBar();
            tb->ToggleTool( ID_SELECT, TRUE );     
        }    
    } else {
        select = FALSE;
    }
    
    if ( pConfig->Read(wxT("Spell"), 1) != 0 ) {
        spell = TRUE;      
        opmenu->Check( xFarDic_Spell, TRUE );      
        if (vtool) {
            wxToolBarBase *tb = GetToolBar();
            tb->ToggleTool( ID_SPELL, TRUE );     
        }    
    } else {
        spell = FALSE;
    }   

    if ( pConfig->Read(wxT("RevSrch"), 0l) != 0 ) {
        revsrch = TRUE;      
        opmenu->Check( xFarDic_RevSrch, TRUE );      
        if (vtool) {
            wxToolBarBase *tb = GetToolBar();
            tb->ToggleTool( ID_REVSRCH, TRUE );     
        }    
    } else {
        revsrch = FALSE;
    }   

    if ( pConfig->Read(wxT("Watcher"), 1) != 0 ) {
        watcher = TRUE;      
        opmenu->Check( xFarDic_Watcher, TRUE );  
    } else {
        watcher = FALSE;
    }   

    if ( pConfig->Read(wxT("Notification"), 1) != 0 ) {
        notification = TRUE;      
        opmenu->Check( xFarDic_Notification, TRUE );  
    } else {
        notification = FALSE;
    }   

    if ( pConfig->Read(wxT("Speak"), 0l) != 0 ) {
        speak = TRUE;      
    } else {
        speak = FALSE;
    }   

    if ( pConfig->Read(wxT("Scanner"), 1) != 0 ) {
        scanner = TRUE;     
        opmenu->Check( xFarDic_Scanner, TRUE );
    
        // Initiating word scanning system
        oSelection.Init();
        oSelection.start();    
    } else {
        scanner = FALSE;

        // Speak if scanner is enabled
        speak = FALSE;
    }   

    if ( pConfig->Read(wxT("Hide"), 0l) != 0 ) {
        hide = TRUE;      
        opmenu->Check( xFarDic_Hide, TRUE );  
    } else {
        hide = FALSE;
    }   

    if ( pConfig->Read(wxT("Srch-Similar"), 0l) != 0 ) {
        srch = TRUE;      
        opmenu->Check( xFarDic_Srch, TRUE );      
        if (vtool) {
            wxToolBarBase *tb = GetToolBar();
            tb->ToggleTool( ID_SRCH, TRUE );     
        }        
    } else {
        srch = FALSE;
    }   
    
    // restore frame position
    int x = pConfig->Read(wxT("x"), 0l);
    int y = pConfig->Read(wxT("y"), 0l);

    Move(x,y);

    int save_cache = pConfig->Read(wxT("Save-Cache"), 1);

    if ( save_cache != 0) {
        cache = TRUE;
    } else {
        cache = FALSE;
    }    

    entryq = pConfig->Read(wxT("Num-Entries"), 10);
    
    if (cache) {
        pConfig->SetPath(wxT("../Cache"));
        wxString str;
        long dummy;
    
        bool bCont = pConfig->GetFirstEntry(str, dummy);
        while (bCont) {
            m_text->Append(str);
            bCont = pConfig->GetNextEntry(str, dummy);
        }
    }
    
    m_text->SetSelection(m_text->GetCount()-1);
    wxString m_textVal(m_text->GetValue());

    if (select) {
        m_text->SetSelection(0,m_textVal.Length());
    } 
     
    pConfig->SetPath(wxT("/"));
    
    //Init swap
    initSwap();

    //Init layout
    if (fit) {
        CreateLayout(TRUE);
    } else {
        CreateLayout(FALSE);
    }
}

void xFarDicApp::OnFocus(wxFocusEvent& event)
{
    wxString m_textVal(m_text->GetValue());
    m_text->SetSelection(0,m_textVal.Length());
    m_text->SetFocus();
    m_translate->SetDefault();
}

void xFarDicApp::OnActivate(wxActivateEvent& event)
{
    wxString m_textVal(m_text->GetValue());
    m_text->SetSelection(0,m_textVal.Length());
    m_text->SetFocus();
    m_translate->SetDefault();
}

void xFarDicApp::ViewToolbar(wxCommandEvent& WXUNUSED(event))
{
    wxToolBar *tbar = GetToolBar();
    wxConfigBase *pConfig = wxConfigBase::Get();
    if ( pConfig == NULL ) {
        return;
    }
      
    pConfig->SetPath(wxT("/"));
    
    if ( !vtool ) {
        vtool = TRUE;
        delete tbar;
        RecreateToolbar();    
        vimenu->Check( xFarDic_ViewToolBar, TRUE );        
        pConfig->Write(wxT("/Options/View-Toolbar"), 1);    
        translate(m_text->GetValue());

    } else {
        
        vtool = FALSE;
        int y = tbar->GetSize().y;    
        delete tbar;
        vimenu->Check( xFarDic_ViewToolBar, FALSE );        
        SetToolBar(NULL);    
        pConfig->Write(wxT("/Options/View-Toolbar"), 0);        
    }
}

void xFarDicApp::AutoTrans(wxCommandEvent& WXUNUSED(event))
{
    DoAutoTrans(); 
}

void xFarDicApp::DoAutoTrans()
{
    if (!revsrch) {
        wxString m_textVal(m_text->GetValue());
        m_textVal.Trim( TRUE );
        m_textVal.Trim( FALSE );
        m_textVal.MakeLower(); 

        if (CheckSpell(m_textVal, FALSE)) {                  
            if (m_textVal.Len() >1 && !srch) {
                translate(m_textVal);
            }
        }
    }
}

void xFarDicApp::OnSelect(wxCommandEvent& WXUNUSED(event))
{
  wxConfigBase *pConfig = wxConfigBase::Get();
    if ( pConfig == NULL ) {
        return;
    }
      
    pConfig->SetPath(wxT("/"));

    if ( select == TRUE ) {
        select = FALSE;
        if (vtool) {
            wxToolBarBase *tb = GetToolBar();
            tb->ToggleTool( ID_SELECT, FALSE );
        }    
        opmenu->Check( xFarDic_Select, FALSE );
        wxString m_textVal;
        m_text->SetSelection(0,0);
        pConfig->Write(wxT("/Options/Auto-Select"), 0);

    } else {
        select = TRUE;
        if (vtool) {
            wxToolBarBase *tb = GetToolBar();
            tb->ToggleTool( ID_SELECT, TRUE );
        }    
        opmenu->Check( xFarDic_Select, TRUE );    
        wxString m_textVal(m_text->GetValue());
        m_text->SetSelection(0,m_textVal.Length());
        pConfig->Write(wxT("/Options/Auto-Select"), 1);
    }
    delete wxConfigBase::Set((wxConfigBase *) NULL);
}

void xFarDicApp::OnSrch(wxCommandEvent& WXUNUSED(event))
{
    wxConfigBase *pConfig = wxConfigBase::Get();
    if ( pConfig == NULL ) {
        return;
    }
      
    pConfig->SetPath(wxT("/"));

    if ( srch == TRUE ) {
        srch = FALSE;
        wxToolBarBase *tb = GetToolBar();
        opmenu->Check( xFarDic_Srch, FALSE );
        tb->ToggleTool( ID_SRCH, FALSE );
        pConfig->Write(wxT("/Options/Srch-Similar"), 0);

    } else {
        srch = TRUE;
        wxToolBarBase *tb = GetToolBar();
        opmenu->Check( xFarDic_Srch, TRUE );
        tb->ToggleTool( ID_SRCH, TRUE );    
        pConfig->Write(wxT("/Options/Srch-Similar"), 1);
    }
    delete wxConfigBase::Set((wxConfigBase *) NULL);
}

void xFarDicApp::OnSpell(wxCommandEvent& WXUNUSED(event))
{
    DoOnSpell();
    if (revsrch) {
        DoOnRevSrch();
    }
}

void xFarDicApp::DoOnSpell()
{
    wxConfigBase *pConfig = wxConfigBase::Get();
    if ( pConfig == NULL ) {
        return;
    }

    pConfig->SetPath(wxT("/"));

    if ( spell == TRUE ) {
        spell = FALSE;
        wxToolBarBase *tb = GetToolBar();
        opmenu->Check( xFarDic_Spell, FALSE );
        tb->ToggleTool( ID_SPELL, FALSE );
        pConfig->Write(wxT("/Options/Spell"), 0);

    } else {
        spell = TRUE;
        wxToolBarBase *tb = GetToolBar();
        opmenu->Check( xFarDic_Spell, TRUE );
        tb->ToggleTool( ID_SPELL, TRUE );    
        pConfig->Write(wxT("/Options/Spell"), 1);
    }
    delete wxConfigBase::Set((wxConfigBase *) NULL);
}

void xFarDicApp::OnRevSrch(wxCommandEvent& WXUNUSED(event))
{
    DoOnRevSrch();
    if (spell) {
        DoOnSpell();
    }
}

void xFarDicApp::DoOnRevSrch()
{
    wxConfigBase *pConfig = wxConfigBase::Get();
    if ( pConfig == NULL ) {
        return;
    }
      
    pConfig->SetPath(wxT("/"));

    if ( revsrch == TRUE ) {
        revsrch = FALSE;
        wxToolBarBase *tb = GetToolBar();
        opmenu->Check( xFarDic_RevSrch, FALSE );
        tb->ToggleTool( ID_REVSRCH, FALSE );
        pConfig->Write(wxT("/Options/RevSrch"), 0);

    } else {
        revsrch = TRUE;
        wxToolBarBase *tb = GetToolBar();
        opmenu->Check( xFarDic_RevSrch, TRUE );
        tb->ToggleTool( ID_REVSRCH, TRUE );    
        pConfig->Write(wxT("/Options/RevSrch"), 1);
    }
    delete wxConfigBase::Set((wxConfigBase *) NULL);
}

void xFarDicApp::OnNotification(wxCommandEvent& WXUNUSED(event))
{
    wxConfigBase *pConfig = wxConfigBase::Get();
    if ( pConfig == NULL ) {
        return;
    }
      
    pConfig->SetPath(wxT("/"));

    if ( notification == TRUE ) {
        notification = FALSE;
        opmenu->Check( xFarDic_Notification, FALSE );
        pConfig->Write(wxT("/Options/Notification"), 0);
    } else {
        notification = TRUE;
        opmenu->Check( xFarDic_Notification, TRUE );
        pConfig->Write(wxT("/Options/Notification"), 1);
    }
    delete wxConfigBase::Set((wxConfigBase *) NULL);
}

void xFarDicApp::OnWatcher(wxCommandEvent& WXUNUSED(event))
{
    wxConfigBase *pConfig = wxConfigBase::Get();
    if ( pConfig == NULL ) {
        return;
    }
      
    pConfig->SetPath(wxT("/"));

    if ( watcher == TRUE ) {
        watcher = FALSE;
        opmenu->Check( xFarDic_Watcher, FALSE );
        pConfig->Write(wxT("/Options/Watcher"), 0);
    } else {
        watcher = TRUE;
        opmenu->Check( xFarDic_Watcher, TRUE );
        pConfig->Write(wxT("/Options/Watcher"), 1);
    }
    delete wxConfigBase::Set((wxConfigBase *) NULL);
}

void xFarDicApp::OnScanner(wxCommandEvent& WXUNUSED(event))
{
    wxConfigBase *pConfig = wxConfigBase::Get();
    if ( pConfig == NULL ) {
        return;
    }
      
    pConfig->SetPath(wxT("/"));
    
    if ( scanner == TRUE ) {
        scanner = FALSE;

        //Speak if scanner is enabled
        speak = FALSE;
        opmenu->Check( xFarDic_Scanner, FALSE );
        pConfig->Write(wxT("/Options/Scanner"), 0);
    } else {
        scanner = TRUE;
        opmenu->Check( xFarDic_Scanner, TRUE );
        pConfig->Write(wxT("/Options/Scanner"), 1);
    }
    delete wxConfigBase::Set((wxConfigBase *) NULL);
}

void xFarDicApp::OnHide(wxCommandEvent& WXUNUSED(event))
{
    wxConfigBase *pConfig = wxConfigBase::Get();
    if ( pConfig == NULL ) {
        return;
    }
      
    pConfig->SetPath(wxT("/"));
  
    if ( hide == TRUE ) {
        hide = FALSE;
        opmenu->Check( xFarDic_Hide, FALSE );
        pConfig->Write(wxT("/Options/Hide"), 0);
    } else {
        hide = TRUE;
        opmenu->Check( xFarDic_Hide, TRUE );
        pConfig->Write(wxT("/Options/Hide"), 1);
    }
    delete wxConfigBase::Set((wxConfigBase *) NULL);
}

void xFarDicApp::OnCopy(wxCommandEvent& WXUNUSED(event))
{
    wxString m_textVal(m_label->GetValue());

    // write to clipboard
    if (wxTheClipboard->Open()) {
        wxTheClipboard->SetData(new wxTextDataObject(m_textVal));
        wxTheClipboard->Close();
    }
}

void xFarDicApp::OnCut(wxCommandEvent& WXUNUSED(event))
{
    wxString m_textVal(m_text->GetValue());
    m_text->SetSelection(0,m_textVal.Length());
    m_text->Cut();
}

void xFarDicApp::OnPaste(wxCommandEvent& WXUNUSED(event))
{
    DoPaste();
}

void xFarDicApp::DoPaste()
{
    wxTextDataObject data;
    wxString Clipstr;

    /// read from clipboard
    if (wxTheClipboard->Open()) {
        if (wxTheClipboard->IsSupported( wxDF_TEXT )) {
            wxTheClipboard->GetData(data);
            Clipstr = data.GetText();          

            if (Clipstr.Len()==0) {
                wxString msg;
                msg.Printf( _("Input text is too long.\n"));
                wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
                m_text->SetFocus();
                return;
            } else {   
                m_text->SetValue(ProcessWord(Clipstr));     
            }
        }
        wxTheClipboard->Close();
    }    
    DoTranslate();
}

void xFarDicApp::Watcher(wxTimerEvent& event)
{
    // Update ltbox contents from config file
    LoadLeitnerBoxContents();

    if (watcher && !swapupdate) {         
        watcher_last = watcher_now.MakeLower();
        wxTextDataObject data;

        // read from clipboard
        if (wxTheClipboard->Open()) {
            wxTheClipboard->GetData(data);
            wxTheClipboard->Close();
        }

        watcher_now = data.GetText();

        if (watcher_now.Len() > 40) {
            watcher_now = watcher_last;
        }

        watcher_now.MakeLower();
        watcher_now.Trim(TRUE);
        watcher_now.Trim(FALSE);    

        // Purify word!
        watcher_now = ProcessWord(watcher_now);
    }

    if (scanner && !swapupdate) {
        wxConfigBase *pConfig = wxConfigBase::Get();
        scanner_last = scanner_now.MakeLower();
        scanner_now = pConfig->Read(wxT("/Options/Temp-String"), _T(""));

        scanner_now.MakeLower();
        scanner_now.Trim(TRUE);
        scanner_now.Trim(FALSE);

        scanner_now = ProcessWord(scanner_now);
    }    
   
    //DEBUGGING
    //fprintf(stderr, "Checking Scanner-Now:%s\n", (const char *)scanner_now.mb_str(wxConvUTF8));
    //fprintf(stderr, "Checking Scanner-Last:%s\n", (const char *)scanner_last.mb_str(wxConvUTF8));        

    if (watcher && !swapupdate) {
        if (watcher_now.Len() > 0) {
            if (!watcher_now.IsSameAs(watcher_last, FALSE) && !watcher_now.IsSameAs(scanner_last, FALSE) && 
               CheckSpell(watcher_now,0) && watcher_now.IsAscii() && watcher_now.IsWord()) {        
                m_text->SetValue(watcher_now);
                if (!notification) {           
                    translate(watcher_now);
                    this->Raise();
                    this->SetFocus();
                }else {
                    translate(watcher_now,FALSE,TRUE);
                }
            }
        }
    }

    if (scanner && !swapupdate) {
        if (scanner_now.Len() > 0 && scanner_now != m_text->GetValue()) {
            if (!scanner_now.IsSameAs(scanner_last, FALSE) && !scanner_now.IsSameAs(watcher_last, FALSE) && 
               CheckSpell(scanner_now,0) && scanner_now.IsAscii() && scanner_now.IsWord()) {        
                m_text->SetValue(scanner_now);
                if (!notification) {           
                    translate(scanner_now);
                    this->Raise();
                    this->SetFocus();
                }else {
                    translate(scanner_now,FALSE,TRUE);
                }
            }
        }
    }
}

void xFarDicApp::PopMenu()
{
    wxMenu* menuFileT = new wxMenu;
    wxArtClient client;

    wxBitmap  bquit = wxArtProvider::GetBitmap(wxART_QUIT, client, wxSize(16,16));
    wxBitmap  bpaste = wxArtProvider::GetBitmap(wxART_PASTE, client, wxSize(16,16));
    wxBitmap  bsettings = wxArtProvider::GetBitmap(wxT("gtk-preferences"), client, wxSize(16,16));
    wxBitmap  bfont = wxArtProvider::GetBitmap(wxART_HELP_SETTINGS, client, wxSize(16,16));
    wxBitmap  babout = wxArtProvider::GetBitmap(wxT("gtk-about"), client, wxSize(16,16));
    
    
    wxMenuItem *paste = new wxMenuItem(menuFileT,xFarDic_Paste, _("&Paste and Translate\tCtrl-V"));
    paste->SetBitmap(bpaste);
    menuFileT->Append(paste);

    wxMenuItem *setfont = new wxMenuItem(menuFileT,xFarDic_Setfont, _("Set Result Box Font\tCtrl+F"));
    setfont->SetBitmap(bfont);
    menuFileT->Append(setfont);

    wxMenuItem *settings = new wxMenuItem(menuFileT,xFarDic_Settings, _("Open Preferences"));
    settings->SetBitmap(bsettings);
    menuFileT->Append(settings);
    menuFileT->AppendSeparator();

    wxMenuItem *about = new wxMenuItem(menuFileT,xFarDic_About, _("&About xFarDic\tF1"));
    about->SetBitmap(babout);
    menuFileT->Append(about);
    menuFileT->AppendSeparator();

    wxMenuItem *tquit = new wxMenuItem(menuFileT,xFarDic_QApp, _("&Quit\tCtrl+Q"));
    tquit->SetBitmap(bquit);
    menuFileT->Append(tquit);
    ticon.PopupMenu(menuFileT);
}

void xFarDicApp::OnSetFont(wxCommandEvent& WXUNUSED(event))
{
    ShowSetFont();
}

void xFarDicApp::ShowSetFont()
{
    wxFontData data;
    wxConfigBase *pConfig = wxConfigBase::Get();
    data.SetInitialFont(m_font);
    
    wxFontDialog dialog(this, data);
    if ( dialog.ShowModal() == wxID_OK ) {
        retData = dialog.GetFontData();
        m_font = retData.GetChosenFont();        
        m_label->SetFont(m_font);    
    
        pConfig->SetPath(wxT("/"));
        
        pConfig->Write(wxT("/Options/Font-Face"), m_font.GetFaceName());
        pConfig->Write(wxT("/Options/Font-Size"), m_font.GetPointSize());
        pConfig->Write(wxT("/Options/Font-Style"), m_font.GetStyle());
        pConfig->Write(wxT("/Options/Font-Family"), m_font.GetFamily());
        pConfig->Write(wxT("/Options/Font-Enc"), m_font.GetDefaultEncoding());
        pConfig->Write(wxT("/Options/Font-Wgt"), m_font.GetWeight());
        
        delete wxConfigBase::Set((wxConfigBase *) NULL);
    } 
}

/// Toolbar Creation Function
void xFarDicApp::RecreateToolbar(bool activate)
{
    // delete and recreate the toolbar
    wxToolBarBase *toolBar = GetToolBar();

    delete toolBar;
    SetToolBar(NULL);    

    if (activate) {
        long style = toolBar ? toolBar->GetWindowStyle() : TOOLBAR_STYLE;   
        style &= ~(wxTB_HORIZONTAL | wxTB_VERTICAL);
        style |= m_horzToolbar ? wxTB_HORIZONTAL : wxTB_VERTICAL;

        toolBar = CreateToolBar(style, ID_TOOLBAR);        

        // Set up toolbar
        wxBitmap toolBarBitmaps[13];
        wxArtClient client;

        wxBitmap  cut = wxArtProvider::GetBitmap(wxART_CUT, client, wxDefaultSize);
        wxBitmap  quit = wxArtProvider::GetBitmap(wxART_QUIT, client, wxDefaultSize);
        wxBitmap  paste = wxArtProvider::GetBitmap(wxART_PASTE, client, wxDefaultSize);
        wxBitmap  copy = wxArtProvider::GetBitmap(wxART_COPY, client, wxDefaultSize);
        wxBitmap  settings = wxArtProvider::GetBitmap(wxT("gtk-preferences"), client, wxDefaultSize);
        wxBitmap  trash = wxArtProvider::GetBitmap(wxT("gtk-clear"), client, wxDefaultSize);
        wxBitmap  selectb = wxArtProvider::GetBitmap(wxART_REDO, client, wxDefaultSize);
        wxBitmap  btranslate = wxArtProvider::GetBitmap(wxART_FIND, client, wxDefaultSize);
        wxBitmap  back = wxArtProvider::GetBitmap(wxART_GO_BACK, client, wxDefaultSize);
        wxBitmap  forward = wxArtProvider::GetBitmap(wxART_GO_FORWARD, client, wxDefaultSize);
        wxBitmap  spellb = wxArtProvider::GetBitmap(wxT("gtk-spell-check"), client, wxDefaultSize);
        wxBitmap  revsrchb = wxArtProvider::GetBitmap(wxART_UNDO, client, wxDefaultSize);
        wxBitmap  similar = wxArtProvider::GetBitmap(wxT("gtk-find-and-replace"), client, wxDefaultSize);
        wxBitmap  leitner = wxArtProvider::GetBitmap(wxT("gnome-devel"), client, wxDefaultSize);                  

        toolBarBitmaps[0]  = back;
        toolBarBitmaps[1]  = forward;
        toolBarBitmaps[2]  = similar;
        toolBarBitmaps[3]  = quit;
        toolBarBitmaps[4]  = selectb;
        toolBarBitmaps[5]  = settings;
        toolBarBitmaps[6]  = copy;
        toolBarBitmaps[7]  = cut;
        toolBarBitmaps[8]  = paste;
        toolBarBitmaps[9]  = trash;
        toolBarBitmaps[10] = spellb;
        toolBarBitmaps[11] = revsrchb;
        toolBarBitmaps[12] = leitner;

        if ( !m_smallToolbar ) {
            int w = 2*toolBarBitmaps[0].GetWidth(),
                h = 2*toolBarBitmaps[0].GetHeight();
            for ( size_t n = 0; n < WXSIZEOF(toolBarBitmaps); n++ ) {
                toolBarBitmaps[n] =
                    wxBitmap(toolBarBitmaps[n].ConvertToImage().Scale(w, h));
            }

            toolBar->SetToolBitmapSize(wxSize(w, h));
        }

        toolBar->SetToolSeparation(0);

        toolBar->AddTool(ID_BACK, _("Back"), toolBarBitmaps[0], _("Previous Word"));
        toolBar->AddTool(ID_FORWARD, _("Fwd"), toolBarBitmaps[1], _("Next Word"));
        toolBar->AddSeparator();
        toolBar->AddTool(ID_CUT, _("Cut"), toolBarBitmaps[7], _("Cut"));
        toolBar->AddTool(ID_COPY, _("Copy"), toolBarBitmaps[6], _("Copy Result"));
        toolBar->AddTool(ID_PASTE, _("Paste"), toolBarBitmaps[8], _("Paste and Translate"));
        toolBar->AddTool(ID_TRASH, _("Trash"), toolBarBitmaps[9], _("Clear History"));
        //toolBar->AddTool(ID_TOOL_LT, _("Leitner Box"), toolBarBitmaps[12], _("Open leitner box"));        
        toolBar->AddSeparator();
        toolBar->AddTool(ID_SELECT, _("Select"), toolBarBitmaps[4], _("Auto Select Text"), wxITEM_CHECK);
        toolBar->AddTool(ID_SPELL, _("Spell"), toolBarBitmaps[10], _("Spell Checking"), wxITEM_CHECK);
        toolBar->AddTool(ID_REVSRCH, wxT("RevSrch"), toolBarBitmaps[11], _("Reverse Search"), wxITEM_CHECK);
        toolBar->AddTool(ID_SRCH, _("Similar"), toolBarBitmaps[2], _("Return similar words"), wxITEM_CHECK);
        toolBar->AddSeparator();
        toolBar->AddTool(ID_SETTINGS, _("Preferences"), toolBarBitmaps[5], _("Preferences"));
        toolBar->AddTool(ID_QUIT, _("Quit"), toolBarBitmaps[3], _("Quit"));

        wxToolBarBase *tb = GetToolBar();
        tb->EnableTool(ID_BACK, FALSE);
        tb->EnableTool(ID_FORWARD, FALSE);

        if (select) {
            tb->ToggleTool( ID_SELECT, TRUE );     
        }
        
        if (spell) {
            tb->ToggleTool( ID_SPELL, TRUE );     
        }

        if (revsrch) {
            tb->ToggleTool( ID_REVSRCH, TRUE );     
        }

        if (srch) {
            tb->ToggleTool( ID_SRCH, TRUE );     
        }  
    } else {
        toolBar = CreateToolBar(-1, ID_TOOLBAR);
    }
}

/// Translation toolbar creation function
void xFarDicApp::RecreateTrToolbar()
{
    m_text = new wxComboBox(this, ID_COMBO, _T(""), wxDefaultPosition, wxSize(335, 32), 0, NULL,
                            wxCB_DROPDOWN & wxPROCESS_ENTER);
    m_text->SetFocus();

    // Icon
    wxArtClient client;    
    wxBitmap  btranslate = wxArtProvider::GetBitmap(wxART_FIND, client, wxDefaultSize);
    wxBitmap  bltbox = wxArtProvider::GetBitmap(wxT("gnome-devel"), client, wxDefaultSize);
    wxBitmap  bttos = wxArtProvider::GetBitmap(wxT("sound"), client, wxDefaultSize);

    m_translate = new wxBitmapButton(this, ID_BUTTON_TRANSLATE, btranslate, wxDefaultPosition, wxSize(45,34));
    m_leitnerbox = new wxBitmapButton(this, ID_BTN_LT, bltbox, wxDefaultPosition, wxSize(45,34));
    m_ttos = new wxBitmapButton(this, ID_BUTTON_TTOS, bttos, wxDefaultPosition, wxSize(45,34));

    if (!tts) {
       m_ttos->Enable(FALSE);
    }

    //Set Default button
    m_translate->SetDefault();   
}

bool xFarDicApp::translate(wxString m_textVal, bool atrans, bool notify)
{
    int nrow, ncol, returnvalue;
    char** qresult;
    char** qrresult;

    wxString qsql;
    wxProgressDialog *prog;
    
    if (m_textVal.Len()==0) {
        m_textVal = m_text->GetValue();    
    }

    found = FALSE;
    
    m_textVal.Trim( TRUE );
    m_textVal.Trim( FALSE );
    m_textVal.MakeLower();    

    // Purify word!
    m_textVal = ProcessWord(m_textVal);

    // DEBUGGING
    //fprintf(stderr, "%s\n", (const char *)m_textVal.mb_str(wxConvUTF8));

    /// mmm... We do not need empty string!
    if (m_textVal.Len()==0) {
        wxString msg;
        msg.Printf( _("Please enter clause.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        m_text->SetFocus();
        return 0;
    }   
    
    wxString document = path;       

    if (srch && !revsrch) {
        int y =0;
        wxBusyCursor wait;
        wxString tmpsrchII;
        tmpstr = _T("");
        if (!swap) {
            prog = new wxProgressDialog(_T("xFarDic"), _("Please wait..."), meanList.GetCount(), 
                                    this, wxPD_APP_MODAL | wxPD_AUTO_HIDE | wxPD_SMOOTH);
        }

        while (y < wordList.GetCount()) {
            tmpsrchII = wordList.Item(y);
            if (tmpsrchII.Contains(m_textVal)) {
                found = TRUE;
                if (!swap) {
                    tmpstr += meanList.Item(y) + _T(" = ") + tmpsrchII + _T("\n\n");            
                } else {
                    qsql = wxT("SELECT outw FROM words WHERE inw LIKE '%")+m_textVal+wxT("%'");
                    returnvalue = sqlite3_get_table(Db, (const char *)qsql.mb_str(wxConvUTF8),&qresult, &nrow, 
                                                    &ncol, &db_error_msg);

                    // DEBUGGING
                    //fprintf(stderr, "returned meanings:%d\n", nrow);
                    
                    for (int x=1; x <= nrow; x++) {
                        tmpstr += UTF8_STR(qresult[x]) + _T(" = ") + tmpsrchII + _T("\n\n");
                    }
                }
            }
            y++;

            if (!swap) {
                if (y % 500  == 0) {
                    prog->Update(y);
                }        
            }
        }
       
        if (!swap) {
            // Killing progress dialog
            delete prog;
            wxYield();    
        }

        m_label->SetFont(m_font);    
        m_label->Clear();
        if (tmpstr.Len()!=0) {
            m_label->WriteText(tmpstr);
        } else {
            m_label->SetValue(_("Phrase not found."));
        }
    } else {
        
        if (!revsrch) {
            if (wordList.Index(m_textVal,FALSE) != wxNOT_FOUND) {
                wxString tmpsrchIII;
                int j=0;
                tmpstr = _T("");
                found = TRUE;
                
                if (m_label->GetValue()) {
                    if (!swap) {
                        while (j < wordList.GetCount()) {
                            tmpsrchIII = wordList.Item(j);
                            if (tmpsrchIII.IsSameAs(m_textVal, FALSE)) {
                                // DEBUGGING
                                // fprintf(stderr, "%s\n", (const char *)wordList.Item(j).mb_str(wxConvUTF8));  
                                // fprintf(stderr, "j:%d\n", j);
                                // fprintf(stderr, "%s\n", (const char *)meanList.Item(j).mb_str(wxConvUTF8));  
                                tmpstr += meanList.Item(j) + _T("\n\n");
                            }        
                            j++;
                        }
                    } else {                    
                        qsql = wxT("SELECT outw FROM words WHERE inw = '")+m_textVal+wxT("'");
                        returnvalue = sqlite3_get_table(Db, (const char *)qsql.mb_str(wxConvUTF8),&qresult, 
                                                        &nrow, &ncol, &db_error_msg);
                        
                        // DEBUGGING
                        //fprintf(stderr, "returned meanings:%d\n", nrow);

                        for (int x=1; x <= nrow; x++) {
                            tmpstr += UTF8_STR(qresult[x]) + _T("\n\n");
                        }                
                    }

                    m_label->Clear();
                    m_label->SetFont(m_font);    
                    m_label->WriteText(tmpstr);               
                    m_text->SetValue(wordList.Item(wordList.Index(m_textVal,FALSE)));    
                }
               
                if (atrans == FALSE) {
                    if (m_text->FindString(m_textVal) == -1) {
                        if (m_text->GetCount() <= entryq-1) {
                            if (m_textVal.Len()>1) {
                                m_text->Append(m_textVal);
                            }
                            m_text->SetSelection(m_text->GetCount()-1);              
                        } else {
                            m_text->Delete(0);

                            if (m_textVal.Len()>1) {
                                m_text->Append(m_textVal);
                            }
                            m_text->SetSelection(m_text->GetCount()-1);
                            m_text->SetValue(m_textVal);
                        }
                    }
                }
            } else {
                found = FALSE;
                m_label->SetValue(_("Phrase not found."));            
            }    
        } else {
            // implement reverse rearch
            int x =0;
            wxBusyCursor wait;
            wxString tmpsrch;
            tmpstr = _T("");
            if (!swap) {
                prog = new wxProgressDialog(_T("xFarDic"), _("Please wait..."), meanList.GetCount(), this,
                                            wxPD_APP_MODAL | wxPD_AUTO_HIDE | wxPD_SMOOTH);
            
                while (x < meanList.GetCount()) {
                    tmpsrch = meanList.Item(x);
                    if (tmpsrch.Contains(m_textVal)) {
                        found = TRUE;                
                        tmpstr += tmpsrch + _T(" = ") + wordList.Item(x) + _T("\n\n");
                    }
                    x++;
                    if (x % 500  == 0) {
                        prog->Update(x);
                    }        
                }    

                // Killing progress dialog
                delete prog;       
                wxYield();
            } else {
                qsql = wxT("SELECT inw FROM words WHERE outw LIKE '%")+m_textVal+wxT("%'");                                
                returnvalue = sqlite3_get_table(Db, (const char *)qsql.mb_str(wxConvUTF8),&qresult, &nrow, 
                                                &ncol, &db_error_msg);

                qsql = wxT("SELECT outw FROM words WHERE outw LIKE '%")+m_textVal+wxT("%'");                                
                returnvalue = sqlite3_get_table(Db, (const char *)qsql.mb_str(wxConvUTF8),&qrresult, &nrow, 
                                                &ncol, &db_error_msg);

                // DEBUGGING
                //fprintf(stderr, "returned meanings:%d\n", nrow);

                if (nrow > 0) {
                    found = TRUE;
                }
                    
                for (int x=1; x <= nrow; x++) {            
                    tmpstr += UTF8_STR(qrresult[x]) + _T(" = ") + UTF8_STR(qresult[x]) + _T("\n\n");
                }
            }

            m_label->SetFont(m_font);    
            m_label->Clear();
            if (tmpstr.Len()!=0) {
                m_label->WriteText(tmpstr);
            } else {
                m_label->SetValue(_("Phrase not found."));
            }
        }
    }
           
    if (found && !revsrch && wordList.Index(m_text->GetValue(),FALSE) > 0 && 
        !(1-(wordList.Index(m_text->GetValue(),FALSE)) == 0)) {

        if (vtool) {
            wxToolBarBase *tb = GetToolBar();
            tb->EnableTool(ID_BACK, TRUE);
        }     
        menuFile->Enable(xFarDic_Back, TRUE);
        if (select) {
            wxString m_textVal(m_text->GetValue());
            m_text->SetSelection(0,m_textVal.Length());
        }  
    } else {
        if (vtool) {
            wxToolBarBase *tb = GetToolBar();
            tb->EnableTool(ID_BACK, FALSE);
        }    
        menuFile->Enable(xFarDic_Back, FALSE);    
    }

    if (found && !revsrch && !((wordList.Index(m_text->GetValue(),FALSE)) == wordList.Index(wordList.Last(),FALSE))) {
        if (vtool) {
            wxToolBarBase *tb = GetToolBar();
            tb->EnableTool(ID_FORWARD, TRUE);
        }  
        menuFile->Enable(xFarDic_Forward, TRUE);
        if (select) {
            wxString m_textVal(m_text->GetValue());
            m_text->SetSelection(0,m_textVal.Length());
        }  
    } else {
        if (vtool) {
            wxToolBarBase *tb = GetToolBar();
            tb->EnableTool(ID_FORWARD, FALSE);
        }    
        menuFile->Enable(xFarDic_Forward, FALSE);    
    }

    if (select) {
        wxString m_textVal(m_text->GetValue());
        m_text->SetSelection(0,m_textVal.Length());
    }  

    if (!found) {
        m_label->SetValue(_("Phrase not found."));    
    } else {
        if (ltbox.GetCount() < ltbaselimit) {
            m_leitnerbox->Enable(TRUE);
        }
    }

#ifdef HAVE_SPEAKLIB
    if (speak) {
        pron->Pronounce(m_text->GetValue());
    }
#endif

    if (notify && notification) {
        ShowNotification(m_textVal, m_label->GetValue());
    }

    return found;
}

void xFarDicApp::OnTranslate(wxCommandEvent& WXUNUSED(event))
{
    DoTranslate();     
}

void xFarDicApp::DoTranslate()
{
    wxString m_textVal(m_text->GetValue());
    m_textVal.Trim( TRUE );
    m_textVal.Trim( FALSE );
    m_textVal.MakeLower();    

    if (spell) {   
        if (!revsrch) {    
            if (CheckSpell(m_textVal,1) == 0) {      
                wxString suggestion = ShowAspell(sugList);                  

                if (suggestion.Len()!=0) {
                    m_text->SetValue(suggestion);
                    m_textVal = suggestion;
                    m_textVal.Trim( TRUE );
                    m_textVal.Trim( FALSE );
                    m_textVal.MakeLower();
                } else {
                    return;
                }                 
            } 
        }
    }  

    //let actually translate!
    translate();  
    m_text->SetFocus();   
}

wxString xFarDicApp::ShowAspell(wxArrayString sugList)
{
    wxSingleChoiceDialog aspelldialog(this, _("xFarDic spell checker found error(s) on your typed word.\n Please choose correct word from list and then click OK."), _("xFarDic Spell Checker"), sugList);

    if (aspelldialog.ShowModal() == wxID_OK) {
        return aspelldialog.GetStringSelection();
    } else {
        return wxEmptyString;
    }                
}

void xFarDicApp::OnSettings(wxCommandEvent& WXUNUSED(event))
{
    ShowSettings();
}

void xFarDicApp::ShowSettings()
{
    if (showSettings) {
        // getting main window position
        int pos_x, pos_y;
        GetPosition(&pos_x, &pos_y);

        // getting mainwindow size
        int size_x, size_y;
        GetSize(&size_x, &size_y);

        // Settings window position
        int z = pos_x + (( size_x - pos_x) / 2 );
        int w = pos_y + (( size_y - pos_y) / 2 );

        setframe = new xFarDicSettings(this, _("xFarDic Preferences"), wxPoint(z, w), wxDefaultSize
                         , m_locale, wxSYSTEM_MENU | wxCAPTION | wxFRAME_FLOAT_ON_PARENT | wxFRAME_NO_TASKBAR | wxCLOSE_BOX);       
           
        setframe->Show(TRUE);
        showSettings = FALSE;
    }
}

void xFarDicApp::ShowAbout()
{
    if (showAbout) {
        // getting main window position
        int pos_x, pos_y;
        GetPosition(&pos_x, &pos_y);

        // getting mainwindow size
        int size_x, size_y;
        GetSize(&size_x, &size_y);

        // About window position
        int z = pos_x + (( size_x - pos_x) / 2 );
        int w = pos_y + (( size_y - pos_y) / 2 );

        abframe = new xFarDicAbout(this, _("About xFarDic"), wxPoint(z, w), wxDefaultSize
                         , m_locale, wxSYSTEM_MENU | wxCAPTION | wxFRAME_FLOAT_ON_PARENT | wxFRAME_NO_TASKBAR | wxCLOSE_BOX);
      
        abframe->Show(TRUE);
        showAbout = FALSE;
    }  
}

void xFarDicApp::ShowLeitner()
{
    if (showLeitner) {
        // getting main window position
        int pos_x, pos_y;
        GetPosition(&pos_x, &pos_y);
 
        // getting mainwindow size
        int size_x, size_y;
        GetSize(&size_x, &size_y);

        // window position
        int z = pos_x + (( size_x - pos_x) / 2 );
        int w = pos_y + (( size_y - pos_y) / 2 );

        ltframe = new xFarDicLeitner(this, _("xFarDic - Leitner Box"), wxPoint(z, w), wxDefaultSize
                         , m_locale, wxSYSTEM_MENU | wxCAPTION | wxFRAME_FLOAT_ON_PARENT | wxFRAME_NO_TASKBAR | wxCLOSE_BOX);
      
        ltframe->Show(TRUE);
        showLeitner = FALSE;
    }  
}

/// Quit event handler
void xFarDicApp::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    DoQuit();
}

void xFarDicApp::DoQuit()
{    
    // TRUE is to force the frame to close
    wxConfigBase *pConfig = wxConfigBase::Get();
    pConfig->SetPath(wxT("/"));

    if ( pConfig->Read(wxT("/Options/Save-Cache"), 1) != 0 ) {
        //delete all entries from file
        int count = pConfig->Read(wxT("/Options/Num-Entries"), 10);
        int textcount = m_text->GetCount();
    
        pConfig->SetPath(wxT("/Cache"));    
        wxString str;
        long dummy;
        int counter =0;
    
        bool bCont = pConfig->GetFirstEntry(str, dummy);
        for (int i=0; i<=textcount; i++) {
            pConfig->DeleteEntry(str, FALSE);     
            str = _T("");           
            pConfig->GetFirstEntry(str, dummy);
            counter++;
            //fprintf(stderr, "delete entry:%d\n", counter);
        }
            
        if (m_text->GetCount() > 0) {                           
            if (textcount < count) {
                count = textcount;
            }
            for (int j=0; j<count; j++) {                           
                pConfig->Write(m_text->GetString(j), j);            
            }
        }    
    } else {
        //delete all entries from file      
        pConfig->SetPath(wxT("/"));
        pConfig->DeleteGroup(wxT("Cache"));    
    }    
    
    pConfig->SetPath(wxT("/"));

    if (pConfig->Read(wxT("/Options/Win-Pos"), 0l) != 0 ) {
        int x, y, w, h;
        GetPosition(&x, &y);
        GetSize(&w, &h);
        pConfig->Write(wxT("/Options/x"), (long) x);
        pConfig->Write(wxT("/Options/y"), (long) y);
        pConfig->Write(wxT("/Options/w"), (long) w);
        pConfig->Write(wxT("/Options/h"), (long) h);
    } else {
        pConfig->Write(wxT("/Options/Win-Pos"), 0);
        pConfig->Write(wxT("/Options/x"), 0);
        pConfig->Write(wxT("/Options/y"), 0);      
        pConfig->Write(wxT("/Options/w"), 0);
        pConfig->Write(wxT("/Options/h"), 0);      
    }

    if (this->IsMaximized()) {
        pConfig->Write(wxT("/Options/IsMaximized"), 1);
    }else {
        pConfig->Write(wxT("/Options/IsMaximized"), 0);
    }

#ifdef HAVE_SPEAKLIB
    //Kill Espeak
    if (tts) {
      pron->Kill();
    }
#endif
    
    //Stop selection system
    oSelection.End();       

    //Destroy xFarDic
    Destroy();
}

/// Close event handles
void xFarDicApp::OnClose(wxCloseEvent& WXUNUSED(event))
{
    if (hide == TRUE) {
        this->Show(FALSE);
    } else {
        DoQuit();
    }
}

void xFarDicApp::OnBack(wxCommandEvent& WXUNUSED(event))
{
    if (wordList.Index(m_text->GetValue(),FALSE) != wxNOT_FOUND ) {
        translate(wordList.Item((wordList.Index(m_text->GetValue(),FALSE))-1),TRUE);
    }
    return;
}

void xFarDicApp::OnForward(wxCommandEvent& WXUNUSED(event))
{     
    if (wordList.Index(m_text->GetValue(),FALSE) != wxNOT_FOUND ) {          
        translate(wordList.Item((wordList.Index(m_text->GetValue(),FALSE))+1),TRUE);
    }
    return;
}

void xFarDicApp::OnFirst(wxCommandEvent& WXUNUSED(event))
{               
    translate(wordList.Item(1),TRUE);
    return;
}

void xFarDicApp::OnLast(wxCommandEvent& WXUNUSED(event))
{               
    translate(wordList.Last(),TRUE);
    return;
}

void xFarDicApp::OnTrash(wxCommandEvent& WXUNUSED(event))
{
    wxConfigBase *pConfig = wxConfigBase::Get();

    //delete all entries from file          
    pConfig->SetPath(wxT("/"));
    pConfig->DeleteGroup(wxT("Cache"));

    delete wxConfigBase::Set((wxConfigBase *) NULL);   
    m_text->Clear();
}

void xFarDicApp::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    ShowAbout();
}

void xFarDicApp::OnLeitner(wxCommandEvent& WXUNUSED(event))
{
    ShowLeitner();
}

void xFarDicApp::Hide(wxIconizeEvent& event)
{    
    if (event.Iconized() && hide == TRUE) {
        this->Show(FALSE);
    } else {
        this->Show(TRUE);                                                                                       
    }                      
}

/// Spell checking main function
/// returns 0 if not correct.
/// returns 1 if correct.
/// returns 2 if Aspell is not installed.
bool xFarDicApp::CheckSpell(wxString chkStr, bool suggest)
{
    //spell checking goes here
    AspellConfig * spell_config = new_aspell_config();

    // Some error handling for Aspell
    //if (inputlang.Len()!=0) {
    //     aspell_config_replace(spell_config, "lang", (const char *)inputlang.mb_str(wxConvUTF8));
    //} else {
    aspell_config_replace(spell_config, "lang","en");
    //}

    // Small hack for two part words to ignore aspell
    if (chkStr.Contains(_T(" "))) { 
        return 1;
    }

    AspellCanHaveError * possible_err = new_aspell_speller(spell_config);
    AspellSpeller * spell_checker = 0;

    if (aspell_error_number(possible_err) != 0) {        
        //DEBUGGING
        //fprintf(stderr, "%s",aspell_error_message(possible_err),1);
        if (!aspelli) {
            wxString msg;
            msg.Printf(_("It seems that Aspell is not installed.\nxFarDic will not work correctly."));
            wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_WARNING, this);
            aspelli = TRUE;
        }
        spell =0;
        return 2;
    } else {
        spell_checker = to_aspell_speller(possible_err); 
    }

    if (suggest) {
        const AspellWordList * suggestions = aspell_speller_suggest(spell_checker, (const char *)chkStr.mb_str(wxConvUTF8),
                                                                    chkStr.Len());
        AspellStringEnumeration * elements = aspell_word_list_elements(suggestions);
        const char * word;

        // clear array
        sugList.Empty();
    
        while ((word = aspell_string_enumeration_next(elements)) != NULL ) {
            // add words to suggestion list         
            size_t copies =1;
            if (wordList.Index(UTF8_STR(word),FALSE) != wxNOT_FOUND) {
                sugList.Add(UTF8_STR(word),copies);    
            }
        }
    }

    // resturns 1 if correct
    return aspell_speller_check(spell_checker, (const char *)chkStr.mb_str(wxConvUTF8), chkStr.Len());
}

bool xFarDicApp::initDB(const char *filename) {    
    int ret, counter, returnvalue;
    size_t copies = 1;      
    wxString msg, tmpstr, path, insertSQL;
    wxFile xmldb;
    
    // Check if xdb file exists before parsing
    if (!xmldb.Exists(UTF8_STR(filename))) {
        // DEBUGGING
        // fprintf(stderr, "%s\n", filename);
        return FALSE;
    }
   
    counter =0;     

    reader = xmlReaderForFile(filename, NULL, 0);
    if (reader != NULL) {
        ret = xmlTextReaderRead(reader);
        while (ret == 1) {
            if (xmlTextReaderNodeType(reader) == 3) {
                counter++; 
                if (counter > 2) {                                                    
                    if (counter % 2 > 0) {                                    
                       tmpstr = UTF8_STR((char *)xmlTextReaderValue(reader));  
                       wordList.Add(tmpstr.Lower(),copies);                
                    } else {
                       if (!swap || swapupdate) {
                           tmpstr = UTF8_STR((char *)xmlTextReaderValue(reader)); 
                           meanList.Add(tmpstr.Lower(),copies);
                       }
                    }
                }        
            }        
            
            ret = xmlTextReaderRead(reader);
            // DEBUGGING      
            // fprintf(stderr, "%d\n", ret);
        } // End while
         
        // DEBUGGING      
        // fprintf(stderr, "Total Meanings:%d\n", meanList.GetCount());
        // fprintf(stderr, "Total Words:%d\n", wordList.GetCount());
        
        xmlFreeTextReader(reader);
        xmlCleanupParser();
        return TRUE;
    } else {        
        msg.Printf( _("Parse Error. Invalid Document.\n It is possible that XML-DB is not installed.\n Set XML DB path in settings window."));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_STOP, this);
        return FALSE;
    }
}

bool xFarDicApp::ShowNotification(wxString word, wxString meaning)
{
    if (! notification) {
       // if notification is not enabled, exit
       return TRUE;
    }

    notify_init("xFarDic");

    //Get Configuration From Config File
    wxConfigBase *pConfig = wxConfigBase::Get();

    pConfig->SetPath(wxT("/Options"));
    int timeout = pConfig->Read(wxT("/Options/Scan-Timeout"), 5);
    
    if (timeout != 0) {
       timeout = timeout*1000;
    }

    if (meaning.Len() > 1100) {
        meaning.Truncate(1100);
        meaning = meaning + _T("...");
    }

    if (n == NULL) {
        n = notify_notification_new ((const char *)word.mb_str(wxConvUTF8), 
                                     (const char *)meaning.mb_str(wxConvUTF8),
                                     "stock_help", NULL);
    } else {
        notify_notification_close (n, NULL);
        n = notify_notification_new ((const char *)word.mb_str(wxConvUTF8), 
                                     (const char *)meaning.mb_str(wxConvUTF8),
                                     "stock_help", NULL);
    }    
    
    notify_notification_set_timeout (n, timeout); // timeout, 0 will disable that
    
    if (!swapupdate) {
        if (!notify_notification_show (n, NULL)) {
            // DEBUGGING
            // fprintf(stderr, "failed to send notification\n");
            return TRUE;
        }
    }

    delete wxConfigBase::Set((wxConfigBase *) NULL);
}

wxString xFarDicApp::ProcessWord(wxString word) {
    wxString LastChar, FirstChar;

    FirstChar = word;
    FirstChar.Right(1);

    LastChar = word.Last();

    // DEBUGGING
    // fprintf(stderr, "%s\n", (const char *)word.mb_str(wxConvUTF8));
    
    // Check last parentheses!    
    if (LastChar.IsSameAs(_T(")"),FALSE)) {
        word = word.RemoveLast();
    }
            
    // Check last point!    
    if (LastChar.IsSameAs(_T("."),FALSE)) {
        word = word.RemoveLast();
    }

    // Check last colon!
    if (LastChar.IsSameAs(_T(":"),FALSE)) {
        word = word.RemoveLast();
    }

    // Check last semicolon!
    if (LastChar.IsSameAs(_T(";"),FALSE)) {
        word = word.RemoveLast();
    }

    // Check last comma!
    if (LastChar.IsSameAs(_T(","),FALSE)) {
        word = word.RemoveLast();
    }

    // Check last quotation!
    if (LastChar.IsSameAs(_T("\""),FALSE)) {
        word = word.RemoveLast();
    }

    // Check last single quotation!
    if (LastChar.IsSameAs(_T("'"),FALSE)) {
        word = word.RemoveLast();
    }

    // Check last exclamation mark!
    if (LastChar.IsSameAs(_T("!"),FALSE)) {
        word = word.RemoveLast();
    }

    // Check last comma!
    if (LastChar.IsSameAs(_T("?"),FALSE)) {
        word = word.RemoveLast();
    }

    // Check last dash!
    if (LastChar.IsSameAs(_T("-"),FALSE)) {
        word = word.RemoveLast();
    }

    // Check last star!
    if (LastChar.IsSameAs(_T("*"),FALSE)) {
        word = word.RemoveLast();
    }

    // Check first parentheses!    
    if (FirstChar.IsSameAs(_T("("),FALSE)) {
        word = word.Right(word.Len()-1);
    }
    
    // Check first point!    
    if (FirstChar.IsSameAs(_T("."),FALSE)) {
        word = word.Right(word.Len()-1);
    }

    // Check first colon!
    if (FirstChar.IsSameAs(_T(":"),FALSE)) {
        word = word.Right(word.Len()-1);
    }

    // Check first comma!
    if (FirstChar.IsSameAs(_T(","),FALSE)) {
        word = word.Right(word.Len()-1);
    }

    // Check first dash!
    if (FirstChar.IsSameAs(_T("-"),FALSE)) {
        word = word.Right(word.Len()-1);
    }

    // Check first semicolon!
    if (FirstChar.IsSameAs(_T(";"),FALSE)) {
        word = word.Right(word.Len()-1);
    }

    // Check first quotation!
    if (FirstChar.IsSameAs(_T("\""),FALSE)) {
        word = word.Right(word.Len()-1);
    }

    // Check first single quotation!
    if (FirstChar.IsSameAs(_T("'"),FALSE)) {
        word = word.Right(word.Len()-1);
    }

    // Check first exclamation mark!
    if (FirstChar.IsSameAs(_T("!"),FALSE)) {
        word = word.Right(word.Len()-1);
    }

    // Check first comma!
    if (FirstChar.IsSameAs(_T("?"),FALSE)) {
        word = word.Right(word.Len()-1);
    }

    // Check first star!
    if (FirstChar.IsSameAs(_T("*"),FALSE)) {
        word = word.Right(word.Len()-1);
    }

    // Check last 's!
    if (word.Right(2) == _T("'s")) {
        return word.Left(word.Len()-2);
    }
    
    // Check for Last ied
    if (word.Right(3) == _T("ied")) {
        return word.Left(word.Len()-3)+_T("y");
    }

    // Check for Last ies
    if (word.Right(3) == _T("ies")) {
        return word.Left(word.Len()-3)+_T("y");
    }

    // Check for Last ying
    if (word.Right(4) == _T("ying")) {
        return word.Left(word.Len()-3);
    }

    // Check for Last ning
    if (word.Right(4) == _T("ning") && (wordList.Index(word,FALSE) == wxNOT_FOUND)) {
        if (wordList.Index(word.Left(word.Len()-4),FALSE) != wxNOT_FOUND) {
            return word.Left(word.Len()-4);
        }
    }

    // Check for Last zation
    if (word.Right(6) == _T("zation") && (wordList.Index(word,FALSE) == wxNOT_FOUND)) {
        if (wordList.Index(word.Left(word.Len()-5)+_T("e"),FALSE) != wxNOT_FOUND) {
            return word.Left(word.Len()-5)+_T("e");
        }
    }

    // Check for Last ment
    if (word.Right(4) == _T("ment") && (wordList.Index(word,FALSE) == wxNOT_FOUND)) {
        if (wordList.Index(word.Left(word.Len()-4),FALSE) != wxNOT_FOUND) {
            return word.Left(word.Len()-4);
        }
    }

    // Check for Last ing
    if (word.Right(3) == _T("ing") && (wordList.Index(word,FALSE) == wxNOT_FOUND)) {
        if (wordList.Index(word.Left(word.Len()-3)+_T("e"),FALSE) != wxNOT_FOUND) {
            return word.Left(word.Len()-3)+_T("e");
        } else {
            return word.Left(word.Len()-3);
        }
    }

    // Check for Last s
    if (word.Right(1) == _T("s") && (wordList.Index(word,FALSE) == wxNOT_FOUND) && 
        (wordList.Index(word.Left(word.Len()-1),FALSE) != wxNOT_FOUND)) {
        return word.Left(word.Len()-1);
    }

    // Check for Last ly
    if (word.Right(2) == _T("ly") && (wordList.Index(word,FALSE) == wxNOT_FOUND) && 
        (wordList.Index(word.Left(word.Len()-2),FALSE) != wxNOT_FOUND)) {
        return word.Left(word.Len()-2);
    }

    // Check for Last ed
    if (word.Right(2) == _T("ed")) {
        if (wordList.Index(word.Left(word.Len()-2),FALSE) != wxNOT_FOUND) {
            return word.Left(word.Len()-2);
        } else {
            return word.Left(word.Len()-1);
        }
    }

    // Check for Last es
    if (word.Right(2) == _T("es") && (wordList.Index(word,FALSE) == wxNOT_FOUND) && 
        (wordList.Index(word.Left(word.Len()-2),FALSE) != wxNOT_FOUND)) {
        return word.Left(word.Len()-2);        
    }

    // Check for Last er
    if (word.Right(2) == _T("er") && (wordList.Index(word,FALSE) == wxNOT_FOUND) && 
        (wordList.Index(word.Left(word.Len()-2),FALSE) != wxNOT_FOUND)) {
        return word.Left(word.Len()-2);
    }

    return word;
}

void xFarDicApp::LoadLeitnerBox()
{
    wxString tmpstr, ltboxstr; 
    wxArrayInt position;

    //Get Configuration From Config File
    wxConfigBase *pConfig = wxConfigBase::Get();

    pConfig->SetPath(wxT("/Options"));

    ltboxstr = pConfig->Read(_T("LTBOX-A"), _T(""));
   
    ltboxstr = ltboxstr.Trim(TRUE);
    ltboxstr = ltboxstr.Trim(FALSE);  

    position.Empty();
 
    if (ltboxstr.Len() > 0) {
        for (int x=1; x <= ltboxstr.Len(); x++) {    
            Part = ltboxstr.GetChar(x);
            if (Part.CmpNoCase(_T(";"))==0) {
                position.Add(x);        
            }
        } // End For
    }

    if (position.GetCount()>0) {    
        for (int x=0; x <= position.GetCount(); x++) {
            if (x == 0) {
                tmpstr = ltboxstr.Mid(0,position[x]);
                if (tmpstr.Len()!=0) {
                    ltbox.Add(ltboxstr.Mid(0,position[x]));
                }
            } else if (x == position.GetCount()) {
                tmpstr = ltboxstr.Mid(position[x-1]+1,ltboxstr.Len());
                if (tmpstr.Len()!=0) {
                    ltbox.Add(ltboxstr.Mid(position[x-1]+1,ltboxstr.Len()));
                }
            } else {
                tmpstr = ltboxstr.Mid(position[x-1]+1,position[x]-position[x-1]-1);
                if (tmpstr.Len()!=0) {
                    ltbox.Add(ltboxstr.Mid(position[x-1]+1,position[x]-position[x-1]-1));
                }
            }
        }         
    } else if (ltboxstr.Len() > 0) {
        ltbox.Add(ltboxstr);
    }
}

void xFarDicApp::OnLeitnerBox(wxCommandEvent& event)
{
    AddToLeitnerBox();
}

void xFarDicApp::AddToLeitnerBox()
{
    wxString tmpstr, att, msg;    

    //Get Configuration From Config File
    wxConfigBase *pConfig = wxConfigBase::Get();

    pConfig->SetPath(wxT("/Options"));

    ltbaselimit = pConfig->Read(_T("Leitner-Base"), 10);

    if (ltbox.GetCount() < ltbaselimit) {
        if (ltbox.Index(m_text->GetValue(),FALSE) == wxNOT_FOUND && 
            wordList.Index(m_text->GetValue(),FALSE) != wxNOT_FOUND) {
            ltbox.Add(m_text->GetValue());
        } else {
            msg.Printf( _("Selected word already exists in the box\nor not found in the installed database(s).\n"));
            wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
            m_text->SetFocus();
            return;
        }
    } else {
        msg.Printf( _("The leitner box is full.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        m_text->SetFocus();
        return;
    }
    
    if (ltbox.GetCount()>0) {          
        for (int x=0; x < ltbox.GetCount(); x++) {
            if (tmpstr.Len()==0) {
                att = _T(";");
            }
            if (x+1 < ltbox.GetCount()) {
                tmpstr = tmpstr + ltbox[x] + att;
            } else {
                tmpstr = tmpstr + ltbox[x];
            }
        }
    }

    pConfig->Write(wxT("/Options/LTBOX-A"), tmpstr);

    m_text->SetFocus();

    if (!showLeitner) {
         ltframe->UpdateBoxes(TRUE);
    }
}

bool xFarDicApp::initSwap()
{
    // SWAP file implementation
    int returnvalue;
    wxString swappath, initsql; 
    wxFile swapfile;
    update = FALSE;

    swappath = wxGetHomeDir()+wxT("/.xfardic.swap");

    if (!swapfile.Exists(swappath) && swap) {
            update = TRUE;
    }   

    returnvalue = sqlite3_open((const char *)swappath.mb_str(wxConvUTF8),&Db);

    // DEBUGGING
    if (returnvalue) {
        //fprintf(stderr, "Could not open the swap database: %s.\n", sqlite3_errmsg(Db));
        sqlite3_close(Db);
    }

    if (update || swapupdate) {
         UpdateSwap();
    }     
}

bool xFarDicApp::UpdateSwap()
{
    // SWAP file implementation
    int returnvalue;
    wxString swappath, initsql, tmpIn, tmpOut;    
    wxFile swapfile;   

    wxProgressDialog *prog; 

    swappath = wxGetHomeDir()+wxT("/.xfardic.swap");

    if (swapfile.Exists(swappath)) {
        wxRemoveFile(swappath);
    }    

    // Disabling update-swap flag
    wxConfigBase *pConfig = wxConfigBase::Get();
    pConfig->SetPath(wxT("/Options"));
    pConfig->Write(wxT("/Options/Swap-Update"), 0);
    swapupdate = FALSE;

    returnvalue = sqlite3_open((const char *)swappath.mb_str(wxConvUTF8),&Db);

    if (returnvalue) {
        //fprintf(stderr, "Could not open the swap database: %s.\n", sqlite3_errmsg(Db));
        sqlite3_close(Db);
    }

    initsql = wxT("DROP TABLE words");

    returnvalue = sqlite3_exec(Db, (const char *)initsql.mb_str(wxConvUTF8), NULL, NULL, &db_error_msg);

    // DEBUGGING
    /*if (returnvalue != SQLITE_OK) {
          fprintf(stderr, "SQL statement: %s FAILED\nREASON: %s\n", (const char *)initsql.mb_str(wxConvUTF8), db_error_msg);             
    }*/

    initsql = wxT("CREATE TABLE words(inw TEXT, outw TEXT)");

    returnvalue = sqlite3_exec(Db, (const char *)initsql.mb_str(wxConvUTF8), NULL, NULL, &db_error_msg);

    // DEBUGGING
    /*if (returnvalue != SQLITE_OK) {
    fprintf(stderr, "SQL statement: %s FAILED\nREASON: %s\n", (const char *)initsql.mb_str(wxConvUTF8), db_error_msg);             
    }*/

    prog = new wxProgressDialog(_T("xFarDic - Creating Swap..."), 
                                _("Creating the swap file. Please wait.\nThis will take a while..."),
                                wordList.GetCount(), this, wxPD_APP_MODAL | wxPD_AUTO_HIDE | wxPD_SMOOTH |
                                wxPD_REMAINING_TIME);

    for (int x=0; x < wordList.Count(); x++) {
        tmpIn = wordList.Item(x);
        tmpOut = meanList.Item(x);

        if (tmpIn.Len() != 0 && tmpOut.Len() !=  0) {
            tmpIn.Replace(wxT("'"),wxT("''"),TRUE);
            tmpOut.Replace(wxT("'"),wxT("''"),TRUE);

            initsql = wxT("INSERT INTO words (inw, outw) VALUES ('")+tmpIn+wxT("','")+tmpOut+wxT("')");
            returnvalue = sqlite3_exec(Db, (const char *)initsql.mb_str(wxConvUTF8), NULL, NULL, &db_error_msg);  
        }

        if (x % 500  == 0) {
            prog->Update(x);
        } 
    }

    // Killing progress dialog
    delete prog;

    // Emptying meanings list after update
    if (meanList.GetCount() > 0) {
        meanList.Empty();  
    }

    // Shrinking the swap file
    initsql = wxT("VACUUM");
    returnvalue = sqlite3_exec(Db, (const char *)initsql.mb_str(wxConvUTF8), NULL, NULL, &db_error_msg);  

    // DEBUGGING
    //fprintf(stderr, "Finished swap file update/create\n");  

    return TRUE;    
}

void xFarDicApp::LoadLeitnerBoxContents()
{
    wxString tmpstr, ltboxstr, Part;
    wxArrayInt position;
   
    //Get Configuration From Config File
    wxConfigBase *pConfig = wxConfigBase::Get();

    pConfig->SetPath(wxT("/Options"));

    ltboxstr = pConfig->Read(_T("LTBOX-A"), _T(""));
   
    ltboxstr = ltboxstr.Trim(TRUE);
    ltboxstr = ltboxstr.Trim(FALSE);
 
    position.Empty();
 
    if (ltboxstr.Len() > 0) {
        for (int x=1; x <= ltboxstr.Len(); x++) {    
            Part = ltboxstr.GetChar(x);
            if (Part.CmpNoCase(_T(";"))==0) {
                position.Add(x);        
            }
        } // End For
    }

    ltbox.Empty();

    if (position.GetCount()>0) {    
        
        for (int x=0; x <= position.GetCount(); x++) {
            if (x == 0) {
                tmpstr = ltboxstr.Mid(0,position[x]);
                if (tmpstr.Len()!=0) {
                    ltbox.Add(ltboxstr.Mid(0,position[x]));
                }
            } else if (x == position.GetCount()) {
                tmpstr = ltboxstr.Mid(position[x-1]+1,ltboxstr.Len());
                if (tmpstr.Len()!=0) {
                    ltbox.Add(ltboxstr.Mid(position[x-1]+1,ltboxstr.Len()));
                }
            } else {
                tmpstr = ltboxstr.Mid(position[x-1]+1,position[x]-position[x-1]-1);
                if (tmpstr.Len()!=0) {
                    ltbox.Add(ltboxstr.Mid(position[x-1]+1,position[x]-position[x-1]-1));
                }
            }
        }         
    } else if (ltboxstr.Len() > 0) {
        ltbox.Add(ltboxstr);
    }
}

void xFarDicApp::CreateLayout(bool fit) {
     wxBoxSizer *horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
     horizontalSizer->Add(m_text,
                    1, //make horizontally stretchable
                    wxALL, //make border all around
                    2); //set border width to 5
     horizontalSizer->Add(m_translate,
                    0, //make horizontally unstretchable
                    wxALL,
                    1);
     horizontalSizer->Add(m_leitnerbox,
                    0,
                    wxALL,
                    1);
     horizontalSizer->Add(m_ttos,
                    0,
                    wxALL,
                    1);
     wxBoxSizer *verticalSizer = new wxBoxSizer(wxVERTICAL);
     verticalSizer->Add(m_label,
               1, //make vertically stretchable
               wxEXPAND | //make horizontally stretchable
               wxALL,
               1);
     wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
     topSizer->Add(horizontalSizer,
               0, //make vertically unstretchable
               wxEXPAND|wxALL);
     topSizer->Add(verticalSizer, 1, wxEXPAND|wxALL, 1);
     SetSizer(topSizer);

     if (fit) {
         topSizer->Fit(this);
         topSizer->SetSizeHints(this);
     }
}

void xFarDicApp::OnTexttoSpeech(wxCommandEvent &event) {
#ifdef HAVE_SPEAKLIB    
    pron->Pronounce(m_text->GetValue());
#endif
}



