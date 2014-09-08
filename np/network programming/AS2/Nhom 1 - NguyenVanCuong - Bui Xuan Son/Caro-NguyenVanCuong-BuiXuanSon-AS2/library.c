#include "library.h"

/************Quan Ly Giao Tiep Client - Server**************/
void initTable(int table[TABLESIZE][TABLESIZE])
{
    int i = 0, j = 0;
    for(i = 0; i < TABLESIZE; i++)
        for(j = 0; j < TABLESIZE; j++)
            table[i][j] = 0;
}

void initRoom(room *Room)
{
    int i = 0;
    for(i < 0; i < ROOMSIZE; i++)
    {
        Room[i].PlayerA.sockfd = -1 ;
        Room[i].PlayerB.sockfd = -1;
        Room[i].state = 0;
        initTable(Room[i].table);
    }
}
int checkIn(int *a, int fd)
{
    int i = 0;
    for( i = 0; i < FD_SETSIZE; i++)
    {
        if(a[i] == fd) return 1;
    }
    return 0;
}
room* getRoom(player Player[], int sockfd, room Room[])
{
    int i = 0;
    for(i = 0; i < FD_SETSIZE; i++)
    {
        if(Player[i].sockfd == sockfd)
        {
            return &Room[Player[i].roomID];
        }
    }
    return NULL;
}
void copyPlayer(player *A, player *B)
{
    A->mark = B->mark;
    A->roomID = B->roomID;
    A->sockfd = B->sockfd;
    A->wait = B->wait;
}
void copyTable( int A[TABLESIZE][TABLESIZE], int B[TABLESIZE][TABLESIZE])
{
    int i, j;
    for( i = 0; i < TABLESIZE; i++)
        for(j = 0; j < TABLESIZE; j++)
            A[i][j] = B[i][j];
}
void copyRoom( room *a, room *b)
{
    copyPlayer(&(a->PlayerA), &(b->PlayerA));
    copyPlayer(&(a->PlayerB), &(b->PlayerB));
    a->state = b->state;
    copyTable(a->table, b->table);
}
void getListRoomFree(room *Room, int *FullRoom, int *WaitingRoom, int *EmptyRoom)
{
    int i;
    int k,l,m;
    k = l = m = 0;
    for(i = 0; i < ROOMSIZE; i++)
    {
        FullRoom[i] = 0;
        WaitingRoom[i] = 0;
        EmptyRoom[i] = 0;
    }
    for(i = 0; i < ROOMSIZE; i++)
    {
        switch(Room[i].state)
        {
        case 0:
            EmptyRoom[k++] = i;
            break;
        case 1:
            WaitingRoom[l++] = i;
            break;
        case 2:
            FullRoom[m++] = i;
            break;
        }
    }
}
char * makeMessage(int *Room)
{
    int i = 0;
    char* buf = (char*)malloc(MAXLINE*sizeof(char));
    char subBuf[10];
    strcpy(buf,"_");
    for( i = 0; i < ROOMSIZE; i++)
    {
        if(Room[i] != 0)
        {
            sprintf(subBuf, "%d_", Room[i]);
            strcat(buf, subBuf);
        }

    }
    return buf;
}
/**************Quan Ly Nguoi Dung**************/
int readFile(user listUser[])
{
    FILE * f;
    char buf[MAXLINE];
    char * token;
    int i=0;
    if((f = fopen("users.txt", "r")) == NULL)
        printf("Open file error!");
    while(fgets(buf, 100, f)!=NULL)
    {
        buf[strlen(buf)-1] = '\0';
        token = strtok (buf," ");
        strcpy(listUser[i].username, token);
        token = strtok (NULL," ");
        strcpy(listUser[i].password, token);
        i++;
    }
    fclose(f);
    return i;
}
int compareUser(user u1, user u2)
{
    if((strcmp(u1.username, u2.username) == 0) && (strcmp(u1.password, u2.password) == 0))
        return 1;
    return 0;
}
int checkExistUsername2(char *username, user *listUser, int nUser)
{
    int i = 0;
    for(i = 0; i < nUser; i++)
        if(strcmp(username, listUser[i].username) == 0) return 1;
    return 0;
}

int checkExistUsername(char *username, char ListUsername[FD_SETSIZE][MAXLINE] )
{
    int i = 0;
    for( i = 0 ; i < FD_SETSIZE; i++)
        if(strcmp(username, ListUsername[i]) == 0)
            return 1;
    return 0;
}
int checkLogin(user *listUser,int n,  user u, char ListUsername[FD_SETSIZE][MAXLINE])
{
    int i;
    for(i = 0; i<n; i++)
    {
        if(compareUser(listUser[i], u))
        {
            if (checkExistUsername(u.username, ListUsername)) return 0;
            return 1;
        }
    }
    return 0;
}

void registerUser (char username[], char  password[], char * filename)
{
    FILE * f;
    char buf[20];
    if((f = fopen(filename, "a+")) == NULL)
    {
        printf("Error!");
        exit(1);
    }
    fprintf(f, "%s %s\n", username, password);
    fclose(f);
}
int checkExistPlayer(player Player[], int sockfd)
{

    int i = 0;
    for( i = 0; i < FD_SETSIZE; i++)
    {
        if(Player[i].sockfd == sockfd)
        {
            return i;
        }
    }
    return -1;
}

/************Quan Ly Khi Choi**************/
void signInTable(int table[TABLESIZE][TABLESIZE], char *message, int flag)
{
    int i, j;
    sscanf(message,"%d%d", &i, &j);
    if(flag == 1)
    {
        table[i][j] = 1;
    }
    else if(flag == 2)
    {
        table[i][j] = 2;
    }
}
/**
* Return 1 : thang
* Return 2 : hoa
*/
int checkWiner( int table[TABLESIZE][TABLESIZE], int xCross, int yCross, int flag)
{
    int x, y;
    int count = 1;
    int i, j;
    int UnFlag;
    int checked = 0;

    // check equals
    for(i = 0; i < TABLESIZE; i++)
        for(j = 0; j < TABLESIZE; j++)
            if(table[i][j] != 0) checked++;
    if(checked == (TABLESIZE*TABLESIZE)) return 2;


    x = xCross;
    y = yCross;
    i = xCross;
    j = yCross;
    if( flag == 1 ) UnFlag =  2;
    else UnFlag = 1;
    // kiem tra theo hang ngang
    while( table[i][--j] == flag) count++;
    while( table[i][++y] == flag) count++;
    if( count == WINSIZE )
    {
        if( j < 0 || y > TABLESIZE ) return 1;
        else if( table[i][j] == UnFlag && table[i][y] == UnFlag) return 0;
        else return 1;
    }
    // Kiem tra theo hang doc
    x = xCross;
    y = yCross;
    i = xCross;
    j = yCross;
    count = 1;
    while( table[--i][j] == flag) count++;
    while( table[++x][j] == flag) count++;
    if( count == WINSIZE )
    {
        if( i < 0 || x > TABLESIZE ) return 1;
        else if( table[i][j] == UnFlag && table[x][j] == UnFlag) return 0;
        else return 1;
    }
    // Kiem tra theo hang cheo1
    x = xCross;
    y = yCross;
    i = xCross;
    j = yCross;
    count = 1;
    while( table[--i][++j] == flag) count++;
    while( table[++x][--y] == flag) count++;
    if( count == WINSIZE )
    {
        if( i < 1 || j > TABLESIZE || x > TABLESIZE || y < 1) return 1;
        else if( table[i][j] == UnFlag && table[x][y] == UnFlag) return 0;
        else return 1;
    }
    // Kiem tra theo hang cheo2
    x = xCross;
    y = yCross;
    i = xCross;
    j = yCross;
    count = 1;
    while( table[--i][--j] == flag) count++;
    while( table[++x][++y] == flag) count++;
    if( count == WINSIZE )
    {
        if( i < 1|| j < 1 || x > TABLESIZE || y > TABLESIZE ) return 1;
        else if( table[i][j] == UnFlag && table[x][y] == UnFlag) return 0;
        else return 1;
    }
    return 0;
}
int checkPlay(int table[TABLESIZE][TABLESIZE], char * message)
{
    if(strcmp(message, "q")==0 ||  strcmp(message, "Q")==0)
        return 2;
    int x, y, k;
    char z;
    k = sscanf(message, "%d %d %c", &x, &y, &z);
    if(k != 2) return 1;
    else
    {
        if(x<1 || x>14 || y<1 || y>14) return 1;
        else
        {
            if((table[x][y] == 1) || (table[x][y] == 2))
                return 1;
            else if(table[x][y] == 0) //Neu chua danh
                return 0;
        }
    }
}


void CreatFileLog( char *infoLog, char *filename)
{
    FILE *f;
    f = fopen(filename, "a+");
    fprintf( f,"%s\n", infoLog);
    fclose(f);
}

void delFile(char filename[])
{
    FILE *f;
    char buf[MAXLINE];
    sprintf(buf,"rm -rf %s", filename);
    system(buf);   // xoa file log khoi server.

}

/************Quan Ly Giao Dien************/
void drawTable(int table[TABLESIZE][TABLESIZE], int xCross, int yCross)
{
    int i, j;
    printf("  ");
    for(i = 0; i < TABLESIZE; i++)
    {
        printf("%3d",i);
    }
    printf("\n");
    for(i = 0; i < TABLESIZE; i++)
    {
        printf("%-3d",i);
        for(j = 0; j < TABLESIZE; j++)
        {
            if(table[i][j] == 0)
            {
                if( i == xCross && j == yCross)
                    printf(MAKE_GREEN "[ ]" RESET_COLOR);
                else printf("[ ]");
            }
            else if(table[i][j] == 1)
            {
                if( i == xCross && j == yCross)
                    printf(MAKE_GREEN "[x]" RESET_COLOR);
                else printf("[x]");
            }
            else
            {
                if( i == xCross && j == yCross)
                    printf(MAKE_GREEN "[o]" RESET_COLOR);
                else printf("[o]");
            }
        }
        printf("\n");
    }

}

int drawTable2(int table[TABLESIZE][TABLESIZE], int * x, int * y, int flag)
{
    char key;
    char buf[MAXLINE];
    int xCross = *x;
    int yCross = *y;
    drawTable(table, xCross, yCross);
    do
    {
        printf("Den Luot Ban (w:up, s:down, a:left, d:right): ");
        key = getch();
        switch(key)
        {
        case 'w'://up
            if(xCross > 0) xCross--;
            clear();
            drawTable(table, xCross, yCross);
            break;
        case 's'://down
            if(xCross < TABLESIZE-1) xCross++;
            clear();
            drawTable(table, xCross, yCross);
            break;
        case 'a'://left
            if(yCross > 0) yCross--;
            clear();
            drawTable(table, xCross, yCross);
            break;
        case 'd'://right
            if(yCross < TABLESIZE -1) yCross++;
            clear();
            drawTable(table, xCross, yCross);
            break;
        default:
            break;
        }
        if(key == '\n'){
            if(table[xCross][yCross] == 0) break;
        }
    }
    while(key != 'q' && key != 'Q');
    if(key == '\n')
    {
        (*x) = xCross;
        (*y) = yCross;
        sprintf(buf,"%d %d", xCross, yCross);
        signInTable(table, buf, flag);
        clear();
        drawTable(table, xCross, yCross);
        return 0;
    }
    else if(key == 'q' || key == 'Q') return 1;;

}
void clear()
{
    system("clear");
}
int getch()
{
    struct termios oldt,
            newt;
    int            ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}


/********************/
void printStateRoom(room *Room)
{
    int i = 0;
    for( i = 0; i < ROOMSIZE; i++)
    {
        if(Room[i].state == 2)
        {
            //drawTable(Room[i].table);
            printf("Room[%d] state : %d sockA : %d sockB : %d\n",i, Room[i].state,Room[i].PlayerA.sockfd,Room[i].PlayerB.sockfd);
            printf("Player A in Room[%d] sock %d roomID %d wait %d\n",i, Room[i].PlayerA.sockfd, Room[i].PlayerA.roomID,Room[i].PlayerA.wait);
            printf("Player B in Room[%d] sock %d roomID %d wait %d\n",i, Room[i].PlayerB.sockfd, Room[i].PlayerB.roomID,Room[i].PlayerB.wait);
        }
    }
}
