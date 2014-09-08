/*
$Revision: 36 $
*/

#include <sigc++/compatibility.h>
#include <libgnomecanvasmm/pixbuf.h>

#include "board.hh"
#include "pawn.hh"

pawn::pawn (Gnome::Canvas::Group & root, char &name, double row, double col)
{
	// from the name passed to this function
	// we should be able to create either a white or black_image
	char white_image_file[] = "../pixmaps/P.png";
	//char black_image_file[] = "../pixmaps/p.png";
	//m_white_image = white_image;
	//m_black_image = black_image;
	m_name = &name;

	// TODO: should first "know" which color from first argument
	m_white_image = Gdk::Pixbuf::create_from_file (white_image_file);

	if (m_white_image)
	{
		Gnome::Canvas::Pixbuf * pixbuf
			=
			Gtk::manage (new Gnome::Canvas::
				     Pixbuf (root, row, col, m_white_image));
		pixbuf->signal_event ().
			connect (bind
				 (SigC::slot (*this, &pawn::on_item_event),
				  pixbuf));
	}
}

pawn::~pawn ()
{
}

bool pawn::pmove (char &name, double row, double col)
{
	// do pieces::move() function for all pieces
	// after verifying valid move for this piece
	// and then return true if everything was ok
	return false;
}
