/* Quan ly SV bang DSLK */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
enum{SUCCESS,FAIL};

#define MAX 100

struct user {
  char name[30];
  char pass[10];
  struct user *next;
}*first, *last;

typedef struct sv {
  char name[30];
  char pass[10];
} sv;

int n = 0;

void nhapmoi(char  name[30], char  pass[30])
{
      //sv ds[20];
  char dssv[]="user.txt";
  int i=0,reval=SUCCESS,n;
  FILE *fin;
  if((fin = fopen(dssv,"a+t"))==NULL)
    {
      printf("Cannot open %s",dssv);
      reval=FAIL;
    }

//      FILE *fout;
//        char bd[]="log.txt";
////  char name[30];
//  struct user *svtmp;

    //printf("\nCho biet ten SV : ");
    //gets(name);
    //gets(name);
    //if (strlen(name))
    //{
      //svtmp = (struct user *) malloc(sizeof(struct user));
      //strcmp(svtmp->name, name);
      //printf("\nCho biet pass : ");
      //gets(svtmp->pass);
fprintf(fin,"%s\t%s\n",name,pass);

//      svtmp->next = NULL;
//      if (first == NULL)
//        first = last = svtmp;
//      else
//      {
//        last->next = svtmp;
//        last = last->next;
//      }
//    }
//
//    if((fout=fopen(bd,"a+t"))==NULL)
//    {printf("Cannot open %s",bd);
//      reval=FAIL;
//    }
//        time_t rawtime;
//    struct tm *timeinfo;
//
//    time(&rawtime);
//    timeinfo = localtime(&rawtime);
//    //printf("Thoi gian hien tai la: %s",asctime(timeinfo));
//  fprintf(fout,"----------------Lich su them----------------\n");
//  fprintf(fout,"%10s %16s %6s\n","thoi gian |","Thao tac |","Ten User");
//  fprintf(fout,"%s %16s %6s\n",asctime(timeinfo),"them bang tay",name);
//  fclose(fout);
  //fclose(fin);
}

int timkiem(char name[30])
{
  int found = 0;
  struct user *svtmp;
//  char name[30];

  if (first == NULL)
  {
    printf("\nDanh sach rong!!!");
    return;
  }
  svtmp = first;
  //printf("\nCho biet ten : ");
  //gets(name);
  //gets(name);
  if (strlen(name))
    while (svtmp != NULL)
      if (strcmp(svtmp->name, name) == 0)
      {
         //printf("\nHo va ten : %s", svtmp->name);
         //printf("\npass : %s", svtmp->pass);
         found = 1;
         break;
      }
      else
        svtmp = svtmp->next;
  if (!found)
    printf("\nKhong tim thay!!!");
    return found;
}

int pass(char name[30])
{
  int found = 0;
  struct user *svtmp;
//  char name[30];

  if (first == NULL)
  {
    printf("\nDanh sach rong!!!");
    return;
  }
  svtmp = first;
  //printf("\nCho biet ten : ");
  //gets(name);
  //gets(name);
  if (strlen(name))
    while (svtmp != NULL)
      if (strcmp(svtmp->pass, name) == 0)
      {
         //printf("\nHo va ten : %s", svtmp->name);
         //printf("\npass : %s", svtmp->pass);
         found = 1;
         break;
      }
      else
        svtmp = svtmp->next;
  if (!found)
    printf("\nKhong tim thay!!!");
    return found;
}
void xoa()
{
  char bd[]="log.txt";
  int reval=SUCCESS;
  FILE *fout;
  char name[30], traloi;
  struct user *svtmp, *before = NULL;

  if (first == NULL)
  {
    printf("\nDanh sach rong!!!");
    return;
  }
  svtmp = first;
  printf("\nCho biet ten : ");
  gets(name);
  gets(name);
  //if (strlen(studentid))
      //while (svtmp != NULL)
      if (strcmp(svtmp->name, name) == 0)
      {
         printf("\nHo va ten : %s", svtmp->name);
         printf("\npass : %s", svtmp->pass);
         printf("\nCo muon xoa khong (C/K)? ");
         do {
           scanf("%c", &traloi);
         } while (traloi != 'C' && traloi != 'K');
         putc(traloi, stdout);
         if (traloi == 'C')
         {
           n--;
           if (before == NULL)
           {
             before = first;
             first = first->next;
           }
           else
             before->next = svtmp->next;
           //free(svtmp);
           //break;
         }
                 time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    //printf("Thoi gian hien tai la: %s",asctime(timeinfo));
             if((fout=fopen(bd,"a+t"))==NULL)
    {
        printf("Cannot open %s",bd);
        reval=FAIL;
    }
  fprintf(fout,"----------------Lich su xoa----------------\n");
  fprintf(fout,"%10s %16s %6s\n","thoi gian |","Thao tac |","User");
  fprintf(fout,"%10s %16s %6s\n",asctime(timeinfo),"xoa",name);
  fclose(fout);
      }
      else
      {
        before = svtmp;
        svtmp = svtmp->next;
      }
}
void import()
{
  printf("Tu dong impot danh sach tu file co san");
  sv ds[20];
  char dssv[]="user.txt",bd[]="log.txt";
  int i=0,reval=SUCCESS,n;
  FILE *fin,*fout;
  if((fin = fopen(dssv,"r"))==NULL)
    {
      printf("Cannot open %s",dssv);
      reval=FAIL;
    }
  //while(fscanf(fin,"%[^\n] %[^\n] %[^\n] %[^\n]",ds[i].studentid,ds[i].name,ds[i].clas,ds[i].department)!=EOF)
    while(fscanf(fin,"%s %s",ds[i].name,ds[i].pass)!=EOF)
    i++;
  n=i;
  printf("\nDoc thanh cong %d sv, ...\n",n);
  for(i=0;i<n;i++)
    {
      printf("%s  \n",ds[i].name);
      //if(scanf("%d",&ds[i].diem) == 0 || ds[i].diem <0|| ds[i].diem>10)
	//{
	  //printf("Diem khong hop le\n");
	 // scanf("%*c");
	 // i--;
	 // continue;
	//}
	//=================================================================

     char name[8];
     struct user *svtmp;
      strcpy(name,ds[i].name);
      if (strlen(name))
      {
      svtmp = (struct user *) malloc(sizeof(struct user));
      //while (svtmp != NULL


      strcpy(svtmp->name, ds[i].name);
      strcpy(svtmp->pass, ds[i].pass);

      svtmp->next = NULL;
      if (first == NULL)
        first = last = svtmp;
      else
      {
        last->next = svtmp;
        last = last->next;
      }
      }
    }

//
//                 time_t rawtime;
//    struct tm *timeinfo;
//
//    time(&rawtime);
//    timeinfo = localtime(&rawtime);
//    //printf("Thoi gian hien tai la: %s",asctime(timeinfo));
//  if((fout=fopen(bd,"a+t"))==NULL)
//    {printf("Cannot open %s",bd);
//      reval=FAIL;
//    }
//  fprintf(fout,"----------------Lich su import----------------\n");
//  fprintf(fout,"%10s %16s %6s\n","thoi gian |","Thao tac|","User");
//  for(i=0;i<n;i++)
//  {
//  fprintf(fout,"%10s %16s %6s\n",asctime(timeinfo),"them tu dong",ds[i].name);
//  }

  fclose(fin);
//  fclose(fout);
}
//void menu()
//{
//    int luachon;
//    while(luachon!=5)
//	{
//      printf("\n*************************");
//      printf("\n* 1. Them bang tay      *");
//      printf("\n* 2. Import tu file     *");
//      printf("\n* 3. Xoa                *");
//      printf("\n* 4. Tim kiem           *");
//      printf("\n* 5. Thoat              *");
//      printf("\n*************************");
//      printf("\nChon lua: ");
//		scanf ("%i", &luachon);
//	    switch(luachon)
//		{
//		case 1: nhapmoi();printf("\n"); break;
//		case 2: import(); printf("\n");break;
//		case 3: xoa();printf("\n"); break;
//		case 4: timkiem();printf("\n");break;
//		case 5: break;
//		}
//	}
//}

//main()
//{
//    time_t rawtime;
//    struct tm *timeinfo;
//
//    time(&rawtime);
//    timeinfo = localtime(&rawtime);
//    printf("Thoi gian hien tai la: %s",asctime(timeinfo));
//menu();
//}
