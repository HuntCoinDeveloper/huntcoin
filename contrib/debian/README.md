
Debian
====================
This directory contains files used to package huntcoind/huntcoin-qt
for Debian-based Linux systems. If you compile huntcoind/huntcoin-qt yourself, there are some useful files here.

## huntcoin: URI support ##


huntcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install huntcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your huntcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoin128.png` to `/usr/share/pixmaps`

huntcoin-qt.protocol (KDE)

