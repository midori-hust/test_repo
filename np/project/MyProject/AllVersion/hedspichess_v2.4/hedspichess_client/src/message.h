#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <stdio.h>

#define MESSAGE_MAXLEN 1024
#define COMP_MAXLEN 64

#define CMD_DECL "cmd : "
#define ARG_DECL "arg : "
#define ARG1_DECL "arg1 : "
#define OPTION_DECL "option : "
#define OPTION1_DECL "option1 : "

typedef enum {
    SIGNIN,             // arg = id, arg1 = password, opt = "0", opt1 = "0"    
    SIGNUP,             // arg = id, arg1 = password, opt = "0", opt1 = "0"    
    SIGNOUT,            // arg = "0", arg1 = "0", opt = "0", opt1 = "0"    
    GET_PLAYERLIST,     // arg = playerQuantity, arg1 = "0", opt = "0", opt1 = "0"    
    INVITE_SEND,        // arg = inviteId, arg1 = "0", opt = "0", opt1 = "0", if the other accepts invitation, server send PICK_SIDE
    INVITE_RECV,        // 
    INVITE_ACCEPT,
    INVITE_DECLINE,
    LEAVE_ROOM,         //
    MOVE,               // arg = from, arg1 = to, opt = oppositePort, opt1 = "0"
    RESULT,             // arg = winSide, arg1 = loseSide, opt = "0", opt1 = "0"    
    DRAW,               // arg = "0", arg1 = "0", opt = "0", opt1 = "0"  
    PICK_SIDE,          // arg = side, arg1 = oppositePort, opt = "0", opt1 = "0"
    FAILURE             // arg, arg1, opt and opt1 = "0"
} CommandCode;


typedef struct message {
    CommandCode  cmd;
    char arg[COMP_MAXLEN];
    char arg1[COMP_MAXLEN];
    char option[COMP_MAXLEN];
    char option1[COMP_MAXLEN];
} message_;

typedef message_ *  message_t;

extern message_t
message_construct(
        CommandCode cmd,
        char *arg,
        char *arg1,
        char *option,
        char *option1
        );

extern message_t
message_parse(char msg[MESSAGE_MAXLEN]);

extern char*
message_toString(message_t msg);

#endif
