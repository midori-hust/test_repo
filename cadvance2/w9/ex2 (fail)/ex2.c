#include "extension_lib.h"

//"words.utf-8.txt";

int main(int argc, char *argv[]) {
	FILE *f;

	if(argc < 2) {
		printf("#Usage:\n\t./<program name> <file name>\n");
		return 1;
	}

	if((f = openFile(argv[1], "r")) == NULL) {
		return 1;
	}

	if(solve(f) != 0) {
		printf("Error occurs when executing program\n");
		return 1;
	}

	fclose(f);
	return 0;
}