#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLENGTH 100

typedef struct _string {
	char content[MAXLENGTH];
} String;

int main() {
	FILE *f;
	//int ch; // Thao's style
	char ch; // Hung's style
	char filename[MAXLENGTH] = "text.txt";
	int i = 0, n = 0;
	String *arrayList;

	if((f = fopen(filename, "r+")) == NULL) {
		printf("Cannot open this file\n");
		return 1;
	}

	while ((ch = fgetc(f)) != EOF) {
		if(ch == '\n')
			i++;
	}

	arrayList = (String*) malloc((i+1)* sizeof(String));

	rewind(f);
	i = 0;

	while ((ch = fgetc(f)) != EOF) {
		if(ch == 10) {
			arrayList[n].content[i] = '\0';
			n++;
			i = 0;
		} else {
			//arrayList[n].content[i] = (char)ch; // Thao's style
			arrayList[n].content[i] = ch; // Hung's style
			i++;
		}
	}

	arrayList[n].content[i] = '\0';

	for(i = 0; i < n+1; i++) {
		printf("%s\n", arrayList[i].content);
	}

	fclose(f);
	return 0;
}