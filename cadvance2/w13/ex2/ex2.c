#include "extension_lib.h"

int main() {
	FILE *f;

	if((f = openFile("class.txt", "r")) == NULL) {
		return 1;
	}

	if(solve(f) != 0) {
		printf("Error occurs when executing program\n");
		fclose(f);
		return 1;
	}

	fclose(f);
	return 0;
}