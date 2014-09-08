#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "rooms.h"
#include "gameserver_core.h"

FILE *fp;
char *userlist_filepath = "userlist.txt";

userlist_t user_list;
roomlist_t room_list;


void gameserver_core_init ()
{
    user_list = userlist_new ();

    fp = fopen(userlist_filepath, "rw");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    room_list = roomlist_new ();
}

int gameserver_core_loadUsers ()
{
    char *line_buffer = NULL;
    size_t len = 0;
    ssize_t read;

    char **line;
    line = (char **) malloc (sizeof(char *) * 1024);

    int count_line = 0;
    while ((read = getline(&line_buffer, &len, fp)) != -1) {
        line[count_line] = (char *) malloc (read);
        strcpy(line[count_line], line_buffer);
        count_line++;
    }
    free(line_buffer);

    for (int i = 0; i < count_line; i++) {
        int id;
        char *username;
        char *password;

        char *pch;
        pch = strtok (line[i], ",");
        id = atoi (pch);
        username = strtok (NULL, ",");
        password = strtok (NULL, ",");
        password[strlen(password) - 1] = '\0';
        user_t newUser = user_new (id, username, password, OFFLINE, -1);

        userlist_append (user_list, newUser);
    }

    for (int i = 0; i < count_line; i++) {
        free(line[i]);
    }
    free(line);

    return count_line;
}

int gameserver_core_signin (char *username, char *password, int sockfd)
{
    userlist_t ptr;
    userlist_traverse (ptr, user_list) {
        if ((strcmp(ptr->user->username, username) == 0)
                &&
                (strcmp(ptr->user->password, password) == 0)) {
            ptr->user->status = ONLINE;
            ptr->user->sockfd = sockfd;
            return ptr->user->id;
        }
    }
    return -1;
}

int gameserver_core_signup (char *username, char *password)
{
    int last_id = (userlist_last(user_list))->user->id;

    user_t newUser = user_new (last_id + 1, username, password, OFFLINE, -1);
    userlist_append (user_list, newUser);

    fseek (fp, 0, SEEK_END);
    fprintf(fp, "%d,%s,%s",  newUser->id,  newUser->username,  newUser->password);

    return last_id;
}

char * gameserver_core_getPlayerlist () {
    char *userlist_str = (char *) malloc (1024);
    strcpy (userlist_str, "");
    // user_id, sockfd, username
    userlist_t ptr;
    userlist_traverse (ptr, user_list) {
    	char *buffer = (char *) malloc (512);
        if (ptr->user->status == ONLINE) {
            sprintf(buffer, "%d,%d,%s|", ptr->user->id, ptr->user->sockfd, ptr->user->username);
            strcat (userlist_str, buffer);
        }
        free(buffer);
    }
    return userlist_str;
}

int gameserver_core_getOtherUserSockfd (int sockfd) {
	return get_otherUserSockfd(room_list, sockfd);
}

void gameserver_core_initNewRoom (int sockfd1, int sockfd2) {
	roomlist_append(room_list, room_new(sockfd1, sockfd2));
}

void gameserver_core_endSession ()
{
	fclose (fp);
}