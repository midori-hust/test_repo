/*
 * $Id: bsetbk.c,v 1.8 2010-05-26 12:39:16 mark Exp $
 *
 *
  bsetbk:  sets info array in block

  int bsetbk(int blk,int type,int misc,int nxblk,int nkeys,int nblks)

    blk    block for which information should be set
    type   block type
    misc   misc info
    nxblk  next block
    nkeys  number of active keys
    nblks  total number of blocks in index file

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

#include <stdio.h>
#include "bc.h"
#include "bt.h"
#include "btree_int.h"

int bsetbk(BTint blk,BTint type,BTint misc,BTint nxblk,BTint nkeys,BTint nblks)
{
    int ioerr,idx;
    
    ioerr = brdblk(blk,&idx);
    if (idx < 0) {
        bterr("BSETBK",QRDBLK,itostr(blk));
    }
    else {
        ((btact->memrec)+idx)->infblk[ZBTYPE] =
            (((BTint) ZVERS) << ((ZBPW/2)*ZBYTEW)) | type;
        ((btact->memrec)+idx)->infblk[ZMISC] = misc;
        ((btact->memrec)+idx)->infblk[ZNXBLK] = nxblk;
        ((btact->memrec)+idx)->infblk[ZNKEYS] = nkeys;
        ((btact->memrec)+idx)->infblk[ZNBLKS] = nblks;
        ((btact->cntrl)+idx)->writes++;
    }
    return(0);
}
