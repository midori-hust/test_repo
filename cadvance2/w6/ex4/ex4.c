#include "extension_lib.h"

int main() {
	FILE *f_domain, *f_user, *fout1, *fout2;
	char filename1[MAXLENGTH] = "domain.txt", 
		filename2[MAXLENGTH] = "user.txt",
		filename3[MAXLENGTH] = "mail.txt",
		filename4[MAXLENGTH] = "mailnodup.txt";

	if((f_domain = openFile(filename1, "r+")) == NULL) {
		return 1;
	}

	if((f_user = openFile(filename2, "r+")) == NULL) {
		return 1;
	}

	if((fout1 = openFile(filename3, "w+")) == NULL) {
		return 1;
	}

	if((fout2 = openFile(filename4, "w+")) == NULL) {
		return 1;
	}

	if(solve(f_domain, f_user, fout1, fout2) != 0) {
		printf("Error occurs when executing program\n");
		return 1;
	}

	fclose(f_user);
	fclose(f_domain);
	fclose(fout1);
	fclose(fout2);
	return 0;
}