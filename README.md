#xFarDic - Multilingual Dictionary engine

## Introduction

_________________________________________________________________



Installation -> Refer to INSTALL file.
Licence -> Refer to LICENCE file.
New Features -> Refer to ChangeLog file.
_________________________________________________________________
Send report bugs and feature requests to alan@technotux.org
Official website : http://www.xfardic.org
<b>xFardic</b> is a comprehensive multilingual dictionary developed using GTK2, wxWidgets, libxml2, under GNU/Linux and relesed under GNU/GPL.

It can be installed and used in different RPM and Debian based distros.

Currently, xFarDic is released with three GPL'd and a non-free word databases. 
* GNU Collaborative International Dictionary of English
* English-English GNU/Linux
* English-Persian computer and scientific databases
* English-Persian generic DB
  * non-free, but distributable.

After installation, you can run xFarDic with xfardic command from terminal or run application dialogs. xFarDic is usable under all desktop environments like KDE, GNOME and XFce. xFarDic 0.8 and above binary packages are dependent to libxml2, wxGTK, libnotify, aspell, aspell-en and notification-daemon packages. Debian based distributions users can use the Parsix GNU/Linux apt repository to install xFarDic package without pain. Just add the following line to your /etc/apt/sources.list file:


Bug reports and feature requests

Send your bug reports and feature requests to alan@technotux.org email address.

## Dependencies

* GTK2
* wxWidgets, 
* libxml2
This code has been run and tested on Windows XP/Vista/7, Ubuntu Linux, Mac OS X.

## Build Dependencies

.wxGTK 2.8.x devel files
. aspell-dev
. libxml2-dev
. libgnome-desktop-dev
. libnotify-dev (0.7.0 minimum)
. libsqlite3-dev
. libespeak-dev 1.29 or later

## How to build


First, clone this repository, e.g.:

    git clone git://github.com/timofonic/xfardic/

. `cd' to the directory containing the package's source code and type
`./configure --prefix=/usr' to configure the package for your system.
  . If you're using `csh' on an old version of System V, you might need to type `sh ./configure --prefix=/usr' instead to prevent `csh' from trying to execute `configure' itself.
  . Running `configure' takes awhile. While running, it prints some messages telling which features it is checking for.
. Type `make' to compile xFarDic .
. Type `make install' as root user to install xFarDic. On Ubuntu based systems you can use `sudo make install' command.

## License

This project is licensed under the <b>GNU GPLv3+</b> license, a copy of which can be found in the `LICENSE.txt` file.

## Support

????
