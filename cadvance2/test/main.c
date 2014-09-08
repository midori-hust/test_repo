#include "extension_lib.h"

int main() {
	FILE *f;
	if((f = openFile("jobs.txt", "r")) == NULL) {
		return 1;
	}

	if(solve(f) != 0) {
		printf("Error occurs when executing program\n");
		return 1;
	}

	fclose(f);
	return 0;
}