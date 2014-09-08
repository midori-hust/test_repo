## Process this file with automake to produce Makefile.in

## Created by Anjuta

uidir = $(datadir)/gtk_rungchuongvang/ui
ui_DATA = gtk_rungchuongvang.ui

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(GTK_RUNGCHUONGVANG_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = gtk_rungchuongvang

gtk_rungchuongvang_SOURCES = \
	callbacks.c \
	callbacks.h \
	main.c

gtk_rungchuongvang_LDFLAGS = \
	-Wl,--export-dynamic

gtk_rungchuongvang_LDADD = $(GTK_RUNGCHUONGVANG_LIBS)

EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(datadir)/gtk_rungchuongvang
