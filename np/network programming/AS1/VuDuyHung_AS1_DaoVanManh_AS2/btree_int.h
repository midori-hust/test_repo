/*
 * $Id: btree_int.h,v 1.7 2004-10-05 17:47:56 mark Exp $
 *
 * Btree internal function definitions
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

#include "bt.h"

extern void bclrlf(void);
extern void bclrst(void);
extern int bcpybk(int,int,int,int,int);
extern void bterr(char *,int,char*);
extern int btgerr(void);
extern int bgtinf(int,int);
extern int bgtfre(void);
extern int bgtslt(void);
extern int bleaf(int);
extern int bnxtbk(int *);
extern int bpull(void);
extern int bpush(int);
extern void bstkin(void);
extern int bputky(int,char *,int,int,int);
extern void bqadd(int);
extern int bqhead(void);
extern int bqmove(int);
/* extern void bqrem(int);*/
extern int brdblk(int,int *);
extern int brepky(int,int,char *,int,int,int);
extern int bsetbk(int,int,int,int,int,int);
extern void bsetbs(int,int);
extern int bstinf(int,int,int);
extern int bsptbk(int,int *);
extern int bsrhbk(int,char *,int *,int *,int *,int *,int *);
extern int bwrblk(int);

extern void balblk(void);
extern void balbk1(int,int,int,char *,int);
extern int bdelk1(char *);
extern void bdemte(int *);
extern void bjnblk(int *);
extern void bjoin(int,int,char *,int);
extern void bmkfre(int);
extern void bremky(int,int);

extern BTA *bnewap(char *);
extern int bacini(BTA *);
extern void initcntrl(BTA *);

extern int bvalap(char *,BTA *);
extern void bacfre(BTA *);
extern int brdsup(void);
extern int bwrsup(void);
extern int block(void);
extern int bulock(void);
extern int btsync(void);
extern int bmodky(int,int,int);
extern void bxdump(char *,int);

extern int binsdt(char *,int dsize);
extern int mkdblk(void);
extern int rdsz(char *);
extern unsigned rdint(char *);
extern void wrsz(int,char *);
extern void wrint(unsigned i,char *);
extern int binsdt(char *,int);
extern int insdat(int,char *,int,unsigned);
extern int bupddt(unsigned, char *, int);
extern int bdeldt(unsigned);
extern int deldat(int, int);
extern int bseldt(int, char *, int);
extern int brecsz(unsigned);
extern void cnvdraddr(unsigned, int *, int *);
extern  unsigned mkdraddr(int, int);
extern int getseginfo(unsigned, int *, unsigned *);
extern int dataok(BTA*);

extern void setaddrsize(int);

extern char* itostr(int);
