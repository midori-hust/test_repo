#include <stdio.h>

void main()
{
int a,trieu,tramnghin,chucnghin,nghin,tram,chuc,donvi;
do{
printf("Nhap so co 7 chu so: ");
scanf("%d",&a);
if ((a<1000000) || (a>9999999))
{
printf("So khong nhu yeu cau! Nhap lai!\n");
}
}while((a<1000000) || (a>9999999));
trieu=a/1000000;
tramnghin=a/100000;
chucnghin=a/10000;
nghin=a/1000;
tram=a/100;
chuc=a/10;
donvi=a%10;
//hang trieu

switch(trieu){
case 1:
printf("Mot Trieu");
break;
case 2:
printf("Hai Trieu");
break;
case 3:
printf("Ba Trieu");
break;
case 4:
printf("Bon Trieu");
break;
case 5:
printf("Nam Trieu");
break;
case 6:
printf("Sau Trieu");
break;
case 7:
printf("Bay Trieu");
break;
case 8:
printf("Tam Trieu");
break;
case 9:
printf("Chin Trieu");
break;
}

switch(tramnghin){
case 1:
printf("Mot Tram");
break;
case 2:
printf("Hai Tram");
break;
case 3:
printf("Ba Tram");
break;
case 4:
printf("Bon Tram");
break;
case 5:
printf("Nam Tram");
break;
case 6:
printf("Sau Tram");
break;
case 7:
printf("Bay Tram");
break;
case 8:
printf("Tam Tram");
break;
case 9:
printf("Chin Tram");
break;
}

//doc so o hang chuc nghin

switch(chucnghin){
case 1:
printf("Muoi");
break;
case 2:
printf("Hai Muoi");
break;
case 3:
printf("Ba Muoi");
break;
case 4:
printf("Bon Muoi");
break;
case 5:
printf("Nam Muoi");
break;
case 6:
printf("Sau Muoi");
break;
case 7:
printf("Bay Muoi");
break;
case 8:
printf("Tam Muoi");
break;
case 9:
printf("Chin Muoi");
break;
case 0:
printf("Linh");
break;
}

//doc so o hang nghin

switch(nghin){
case 1:
printf("Mot Nghin");
break;
case 2:
printf("Hai Nghin");
break;
case 3:
printf("Ba Nghin");
break;
case 4:
printf("Bon Nghin");
break;
case 5:
printf("Nam Nghin");
break;
case 6:
printf("Sau Nghin");
break;
case 7:
printf("Bay Nghin");
break;
case 8:
printf("Tam Nghin");
break;
case 9:
printf("Chin Nghin");
break;
}

//doc so o hang tram

switch(tram){
case 0:
printf("Khong Tram");
break;
case 1:
printf("Mot Tram");
break;
case 2:
printf("Hai Tram");
break;
case 3:
printf("Ba Tram");
break;
case 4:
printf("Bon Tram");
break;
case 5:
printf("Nam Tram");
break;
case 6:
printf("Sau Tram");
break;
case 7:
printf("Bay Tram");
break;
case 8:
printf("Tam Tram");
break;
case 9:
printf("Chin Tram");
break;
}

//doc so o hang chuc

switch(chuc){
case 0:
printf("linh");
break;
case 1:
printf("Muoi");
break;
case 2:
printf("Hai Muoi");
break;
case 3:
printf("Ba Muoi");
break;
case 4:
printf("Bon Muoi");
break;
case 5:
printf("Nam Muoi");
break;
case 6:
printf("Sau Muoi");
break;
case 7:
printf("Bay Muoi");
break;
case 8:
printf("Tam Muoi");
break;
case 9:
printf("Chin Muoi");
break;
}

//doc so o hang don vi

switch(donvi){
case 0:
printf("Khong");
break;
case 1:
printf("Mot");
break;
case 2:
printf("Hai");
break;
case 3:
printf("Ba");
break;
case 4:
printf("Tu");
break;
case 5:
printf("Nam");
break;
case 6:
printf("Sau");
break;
case 7:
printf("Bay");
break;
case 8:
printf("Tam");
break;
case 9:
printf("Chin");
break;
}
}
