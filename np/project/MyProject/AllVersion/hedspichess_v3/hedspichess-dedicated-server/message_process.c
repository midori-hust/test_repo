#include <stdio.h>

/**
 * process in case of mesg->cmd = SIGNIN
 *
 */
int mesg_process_signin (message_t mesg)
{
    return gameserver_core_signin(mesg->arg, mesg->arg1);
}

int mesg_process_signup (message_t mesg)
{
    return gameserver_core_signup(mesg->arg, mesg->arg1);
}

int mesg_process_signout (message_t mesg)
{
    return gameserver_core_signout(mesg->arg);
}

int mesg_process_join (message_t mesg)
{
    return mesg_process_join (mesg->arg);
}

int mesg_process (message_t mesg)
{
    switch (mesg->cmd) {
        case SIGNIN:
            mesg_process_signin(mesg);
            break;

        case SIGNUP:
                mesg_process_signup(mesg);
                break;

    }
}
