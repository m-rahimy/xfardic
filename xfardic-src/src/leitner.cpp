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

#include "leitner.h"

BEGIN_EVENT_TABLE(xFarDicLeitner, wxFrame)
    EVT_BUTTON(wxID_OK, xFarDicLeitner::OnOK)
    EVT_BUTTON(wxID_CLEAR, xFarDicLeitner::OnClear)        
    EVT_BUTTON(ID_BTN_TRANS_A, xFarDicLeitner::OnTranslateA)
    EVT_BUTTON(ID_BTN_TRANS_B, xFarDicLeitner::OnTranslateB)
    EVT_BUTTON(ID_BTN_TRANS_C, xFarDicLeitner::OnTranslateC) 
    EVT_BUTTON(ID_BTN_TRANS_D, xFarDicLeitner::OnTranslateD)
    EVT_BUTTON(ID_BTN_TRANS_E, xFarDicLeitner::OnTranslateE)
    EVT_BUTTON(ID_BTN_NEXT_A, xFarDicLeitner::OnNextA)
    EVT_BUTTON(ID_BTN_NEXT_B, xFarDicLeitner::OnNextB)
    EVT_BUTTON(ID_BTN_NEXT_C, xFarDicLeitner::OnNextC)
    EVT_BUTTON(ID_BTN_NEXT_D, xFarDicLeitner::OnNextD)
    EVT_BUTTON(ID_BTN_BACK_B, xFarDicLeitner::OnBackB)
    EVT_BUTTON(ID_BTN_BACK_C, xFarDicLeitner::OnBackC)
    EVT_BUTTON(ID_BTN_BACK_D, xFarDicLeitner::OnBackD)
    EVT_BUTTON(ID_BTN_BACK_E, xFarDicLeitner::OnBackE)
    EVT_BUTTON(ID_BTN_SPK_A, xFarDicLeitner::OnSpeakA)
    EVT_BUTTON(ID_BTN_SPK_B, xFarDicLeitner::OnSpeakB)
    EVT_BUTTON(ID_BTN_SPK_C, xFarDicLeitner::OnSpeakC)
    EVT_BUTTON(ID_BTN_SPK_D, xFarDicLeitner::OnSpeakD)
    EVT_BUTTON(ID_BTN_SPK_E, xFarDicLeitner::OnSpeakE)
    EVT_BUTTON(ID_BTN_REMOVE, xFarDicLeitner::OnRemoveA)
    EVT_BUTTON(ID_BTN_CONFIRM, xFarDicLeitner::OnConfirm)
END_EVENT_TABLE()

bool showLeitner = TRUE;

xFarDicLeitner::~xFarDicLeitner()
{ 
  showLeitner = TRUE;
}

/// Leitner Windows creation function
xFarDicLeitner::xFarDicLeitner(wxWindow *parent, const wxString& title, const wxPoint& pos, const wxSize& size, wxLocale& locale, long style)
       : wxFrame(parent, -1, title, pos, size, style), m_locale(locale)
{    
    // set the frame icon    
    SetIcon(wxIcon(xfardic24x24));

    wxConfigBase *pConfig = wxConfigBase::Get();
    pConfig->SetPath(_T("/Options"));

    bacap = pConfig->Read(_T("Leitner-Base"), 10);
    watcher = pConfig->Read(_T("Watcher"), 0l);

    // First initialize Espeak engine
#ifdef HAVE_SPEAKLIB
    tts = pConfig->Read(_T("TTS"), 0l);
    if (tts) { 
        pronounce = new xFarDicPronounce();
        pronounce->Init();
    }
#else
    tts = FALSE;
#endif   

    // Box capacity calculation
    bbcap = bacap * 2;
    bccap = bacap * 4;
    bdcap = bacap * 8;
    becap = bacap * 15;  

    wxArtClient client;

    wxBitmap logo = wxArtProvider::GetBitmap(wxT("gnome-devel"), client, wxSize(32,35));

    staticBitmap = new wxStaticBitmap (this, -1, logo, wxPoint(10, 10));

    layout = new wxNotebook(this, xFarDic_ChangeTab);

    bapanel = new wxPanel(layout);
    bbpanel = new wxPanel(layout);
    bcpanel = new wxPanel(layout);
    bdpanel = new wxPanel(layout);
    bepanel = new wxPanel(layout);

    m_ltbox = new wxStaticBox(this, ID_LTBOX, _T(""));
    m_ok    = new wxButton(this, wxID_OK, _("&OK"), wxDefaultPosition,wxSize(80,36));
    m_clear = new wxButton(this, wxID_CLEAR, _("&Clear"), wxDefaultPosition, wxSize(80,36));

    // Set Default button
    m_ok->SetDefault();   

    lttext = new wxStaticText(this, -1, _("Leitner box can be used to support\nmemorization by way of spaced repetition.\nThis is how it works: you try to recall the\nmeaning of a word. If you succeed, you send\nthe word to the next box. But if you fail, you\nsend it back to the first box.")); 

    // Load box contents
    boxacontents = LoadLeitnerBoxContents(wxT("LTBOX-A"));
    boxbcontents = LoadLeitnerBoxContents(wxT("LTBOX-B"));
    boxccontents = LoadLeitnerBoxContents(wxT("LTBOX-C"));
    boxdcontents = LoadLeitnerBoxContents(wxT("LTBOX-D"));
    boxecontents = LoadLeitnerBoxContents(wxT("LTBOX-E"));

    boxa = new wxListBox(bapanel, ID_LTBOX_A, wxDefaultPosition, wxDefaultSize, boxacontents, wxLB_SINGLE|wxLB_NEEDED_SB);
    boxb = new wxListBox(bbpanel, ID_LTBOX_B, wxDefaultPosition, wxDefaultSize, boxbcontents, wxLB_SINGLE|wxLB_NEEDED_SB);
    boxc = new wxListBox(bcpanel, ID_LTBOX_C, wxDefaultPosition, wxDefaultSize, boxccontents, wxLB_SINGLE|wxLB_NEEDED_SB);
    boxd = new wxListBox(bdpanel, ID_LTBOX_D, wxDefaultPosition, wxDefaultSize, boxdcontents, wxLB_SINGLE|wxLB_NEEDED_SB);
    boxe = new wxListBox(bepanel, ID_LTBOX_E, wxDefaultPosition, wxDefaultSize, boxecontents, wxLB_SINGLE|wxLB_NEEDED_SB);

    boxasize = _("Word Count: ")+wxString::Format(wxT("%d"), boxa->GetCount())+wxT("/")+wxString::Format(wxT("%d"), bacap);
    boxbsize = _("Word Count: ")+wxString::Format(wxT("%d"), boxb->GetCount())+wxT("/")+wxString::Format(wxT("%d"), bbcap);
    boxcsize = _("Word Count: ")+wxString::Format(wxT("%d"), boxc->GetCount())+wxT("/")+wxString::Format(wxT("%d"), bccap);
    boxdsize = _("Word Count: ")+wxString::Format(wxT("%d"), boxd->GetCount())+wxT("/")+wxString::Format(wxT("%d"), bdcap);
    boxesize = _("Word Count: ")+wxString::Format(wxT("%d"), boxe->GetCount())+wxT("/")+wxString::Format(wxT("%d"), becap);
    
    boxatext = new wxStaticText(bapanel, -1, boxasize);
    boxbtext = new wxStaticText(bbpanel, -1, boxbsize);
    boxctext = new wxStaticText(bcpanel, -1, boxcsize);
    boxdtext = new wxStaticText(bdpanel, -1, boxdsize);
    boxetext = new wxStaticText(bepanel, -1, boxesize);

    // Icon
    wxBitmap  next = wxArtProvider::GetBitmap(wxART_GO_FORWARD, client, wxDefaultSize);
    wxBitmap  back = wxArtProvider::GetBitmap(wxART_GO_BACK, client, wxDefaultSize);
    wxBitmap  trans = wxArtProvider::GetBitmap(wxART_FIND, client, wxDefaultSize);
    wxBitmap  del = wxArtProvider::GetBitmap(wxART_DEL_BOOKMARK, client, wxDefaultSize);
    wxBitmap  confirm = wxArtProvider::GetBitmap( wxART_TIP, client, wxDefaultSize);
    wxBitmap  bttos = wxArtProvider::GetBitmap(wxT("sound"), client, wxDefaultSize);

    m_anext = new wxBitmapButton(bapanel, ID_BTN_NEXT_A, next, wxDefaultPosition,wxSize(80,36));
    m_bnext = new wxBitmapButton(bbpanel, ID_BTN_NEXT_B, next, wxDefaultPosition,wxSize(80,36));
    m_cnext = new wxBitmapButton(bcpanel, ID_BTN_NEXT_C, next, wxDefaultPosition,wxSize(80,36));
    m_dnext = new wxBitmapButton(bdpanel, ID_BTN_NEXT_D, next, wxDefaultPosition,wxSize(80,36));

    m_bback = new wxBitmapButton(bbpanel, ID_BTN_BACK_B, back, wxDefaultPosition,wxSize(80,36));
    m_cback = new wxBitmapButton(bcpanel, ID_BTN_BACK_C, back, wxDefaultPosition,wxSize(80,36));
    m_dback = new wxBitmapButton(bdpanel, ID_BTN_BACK_D, back, wxDefaultPosition,wxSize(80,36));
    m_remove = new wxBitmapButton(bapanel, ID_BTN_REMOVE, del, wxDefaultPosition,wxSize(80,36));
    m_confirm = new wxBitmapButton(bepanel, ID_BTN_CONFIRM, confirm, wxDefaultPosition,wxSize(80,36));
    m_eback = new wxBitmapButton(bepanel, ID_BTN_BACK_E, back, wxDefaultPosition,wxSize(80,36));

    m_atrans = new wxBitmapButton(bapanel, ID_BTN_TRANS_A, trans, wxDefaultPosition,wxSize(80,36));
    m_btrans = new wxBitmapButton(bbpanel, ID_BTN_TRANS_B, trans, wxDefaultPosition,wxSize(80,36));
    m_ctrans = new wxBitmapButton(bcpanel, ID_BTN_TRANS_C, trans, wxDefaultPosition,wxSize(80,36));
    m_dtrans = new wxBitmapButton(bdpanel, ID_BTN_TRANS_D, trans, wxDefaultPosition,wxSize(80,36));
    m_etrans = new wxBitmapButton(bepanel, ID_BTN_TRANS_E, trans, wxDefaultPosition,wxSize(80,36));

    if (! watcher) {
       m_atrans->Enable(FALSE);
       m_btrans->Enable(FALSE);
       m_ctrans->Enable(FALSE);
       m_dtrans->Enable(FALSE);
       m_etrans->Enable(FALSE);
    }

    m_aspeak = new wxBitmapButton(bapanel, ID_BTN_SPK_A, bttos, wxDefaultPosition,wxSize(80,36));
    m_bspeak = new wxBitmapButton(bbpanel, ID_BTN_SPK_B, bttos, wxDefaultPosition,wxSize(80,36));
    m_cspeak = new wxBitmapButton(bcpanel, ID_BTN_SPK_C, bttos, wxDefaultPosition,wxSize(80,36));
    m_dspeak = new wxBitmapButton(bdpanel, ID_BTN_SPK_D, bttos, wxDefaultPosition,wxSize(80,36));
    m_espeak = new wxBitmapButton(bepanel, ID_BTN_SPK_E, bttos, wxDefaultPosition,wxSize(80,36));

    if (! tts) {
       m_aspeak->Enable(FALSE);
       m_bspeak->Enable(FALSE);
       m_cspeak->Enable(FALSE);
       m_dspeak->Enable(FALSE);
       m_espeak->Enable(FALSE);
    }

    // Quantity Checks
    if (boxacontents.GetCount() < bacap) {
        m_anext->Enable(FALSE);
    }

    if (boxbcontents.GetCount() < bbcap) {
        m_bnext->Enable(FALSE);
    }

    if (boxccontents.GetCount() < bccap) {
        m_cnext->Enable(FALSE);
    }

    if (boxdcontents.GetCount() < bdcap) {
        m_dnext->Enable(FALSE);
    }

    layout->AddPage(bapanel, _("Box A"));    
    layout->AddPage(bbpanel, _("Box B"));
    layout->AddPage(bcpanel, _("Box C")); 
    layout->AddPage(bdpanel, _("Box D")); 
    layout->AddPage(bepanel, _("Box E")); 
    CreateLayout(); 
}

/// OK button click event handler.
void xFarDicLeitner::OnOK(wxCommandEvent& WXUNUSED(event))
{
    SubmitChanges();
    Close(TRUE);
}

wxArrayString xFarDicLeitner::LoadLeitnerBoxContents(wxString configpath)
{
    wxString ItemString, ltboxstr;
    wxArrayString tmparr;

    //Get Configuration From Config File
    wxConfigBase *pConfig = wxConfigBase::Get();

    pConfig->SetPath(_T("/Options"));

    ltboxstr = pConfig->Read(configpath, _T(""));
    delete wxConfigBase::Set((wxConfigBase *) NULL);
   
    ltboxstr = ltboxstr.Trim(TRUE);
    ltboxstr = ltboxstr.Trim(FALSE);
 
    if (ltboxstr.Len() > 0) {
        // Get number of array items, by number of delimiters + 1
        int array_items = ltboxstr.Freq( ArraySeparator ) + 1;

        // Loop through the string parsing
        for ( int i = 0; i < array_items; i++ ) {
            ItemString = ltboxstr.BeforeFirst( ArraySeparator );
            tmparr.Add( ItemString );
            ltboxstr = ltboxstr.AfterFirst( ArraySeparator );
        }        
    }

    return tmparr;
}

void xFarDicLeitner::OnTranslateA(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr, msg;
    
    wxConfigBase *pConfig = wxConfigBase::Get();

    boxa->GetSelections(selection);

    if (selection.GetCount()>0) {
        tmpStr = boxa->GetString(selection[0]);
    }else {
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;
    }

    if (tmpStr.Len()>0) {                  
        GlobalStr = tmpStr;
    }
}

void xFarDicLeitner::OnTranslateB(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr, msg;
    
    wxConfigBase *pConfig = wxConfigBase::Get();

    boxb->GetSelections(selection);

    if (selection.GetCount()>0) {
        tmpStr = boxb->GetString(selection[0]);
    }else {
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;
    }

    if (tmpStr.Len()>0) {                  
        GlobalStr = tmpStr;
    }
}

void xFarDicLeitner::OnTranslateC(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr, msg;
    
    wxConfigBase *pConfig = wxConfigBase::Get();

    boxc->GetSelections(selection);

    if (selection.GetCount()>0) {
        tmpStr = boxc->GetString(selection[0]);
    }else {
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;
    }

    if (tmpStr.Len()>0) {                  
        GlobalStr = tmpStr;
    }
}

void xFarDicLeitner::OnTranslateD(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr, msg;
    
    wxConfigBase *pConfig = wxConfigBase::Get();

    boxd->GetSelections(selection);

    if (selection.GetCount()>0) {
        tmpStr = boxd->GetString(selection[0]);
    }else {
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;
    }

    if (tmpStr.Len()>0) {                  
        GlobalStr = tmpStr;
    }
}

void xFarDicLeitner::OnTranslateE(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr, msg;
    
    wxConfigBase *pConfig = wxConfigBase::Get();

    boxe->GetSelections(selection);

    if (selection.GetCount()>0) {
        tmpStr = boxe->GetString(selection[0]);
    }else {
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;
    }

    if (tmpStr.Len()>0) {                  
        GlobalStr = tmpStr;
    }
}

void xFarDicLeitner::OnSpeakA(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString msg;
    
    boxa->GetSelections(selection);
#ifdef HAVE_SPEAKLIB
    if (selection.GetCount()>0) {
        pronounce->Pronounce(boxa->GetString(selection[0]));
    }else {
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;
    }
#endif
}

void xFarDicLeitner::OnSpeakB(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString msg;
    
    boxb->GetSelections(selection);
#ifdef HAVE_SPEAKLIB
    if (selection.GetCount()>0) {
        pronounce->Pronounce(boxb->GetString(selection[0]));
    }else {
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;
    }
#endif
}

void xFarDicLeitner::OnSpeakC(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString msg;
    
    boxc->GetSelections(selection);
#ifdef HAVE_SPEAKLIB
    if (selection.GetCount()>0) {
        pronounce->Pronounce(boxc->GetString(selection[0]));
    }else {
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;
    }
#endif
}

void xFarDicLeitner::OnSpeakD(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString msg;
    
    boxd->GetSelections(selection);
#ifdef HAVE_SPEAKLIB
    if (selection.GetCount()>0) {
        pronounce->Pronounce(boxd->GetString(selection[0]));
    }else {
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;
    }
#endif
}

void xFarDicLeitner::OnSpeakE(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString msg;
    
    boxe->GetSelections(selection);
#ifdef HAVE_SPEAKLIB
    if (selection.GetCount()>0) {
        pronounce->Pronounce(boxe->GetString(selection[0]));
    }else {
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;
    }
#endif
}

void xFarDicLeitner::OnNextA(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr, msg;    

    boxa->GetSelections(selection);

    if (!selection.GetCount() > 0) {    
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;
    } else {
        
        if (boxbcontents.GetCount() < bbcap) {        
            tmpStr = boxa->GetString(selection[0]);
            if (boxbcontents.Index(tmpStr,FALSE) == wxNOT_FOUND) {
                boxbcontents.Add(tmpStr);
            }
            boxacontents.RemoveAt(boxacontents.Index(tmpStr,FALSE),1);

            UpdateBoxes();

            SubmitChanges();            
        } else {
            msg.Printf( _("Box B is full.\n"));
            wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
            return;
        }
    }
}

void xFarDicLeitner::OnRemoveA(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr, msg;    

    boxa->GetSelections(selection);

    if (!selection.GetCount() > 0) {    
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;

    } else {
        tmpStr = boxa->GetString(selection[0]);
        boxacontents.RemoveAt(boxacontents.Index(tmpStr,FALSE),1);

        UpdateBoxes();
        SubmitChanges();            
    }
}

void xFarDicLeitner::OnConfirm(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr, msg;
    wxMessageDialog *confirm; 

    boxe->GetSelections(selection);

    if (!selection.GetCount() > 0) {    
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;

    } else {
        msg.Printf( _("Are you sure that you have learnt this word?\n"));
        confirm = new wxMessageDialog(this, msg, _T("xFarDic"), wxYES_NO | wxNO_DEFAULT | wxICON_EXCLAMATION | wxSTAY_ON_TOP);
        
        if (confirm->ShowModal() == wxID_YES) {
            tmpStr = boxe->GetString(selection[0]);
            boxecontents.RemoveAt(boxecontents.Index(tmpStr,FALSE),1);
        
            UpdateBoxes();
            SubmitChanges();            
        }
    }
}

void xFarDicLeitner::OnClear(wxCommandEvent& event)
{
    wxString msg;
    wxMessageDialog *confirm;
    msg.Printf( _("Are you sure that you want to clear the box contents?\n"));

    confirm = new wxMessageDialog(this, msg, _T("xFarDic"), wxYES_NO | wxNO_DEFAULT | wxICON_EXCLAMATION | wxSTAY_ON_TOP);

    if (confirm->ShowModal() == wxID_YES) {
        boxacontents.Empty();
        boxbcontents.Empty();
        boxccontents.Empty();
        boxdcontents.Empty();
        boxecontents.Empty();

        UpdateBoxes();
        SubmitChanges();            
    }
}

void xFarDicLeitner::OnBackB(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr, msg;    

    boxb->GetSelections(selection);

    if (!selection.GetCount() > 0) {    
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;
    } else {
        if (boxacontents.GetCount() < bacap) {        
            tmpStr = boxb->GetString(selection[0]);
            if (boxacontents.Index(tmpStr,FALSE) == wxNOT_FOUND) {
                boxacontents.Add(tmpStr);
            }
            boxbcontents.RemoveAt(boxbcontents.Index(tmpStr,FALSE),1);

            UpdateBoxes();

            SubmitChanges();            
        } else {
            msg.Printf( _("Box A is full.\n"));
            wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
            return;
        }
    }
}

void xFarDicLeitner::OnNextB(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr, msg;    

    boxb->GetSelections(selection);

    if (!selection.GetCount() > 0) {    
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;
    } else {
        if (boxccontents.GetCount() < bccap) {        
            tmpStr = boxb->GetString(selection[0]);
            if (boxccontents.Index(tmpStr,FALSE) == wxNOT_FOUND) {
                boxccontents.Add(tmpStr);
            }
            boxbcontents.RemoveAt(boxbcontents.Index(tmpStr,FALSE),1);

            UpdateBoxes();

            SubmitChanges();            
        } else {
            msg.Printf( _("Box C is full.\n"));
            wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
            return;
        }
    }
}

void xFarDicLeitner::OnBackC(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr, msg;    

    boxc->GetSelections(selection);

    if (!selection.GetCount() > 0) {    
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;
    } else {
        if (boxacontents.GetCount() < bacap) {        
            tmpStr = boxc->GetString(selection[0]);
            if (boxacontents.Index(tmpStr,FALSE) == wxNOT_FOUND) {
                boxacontents.Add(tmpStr);
            }
            boxccontents.RemoveAt(boxccontents.Index(tmpStr,FALSE),1);

            UpdateBoxes();

            SubmitChanges();            
        } else {
            msg.Printf( _("Box A is full.\n"));
            wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
            return;
        }
    }
}

void xFarDicLeitner::OnNextC(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr, msg;    

    boxc->GetSelections(selection);

    if (!selection.GetCount() > 0) {    
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;
    } else {
        if (boxdcontents.GetCount() < bdcap) {        
            tmpStr = boxc->GetString(selection[0]);
            if (boxdcontents.Index(tmpStr,FALSE) == wxNOT_FOUND) {
                boxdcontents.Add(tmpStr);
            }
            boxccontents.RemoveAt(boxccontents.Index(tmpStr,FALSE),1);

            UpdateBoxes();

            SubmitChanges();            
        } else {
            msg.Printf( _("Box D is full.\n"));
            wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
            return;
        }
    }
}

void xFarDicLeitner::OnBackD(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr, msg;    

    boxd->GetSelections(selection);

    if (!selection.GetCount() > 0) {    
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;
    } else {
        if (boxacontents.GetCount() < bacap) {        
            tmpStr = boxd->GetString(selection[0]);
            if (boxacontents.Index(tmpStr,FALSE) == wxNOT_FOUND) {
                boxacontents.Add(tmpStr);
            }
            boxdcontents.RemoveAt(boxdcontents.Index(tmpStr,FALSE),1);

            UpdateBoxes();

            SubmitChanges();            
        } else {
            msg.Printf( _("Box A is full.\n"));
            wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
            return;
        }
    }
}

void xFarDicLeitner::OnNextD(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr, msg;    

    boxd->GetSelections(selection);

    if (!selection.GetCount() > 0) {    
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;
    } else {
        if (boxecontents.GetCount() < becap) {        
            tmpStr = boxd->GetString(selection[0]);
            if (boxecontents.Index(tmpStr,FALSE) == wxNOT_FOUND) {
                boxecontents.Add(tmpStr);
            }
            boxdcontents.RemoveAt(boxdcontents.Index(tmpStr,FALSE),1);

            UpdateBoxes();

            SubmitChanges();            
        } else {
            msg.Printf( _("Box E is full.\n"));
            wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
            return;
        }
    }
}

void xFarDicLeitner::OnBackE(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr, msg;    

    boxe->GetSelections(selection);

    if (!selection.GetCount() > 0) {    
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;
    } else {
        if (boxacontents.GetCount() < bacap) {        
            tmpStr = boxe->GetString(selection[0]);
            if (boxacontents.Index(tmpStr,FALSE) == wxNOT_FOUND) {
                boxacontents.Add(tmpStr);
            }
            boxecontents.RemoveAt(boxecontents.Index(tmpStr,FALSE),1);

            UpdateBoxes();

            SubmitChanges();            
        } else {
            msg.Printf( _("Box A is full.\n"));
            wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
            return;
        }
    }
}

void xFarDicLeitner::UpdateBoxes(bool reload)
{
    if (reload) {
       boxacontents = LoadLeitnerBoxContents(wxT("LTBOX-A"));
       boxbcontents = LoadLeitnerBoxContents(wxT("LTBOX-B"));
       boxccontents = LoadLeitnerBoxContents(wxT("LTBOX-C"));
       boxdcontents = LoadLeitnerBoxContents(wxT("LTBOX-D"));
       boxecontents = LoadLeitnerBoxContents(wxT("LTBOX-E"));
    }
    
    // Update contents
    boxa->Set(boxacontents);
    boxb->Set(boxbcontents);
    boxc->Set(boxccontents);
    boxd->Set(boxdcontents);
    boxe->Set(boxecontents);

    if (boxdcontents.GetCount() < bdcap) {
        m_dnext->Enable(FALSE);
    } else {
        m_dnext->Enable(TRUE);
    }

    if (boxccontents.GetCount() < bccap) {
        m_cnext->Enable(FALSE);
    } else {
        m_cnext->Enable(TRUE);
    }

    if (boxbcontents.GetCount() < bbcap) {
        m_bnext->Enable(FALSE);
    } else {
        m_bnext->Enable(TRUE);
    }

    if (boxacontents.GetCount() < bacap) {
        m_anext->Enable(FALSE);
    } else {
        m_anext->Enable(TRUE);
    }

    // Update box counter labels
    boxasize = _("Word Count: ")+wxString::Format(wxT("%d"), boxa->GetCount())+wxT("/")+wxString::Format(wxT("%d"), bacap);
    boxbsize = _("Word Count: ")+wxString::Format(wxT("%d"), boxb->GetCount())+wxT("/")+wxString::Format(wxT("%d"), bbcap);
    boxcsize = _("Word Count: ")+wxString::Format(wxT("%d"), boxc->GetCount())+wxT("/")+wxString::Format(wxT("%d"), bccap);
    boxdsize = _("Word Count: ")+wxString::Format(wxT("%d"), boxd->GetCount())+wxT("/")+wxString::Format(wxT("%d"), bdcap);
    boxesize = _("Word Count: ")+wxString::Format(wxT("%d"), boxe->GetCount())+wxT("/")+wxString::Format(wxT("%d"), becap);
    
    boxatext->SetLabel(boxasize);
    boxbtext->SetLabel(boxbsize);
    boxctext->SetLabel(boxcsize);
    boxdtext->SetLabel(boxdsize);
    boxetext->SetLabel(boxesize);
}

void xFarDicLeitner::SubmitChanges()
{
    wxString tmpStr, att;

    tmpStr = wxT("");

    wxConfigBase *pConfig = wxConfigBase::Get();

    if (boxacontents.GetCount()>0) {          
        for (int x=0; x < boxacontents.GetCount(); x++) {
            if (tmpStr.Len()==0) {
                att = _T(";");
            } 
            if (x+1 < boxacontents.GetCount()) {
                tmpStr = tmpStr + boxacontents[x] + att;
            } else {
                tmpStr = tmpStr + boxacontents[x];
            }
        }
    }

    pConfig->Write(_T("/Options/LTBOX-A"), tmpStr);

    tmpStr = wxT("");        

    if (boxbcontents.GetCount()>0) {          
        for (int x=0; x < boxbcontents.GetCount(); x++) {
            if (tmpStr.Len()==0) {
                att = _T(";");
            }
            if (x+1 < boxbcontents.GetCount()) {
                tmpStr = tmpStr + boxbcontents[x] + att;
            } else {
                tmpStr = tmpStr + boxbcontents[x];
            }
        }
    }

    pConfig->Write(_T("/Options/LTBOX-B"), tmpStr);

    tmpStr = wxT("");

    if (boxccontents.GetCount()>0) {          
        for (int x=0; x < boxccontents.GetCount(); x++) {
            if (tmpStr.Len()==0) {
                att = _T(";");
            }
            if (x+1 < boxccontents.GetCount()) {
                tmpStr = tmpStr + boxccontents[x] + att;
            } else {
                tmpStr = tmpStr + boxccontents[x];
            }
        }
    }

    pConfig->Write(_T("/Options/LTBOX-C"), tmpStr);

    tmpStr = wxT("");

    if (boxdcontents.GetCount()>0) {          
        for (int x=0; x < boxdcontents.GetCount(); x++) {
            if (tmpStr.Len()==0) {
                att = _T(";");
            }
            if (x+1 < boxdcontents.GetCount()) {
                tmpStr = tmpStr + boxdcontents[x] + att;
            } else {
                tmpStr = tmpStr + boxdcontents[x];
            }
        }
    }

    pConfig->Write(_T("/Options/LTBOX-D"), tmpStr);
    delete wxConfigBase::Set((wxConfigBase *) NULL);
}

void xFarDicLeitner::CreateLayout() {
     wxBoxSizer *topsizer = new wxBoxSizer( wxVERTICAL );

     wxBoxSizer *logoandtextsizer = new wxBoxSizer(wxHORIZONTAL);
     logoandtextsizer->Add(staticBitmap, 0, wxALIGN_LEFT|wxALL, 4);
     logoandtextsizer->Add(lttext, 0, wxALIGN_LEFT|wxALL, 4);
     topsizer->Add(logoandtextsizer, 0, wxEXPAND|wxALL, 0);
     
     topsizer->Add(layout, 1, wxALL|wxEXPAND, 4);

     wxBoxSizer *bapanelsizer = new wxBoxSizer(wxHORIZONTAL);
     bapanelsizer->Add(boxa, 1, wxEXPAND|wxALL, 0);
     wxBoxSizer *babuttonssizer = new wxBoxSizer(wxVERTICAL);
     babuttonssizer->Add(boxatext, 1, wxALIGN_CENTER|wxALL, 0);
     babuttonssizer->Add(m_anext ,1 , wxALIGN_CENTER|wxALL, 1);
     babuttonssizer->Add(m_remove ,1 ,wxALIGN_CENTER|wxALL, 1);
     babuttonssizer->Add(m_atrans ,1 ,wxALIGN_CENTER|wxALL, 1);
     babuttonssizer->Add(m_aspeak ,1 ,wxALIGN_CENTER|wxALL, 1);
     bapanelsizer->Add(babuttonssizer, 1, wxEXPAND|wxALL, 2);

     wxBoxSizer *bbpanelsizer = new wxBoxSizer(wxHORIZONTAL);
     bbpanelsizer->Add(boxb, 1, wxEXPAND|wxALL, 0);
     wxBoxSizer *bbbuttonssizer = new wxBoxSizer(wxVERTICAL);
     bbbuttonssizer->Add(boxbtext, 1, wxALIGN_CENTER|wxALL, 0);
     bbbuttonssizer->Add(m_bnext ,1 , wxALIGN_CENTER|wxALL, 1);
     bbbuttonssizer->Add(m_bback ,1 , wxALIGN_CENTER|wxALL, 1);
     bbbuttonssizer->Add(m_btrans ,1 ,wxALIGN_CENTER|wxALL, 1);
     bbbuttonssizer->Add(m_bspeak ,1 ,wxALIGN_CENTER|wxALL, 1);
     bbpanelsizer->Add(bbbuttonssizer, 1, wxEXPAND|wxALL, 2);

     wxBoxSizer *bcpanelsizer = new wxBoxSizer(wxHORIZONTAL);
     bcpanelsizer->Add(boxc, 1, wxEXPAND|wxALL, 0);
     wxBoxSizer *bcbuttonssizer = new wxBoxSizer(wxVERTICAL);
     bcbuttonssizer->Add(boxctext, 1, wxALIGN_CENTER|wxALL, 0);
     bcbuttonssizer->Add(m_cnext ,1 , wxALIGN_CENTER|wxALL, 1);
     bcbuttonssizer->Add(m_cback ,1 , wxALIGN_CENTER|wxALL, 1);
     bcbuttonssizer->Add(m_ctrans ,1 ,wxALIGN_CENTER|wxALL, 1);
     bcbuttonssizer->Add(m_cspeak ,1 ,wxALIGN_CENTER|wxALL, 1);
     bcpanelsizer->Add(bcbuttonssizer, 1, wxEXPAND|wxALL, 2);

     wxBoxSizer *bdpanelsizer = new wxBoxSizer(wxHORIZONTAL);
     bdpanelsizer->Add(boxd, 1, wxEXPAND|wxALL, 0);
     wxBoxSizer *bdbuttonssizer = new wxBoxSizer(wxVERTICAL);
     bdbuttonssizer->Add(boxdtext, 1, wxALIGN_CENTER|wxALL, 0);
     bdbuttonssizer->Add(m_dnext ,1 , wxALIGN_CENTER|wxALL, 1);
     bdbuttonssizer->Add(m_dback ,1 , wxALIGN_CENTER|wxALL, 1);
     bdbuttonssizer->Add(m_dtrans ,1 ,wxALIGN_CENTER|wxALL, 1);
     bdbuttonssizer->Add(m_dspeak ,1 ,wxALIGN_CENTER|wxALL, 1);
     bdpanelsizer->Add(bdbuttonssizer, 1, wxEXPAND|wxALL, 2);

     wxBoxSizer *bepanelsizer = new wxBoxSizer(wxHORIZONTAL);
     bepanelsizer->Add(boxe, 1, wxEXPAND|wxALL, 0);
     wxBoxSizer *bebuttonssizer = new wxBoxSizer(wxVERTICAL);
     bebuttonssizer->Add(boxetext, 1, wxALIGN_CENTER|wxALL, 0);
     bebuttonssizer->Add(m_eback ,1 , wxALIGN_CENTER|wxALL, 1);
     bebuttonssizer->Add(m_confirm ,1 ,wxALIGN_CENTER|wxALL, 1);
     bebuttonssizer->Add(m_etrans ,1 ,wxALIGN_CENTER|wxALL, 1);
     bebuttonssizer->Add(m_espeak ,1 ,wxALIGN_CENTER|wxALL, 1);
     bepanelsizer->Add(bebuttonssizer, 1, wxEXPAND|wxALL, 2);

     bapanel->SetAutoLayout( TRUE );
     bapanel->SetSizer( bapanelsizer );
     bbpanel->SetAutoLayout( TRUE );
     bbpanel->SetSizer( bbpanelsizer );
     bcpanel->SetAutoLayout( TRUE );
     bcpanel->SetSizer( bcpanelsizer );
     bdpanel->SetAutoLayout( TRUE );
     bdpanel->SetSizer( bdpanelsizer );
     bepanel->SetAutoLayout( TRUE );
     bepanel->SetSizer( bepanelsizer );

     wxBoxSizer *bottomsizer = new wxBoxSizer(wxHORIZONTAL);
     bottomsizer->AddStretchSpacer(1);
     bottomsizer->Add(m_clear, 0, wxALIGN_RIGHT|wxALL, 2);
     bottomsizer->Add(m_ok, 0, wxALIGN_RIGHT|wxALL, 2);
     
     topsizer->Add(bottomsizer, 0, wxEXPAND|wxALL, 0);

     SetSizer( topsizer );
     topsizer->SetSizeHints( this );
}

