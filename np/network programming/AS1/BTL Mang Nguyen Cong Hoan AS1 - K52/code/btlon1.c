#include <stdio.h> 
#include <string.h> 
#include "inc/btree.h" 
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

/*----------------------*_*-----------------------*/

//btree1
typedef struct 
{ 
   char key[40];
   char value[300]; 
} dict1;

//btree2
typedef struct 
{ 
   char key[60][30];
   char value[60][200]; 
   int i;
} dict2;
/*----------------------*_*-----------------------*/

char *data1="dic1.dat"; 
char *data2="dic2.dat"; 
BTA *bt1,*bt2; 
int rsize1,rsize2;
char sound[30],s1[30];
char key[40];
dict2 *p2;
dict1 *p1; 
/*----------------------*_*-----------------------*/

int mygetch( );
void init1();
void add1();
void search();
void delete_key();
void edit();
void search_tab();
void menu();
int check(char *x,char *y);
int soundex(char *SoundEx,char *WordString,int   LengthOption,int   CensusOption);
void add2();   
void search2();
/*----------------------*_*-----------------------*/

//ham main
int main() 
{ 
   init1(); 
   add1();
   add2();
   system("clear");
   menu();
   btcls(bt1);
   btcls(bt2);
} 

//menu
void menu()
{
     int choice; 
     do 
     { 
                               printf(" \033[36m     DICTIONARY\n"); 
                               printf("1:Xoa Tu\n"); 
                               printf("2:Tim Kiem Tu \n"); 
                               printf("3:Tim Kiem Tu Su Dung Tab \n");
                               printf("4:Them Tu \n");
                               printf("5:Tim Kiem Nang Cao \n");
                               printf("6:Thoat \033[0m\n"); 
        printf("Lua chon: "); scanf("%d",&choice); 
        printf("-------------------------*_*---------------------------\n\n");
        switch (choice) 
      { 
         case 1: delete_key();      system("clear");  break; 
         case 2: search();          system("clear");  break; 
         case 3: search_tab();      system("clear");  break; 
         case 4: edit();            system("clear");  break; 
         case 5: search2();         system("clear");  break;
         case 6:                    system("clear");  break; 
      } 
     } 
   while (choice != 6); 
}

//getch()
int mygetch() 
{
    struct termios oldt,
    newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

//khoi tao cay btree1&2
void init1()
{ 
   btinit(); 
   if (fopen(data1,"r")==NULL) bt1 = btcrt(data1,0,0); 
   else bt1 = btopn(data1,0,0); //tra ve BTA
   bt2 = btcrt(data2,0,0);  //tra ve BTA
} 

//dua vao cay btree1
void add1()        
{
   FILE *f;
   f=fopen("nhap.txt","r");
   while(!feof(f))
   {
     p1=(dict1*)malloc(sizeof(dict1));
     fscanf(f,"%s",p1->key);
     fgets(p1->value,256,f);
     btins(bt1,p1->key,(char*)p1,sizeof(dict1)); 
     free(p1);
   }  
   fclose(f);
} 

//tim` kiem tren btree1
void search()
{   
  printf("\nNhap tu can tim kiem:");scanf("%*c");gets(key);
     if(btsel(bt1,key,(char*)p1,sizeof(dict1),&rsize1)!=0)
     {
       printf("\n\033[31mKhong co tu nay\033[0m");
       mygetch();
     }
     else 
     {
       printf("\n%s:\t%s",p1->key,p1->value);
       mygetch();
     }
     mygetch();
}

//xoa key tren btree1
void delete_key()
{
  printf("\nNhap tu muon xoa:");scanf("%*c");gets(key);
     if(btdel(bt1,key)!=0) 
     {
       printf("\n\033[31m=>Khong co tu nay\033[0m");
       mygetch();
     }
     else 
     {  
       printf("\n=>Da xoa");
       mygetch();
     }
     mygetch();
}

//thay doi thong tin tren key
void edit() 
{ 
  char xau[20];
    p1=(dict1*)malloc(sizeof(dict1));
    printf("\nNhap tu muon them:"); scanf("%*c");gets(xau); 
    strcpy(p1->key,xau);
    if (btsel(bt1,p1->key,(char*)p1,sizeof(dict1),&rsize1)!=0) 
    {
       mygetch();
       printf("\nNhap y nghia:");gets(p1->value);
       btins(bt1,p1->key,(char*)p1,sizeof(dict1)); 
       printf("\nDa cap nhat");
       mygetch();
    } 
    else 
    { 
       mygetch();
       printf("\nNhap vao nghia tu:");gets(p1->value);
       btupd(bt1,p1->key,(char*)p1,sizeof(dict1)); 
       printf("\nNghia da duoc thay doi");
       mygetch();
    } 
} 

//tim` kiem su dung TAB
void search_tab()
{ 
     
     char c,keyc[40];
     int i=0,kt;
     p1 = (dict1*) malloc(sizeof(dict1));
     fflush(stdin);
     printf("Nhap tu ban muon tim kiem(TAB):");mygetch();
     do
      { 
        c = mygetch();printf("%c",c);
        keyc[i]=c;
        i++;
      }
     while((c!='\t')&&(c!='\n'));
     keyc[i-1]='\0';
     kt=btsel(bt1,keyc,(char*)p1,sizeof(dict1),&rsize1);
     if(c=='\n')
     {
      if(kt==0)
      {
         printf("\n%s%s ",p1->key,p1->value);
         mygetch(); 
      }
      else
      {  
         printf("\n\033[31mKhong the tim\033[0m");
         mygetch(); 
      }
     }
     while(c=='\t')
     {    
        btseln(bt1,key,(char*)p1,sizeof(dict1),&rsize1);
        if(check(keyc,key)==0)
        {  
          printf("\n\nKet thuc");
          mygetch();
          break;
        }
        else
        {
          printf("\n\n%s\t%s ",p1->key,p1->value);
          mygetch();
        }
     }
     free(p1);     
}

//kiem tra 2 xau
int check(char *x,char *y)
{
    int i=0;
    while(i<strlen(x))
    {
      if(x[i]!=y[i]) return 0;
      else i++;
    }
    return 1;
}

/*----------------------*_*-----------------------*/

//dua du lieu vao cay btree2
void add2()        
{
   FILE *f;
   f=fopen("nhap.txt","r");
   int kt,i,j;
   while(!feof(f))
   {
      p2=(dict2*)malloc(sizeof(dict2));
      p1=(dict1*)malloc(sizeof(dict1));
      fscanf(f,"%s",p1->key);
      fgets(p1->value,256,f);
      p2->i=0;
      soundex(sound,p1->key,1,1);
   if(btsel(bt2,sound,(char*)p2,sizeof(dict2),&rsize2)!=0)
   {
      strcpy(p2->key[p2->i],p1->key);
      strcpy(p2->value[p2->i],p1->value);
      btins(bt2,sound,(char*)p2,sizeof(dict2));
   }
   else
   {  
      p2->i++;
      strcpy(p2->key[p2->i],p1->key);
      strcpy(p2->value[p2->i],p1->value);
      if(strcmp(p2->key[p2->i],p2->key[p2->i-1])!=0)
      btupd(bt2,sound,(char*)p2,sizeof(dict2));
   }  
   free(p2);
   free(p1);
   }  
   fclose(f);
} 

//tim` kiem
void search2()
{   
  int j,kt=0,c,i=0;
     char key1[40];
     p2=(dict2*)malloc(sizeof(dict2));
     printf("\nNhap tu ban muon tim:");mygetch();
     do
       { 
	 c = mygetch();printf("%c",c);
	 key[i]=c;
	 i++;
       }
     while((c!='\t')&&(c!='\n'));
     key[i-1]='\0';
     /*scanf("%*c");gets(key);
          if(btsel(bt1,key,(char*)p1,sizeof(dict1),&rsize1)!=0)
     {
       printf("\n\033[31m=>Khong co tu nay\033[0m");
       mygetch();
       }*/
     soundex(s1,key,1,1);
     if(btsel(bt2,s1,(char*)p2,sizeof(dict2),&rsize2)!=0)
     {
       printf("\n=>\033[31mKhong co tu nay\033[0m");
       mygetch();
     }
     else 
     {
       printf("\nTim kiem nang cao(bang thu vien soundex):\n");
       for(j=0;j<=p2->i;j++)
       {
         printf("%s=>\t",p2->key[j]);
       }
       mygetch();
       printf("\n\n=>Nhap vao y nghia:");scanf("%s",key1);
       for(j=0;j<=p2->i;j++)
       {
         if(strcmp(key1,p2->key[j])==0) 
         {
           printf("\n%s\t%s",key1,p2->value[j]);
           kt=1;
           break;
         }
       }
       if (kt==0) printf("\n\n\033[31mKhong co tu nay\033[0m");
       mygetch();
     }
     //     }
    mygetch();
}

//ham` soundex
int soundex(char *SoundEx,char *WordString,int   LengthOption,int   CensusOption)
{
      int  InSz = 31;
      char WordStr[32];     /* one bigger than InSz */
      int  SoundExLen, WSLen, i;
      char FirstLetter, *p, *p2;

      SoundExLen = WSLen = 0;
      SoundEx[0] = 0;

      if(CensusOption) {
        LengthOption = 4;
      }

      if(LengthOption) {
          SoundExLen = LengthOption;
      }
      if(SoundExLen > 10) {
          SoundExLen = 10;
      }
      if(SoundExLen < 4) {
          SoundExLen = 4;
      }

      if(!WordString) {
          return(0);
      }

      /* Copy WordString to WordStr
       * without using funcs from other
       * libraries.
      */
for(p = WordString,p2 = WordStr,i = 0;(*p);p++,p2++,i++) {
        if(i >= InSz) break;
        (*p2) = (*p);
      }
      (*p2) = 0;



      /* Convert WordStr to
       * upper-case, without using funcs
       * from other libraries
      */
      for(p = WordStr;(*p);p++) {
        if( (*p) >= 'a' && (*p) <= 'z' ) {
            (*p) -= 0x20;
        }
      }


      /* convert all non-alpha
       * chars to spaces
      */
      for(p = WordStr;(*p);p++) {
        if( (*p) < 'A' || (*p) > 'Z' ) {
            (*p) = ' ';
        }
      }

      /* Remove leading spaces
      */
for(i = 0, p = p2 = WordStr;(*p);p++) {
          if(!i) {
              if( (*p) != ' ' ) {
                  (*p2) = (*p);
                  p2++;
                  i++;
              }
          }
          else {
              (*p2) = (*p);
              p2++;
          }
      }
      (*p2) = 0;

      /* Get length of WordStr
      */
      for(i = 0,p = WordStr;(*p);p++) i++;


      /* Remove trailing spaces
      */
      for(;i;i--) {
          if(WordStr[i] == ' ') {
            WordStr[i] = 0;
          }
          else {
              break;
          }
      }

      /* Get length of WordStr
      */
      for(WSLen = 0,p = WordStr;(*p);p++) WSLen++;

      if(!WSLen) {
        return(0);
      }



      /* Perform our own multi-letter
       * improvements
       *
       * underscore placeholders (_) will be
       * removed below.
      */
      if(!CensusOption) {
          if(WordStr[0] == 'P' && WordStr[1] == 'S') {
              WordStr[0] = '_';
          }
          if(WordStr[0] == 'P' && WordStr[1] == 'F') {
              WordStr[0] = '_';
          }

          for(i = 0;i < WSLen;i++) {
              if(WordStr[i] == 'D' && WordStr[i+1] == 'G') {
                  WordStr[i] = '_';
                  i++;
                  continue;
              }
              if(WordStr[i] == 'G' && WordStr[i+1] == 'H') {
                  WordStr[i] = '_';
                  i++;
                  continue;
              }
if(WordStr[i] == 'K' && WordStr[i+1] == 'N') {
                  WordStr[i] = '_';
                  i++;
                  continue;
              }
              if(WordStr[i] == 'G' && WordStr[i+1] == 'N') {
                  WordStr[i] = '_';
                  i++;
                  continue;
              }
              if(WordStr[i] == 'M' && WordStr[i+1] == 'B') {
                  WordStr[i+1] = '_';
                  i++;
                  continue;
              }

              if(WordStr[i] == 'P' && WordStr[i+1] == 'H') {
                  WordStr[i] = 'F';
                  WordStr[i+1] = '_';
                  i++;
                  continue;
              }
              if(WordStr[i]  ==  'T'  &&
                 WordStr[i+1] == 'C' &&
                 WordStr[i+2] == 'H'
                ) {

                  WordStr[i] = '_';
                  i++; i++;
                  continue;
              }
              if(WordStr[i] == 'M' && WordStr[i+1] == 'P'
                 && (WordStr[i+2] == 'S' ||
                     WordStr[i+2] == 'T' ||
                     WordStr[i+2] == 'Z')
                ) {
                  WordStr[i+1] = '_';
                  i++;
              }
          }
      } /* end if(!CensusOption) */



      /* squeeze out underscore characters
       * added as a byproduct of above process
       * (only needed in c styled replace)
      */
      for(p = p2 = WordStr;(*p);p++) {
        (*p2) = (*p);
        if( (*p2) != '_' ) {
            p2++;
        }
      }
      (*p2) = 0;





      /* This must be done AFTER our
       * multi-letter replacements
       * since they could change
       * the first letter
      */
FirstLetter = WordStr[0];


      /* In case we're in CensusOption
       * 1 and the word starts with
       * an 'H' or 'W'
       *  (v1.0c djr: add test for H or W)
      */
      if(FirstLetter == 'H' || FirstLetter == 'W') {
          WordStr[0] = '-';
      }



      /* In properly done census
       * SoundEx, the H and W will
       * be squezed out before
       * performing the test
       * for adjacent digits
       * (this differs from how
       * 'real' vowels are handled)
      */
      if(CensusOption == 1) {
          for(p = &(WordStr[1]);(*p);p++) {
             if((*p) == 'H' || (*p) == 'W') {
                 (*p) = '.';
             }
          }
      }





      /* Perform classic SoundEx
       * replacements.
      */
      for(p = WordStr;(*p);p++) {
          if( (*p) == 'A'   ||
              (*p) == 'E'   ||
              (*p) == 'I'   ||
              (*p) == 'O'   ||
              (*p) == 'U'   ||
              (*p) == 'Y'   ||
              (*p) == 'H'   ||
              (*p) == 'W'
            ){
              (*p) = '0';   /* zero */
          }
          if( (*p) == 'B'   ||
              (*p) == 'P'   ||
              (*p) == 'F'   ||
              (*p) == 'V'
            ){
              (*p) = '1';
          }
          if( (*p) == 'C'   ||
              (*p) == 'S'   ||
              (*p) == 'G'   ||
              (*p) == 'J'   ||
              (*p) == 'K'   ||
              (*p) == 'Q'   ||
              (*p) == 'X'   ||
              (*p) == 'Z'
            ){
              (*p) = '2';
          }
          if( (*p) == 'D'   ||
              (*p) == 'T'
            ){
              (*p) = '3';
          }
          if( (*p) == 'L' ) {
              (*p) = '4';
          }

          if( (*p) == 'M'   ||
              (*p) == 'N'
            ){
              (*p) = '5';
          }
          if( (*p) == 'R' ) {
              (*p) = '6';
          }
      }
      /* soundex replacement loop done  */




      /* In properly done census
       * SoundEx, the H and W will
       * be squezed out before
       * performing the test
       * for adjacent digits
       * (this differs from how
       * 'real' vowels are handled)
      */
      if(CensusOption == 1) {
          /* squeeze out dots
          */
          for(p = p2 = &WordStr[1];(*p);p++) {
            (*p2) = (*p);
            if( (*p2) != '.' ) {
                p2++;
            }
          }
          (*p2) = 0;
      }



      /* squeeze out extra equal adjacent digits
       * (don't include first letter)
       * v1.0c djr (now includes first letter)
      */
      for(p = p2 = &(WordStr[0]);(*p);p++) {
        (*p2) = (*p);
        if( (*p2) != p[1] ) {
            p2++;
        }
      }
      (*p2) = 0;



      /* squeeze out spaces and zeros
       * Leave the first letter code
       * to be replaced below.
       * (In case it made a zero)
      */
      for(p = p2 = &WordStr[1];(*p);p++) {
        (*p2) = (*p);
        if( (*p2) != ' ' && (*p2) != '0' ) {
            p2++;
        }
      }
      (*p2) = 0;



      /* Get length of WordStr
      */
      for(WSLen = 0,p = WordStr;(*p);p++) WSLen++;


      /* Right pad with zero characters
      */
      for(i = WSLen;i < SoundExLen;i++ ) {
          WordStr[i] = '0';
      }

      /* Size to taste
      */
      WordStr[SoundExLen] = 0;


      /* Replace first digit with
       * first letter.
      */
      WordStr[0] = FirstLetter;


      /* Copy WordStr to SoundEx
      */
      for(p2 = SoundEx,p = WordStr;(*p);p++,p2++) {
          (*p2) = (*p);
      }
      (*p2) = 0;
      
      return(SoundExLen);
  }
 
