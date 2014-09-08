#include "library.h"
void initMemory()
{
    int i,j;
    for (i=0; i<BACKLOG; i++)
    {
        allControl[i] = EMPTINESS;
        role_ans[i] = EMPTINESS;
	}
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
    }
    //clear();
    i++;
    strcpy(result,"");//clear result string
    if (btsel(file_account, object.user,result,50,&rsize)==0)
    {
        result[rsize]='\0';
        printf("Pass in system: %s\nPass user: %s\n",result,object.pass);
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
            role_ans[i] = socketID;
            return;
        }
    }
}


int readQues( char *fileName){
    char line[200],*s1,*s2,*s3,*s4,*s5,*s6,*s7;
    int i=0;
    FILE *f;
    f=fopen(fileName,"r+b");
    if(f==NULL){
        perror("read file");
        return 0;
    }
    else{
        while(fgets(line,200,f)!=NULL){
            s1=strtok(line,":");
            quesArr[i].IDQuestion= atoi(s1);
            s2= strtok(NULL,":");
            strcpy(quesArr[i].ques,s2);
            s3= strtok(NULL,":");
            strcpy(quesArr[i].ans1,s3);
            s4= strtok(NULL,":");
            strcpy(quesArr[i].ans2,s4);
            s5= strtok(NULL,":");
            strcpy(quesArr[i].ans3,s5);
            s6= strtok(NULL,":");
            strcpy(quesArr[i].ans4,s6);
            s7= strtok(NULL,":");
            quesArr[i].ans=atoi(s7);
            i++;
        }
        return 1;
    }
}
