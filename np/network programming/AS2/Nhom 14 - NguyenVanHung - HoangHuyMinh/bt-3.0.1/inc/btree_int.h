/*
 * $Id: btree_int.h,v 1.9 2010-05-27 19:56:44 mark Exp $
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
extern int bcpybk(BTint,BTint,int,int,int);
extern void bterr(char *,int,char*);
extern int btgerr(void);
extern BTint bgtinf(BTint,int);
extern BTint bgtfre(void);
extern int bgtslt(void);
extern int bleaf(int);
extern int bnxtbk(BTint *);
extern BTint bpull(void);
extern int bpush(BTint);
extern void bstkin(void);
extern int bputky(BTint,char *,BTint,BTint,BTint);
extern void bqadd(int);
extern int bqhead(void);
extern int bqmove(int);
/* extern void bqrem(int);*/
extern int brdblk(BTint,int *);
extern int brepky(BTint,int,char *,BTint,BTint,BTint);
extern int bsetbk(BTint,BTint,BTint,BTint,BTint,BTint);
extern void bsetbs(BTint,int);
extern int bstinf(BTint,int,BTint);
extern int bsptbk(BTint,BTint *);
extern int bsrhbk(BTint,char *,int *,BTint *,BTint *,BTint *,int *);
extern int bwrblk(BTint);

extern void balblk(void);
extern void balbk1(BTint,BTint,int,char *,BTint);
extern int bdelk1(char *);
extern void bdemte(BTint *);
extern void bjnblk(BTint *);
extern void bjoin(BTint,BTint,char *,BTint);
extern void bmkfre(BTint);
extern void bremky(BTint,int);

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
extern int bmodky(BTint,int,BTint);
extern void bxdump(char *,int);

extern BTint mkdblk(void);
extern int rdsz(char *);
extern BTint rdint(char *);
extern void wrsz(int, char *);
extern void wrint(BTint, char *);
extern BTint binsdt(char *,int);
extern int insdat(BTint,char *,int,BTint);
extern int bupddt(BTint, char *, int);
extern int bdeldt(BTint);
extern int deldat(BTint, int);
extern int bseldt(BTint, char *, int);
extern int brecsz(BTint);
extern void cnvdraddr(BTint, BTint *, int *);
extern  BTint mkdraddr(BTint, int);
extern int getseginfo(BTint, int *, BTint *);
extern int dataok(BTA*);

extern void setaddrsize(BTint);

extern char* itostr(BTint);

