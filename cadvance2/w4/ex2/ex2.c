#include "extension_lib.h"

int main() {
	FILE *f;
	char fileName[MAXLENGTH] = "data.txt";

	if((f = openFile(fileName, "w+")) == NULL) {
		return 1;
	}

	if(solve(f) != 0) {
		printf("Error occurs when program's running!\n");
		fclose(f);
		return 1;
	}

	fclose(f);
	return 0;
}