/*
 * $Id: balbk1.c,v 1.8 2010-05-28 10:34:38 mark Exp $
 *
 * balbk1: balances keys between blocks 
 *
 * Parameters:
 *   lblk   left block of pair 
 *   rblk   right block of pair 
 *   diff   if negative, move diff/2 keys left 
 *          else move diff/2 keys right 
 *   key    name of current parent key for both blocks 
 *   val    value of parent key
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

#include <stdlib.h>
#include <stdio.h>

#include "bc.h"
#include "bt.h"
#include "btree_int.h"

void balbk1(BTint lblk,BTint rblk,int diff,char *key,BTint val)
{

    BTint tblk,fblk,tval,link1,link2;
    int i,dir,keypos,result,limit;
    char tkey[ZKYLEN];

#if DEBUG >= 1
    printf("BALBK1: Balancing keys between lblk: " ZINTFMT ", rblk: " ZINTFMT
           "\n",lblk,rblk);
    printf("        with parent: %s\n",key);
#endif
    if (diff < 0) {
        dir = 1;
        tblk = lblk;
        fblk = rblk;
        keypos = 0; 
        limit = abs(diff/2);
    }
    else {
        dir = -1;
        tblk = rblk;
        fblk = lblk;
        keypos = bgtinf(fblk,ZNKEYS)-1;
        limit = keypos-abs(diff/2);
    }
    /* move parent key into to block */
    bputky(tblk,key,val,ZNULL,ZNULL);
    bremky(btact->cntxt->lf.lfblk,btact->cntxt->lf.lfpos);
    /* move keys from fblk to tblk */
    for (i=keypos;i!=limit;i+=dir) {
        bsrhbk(fblk,tkey,&keypos,&tval,&link1,&link2,&result);
        if (result != 0) {
            bterr("BALBK1",QBALSE,NULL);
            goto fin;
        }
        bremky(fblk,keypos);
        if (dir < 0) keypos--;
        bputky(tblk,tkey,tval,ZNULL,ZNULL);
    }
    /* move last key from fblk into parent */
    i = keypos;
    bsrhbk(fblk,tkey,&keypos,&tval,&link1,&link2,&result);
    if (result != 0) {
        bterr("BALBK1",QBALSE,NULL);
        goto fin;
    }
    bputky(btact->cntxt->lf.lfblk,tkey,tval,lblk,rblk);
    bremky(fblk,keypos);
    btact->cntxt->stat.xbal++;
fin:
    return;
}
