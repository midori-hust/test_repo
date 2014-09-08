#include "extension_lib.h"

int main(int argc, char *argv[]) {
	char *fileName;

	if(argc < 2) {
		fileName = NULL;
	} else {
		fileName = argv[1];
		// if((f = openFile(argv[1], "r")) == NULL) {
		// 	return 1;
		// }
	}

	if(solve(fileName) != 0) {
		printf("Error occurs when executing program\n");
		return 1;
	}

	return 0;
}