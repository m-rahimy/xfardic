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

#include "my_app.h"

/* xFarDic Logo 24x24 */
const char* xfardic24x24[] = {
"24 24 151 2",
"  	c None",
". 	c #000000",
"+ 	c #363636",
"@ 	c #3C3C3C",
"# 	c #303030",
"$ 	c #0C0C0C",
"% 	c #6F6F6F",
"& 	c #D3D3D3",
"* 	c #FFFFFF",
"= 	c #D8D8D8",
"- 	c #5C5C5C",
"; 	c #5A5A5A",
"> 	c #9C9C9C",
", 	c #A1A1A1",
"' 	c #313131",
") 	c #34342F",
"! 	c #BDBDBC",
"~ 	c #EBEAEA",
"{ 	c #3D3C3A",
"] 	c #6C6C6C",
"^ 	c #BBBBBB",
"/ 	c #F9F9F8",
"( 	c #AAAAA6",
"_ 	c #413F22",
": 	c #929186",
"< 	c #E9E8E8",
"[ 	c #F9F9F9",
"} 	c #B6B6B3",
"| 	c #343322",
"1 	c #A8A8A8",
"2 	c #FDFDFE",
"3 	c #DDDCD8",
"4 	c #7B7843",
"5 	c #827E3B",
"6 	c #D7D6C9",
"7 	c #FDFDFF",
"8 	c #F7F7F7",
"9 	c #646244",
"0 	c #AEAEAE",
"a 	c #E1E0DF",
"b 	c #7D7A57",
"c 	c #F2EB5B",
"d 	c #7C783C",
"e 	c #E0E0D8",
"f 	c #858361",
"g 	c #4D4A21",
"h 	c #424242",
"i 	c #A6A6A6",
"j 	c #D9D8D0",
"k 	c #817E3F",
"l 	c #FFF860",
"m 	c #7D7941",
"n 	c #E0E0D9",
"o 	c #CDCDCD",
"p 	c #BEBEBE",
"q 	c #828069",
"r 	c #908D3C",
"s 	c #585858",
"t 	c #696969",
"u 	c #78787B",
"v 	c #888671",
"w 	c #C0BA49",
"x 	c #86833C",
"y 	c #DBDAD0",
"z 	c #929292",
"A 	c #7F7E65",
"B 	c #E1DA59",
"C 	c #949135",
"D 	c #A2A2A4",
"E 	c #B9B9B7",
"F 	c #868455",
"G 	c #FEF65C",
"H 	c #B3AE43",
"I 	c #C0BFAC",
"J 	c #EFEFF4",
"K 	c #FBFBFB",
"L 	c #F6F6F6",
"M 	c #817F61",
"N 	c #EBE55D",
"O 	c #999537",
"P 	c #B1B1B3",
"Q 	c #D3D3CF",
"R 	c #8C8953",
"S 	c #FFFE60",
"T 	c #EFE857",
"U 	c #8D8B5F",
"V 	c #CFCFCE",
"W 	c #FCFCFC",
"X 	c #807E58",
"Y 	c #EBE55B",
"Z 	c #9E993A",
"` 	c #858688",
" .	c #91908D",
"..	c #95925E",
"+.	c #FFFE61",
"@.	c #8F8B3D",
"#.	c #BDBCAD",
"$.	c #FBFCFF",
"%.	c #9D9C8E",
"&.	c #CCC655",
"*.	c #FFFA5F",
"=.	c #9E993B",
"-.	c #59595A",
";.	c #A1A07B",
">.	c #E9E154",
",.	c #FFF961",
"'.	c #F6EE59",
").	c #878446",
"!.	c #A2A29F",
"~.	c #E8E8E5",
"{.	c #7C7947",
"].	c #F3EC5D",
"^.	c #FFFF64",
"/.	c #9D983B",
"(.	c #474637",
"_.	c #97933E",
":.	c #FFF960",
"<.	c #FFFA61",
"[.	c #F8F15B",
"}.	c #A9A449",
"|.	c #6C6B4E",
"1.	c #797763",
"2.	c #75734A",
"3.	c #E5DE56",
"4.	c #FEF75F",
"5.	c #989439",
"6.	c #47441A",
"7.	c #EFE859",
"8.	c #939037",
"9.	c #5D5A22",
"0.	c #F3EC5B",
"a.	c #FFFB61",
"b.	c #8E8A35",
"c.	c #646025",
"d.	c #E3DC55",
"e.	c #FFFD62",
"f.	c #FEF65F",
"g.	c #888332",
"h.	c #424018",
"i.	c #C2BD48",
"j.	c #FFFC61",
"k.	c #A39E3C",
"l.	c #2F2F11",
"m.	c #696626",
"n.	c #C0BB47",
"o.	c #D4CE4F",
"p.	c #5B5A22",
"q.	c #46451A",
"r.	c #5F5C23",
"s.	c #5A5722",
"t.	c #312F12",
"                                                ",
"                .                               ",
"            .       .                           ",
"            .               + @ #               ",
"  . . .     .           $ % & * = -             ",
"              ; > , '   ) ! * * * ~ {           ",
"            ] ^ * / ( _ : < * * * [ } |         ",
"            1 * 2 3 4 5 6 7 * * * * 8 9         ",
"            0 * a b c d e * * * * * * f g       ",
"          h i * j k l m n * o p * * * q r       ",
"          s t u v w l x y * z ] * * * A B C     ",
"            D E F G l H I J K L * * * M N O     ",
"            P Q R S l T U V * * * * W X Y Z     ",
"            `  ...S l +.@.#.$.* * L %.&.*.=.    ",
"              -.;.>.l ,.'.).!.* * ~.{.].^./.    ",
"                (._.l :.<.[.}.|.1.2.3.4.^.5.    ",
"                  6.7.l l l l l l l l l ^.8.    ",
"                    9.0.a.l l l l l l l ^.b.    ",
"                      c.d.e.l l l l l :.f.g.    ",
"                        h.i.j.:.l l l e.k.      ",
"                          l.m.n.a.:.l o.p.      ",
"                                q.r.s.t.        ",
"                                                ",
"                                                "};

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

