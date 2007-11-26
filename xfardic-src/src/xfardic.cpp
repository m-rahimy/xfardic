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

#include "my_app.h"

// Create a new application object: this macro will allow wxWindows to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also declares the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)

IMPLEMENT_APP(MyApp)

BEGIN_EVENT_TABLE(MyApp, wxApp)
    EVT_TASKBAR_RIGHT_UP(MyApp::OnTaskRightDown)
    EVT_TASKBAR_LEFT_UP(MyApp::OnTaskLeftDown)
    EVT_MENU(xFarDic_QApp,  MyApp::OnQuit)    
    EVT_MENU(xFarDic_Paste,  MyApp::OnPaste)    
    EVT_MENU(xFarDic_About,  MyApp::OnAbout)    
    EVT_MENU(xFarDic_Settings,  MyApp::OnSettings)    
    EVT_MENU(xFarDic_Setfont,  MyApp::OnSetFont)    
END_EVENT_TABLE()

/// 'Main program' equivalent: the program execution "starts" here
bool MyApp::OnInit()
{
    // Disabling wxLog
    wxLogNull logNo;

    wxString logo, Param;

    // Command line argument
    static const wxCmdLineEntryDesc cmdLineDesc[] =
    {
        { wxCMD_LINE_SWITCH, _T("h"), _T("help"), _("displays this help message"), wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },
        { wxCMD_LINE_PARAM, NULL, NULL, wxT("word"), wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },
        { wxCMD_LINE_NONE }
    };
    wxCmdLineParser parser(cmdLineDesc, wxApp::argc, wxApp::argv);
    logo.Printf(wxT("xFarDic %s (C)2004-2007 Alan Baghumian, Armen Baghumian\nxFarDic is free software released under the GPL.\n"),
          XVERSION);
    parser.SetLogo(logo);
    
    if (parser.Parse()) {
        return FALSE;
    }

    Param = parser.GetParam(0);
    
    // DEBUGGING
    // fprintf(stderr, "%s\n", (const char *)Param.mb_str(wxConvUTF8));
    // End Command line argument

    wxString xapp = wxString::Format(wxT("xFarDic"), wxGetUserId().c_str());
    m_checker = new wxSingleInstanceChecker(xapp);
    if (m_checker->IsAnotherRunning()) {
        wxString msg;
        msg.Printf( _("Another program instance is already running, aborting."));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_EXCLAMATION, 0);
        return FALSE;
    }

    wxImage::AddHandler(new wxPNGHandler);

    wxConfigBase *pConfig = wxConfigBase::Get();

    // note that it makes no sense to translate these strings, they are
    // shown before we set the locale anyhow
    const wxString langNames[] =
    {
        _T("Farsi"),
        _T("English (U.S.)"),
        _T("System default"),
        //_T("Azeri")
    };

    static const wxLanguage langIds[] =
    {
        wxLANGUAGE_FARSI,
        wxLANGUAGE_ENGLISH,
        wxLANGUAGE_DEFAULT,
        //wxLANGUAGE_AZERI_LATIN
    };

    // the arrays should be in sync
    wxCOMPILE_TIME_ASSERT( WXSIZEOF(langNames) == WXSIZEOF(langIds),
                           LangArraysMismatch );

    pConfig->SetPath(wxT("/Options"));
    m_locale.Init(langIds[pConfig->Read(_T("GUI-Lang"), 2)]);  
    
    // m_locale.Init(langIds[1]);

    // Initialize the catalogs we'll be using
    m_locale.AddCatalogLookupPathPrefix(wxT("/usr/share/locale/"));
    m_locale.AddCatalogLookupPathPrefix(wxT("/usr/local/share/locale/"));
    m_locale.AddCatalog(_T("xfardic"));

    // this catalog is installed in standard location on Linux systems and
    // shows that you may make use of the standard message catalogs as well
    //
    // if it's not installed on your system, it is just silently ignored
    wxLogNull noLog;
    m_locale.AddCatalog(_T("fileutils"));

    //DEBUGGING
    //fprintf(stderr, "Going to starting Frame\n");    

    // create the main application window
    frame = new xFarDicApp(_T("xFarDic ")XVERSION, wxDefaultPosition, wxDefaultSize, m_locale,
                           wxDEFAULT_FRAME_STYLE);

    //DEBUGGING
    //fprintf(stderr, "Frame Started\n");    
               
    // uncomment this to force writing back of the defaults for all values
    // if they're not present in the config - this can give the user an idea
    // of all possible settings for this program
    // pConfig->SetRecordDefaults();

    // restore frame position
    int x = pConfig->Read(_T("x"), 0l);
    int y = pConfig->Read(_T("y"), 0l);
    int saved = pConfig->Read(_T("Save-Cache"), 1);    

    if (x == 0 && y ==0) {
        frame->Centre();
    }

    // translate sent argument or first cached word

    if (Param.Len() != 0 && frame->CheckSpell(Param,0)) {
        pConfig->Write(wxT("/Options/Temp-String"), Param);
    } else {
        if (saved != 0) {
            wxString str;
            long dummy;
            pConfig->SetPath(wxT("/Cache"));
            bool bCont = pConfig->GetFirstEntry(str, dummy);
            if (bCont) {
                frame->translate();
            }
        }
    } 

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
      
    frame->Show(TRUE);
    
    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned FALSE here, the
    // application would exit immediately.
    
    // DEBUGGING
    //fprintf(stderr, "Finished OnInit()\n");
    return TRUE;
}

/// Taskbar right-click event handler
void MyApp::OnTaskRightDown(wxTaskBarIconEvent& WXUNUSED(event))
{           
     frame->PopMenu();    
     //DEBUGGING
     //fprintf(stderr, "task right click\n");
}

/// Taskbar left-click event handler
void MyApp::OnTaskLeftDown(wxTaskBarIconEvent& WXUNUSED(event))
{

    if (frame->IsIconized()) {
        if (frame->hide) {
            frame->Show(TRUE);  
        } else {
            frame->Raise();
            frame->SetFocus();                                                                                    
        }
    } else {
        if (frame->hide) {
            frame->Show(FALSE);                                                                                       
        }        
    }                                     
    //DEBUGGING
    //fprintf(stderr, "task left click\n");
}

void MyApp::OnSetFont(wxCommandEvent& WXUNUSED(event))
{
    frame->Show(TRUE);
    frame->Raise();
    frame->SetFocus();
    frame->ShowSetFont();
}

void MyApp::OnSettings(wxCommandEvent& WXUNUSED(event))
{
    frame->Show(TRUE);
    frame->Raise();
    frame->SetFocus();
    frame->ShowSettings();
}

void MyApp::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    frame->Show(TRUE);        
    frame->Raise();
    frame->SetFocus();
    frame->ShowAbout();
}

void MyApp::OnPaste(wxCommandEvent& WXUNUSED(event))
{
  
    frame->Show(TRUE);
    frame->Raise();
    frame->SetFocus();
    frame->DoPaste();
}

void MyApp::OnQuit(wxCommandEvent& WXUNUSED(event))
{           
    frame->Destroy();  
    //DEBUGGING
    //fprintf(stderr, "Quit\n");
}

MyApp::~MyApp()
{
    // Delete execution Lock file
    delete m_checker;
}

