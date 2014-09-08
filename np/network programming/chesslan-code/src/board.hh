/*
 * $Revision: 70 $ Defines the board and the squares, plus move list. 
 */

#ifndef _BOARD_HH
#  define _BOARD_HH

// handle some errors here...

#include <gtkmm/messagedialog.h>

// #include <glibmm/exceptionhandler.h>
#include <gtkmm/table.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/alignment.h>
#include <gtkmm/frame.h>

// #include <libgnomecanvasmm/init.h>
#include <libgnomecanvasmm/canvas.h>
#include <libgnomecanvasmm/group.h>
#include <libgnomecanvasmm/item.h>
#include <libgnomecanvasmm/rect.h>
#include <libgnomecanvasmm/pixbuf.h>

#include <iostream>
#include <sstream>

// stl
// #include <vector>
#include <map>
// end stl

#include "config.h"
#include "network.hh"
#include "pieces.hh"

class board:public
        Gtk::VBox,
        public
        network
{
      public:
        // Gnome::Canvas::CanvasAA* canvas
        board ();
        board (int n_x, int n_y);
         ~
        board ();
        /*
         * bool push (); bool pop (); 
         */

        /*
         * TODO these should come from gconf preferences: guint get_darkcolor 
         * (); guint get_lightcolor (); 
         */

        // draws all squares
        void
        draw_board ();

        bool
        load_pieces (const char *path);

        bool
        move_piece (const char *piece, double col, double row);

        bool
        create_piece_at (const char *name, double col, double row);

        bool
        create_piece_at (Piece * _piece);

      private:
        // helper functions
        bool
        on_item_event (GdkEvent * event, Gnome::Canvas::Item * item);

        bool
        on_board_event (GdkEvent * event, Gnome::Canvas::Item * item);

        /* helpers for the original positioning of the pieces */
        void
        create_pawn (const char *name, const char *fpath);
        void
        create_knight (const char *name, const char *fpath);
        void
        create_bishop (const char *name, const char *fpath);
        void
        create_rook (const char *name, const char *fpath);
        void
        create_queen (const char *name, const char *fpath);
        void
        create_king (const char *name, const char *fpath);

        Gnome::Canvas::Pixbuf *
        create_piece (const char *image_file, double col, double row);

        Piece *
        get_piece (const char *piece);

        Piece *
        get_piece (double col, double row);

        Piece *
        get_piece (Gnome::Canvas::Item * item);

        double
        snap(double n);

      protected:
        Gnome::Canvas::CanvasAA *
                m_canvas;
        Gnome::Canvas::Rect *
                m_squares[64];

        Gnome::Canvas::Group *
                m_board[8][8];  // row,col

        std::map < int, std::string>
                m_move_list;    // dynamic array m_move_list[0]=d5-d6 ... or
                                // so

        // m_pieces["Pawn0"] for a the first white pawn
        std::map < std::string,
        Piece * >
                m_pieces;

};
#endif
