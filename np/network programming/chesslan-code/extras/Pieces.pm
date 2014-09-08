#!/usr/bin/perl
# Luis Mondesi <lemsx1@gmail.com>
# 2006-10-12 16:17 EDT
#
# Based on gd_draw from Games::Chess::Coverage eg directory
# Put this in /usr/local/lib/site_perl/Pieces.pm or where Perl can find it

=pod

=head1 NAME

Pieces - Draw the pieces in Games::Chess with GD

=head1 DESCRIPTION

This is directly taken from the C<Games::Chess> module but simplified
and made to operate as a C<Games::Chess::Coverage> plug-in.

=head1 SEE ALSO

The source code of this file of course.

L<Games::Chess>

L<Games::Chess::Coverage::Draw>

L<GD>

=head1 AUTHOR

Gene Boggs E<lt>gene@cpan.orgE<gt>

=head1 COPYRIGHT AND LICENSE

Copyright 2004, Gene Boggs

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself. 

=cut

package Pieces;    # A.K.A. Games::Chess::GD::Pieces
$VERSION = '0.0201';
use strict;
use warnings;
use Carp;
use GD; # libgd-gd2-perl
use Games::Chess qw( :functions );

# Global holder for the piece images to be populated by Games::Chess.
use vars qw( $gifs );

sub Pieces
{
    my ($self, %args) = @_;

    my $c = $self->{coverage}->game->at($args{x}, $args{y})->code;
    return if $c eq ' ';

    # Populate the image hash of piece glyphs if one does not exist.
    $gifs = Games::Chess::Position::piece_gifs unless keys %$gifs;

    # Copy the glyph to the evolving image.
    $self->{image}
      ->copy($gifs->{$c}, $args{left}, $args{top}, 0, 0, $self->{square_width},
             $self->{square_height});
}

1;

