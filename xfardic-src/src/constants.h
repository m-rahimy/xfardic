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

#ifndef __CONSTANTS_H
#define __CONSTANTS_H

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

#define XVERSION  _T("0.8.4")

// IDs for the controls and the menu commands
enum
{
    // menu items
    xFarDic_Quit = 1,
    xFarDic_Translate,
    xFarDic_Go,
    xFarDic_Back,
    xFarDic_Forward,
    xFarDic_First,
    xFarDic_Last,
    xFarDic_Select,
    xFarDic_Settings,
    xFarDic_Copy,
    xFarDic_Cut,
    xFarDic_Paste,
    xFarDic_Trash,
    xFarDic_Setfont,
    xFarDic_Srch,
    xFarDic_ViewToolBar,
    xFarDic_QApp,
    xFarDic_Spell,
    xFarDic_Watcher,
    xFarDic_Scanner,       
    xFarDic_Hide,        
    xFarDic_SOT,
    xFarDic_RevSrch,
    xFarDic_ChangeTab,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    xFarDic_About = wxID_ABOUT
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

const int ID_TOOLBAR = 500;

static const long TOOLBAR_STYLE = wxTB_FLAT | wxTB_DOCKABLE;

// ----------------------------------------------------------------------------
// event tables and other macros for wxWindows
// ----------------------------------------------------------------------------

// the event tables connect the wxWindows events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
const int  ID_BUTTON_TRANSLATE   = 100;
const int  ID_BOX_TRANSLATE      = 101;
const int  ID_BOX_RESULT         = 102;
const int  ID_SBITMAP            = 104;
const int  ID_ABBOX              = 105;
const int  ID_BACK               = 106;
const int  ID_FORWARD            = 107;
const int  ID_TRANSLATE          = 108;
const int  ID_QUIT               = 109;
const int  ID_ABOUT              = 110;
const int  ID_COMBO              = 111;
const int  ID_CHK_SELECT         = 112;
const int  ID_SELECT             = 113;
const int  ID_SETTINGS           = 116;
const int  ID_CUT                = 117;
const int  ID_COPY               = 118;
const int  ID_PASTE              = 119;
const int  ID_SPIN_ENTRY         = 120;
const int  ID_SETBOX             = 121;
const int  ID_SETBOXSMALL        = 122;
const int  ID_CHK_WINPOS         = 123;
const int  ID_RES_CTRL           = 124;
const int  ID_CHK_CACHE          = 125;
const int  ID_TRASH              = 126;
const int  ID_SETFONT            = 127;
const int  ID_CHK_SRCHSIM        = 128;
const int  ID_SRCH               = 129;
const int  ID_TRANSTOOLBAR       = 130;
const int  ID_DB_PATH            = 131;
const int  ID_CHK_SCANNER	 = 132;
const int  ID_SPELL              = 133;
const int  ID_CHK_SPELL          = 134;
const int  ID_CHOICE         	 = 135;
const int  ID_TIMER         	 = 136;
const int  ID_CHK_WATCHER	 = 137;
const int  ID_WATCHER	       	 = 138;
const int  ID_CHK_HIDE    	 = 139;
const int  ID_HIDE	         = 140;
const int  ID_SOT	         = 141;
const int  ID_REVSRCH         	 = 142;
const int  ID_CHK_REVSRCH 	 = 143;
const int  ID_SPIN_TIMEOUT 	 = 144;
#endif
