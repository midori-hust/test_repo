bin_PROGRAMS = chesslan

chesslan_SOURCES = \
	board.cc\
	chesslan.cc\
	chesslan1_glade.cc \
	chesslan1.cc \
	menubar1_glade.cc \
	menubar1.cc \
	network.cc\
	notebook1_glade.cc \
	notebook1.cc \
	frame1_glade.cc \
	frame1.cc \
	statusbar1_glade.cc \
	statusbar1.cc \
	treeview1_glade.cc \
	treeview1.cc \
	toolbar1_glade.cc \
	toolbar1.cc 

noinst_HEADERS = \
	chesslan1_glade.hh \
	chesslan1.hh \
	menubar1_glade.hh \
	menubar1.hh \
	notebook1_glade.hh \
	notebook1.hh \
	frame1_glade.hh \
	frame1.hh \
	statusbar1_glade.hh \
	statusbar1.hh \
	treeview1_glade.hh \
	treeview1.hh \
	toolbar1_glade.hh \
	toolbar1.hh 

AM_CXXFLAGS = @GTKMM_CFLAGS@ @GNOMECANVASMM_CFLAGS@

chesslan_LDADD = @LIBS@ @GTKMM_LIBS@ @GNOMECANVASMM_LIBS@
