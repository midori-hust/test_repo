#include "extension_lib.h"

int main() {
	// FILE *f;
	// char fileName[MAXLENGTH] = "data.txt";

	// if((f = openFile(fileName, "w+")) == NULL) {
	// 	return 1;
	// }

	if(solve() != 0) {
		printf("Error occurs when program's running!\n");
		return 1;
	}

	return 0;
}