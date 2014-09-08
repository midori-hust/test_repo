#include "extension_lib.h"

int solve() {
	long int num;

	printf("Please enter the number:\n");
	num = getLongInt();

	printf("The lowest number which can divide for %ld and contains only 1 and 0 is %ld\n", num, getTheLessMultiple(num));

	return 0;
}

long int getLongInt() {
	long int res;
	
	while(scanf("%ld", &res) != 1) {
		printf("Invalid integer! Please enter again!\n");
		while(getchar() != '\n');
	}
	while(getchar() != '\n');

	return res;
}

long int getTheLessMultiple(long int num) {
	long int i;
	long int res;

	if(num < 0)
		return -1;

	if(num < 2)
		return num;

	for(i = 2; ; i++) {
		if(((res = convertToPsuedoBin(i)) % num) == 0)
			return res;
	}
}

long int convertToPsuedoBin(long int num) {
	int i;
	long int res = 0;
	long int temp = num;

	for(i = 0; i < 32; i++) {
		if(temp & 0x80000000)
			res = res * 10 + 1;
		else
			res *= 10;
		temp <<= 1;
	}

	return res;
}