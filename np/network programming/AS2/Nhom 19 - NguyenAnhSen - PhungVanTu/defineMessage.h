#ifndef DEFINE_MESSAGE
#define DEFINE_MESSAGE
#include "common.h"
#include "message.h"
Boolean isAskPlayer(Message *);
Boolean isAskQuestion(Message *message);
Boolean isQuestion(Message *newMessage);
Boolean isUserAnswer(Message *newMessage);
Boolean isAccept(Message *message);
Boolean isLoginRequest(Message *messge);
Boolean isSuccessLogin(Message *message);
Boolean isComplete(Message *message);
Boolean isCorrect(Message *message);
Boolean isCountDown(Message *message);
Boolean isClose(Message *);
Boolean isAskQuestionLevel(Message *message);
#endif
