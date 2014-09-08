#include<stdio.h>
#include"creatbtdic.h"

BTA* btdic;
void creat_btree(BTA* btact){
  IS is;
  dict* dic;
  int i;
  btinit();
  is=new_inputstruct("dictionary.txt");
  if(is==NULL){
    printf("Not exsit this file\n");return ;
  } 
  while((get_line(is)>=0)){
    dic=(dict*)malloc(sizeof(dict)); 
    strcpy(dic->word,is->fields[0]);
    for(i=1;i<is->NF;i++){
      strcat(dic->mean,is->fields[i]);
      if(i!=is->NF-1)
	strcat(dic->mean," ");
    }            
    btins(btact,dic->word,(char*)dic,sizeof(dict));
	  //printf("%s\n",dic->word);
  }  
  jettison_inputstruct(is); 
}
/*main(){
  BTA* btdic;
  btinit();
  btdic=btopn("dict.dat",0,0); 
  if(btdic==NULL)
    {
      btdic=btcrt("dict.dat",0,0);   
      creat_btree(btdic);
    }
    }*/
