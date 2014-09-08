#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 100

void getInput(char *str, char *replaceStr, char *replaceChar);
void getNewString(char *src, char *des, char replaceChar, char *replaceStr);

int main() {
	char input[MAXLENGTH];
	char output[MAXLENGTH];
	char replaceStr[MAXLENGTH];
	char replaceChar;

	getInput(input, replaceStr, &replaceChar);

	getNewString(input, output, replaceChar, replaceStr);

	printf("The output after replace char \'%c\' by string \"%s\":\n\t%s\n", replaceChar, replaceStr, output);
	return 0;
}

void getInput(char *str, char *replaceStr, char *replaceChar) {
	printf("Please enter the input string:\n");
	fgets(str, MAXLENGTH, stdin);
	str[strlen(str) - 1] = '\0';

	printf("Please enter the replace char:\n");
	scanf("%c", replaceChar);
	while(getchar() != '\n');

	printf("Please enter the replace string:\n");
	fgets(replaceStr, MAXLENGTH, stdin);
	replaceStr[strlen(replaceStr) - 1] = '\0';	
}

void getNewString(char *src, char *des, char replaceChar, char *replaceStr) {
	int i, j = 0, k;

	for(i = 0; i < strlen(src); i++) {
		if(src[i] == replaceChar) {
			for(k = 0; k < strlen(replaceStr); k++) {
				des[j++] = replaceStr[k];
			}
			continue;
		}

		des[j++] = src[i];
	}
	des[j] = '\0';
}