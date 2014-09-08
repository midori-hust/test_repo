#include<stdio.h>
#include<stdlib.h>
enum{SUCCESS,FAIL};
//HAM DEM SO LAN XUAT HIEN TUNG KI TU
void demkitu(char c){
  int count[26]={0};
  while(c!='\n' && c>=0){
    if(c<'z' && c>='a')
      ++count[c-'a'];
    if(c<'Z' && c>='A')
      ++count[c-'Z'];
  }
}
//HAM IN KET QUA
void ketqua(FILE*fptr1, FILE*fptr2){
  int count[26]={0};
  int i;
  while((fgetc(fptr1))!=EOF){
    for(i=0;i<26;i++){
      if(count[i]>0){
    fprintf(fptr2,"Ki tu %c xuat hien %d lan trong cau.\n",'a'+i,count[i]);
    printf("Ki tu %c xuat hien %d lan trong cau.\n", 'a'+i,count[i]);
      }
    }
  }
}
int main(int argc,char* argv[]){
  FILE *fptr1,*fptr2;
  char c;
  if(argc!=3){
    printf("Cau lenh chay chuong trinh sai.Nhap dung 3 tham so dong lenh.\n");
    return 0;
  }
  int reval=SUCCESS;
  if((fptr1=fopen(argv[1],"r"))==NULL){
    printf("Khong the mo duoc file %s.\n",argv[1]);
    reval=FAIL;
  }
  else{
  if((fptr2=fopen(argv[2],"w"))==NULL){
    printf("Khong the mo duoc file %s.\n",argv[2]);
    reval=FAIL;
  }
  else{
    while((c=fgetc(fptr1))!=EOF){
      demkitu(c);
      ketqua(fptr1, fptr2);
    }
  }
  }
  fclose(fptr1);
  fclose(fptr2);
  return reval;
}
