#include "extension_lib.h"
#include "my_input_lib.h"

int main() {
	FILE *fin1, *fin2, *fout;
	char filename1[MAXLENGTH] = "phone.txt", filename2[MAXLENGTH] = "phonecall.log", filename3[MAXLENGTH] = "RunningTime.txt";
	String *array; // Phone list
	PhoneCall *phoneCallList; // Phone call log list
    PhoneCall *extendPhoneCallList;

	int choice;
	int n, i, newRecord;
	int percents = 0;
    int flag = 0;

	clock_t begin, end;
	double mesureTime;
	double quickSortRunningTime = -1, insertionSortRunningTime = -1, selectionSortRunningTime = -1;

	if((fin1 = fopen(filename1, "r+")) == NULL) {
		printf("Cannot open file %s\n", filename1);
		return 1;
	}

	if((fin2 = fopen(filename2, "w+")) == NULL) {
		printf("Cannot open file %s\n", filename2);
		return 1;
	}

	if((fout = fopen(filename3, "r+")) == NULL) {
		printf("Cannot open file %s\n", filename3);
		return 1;
	}

	if((array = (String*) malloc((10001) * sizeof(String))) == NULL) {
		printf("Cannot allocated memory\n");
		return 1;
	}

	i = 0;
	while((fscanf(fin1, "%s\n", array[i++].content)) != EOF);


	while(1) {
      switch(choice = menu()) {
        case 1:
        printf("You choose option %d\n", choice);
        if(flag) {
            printf("You've just selected the data. Please choose option 5 to extend the database\n");
            continue;
        }
        printf("Please enter the number of the phone call (100, 10000, 50000):\n");
        n = getInt();
        if((n != 100) && (n != 10000) && (n != 50000)) {
        	printf("This is not an answer. Program's continue\n");
        	continue;
        }
        if((phoneCallList = (PhoneCall*) malloc((n + 1) * sizeof(PhoneCall))) == NULL) {
			printf("Cannot allocated memory\n");
			return 1;
		}
        genPhoneCallData(array, 10000, phoneCallList, n);

        for(i = 0; i < n; i++) {
        	fprintf(fin2, "%s\t%s\t%d:%d:%d\t%d\n", 
        		phoneCallList[i].caller.content, 
        		phoneCallList[i].called.content, 
        		phoneCallList[i].beginTime.hour, 
        		phoneCallList[i].beginTime.minute, 
        		phoneCallList[i].beginTime.second, 
        		phoneCallList[i].during);
        }
        rewind(fin2);
        printf("Generated successfully\n");
        flag = 1;
        continue;
        case 2:
        printf("You choose option %d\n", choice);
        i = 0;
        
        free(phoneCallList);
        
        if((phoneCallList = (PhoneCall*) malloc((n + 1) * sizeof(PhoneCall))) == NULL) {
            printf("Cannot allocated memory\n");
            return 1;
        }

        while((fscanf(fin2, "%s\t%s\t%d:%d:%d\t%d\n", 
        	phoneCallList[i].caller.content, 
        	phoneCallList[i].called.content, 
        	&phoneCallList[i].beginTime.hour, 
        	&phoneCallList[i].beginTime.minute, 
        	&phoneCallList[i].beginTime.second, 
        	&phoneCallList[i].during)) != EOF) {
        	i++;
        }
        rewind(fin2);
        begin = clock();
        quickSort(phoneCallList, 0, n-1);
        end = clock();
        mesureTime = (double) (end - begin) / CLOCKS_PER_SEC;
        printf("Mesuring time: %f\n", mesureTime);
        quickSortRunningTime = mesureTime;
        continue;
        case 3:
        printf("You choose option %d\n", choice);
        i = 0;

        free(phoneCallList);
        
        if((phoneCallList = (PhoneCall*) malloc((n + 1) * sizeof(PhoneCall))) == NULL) {
            printf("Cannot allocated memory\n");
            return 1;
        }

        while((fscanf(fin2, "%s\t%s\t%d:%d:%d\t%d\n", 
        	phoneCallList[i].caller.content, 
        	phoneCallList[i].called.content, 
        	&phoneCallList[i].beginTime.hour, 
        	&phoneCallList[i].beginTime.minute, 
        	&phoneCallList[i].beginTime.second, 
        	&phoneCallList[i].during)) != EOF) {
        	i++;
        }
        rewind(fin2);
        begin = clock();
        insertionSort(phoneCallList, n);
        end = clock();
        mesureTime = (double) (end - begin) / CLOCKS_PER_SEC;
        printf("Mesuring time: %f\n", mesureTime);
        insertionSortRunningTime = mesureTime;
        continue;
        case 4:
        printf("You choose option %d\n", choice);
        i = 0;

        free(phoneCallList);
        
        if((phoneCallList = (PhoneCall*) malloc((n + 1) * sizeof(PhoneCall))) == NULL) {
            printf("Cannot allocated memory\n");
            return 1;
        }
        
        while((fscanf(fin2, "%s\t%s\t%d:%d:%d\t%d\n", 
        	phoneCallList[i].caller.content, 
        	phoneCallList[i].called.content, 
        	&phoneCallList[i].beginTime.hour, 
        	&phoneCallList[i].beginTime.minute, 
        	&phoneCallList[i].beginTime.second, 
        	&phoneCallList[i].during)) != EOF) {
        	i++;
        }
        rewind(fin2);
        begin = clock();
        selectionSort(phoneCallList, n);
        end = clock();
        mesureTime = (double) (end - begin) / CLOCKS_PER_SEC;
        printf("Mesuring time: %f\n", mesureTime);
        selectionSortRunningTime = mesureTime;
        continue;
        case 5:
        printf("You choose option %d\n", choice);
        if(!flag) {
            printf("You have not selected the data yet. Please choose option 1 to initialize the database first\n");
            continue;
        }

        printf("How many percents you want to extend the database?\n");
        percents = getInt();
        if(percents < 0 || percents > 100) {
            printf("Invalid percent number (must be in range [0, 100])\n");
            continue;
        }

        newRecord = 100 * n / (100 - percents);

        if((extendPhoneCallList = (PhoneCall*) malloc((newRecord - n + 1) * sizeof(PhoneCall))) == NULL) {
            printf("Cannot allocated memory to extend the database\n");
            continue;
        }

        genPhoneCallData(array, 10000, extendPhoneCallList, newRecord - n);

        // Now save the sorted data first
        for(i = 0; i < n; i++) {
            fprintf(fin2, "%s\t%s\t%d:%d:%d\t%d\n", 
                phoneCallList[i].caller.content, 
                phoneCallList[i].called.content, 
                phoneCallList[i].beginTime.hour, 
                phoneCallList[i].beginTime.minute, 
                phoneCallList[i].beginTime.second, 
                phoneCallList[i].during);
        }

        // Then extend the data
        for(i = 0; i < (newRecord - n); i++) {
            fprintf(fin2, "%s\t%s\t%d:%d:%d\t%d\n", 
                extendPhoneCallList[i].caller.content, 
                extendPhoneCallList[i].called.content, 
                extendPhoneCallList[i].beginTime.hour, 
                extendPhoneCallList[i].beginTime.minute, 
                extendPhoneCallList[i].beginTime.second, 
                extendPhoneCallList[i].during);
        }
        rewind(fin2);
        printf("Generated successfully\n");
        printf("Old size of database: %d\n", n);
        n = newRecord; // new number of records
        printf("The size of database now is %d records\n", n);
        free(extendPhoneCallList);
        continue;
        case 6:
        printf("You choose option %d\n", choice);
        if(saveRunningTime(fout, quickSortRunningTime, insertionSortRunningTime, selectionSortRunningTime, n) != 0) {
        	printf("You must run all of sort types before saving the result.\n");
        	continue;
        }
        printf("Recording test result successfully\n");
	    fclose(fin1);
		fclose(fin2);
		fclose(fout);
        printf("Bye bye\n");
        break;
        default:
        printf("It is not an option\n");
        continue;
      }
      break;
    }
	return 0;
}