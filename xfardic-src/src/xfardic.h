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

#ifndef __XFARDIC_H
#define __XFARDIC_H

using namespace std;

// For compilers that support precompilation, includes "wx/wx.h".
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/wxprec.h"
#include "wx/filefn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xmlreader.h>
#include "wx/string.h"
#include "wx/config.h"
#include "wx/choice.h"
#include "wx/clipbrd.h"
#include "wx/filename.h"
#include "wx/statbmp.h"
#include "wx/spinctrl.h"
#include "wx/splash.h"
#include "wx/fontdlg.h"
#include "wx/fontenum.h"
#include "wx/fontmap.h"
#include "wx/taskbar.h"
#include "wx/utils.h"
#include "wx/filedlg.h"
#include "wx/slider.h"
#include "wx/generic/filedlgg.h"
#include "wx/log.h"
#include "wx/intl.h"
#include "wx/timer.h"
#include "wx/choicdlg.h"
#include "wx/listbox.h"
#include "wx/notebook.h"
#include "wx/msgdlg.h"
#include "aspell.h"
#include "wx/dynarray.h"
#include "wx/progdlg.h"
#include "wx/bmpbuttn.h"
#include "wx/artprov.h"
#include "wx/snglinst.h"
#include "wx/filesys.h"
#include "wx/cmdline.h"
#include <libnotify/notify.h>
#include <gtk/gtk.h>
#include <cstring>
#include "sqlite3.h"
#include "constants.h"

#ifdef HAVE_SPEAKLIB
    #include "speak_lib.h"
#endif

#define ArraySeparator            ';'

extern bool showAspell;
extern bool showAbout;
extern bool showLeitner;
extern bool showSettings;

#endif
