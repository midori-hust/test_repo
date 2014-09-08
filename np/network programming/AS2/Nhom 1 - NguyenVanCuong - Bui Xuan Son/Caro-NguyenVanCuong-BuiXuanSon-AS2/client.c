#include "library.h"

int number = 0;
room Room[ROOMSIZE];
int table[TABLESIZE][TABLESIZE]; // luu tru trang thai ban co
int numPlayer = 0;
int isLogIn = 1;  // Default = 0;
int isGetRoom = 0;
int isPlaying = 0;
int isQuit = 0;
int isWin = 0;
int numberLogin = 0;
int flag = 1;
int unflag = 2;
int number_of_play = 0;
int start = 0;
int stop = 0;

int main(int args , char *argv[])
{

    int fd;

    struct sockaddr_in server;
    struct hostent *he;

    int numBytes;
    char recvMessage[MAXLINE];
    char sendMessage[MAXLINE];
    char EmptyRoom[MAXLINE];
    char WaitingRoom[MAXLINE];
    char filename[MAXLINE];
    char room[2];

    int xCross, yCross;
    char temp[MAXLINE];
    int check = 0;
    // username and password
    char username[MAXLINE];
    char password[MAXLINE];
    char *buffer;
    char buf[MAXLINE];
    FILE *f;
    int n;

    // bien lua chon
    int choose, subChoose;

    //init table
    initTable(table);


    if(args < 3)
    {
        printf("Usage : %s <IP> <PORT>\n", argv[0]);
        exit(-1);
    }
    // get info from host

    if((he = gethostbyname(argv[1])) == NULL)
    {
        printf("gethostbyname() error!\n");
        exit(-1);
    }

    // init info for server
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr = *((struct in_addr*)he->h_addr);
    bzero(&(server.sin_zero),8);
    do
    {
        printf("1.Dang nhap\n");
        printf("2.Dang ki\n");
        printf("3.Thoat\n");
        printf("Lua chon : ");
        scanf("%d", &choose);
        while(getchar()!='\n');
        switch(choose)
        {
        case 1:
            if((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
            {
                printf("socket() error!");
                exit(-1);
            }
            if( connect(fd,(struct sockaddr*)&server , sizeof(server)) == -1 )
            {
                printf("connect() error\n");
                exit(1);
            }
            // receive welcome message from server
            numBytes = recv(fd, recvMessage, MAXLINE, 0);
            recvMessage[numBytes] = '\0';
            printf("%s\n", recvMessage);
            do
            {
                // authenticate
                printf("*************Dang Nhap*************\n");
                send(fd, SIGNAL_LOGIN, strlen(SIGNAL_LOGIN), 0);
                printf("Nhap vao username : ");
                gets(username);
                printf("Nhap vao password : ");
                gets(password);
                //send username and password to server
                send(fd, username, strlen(username), 0);
                send(fd, password, strlen(password), 0);
                numBytes = recv(fd, recvMessage, MAXLINE, 0);
                recvMessage[numBytes] = '\0';
                printf(">>>>>%s\n",recvMessage);
                if(strcmp(recvMessage, SIGNAL_LOGIN_OK) == 0)
                {
                    printf("Dang nhap thanh cong\n");
                    isLogIn = 1;
                    clear();
                    break;
                }
                else printf("Dang nhap that bai. Thu lai !\n");
                numberLogin++;
                if(numberLogin == 3)
                {
                    break;
                }
            }
            while(1);

            if(numberLogin >= 3)
            {
                clear();
                close(fd);
                numberLogin = 0;
                break;
            }
            else
            {
                numberLogin = 0;
            }
            // start game....
            // Lua chon
            do
            {
                if(isGetRoom == 0)
                    printf("1.Chon phong choi\n");
                printf("2.Bat dau choi\n");
                printf("3.Ket thuc\n");
                printf("Lua chon : ");
                scanf("%d", &subChoose);
                while(getchar()!='\n');
                switch(subChoose)
                {
                case 1: // lua chon phong choi
                    if(isLogIn == 0)
                    {
                        printf("Thong bao : Phai Dang Nhap!\n");
                        break;
                    }
                    if(isGetRoom != 0){
                        printf("Thong bao : Da chon phong choi!\nHay chon 2 de bat dau\n");
                        break;
                    }
                    send(fd, SIGNAL_GET_LIST_ROOM, strlen(SIGNAL_GET_LIST_ROOM), 0);
                    numBytes = recv(fd, recvMessage, MAXLINE, 0);
                    recvMessage[numBytes]='\0';
                    printf("Phong dang cho : %s\n", recvMessage);
                    strcpy(WaitingRoom, recvMessage);
                    numBytes = recv(fd, recvMessage, MAXLINE, 0);
                    recvMessage[numBytes]='\0';
                    printf("Phong dang trong : %s\n", recvMessage);
                    strcpy(EmptyRoom, recvMessage);
                    do
                    {
                        printf("Chon Phong : ");
                        gets(room);
                    }
                    while((strstr(EmptyRoom,room ) == NULL) && (strstr(WaitingRoom, room) == NULL));

                    send(fd, room, strlen(room), 0);
                    //nhan tin hieu cho tu server
                    numBytes = recv(fd, recvMessage, MAXLINE, 0);
                    recvMessage[numBytes] = '\0';
                    printf("%s\n", recvMessage);
                    isGetRoom = 1;
                    if(strcmp(recvMessage, SIGNAL_START) != 0)
                    {
                        numBytes = recv(fd, recvMessage, MAXLINE, 0);
                        recvMessage[numBytes] = '\0';
                        printf("%s\n", recvMessage);
                    }
                    clear();
                case 2: // bat dau choi ... trang thai san sang
                    if(isGetRoom == 0)
                    {
                        printf("Thong bao : Hay chon phong truoc!\n");
                        break;
                    }
                    send(fd, SIGNAL_READY_PLAY, strlen(SIGNAL_READY_PLAY), 0);
                    isPlaying = 1;
                    flag = 1;
                    unflag = 2;
                    drawTable(table, -1, -1);
                    do
                    {
                        numBytes = recv(fd, recvMessage, MAXLINE, 0);
                        recvMessage[numBytes] = '\0';
                        if(strcmp(recvMessage, SIGNAL_WIN) == 0)
                        {
                            isWin = 1;
                            initTable(table);
                            send(fd, SIGNAL_GET_LOG_FILE, strlen(SIGNAL_GET_LOG_FILE), 0);
                            sprintf(filename,"%s_%d.txt", username,number_of_play++);
                            n = recv(fd, buf, MAXLINE, 0);
                            buf[n] = '\0';
                            buffer = (char*) malloc (sizeof(char)*atoi(buf));
                            n = recv(fd, buffer, atoi(buf), 0);
                            buffer[n] = '\0';
                            f = fopen( filename, "w+");
                            fprintf(f, "%s", buffer);

                            fclose(f);
                            if(buffer!=NULL)
                                free(buffer);
                            send(fd, SIGNAL_OK, strlen(SIGNAL_OK), 0);

                            break;
                        }
                        else if(strstr(recvMessage, SIGNAL_LOOSE) !=NULL)
                        {

                            isWin = 0;
                            printf("Message loose : %s\n", recvMessage);
                            sscanf(recvMessage, "%d %d %s", &xCross, &yCross, temp);
                            sprintf(temp, "%d %d", xCross, yCross);
                            printf(">>>>>>%s_%d_%d\n", recvMessage, xCross, yCross);
                            signInTable(table, temp,unflag);
                            clear();
                            drawTable(table, xCross, yCross);
                            send(fd, SIGNAL_LOOSE, strlen(SIGNAL_LOOSE), 0);  //??
                            initTable(table);
                            recv(fd, recvMessage, MAXLINE, 0);
                            send(fd, SIGNAL_GET_LOG_FILE, strlen(SIGNAL_GET_LOG_FILE), 0 );
                            sprintf(filename,"%s_%d.txt", username,number_of_play++);
                            n = recv(fd, buf, MAXLINE, 0);
                            buf[n] = '\0';
                            buffer = (char*) malloc (sizeof(char)*atoi(buf));
                            n = recv(fd, buffer, atoi(buf), 0);
                            buffer[n] = '\0';
                            f = fopen( filename, "w+");
                            fprintf(f, "%s", buffer);
                            if(buffer!=NULL)
                            {
                                free(buffer);
                                buffer = NULL;
                            }
                            fclose(f);
                            send(fd, SIGNAL_OK, strlen(SIGNAL_OK), 0);
                            break;
                        }

                        /*****************PLAY******************/

                        if(strcmp(recvMessage, SIGNAL_START) == 0)
                        {
                            printf("Other Client : %s\n", recvMessage);
                            flag = 2;
                            unflag = 1;
                            initTable(table);
                            xCross = 4;
                            yCross = 4;
                            start = 0;
                        }
                        else
                        {
                            printf("Doi Phuong Danh : %s\n", recvMessage);
                            signInTable(table, recvMessage, unflag);
                            clear();
                            sscanf(recvMessage,"%d %d", &xCross, &yCross);
                            drawTable(table, xCross, yCross);
                            start = 1;
                        }
                        clear();
                        stop = drawTable2(table, &xCross, &yCross, flag);
                        if(stop){
                            //send tin nhan bao out khoi tro choi khi dang choi...
                            send(fd, SIGNAL_OUT_ROOM, strlen(SIGNAL_OUT_ROOM), 0);
                            initTable(table);
                            recv(fd, recvMessage, MAXLINE, 0);
                            send(fd, SIGNAL_GET_LOG_FILE, strlen(SIGNAL_GET_LOG_FILE), 0);
                            sprintf(filename,"%s_%d.txt", username,number_of_play++);
                            n = recv(fd, buf, MAXLINE, 0);
                            buf[n] = '\0';
                            buffer = (char*) malloc (sizeof(char)*atoi(buf));
                            n = recv(fd, buffer, atoi(buf), 0);
                            buffer[n] = '\0';
                            f = fopen( filename, "w+");
                            fprintf(f, "%s", buffer);
                            if(buffer != NULL)
                            {
                                free(buffer);
                                buffer = NULL;
                            }

                            fclose(f);
                            send(fd, SIGNAL_OK, strlen(SIGNAL_OK), 0);
                            isWin = 0;
                            break;
                        }else{
                            sprintf(sendMessage,"%d %d", xCross, yCross);
                            send(fd, sendMessage,strlen(sendMessage), 0);

                        }
                        /*********************END PLAY*********************/
                    }
                    while(1);
                    if(isWin == 0)
                    {
                        printf(MAKE_GREEN "\n%s :( :( :(\n" RESET_COLOR, SIGNAL_LOOSE);
                    }
                    else
                    {
                        printf(MAKE_GREEN "\n%s :) :) :)\n" RESET_COLOR, SIGNAL_WIN);
                    }
                    isGetRoom = 0;
                    isPlaying = 0;
                    break;
                case 3: // ket thuc
                    send(fd, SIGNAL_QUIT, strlen(SIGNAL_QUIT), 0);
                    isLogIn = 0;
                    close(fd);
                    clear();
                    break;
                default:
                    break;
                }
            }
            while(subChoose!=3);
            break;
        case 2:
            if((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
            {
                printf("socket() error!");
                exit(-1);
            }
            if( connect(fd,(struct sockaddr*)&server , sizeof(server)) == -1 )
            {
                printf("connect() error\n");
                exit(1);
            }
            // receive welcome message from server
            numBytes = recv(fd, recvMessage, MAXLINE, 0);
            recvMessage[numBytes] = '\0';
            printf("%s\n", recvMessage);

            printf("*************Dang Ky*************\n");
            send(fd, SIGNAL_REGISTER, strlen(SIGNAL_REGISTER), 0);
            printf("Nhap vao username : ");
            gets(username);
            printf("Nhap vao password : ");
            gets(password);
            //send username and password to server
            send(fd, username, strlen(username), 0);
            send(fd, password, strlen(password), 0);
            numBytes = recv(fd, recvMessage, MAXLINE, 0);
            recvMessage[numBytes] = '\0';
            if(strstr(recvMessage, "fail") != NULL)
            {
              printf("Da ton tai username ! \n dang ki that bai\nAn phim bat ki de tiep tuc\n");
              getchar();
            }
            close(fd);
            clear();
            break;
        case 3:
            printf("Bye_Bye^^\n");
            break;
        }
    }
    while(choose!=3);
}


