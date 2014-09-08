#include "extension_lib.h"

BigObj* mallocBigObjStruct(int amount) {
  BigObj *result;

  if((result = (BigObj*) malloc((amount + 1) * sizeof(BigObj))) == NULL) {
    printf("Cannot allocated memory\n");
    return NULL;
  }

  return result;
}

void genBigObjData(BigObj *bigObj, int amount) {
	int i, j;

	srand(time(NULL));
	for(i = 0; i < amount; i++) {
		bigObj[i].key = rand() % MAX;
		for(j = 0; j < MAXSIZE; j++) {
			bigObj[i].content[j] = 0;//rand() % MAX;
		}
	}
}

void printListObj(BigObj *bigObj, int amount) {
	int i;

	for(i = 0; i < amount; i++) {
		printf("Obj %d: key %d\n", i, bigObj[i].key);
	}
}

BigObj* clone(BigObj *source, int amount) {
	int i, j;
	BigObj *des;

	if((des = mallocListObj(amount)) == NULL) {
		return NULL;
	}

	srand(time(NULL));
	for(i = 0; i < amount - 1; i++) {
		des[i].key = source[i].key;
		for(j = 0; j < MAXSIZE; i++) {
			des[i].content[j] = 0;
		}
	}
	return des;
} // Not work

void selectionSort(BigObj *bigObj, int n) {
	int i, j;
	int iMin;

	for(j = 0; j < n - 1; j++) {
		iMin = j;
		for(i = j + 1; i < n; i++) {
			if(bigObj[i].key < bigObj[iMin].key)
				iMin = i;
		}

		if(iMin != j)
			swap(&bigObj[j], &bigObj[iMin]);
	}
}

void swap(BigObj *a, BigObj *b) {
	BigObj temp = *a;
	*a = *b;
	*b = temp;
}

int choosePivot(int left, int right) {
	return (left + right) / 2;
}

void quickSort(BigObj *bigObj, int left, int right) {
	int i, j;
	BigObj pivot;

	if(left < right) {
		swap(&bigObj[left], &bigObj[choosePivot(left, right)]);
		pivot = bigObj[left];
		i = left + 1;
		j = right;

		while(i <= j) {
			while((bigObj[i].key <= pivot.key) && (i <= right))
				i++;
			while((bigObj[j].key > pivot.key) && (j >= left))
				j--;
			if(i < j)
				swap(&bigObj[i], &bigObj[j]);	
		}
		swap(&bigObj[left], &bigObj[j]);
		quickSort(bigObj, left, j - 1);
		quickSort(bigObj, j + 1, right);
	}
}

int solve() {
	BigObj *bigObjList, *temp;
	clock_t begin, end;
	double mesureTime;
	int extendSize = getTheNumberOfTimesExtending();

	if((bigObjList = mallocListObj(extendSize)) == NULL) {
		return 1;
	}

	printf("Size of data: %d - size of data content: %d\n", extendSize, MAXSIZE);
	genBigObjData(bigObjList, extendSize);
	begin = clock();
	selectionSort(bigObjList, extendSize);
	end = clock();
	mesureTime = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("Measuring time: selection sort: %f\n", mesureTime);
	
	genBigObjData(bigObjList, extendSize);
	begin = clock();
	quickSort(bigObjList, 0, extendSize - 1);
	end = clock();
	mesureTime = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("Measuring time: quick sort: %f\n", mesureTime);
	
	// printListObj(bigObjList, extendSize); // Debugging
	free(bigObjList);
	return 0;
}

BigObj* mallocListObj(int amount) {
  BigObj *result;
  int i;
  int remain = amount;

  if((result = mallocBigObjStruct(MAX)) == NULL) {
    return NULL;
  }

  if(amount < MAX)
  	return result;

  for(i = 1; i <= amount / MAX; i++) {
  	result = extendList(result, i * MAX, (i + 1) * MAX); // It works
  	remain = amount - i * MAX;
  	if(remain < 0)
  		break;
  }

  if(remain > 0)
  	result = extendList(result, amount - remain, amount);
  
  return result;
}

BigObj* extendList(BigObj *bigObj, int size, int new_size) {
	BigObj *result;

	if(size > new_size) {
		printf("Cannot allocated memory\n");
		return bigObj;
	}

	if((result = realloc(bigObj, new_size * sizeof(BigObj))) == NULL) {
		printf("Memory exhausted\n");
		// free(bigObj);
		return bigObj;
	}

	return result;
}

int getTheNumberOfTimesExtending() {
	int n;

	printf("How many times of MAX (%d records) do you want to generate?\n", MAX);
	while((n = getInt()) > 7 || n <= 0) {
		if(n <= 0) 
			printf("Do not enter the too small number!\n");
		else
			printf("This is so big, please enter the less number!\n");
	}

	return n * MAX;
}