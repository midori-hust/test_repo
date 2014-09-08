#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "mlibrary.h"
#include <errno.h>

int main(int agrs, char *argv[] ){
	int readResult=readQuestionFile("question.txt");
	if(readResult){
		printf("Got the question library already!\nNumbers question : %d\n",readResult);
		int i,j;
		for(i=0;i<15;i++){
			for(j=0;j<NUMBERS_PER_QUES;j++){
				printf("%s\n",questLib[i][j].ques);
			}
		}
	}
}
