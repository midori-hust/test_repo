#include"soundex.h"
#include<stdio.h>
char* coding(char* word){
  char* s,*ch;
  int n=1,i,len;
  s=(char*)malloc(sizeof(char)*10);
  len=strlen(word);
  ch=strdup(word);
  if(len>=1){
    s[0]=ch[0];
    for(i=1;i<len&&n<4;i++){
      ch[i]=toupper(ch[i]);
      switch(ch[i]){
      case 'A':
      case 'I':
      case 'E':
      case 'O':
      case 'U':
      case 'H':
      case 'W':
      case 'Y':
	break;
      case 'B':
      case 'F':
      case 'P':
      case 'V':
	if(s[n-1]!='1')
	  s[n++]='1';
      break;
      case 'C':
      case 'G':
      case 'J':
      case 'K':
      case 'Q':
      case 'S':
      case 'X':
      case 'Z':
	if(s[n-1]!='2')
	  s[n++]='2';
      break;
      case 'D':
      case 'T':
	if(s[n-1]!='3')
	  s[n++]='3';
      break;
      case 'L':
	if(s[n-1]!='4')
	  s[n++]='4';
	break;
      case 'M':
      case 'N':
	if(s[n-1]!='5')
	  s[n++]='5';
      break;
      case 'R':
	if(s[n-1]!='6')
	  s[n++]='6';
	break;
      }
    }
    if(n<4)
      for(i=n;i<4;i++)
	s[i]='0';
    free(ch);
    return s;
  }
  else return "";
}
void creat_btsoundex(BTA* btactSoundex){
  IS is;
  dictsd* dicsd;
  int i;
  btinit();
  is=new_inputstruct("dictionary.txt");
  if(is==NULL){
    printf("Not exsit this file\n");return ;
  }
  while((get_line(is)>=0)){
    dicsd=(dictsd*)malloc(sizeof(dictsd));
    strcpy(dicsd->word,is->fields[0]);
    strcpy(dicsd->code,coding(is->fields[0]));
    for(i=1;i<is->NF;i++){
      strcat(dicsd->mean,is->fields[i]);
      if(i!=is->NF-1)
	strcat(dicsd->mean," ");
    }     
    btins(btactSoundex,dicsd->code,(char*)dicsd,sizeof(dictsd));
  }  
  jettison_inputstruct(is); 
}

