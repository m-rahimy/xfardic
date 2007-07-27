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

#ifndef __TEXTTOSPEECH_H
#define __TEXTTOSPEECH_H

#include <xfardic.h>

/// xFarDic Text to Speech Abstraction Class
class xFarDicTexttoSpeech 
{
public:
        bool init;
        xFarDicTexttoSpeech(bool debug);
        int say(const char *, ...);        
private:
        CORBA_Object co;
        CORBA_Environment cev;
        CORBA_string driver_name, driver_version;
        CORBA_string synth_name, synth_version;
        GNOME_Speech_Speaker speaker;
        GNOME_Speech_voice_gender gender;
        GNOME_Speech_VoiceInfoList *voices;
        
        CORBA_Object select_server(CORBA_Environment *, bool debug);        
};

#endif
