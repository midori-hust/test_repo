#include <stdio.h>
#include <string.h>

/*
* Original
void xoaEnter (char*);

char* catLayTen (char str[]);

main(){
	char FullName[30];
	char FirstName[10];
	printf("FullName?\n");
	fgets(FullName,30,stdin);
	xoaEnter(&FullName[0]);
	&FirstName[0] = catLayTen(FullName);
	printf("%s\n",FirstName );
}

void xoaEnter (char *A){
	for(;;A++){
		if(*A == '\0'){
			*(A-1) = '\0';
			return;
		}
	}
}

char* catLayTen (char str[]){
	int i;
	i = strlen(str);
	for(; i >0 && str[i-1] != ' ' ; i--);
	return &str[i];
}
*/

char* catLayTen (char str[]);

main(){
	char FullName[30];
	char *FirstName;
	printf("FullName?\n");
	fgets(FullName,30,stdin);
	FullName[strlen(FullName) - 1] = '\0';
	FirstName = catLayTen(FullName);
	printf("%s\n",FirstName );
}

char* catLayTen (char str[]){
	int i;
	// i = strlen(str);
	for(i = strlen(str); i >0 && str[i-1] != ' ' ; i--);
	return &str[i];
}