/* Quan ly SV bang DSLK */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
enum{SUCCESS,FAIL};

#define MAX 100

struct sinhvien {
  char studentid[8];
  char name[30];
  char clas[10];
  char department[10];
  struct sinhvien *next;
}*first, *last;

typedef struct sv {
  char studentid[8];
  char name[30];
  char clas[10];
  char department[10];
} sv;

int n = 0;

void nhapmoi()
{
      FILE *fout;
        char bd[]="log.txt";
          int reval=SUCCESS;
  char name[30], studentid[8];
  struct sinhvien *svtmp;

    printf("\nCho biet ma so SV : ");
    gets(studentid);
    gets(studentid);
    if (strlen(studentid))
    {
      svtmp = (struct sinhvien *) malloc(sizeof(struct sinhvien));
      strcpy(svtmp->studentid, studentid);
      printf("\nCho biet ho ten : ");
      gets(svtmp->name);
      printf("\nCho biet lop : ");
      gets(svtmp->clas);
      printf("\nCho biet khoa : ");
      gets(svtmp->department);

      svtmp->next = NULL;
      if (first == NULL)
        first = last = svtmp;
      else
      {
        last->next = svtmp;
        last = last->next;
      }
    }

    if((fout=fopen(bd,"a+t"))==NULL)
    {printf("Cannot open %s",bd);
      reval=FAIL;
    }
        time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    //printf("Thoi gian hien tai la: %s",asctime(timeinfo));
  fprintf(fout,"----------------Lich su them----------------\n");
  fprintf(fout,"%10s %16s %6s\n","thoi gian |","Thao tac |","so hieu SV");
  fprintf(fout,"%s %16s %6s\n",asctime(timeinfo),"them bang tay",studentid);
  fclose(fout);
}

void timkiem()
{
  char studentid[8];
  int found = 0;
  struct sinhvien *svtmp;

  if (first == NULL)
  {
    printf("\nDanh sach rong!!!");
    return;
  }
  svtmp = first;
  printf("\nCho biet ma so SV : ");
  gets(studentid);
  gets(studentid);
  if (strlen(studentid))
    while (svtmp != NULL)
      if (stricmp(svtmp->studentid, studentid) == 0)
      {
         printf("\nMa so SV : %s", svtmp->studentid);
         printf("\nHo va ten : %s", svtmp->name);
         printf("\nLop : %s", svtmp->clas);
         printf("\nKhoa : %s", svtmp->department);
         found = 1;
         break;
      }
      else
        svtmp = svtmp->next;
  if (!found)
    printf("\nKhong tim thay!!!");
}

void xoa()
{
  char bd[]="log.txt";
  int reval=SUCCESS;
  FILE *fout;
  char studentid[8], traloi;
  struct sinhvien *svtmp, *before = NULL;

  if (first == NULL)
  {
    printf("\nDanh sach rong!!!");
    return;
  }
  svtmp = first;
  printf("\nCho biet ma so SV : ");
  gets(studentid);
  gets(studentid);
  //if (strlen(studentid))
      //while (svtmp != NULL)
      if (stricmp(svtmp->studentid, studentid) == 0)
      {
         printf("\nMa so SV : %s", svtmp->studentid);
         printf("\nHo va ten : %s", svtmp->name);
         printf("\nLop : %s", svtmp->clas);
         printf("\nKhoa   : %s", svtmp->department);
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
  fprintf(fout,"%10s %16s %6s\n","thoi gian |","Thao tac |","so hieu SV");
  fprintf(fout,"%10s %16s %6s\n",asctime(timeinfo),"xoa",studentid);
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
  char dssv[]="student.txt",bd[]="log.txt";
  int i=0,reval=SUCCESS,n;
  FILE *fin,*fout;
  if((fin = fopen(dssv,"r"))==NULL)
    {
      printf("Cannot open %s",dssv);
      reval=FAIL;
    }
  //while(fscanf(fin,"%[^\n] %[^\n] %[^\n] %[^\n]",ds[i].studentid,ds[i].name,ds[i].clas,ds[i].department)!=EOF)
    while(fscanf(fin,"%1s %s %s %s",ds[i].studentid,ds[i].name,ds[i].clas,ds[i].department)!=EOF)
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

     char studentid[8];
     struct sinhvien *svtmp;
      strcpy(studentid,ds[i].studentid);
      if (strlen(studentid))
      {
      svtmp = (struct sinhvien *) malloc(sizeof(struct sinhvien));
      //while (svtmp != NULL


      strcpy(svtmp->studentid,studentid);
      strcpy(svtmp->name, ds[i].name);
      strcpy(svtmp->clas, ds[i].clas);
      strcpy(svtmp->department, ds[i].department);


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


                 time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    //printf("Thoi gian hien tai la: %s",asctime(timeinfo));
  if((fout=fopen(bd,"a+t"))==NULL)
    {printf("Cannot open %s",bd);
      reval=FAIL;
    }
  fprintf(fout,"----------------Lich su import----------------\n");
  fprintf(fout,"%10s %16s %6s\n","thoi gian |","Thao tac|","so hieu SV");
  for(i=0;i<n;i++)
  {
  fprintf(fout,"%10s %16s %6s\n",asctime(timeinfo),"them tu dong",ds[i].studentid);
  }

  fclose(fin);
  fclose(fout);
}
void menu()
{
    int luachon;
    while(luachon!=5)
	{
      printf("\n*************************");
      printf("\n* 1. Them bang tay      *");
      printf("\n* 2. Import tu file     *");
      printf("\n* 3. Xoa                *");
      printf("\n* 4. Tim kiem           *");
      printf("\n* 5. Thoat              *");
      printf("\n*************************");
      printf("\nChon lua: ");
		scanf ("%i", &luachon);
	    switch(luachon)
		{
		case 1: nhapmoi();printf("\n"); break;
		case 2: import(); printf("\n");break;
		case 3: xoa();printf("\n"); break;
		case 4: timkiem();printf("\n");break;
		case 5: break;
		}
	}
}

main()
{
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    printf("Thoi gian hien tai la: %s",asctime(timeinfo));
menu();
}
