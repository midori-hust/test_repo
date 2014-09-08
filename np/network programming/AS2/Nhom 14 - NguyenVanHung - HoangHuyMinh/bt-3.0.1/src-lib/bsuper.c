/*
 * $Id: bsuper.c,v 1.9 2010-07-01 09:43:51 mark Exp $
 *
 *
 * brdsup  - reads super root
 * bwrsup  - writes super root
 *
 * Both return 0 for success, error code otherwise
 * 
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

/* get super root from disk */
int brdsup()
{
    int ioerr,idx;

    ioerr = brdblk(ZSUPER,&idx);
    if (ioerr != 0) {
        bterr("BRDSUP",QRDSUP,(ioerr<0)?"(EOF?)":"");
        goto fin;
    } 
    if (bgtinf(ZSUPER,ZBTYPE) != ZROOT) {
        bterr("BRDSUP",QSRNR,NULL);
        ioerr = QSRNR;
        goto fin;
    }
    if (bgtinf(ZSUPER,ZBTVER) != ZVERS) {
        bterr("BRDSUP",QBADVR,itostr(ZVERS));
        ioerr = QBADVR;
        goto fin;
    }
    
    /* retain free list pointers et al */
    btact->cntxt->super.snfree = bgtinf(ZSUPER,ZMISC);
    btact->cntxt->super.sfreep = bgtinf(ZSUPER,ZNXBLK);
    btact->cntxt->super.sblkmx = bgtinf(ZSUPER,ZNBLKS);
    return(0);
fin:
    return(ioerr);
}

/* update super root on disk */
int bwrsup()
{
    int ioerr,idx;
    BTint nkeys;

    ioerr = brdblk(ZSUPER,&idx);
    if (ioerr != 0) {
        bterr("BWRSUP",QRDSUP,itostr(ZSUPER));
        goto fin;
    }
    nkeys = bgtinf(ZSUPER,ZNKEYS);
    bsetbk(ZSUPER,ZROOT,btact->cntxt->super.snfree,
        btact->cntxt->super.sfreep,
        nkeys,
        btact->cntxt->super.sblkmx);
    ioerr = bwrblk(ZSUPER);
    if (ioerr != 0) {
        bterr("BWRSUP",QWRSUP,itostr(ZSUPER));
        goto fin;
    }
    return(0);
fin:
    return(ioerr);
}
