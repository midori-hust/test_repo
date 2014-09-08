#include <stdio.h>

typedef struct qt {
  char cauhoi[128];
  char pa1[30];
  char pa2[30];
  char pa3[30];
  int dapan;
} qt_type;

typedef struct nguoichoi {
  char ten[60];
  int cauhoi[5];
  int dapan[5];
  int diem;
} nguoichoi_type;

void in_menu(void)
{
    printf("\n\n\n\n--------------------------\n");
    printf("__________MENU____________\n");
    printf("____TOI YEU THE THAO______\n");
    printf("1, Tao cau hoi\n");
    printf("2, In cau hoi\n");
    printf("3, Thay doi dap an\n");
    printf("4, Thuc hien choi\n");
    printf("5, Exit\n");
    printf("Xin moi lua chon: \n");
}

qt_type taocauhoi()
{
  int i;
  qt_type a[6];
  for(i=1;i<=5;i++)
    {
      printf("Cau hoi %d : ",i);
      gets(a[i].cauhoi);

      printf("PA1 : ");
      gets(a[i].pa1);

      printf("PA2 : ");
      gets(a[i].pa2);

      printf("PA3 : ");
      gets(a[i].pa3);
 
      printf("Dap an : ");
      scanf("%d",&a[i].dapan);
    }
  return a[6];
}

void incauhoi(qt_type dscauhoi[6])
{
  int i;
  for(i=1;i<=5;i++)
    printf("Cau hoi : %s",dscauhoi[i].cauhoi);
    printf("PA1 : %s",dscauhoi[i].pa1);
    printf("PA2 : %s",dscauhoi[i].pa2);
    printf("PA3 : %s",dscauhoi[i].pa3);
}

void inluachonnguoichoi(nguoichoi_type a)
{
  int i;
  printf("Nguoi choi : %s\n", a.ten);
  printf("Cau hoi \t lua chon\n");
  for(i=1;i<=3;i++)
    printf("%d \t %d\n",a.cauhoi[i],a.dapan[i]);
}

/*nguoichoi_type choi(nguoichoi_type dsnguoichoi[100])
{
  int stt;
  stt = 1;
  printf("Ho va te : ");
  gets(dsnguoichoi[stt].ten);
  incauhoi(dscauhoi[6]);
}


nguoichoi_type thaydoidapan(nguoichoi_type a)
{
  printf("");
}
*/
main()
{
  int luachon,stt;
    char ss[5];
    qt_type dscauhoi[6];
    nguoichoi_type dsnguoichoi[100];
    quaylai: 
    in_menu();
    scanf("%d",&luachon);
    gets(ss);
    if(luachon==1)
    {
        printf("1. Tao cau hoi\n");
		dscauhoi[6]=taocauhoi();
        goto quaylai;
    }

    if(luachon==2)
    {
        printf("2. In cau hoi\n");
		incauhoi(dscauhoi);
        goto quaylai;
    }
    if(luachon==3)
    {
        printf("This is function 3\n");
        goto quaylai;
    }
    if(luachon==4)
    {
        printf("This is function 4\n");
        goto quaylai;
    }
    if(luachon==5)
    {
        printf("Good bye!!\n");

    }

}
