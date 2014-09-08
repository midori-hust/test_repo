#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//======================

typedef struct
{
  double x;
  double y;
} point;

//=====================

typedef struct circle
{
  point center;
  double radius;
} circle;

//=========================================================

int isIntersect(circle m, circle n)
{
  double a,b,c;
  a = abs(m.radius - n.radius);
  b = sqrt((m.center.x - n.center.x) * (m.center.x - n.center.x) + (m.center.y - n.center.y) * (m.center.y - n.center.y));
  c = m.radius + n.radius;
  return ( (a<b) && (b<c) );
}

//========================================================

int maxIntersect(circle *a,int n)
{
  int i,j,k = 0,count[n];

  for(i = 0; i < n; i++)
    count[i] = 0;

  for(i = 0; i < n; i++) 
    for(j = 0;j < n;j++)
      {
	if((i != j) && (isIntersect(a[i],a[j]) > 0))
	  count[i]++;
      }     
  
  int max = count[0];
  for(i = 0; i < n; i++)
    if(count[i] > max)
      {
	max = count[i];
	k = i;
      }
  
  return k;
}

//===============================================

int Intersected(circle *a, int *output, int n)
{
  int i,dem = 0;
  int k = maxIntersect(a,n);

  for(i = 0; i < n; i++) 
    {
      if((i != k) && isIntersect(a[i],a[k]) )
	output[dem++] = i;
    }    
  return dem;
}

//============================================================

int menu()
{
  int c;
  printf("\n\t===========================");
  printf("\n\tDUONG TRON");
  printf("\n\t\t1. Sinh du lieu thu nghiem bang tay.");
  printf("\n\t\t2. Sinh du lieu thu nghiem ngau nhien.");
  printf("\n\t\t3. Thong tin ve cac duong tron.");
  printf("\n\t\t4. Duong tron giao voi nhieu duong tron nhat.");
  printf("\n\t\t5. Thoat.");
  printf("\n\t===========================");
  printf("\n\t Ban chon:....... ");
  scanf("%d",&c);
  return c;
}

//==============Ham chinh==================//

int main()
{
  int choice,quit = 0;
  int i,k,m,n,output[1000];
  circle *a;

  while(quit == 0)
    {
      choice = menu();
      switch(choice)
	{
	
	case 1: printf("Moi ban nhap so duong tron muon sinh ra: "); 
	        scanf("%d",&n);
		a = (circle*)malloc(n * sizeof(circle));

		for(i = 0; i < n; i++)
		  {
		    printf("\nDuong tron thu %d:",i + 1);
		    printf("\nToa do tam (x;y) = "); scanf("%lf %lf",&a[i].center.x,&a[i].center.y);
		    printf("Ban kinh R = "); scanf("%lf",&a[i].radius);
		  }
		break;
	
	case 2: srand((unsigned)time(NULL));
                printf("Moi ban nhap so duong tron muon sinh ra: "); 
	        scanf("%d",&n);
		a = (circle*)malloc(n*sizeof(circle));
		for(i = 0; i < n; i++)
		  {
		    a[i].center.x = (double)rand()/ RAND_MAX * 100;
		    a[i].center.y = (double)rand() / RAND_MAX * 100;
		    a[i].radius = (double)rand() / RAND_MAX * 100;
		    a[i].radius = (a[i].radius > 0) ? (a[i].radius) : (-a[i].radius);
		  }
		printf("Sinh ngau nhien %d duong tron thanh cong!\n", n);
		break;

	case 3: printf("%-15s%-15s%-20s\n", "DUONG TRON","TAM","BAN KINH");
	        for(i = 0; i < n; i++)
		  printf("   %-10d(%.1lf;%.1lf)%10.1lf\n",i+1,a[i].center.x,a[i].center.y,a[i].radius);
		break;

	case 4: k = maxIntersect(a,n);
	        if(k > 0)
		  {
		    printf("Duong tron giao voi nhieu duong tron nhat la:\n");
		    printf("%-15s%-15s%-20s\n", "DUONG TRON","TAM","BAN KINH");
		    printf("   %-10d(%.1lf;%.1lf)%10.1lf\n",k+1,a[k].center.x,a[k].center.y,a[k].radius);
		    
		    printf("Cac duong tron giao voi duong tron nay:\n");
		    printf("%-15s%-15s%-20s\n", "DUONG TRON","TAM","BAN KINH");
		    m = Intersected(a,output,n);
		    for(i = 0; i < m; i++)
		      printf("   %-10d(%.1lf;%.1lf)%10.1lf\n",output[i]+1,a[output[i]].center.x,a[output[i]].center.y,a[output[i]].radius);
		  }
		else printf("Cac duong tron sinh ra khong giao nhau tung doi mot.\n");
		break;

	case 5: quit++;
	        printf("Hen gap lai !!\n");
		break;
	
	default: printf("Moi ban chon lai tu 1 den 5.\n");

	}
    }
  return 0;
}
