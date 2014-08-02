// +-------------------------------------------------------------------------+
// | xFarDic Multilingual Dictionary                                         |
// | Copyright (C) 2004-2011 by the xFarDic Development Team.                |
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

/* xFarDic Logo 24x24 */
const char* xfardic24x24[] = {
"21 24 111 2",
"  	c None",
". 	c #000000",
"+ 	c #3F3F3F",
"@ 	c #343434",
"# 	c #1E1E1E",
"$ 	c #9C9C9C",
"% 	c #FEFEFE",
"& 	c #F5F5F5",
"* 	c #676767",
"= 	c #333333",
"- 	c #929292",
"; 	c #A8A8A8",
"> 	c #353535",
", 	c #474743",
"' 	c #FFFFFF",
") 	c #FAFAFA",
"! 	c #3E3D3A",
"~ 	c #949494",
"{ 	c #ABABA7",
"] 	c #3E3C1F",
"^ 	c #B1B0AB",
"/ 	c #B6B6B3",
"( 	c #242311",
"_ 	c #383838",
": 	c #E7E7E7",
"< 	c #7B7843",
"[ 	c #898544",
"} 	c #ECECEC",
"| 	c #F7F7F7",
"1 	c #565434",
"2 	c #525252",
"3 	c #78765F",
"4 	c #F2EB5B",
"5 	c #777443",
"6 	c #787651",
"7 	c #45431A",
"8 	c #585858",
"9 	c #EFEFEF",
"0 	c #F4F4F4",
"a 	c #7B7845",
"b 	c #FFF860",
"c 	c #777448",
"d 	c #A6A6A6",
"e 	c #78765A",
"f 	c #999539",
"g 	c #5D5D5D",
"h 	c #767676",
"i 	c #7E7D7B",
"j 	c #B6B149",
"k 	c #817E42",
"l 	c #F6F6F6",
"m 	c #FCFCFC",
"n 	c #3D3D3D",
"o 	c #7A7857",
"p 	c #F4ED5B",
"q 	c #323113",
"r 	c #DADADA",
"s 	c #73725E",
"t 	c #F6EF5C",
"u 	c #AEA947",
"v 	c #CBCBCB",
"w 	c #F2F2F2",
"x 	c #7C7A53",
"y 	c #403E18",
"z 	c #393939",
"A 	c #FBFBFB",
"B 	c #7A785E",
"C 	c #E8E157",
"D 	c #82816E",
"E 	c #7C794A",
"F 	c #504E1E",
"G 	c #A0A0A0",
"H 	c #7D7B62",
"I 	c #7C7943",
"J 	c #EAEAEA",
"K 	c #9D9C8E",
"L 	c #D3CD51",
"M 	c #5D5B23",
"N 	c #404040",
"O 	c #8D8D80",
"P 	c #E2DB55",
"Q 	c #656450",
"R 	c #F1F1F1",
"S 	c #7C7947",
"T 	c #615E24",
"U 	c #373737",
"V 	c #8A873C",
"W 	c #E7E056",
"X 	c #6F6D42",
"Y 	c #7E7C66",
"Z 	c #6C6A4A",
"` 	c #E5DE56",
" .	c #565420",
"..	c #343213",
"+.	c #EFE859",
"@.	c #49471B",
"#.	c #393715",
"$.	c #6F6C29",
"%.	c #FEF75F",
"&.	c #F3EC5B",
"*.	c #2C2B10",
"=.	c #575420",
"-.	c #F7F05C",
";.	c #898533",
">.	c #424018",
",.	c #FBF45E",
"'.	c #CBC64C",
").	c #373614",
"!.	c #5E5C23",
"~.	c #5A5822",
"{.	c #2D2B10",
"                    . . .                 ",
"                .                         ",
"                                          ",
"        .                                 ",
"        .                                 ",
". .     .                   + @           ",
"                        # $ % & *         ",
"              = - ; >   , ' ' ' ) !       ",
"              ~ ' ' { ] ^ ' ' ' ' / (     ",
"            _ ) ' : < [ } ' ' ' ' | 1     ",
"            2 ' ' 3 4 5 ' ' ' ' ' ' 6 7   ",
"            8 9 0 a b c ' ' d % ' ' e f   ",
"            g h i j b k l m n 9 ' ' o p q ",
"            2 r s t b u v ' w ' ' ' x b y ",
"            z A B b b C D ' ' ' ' m E b F ",
"              G H b b b I J ' ' ' K L b M ",
"              N O P b b C Q R ' 0 S b b T ",
"                U V b b b W X Y Z ` b b  .",
"                  ..+.b b b b b b b b b @.",
"                    M b b b b b b b b b #.",
"                      $.%.b b b b b b &.*.",
"                        =.-.b b b b b ;.  ",
"                          >.f ,.b b '.).  ",
"                              y !.~.{.    "};
// This is a global wxString which is used as watcher/scanner
// system entry. 
wxString GlobalStr;

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

    // restore frame position & state
    int x = pConfig->Read(_T("x"), 0l);
    int y = pConfig->Read(_T("y"), 0l);
    int w = pConfig->Read(_T("w"), 0l);
    int h = pConfig->Read(_T("h"), 0l);
    bool maximized = pConfig->Read(_T("IsMaximized"), 0l);

    // create the main application window
    if (h > 0 && w > 0) {
         frame = new xFarDicApp(_T("xFarDic ")XVERSION, wxPoint(x,y), wxSize(w,h), m_locale,
                       wxDEFAULT_FRAME_STYLE, FALSE);
    } else {
         frame = new xFarDicApp(_T("xFarDic ")XVERSION, wxPoint(x,y), wxDefaultSize, m_locale,
                       wxDEFAULT_FRAME_STYLE, TRUE);
    }

    // Set minimum allowed size
    frame->SetMinSize(wxSize(509, 294));

    //DEBUGGING
    //fprintf(stderr, "Frame Started\n");    
                 
    if (x == 0 && y == 0) {
        frame->Centre();
    }

    if (maximized) {
        frame->Maximize();
    }

    // translate sent argument or first cached word
    int saved = pConfig->Read(_T("Save-Cache"), 1);

    if (Param.Len() != 0 && frame->CheckSpell(Param,0)) {
        GlobalStr = Param;
    } else {
        if (saved != 0) {
            wxString str;
            long dummy;
            pConfig->SetPath(wxT("/Cache"));
            bool bCont = pConfig->GetFirstEntry(str, dummy);
            if (bCont && !frame->swapupdate) {
                frame->Translate();
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
            if (!showLeitner) {
               frame->ltframe->Show(TRUE);
            }
            if (!showAbout) {
               frame->abframe->Show(TRUE);
            }
            if (!showSettings) {
               frame->setframe->Show(TRUE);
            }
        }
        frame->Raise();
        frame->SetFocus();                                                                                    
    } else {
        if (frame->hide) {
            frame->Show(FALSE);
            if (!showLeitner) {
               frame->ltframe->Show(FALSE);
            }
            if (!showAbout) {
               frame->abframe->Show(FALSE);
            }
            if (!showSettings) {
               frame->setframe->Show(FALSE);
            }
        }else {
            frame->Iconize();
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

