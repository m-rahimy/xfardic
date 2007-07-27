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

#include "tts.h"

xFarDicTexttoSpeech::xFarDicTexttoSpeech() {
     CORBA_exception_init(&cev);
     int argc = 1;
     char *argv[1];
     argv[0] = "xfardic";
        if (!bonobo_init(&argc,argv))
        {
                g_error ("Can't initialize Bonobo...\n");
          init = false;
          return;
        }
        co = select_server(&cev); //priority is with festival synthesizer engine
        if (BONOBO_EX (&cev) || co == CORBA_OBJECT_NIL)
        {
                fprintf (stderr, "Server selection failed");//: %s.\n",
                //BONOBO_EX (&cev) ? bonobo_exception_get_text (&cev) : "object is NIL");
                init = false;
          return;
        }
        /* Attempt to initialize the driver  */
        if (!GNOME_Speech_SynthesisDriver_driverInit (co, &cev)) {
                fprintf (stderr, "Server could not be initialized.\n");
                bonobo_object_release_unref (co, NULL);
                CORBA_exception_free (&cev);
                bonobo_debug_shutdown ();
                init = false;
          return;
        }

        driver_name = GNOME_Speech_SynthesisDriver__get_driverName (co, &cev);
        if (!BONOBO_EX (&cev))
        {
                fprintf (stderr, "Driver name: %s\n", driver_name);
                CORBA_free (driver_name);
        }
        driver_version = GNOME_Speech_SynthesisDriver__get_driverVersion (co, &cev);
        if (!BONOBO_EX (&cev))
        {
                fprintf (stderr, "Driver version: %s\n", driver_version);
                CORBA_free (driver_version);
        }
        synth_name = GNOME_Speech_SynthesisDriver__get_synthesizerName (co, &cev);
        if (!BONOBO_EX (&cev))
        {
                fprintf (stderr, "Synthesizer name: %s\n", synth_name);
                CORBA_free (synth_name);
        }
        synth_version = GNOME_Speech_SynthesisDriver__get_synthesizerVersion (co, &cev);
        if (!BONOBO_EX (&cev))
        {
                fprintf (stderr, "Synthesizer Version: %s\n", synth_version);
                CORBA_free (synth_version);
        }

        fprintf(stderr, "selecting male gender.\n");
        gender = GNOME_Speech_gender_male;// GNOME_Speech_gender_female;

        /* Display list of voices */

        voices = GNOME_Speech_SynthesisDriver_getAllVoices (co, &cev);
       
        if (BONOBO_EX (&cev)) {
                fprintf (stderr, "Exception getting voice list.\n");//%s getting voice list.\n",
                         //bonobo_exception_get_text (&cev));
                init = false;
          return;
        }

        if (voices->_length < 1) {
                fprintf (stderr, "No voices, bailing out.\n");
                init = false;
          return;
        }
     int i;
       for (i = 0; i < voices->_length; i++) {
                if (strstr(voices->_buffer[i].name,"english") != NULL || strstr(voices->_buffer[i].language,"english") != NULL) {
          speaker = GNOME_Speech_SynthesisDriver_createSpeaker (co, &voices->_buffer[i], &cev);
                if (BONOBO_EX (&cev)) {
                        fprintf (stderr, "Exception creating speaker.\n");//%s creating speaker.\n", bonobo_exception_get_text (&cev));
                        bonobo_object_release_unref (speaker, NULL);
          }
          
       }
      } 
     if (speaker == CORBA_OBJECT_NIL) {
                fprintf (stderr, "Error creating speaker.\n");
                init = false;
          return;
        }
     fprintf(stderr, "xFarDic TTS initialized properly...\n");
            init = true;
}

int xFarDicTexttoSpeech::say(const char *format, ...) {
     if (init = false) return -1;
     va_list args;
        char *str;
        va_start (args, format);
        CORBA_exception_init (&cev);

        str = g_strdup_vprintf (format, args);
        fprintf (stderr, "%s\n", str);
        GNOME_Speech_Speaker_say (speaker, str, &cev);
        if (BONOBO_EX (&cev))
                printf ("Exception writing '%s'\n",//%s writing '%s'",
                        //bonobo_exception_get_text (&cev), str);
                        str);
        g_free (str);
        CORBA_exception_free (&cev);
        va_end (args);
}

CORBA_Object xFarDicTexttoSpeech::select_server(CORBA_Environment *ev) {
     int i;
        Bonobo_ServerInfoList *servers;
        Bonobo_ServerInfo *info;
        CORBA_Object rv;

        servers = bonobo_activation_query (
                "repo_ids.has ('IDL:GNOME/Speech/SynthesisDriver:0.3')",
                NULL, ev);
        if (BONOBO_EX (ev)) {
                return CORBA_OBJECT_NIL;
        }
        if (!servers)
        {
                return CORBA_OBJECT_NIL;
        }
     if (servers->_length > 0) 
          fprintf(stderr,"Detected servers:\n");
        int Festival = -1,Espeak = -1;
     for (i = 0; i < servers->_length; i++)
        {
                info = &servers->_buffer[i];
                printf ("%d-%s\n", i+1, info->iid);
          if (strstr(info->iid, "Festival") != NULL) {
               Festival = i;
               fprintf(stderr, "Festival driver found\n");
          } else if (strstr(info->iid, "Espeak") != NULL ) {
               Espeak = i;
               fprintf(stderr, "Espeak driver found\n");
          }
        }
     //currently two speech synthesis engine is supported: 1-Festival 2-Espeak
     if (Festival > 0) 
          info = &servers->_buffer[Festival];
     else if (Espeak > 0)
          info = &servers->_buffer[Espeak];
     else {
          fprintf(stderr, "no supported driver found, please install one of Festival or Espeak synthesis drivers\n");
          return CORBA_OBJECT_NIL;
     }
        fprintf (stderr, "Attempting to activate %s.\n", info->iid);
        rv = bonobo_activation_activate_from_id (
                (const Bonobo_ActivationID) info->iid,
                0, NULL, ev);
        if (BONOBO_EX (ev)) {
          fprintf (stderr, "Error activating service\n.");//: %s\n", bonobo_exception_get_text (ev));
          return CORBA_OBJECT_NIL;
     }
        CORBA_free (servers);

        return rv;
}

