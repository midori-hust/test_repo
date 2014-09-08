#include "message.h"
#include "common.h"
#include <string.h>
#include <stdlib.h>

Boolean isAskPlayer(Message *message)
{
	char *type = message -> getParameter(message,"type");
	Boolean check = !strcmp(type,"ASKPLAYER");
	free(type);
	return check;
}

Boolean isQuestion(Message *message)
{
	char *type = message->getParameter(message,"type");
	Boolean check = !strcmp(type,"QUESTION");
	free(type);
	return check;
}

Boolean isAskQuestion(Message *message)
{
	char *type = message->getParameter(message,"type");
	Boolean check = !strcmp(type,"ASKQUESTION");
	free(type);
	return check;
}

Boolean isUserAnswer(Message *message)
{
	char *type = message ->getParameter(message,"type");
	Boolean check = !strcmp(type,"USERANSWER");
	free(type);
	return check;
}

Boolean isAccept(Message *message)
{
	char *status = message->getParameter(message,"status");
	Boolean check = !strcmp(status,"ACCEPT");
	free(status);
	return check;
}

Boolean isLoginRequest(Message *message)
{
	char *type = message->getParameter(message,"type");
	Boolean check = !strcmp(type,"LOGIN");
	free(type);
	return check;
}

Boolean isSuccessLogin(Message *message)
{
	char *status = message -> getParameter(message,"status");
	Boolean check = !strcmp(status,"SUCCESS");
	free(status);
	return check;
}

Boolean isComplete(Message *message)
{
	char *status = message -> getParameter(message,"status");
	Boolean check = !strcmp(status,"COMPLETE");
	free(status);
	return check;
}

Boolean isCorrect(Message *message)
{
	char *status = message -> getParameter(message, "status");
	Boolean check = !strcmp(status,"CORRECT");
	free(status);
	return check;
}

Boolean isCountDown(Message *message)
{
	char *type = message -> getParameter(message,"type");
	Boolean check =!strcmp(type,"COUNTDOWN");
	free(type);
	return check;
}

Boolean isClose(Message *message)
{
	char *type = message -> getParameter(message,"type");
	Boolean check = !strcmp(type,"CLOSE");
	free(type);
	return check;
}

Boolean isAskQuestionLevel(Message *message)
{
	char *type = message -> getParameter(message,"type");
	Boolean check = !strcmp(type,"ASKQUESTIONLEVEL");
	free(type);
	return check;
}
