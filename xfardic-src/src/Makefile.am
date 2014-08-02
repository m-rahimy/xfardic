xfardic_cppflags = -I/usr/include -I/opt/gnome/include -I/usr/include/libxml2 `pkg-config --cflags gtk+-2.0` -I/usr/include/bonobo-activation-2.0 -I/usr/include/orbit-2.0 -I/usr/include/libbonobo-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/opt/gnome/include/pango-1.0 `wx-config --cxxflags` 

if BUILD_WITH_SPEAKLIB
xfardic_cppflags_extra = -I/usr/include/espeak
endif

AM_CPPFLAGS = 	\
		$(xfardic_cppflags)	\
		$(xfardic_cppflags_extra)

bin_PROGRAMS = xfardic
xfardic_SOURCES= xfardic.cpp xfardic_app.cpp about.cpp settings.cpp selection.cpp leitner.cpp pronounce.cpp
xfardic_ldflags = xfardic_ldflags = -lxml2 -laspell -pthread -lSM -lICE -lz `pkg-config --libs gtk+-2.0` -lXext -lXrender -lXinerama -lXi -lXrandr -lXcursor -lXfixes -lX11 -lm -lgmodule-2.0 -ldl -lgthread-2.0 -lnotify -lz `wx-config --libs` -lsqlite3
if BUILD_WITH_SPEAKLIB
xfardic_ldflags_extra = -lespeak
endif

AM_LDFLAGS =	\
		$(xfardic_ldflags)	\
		$(xfardic_ldflags_extra)	
