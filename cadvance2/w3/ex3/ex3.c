#include "extension_lib.h"

int main() {
	FILE *f;
	char filename[MAXLENGTH] = "words";

	if((f = openFile(filename, "r+")) == NULL) {
		return 1;
	}

	if(solve(f) != 0) {
		printf("Error occurs when executing program\n");
		return 1;
	}

	fclose(f);
	return 0;
}