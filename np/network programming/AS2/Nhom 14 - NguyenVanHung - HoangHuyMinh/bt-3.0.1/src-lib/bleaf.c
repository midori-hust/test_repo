/*
 * $Id: bleaf.c,v 1.7 2010-05-26 12:39:16 mark Exp $
 *
 *
 * bleaf: position to left or right-most leaf block from current position
 *
 * Parameters:
 *   dir    direction (0 for left, 1 for right)
 *
 * Copyright (C) 2003, 2004 Mark Willson.
 *
 * This file is part of the B Tree library.
 *
 * The B Tree library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * The B Tree library  is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the B Tree library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#include "bc.h"
#include "bt.h"
#include "btree_int.h"

int bleaf(int dir)
{
    int idx,ioerr;

    ioerr = brdblk(btact->cntxt->lf.lfblk,&idx);
    if (idx < 0) {
        bterr("BLEAF",QRDBLK,itostr(btact->cntxt->lf.lfblk));
    }
    else {
        if (bgtinf(btact->cntxt->lf.lfblk,ZNKEYS) == 0) return 0;
        while (((btact->memrec)+idx)->lnkblk[btact->cntxt->lf.lfpos] != ZNULL) {
            bpush(btact->cntxt->lf.lfblk);
            bpush(btact->cntxt->lf.lfpos);
            btact->cntxt->lf.lfblk = 
                ((btact->memrec)+idx)->lnkblk[btact->cntxt->lf.lfpos];
            ioerr = brdblk(btact->cntxt->lf.lfblk,&idx);
            if (idx < 0) {
                bterr("BLEAF",QRDBLK,itostr(btact->cntxt->lf.lfblk));
                break;
            }
            if (dir == 0) 
                /* proceed to leftmost leaf  */
                btact->cntxt->lf.lfpos = 0;
            else {
                /* proceed to rightmost leaf */
                 btact->cntxt->lf.lfpos = bgtinf(btact->cntxt->lf.lfblk,ZNKEYS);
            }
        }
    }
    /* if proceeding right, ensure we point at last key */
    if (dir == 1) btact->cntxt->lf.lfpos--;
    return(0);
}
