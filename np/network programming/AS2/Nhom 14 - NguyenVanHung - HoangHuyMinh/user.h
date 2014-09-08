#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"./libfdr/fields.h"
#include"./bt-3.0.1/inc/btree.h"

typedef struct{
  char userName[100];
  char passWord[50];
  int rights;				// right=0: User can search
					// right=1: User can search,edit
					// right=2: Users are admins.
                                        // They can search,edit,delete,update.Delete another user
}USER;
void creatBtreeUser(BTA* btUser);
int checkLogin(BTA* btUser,USER* users);	// Return rights of user if not error occurr
					// Return -1 if error occurr
int newUser(BTA* btUser, USER* users);
int deleteUser(BTA* btUser, USER* users);
