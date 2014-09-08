typedef struct np{
  char name[20];
  char pass[20];
}NamePass;
typedef struct us{
  int FD;
  char name[20];
  int mark;
  int lost;
}User;
typedef struct qa{
  char question[1000];
  char ans[5];
  char p[5];
  int toAns;
}QA;

void printQuestion(char s[]);

NamePass* getNamePassFromFile(char *fileName,int *total);

QA* getQAFromFile(char *fileName,int *total);

int compareForRegister(NamePass us,NamePass *dt,int total);

int compareForLogin(NamePass us,NamePass *dt,int total);

int registerToFile(char *fileName,NamePass us);

User* userLogedIn(NamePass us,int FD,User *listUs,int *total);

