#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH 100

typedef struct  String{
	char str[100];	
} String;

//input s string

void inputString(char *str){
	printf("Input String \n");
	fgets(str, MAXLENGTH, stdin);
	str[strlen(str) - 1] = '\0';
}

int cutString(char *str, char splitChar, String output[]){
	int i, n, j;

	j = 0;
	n = 0;

	for( i= 0; i< strlen(str); i++){
		if(str[i]== splitChar){
			output[n++].str[j] = '\0';
			j = 0;
			continue;
		}
		output[n].str[j++] = str[i];
	}

	return n+1;
} 

int myCutter(char *str, String *output) {
	int counter = 0;
	int i;
	char temp[MAXLENGTH], *ptr;

	strcpy(temp, str);
	ptr = temp;

	for(i = 0; i < strlen(temp); i++) {
		if(temp[i] == ' ') {
			temp[i] = '\0';
			strcpy(output[counter++].str, ptr);
			ptr = temp + i + 1;
		}
	}

	strcpy(output[counter++].str, ptr);

	return counter;
}

void printResult(String *output, int amount) {
	int i;

	for(i = 0; i < amount; i++) {
		printf("%s\n", output[i].str);
	}
}

int main(){
//input a string input 
	String output[100];
	int sizeOfOutput;
	char str[100];

	inputString(str);
	sizeOfOutput = cutString(str, ' ', output);
	// sizeOfOutput = myCutter(str, output);
	printResult(output, sizeOfOutput);

	return 0;
}