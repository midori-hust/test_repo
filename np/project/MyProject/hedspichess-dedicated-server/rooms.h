#ifndef __ROOMS_H__
#define __ROOMS_H__

#include <stdio.h>

struct room {
    int user1_sockfd;
    int user2_sockfd;
    char *move_history;
};

typedef struct room * room_t;

struct roomlist {
    room_t room;
    struct roomlist * next;
    struct roomlist * prev;
};

typedef struct roomlist * roomlist_t;

#define roomlist_first(list) ((list)->prew)
#define roomlist_last(list) ((list)->next)
#define roomlist_next(list) ((list)->next)
#define roomlist_prev(list) ((list)->prev)
#define roomlist_nil(list) (list)

#define roomlist_traverse(ptr, list) \
    for (ptr = list->next; ptr != list; ptr = ptr->next)

#define roomlist_rtraverse(ptr, list) \
    for (ptr = list->prev; ptr != list; ptr = ptr->prev)

extern room_t room_new (
        int user1_sockfd,
        int user2_sockfd
        );

extern roomlist_t roomlist_new ();

extern void roomlist_drop (roomlist_t list);

extern int roomlist_insertA (roomlist_t list, room_t room);

extern int roomlist_insertB (roomlist_t list, room_t room);

extern int roomlist_append (roomlist_t list, room_t room);

extern int roomlist_prepend ();

extern void roomlist_removeNode (roomlist_t node);

extern int roomlist_getRoom (roomlist_t node);

extern int roomlist_isEmpty (roomlist_t list);

extern int get_otherUserSockfd (roomlist_t roomlist, int sockfd);

#endif


