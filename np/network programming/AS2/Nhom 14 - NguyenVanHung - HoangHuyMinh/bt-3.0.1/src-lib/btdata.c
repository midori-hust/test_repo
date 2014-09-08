/*
 * $Id: btdata.c,v 1.21 2010-06-01 19:04:29 mark Exp $
 *
 *  NAME
 *      btdata.c - handles data storage and retrieval from index files
 *
 *  DESCRIPTION
 *      These routines allow a btree to store and retrieve binary
 *      data, associated with a key.  This is a continuing
 *      development, and documentation will be enhanced in line with
 *      the code.
 *
 *  NOTES
 *      Data blocks will be returned to the free list only when they
 *      are completely empty.  No attempt is made to reclaim space
 *      when a data record is deleted.  However when all the segments
 *      in a block have been deleted, the entire block is returned to
 *      the free list.  This strategy means that a btree database is
 *      likely to grow over time.  To clean up a btree database and
 *      recover all wasted space, it must be copied to a new (and
 *      empty) btree database.
 *
 *      A data record address is held in a ZBPW byte field (as this is
 *      the maximum size of a data value stored with a key in the
 *      btree index), in the following format (for a 32 bit int,
 *      i.e. 4 bytes per word where bytes are 8 bits):
 *      
 *      31                                             0
 *      +----------------------------+-----------------+
 *      |   block number             | byte offset     |
 *      +----------------------------+-----------------+
 *
 *      With the default block size of 1024 bytes, the byte offset is
 *      10 bits wide, while the block number field is 22 bits wide.
 *
 *      Note for implementations where the default int size is not 32
 *      bits (e.g. 16 bits), the amount left for the block
 *      number is only 6 bits (127 blocks).  This limits the amount of
 *      data that can be stored significantly.
 *
 *      The field widths for the block number and offset are
 *      calculated from the block size when the btree library is
 *      initialised.
 *
 *      If a data record will not fit into a block, it is split into
 *      segments, sized to fit the data block.
 *      
 *      Each data segment is prefixed by ZDOVRH bytes of information
 *      (six bytes for a 32 bit int implementation).  These are used
 *      as follows:
 *
 *          Bytes 1 and 2: the size of the data segment in bytes
 *          (maximum size of a data segment is therefore 65536 bytes)
 *          
 *          Bytes 3-6: address of the next segment of this data record
 *          (0 if the last (or only) segment).
 *          
 *
 *  MODIFICATION HISTORY
 *  Mnemonic    Release Date    Who
 *  DT-ALPHA    1.0     010605  mpw
 *      Created.
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
#include <string.h>

#include "bc.h"
#include "bt.h"
#include "btree.h"
#include "btree_int.h"


/* #undef DEBUG */
/* #define DEBUG 1 */


/*------------------------------------------------------------------------
 * The btins routine will insert key and an associated data record
 * into a btree database.
 *
 *      BTA *b      btree context handle
 *      char *key   pointer to key string
 *      char *data  pointer to data
 *      int dsize   size of data record (in bytes)
 *
 * btins returns 0 if no errors encountered, error code otherwise.
 *------------------------------------------------------------------------
 */

int btins(BTA *b,char *key, char *data, int dsize)
{
    int status;
    BTint draddr = 0;
    BTint dontcare;

    bterr("",0,NULL);
    if ((status=bvalap("BTINS",b)) != 0) return(status);

    btact = b;  /* set context pointer */
    
    if (!dataok(btact)) {
        bterr("BTINS",QDAERR,NULL);
        goto fin;
    }
        
    if (btact->shared) {
        if (!block()) {
            bterr("BTINS",QBUSY,NULL);
            goto fin;
        }
    }

    /* does key already exist? */
    status = bfndky(btact,key,&dontcare);
    if (status == 0) {
        bterr("BTINS",QDUP,NULL);
        goto fin;
    }
    else if (status != QNOKEY) {
        goto fin;
    }

    /* clear error code */
    bterr("",0,NULL);
    
    /* insert data in btree if record has zero or more bytes*/
    if (dsize >= 0) {
        draddr = binsdt(data,dsize);
        if (draddr != ZNULL) {
            if (draddr < 0) {
                bterr("BTINS",QDRANEG,itostr(draddr));
                goto fin;
            }
            status = binsky(btact,key,draddr);
            if (status != 0){
                /* can't insert new key, therefore must delete data */
                status = bdeldt(draddr);
            }
        }
    }
    else {
        bterr("BTINS",QDNEG,NULL);
    }
    
fin:
    if (btact->shared) bulock();
    return(btgerr());
}

/*------------------------------------------------------------------------
 * The btupd routine will update the data record associated with a
 * key in the btree database.
 *
 *      BTA *b      btree context handle
 *      char *key   pointer to key string
 *      char *data  pointer to data
 *      int dsize   size of data record (in bytes)
 *
 * btupd returns 0 if no errors encountered, error code otherwise.
 *------------------------------------------------------------------------
 */

int btupd(BTA *b,char *key, char *data, int dsize)
{
    BTint draddr;
    int status, result;

    bterr("",0,NULL);
    if ((result=bvalap("BTUPD",b)) != 0) return(result);

    if (dsize < 0) {
        bterr("BTUPD",QDNEG,NULL);
        return QDNEG;
    }

    btact = b;      /* set context pointer */

    if (!dataok(btact)) {
        bterr("BTUPD",QDAERR,NULL);
        goto fin;
    }
    
    if (btact->shared) {
        if (!block()) {
            bterr("BTUPD",QBUSY,NULL);
            goto fin;
        }
    }

    /* find key in btree */
    status = bfndky(btact,key,&draddr);
    if (status != 0) goto fin;

    /* update data in btree */
    status = bupddt(draddr,data,dsize);

fin:
    if (btact->shared) bulock();
    return(btgerr());
}

/*------------------------------------------------------------------------
 * The btsel routine will return the data record associated with a
 * key in the btree database.
 *
 *      BTA *b      btree context handle
 *      char *key   pointer to key string
 *      char *data  pointer to data recipient location
 *      int dsize   size of data record expected (in bytes)
 *      int *size   size of data record actually return (in bytes)
 *                  No more than dsize bytes will be returned.
 *
 * btsel returns 0 if no errors encountered, error code otherwise.
 *------------------------------------------------------------------------
 */

int btsel(BTA *b,char *key, char *data, int dsize,int *rsize)
{
    BTint draddr;
    int status, result;

    bterr("",0,NULL);
    if ((result=bvalap("BTSEL",b)) != 0) return(result);

    btact = b;      /* set context pointer */

    if (!dataok(btact)) {
        bterr("BTSEL",QDAERR,NULL);
        goto fin;
    }
    
    if (btact->shared) {
        if (!block()) {
            bterr("BTSEL",QBUSY,NULL);
            goto fin;
        }
    }

    /* find key in btree */
    status = bfndky(btact,key,&draddr);
    if (status != 0) goto fin;

    if (draddr < 0) {
        bterr("BTSEL",QDRANEG,itostr(draddr));
        goto fin;
    }

    /* retrieve data from btree */
    *rsize = bseldt(draddr,data,dsize);

fin:
    if (btact->shared) bulock();
    return(btgerr());
}

/*------------------------------------------------------------------------
 * The btdel routine will remove the data record associated with a
 * key in the btree database.
 *
 *      BTA *b      btree context handle
 *      char *key   pointer to key string
 *
 * btdel returns 0 if no errors encountered, error code otherwise.
  *------------------------------------------------------------------------
 */

int btdel(BTA *b,char *key)
{
    BTint draddr;
    int status, result;

    bterr("",0,NULL);
    if ((result=bvalap("BTDEL",b)) != 0) return(result);

    btact = b;      /* set context pointer */

    if (!dataok(btact)) {
        bterr("BTDEL",QDAERR,NULL);
        goto fin;
    }

    if (btact->shared) {
        if (!block()) {
            bterr("BTDEL",QBUSY,NULL);
            goto fin;
        }
    }

    /* find key in btree */
    status = bfndky(btact,key,&draddr);
    if (status != 0) goto fin;

    /* delete data record first */
    status = bdeldt(draddr);
    if (status == 0) {
        status = bdelky(btact,key);
    }

fin:
    if (btact->shared) bulock();
    return(btgerr());
}

/*------------------------------------------------------------------------
 * btseln will return the next key and data record following a
 * successful return from a previous call to the Btsel function.
 *------------------------------------------------------------------------
 */

int btseln(BTA *b,char *key, char *data, int dsize,int *rsize)
{
    BTint draddr;
    int status, result;

    bterr("",0,NULL);
    if ((result=bvalap("BTSELN",b)) != 0) return(result);

    btact = b;      /* set context pointer */

    if (!dataok(btact)) {
        bterr("BTSELN",QDAERR,NULL);
        goto fin;
    }

    if (b->shared) {
        if (!block()) {
            bterr("BTSELN",QBUSY,NULL);
            goto fin;
        }
    }

    /* return next key in btree */
    status = bnxtky(btact,key,&draddr);
    if (status != 0) goto fin;

    /* TBD check for valid data pointer */

    /* retrieve data from btree */
    *rsize = bseldt(draddr,data,dsize);

fin:
    if (btact->shared) bulock();
    return(btgerr());
}

/*------------------------------------------------------------------------
 * Btrecs will return the total record size of the data record
 * associated with a given key.  This value may be used by the client
 * application to acquire sufficient memory to retrieve the record.
 *
 *------------------------------------------------------------------------
 */

int btrecs(BTA *b, char *key, int *rsize)
{
    BTint draddr;
    int status, result;

    bterr("",0,NULL);
    if ((result=bvalap("BTRECS",b)) != 0) return(result);

    btact = b;      /* set context pointer */

    if (!dataok(btact)) {
        bterr("BTRECS",QDAERR,NULL);
        goto fin;
    }
    
    if (btact->shared) {
        if (!block()) {
            bterr("BTRECS",QBUSY,NULL);
            goto fin;
        }
    }
 
    status = bfndky(btact,key,&draddr);
    if (status != 0) goto fin;

    *rsize = brecsz(draddr);

  fin:
    if (btact->shared) bulock();
    return(btgerr());
}


/*========================================================================
 * INTERNAL ROUTINES
 *========================================================================
 */

/*------------------------------------------------------------------------
 * bseldt will retrieve data record at address held in draddr.  A maximum
 * of dsize bytes will be retrieved.  If the actual number of bytes in
 * the data record is less than dsize bytes, the actual value is
 * returned, otherwise dsize is returned.
 *
 * Data is copied into the memory array pointed to by the data
 * character pointer.
 * 
 *------------------------------------------------------------------------
 */

int bseldt(BTint draddr, char *data, int dsize) 
{
    BTint dblk;
    int status, idx,
        segsz = 0, cpsz = -1;
    int offset = 0;
    int totsz = 0;
    int sprem = dsize;
    
    DATBLK *d;

    while (sprem > 0 && draddr != 0) {
        /* unpick data pointer */
        cnvdraddr(draddr,&dblk,&offset);

        if (bgtinf(dblk,ZBTYPE) != ZDATA) {
            bterr("BSELDT",QNOTDA,itostr(dblk));
            totsz = -1;
            goto fin;
        }

        status = brdblk(dblk,&idx);
        d = (DATBLK *) (btact->memrec)+idx;
#if DEBUG > 0
        fprintf(stderr,"BSELDT: Using draddr 0x " ZXFMT " (" ZINTFMT
                ",%d), found 0x " ZXFMT "\n",
                draddr,dblk,offset,*(d->data+offset+ZDOVRH));
#endif

        segsz = rdsz(d->data+offset);
        draddr = rdint(d->data+offset+ZDRSZ);
#if DEBUG > 0
        fprintf(stderr,"BSELDT: Seg size: %d, next draddr: 0x" ZXFMT "\n",
                segsz,draddr);
#endif
        cpsz = (segsz>sprem)?sprem:segsz;
#if DEBUG > 0
        fprintf(stderr,"BSELDT: copying %d bytes\n",cpsz);
#endif      
        memcpy(data,d->data+offset+ZDOVRH,cpsz);
        data += cpsz;
        sprem -= cpsz;
        totsz += cpsz;
    }
    
fin:
    return(totsz);
}

int bdeldt(BTint draddr)
{
    BTint dblk;
    int status, size, offset;

    while (draddr != 0) {
        /* unpick data pointer */
        cnvdraddr(draddr,&dblk,&offset);
    
        if (bgtinf(dblk,ZBTYPE) != ZDATA) {
            bterr("BDELDT",QNOTDA,NULL);
            return(QNOTDA);
        }
        getseginfo(draddr,&size,&draddr);
    
        status = deldat(dblk,offset);
    }
    
    return(status);
}

/*------------------------------------------------------------------------
 * bupddt will update an existing data record with a new record.
 * Existing segments are reused.  If new segments are required, they
 * are attached to the existing segment chain. If the new data record
 * is smaller than the old, excess segments are deleted.
 * 
 * The function returns 0 for success, error code otherwise.
 *------------------------------------------------------------------------
 */

int bupddt(BTint draddr, char *data, int dsize) 
{
    BTint dblk;
    int status, idx, segsz, cpsz = ZNULL;
    int offset;
    int freesz;
    int remsz = dsize;
        
    DATBLK *d;

    while (draddr != 0 && remsz >= 0) {
        /* unpick blk/offset pointer */
        cnvdraddr(draddr,&dblk,&offset);
#if DEBUG > 0
        fprintf(stderr,"BUPDDT: processing blk: " ZINTFMT ", offset: %d\n",
                dblk,offset);
#endif      
        if (bgtinf(dblk,ZBTYPE) != ZDATA) {
            bterr("BUPDDT",QNOTDA,NULL);
            goto fin;
        }
        getseginfo(draddr,&segsz,&draddr);

        status = brdblk(dblk,&idx);
        d = (DATBLK *) (btact->memrec)+idx;

        cpsz = ((segsz>remsz)?remsz:segsz);
#if DEBUG > 0
        fprintf(stderr,"BUPDDT: Old seg: %d, new seg: %d\n",segsz,cpsz);
#endif
        memcpy(d->data+offset+ZDOVRH,data,cpsz);
        ((btact->cntrl)+idx)->writes++;
        if (cpsz == remsz) {
            /* last (or only) segment */
            wrsz(cpsz,d->data+offset);
            wrint(0,d->data+offset+ZDRSZ);
            /* update free space in block */
            freesz = bgtinf(dblk,ZMISC);
            freesz += (segsz-cpsz);
            bstinf(dblk,ZMISC,freesz);
            if (cpsz == 0) remsz = -1;
        }
        remsz -= cpsz;
        data += cpsz;
    }
    if (draddr != 0) {
        /* new data record is smaller than original, need to free
         * remaining segments
         */
        bdeldt(draddr);
    }
    else if (remsz > 0) {
        /* new data record is larger, need new segments for rest of record
         */
        draddr = binsdt(data,remsz);
        if (draddr == ZNULL) {
            /* no more blocks; force this to be last segment */
            draddr = 0;
        }
        /* insert returned data address into original last segment */
        status = brdblk(dblk,&idx);
        d = (DATBLK *) (btact->memrec)+idx;
        wrint(draddr,d->data+offset+ZDRSZ);
        ((btact->cntrl)+idx)->writes++;
    }
    
fin:
    return(btgerr());
}

/*------------------------------------------------------------------------
 * binsdt takes a data record, of length dsize, and copies it into 
 * one or more data blocks.  Data records are split into segments,
 * when a data record is too large to fit into one data block.
 *
 * Segments are stored in reverse order, to make it easier to
 * reconstitute the original record on retrieval.
 *
 * binsdt returns the data record address of the first segment, or
 * ZNULL if the record could not be stored.
 *------------------------------------------------------------------------
 */

BTint binsdt(char *data, int dsize)
{
    BTint dblk, nblk;
    int offset;
    char *segptr = data+dsize;
    int remsize = dsize;
    BTint segaddr = 0;
    int freesz;

    /* ensure there is an active data block */
    dblk = bgtinf(btact->cntxt->super.scroot,ZNXBLK);
    if (dblk == ZNULL) {
        dblk = mkdblk();
        if (dblk == ZNULL) {
            bterr("BINSDT",QNOBLK,NULL);
            goto fin;
        }
        bstinf(btact->cntxt->super.scroot,ZNXBLK,dblk);
    }

    /* sanity check; is this a data block? */
    if (bgtinf(dblk,ZBTYPE) != ZDATA) {
        bterr("BINSDT",QNOTDA,itostr(dblk));
        goto fin;
    }

    /* process the data record */
    while (remsize >= 0) {
        /* free size is space left from first free byte onwards */
        freesz = (ZBLKSZ-(ZINFSZ*ZBPW))-bgtinf(dblk,ZNKEYS);
        if (freesz >= remsize+ZDOVRH) {
            /* segment fits in active block */
            segptr -= remsize;
            offset = insdat(dblk,segptr,remsize,segaddr);
            remsize = -1;
        }
        else if (freesz < (ZDOVRH+ZDSGMN)) {
            /* space below min seg size; need new block */
            nblk = mkdblk();
            if (nblk == ZNULL) {
                bterr("BINSDT",QNOBLK,NULL);
                goto fin;
            }
            /* maintain double-linked list of data blocks to allow
             * blocks to be returned to the free list, without
             * destroying the data block chain for this root.
             */
            bstinf(nblk,ZNXBLK,dblk);
            bstinf(dblk,ZNBLKS,nblk);
            
            dblk = nblk;
            /* new data list head */
            bstinf(btact->cntxt->super.scroot,ZNXBLK,dblk); 

        }
        else {
            /* determine beginning of segment and store */
            freesz -= ZDOVRH;
            segptr -= freesz;
            offset = insdat(dblk,segptr,freesz,segaddr);
            segaddr = mkdraddr(dblk,offset);
            remsize -= freesz;
        }
    }

    if (offset == ZNULL) goto fin;
    return(mkdraddr(dblk,offset));
    
  fin:
    return(ZNULL);
}

int deldat(BTint blk,int offset) 
{
    int status, freesz, size, idx;
    BTint pblk, nblk;
    
    DATBLK *d;

    status = brdblk(blk,&idx);
    if (status != 0) {
        return(status);
    }
    freesz = bgtinf(blk,ZMISC);
    d = (DATBLK *) (btact->memrec)+idx;
    size = rdsz(d->data+offset);
    freesz += (size+ZDOVRH);
#if DEBUG > 0
    fprintf(stderr,"Deleting segment: blk " ZINTFMT ", offset: %d\n",
            blk,offset);
    fprintf(stderr,"seg size: %d, free space now = %d, free target = %d\n",
            size,freesz,ZBLKSZ-(ZINFSZ*ZBPW));
#endif  
    if (freesz == ZBLKSZ-(ZINFSZ*ZBPW)) {
        bstinf(blk,ZMISC,freesz);
        bstinf(blk,ZNKEYS,0);   /* reset offset pointer */          
        /* no data left in this block; can remove this block from the
         * active data block list */
        pblk = bgtinf(blk,ZNBLKS);
        nblk = bgtinf(blk,ZNXBLK);
        if (nblk != ZNULL) bstinf(nblk,ZNBLKS,pblk);
        if (pblk != ZNULL) bstinf(pblk,ZNXBLK,nblk);
        bmkfre(blk);
        if (blk == bgtinf(btact->cntxt->super.scroot,ZNXBLK)) {
            /* no active data block now */
            bstinf(btact->cntxt->super.scroot,ZNXBLK,ZNULL);
        }
    }
    else if (freesz < 0 || freesz > ZBLKSZ-(ZINFSZ*ZBPW)) {
        /* shouldn't have a negative count or greater than max free
         * space*/
        bterr("DELDAT",QNEGSZ,itostr(freesz));
    }
    else {
        bstinf(blk,ZMISC,freesz);
    }
    return (0);
}

int insdat(BTint blk,char *data, int dsize, BTint prevseg)
{
    int offset;
    int status, idx, freesz;
    DATBLK *d;

    offset = bgtinf(blk,ZNKEYS);
    status = brdblk(blk,&idx);
    d = (DATBLK *) (btact->memrec)+idx;
    wrsz(dsize,d->data+offset);
    wrint(prevseg,d->data+offset+ZDRSZ);
#if DEBUG > 0
    fprintf(stderr,"writing segment at block " ZINTFMT
            ", offset %d, of size %d\n",blk,offset,dsize);
#endif  
    memcpy(d->data+offset+ZDOVRH,data,dsize);
    ((btact->cntrl)+idx)->writes++;
    bstinf(blk,ZNKEYS,offset+ZDOVRH+dsize);
    freesz = bgtinf(blk,ZMISC);
    bstinf(blk,ZMISC,freesz-(ZDOVRH+dsize));
    return(offset);
}
/*-----------------------------------------------------------
 * return number of bytes occupied by data record pointed to by draddr
 * ----------------------------------------------------------
 */

int brecsz(BTint draddr)
{
    BTint blk,newdraddr;
    int offset, segsz, recsz;
    
    recsz = 0;
    while (draddr != 0) {
        cnvdraddr(draddr,&blk,&offset);
#if DEBUG > 0
        fprintf(stderr,"BRECSZ: Processing draddr: 0x" ZXFMT ", blk: " ZINTFMT
                ", offset: %d\n",draddr,blk,offset);
#endif
        /* ensure we are pointing at a data block */
        if (bgtinf(blk,ZBTYPE) != ZDATA) {
            bterr("BRECSZ",QNOTDA,itostr(blk));
            return(0);
        }
        getseginfo(draddr,&segsz,&newdraddr);
        
#if DEBUG > 0       
        fprintf(stderr,"BRECSZ: Seg size: %d, next seg: 0x" ZXFMT "\n",
                segsz,newdraddr);
#endif      
        if (newdraddr == draddr) {
            /* next segment address should never refer to current
               segment */
            bterr("BRECSZ",QDLOOP,NULL);
            return(0);
        }
        draddr = newdraddr;
        recsz += segsz;
    }
    return(recsz);
}

/*-----------------------------------------------------------
 * create a new data block from free list (or thin air)
 * ----------------------------------------------------------
 */

BTint mkdblk(void)
{
    BTint blk;

    blk = bgtfre();
    if (blk != ZNULL ) {
        /* check if block is addressable with implementation word
           length and block offset width */
        if (mkdraddr(blk,0) == 0) {
            bterr("MKDBLK",QDAOVR,itostr(blk));
            return(ZNULL);
        }
        /* data block info set as follows:
           0 - block type
           1 - number of free bytes in block
           2 - pointer to next data block in data block chain
           3 - offset of first free byte within data area of block (0)
           4 - pointer to previous data block in block chain
        */
        bsetbk(blk,ZDATA,ZBLKSZ-(ZINFSZ*ZBPW),ZNULL,0,ZNULL);
        return(blk);
    }
    return(ZNULL);
}

int rdsz(char *a)
{
    int s;

    s = *a++ & 0xff;
    s |= (*a & 0xff) << 8;
    return (s);
}

BTint rdint(char *a)
{
    BTint i = 0;
    int k;

    for (k=0;k<ZBPW;k++) {
        i |= ((BTint) (*a++ & 0xff)) << ZBYTEW*k;
    }
    return(i);
}

void wrsz(int i, char *a)
{
    short s;

    s = i;
    *a++ = s & 0xff;
    *a = (s>>8) & 0xff;
}

void wrint(BTint i, char *a)
{
    int k;

    for (k=0;k<ZBPW;k++) {
        *a++ = (i >> ZBYTEW*k) & 0xff;
    }
}

BTint offsetmask;                 /* used to mask out block number
                                 * from data address */
int offsetwidth;                /* number of bits needed to offer data
                                 * block segment offset */

/*-----------------------------------------------------------------------
 * Determine and save data block addressing, based on block size
 * Redundant (as of 20100525)
 *---------------------------------------------------------------------*/

void setaddrsize(BTint blksz)
{
    int width = 0;
    offsetmask = blksz-1;
    while (blksz>>=1) width++;
    offsetwidth = width;
}

/*------------------------------------------------------------------------
 * Convert data block address into block number and offset
 * Assumes ZBLKSZ is a power of 2
 *----------------------------------------------------------------------*/

void cnvdraddr(BTint draddr, BTint *dblk, int *offset)
{
    *dblk = draddr/ZBLKSZ;
    *offset = draddr & (ZBLKSZ-1);
}

/*------------------------------------------------------------------------
 * Convert data block number and data offset to draddr value
 * Assumes ZBLKSZ is a power of 2
 *----------------------------------------------------------------------*/

BTint mkdraddr(BTint dblk, int offset)
{
    BTint draddr = dblk*ZBLKSZ | offset;
    return draddr;
}

/*------------------------------------------------------------------------
 * Return size and next segment address of data record segment
 * indicated by draddr
 *----------------------------------------------------------------------*/

int getseginfo(BTint draddr, int *size, BTint *nextseg) 
{
    BTint blk;
    int offset;
    int status,  idx;
    DATBLK *d;

    cnvdraddr(draddr,&blk,&offset);
    
    status = brdblk(blk,&idx);
    if (status != 0) {
        return(status);
    }

    d = (DATBLK *) (btact->memrec)+idx;
    *size = rdsz(d->data+offset);
    *nextseg = rdint(d->data+offset+ZDRSZ);
    return(0);
}

/* -----------------------------------------------------------------------
 * Validate if the current root permits storage of data records
 * -----------------------------------------------------------------------
 */
int dataok(BTA* b)
{
    if (b->cntxt->super.scroot == ZSUPER)
        return FALSE;
    else
        return TRUE;
}




