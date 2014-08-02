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

// This code is based on StarDic's selection system.
#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include "selection.h"

wxMBConv *CharsetConvert = &wxConvUTF8;
#define UTF8_STR(s) (wxString(s, *CharsetConvert))

Selection::Selection()
{
    UTF8_STRING_Atom = COMPOUND_TEXT_Atom = GDK_NONE;
    IsBusy = 0;
    selection_widget = NULL;
    timeout = 0;
}

void Selection::create_selection_widget()
{
    if (selection_widget) {
        gtk_widget_destroy(selection_widget);
    }
    selection_widget = gtk_invisible_new ();
    g_signal_connect (G_OBJECT (selection_widget), "selection_received", G_CALLBACK (SelectionReceivedCallback), this);
}


void Selection::Init()
{
    UTF8_STRING_Atom = gdk_atom_intern("UTF8_STRING",FALSE);
    COMPOUND_TEXT_Atom = gdk_atom_intern("COMPOUND_TEXT",FALSE);

    create_selection_widget();
}

void Selection::End()
{
    stop();
    if (selection_widget) {
        gtk_widget_destroy(selection_widget);
    }
}

void Selection::start()
{
    if (!timeout) {
        timeout = g_timeout_add(SELECTION_INTERVAL,TimeOutCallback,this);
    }
}

void Selection::stop()
{
    if (timeout) {
        g_source_remove(timeout);
        timeout = 0;
    }
    LastClipWord.clear();
}

gint Selection::TimeOutCallback(gpointer data)
{
    Selection *oSelection = (Selection *)data;
  
    if (oSelection->IsBusy) {
        oSelection->IsBusy++;
        if (oSelection->IsBusy*SELECTION_INTERVAL > 8000 ) {
            //"selection_received" signal is not received for 8 seconds.
            //there encounter some error,and i find that this often take a long time (serveral minutes) to get the signal at last,
            //during this perioed,if you call gtk_selection_convert(),the "selection_received" signal will not be received also,
            //and at last these signals are received at almost the same time...BAD.
            //so here create a new selection_widget, then call gtk_selection_convert(). this should can throw that 
            //error selection.            
            g_warning("Error, selection data didn't received, retring!\n");
            oSelection->create_selection_widget();
            oSelection->IsBusy = 0;
        }
    } else {
        oSelection->IsBusy = 1;
        gtk_selection_convert (oSelection->selection_widget, GDK_SELECTION_PRIMARY, oSelection->UTF8_STRING_Atom, 
                               GDK_CURRENT_TIME);
    }

    return TRUE;
}

void Selection::SelectionReceivedCallback(GtkWidget* widget,GtkSelectionData *selection_data, guint time, Selection *oSelection)
{    
    gchar *result;
    result = (gchar *)gtk_selection_data_get_text (selection_data);
    if (!result) {
        /* If we asked for UTF8 and didn't get it, try compound_text;
        * if we asked for compound_text and didn't get it, try string;
        * If we asked for anything else and didn't get it, give up.
        */
        if (selection_data->target == oSelection->UTF8_STRING_Atom) {
            gtk_selection_convert (widget, GDK_SELECTION_PRIMARY, oSelection->COMPOUND_TEXT_Atom, GDK_CURRENT_TIME);
        } else if (selection_data->target == oSelection->COMPOUND_TEXT_Atom) {
            gtk_selection_convert (widget, GDK_SELECTION_PRIMARY, GDK_TARGET_STRING, GDK_CURRENT_TIME);
        } else {
            oSelection->IsBusy = 0;
            oSelection->LastClipWord.clear();
        }
        return;
    }
    oSelection->IsBusy = 0;

    oSelection->SelectionReceived(result);    
    g_free (result);
}

void Selection::SelectionReceived(char* sToken)
{
    if (sToken[0] == '\0') {
        LastClipWord.clear();
        return;
    }

    gint len = 0;
    gchar *a = sToken;
    while ((*a) && len < MaxValidLength ) {
        a = g_utf8_next_char (a);
        ++len;
    }
    *a = '\0';
    
    while (g_ascii_isspace(*sToken)) {
        sToken++;
    }

    if (sToken[0] == '\0') {
        LastClipWord.clear();
        return;
    }

    a=strchr(sToken,'\n');
    if (a) {
        *a='\0';
    }

    if (LastClipWord != sToken) {
        LastClipWord = sToken;
        GlobalStr = UTF8_STR(sToken);
        //DEBUGGING
        //fprintf(stderr, "Selection Received:%s\n", compStr);    
    }
}

