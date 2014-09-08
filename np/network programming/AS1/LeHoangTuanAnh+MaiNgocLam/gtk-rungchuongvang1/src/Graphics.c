#ifdef GRAPHIC
#  include <config.h>
#endif

#include "callbacks.h"

void destroy(GtkWidget *widget, gpointer data);
{
gtk_main_quit ();
}
