#ifndef MESSAGE
#define MESSAGE
#include <stdio.h>
typedef char* PtrChar;
typedef struct Message
{
	int n_max;
	int n;
	char **paramValue;
	int *indexParam; // It contain indexs in paramName array order with paramName
	char **paramName;
	char* (*getParameter)(struct Message *, char *);
	int (*setParameter)(struct Message *, char* , char *);
	void (*freeAll)(struct Message *message);
	char* (*toString)(struct Message *);
	int (*parseString)(struct Message *, char *);
	void (*displayMessage)(struct Message *);
}Message;
Message createMessage(int n_max);
void freeAll(Message *self);
int setParameter(Message *self, char *param_name, char *param_value);
char* getParameter(Message *self, char *param_name);
char *toString(Message *self); // Dynamic memory allocate, you can free it after use
int parseString(Message *self,char *str);
void displayMessage(Message *self);
#endif
