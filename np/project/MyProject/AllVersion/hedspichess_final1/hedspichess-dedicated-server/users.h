#ifndef __USERS_H__
#define __USERS_H__

#include <stdio.h>

#define STR_MAXLEN 64

typedef enum  {
    DEACTIVATED,
    OFFLINE,
    ONLINE,
    INVITED,
    PLAYING
} UserStatusCode;

struct user {
    int id;
    char username[STR_MAXLEN];
    char password[STR_MAXLEN];
    UserStatusCode status;
    int sockfd;
};

typedef struct user *  user_t;

extern user_t user_new (
        int id,
        char *username,
        char *password,
        UserStatusCode statuscode,
        int sockfd
        );

struct userlist {
    user_t user;
    struct userlist * next;
    struct userlist * prev;
};

typedef struct userlist * userlist_t;

#define userlist_first(list) ((list)->prew)
#define userlist_last(list) ((list)->next)
#define userlist_next(list) ((list)->next)
#define userlist_prev(list) ((list)->prev)
#define userlist_nil(list) (list)

#define userlist_traverse(ptr, list) \
    for (ptr = list->next; ptr != list; ptr = ptr->next)

#define userlist_rtraverse(ptr, list) \
    for (ptr = list->prev; ptr != list; ptr = ptr->prev)

extern userlist_t userlist_new ();

extern void userlist_drop (userlist_t list);

extern int userlist_insertA (userlist_t list, user_t user);

extern int userlist_insertB (userlist_t list, user_t user);

extern int userlist_append (userlist_t list, user_t user);

extern int userlist_prepend ();

extern void userlist_removeNode (userlist_t node);

extern int userlist_getUser (userlist_t node);

extern int userlist_isEmpty (userlist_t list);

#endif
