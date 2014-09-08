#include "controller.h"

int createData(Jval *array, int type) {
	int n;

	printf("Please enter the size of array:\n");
	while((n = getInt()) <= 0) {
		printf("Please enter the positive number!\n");
	}

	switch(type) {
		case INTERGER:
		makeIntegerData(array, n);
		break;
		case STRING:
		makeStringData(array, n);
		break;
		case STRUCT:
		makeStructData(array, n);
		break;
		case NONE:
		printf("Can not create data\n");
		break;
		default:
		printf("Error occurs somewhere\n");
		break;
	}

	return n;
}

void makeIntegerData(Jval *array, int amount) {
	int i;

	for(i = 0; i < amount; i++) {
		printf("Item %d\n", i + 1);
		array[i] = new_jval_i(getInt());
	}
}

void makeStringData(Jval *array, int amount) {
	int i;
	char *temp;

	

	for(i = 0; i < amount; i++) {
		if((temp = myMalloc(sizeof(char), TEMP_CONTROLLER_SIZE)) == NULL) {
			return;
		}
		printf("Item %d\n", i + 1);
		fgets(temp, TEMP_CONTROLLER_SIZE, stdin);
		temp[strlen(temp) - 1] = '\0';
		// array[i] = new_jval_s(strdup(temp));
		array[i] = new_jval_s(temp);
	}
}

void makeStructData(Jval *array, int amount) {
	int i;
	TestStruct *temp;

	// if((temp = myMalloc(sizeof(TestStruct), 1)) == NULL) {
	// 	return;
	// }

	for(i = 0; i < amount; i++) {
		if((temp = myMalloc(sizeof(TestStruct), 1)) == NULL) {
			return;
		}
		printf("Item %d\n", i + 1);
		printf("Enter x: ");
		temp->x = getInt();
		printf("Enter y: ");
		temp->y = getInt();

		array[i] = new_jval_v(temp);
	}
}

void printController(Jval *array, int amount, int type) {
	switch(type) {
		case INTERGER:
		printIntJval(array, amount);
		break;
		case STRING:
		printStrJval(array, amount);
		break;
		case STRUCT:
		printStructJval(array, amount);
		break;
		case NONE:
		printf("Cannot print this shit\n");
		break;
		default:
		printf("Cannot print this shit\n");
		break;
	}
}

void printIntJval(Jval *array, int amount) {
	int i;

	printf("Jval list: \n");
	for(i = 0; i < amount; i++) {
		printf("Item %d: %d\n", i+1, jval_i(array[i]));
	}
}

void printStrJval(Jval *array, int amount) {
	int i;

	printf("Jval list: \n");
	for(i = 0; i < amount; i++) {
		printf("Item %d: %s\n", i+1, jval_s(array[i]));
	}
}

void printStructJval(Jval *array, int amount) {
	int i;
	TestStruct *temp;

	if((temp = myMalloc(sizeof(TestStruct), 1)) == NULL) {
		return;
	}

	printf("Jval list: \n");
	for(i = 0; i < amount; i++) {
		temp = jval_v(array[i]);
		printf("Item %d:\n\tx = %d\ty = %d\n", i+1, temp->x, temp->y);
	}
}

// Private
void printJval(Jval *array, int amount, void (*printData)(Jval*)) {
	int i;

	for(i = 0; i < amount; i++) {
		printf("Item %d: ", i + 1);
		printData(&array[i]);
	}
}

void sequentialSearchController(Jval *array, int amount, int type) {
	int tempInt;
	char *temp;
	TestStruct *tempStruct;

	int res;

	printf("Please enter the item which you want to find\n");

	switch(type) {
		case INTERGER:
		tempInt = getInt();
		if((res = seqSearchJval(array, amount, new_jval_i(tempInt), intCompare)) < 0) {
			printf("Not found!\n");
			return;
		}
		printf("Item found: \"%d\" at index %d\n", tempInt, res);
		break;
		case STRING:
		if((temp = myMalloc(sizeof(char), TEMP_CONTROLLER_SIZE)) == NULL) {
			return;
		}
		fgets(temp, TEMP_CONTROLLER_SIZE, stdin);
		temp[strlen(temp) - 1] = '\0';
		if((res = seqSearchJval(array, amount, new_jval_s(temp), strCompare)) < 0) {
			printf("Not found!\n");
			return;	
		}
		printf("Item found: \"%s\" at index %d\n", temp, res);
		break;
		case STRUCT:
		if((tempStruct = myMalloc(sizeof(TestStruct), 1)) == NULL) {
			return;
		}

		printf("x = ");
		tempStruct->x = getInt();
		printf("y = ");
		tempStruct->y = getInt();
		if((res = seqSearchJval(array, amount, new_jval_v(tempStruct), structCompare)) < 0) {
			printf("Not found!\n");
			return;
		}

		printf("Item found: \"x = %d, y = %d\" at index %d\n", tempStruct->x, tempStruct->y, res);
		break;
		case NONE:
		printf("Cannot find!\n");
		break;
		default:
		printf("Cannot find!\n");
		break;
	}
}

int intCompare(Jval *a, Jval *b) {
	int x = jval_i(*a);
	int y = jval_i(*b);

	return x - y;
}

int strCompare(Jval *a, Jval *b) {
	return strcmp(jval_s(*a), jval_s(*b));
}

int structCompare(Jval *a, Jval *b) {
	TestStruct *x = (TestStruct*)jval_v(*a);
	TestStruct *y = (TestStruct*)jval_v(*b);

	return utilityFunction(x->x, x->y) - utilityFunction(y->x, y->y);
}

int utilityFunction(int x, int y) {
	return 10000 * x + y;
}

void sortController(Jval *array, int amount, int type) {
	switch(type) {
		case INTERGER:
		quickSort3WayJval(array, 0, amount - 1, intCompare);
		printIntJval(array, amount);
		break;
		case STRING:
		quickSort3WayJval(array, 0, amount - 1, strCompare);
		printStrJval(array, amount);
		break;
		case STRUCT:
		quickSort3WayJval(array, 0, amount - 1, structCompare);
		printStructJval(array, amount);
		break;
		case NONE:
		break;
		default:
		break;
	}
}

void binarySearchController(Jval *array, int amount, int type) {
	int tempInt;
	char *temp;
	TestStruct *tempStruct;

	int res;

	printf("Please enter the item which you want to find\n");

	switch(type) {
		case INTERGER:
		tempInt = getInt();
		if((res = binarySearchJval(array, new_jval_i(tempInt), 0, amount - 1, intCompare)) < 0) {
			printf("Not found!\n");
			return;
		}
		printf("Item found: \"%d\" at index %d\n", tempInt, res);
		break;
		case STRING:
		if((temp = myMalloc(sizeof(char), TEMP_CONTROLLER_SIZE)) == NULL) {
			return;
		}
		fgets(temp, TEMP_CONTROLLER_SIZE, stdin);
		temp[strlen(temp) - 1] = '\0';
		if((res = binarySearchJval(array, new_jval_s(temp), 0, amount - 1, strCompare)) < 0) {
			printf("Not found!\n");
			return;	
		}
		printf("Item found: \"%s\" at index %d\n", temp, res);
		break;
		case STRUCT:
		if((tempStruct = myMalloc(sizeof(TestStruct), 1)) == NULL) {
			return;
		}

		printf("x = ");
		tempStruct->x = getInt();
		printf("y = ");
		tempStruct->y = getInt();
		if((res = binarySearchJval(array, new_jval_v(tempStruct), 0, amount - 1, structCompare)) < 0) {
			printf("Not found!\n");
			return;
		}

		printf("Item found: \"x = %d, y = %d\" at index %d\n", tempStruct->x, tempStruct->y, res);
		break;
		case NONE:
		printf("Cannot find!\n");
		break;
		default:
		printf("Cannot find!\n");
		break;
	}
}