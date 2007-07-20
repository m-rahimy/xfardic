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
    EVT_BUTTON(ID_BTN_REMOVE, xFarDicLeitner::OnRemoveA)
END_EVENT_TABLE()

bool showLeitner = true;

xFarDicLeitner::~xFarDicLeitner()
{ 
  showLeitner = true;
}

/// Leitner Windows creation function
xFarDicLeitner::xFarDicLeitner(wxWindow *parent, const wxString& title, const wxPoint& pos, const wxSize& size, wxLocale& locale, long style)
       : wxFrame(parent, -1, title, pos, size, style), m_locale(locale)
{    
    // set the frame icon    
    wxBitmap  micon(_T("/usr/share/xfardic/pixmaps/xfardic32.png"), wxBITMAP_TYPE_PNG);

    if (!micon.Ok()) {
        micon.LoadFile(_T("/usr/local/share/xfardic/pixmaps/xfardic32.png"), wxBITMAP_TYPE_PNG);
    }

    wxIcon wicon;
    wicon.CopyFromBitmap(micon);
    SetIcon(wicon);

    wxConfigBase *pConfig = wxConfigBase::Get();
    pConfig->SetPath(_T("/Options"));

    bacap = pConfig->Read(_T("Leitner-Base"), 10);

    // Box capacity calculation
    bbcap = bacap * 2;
    bccap = bacap * 4;
    bdcap = bacap * 8;
    becap = bacap * 15;  

    wxArtClient client;

    wxBitmap  logo = wxArtProvider::GetBitmap(wxT("gnome-devel"), client, wxSize(32,35));

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

    // Icon
    wxBitmap  next = wxArtProvider::GetBitmap(wxART_GO_FORWARD, client, wxDefaultSize);
    wxBitmap  back = wxArtProvider::GetBitmap(wxART_GO_BACK, client, wxDefaultSize);
    wxBitmap  trans = wxArtProvider::GetBitmap(wxART_FIND, client, wxDefaultSize);
    wxBitmap  del = wxArtProvider::GetBitmap(wxART_DEL_BOOKMARK, client, wxDefaultSize);
    wxBitmap  confirm = wxArtProvider::GetBitmap( wxART_TIP, client, wxDefaultSize);

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
    wxString tmpstr, ltboxstr, Part;
    wxArrayInt ltseppos;
    wxArrayString tmparr;

    //Get Configuration From Config File
    wxConfigBase *pConfig = wxConfigBase::Get();

    pConfig->SetPath(_T("/Options"));

    ltboxstr = pConfig->Read(configpath, _T(""));
   
    ltboxstr = ltboxstr.Trim(TRUE);
    ltboxstr = ltboxstr.Trim(FALSE);
 
    if (ltboxstr.Len() > 0) {
        for (int x=1; x <= ltboxstr.Len(); x++) {
            Part = ltboxstr.GetChar(x);
            if (Part.CmpNoCase(_T(";"))==0) {
                ltseppos.Add(x);
            }
        } // End For
    }

    if (ltseppos.GetCount()>0) {    
        for (int x=0; x <= ltseppos.GetCount(); x++) {
            if (x == 0) {
                tmpstr = ltboxstr.Mid(0,ltseppos[x]);
                if (tmpstr.Len()!=0) {
                    tmparr.Add(ltboxstr.Mid(0,ltseppos[x]));
                }
            } else if (x == ltseppos.GetCount()) {
                tmpstr = ltboxstr.Mid(ltseppos[x-1]+1,ltboxstr.Len());
                if (tmpstr.Len()!=0) {
                    tmparr.Add(ltboxstr.Mid(ltseppos[x-1]+1,ltboxstr.Len()));
                }
            } else {
                tmpstr = ltboxstr.Mid(ltseppos[x-1]+1,ltseppos[x]-ltseppos[x-1]-1);
                if (tmpstr.Len()!=0) {
                    tmparr.Add(ltboxstr.Mid(ltseppos[x-1]+1,ltseppos[x]-ltseppos[x-1]-1));
                }
            }
        }         
    } else if (ltboxstr.Len() > 0) {
        tmparr.Add(ltboxstr);
    }

    return tmparr;
}

void xFarDicLeitner::OnTranslateA(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr;
    
    wxConfigBase *pConfig = wxConfigBase::Get();

    boxa->GetSelections(selection);

    if (selection.GetCount()>0) {
        boxa->GetSelections(selection);
        tmpStr = boxa->GetString(selection[0]);
    }

    if (tmpStr.Len()>0) {                  
        pConfig->SetPath(_T("/"));
        pConfig->Write(_T("/Options/Temp-String"), tmpStr);        
    }
}

void xFarDicLeitner::OnTranslateB(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr;
    
    wxConfigBase *pConfig = wxConfigBase::Get();

    boxb->GetSelections(selection);

    if (selection.GetCount()>0) {
        tmpStr = boxb->GetString(selection[0]);
    }

    if (tmpStr.Len()>0) {                  
        pConfig->SetPath(_T("/"));
        pConfig->Write(_T("/Options/Temp-String"), tmpStr);        
    }
}

void xFarDicLeitner::OnTranslateC(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr;
    
    wxConfigBase *pConfig = wxConfigBase::Get();

    boxc->GetSelections(selection);

    if (selection.GetCount()>0) {
        tmpStr = boxc->GetString(selection[0]);
    }

    if (tmpStr.Len()>0) {                  
        pConfig->SetPath(_T("/"));
        pConfig->Write(_T("/Options/Temp-String"), tmpStr);        
    }
}

void xFarDicLeitner::OnTranslateD(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr;
    
    wxConfigBase *pConfig = wxConfigBase::Get();

    boxd->GetSelections(selection);

    if (selection.GetCount()>0) {
        tmpStr = boxd->GetString(selection[0]);
    }

    if (tmpStr.Len()>0) {                  
        pConfig->SetPath(_T("/"));
        pConfig->Write(_T("/Options/Temp-String"), tmpStr);        
    }
}

void xFarDicLeitner::OnTranslateE(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr;
    
    wxConfigBase *pConfig = wxConfigBase::Get();

    boxe->GetSelections(selection);

    if (selection.GetCount()>0) {
        tmpStr = boxe->GetString(selection[0]);
    }

    if (tmpStr.Len()>0) {                  
        pConfig->SetPath(_T("/"));
        pConfig->Write(_T("/Options/Temp-String"), tmpStr);        
    }
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
            if (boxbcontents.Index(tmpStr,false) == wxNOT_FOUND) {
                boxbcontents.Add(tmpStr);
            }
            boxacontents.RemoveAt(boxacontents.Index(tmpStr,false),1);

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
        boxacontents.RemoveAt(boxacontents.Index(tmpStr,false),1);

        UpdateBoxes();
        SubmitChanges();            
    }
}

void xFarDicLeitner::OnConfirm(wxCommandEvent& event)
{
    wxArrayInt selection;
    wxString tmpStr, msg;    

    boxe->GetSelections(selection);

    if (!selection.GetCount() > 0) {    
        msg.Printf( _("Please select a word.\n"));
        wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
        return;
    } else {
        tmpStr = boxe->GetString(selection[0]);
        boxecontents.RemoveAt(boxecontents.Index(tmpStr,false),1);

        UpdateBoxes();
        SubmitChanges();            
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
            if (boxacontents.Index(tmpStr,false) == wxNOT_FOUND) {
                boxacontents.Add(tmpStr);
            }
            boxbcontents.RemoveAt(boxbcontents.Index(tmpStr,false),1);

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
            if (boxccontents.Index(tmpStr,false) == wxNOT_FOUND) {
                boxccontents.Add(tmpStr);
            }
            boxbcontents.RemoveAt(boxbcontents.Index(tmpStr,false),1);

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
            if (boxacontents.Index(tmpStr,false) == wxNOT_FOUND) {
                boxacontents.Add(tmpStr);
            }
            boxccontents.RemoveAt(boxccontents.Index(tmpStr,false),1);

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
            if (boxdcontents.Index(tmpStr,false) == wxNOT_FOUND) {
                boxdcontents.Add(tmpStr);
            }
            boxccontents.RemoveAt(boxccontents.Index(tmpStr,false),1);

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
            if (boxacontents.Index(tmpStr,false) == wxNOT_FOUND) {
                boxacontents.Add(tmpStr);
            }
            boxdcontents.RemoveAt(boxdcontents.Index(tmpStr,false),1);

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
            if (boxecontents.Index(tmpStr,false) == wxNOT_FOUND) {
                boxecontents.Add(tmpStr);
            }
            boxdcontents.RemoveAt(boxdcontents.Index(tmpStr,false),1);

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
            if (boxacontents.Index(tmpStr,false) == wxNOT_FOUND) {
                boxacontents.Add(tmpStr);
            }
            boxecontents.RemoveAt(boxecontents.Index(tmpStr,false),1);

            UpdateBoxes();

            SubmitChanges();            
        } else {
            msg.Printf( _("Box A is full.\n"));
            wxMessageBox(msg, _T("xFarDic"), wxOK | wxICON_INFORMATION, this);
            return;
        }
    }
}

void xFarDicLeitner::UpdateBoxes()
{
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
}

void xFarDicLeitner::CreateLayout() {
     wxBoxSizer *topsizer = new wxBoxSizer( wxVERTICAL );

     wxBoxSizer *logoandtextsizer = new wxBoxSizer(wxHORIZONTAL);
     logoandtextsizer->Add(staticBitmap, 0, wxALIGN_LEFT|wxALL, 5);
     logoandtextsizer->Add(lttext, 0, wxALIGN_LEFT|wxALL, 5);
     topsizer->Add(logoandtextsizer, 0, wxEXPAND|wxALL, 5);
     
     topsizer->Add(layout, 1, wxALL|wxEXPAND, 5);

     wxBoxSizer *bapanelsizer = new wxBoxSizer(wxHORIZONTAL);
     bapanelsizer->Add(boxa, 1, wxEXPAND|wxALL, 10);
     wxBoxSizer *babuttonssizer = new wxBoxSizer(wxVERTICAL);
     babuttonssizer->Add(m_anext ,1 ,wxEXPAND|wxALL ,5);
     babuttonssizer->Add(m_remove ,1 ,wxEXPAND|wxALL ,5);
     babuttonssizer->Add(m_atrans ,1 ,wxEXPAND|wxALL ,5);
     bapanelsizer->Add(babuttonssizer, 0, wxEXPAND|wxALL, 10);

     wxBoxSizer *bbpanelsizer = new wxBoxSizer(wxHORIZONTAL);
     bbpanelsizer->Add(boxb, 1, wxEXPAND|wxALL, 10);
     wxBoxSizer *bbbuttonssizer = new wxBoxSizer(wxVERTICAL);
     bbbuttonssizer->Add(m_bnext ,1 ,wxEXPAND|wxALL ,5);
     bbbuttonssizer->Add(m_bback ,1 ,wxEXPAND|wxALL ,5);
     bbbuttonssizer->Add(m_btrans ,1 ,wxEXPAND|wxALL ,5);
     bbpanelsizer->Add(bbbuttonssizer, 0, wxEXPAND|wxALL, 10);

     wxBoxSizer *bcpanelsizer = new wxBoxSizer(wxHORIZONTAL);
     bcpanelsizer->Add(boxc, 1, wxEXPAND|wxALL, 10);
     wxBoxSizer *bcbuttonssizer = new wxBoxSizer(wxVERTICAL);
     bcbuttonssizer->Add(m_cnext ,1 ,wxEXPAND|wxALL ,5);
     bcbuttonssizer->Add(m_cback ,1 ,wxEXPAND|wxALL ,5);
     bcbuttonssizer->Add(m_ctrans ,1 ,wxEXPAND|wxALL ,5);
     bcpanelsizer->Add(bcbuttonssizer, 0, wxEXPAND|wxALL, 10);

     wxBoxSizer *bdpanelsizer = new wxBoxSizer(wxHORIZONTAL);
     bdpanelsizer->Add(boxd, 1, wxEXPAND|wxALL, 10);
     wxBoxSizer *bdbuttonssizer = new wxBoxSizer(wxVERTICAL);
     bdbuttonssizer->Add(m_dnext ,1 ,wxEXPAND|wxALL ,5);
     bdbuttonssizer->Add(m_dback ,1 ,wxEXPAND|wxALL ,5);
     bdbuttonssizer->Add(m_dtrans ,1 ,wxEXPAND|wxALL ,5);
     bdpanelsizer->Add(bdbuttonssizer, 0, wxEXPAND|wxALL, 10);

     wxBoxSizer *bepanelsizer = new wxBoxSizer(wxHORIZONTAL);
     bepanelsizer->Add(boxe, 1, wxEXPAND|wxALL, 10);
     wxBoxSizer *bebuttonssizer = new wxBoxSizer(wxVERTICAL);
     bebuttonssizer->Add(m_eback ,1 ,wxEXPAND|wxALL ,5);
     bebuttonssizer->Add(m_confirm ,1 ,wxEXPAND|wxALL ,5);
     bebuttonssizer->Add(m_etrans ,1 ,wxEXPAND|wxALL ,5);
     bepanelsizer->Add(bebuttonssizer, 0, wxEXPAND|wxALL, 10);

     bapanel->SetAutoLayout( true );
     bapanel->SetSizer( bapanelsizer );
     bbpanel->SetAutoLayout( true );
     bbpanel->SetSizer( bbpanelsizer );
     bcpanel->SetAutoLayout( true );
     bcpanel->SetSizer( bcpanelsizer );
     bdpanel->SetAutoLayout( true );
     bdpanel->SetSizer( bdpanelsizer );
     bepanel->SetAutoLayout( true );
     bepanel->SetSizer( bepanelsizer );

     wxBoxSizer *bottomsizer = new wxBoxSizer(wxHORIZONTAL);
     bottomsizer->AddStretchSpacer(1);
     bottomsizer->Add(m_clear, 0, wxALIGN_RIGHT|wxALL, 5);
     bottomsizer->Add(m_ok, 0, wxALIGN_RIGHT|wxALL, 5);
     
     topsizer->Add(bottomsizer, 0, wxEXPAND|wxALL, 5);

     SetSizer( topsizer );
     topsizer->SetSizeHints( this );
}
