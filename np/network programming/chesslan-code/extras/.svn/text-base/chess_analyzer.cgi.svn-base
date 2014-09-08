#!/usr/bin/perl
# Luis Mondesi <lemsx1@gmail.com>
# 2006-10-12 16:17 EDT
#
# Based on gd_draw from Games::Chess::Coverage eg directory
#

package main;

use lib '/usr/local/lib/site_perl';
use strict;
use warnings;

use CGI qw/:cgi/;

use File::Basename;
use Games::Chess::Coverage;              # cpan
use Games::Chess::Coverage::GD;          # cpan
use Graphics::ColorNames 'hex2tuple';    # libgraphics-colornames-perl

my $DEBUG   = 0;
my $PGN_DIR = '/var/tmp/chess_analyzer';
my $URL_DIR = '/chess_analyzer/';    # defined in Apache as an alias to $PNG_DIR

# TODO add to documentation
# Alias /chess_analyzer "/var/tmp/chess_analyzer"
# <Directory "/var/tmp/chess_analyzer">
#     Order Deny,Allow
#     Allow from all
# </Directory>

my $html = new CGI;

sub _print_form
{

    # note that this assumes we are already in $PGN_DIR
    my @pgn_files = glob("*.pgn");

    # will copy file in $PGN_DIR
    print STDOUT (
                  $html->start_multipart_form('-name' => "form1"),
                  "\n<div id='fileupload'>",
                  $html->p(
                           $html->filefield(
                                            '-name'      => 'uploadpgn',
                                            '-size'      => '30',
                                            '-maxlength' => '255'
                                           )
                          ),
                  "\n</div>\n<div id='pgnpopup'>\n",
                  $html->popup_menu(
                                    '-name'   => "pgn",
                                    '-values' => [@pgn_files]
                                   ),
                  "\n</div>\n<div id='overridecheckbox'>\n",
                  $html->br(),
                  "\n",
                  $html->checkbox(
                                  -name  => 'override',
                                  -label => 'Force'
                                 ),
                  "\n</div>\n<div id='resetbutton'>",
                  $html->br(),
                  "\n",
                  $html->reset("Reset"),
                  "\n</div><div id='selectbutton'>",
                  $html->submit("Select Game"),
                  "\n</div>\n",
                  $html->end_form(),
                  "\n",
                  $html->hr(),
                  "\n",
                 );
}

sub _display_game
{
    my $_checksum = shift;
    my $_filename = shift;
    my $_action   = shift;

    return "" if (!$_checksum);

    #print $html->p("checksum: ".$_checksum);

    # TODO use catpath...
    my $_dir = "$PGN_DIR/generated/$_checksum";
    my $_img = ($_filename) ? "${URL_DIR}generated/$_checksum/" . basename($_filename):"";

    if ($_filename)
    {
        $_filename =~ s#^.*/##;

        #print $html->p("filename: ".$_filename);

        # find next filename and set $_img
        my @files = glob("$_dir/*.gif");
        my $found = 0;

        if ($_action eq "next")
        {
            foreach (@files)
            {
                if ($found)
                {
                    $_img = "${URL_DIR}generated/$_checksum/" . basename($_);
                    last;
                }
                if ($_filename eq basename($_))
                {
                    $found = 1;
                }
            }
        } elsif ( $_action eq "prev" ) {
            my $_last = $files[0];
            foreach (@files)
            {
                if ($_filename eq basename($_))
                {
                    $_img = "${URL_DIR}generated/$_checksum/" . basename($_last);
                    last;
                }
                $_last = $_;
            }
        } elsif ( $_action eq "begin" ) {
            $_img = "${URL_DIR}generated/$_checksum/" . basename($files[0]);
        } elsif ( $_action eq "last" ) {
            $_img = "${URL_DIR}generated/$_checksum/" . basename($files[$#files]);
        }
    }
    else
    {
        my @files = glob("$_dir/*.gif");
        $_img = "${URL_DIR}generated/$_checksum/" . basename($files[0]);
    }

    #print $html->p("img: ".$_img);

    # print Game with proper labels and Ajax/javascript to move to the next
    # game position

    print STDOUT (
        $html->start_multipart_form(
            '-name' => "form2",

            #'-onsubmit' => "move(this)"
                                   ),
        "\n<div id='board'>\n",
        $html->p($html->img({'src' => $_img,})),
        "\n</div>\n<div id='controllers'>\n",
        $html->p(
                     $html->submit('-name' => "<<")
                   . $html->submit('-name' => "<")
                   . $html->submit('-name' => ">")
                   . $html->submit('-name' => ">>")
                ),
        $html->hidden('-name' => "checksum", '-default' => $_checksum),

        # for some reason Perl caches $html->hidden() write directly:
        "<input type='hidden' name='currentimg' value='$_img'/>",
        $html->end_form(),
        "</div> \n",
                 );
}

sub _die
{
    my $msg = shift;
    print $html->p({'class' => 'debugtext'}, $msg);
    print STDERR $msg, "\n";    # apache log
    print $html->end_html();
    exit(1);
}

sub _debug
{
    my $str = shift;
    print $html->p({class => 'debugtext'}, $str)
      if ($DEBUG);
}

my $style = <<EOF;
SELECT,TEXTAREA
{
    font-family : Verdana, "hoefler text", Tahoma, Helvetica, sans-serif;
    font-size : 10pt;
    color : #808080;
    text-decoration : none;
}
BODY
{
    font-family : Verdana, "hoefler text", Tahoma, Helvetica, sans-serif;
    font-size : 11pt;
    color : #808080;
    text-decoration : none;
    background: #ffffff;
}
input {
    border: #000 1px solid;
    margin: 3px;
}
hr {
    color:  #808080;
    height: 1px;
    width: 80%;
}
.template {
    font-family : Arial,Verdana, "hoefler text", Tahoma, Helvetica, sans-serif;
    font-size : 12pt;
    color : #000000;
    text-decoration : none;
    background: #ffffff;
}
.smalltext {
        font-size: 6pt;
        font-family: sans-serif;
}
.errortext {
        font-size: 10pt;
        font-family: sans-serif;
        color: red;
}
.debugtext {
        font-size: 14pt;
        font-family: sans-serif;
        color: red;
}
.successtext {
        font-size: 10pt;
        font-family: sans-serif;
        color: green;
}

EOF

my $jscript = <<EOF;
    function reset_form()
    {
        for (i=0;i<document.form1.elements.length;i++)
        {
            if (document.form1.elements[i].type == "text")
            {
                document.form1.elements[i].value = "foo";
            }
        }
    }
EOF

my $pgn = undef;

print $html->header();
print $html->start_html(
    '-title' => 'Chess Analyzer: A powerful way to visualize Chess',

    '-script' => $jscript,
    '-style'  => {

        #'-src'  => "/styles/style.css",
        '-code' => $style
    }
);

mkdir($PGN_DIR)
  or _die("Could not create work directory $PGN_DIR. $!")
  if (!-d $PGN_DIR);
chdir($PGN_DIR) or _die("Could not change to work directory $PGN_DIR. $!");

_print_form();

if ($html->param() and ($html->param('pgn') or $html->param('uploadpgn')))
{
    _debug("handling upload") if ($html->param('uploadpgn'));
    _debug("handling pgn")    if ($html->param('pgn'));

    # in the event we were sent both, an uploaded file and a file selected from the popup
    # menu, default to using the uploaded file
    if ($html->param('uploadpgn'))
    {
        my $filename = $html->param('uploadpgn');
        $filename = basename($filename);
        $filename =~ s/.*\\([^\\])+$/$1/;    # dos?
                                             # put a .pgn extension
        $filename =~ s/\.[^\.]+$//;
        $filename .= ".pgn";
        open(OUTFILE, ">$PGN_DIR/$filename")
          or _die("Could not create file $filename. $!");
        my $fh = $html->upload('uploadpgn');

        while (<$fh>)
        {
            chomp();
            s/\r|\n//g;                      # deals with DOS
            print OUTFILE ($_, "\n");
        }
        close(OUTFILE);
        close($fh);

        $pgn = $filename;
    }
    elsif ($html->param('pgn'))
    {
        $pgn = $PGN_DIR . '/' . basename($html->param('pgn'));
    }
    else
    {
        _die("No PGN file given");
    }

    $html->p({'class' => 'errortext'}, "Cannot read file " . basename($pgn))
      if (!-r $pgn);

    my %colors;
    tie %colors, 'Graphics::ColorNames';

    my %apply = (    # {{{
        board => sub {
            my $drawing = shift;
            $drawing->add_rule('Pieces');    # FIXME
        },
        draw => sub {
            my $drawing = shift;
            $drawing->add_rule(
                            'Games::Chess::Coverage::GD::Move',
                            white_move_color => [hex2tuple($colors{lightblue})],
                            black_move_color => [hex2tuple($colors{palegreen})],
                            both_move_color  => [hex2tuple($colors{pink})],
            );
            $drawing->add_rule(
                          'Games::Chess::Coverage::GD::Threat',
                          white_threat_color => [hex2tuple($colors{darkblue})],
                          black_threat_color => [hex2tuple($colors{darkgreen})],
            );
        },
        move => sub {
            my $drawing = shift;
            $drawing->add_rule(
                            'Games::Chess::Coverage::GD::Move',
                            white_move_color => [hex2tuple($colors{lightblue})],
                            black_move_color => [hex2tuple($colors{palegreen})],
                            both_move_color  => [hex2tuple($colors{pink})],
            );
        },
        threat => sub {
            my $drawing = shift;
            $drawing->add_rule(
                               'Games::Chess::Coverage::GD::Threat',
                               white_threat_color => [hex2tuple($colors{blue})],
                               black_threat_color => [hex2tuple($colors{red})],
                              );
        },
        arrows => sub {
            my $drawing = shift;
            $drawing->add_rule(
                               'Games::Chess::Coverage::GD::Arrows',
                               white_arrow_color => [hex2tuple($colors{blue})],
                               black_arrow_color => [hex2tuple($colors{red})],
                              );    # Grrr!
        },
    );                              # }}}

    use Digest::MD5 qw(md5_hex);
    my $sum = Digest::MD5->new();

    open(PGN, "< $pgn")
      or _die("Cannot get checksum from file " . basename($pgn));
    binmode(PGN);
    $sum->addfile(*PGN);

    my $_checksum = $sum->hexdigest();

    close(PGN);

    mkdir("$PGN_DIR/generated") if (!-d "$PGN_DIR/generated");
    my $dir = "$PGN_DIR/generated/$_checksum";
    if (!-d $dir)
    {
        mkdir($dir) or _die("Cannot make directory $dir. $!\n");

        my $cover =
          Games::Chess::Coverage->new(verbose => $DEBUG,
                                      pgn     => $pgn);

        _die("No games in $pgn\n") if ($cover->number_of_games < 1);

        # FIXME handle many games in PGN file
        _die("Too many games in $pgn\n") if ($cover->number_of_games > 1);

        my $action = "board";
        my $i      = 0;
        for my $game (1 .. $cover->number_of_games)
        {
            my $j = 0;

            #foreach my $action (keys %apply)
            {
                for my $ply (0 .. $cover->number_of_ply($game))
                {
                    $cover->build_game($game, $ply);
                    my $drawing =
                      Games::Chess::Coverage::GD->new(
                                                      verbose  => $DEBUG,
                                                      coverage => $cover,
                                                      out_file => "$dir/"
                                                        . sprintf('%03d', $i)
                                                        . sprintf('%03d', $j),
                                                      image_type => 'gif',
                                                     );
                    {    # all our actions need a board
                        $drawing->add_rule(
                            'Games::Chess::Coverage::GD::Board',
                            board_color => [hex2tuple($colors{white})]
                            ,    #[00,00,00]
                            border       => 2,
                            border_color => [hex2tuple($colors{black})]
                            ,    #[255,255,255]
                            letters      => 1,
                            letter_color => [hex2tuple($colors{blue})]
                            ,    #[0,0,255]
                            grid       => 1,
                            grid_color => [hex2tuple($colors{grey})]
                            ,    #[127,127,127]
                                          );
                    }
                    $apply{$action}->($drawing);
                    $drawing->draw;
                    $drawing->write;
                    $j++;
                }
            }
            $i++;
        }
    }
    else
    {

        # TODO _warn("PGN file $pgn has already been generated. Use Force checkbox to redo");
        print;
    }

    _display_game($_checksum);
}
elsif ($html->param() and ($html->param('>')))
{
    _display_game($html->param('checksum'), $html->param('currentimg'), "next");
}
elsif ($html->param() and ($html->param('<')))
{
    _display_game($html->param('checksum'), $html->param('currentimg'), "prev");
}
elsif ($html->param() and ($html->param('<<')))
{
    _display_game($html->param('checksum'), $html->param('currentimg'), "begin");
}
elsif ($html->param() and ($html->param('>>')))
{
    _display_game($html->param('checksum'), $html->param('currentimg'), "last");
}
else
{
    _debug("No parameters");
}
print $html->end_html();

=pod

=head1 NAME

Chess_analyzer - Analyzes various aspects of a given chess game in a PGN file

=head1 DESCRIPTION

This is inspired from the C<gd_draw> example script. You should be able to run this
from a webserver. You will need a web browser with JScript (javascript) turned on.

=head1 SEE ALSO

L<Games::Chess>

L<Games::Chess::Coverage::Draw>

L<Games::Chess::Coverage>

=head1 AUTHOR

Luis Mondesi E<lt>lemsx1@gmail.comE<gt>

=head1 COPYRIGHT AND LICENSE

Copyright 2006, Luis Mondesi

This code is free software; you can redistribute it and/or modify
it under the same terms as Perl itself. 

=cut

