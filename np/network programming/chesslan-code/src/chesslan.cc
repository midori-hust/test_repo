// generated 2006/10/14 15:24:36 EDT by luigi@tuxy.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to chesslan.cc_new

// This file is for your program, I won't touch it again!

#include <config.h>
#include <gtkmm/main.h>
#include <glib/gi18n.h>
#include <libgnomecanvasmm.h>

#include "chesslan1.hh"

int main(int argc, char **argv)
{  
#if defined(ENABLE_NLS)
   bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
   bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
   textdomain (GETTEXT_PACKAGE);
#endif //ENABLE_NLS
   //Glib::thread_init();
   Gnome::Canvas::init();  
   Gtk::Main m(&argc, &argv);

chesslan1 *chesslan1 = new class chesslan1();
   m.run(*chesslan1);
delete chesslan1;
   return 0;
}
