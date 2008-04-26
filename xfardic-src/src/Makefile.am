xfardic_cppflags = -I/usr/include -I/opt/gnome/include -I/usr/include/libxml2 -I/usr/include/gtk-2.0 -I/opt/gnome/include/gtk-2.0 -I/usr/lib/gtk-2.0/include -I/usr/lib/glib-2.0/include -I/opt/gnome/lib/glib-2.0/include -I/opt/gnome/lib/gtk-2.0/include -I/opt/gnome/include/glib-2.0 -I/usr/include/bonobo-activation-2.0 -I/usr/include/orbit-2.0 -I/usr/include/libbonobo-2.0 -I/usr/include/cairo -I/usr/include/atk-1.0 -I/opt/gnome/include/atk-1.0 -I/usr/include/pango-1.0 -I/opt/gnome/include/pango-1.0 -I/usr/include/glib-2.0 `wx-config --cxxflags` 

if BUILD_WITH_SPEAKLIB
xfardic_cppflags_extra = -I/usr/include/espeak
endif

AM_CPPFLAGS = 	\
		$(xfardic_cppflags)	\
		$(xfardic_cppflags_extra)

bin_PROGRAMS = xfardic
xfardic_SOURCES= xfardic.cpp xfardic_app.cpp about.cpp settings.cpp selection.cpp leitner.cpp pronounce.cpp
xfardic_ldflags = -lxml2 -laspell -pthread -lgnomeui-2 -lSM -lICE -lbonoboui-2 -lgnome-keyring -lz -lgnomecanvas-2 -lgnome-2 -lpopt -lart_lgpl_2 -lpangoft2-1.0 -lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgdk_pixbuf-2.0 -lpangocairo-1.0 -lfontconfig -lXext -lXrender -lXinerama -lXi -lXrandr -lXcursor -lXfixes -lpango-1.0 -lcairo -lX11 -lgnomevfs-2 -lbonobo-2 -lgconf-2 -lgobject-2.0 -lbonobo-activation -lORBit-2 -lm -lgmodule-2.0 -ldl -lgthread-2.0 -lglib-2.0 -lnotify -lz `wx-config --libs` -lsqlite3

if BUILD_WITH_SPEAKLIB
xfardic_ldflags_extra = -lespeak
endif

AM_LDFLAGS =	\
		$(xfardic_ldflags)	\
		$(xfardic_ldflags_extra)	
