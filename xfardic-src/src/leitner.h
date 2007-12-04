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

#ifndef __LEITNER_H
#define __LEITNER_H

#include "xfardic.h"

class xFarDicApp;

/// xFarDic Leitner Dialog Class
class xFarDicLeitner : public wxFrame
{
public:
    /// ctor(s)
    xFarDicLeitner(wxWindow *parent, const wxString& title, const wxPoint& pos, const wxSize& size, wxLocale& m_locale,
            long style = wxDEFAULT_FRAME_STYLE);

    /// OK click handler
    void OnOK(wxCommandEvent& event); 
    /// Boxes content loader
    wxArrayString LoadLeitnerBoxContents(wxString configpath); 
    /// Translate buttons event handlers
    void OnTranslateA(wxCommandEvent& event);
    void OnTranslateB(wxCommandEvent& event);    
    void OnTranslateC(wxCommandEvent& event);    
    void OnTranslateD(wxCommandEvent& event);    
    void OnTranslateE(wxCommandEvent& event);
    /// Pronounce buttons event handlers
    void OnSpeakA(wxCommandEvent& event);
    void OnSpeakB(wxCommandEvent& event);    
    void OnSpeakC(wxCommandEvent& event);    
    void OnSpeakD(wxCommandEvent& event);    
    void OnSpeakE(wxCommandEvent& event);   
    /// Next buttons event handlers
    void OnNextA(wxCommandEvent& event);
    void OnNextB(wxCommandEvent& event);    
    void OnNextC(wxCommandEvent& event);    
    void OnNextD(wxCommandEvent& event);  
    /// Back buttons event handlers
    void OnBackB(wxCommandEvent& event);
    void OnBackC(wxCommandEvent& event);
    void OnBackD(wxCommandEvent& event);     
    void OnBackE(wxCommandEvent& event);
    /// Remove word button event handler
    void OnRemoveA(wxCommandEvent& event);
    /// Confirm word event handler
    void OnConfirm(wxCommandEvent& event);
    /// Cleans up all boxes
    void OnClear(wxCommandEvent& event);      
    /// Commit changes to the config file
    void SubmitChanges();
    /// Updates boxes
    void UpdateBoxes(bool reload = FALSE); 
    /// Pronounce the word
    void Speak(wxString strSpk);
    /// Leitner window constructor
    ~xFarDicLeitner(); 

    wxLocale& m_locale;
    void CreateLayout();
    wxStaticBitmap *staticBitmap;
    wxStaticText *lttext;

private:
    // any class wishing to process wxWindows events must use this macro   
    wxListBox *boxa,
              *boxb,
              *boxc,
              *boxd,
              *boxe;

    wxStaticBox *m_ltbox;

    wxString boxasize,
             boxbsize,
             boxcsize,
             boxdsize,
             boxesize;

    wxArrayString boxacontents,
                  boxbcontents,
                  boxccontents,
                  boxdcontents,
                  boxecontents;
   
    wxPanel *bapanel,
            *bbpanel,
            *bcpanel,
            *bdpanel,
            *bepanel;

    wxButton *m_ok, *m_clear;

    wxBitmapButton *m_anext,
                   *m_bnext,
                   *m_cnext,
                   *m_dnext,
                   *m_bback,
                   *m_cback,
                   *m_dback,
                   *m_eback,
                   *m_atrans,
                   *m_btrans,
                   *m_ctrans,
                   *m_dtrans,
                   *m_etrans,
                   *m_remove,
                   *m_confirm,
                   *m_aspeak,
                   *m_bspeak,
                   *m_cspeak,
                   *m_dspeak,
                   *m_espeak;

    wxStaticText *boxatext,
                 *boxbtext,
                 *boxctext,
                 *boxdtext,
                 *boxetext;

    wxNotebook *layout;

    int bacap,
        bbcap,
        bccap,
        bdcap,
        becap; 

    bool tts; 
   
    DECLARE_EVENT_TABLE()
};
#endif

