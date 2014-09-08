#include"operation.h"

BTA* btUser;
BTA* btDic;
BTA* btSoundex;

int searchWord(BTA* btDic,BTA* btSoundex,
	       dict* foundWord,dictsd* hintWord,char word[]){
  dict* dic;
  dictsd* dicsd;
  char code[10];
  int size;
  int found;

  found = btsel(btDic,word,(char*)(foundWord),sizeof(dict),&size);
  if(found == 0){
    printf("Found:%-15s%s\n",(foundWord)->word,(foundWord)->mean);
    return 1;
  }
  else{
    printf("Error!!Not found\n");
    strcpy(code,coding(word));    
    found = btsel(btSoundex,code,(char*)(hintWord),sizeof(dictsd),&size);
    if(found == 0){
      printf("You want to find: %-15s%s\n",hintWord->word,hintWord->mean);
      return 0;
    }
    else return -1;
  }
}
int editWord(BTA* btDic,BTA* btSoundex,dict* edittedWord,dict* word, int right){
  int found;
  int size;
  dictsd* dicsd;
  char* code;

  if(right == 1 || right == 2){
    edittedWord = (dict*)malloc(sizeof(dict));
    found = btsel(btDic,word->word,(char*)edittedWord,sizeof(dict),&size);
    if(found != 0){
      printf("Not exsit this word\n");
      return 0;
    }

    strcat(edittedWord->mean,", ");
    strcat(edittedWord->mean,word->mean);
    btupd(btDic,edittedWord->word,(char*)edittedWord,sizeof(dict));

    dicsd = (dictsd*)malloc(sizeof(dictsd));
    code = coding(word->word);
    found = btsel(btSoundex,code,(char*)dicsd,sizeof(dictsd),&size);
    if(strcmp(word->word,dicsd->word) == 0){
      strcpy(dicsd->word,edittedWord->word);
      strcpy(dicsd->mean,edittedWord->mean);
      btupd(btSoundex,code,(char*)dicsd,sizeof(dictsd));
    }
    return 1;
  }
  else{
    printf("You must login to complete this feature\n");
    return -1;
  }
  
}
int deleteWord(BTA* btDic,BTA* btSoundex,char word[], int right){
  int found;
  int size;
  dictsd* dicsd;
  char* code;

  if(right != 2){
    printf("Don't allow you to operate this feature\n");
    return -1;
  }
  found = btdel(btDic,word);
  if(found != 0){
    printf("Don't exsit this word\n");
    return -1;
  }
  dicsd = (dictsd*)malloc(sizeof(dictsd));
  code = coding(word);
  found = btsel(btSoundex,code,(char*)dicsd,sizeof(dictsd),&size);
  if(strcmp(word,dicsd->word) == 0){
    btdel(btSoundex,code);
  }
  return 0;
}
int addWord(BTA* btDic,BTA* btSoundex,dict* newWord, int right){
  int found;
  int size;
  dict* dic;
  dictsd* dicsd;  
  if(right == 1||right == 2){
    dic = (dict*)malloc(sizeof(dict));
    if((found = btsel(btDic,newWord->word,(char*)dic,sizeof(dict),&size))!=0){
      btins(btDic,newWord->word,(char*)newWord,sizeof(dict));

      dicsd = (dictsd*)malloc(sizeof(dictsd));
      strcpy(dicsd->word,newWord->word);
      strcpy(dicsd->mean,newWord->mean);
      strcpy(dicsd->code,coding(newWord->word));
      btins(btSoundex,dicsd->code,(char*)dicsd,sizeof(dictsd));
	return 1;
    }
    else{
      printf("This word are exsited!!\n");
      return 0;
    }
  }
  else{
    printf("Don't allow you to add\n");
    return -1;
  }
  
}
