#include <stdio.h>
#include <string.h>

#define T 10

typedef struct{
  char name[25];
  int old;
  int score[5];
}game;

int menu();
void nhapxau(char *str);
int soluong(int a,int b);
void danhsach(game person[],int n);
void printlist(game person[],int n);
void play(game person[],int n,char *xaugoc); 
void xaugia(char *xau,int dai);
int choidoan(char *xaugoc,char *xau,char ch);
char *xauhoa(char *xau1);
void diem(game person[],int i,int k,int d);
void ketqua1(game person[],int n);
void sapxep(game person[],int n);

void printlist1(game *person, int n);

main()
{
  int choice, n;
  char xaugoc[40], xau[40];

  game person[T];

  do{
    choice=menu();    
    switch(choice)
      {
      case 1:
    	printf("Nhap xau: ");
    	nhapxau(xaugoc);
    	printf("Nhap so nguoi choi: ");
    	n = soluong(1, 4);
    	danhsach(person, n);
    	printlist(person, n);
      break;
      case 2:
	    play(person, n, xaugoc);
      break;
      case 3:
    	sapxep(person, n);
    	printlist1(person, n);
    	break;
      }
  } while(choice != 4);
}

int menu()
{
  int cn;
  do {
    printf("\n\n_______TRO CHOI LAT O CHU________\n");
    printf("\n1. Khoi dong tro choi\n");
    printf("2. Choi doan ki tu\n");
    printf("3. Tong hop ket qua\n4. Thoat\n");
    printf("Chon chuc nang: ");
    scanf("%d%*c", &cn);
  } while(cn<0 || cn>4);

  return cn;
}

void khoidong(game person[], char *xau)
{
  int i,n;
  char xaugoc[40];
  printf("Nhap xau: ");
  nhapxau(xaugoc);
  printf("Nhap so nguoi choi: ");
  n=soluong(1,4);
  printf("%d\n",n);
  danhsach(person,n);
  printlist(person,n);
}

void nhapxau(char *str)
{
  int i, dai;
  do {
    scanf("%[^\n]%*c", str);
    xauhoa(str);
    dai = strlen(str);
    if(dai<20 || dai>40) 
      printf("Nhap lai xau dai tu 20-40\n");
    if(strstr(str," ") != NULL) 
      printf("Nhap lai xau ko chua dau cach\n");
  } while(dai<20 || dai>40 || strstr(str," ") != NULL);
}

int soluong(int a, int b)
{
  int m;

  do{
    scanf("%d%*c", &m);
    if(m<a || m>b) printf("Nhap lai so nguoi choi <=%d\n", b);
  } while(m<a || m>b);

  return m;
}

void danhsach(game person[], int n)
{
  int i = 0;

  do{
    printf("Nhap ten nguoi choi thu %d: ", i+1);
    scanf("%[^\n]%*c",person[i].name);
    printf("Nhap tuoi cua %s: ",person[i].name);
    scanf("%d%*c",&person[i].old);
    i++;
  } while(i<n);
}

void printlist(game person[], int n)
{
  int i;
  
  printf("\n___DANH SACH NGUOI CHOI___\n");
  printf("%-25s%-25s\n","Ho va ten","Tuoi");
  for(i=0; i<n; i++) 
    printf("%-25s%d\n",person[i].name,person[i].old);
}

void play(game person[],int n, char *xaugoc)
{
  char xau[40], xaudoan[40];
  char ch;
  int i = 0, k, j, d, t;

  do{
    xaugia(xau, strlen(xaugoc));
    printf("%s\n",xau);
    k=0;
    t=0;
    printf("Nguoi choi thu %d doan\n",i+1);
    do{
      person[i].score[k]=0;
      printf("lan %d: ",k+1);
      scanf("%c%*c",&ch);
      if(ch<97) ch=ch+32;
      person[i].score[k]=choidoan(xaugoc,xau,ch);
      printf("%s\n",xau);
      k++;
    }while(k<4);
    printf("Doan xau: ");
    scanf("%[^\n]%*c",xaudoan);
    xauhoa(xaudoan);
    if(strcmp(xaugoc,xaudoan)==0) t=20;
    person[i].score[4]=person[i].score[0]+person[i].score[1]+person[i].score[2]+person[i].score[3]+t;
    i++;
  }while(i<n);
  printf("%-25s%-6s%-6s%-6s%-6s%s\n","Ho va ten","L1","L2","L3","L4","Ket qua");
  ketqua1(person,n);
}

char *xauhoa(char *xau1)
{
  int i;
  for(i=0;i<strlen(xau1);i++)
    if(xau1[i]<97) xau1[i]+=32;
  return xau1;
}

void xaugia(char *xau,int dai)
{
  int i;

  for(i=0;i<dai;i++) 
    xau[i]='*';

  xau[dai-1]='\0';
}

int choidoan(char *xaugoc,char *xau,char ch)
{
  int i, d = 0;

  for(i = 0; i < strlen(xau); i++)
    {
      if(xaugoc[i]==ch&&xau[i]!=ch) {
        xau[i] = ch;
        d += 1;
      } 
    }

  return d;
}

void ketqua1(game person[], int n)
{
  int i;
  for(i=0; i<n; i++)
    printf("%-25s%-6d%-6d%-6d%-6d%d\n",person[i].name, person[i].score[0], person[i].score[1],
      person[i].score[2], person[i].score[3], person[i].score[4]);
}

void sapxep(game person[],int n)
{
  int i, j;
  game tg;

  for(i=0;i<n;i++)
    for(j=i+1;j<n;j++)
      if(person[i].score[4]<person[j].score[4]) {
      	tg=person[i];person[i]=person[j];person[j]=tg;
      }

  // printf("%-5s%-25s%s\n","STT","Ho va ten","Ket qua");
  // for(i=0;i<n;i++)
  //   printf("%-5d%-25s%d\n",i+1,person[i].name,person[i].score[4]);

	// printlist1(person, n);
}

void printlist1(game *person, int n) {
	int i;

	printf("%-5s%-25s%s\n","STT","Ho va ten","Ket qua");
  	for(i=0;i<n;i++)
    	printf("%-5d%-25s%d\n",i+1,person[i].name,person[i].score[4]);	
}