// generated 2006/10/14 15:24:36 EDT by luigi@tuxy.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to menubar1.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _MENUBAR1_HH
#  include "menubar1_glade.hh"
#  define _MENUBAR1_HH
class menubar1 : public menubar1_glade
{  
public:
        
        menubar1(GlademmData *gmm_data) : menubar1_glade(gmm_data)
        {  
        }
private:
        
        void on_new1_activate();
        void on_open1_activate();
        void on_save1_activate();
        void on_save_as1_activate();
        void on_quit1_activate();
        void on_preferences1_activate();
        void on_about1_activate();
};
#endif
