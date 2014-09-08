/*
 * $Id: bt.h,v 1.5 2004-10-05 17:47:56 mark Exp $
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

/* B tree structure header */

#ifndef _btheader_
#define _btheader_
#include <stdio.h>

#include "bc.h"

/*
  B tree cache manager structure
*/
struct _cntrl {
   int inmem;  /* holds block number of in-memory copy */
   int busy;   /* if non-ZERO, block cannot be flushed to disk */
   int writes; /* if non-ZERO, number of writes to this block */
   int lrunxt;  /* index of next in-memory block for LRU queue */
};

typedef struct _cntrl CNTRL;

/* Tail and head of least recently used queue */

struct _lru {
    int lrut;
    int lruh;
};

/*
   B tree in-memory cached blocks
*/

struct _memrec {
   int infblk[ZINFSZ];
   char keyblk[ZMXKEY] [ZKYLEN];
   int valblk[ZMXKEY];
   int lnkblk[ZMXKEY+1];
#if ZPAD != 0
    int padblk[ZPAD];
#endif
};

typedef struct _memrec MEMREC;

/* Structure describing a data block */

struct _datblk {
    int infblk[ZINFSZ];
    char data[ZBLKSZ-(ZINFSZ*ZBPW)];
};

typedef struct _datblk DATBLK;


/* context from last find operation */

struct _lf {
    char lfkey[ZKYLEN];
    int lfblk;
    int lfpos;
    int lfexct;
};

/* B tree statistic counters */

struct _stat {
    int xlogrd;
    int xlogwr;
    int xphyrd;
    int xphywr;
    int xsplit;
    int xjoin;
    int xbal;
    int xgot;
    int xrel;
};

/*  B tree stack */

#define STKMAX 40

struct _stk {
    int stkptr;
    int stk[STKMAX];
};


/* B tree: Super root information plus current root */

struct _super {
    int sblkmx;
    int snfree;
    int sfreep;
    int scroot;
    int smode;
    int smod;
    char scclas[ZKYLEN];
};

/* Common structure for all context information for an index */

struct _cntxt {
    struct _lru lru;
    struct _lf lf;
    struct _stk stk;
    struct _stat stat;
    struct _super super;
};

typedef struct _cntxt CNTXT;

#define FIDSZ 72

struct _btactive {
    FILE *idxunt;
    char idxfid[FIDSZ];
    int fd;                 /* used to hold index file descriptor */
    int lckcnt;             /* re-entrant lock count */
    int shared;
    CNTRL *cntrl;
    MEMREC *memrec;
    CNTXT *cntxt;
};

typedef struct _btactive BTA;

extern BTA btat[];                  /* might not need this if we can access
                                        everything through btact */

extern BTA *btact;                  /* point to active index info */

#endif
