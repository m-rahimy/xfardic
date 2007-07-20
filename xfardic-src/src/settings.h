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
     wxStaticBitmap *settingsBitmap;
     wxStaticText *effecttext;
     wxStaticText *langtext;
     wxStaticText *settext;
     wxStaticText *timeouttext;
     wxStaticText *leitnertext;
     wxStaticText *dbtext;
     wxStaticText *dbnote;
     wxStaticText *swapnote;
     wxStaticBitmap *notelogoBitmap1;
     wxStaticBitmap *notelogoBitmap2;

private:
    // any class wishing to process wxWindows events must use this macro
    wxButton    *m_ok;
    wxButton    *m_apply;
    wxButton    *m_cancel;
    wxStaticBox *m_setbox;
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
                *chk_swap;

    wxChoice      *lang;
    wxArrayString langlist;
    wxSpinCtrl    *numEntry,
                  *scantimeout,
                  *leitner;

    wxButton      *dbinfo;
    wxButton      *dbdir;
    wxListBox     *dbpath;
    wxString      strSel;
    wxString      dbname;
    wxString      author;
    wxString      inputlang;
    wxString      version, tmppath; 

    xmlTextReaderPtr reader;
    wxArrayString    dbs;
    wxArrayInt       dbcount, seppos;
    wxNotebook       *layout;

    DECLARE_EVENT_TABLE()
};

#endif

