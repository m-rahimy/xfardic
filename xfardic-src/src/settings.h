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

#ifndef __SETTINGS_H
#define __SETTINGS_H

#include "xfardic.h"

/// xFarDic Settings Window Class
class xFarDicSettings : public wxFrame
{
public:
    // ctor(s)
    xFarDicSettings(wxWindow *parent, const wxString& title, const wxPoint& pos, const wxSize& size, wxLocale& m_locale,
            long style = wxDEFAULT_FRAME_STYLE);

    // event handlers (these functions should _not_ be virtual)
    /// OK button process handler
    void OnOK(wxCommandEvent& event);  
    /// Apply button process handler
    void OnApply(wxCommandEvent& event); 
    /// Cancel button process handler
    void OnCancel(wxCommandEvent& event);
    /// Add DBs 
    void OnSetDB(wxCommandEvent& event); 
    /// Return DB info
    void OnDBinfo(wxCommandEvent& event);
    /// Delete button event handler
    void OnDelete(wxCommandEvent& event); 
    /// Up button event handler
    void OnUp(wxCommandEvent& event);  
    /// Down button event handler
    void OnDown(wxCommandEvent& event);  
    /// Select check box event handler
    void OnChkSelect(wxCommandEvent& event); 
    /// Win-Pos check box event handler
    void OnChkWinPos(wxCommandEvent& event);
    /// History check box event handler 
    void OnChkCache(wxCommandEvent& event); 
    /// Spin controls event handler
    void EnableSpApply(wxSpinEvent& event); 
    /// Enables Apply button
    void EnableApply(wxCommandEvent& event);
    /// Enables Apply & TTS check box
    void EnableTTS(wxCommandEvent& event);
    /// Process path update event
    void OnPathUpdate(wxCommandEvent& event);  
    /// Checks XML DB validation
    bool DB(const char *filename);
    /// Submits configuration changes to the config file
    void SubmitChanges();
    /// Checks DB path
    bool CheckPath(wxString dbpath);
    
    bool exist,
         submit,
         swapupdate;
    /// constructor
    ~xFarDicSettings();    

    wxLocale& m_locale;

private:
    void CreateLayout();

    bool db_sort_order;    

    wxStaticBitmap *settingsBitmap,
                   *notelogoBitmap1,
                   *notelogoBitmap2;

    wxStaticText *effecttext,
                 *langtext,
                 *acnttext,
                 *settext,
                 *timeouttext,
                 *leitnertext,
                 *dbtext,
                 *dbnote,
                 *swapnote;

    wxButton    *m_ok,
                *m_apply,
                *m_cancel,
                *dbinfo,
                *dbdir,
                *dbdel,
                *sort_up,
                *sort_down;

    wxPanel     *setpanel,
                *dbpanel;
    wxCheckBox  *chk_select,
                *chk_winpos,
                *chk_cache,
                *chk_srchsim,
                *chk_spell,
                *chk_watcher,
                *chk_hide,
                *chk_revsrch,
                *chk_scanner,
                *chk_swap,
                *chk_speak,
                *chk_tts,
                *chk_notify;

    wxChoice    *lang,
                *accent;

    wxArrayString langlist,
                  acntlist,
                  dbs,
                  dbstatus;

    wxSpinCtrl    *numEntry,
                  *scantimeout,
                  *leitner;
    
    wxCheckListBox     *dbpath;

    wxString      strSel,
                  dbname,
                  author,
                  inputlang,
                  version,
                  tmppath,
                  ItemString;

    xmlTextReaderPtr reader;
    wxArrayInt       seppos;
    wxNotebook       *layout;

    DECLARE_EVENT_TABLE()
};

#endif

