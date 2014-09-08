#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rooms.h"

room_t room_new (
        int user1_sockfd,
        int user2_sockfd
        )
{
    room_t new_room = (room_t) malloc (sizeof(struct room));

    new_room->user1_sockfd = user1_sockfd;
    new_room->user2_sockfd = user2_sockfd;
    return new_room;
}

roomlist_t roomlist_new ()
{
    roomlist_t list;
    list = (roomlist_t) malloc (sizeof(struct roomlist));
    list->next = list;
    list->prev = list;
    return list;
}

void roomlist_removeNode (roomlist_t list)
{
    list->next->prev = list->prev;
    list->prev->next = list->next;
    free(list);
}

int roomlist_isEmpty (roomlist_t list)
{
    return (list->next == list);
}

void roomlist_drop (roomlist_t list)
{
    while (!roomlist_isEmpty(list)) {
        roomlist_removeNode(list);
    }
    free(list);
}


/**
 * insert a new room before a given node
 */

int roomlist_insertB (roomlist_t node, room_t room)
{
    roomlist_t newNode;
    newNode = (roomlist_t) malloc (sizeof(struct roomlist));
    newNode->room = room;

    newNode->next = node;
    newNode->prev = node->prev;
    newNode->prev->next = newNode;
    newNode->next->prev = newNode;
    return 0;

}

int roomlist_append (roomlist_t list, room_t room)
{
    roomlist_insertB (list, room);
    return 0;
}

int get_otherUserSockfd (roomlist_t roomlist, int sockfd)
{
    roomlist_t ptr;
    roomlist_traverse (ptr, roomlist) {
        if (ptr->room->user1_sockfd == sockfd)
            return ptr->room->user2_sockfd;
        if (ptr->room->user2_sockfd == sockfd)
            return ptr->room->user1_sockfd;
    }
    return -1;
}

