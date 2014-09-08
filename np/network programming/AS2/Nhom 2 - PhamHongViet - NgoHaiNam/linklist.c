#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"linklist.h"

void getTime(char* str){
  struct tm* now = NULL;
  time_t time_value = 0;
  time_value = time(NULL);
  now = localtime(&time_value);
  sprintf(str, "%d-%d-%d#%d:%d:%d", now->tm_mday, now->tm_mon + 1, now->tm_year + 1900, now->tm_hour, now->tm_min, now->tm_sec);
}

void initList(){
  root = NULL;
}

void getID(char* t){
  struct timeval time;
  gettimeofday(&time, NULL);
  sprintf(t, "%d%d", time.tv_sec, time.tv_usec);	
}

ClientInfo* newInfo(char* id, char user[], char addr[], int size, char logfile[]){
  ClientInfo* info;
  int i;
  info = (ClientInfo*)malloc(sizeof(ClientInfo));
  info->id = (char*)malloc(strlen(id));
  strcpy(info->id, id);
  strcpy(info->user, user);
  strcpy(info->address, addr);
  info->size = size;
  info->table = (char*)malloc(size * size);
  for(i = 0; i < size * size; i++)
    (info->table)[i] = 0;
  strcpy(info->logfile, logfile);
  info->next = NULL;
}

ClientInfo* getInfo(char* id){
  ClientInfo* cur = root;
  while(cur != NULL){
    if(strcmp(cur->id,id) == 0)
      return cur;
    cur = cur->next;
  }
  return NULL;
}

void freeInfo(ClientInfo* i){
  free(i->table);
  free(i->id);
}

char* addInfo(char addr[], int size, char user[]){
  ClientInfo* i;
  ClientInfo* cur;  
  char logfile[100];
  char id[30];
  char time[50];
  getID(id);
  getTime(time);
  sprintf(logfile,"%s#%s#%s#%s.log", user, id, addr, time);
  i = newInfo(id, user, addr, size, logfile);

  cur = root;
  while(cur != NULL && cur->next != NULL)
    cur = cur->next;
  
  if(cur == NULL){
    i->next = NULL;
    root = i;  
  }
  else{
    cur->next = i;
    i->next = NULL;  
  }
  return i->id;
}

int removeInfo(char* id){
  ClientInfo *prev, *cur;
  cur = root;
  while(cur != NULL && strcmp(cur->id,id) != 0){
    prev = cur;
    cur = cur->next;    
  }

  if(cur == NULL)
    return -1;
  else if(cur == root){
    root = root->next;
    freeInfo(cur);
    free(cur); 
  }
  else{
    prev->next = cur->next;  
    freeInfo(cur);
    free(cur);  
  }

  return 0;
}

void printInfo(ClientInfo* i){
  if(i != NULL)
    printf("id= %s user = %s addr=%s size=%d log=%s\n", i->id, i->user, i->address, i->size, i->logfile);
}

/*
main(){ 
  int n;
  char* id[3];
  initList();
  printf("%s\n",id[0] = addInfo("127.0.0.1", 5, "asd"));
  printf("%s\n",id[1] = addInfo("127.0.0.1", 6, "qwe"));
  printf("%s\n",id[2] = addInfo("127.0.0.1", 7, "zxc"));
  for(n = 0; n < 3; n++){
    printInfo(getInfo(id[n]));    
  } 
  removeInfo(id[2]);
  for(n = 0; n < 3; n++){
    printInfo(getInfo(id[n]));    
  } 
}
*/

