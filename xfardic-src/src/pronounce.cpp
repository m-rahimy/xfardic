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

#include "pronounce.h"

void xFarDicPronounce::Init()
{
#ifdef HAVE_SPEAKLIB
    // First initialize Espeak engine
    wxConfigBase *pConfig = wxConfigBase::Get();
    pConfig->SetPath(_T("/Options"));

    tts = pConfig->Read(_T("TTS"), 0l);
    acnt = pConfig->Read(_T("Accent"), 0l);

    if (tts) { 
        espeak_Initialize(AUDIO_OUTPUT_PLAYBACK, 0, NULL, 0);

        espeak_SetParameter(espeakRATE, pConfig->Read(_T("Rate"), 125), 0);
        espeak_SetParameter(espeakVOLUME, pConfig->Read(_T("Volume"), 100), 0);
        espeak_SetParameter(espeakPITCH, pConfig->Read(_T("Pitch"), 55), 0);
        espeak_SetParameter(espeakRANGE, pConfig->Read(_T("Range"), 50), 0);

        switch (acnt) {
               case 0:
                   // American Accent
                   voiceName = wxT("en-r");
                   break;
               case 1:
                   // British Accent
                   voiceName = wxT("en");
                   break;
        }

        espeak_SetVoiceByName((const char *)voiceName.mb_str(wxConvUTF8));
    }
#else
    tts = FALSE;
#endif
}

void xFarDicPronounce::Pronounce(wxString strSpk)
{
#ifdef HAVE_SPEAKLIB
   if (tts) {
        // Espeak playback implementation
        int synth_flags = espeakCHARS_AUTO | espeakPHONEMES | espeakENDPAUSE;
        int size;

        size = strlen(strSpk.mb_str(wxConvUTF8));

        espeak_Synth(strSpk.mb_str(wxConvUTF8), size+1 ,0 ,POS_CHARACTER, 0, synth_flags, NULL, NULL);
        espeak_Synchronize();

        espeak_Cancel();
    }
#endif

    return;
}

void xFarDicPronounce::Kill()
{
#ifdef HAVE_SPEAKLIB
      espeak_Cancel();
      espeak_Terminate();
#endif
}

