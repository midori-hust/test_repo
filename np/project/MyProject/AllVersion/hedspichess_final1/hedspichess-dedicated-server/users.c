#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"

user_t user_new (
        int id,
        char *username,
        char *password,
        UserStatusCode statuscode,
        int sockfd
        )
{
    user_t new_user = (user_t) malloc (sizeof(struct user));

    new_user->id = id;
    strcpy (new_user->username, username);
    strcpy (new_user->password, password);
    new_user->status = statuscode;
    new_user->sockfd = sockfd;
    return new_user;
}

userlist_t userlist_new ()
{
    userlist_t list;
    list = (userlist_t) malloc (sizeof(struct userlist));
    list->next = list;
    list->prev = list;
    return list;
}

void userlist_removeNode (userlist_t list)
{
    list->next->prev = list->prev;
    list->prev->next = list->next;
    free(list);
}

int userlist_isEmpty (userlist_t list)
{
    return (list->next == list);
}

void userlist_drop (userlist_t list)
{
    while (!userlist_isEmpty(list)) {
        userlist_removeNode(list);
    }
    free(list);
}


/**
 * insert a new user before a given node
 */

int userlist_insertB (userlist_t node, user_t user)
{
    userlist_t newNode;
    newNode = (userlist_t) malloc (sizeof(struct userlist));
    newNode->user = user;

    newNode->next = node;
    newNode->prev = node->prev;
    newNode->prev->next = newNode;
    newNode->next->prev = newNode;
    return 0;

}

int userlist_append (userlist_t list, user_t user)
{
    userlist_insertB (list, user);
    return 0;
}
