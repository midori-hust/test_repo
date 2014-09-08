#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH 100

int main(int argc, char const *argv[])
{
	char input[MAXLENGTH];
	char *ptr;
	int i;
	int n;

	printf("Hay nhap vao 1 xau.\n");
	gets(input);

	ptr = input;
	while(i<strlen(input))	{
		if(input[i]==' ') {
			input[i] = '\0';
			printf("%s\n", input);
			ptr = ptr + i + 1;
		}
		i++;
	}


/*
	for(i=0; i<strlen(input); i++) {
		if(input[i] == ' ') {
			input[i] = '\0';
			printf("%s\n", ptr);
			ptr = input + i + 1;
			//break;
		}
	}

	//ptr = input + n + 1;
	//printf("%s\n", ptr);
*/
	return 0;
}