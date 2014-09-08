#include "extension_lib.h"

void randomPhoneNumber(String *array, int n) {
	int i, j, temp;
	srand(time(NULL));

	for(i = 0; i < n; i++) {
		for(j = 0; j < 10; j++) {
			temp = rand() % 10;
			sprintf(array[i].content, "%s%d", array[i].content, temp);
		}
	}
}

void genPhoneCallData(String *array, int n, PhoneCall *phoneCall, int amount) {
	int i;

	srand(time(NULL));
	for(i = 0; i < amount; i++) {
		strcpy(phoneCall[i].caller.content, array[rand() % (n+1)].content);
		strcpy(phoneCall[i].called.content, array[rand() % (n+1)].content);
		phoneCall[i].beginTime.hour = rand() % 24;
		phoneCall[i].beginTime.minute = rand() % 60;
		phoneCall[i].beginTime.second = rand() % 60;
		phoneCall[i].during = rand() % 200 + 1;
	}
}


void selectionSort(PhoneCall *phoneCall, int n) {
	int i, j;
	int iMin;

	for(j = 0; j < n - 1; j++) {
		iMin = j;
		for(i = j + 1; i < n; i++) {
			if(phoneCall[i].during < phoneCall[iMin].during)
				iMin = i;
		}

		if(iMin != j)
			swap(&phoneCall[j], &phoneCall[iMin]);
	}
}

void swap(PhoneCall *a, PhoneCall *b) {
	PhoneCall temp = *a;
	*a = *b;
	*b = temp;
}

PhoneCall* reverseList(PhoneCall phoneCall) {

}

void printPhoneCallLog(PhoneCall *phoneCallList, int n) {
	int i;
	for(i = 0; i < n; i++) {
		printf("%s\t%s\t%d:%d:%d\t%4d\n", 
			phoneCallList[i].caller.content, 
			phoneCallList[i].called.content, 
			phoneCallList[i].beginTime.hour, 
			phoneCallList[i].beginTime.minute, 
			phoneCallList[i].beginTime.second, 
			phoneCallList[i].during);
	}
}

void insertionSort(PhoneCall *phoneCall, int n) {
	int i, j;

	for(i = 1; i < n; i++) {
		j = i;
		while ((j > 0) && (phoneCall[j-1].during > phoneCall[j].during)) {
			swap(&phoneCall[j], &phoneCall[j-1]);
			j--;
		}
	}
}

int choosePivot(int left, int right) {
	return (left + right) / 2;
}

void quickSort(PhoneCall *phoneCall, int left, int right) {
	int i, j;
	PhoneCall pivot;

	if(left < right) {
		swap(&phoneCall[left], &phoneCall[choosePivot(left, right)]);
		pivot = phoneCall[left];
		i = left + 1;
		j = right;

		while(i <= j) {
			while((phoneCall[i].during <= pivot.during) && (i <= right))
				i++;
			while((phoneCall[j].during > pivot.during) && (j >= left))
				j--;
			if(i < j)
				swap(&phoneCall[i], &phoneCall[j]);	
		}
		swap(&phoneCall[left], &phoneCall[j]);
		quickSort(phoneCall, left, j - 1);
		quickSort(phoneCall, j + 1, right);
	}
}

int saveRunningTime(FILE *f, double quickSortTime, double insertionSortTime, double selectionSortTime, int amount) {
	int n = 0, flag = 0;
	char temp[MAXLENGTH];

	if(f == NULL) 
		return 1;

	if((quickSortTime == -1) || (insertionSortTime == -1) || (selectionSortTime == -1)) 
		return 1;

	while(fscanf(f, "%s", temp) != EOF) {
		if(flag) {
			n = atoi(temp);
		}
		if(strcmp(temp, "times:") == 0) {
			flag = 1;
		} else {
			flag = 0;
		}
	}
	
	fprintf(f, "Running times: %d\nNumber of records: %d\nQuick sort: %fs - Insertion sort: %fs - Selection sort: %fs\n", 
		n + 1, 
		amount, 
		quickSortTime, 
		insertionSortTime, 
		selectionSortTime);
	return 0;
}

int extendRecord(FILE *f, int amount, int percents, PhoneCall *phoneCallList) {
	String *array;
	int m = amount * percents / 100;
	int i;

	if(percents <= 0) {
		return 1;
	}

	if((array = (String*) malloc((m + 1) * sizeof(String)))) {
		return 1;
	}

	while(fgetc(f) != EOF);
	
	genPhoneCallData(array, m, phoneCallList, amount);

    for(i = 0; i < m; i++) {
     	fprintf(f, "%s\t%s\t%d:%d:%d\t%d\n", 
   		phoneCallList[i].caller.content, 
   		phoneCallList[i].called.content, 
   		phoneCallList[i].beginTime.hour, 
  		phoneCallList[i].beginTime.minute, 
    	phoneCallList[i].beginTime.second, 
    	phoneCallList[i].during);
    }
    return 0;
}