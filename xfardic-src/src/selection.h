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
// | Created: 03/26/2004                                                     |
// +-------------------------------------------------------------------------+
// | Authors: Alan Baghumian  <alan@technotux.org                            |
// |          Armen Baghumian <armen@OpenSourceClub.org>                     |
// +-------------------------------------------------------------------------+
#ifndef __SD_SELECTION_H__
#define __SD_SELECTION_H__

#include "xfardic.h"

const int SELECTION_INTERVAL=1000; 		    // check selection interval.

class Selection {
private:    	

	gint IsBusy;
	gint timeout;

	void create_selection_widget();

	static gint TimeOutCallback(gpointer data);
	static void SelectionReceivedCallback(GtkWidget* widget,GtkSelectionData *selection_data, guint time, Selection *oSelection);
	void SelectionReceived(char* sValue);
	gboolean Enable();
public:
	GdkAtom UTF8_STRING_Atom, COMPOUND_TEXT_Atom; //need to set it to static? this make oTextWin can't use it conveniently.
	std::string LastClipWord;
	char* compStr;
	GtkWidget* selection_widget;

    Selection();
	void Init();
	void End();
	void start();
	void stop();
};

#endif
