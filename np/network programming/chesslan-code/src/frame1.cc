/*
 * $Revision: 46 $ Hollow frame to hold board canvas 
 */

// #include <sigc++/compatibility.h>

// iostream for debugging purposes only
#ifndef _ERROR_HH
#include "error.hh"
#endif

#include "config.h"
#include "frame1.hh"

frame1::frame1 (GlademmData * _data):frame1_glade (_data)
{
        Gtk::Frame * frame1 = this;

        Gtk::Label * flabel1 = Gtk::manage (new class Gtk::Label (""));
        // set attributes for label
        flabel1->set_alignment (0.5, 0.5);
        flabel1->set_padding (0, 0);
        flabel1->set_justify (Gtk::JUSTIFY_LEFT);
        flabel1->set_line_wrap (false);
        flabel1->set_use_markup (false);
        // set defaults for frame1
        frame1->set_size_request (X_dimension, Y_dimension);
        frame1->set_shadow_type (Gtk::SHADOW_ETCHED_IN);
        frame1->set_label_align (0, 0.5);
        frame1->set_label_widget (*flabel1);

        // put the board in the canvas
        board *
                board1 =
                Gtk::manage (new class board(X_dimension, Y_dimension));

        // add canvas
        frame1->add (*board1);

        // canvas->signal_key_press_event()
        // .connect(bind(SigC::slot(*this, &pawn::on_key_press), canvas));
        // add board to frame1
        // frame1->add(*board);

        flabel1->show ();
        frame1->show_all ();
}

/*
 * frame1::~frame1() { } 
 */
