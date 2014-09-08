#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convertToLower(char *str){
	int i;

	for(i=0; i< strlen(str) ; i++ )
		tolower(str[i]);
}

void countLetter(char *str, int output[],int n){
	int i;

	for(i = 0; i<n; i++)
		output[i] = 0;

	for(i =0; i<strlen(str); i++)
		output[str[i] - 'a'] ++;
}

void printfResult(int output[], int n){
	int i;

	for(i=0; i<n; i++)
		if(output[i]!= 0) 
			printf("Letter %c : %d \n", i+'a', output[i]);
}

int main(){
	char str[100];
	int output[26];

	printf("input string \n");
	gets(str);
	countLetter(str, output,26);
	printfResult(output, 26);

	return 0;
}

