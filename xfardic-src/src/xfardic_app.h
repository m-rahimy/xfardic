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

#ifndef __XFARDIC_APP_H
#define __XFARDIC_APP_H

#include "xfardic.h"
#include "about.h"
#include "settings.h"
#include "selection.h"
#include "leitner.h"

#ifdef HAVE_SPEAKLIB
#include "pronounce.h"
#endif

/// xFarDic Application Main Class
class xFarDicApp : public wxFrame
{
public:
    /// Main App startup function
    xFarDicApp(const wxString& title, const wxPoint& pos, const wxSize& size, wxLocale& m_locale,
            long style = wxDEFAULT_FRAME_STYLE, bool fit = TRUE);

    /// Quits Event Handler
    void OnQuit(wxCommandEvent& event);
    /// Process Close Event 
    void OnClose(wxCloseEvent& event); 
    /// Process Open About Dialog
    void OnAbout(wxCommandEvent& event); 
    /// Process Open Leitner Dialog
    void OnLeitner(wxCommandEvent& event); 
    /// Shows About dialog
    void ShowAbout(); 
    /// Shows Leitner dialog
    void ShowLeitner(); 
    /// Navigate: Previous word
    void OnBack(wxCommandEvent& event); 
    /// Navigate: Next word
    void OnForward(wxCommandEvent& event); 
    /// Navigate: First word
    void OnFirst(wxCommandEvent& event);
    /// Navigate: Last word 
    void OnLast(wxCommandEvent& event); 
    /// Translate Button/Menu Event handler
    void OnTranslate(wxCommandEvent& event); 
    /// Leitner button Event handler
    void OnLeitnerBox(wxCommandEvent& event);
    /// Text to Speech button Event handler
    void OnTexttoSpeech(wxCommandEvent &event);
    /// Selecting "Select" option 
    void OnSelect(wxCommandEvent& event); 
    /// Selecting "Search Similar" option
    void OnSrch(wxCommandEvent& event); 
    /// Selecting "Spell check" option
    void OnSpell(wxCommandEvent& event); 
    /// Selecting "Enable notification" option
    void OnNotification(wxCommandEvent& event); 
    /// Selecting "Reverse Search" option
    void OnRevSrch(wxCommandEvent& event); 
    /// Clipboard watcher caller
    void OnWatcher(wxCommandEvent& event); 
    /// Selection scanner caller
    void OnScanner(wxCommandEvent& event); 
    /// Hides/Unhides main window option
    void OnHide(wxCommandEvent& event);
    /// Process Open Settings dialog
    void OnSettings(wxCommandEvent& event); 
    /// Shows settings dialog
    void ShowSettings(); 
    /// Populates Spelling suggestion list
    wxString ShowAspell(wxArrayString sugList); 
    /// Copies result to clipboard
    void OnCopy(wxCommandEvent& event);
    /// Cuts input box content 
    void OnCut(wxCommandEvent& event); 
    /// Pastes to input box process handler
    void OnPaste(wxCommandEvent& event); 
    /// Does paste!
    void DoPaste(); 
    /// Quits from xFarDic
    void DoQuit();
    // Do Translate
    void DoTranslate(); 
    /// Clipboard watcher main function
    void Watcher(wxTimerEvent& event); 
    /// Deletes history
    void OnTrash(wxCommandEvent& event); 
    /// Process Set font event
    void OnSetFont(wxCommandEvent& event); 
    /// Shows set font dialog
    void ShowSetFont(); 
    /// Shows/Hides toolbar      
    void ViewToolbar(wxCommandEvent& event);  
    /// Core translation function
    bool Translate(wxString m_textVal = _T(""), bool atrans=FALSE, bool notify=FALSE); 
    /// Word spelling function
    bool CheckSpell(wxString chkStr, bool suggest); 
    /// Auto-Translation process handler  
    void AutoTrans(wxCommandEvent& event); 
    /// Focus event handler
    void OnFocus(wxFocusEvent& event); 
    /// Focus event handler
    void OnActivate(wxActivateEvent& event); 
    /// Auto translation function  
    void DoAutoTrans();  
    /// Taskbar popup menu
    void PopMenu(); 
    /// Do OnSpell
    void DoOnSpell(); 
    /// Do OnRevSrch
    void DoOnRevSrch(); 
    /// Hides window
    void Hide(wxIconizeEvent &event); 
    /// Load XML DBs
    bool initDB(const char *filename); 
    /// Init swap file
    bool initSwap();
    /// Update swap file
    bool UpdateSwap();      
    /// Create toolbar function
    void RecreateToolbar(bool activate=TRUE); 
    /// Create translation toolbar function
    void RecreateTrToolbar(); 
    /// Shows desktop notifications
    bool ShowNotification(wxString word, wxString meaning);
    /// Processes input word and returned pure word
    wxString ProcessWord(wxString word);
    /// Updates ltbox contents from config file
    void LoadLeitnerBoxContents(wxString configpath);
    /// Add word to the leitner box
    void AddToLeitnerBox();

    wxLocale& m_locale;
    bool             hide,
                     swapupdate;
    wxComboBox       *m_text;
    xFarDicAbout     *abframe;
    xFarDicSettings  *setframe;
    xFarDicLeitner   *ltframe;

private:
    void CreateLayout(bool fit=TRUE);

    wxTextCtrl       *m_label;
    wxBitmapButton   *m_translate,
                     *m_leitnerbox,
                     *m_ttos;
    //wxPanel *panel;
    bool    m_smallToolbar,
            m_horzToolbar,
            select,
            srch,
            cache,
            spell,
            watcher,
            scanner,
            speak,
            tts,
            vtool,    
            found,
            revsrch,
            aspelli,
            swap,
            update,
            notification;

    size_t  m_rows;

    wxMenu  *gomenu,
            *opmenu,
            *vimenu,
            *edmenu,
            *helpMenu,
            *menuFile,
            *toolsMenu;

    wxMenuBar        *menuBar;

#ifdef HAVE_SPEAKLIB
    xFarDicPronounce *pron;
#endif
     
    wxFont           m_font;
    wxFontData       retData;
    wxTaskBarIcon    ticon;
    wxArrayString    sugList,
                     wordList,
                     meanList,
                     paths,
                     statuses,
                     ltbox,
                     ltboxa;
    wxString         watcher_now, 
                     watcher_last,
                     scanner_now,
                     scanner_last,
                     inputlang, 
                     path,
                     status,
                     tmppath,
                     tmpstr;

    wxTimer          m_timer;  
    xmlTextReaderPtr reader;
    wxArrayInt       seppos;
    wxSplashScreen   *splash;
    int              ltbaselimit,
                     array_items,
                     entryq;
    
    //Swapfile handle
    sqlite3          *Db;
    char             *db_error_msg;

    //Notification!
    NotifyNotification *n;  

    //Selection System
    Selection oSelection;  
          
    DECLARE_EVENT_TABLE()
};

#endif

