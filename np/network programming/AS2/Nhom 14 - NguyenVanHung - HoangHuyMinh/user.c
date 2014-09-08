#include"user.h"
#include<ctype.h>
#include<string.h>
USER* root;
void creatBtreeUser(BTA* btUser){
  IS is;
  USER* user;
  int i = 0;
  btinit();
  is = new_inputstruct("user.txt");
  if(is == NULL){
    printf("Not exsit this file\n");
    return;
  } 
  while((get_line(is) >= 0)){
    user = (USER*)malloc(sizeof(USER)); 
    strcpy(user->userName,is->fields[0]);
    strcpy(user->passWord,is->fields[1]);
    user->rights = atoi(is->fields[2]);
    btins(btUser,user->userName,(char*)user,sizeof(USER)); 
    if(i == 0)
      root = user;
    else i++;
  }
  jettison_inputstruct(is);
}
int checkLogin(BTA* btUser, USER* users){
  int rights;
  int check;
  USER* usr;
  int size;

  if(users == NULL)
    return 0;
  usr = (USER*)malloc(sizeof(USER)); 
  check = btsel(btUser,users->userName,(char*)usr,sizeof(USER),&size);
  if(check == 0){
    if(strcmp(users->passWord,usr->passWord) == 0){
      printf("Login successful\n");
      return usr->rights;
    }
    else{
      printf("Password incorect!!!Please input try again\n");
      return -1;
    }
  }
  else{
    printf("User not exsit!!!\n");
    return -2;
  }
}
int newUser(BTA* btUser, USER* users){
  int check;
 
  if(strcmp(users->userName,"")==0 || strcmp(users->passWord,"")==0){
    printf("Please input both user and pass!!\n");
    return -1;
  }
  check = btins(btUser,users->userName,(char*)users,sizeof(USER));
  if(check == 0){
    printf("You register successful\n");
    return 0;
  }
  else{
    printf("User was exsited!!Try register\n");
    return -2;
  }
}
int deleteUser(BTA* btUser, USER* users){
  int check = btdel(btUser,users->userName);
  if(check != 0){
    printf("User don't exsit\n");
    return 0;
  }
  else{
    printf("Delete successful\n");
    return 1;
  }
}

/*main(){
  BTA* btUser;
  USER* user;
  char name[30];
  int size;

  btinit();  
  btUser = btopn("user.dat",0,0); 
  if(btUser == NULL){
    btUser = btcrt("user.dat",0,0);
    creatBtreeUser(btUser);    
  }
  user = (USER*)malloc(sizeof(USER));
  printf("Register\n");
  do{
    printf("Username:");gets(user->userName);fflush(stdin);
    printf("Password:");gets(user->passWord);fflush(stdin);
  }while(newUser(btUser,user) == -1);
  printf("Login\n");
  do{
    printf("Username:");gets(user->userName);fflush(stdin);
    printf("Password:");gets(user->passWord);fflush(stdin);
  }while(checkLogin(btUser,user) == -1); 
  btcls(btUser) ;
}

*/
