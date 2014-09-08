#include "library.h"

void initFileLog(int socketIndex, data buf, char *address_client)
{
    char filename[100];
    filename[0] = '\0';
    strcat(filename,buf.object.user);
    strcat(filename,"_");
    //lay time he thong
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strcat(filename,asctime(timeinfo));
    strcat(filename,".txt");
    memcpy(fileName[socketIndex],filename, strlen(filename));
    logArray[socketIndex] = fopen(filename,"w");
    printf("--------- dia chi con tro file khoi tao %p\n",logArray[socketIndex]);
    if (logArray[socketIndex]==NULL)
        printf("Loi khoi tao file log");
    else
    {
		fprintf(logArray[socketIndex],"IP address of client : %s\n",address_client);
        fprintMap(all[socketIndex], logArray[socketIndex]);
        fclose(logArray[socketIndex]);
	}
}

void initMemory()
{
    int i,j;
    for (i=0; i<BACKLOG; i++)
    {
        allControl[i] = EMPTINESS;
        logArray[i] = NULL;
	}

    for (i=0; i<BACKLOG; i++)
    {
        fileName[i][0] = '\0';
        all[i][0] = 10;
        for (j=1; j<6; j++)
        {
            all[i][j] = 5;
            all[i][j+6] = 5;
        }
        all[i][6] = 10;
        all[i][12] = 0;
        all[i][13] = 0;
    }
}

void printMap(int *info)
{
    //in score server
    printf("Score of Boss : %d\n",info[12]);

    //in so do tro choi
    printf(" _________________________________________\n");
    printf("|     |     |     |     |     |     |     |\n");
    printf("|     | %2d  | %2d  | %2d  | %2d  | %2d  |     |\n",info[1],info[2],info[3],info[4],info[5]);
    printf("|     |_____|_____|_____|_____|_____|     |\n");
    printf("|     |                             |     |\n");
    printf("| %2d  |                             | %2d  |\n",info[0],info[6]);
    printf("|     |_____ _____ _____ _____ _____|     |\n");
    printf("|     |     |     |     |     |     |     |\n");
    printf("|     | %2d  | %2d  | %2d  | %2d  | %2d  |     |\n",info[11],info[10],info[9],info[8],info[7]);
    printf("|_____|_____|_____|_____|_____|_____|_____|\n");
    printf("         a     b     c     d     e\n");
    //in score client
    printf("\nScore of You : %d\n",info[13]);
}

void fprintMap(int *info, FILE *fp)
{
    printf("*************************** ghi log %p\n",fp);
    //in score server
    fprintf(fp,"Score of Boss : %d\n",info[12]);

    //in so do tro choi
    fprintf(fp,"         1     2     3     4    5\n");
    fprintf(fp," _________________________________________\n");
    fprintf(fp,"|     |     |     |     |     |     |     |\n");
    fprintf(fp,"|     | %2d  | %2d  | %2d  | %2d  | %2d  |     |\n",info[1],info[2],info[3],info[4],info[5]);
    fprintf(fp,"|     |_____|_____|_____|_____|_____|     |\n");
    fprintf(fp,"|     |                             |     |\n");
    fprintf(fp,"| %2d  |                             | %2d  |\n",info[0],info[6]);
    fprintf(fp,"|     |_____ _____ _____ _____ _____|     |\n");
    fprintf(fp,"|     |     |     |     |     |     |     |\n");
    fprintf(fp,"|     | %2d  | %2d  | %2d  | %2d  | %2d  |     |\n",info[11],info[10],info[9],info[8],info[7]);
    fprintf(fp,"|_____|_____|_____|_____|_____|_____|_____|\n");
    fprintf(fp,"        11    10     9     8     7\n");
    //in score client
    fprintf(fp,"\nScore of You : %d\n",info[13]);
}

step choice(int *info)
{
    step tmp;
    //khoi tao step.position = 0
    tmp.position = 0;
    char c;
    int sign = 0;
    do
    {
        printf("Choice position (quit = q):");
        scanf("%c%*c",&c);
        if (info['e'-c+7]==0)
        {
            printf("You have choosen empty cell, please again\n");
            sign = 1;
        }
        if (c=='q' || c=='Q')
            return tmp;
        else
            sign = 0;
    }
    while (sign);
    tmp.position = 'e'-c+7;
    printf("You go left (L) or right (R) : ");
    scanf("%c%*c",&c);
    tmp.way = c;
    return tmp;
}

int play(int *info,step tmp)
{
    int number,position,i;
    position = tmp.position;
    number = info[position];
    step subStep;

    //di theo huong ben trai
    if (tmp.way == 'l')
    {
        info[position] = 0;
        for (i=number; i>0; i--)
        {
            position = (position+1)%12;
            info[position]++;
        }
        //kiem tra xem phia truoc co o rong ko
        position = (position+1)%12;
        if (info[position]==0)
        {
            // co trong
            number = info[(position+1)%12];
            info[(position+1)%12] = 0;
            subStep.position = (position+1)%12;
            subStep.way = 'l';
            // tra ve gia tri cua o tiep theo
            return number + checkContinue(info,subStep) ;
        }
        else
        {
            subStep.position = position;
            subStep.way = 'l';
            return play(info, subStep);
        }
    }
    else
    {
        info[position] = 0;
        for (i=number; i>0; i--)
        {
            position = (position-1)%12;
            if (position<0)
                position += 12;
            info[position]++;
        }
        //kiem tra xem phia truoc co o rong ko
        position = (position-1)%12;
        if (position<0)
            position += 12;
        if (info[position]==0)
        {
            position = (position-1)%12;
            if (position<0)
                position += 12;
            number = info[position];
            info[position] = 0;
            subStep.position = position;
            subStep.way = 'r';
            // tra ve gia tri cua o tiep theo
            return number + checkContinue(info,subStep) ;
        }
        else
        {
            step subStep2;
            subStep2.position = position;
            subStep2.way = 'r';
            return play(info, subStep2);
        }
    }
}

int checkContinue(int *info, step tmp)
{
    step subStep;
    int number,position;

    if (tmp.way == 'l')
    {
        if (info[(tmp.position+1)%12]==0)
        {
            subStep.position = (tmp.position+2)%12;
            subStep.way = 'l';
            number = info[(tmp.position+2)%12];
            info[(tmp.position+2)%12] = 0;
            //thoat neu o tiep theo cua tiep theo van la 0
            if (number == 0)
                return 0;
            return number + checkContinue(info, subStep);
        }
        else
            return 0;
    }
    else
    {
        position = (tmp.position-1)%12;
        if (position<0)
            position += 12;

        if (info[position]==0)
        {
            position = (position-1)%12;
            if (position<0)
                position += 12;

            subStep.position = position;
            subStep.way = 'r';
            number = info[position];
            info[position] = 0;
            //thoat neu o tiep theo cua tiep theo van la 0
            if (number == 0)
                return 0;
            return number + checkContinue(info, subStep);
        }
        else
            return 0;
    }
}

step calculator(int *info)
{
    step final,tmp;
    int score = 0,score2,i;
    final.position = 0;
    for (i=1; i<=5; i++)
    {
        if (info[i]>0)
        {
            tmp.position = i;
            //xet huong trai
            tmp.way = 'l';
            if (score < (score2=predict(info, tmp)))
            {
                final.position = tmp.position;
                final.way = tmp.way;
                score = score2;
            }
            //xet huong phai
            tmp.way = 'r';
            if (score < (score2=predict(info, tmp)))
            {
                final.position = tmp.position;
                final.way = tmp.way;
                score = score2;
            }
        }
    }
    printf("\n-----------------------\n calculate position %d way %c \n",final.position, final.way);
    return final;
    // can kiem soat truong hop ko con quan nao di khi position=0
}

int predict(int *info,step tmp)
{
    int tmp1[13];
    memcpy(tmp1,info,14*sizeof(int));
    return play(tmp1, tmp);
}

void logGame(int socketIndex, step tmp)
{
    int *info;
    info = all[socketIndex];

    FILE *fp;
    fp = fopen(fileName[socketIndex],"a");
    if( fp == NULL)
	{
		printf("loi mo file ghi log");
		return ;
	}
    fprintf(fp,"\n-------------------------------------------------------\n");
    if (tmp.position>0 && tmp.position<6)
    {
        fprintf(fp,"Boss play: position %d ",tmp.position);
        if (tmp.way == 'l')
            fprintf(fp,", way Left\n");
        else
            fprintf(fp,", way Right\n");
    }
    else
    {
        fprintf(fp,"You play: position %d ",tmp.position);
        if (tmp.way == 'l')
            fprintf(fp,", way Left\n");
        else
            fprintf(fp,", way Right\n");
    }
    fprintMap(info, fp);
    fclose(fp);
}

int checkExit(int socketIndex)
{
    int *info;
    info = all[socketIndex];

    FILE *fp;
    fp = fopen(fileName[socketIndex],"a");
    if( fp == NULL)
	{
		printf("loi mo file de check exit");
		return 0;
	}
    int sum1 = info[1]+info[2]+info[3]+info[4]+info[5];
	int sum2 = info[7]+info[8]+info[9]+info[10]+info[11];
	
    if (info[0] == 0 && info[6] == 0)
    {
        printf("game exit\n");
        fprintf(fp,"--------------Game exit-----------\n");
        quitGame(info, fp);
        fclose(fp);
        return 1;
    }
    if(sum1 == 0 || sum2 == 0)
    {
        printf("game exit\n");
        fprintf(fp,"--------------Game exit-----------\n");
        quitGame(info, fp);
        fclose(fp);
        return 1;
    }
    return 0;
}

void quitGame(int *info, FILE *fp)
{
    int i;
    //tinh diem cho boss
    for (i=1; i<6; i++)
    {
        info[12] += info[i];
        info[i] = 0;
    }
    //tinh diem cho client
    for (i=7; i<12; i++)
    {
        info[13] += info[i];
        info[i] = 0;
    }
    fprintf(fp,"Score of Boss %d\n",info[12]);
    fprintf(fp,"Score of You %d\n",info[13]);
    //fclose(fp);
    //fp = NULL;
}


int searchAccount(account object)
{
    char result[50];
    int rsize,i=0;
    BTA *file_account;
    btinit();     //khoi tao che do lam viec voi Btree
    file_account= btopn("ManageAccount",0,0);       //mo file du lieu dc ghi duoi dang Btree
    if (!file_account)
    {
        printf("Creat file ManageAccount\n");
        file_account= btcrt("ManageAccount",0,0);
        //khoi tao file Btree
        //return NOT_FOUND;
    }
    //clear();
    i++;
    strcpy(result,"");//clear result string
    if (btsel(file_account, object.user,result,50,&rsize)==0)
    {
        printf("rsize == %d\n\n",rsize);
        //printf("mmm == %d\n\n",i);
        result[rsize]='\0';
        //strcat(result,"\0");
        printf("Pass in system: %s\nPass user: %s\n",result,object.pass);
        printf("im in search\n\n");
        //btcls(file_account);
        if (strcmp(result, object.pass)==0)
        {
            btcls(file_account);
            return FOUND;
        }
        else
        {
            btcls(file_account);
            return WRONG_PASS;
        }
    }
    else
    {
        btcls(file_account);
        return NOT_FOUND;
    }
}

//add new account
void addAccount(account object)
{
    BTA *file_account;
    btinit();     //khoi tao che do lam viec voi Btree
    file_account= btopn("ManageAccount",0,0);       //mo file du lieu dc ghi duoi dang Btree
    if (!file_account)
    {
        printf("Creat file ManageAccount\n");
        file_account= btcrt("ManageAccount",0,0);   //khoi tao file Btree
    }
    printf("object.pass==%s\n\n",object.pass);
    btins(file_account, object.user, object.pass, strlen(object.pass));
    btcls(file_account);
}



int searchSocket(int socketID)
{
    int i;
    for (i=0;i<BACKLOG;i++)
    {
        if (allControl[i]==socketID)
            return i;
    }
    return NOT_FOUND;
}

void clearSocketData(int socketID)
{
    int i,j;
    for (i=0;i<BACKLOG;i++)
    {
        if (allControl[i]==socketID)
        {
            allControl[i]=EMPTINESS;
            {
                fileName[i][0] = '\0';
                all[i][0] = 10;
                for (j=1; j<6; j++)
                {
                    all[i][j] = 5;
                    all[i][j+6] = 5;
                }
                all[i][6] = 10;
                all[i][12] = 0;
                all[i][13] = 0;
            }
            return;
        }
    }
    return;
}

int isLimited(void)
{
    int i;
    for (i=0;i<BACKLOG;i++)
    {
        if (allControl[i]==EMPTINESS)
            return NO;
    }
    return YES;
}

void creatSocketData(int socketID)
{
    int i,j;
    for (i=0;i<BACKLOG;i++)
    {
        if (allControl[i]==EMPTINESS)
        {
            allControl[i]= socketID;
            return;
        }
    }
    //for(j=0;j<12;j++){
    //all[i][j]=5;
    //}
}


