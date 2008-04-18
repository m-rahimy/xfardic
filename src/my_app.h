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

#ifndef __MY_APP_H
#define __MY_APP_H

#include "xfardic.h"
#include "xfardic_app.h"

/// xFarDic Main Parent Class
class MyApp : public wxApp
{
public:
    // override base class virtuals
    // ----------------------------

    /// this one is called on application startup and is a good place for the app
    /// initialization (doing it here and not in the ctor allows to have an error
    /// return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();    
    /// Taskbar icon Right click event handler
    void OnTaskRightDown(wxTaskBarIconEvent& event);
    /// Taskbar icon Left click event handler
    void OnTaskLeftDown(wxTaskBarIconEvent& event);
    /// Paste from clipboard event handler
    void OnPaste(wxCommandEvent& event);
    /// Quit event handler
    void OnQuit(wxCommandEvent& event);   
    /// Show about window event handler 
    void OnAbout(wxCommandEvent& event);  
    /// Show settigs window event handler  
    void OnSettings(wxCommandEvent& event);    
    /// Set output font event handler
    void OnSetFont(wxCommandEvent& event); 
    /// Destructor
    ~MyApp();  
    
private:    
    xFarDicApp *frame;   

protected:
    wxLocale m_locale; // locale we'll be using 
    wxSingleInstanceChecker *m_checker;   
    
    DECLARE_EVENT_TABLE()
};

#endif

