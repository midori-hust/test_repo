#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "message.h"

Message createMessage(int n_max)
{
	Message newMessage;
	newMessage.n_max = n_max;
	newMessage.n = 0;
	newMessage.freeAll =freeAll;
	newMessage.setParameter = setParameter;
	newMessage.getParameter = getParameter;
	newMessage.parseString = parseString;
	newMessage.toString = toString;
	newMessage.displayMessage = displayMessage;
	newMessage.indexParam = (int*)malloc(n_max * sizeof(int));
	bzero(newMessage.indexParam,n_max * sizeof (int));
	newMessage.paramName = (PtrChar*)malloc(n_max * sizeof (PtrChar));
	newMessage.paramValue = (PtrChar*)malloc(n_max * sizeof(PtrChar));
	return newMessage;
}

void freeAll(Message *self)
{
	int i =0;
	for (i = 0; i < self->n;i++)
	{
		free(self->paramName[i]);
		free(self->paramValue[i]);
	}
	free(self->indexParam);
	free(self->paramName);
	free(self->paramValue);
	self->n_max =0;
	self->n = 0;
}

int setParameter(Message *self, char *param_name, char *param_value)
{
	int i = 0;
	int compare =-1;
	for (i = 0; i < self ->n;i++)
	{
		int compare = strcmp(param_name,self->paramName[self->indexParam[i]]);
		if (compare <=0)
		{
			break;
		}
	}
	if (compare == 0 ) // This paramName is already exist
	{
		i = self->indexParam[i];
		free(self->paramValue[i]);
		self->paramValue[i] = strdup(param_value);
		return 1;
	}
	if (compare != 0)  // Create new parameter
	{
		if  (self->n == self->n_max) return -1;
		self -> paramName[self->n] = strdup(param_name);
		self->paramValue[self->n ] = strdup(param_value);		
		int j = 0;
		for (j = self->n ; j  > i ;j--)
		{
			self->indexParam[j] = self->indexParam[j-1];
		}
		self->indexParam[i] = self->n++;
		return 0;
	}
	return 0;
}

char* getParameter(Message *self, char *param_name)
{
	int low = 0;
	int high = self -> n -1;
	int compare = -1;
	int indexMid;
	do
	{
		indexMid = (high + low)/2;
		compare = strcmp(param_name,self->paramName[self -> indexParam[indexMid]]);
		if (compare == 0)
		{
			return strdup(self->paramValue[self->indexParam[indexMid]]);
		}
		else
		if (compare <0 )
		{
			high = indexMid -1;
		}
		else 
			{
				low = indexMid + 1;	
			}
	}
	while (high >= low);
	return NULL;
}

char *toString(Message *self) // Dynamic memory allocate, you can free it after use
{
	int i = 0;
	int len = 0;
	for (i = 0; i < self->n;i++)
	{
		len += strlen(self->paramValue[i]) + strlen(self -> paramName[i]) + 2;
	}
	len+=1; // Add to \0
	char *messageString = (char *) malloc (sizeof (char ) * len);
	*messageString = 0;
	for (i = 0; i< self->n;i++)
	{
		strcat(messageString,self->paramName[i]);
		strcat(messageString,"=");
		strcat(messageString,self->paramValue[i]);
		strcat(messageString,";");
	}
	return messageString;
}

int parseString(Message *self,char *str)
{
	char *Str = (char *) malloc((strlen(str) + 1) * sizeof (char));
	strcpy(Str,str);
	printf("String : %s\n",Str);
	char *equal;
	char *semicolon;
	char *tempStr = Str;
	char *param_name;
	char *param_value;
	do
	{
		param_name = tempStr;
		equal = strchr(tempStr,'=');
		if (equal == NULL) break;
		*equal = 0;
		equal++;
		param_value = equal;
		semicolon = strchr(equal,';');
		*semicolon = 0;
		self->setParameter(self,param_name,param_value);
		tempStr = semicolon + 1;
	}
	while (1);
	free(Str);
	return 0;
}

void displayMessage(Message *self)
{
	printf("Message view\n");
	printf("Message capacity : %d couple\n",self -> n_max);
	int i = 0;
	for (i = 0; i < self -> n;i++)
	{
		printf("Name : %s -> value : %s\n",self -> paramName[i], self -> paramValue[i]);
	}
}
