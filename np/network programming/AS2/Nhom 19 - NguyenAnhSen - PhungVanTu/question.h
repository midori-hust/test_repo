#ifndef QUESTION
#define QUESTION
#include "dbaction.h"
#define MAX_LENG_ANS 400
#define MAX_CONTENT_LENGTH 1000
#define MAX_TYPE_LENGTH 400
typedef enum
{
	LICH_SU,
	DIA_LY,
	VAN_HOC,
	DIEN_ANH,
	THE_THAO,
	KHOA_HOC
}
Type;

typedef enum level
{
	HARD,
	EASY
}Level;

typedef enum
{
	ID_COLUMN,
	A_ANS_COLUMN,
	B_ANS_COLUMN,
	C_ANS_COLUMN,
	D_ANS_COLUMN,
	CORRECT_ANS_COLUMN,
	LEVEL_COLUMN,
	CONTENT_COLUMN,
	TYPE_COLUMN
}COLUMN_ORDER;
typedef struct Question 
{
	DbAction *db;
	int typeID;
	int levelID;
	char type[MAX_TYPE_LENGTH];
	char level[MAX_TYPE_LENGTH];
	char correct[MAX_LENG_ANS];
	char content[MAX_CONTENT_LENGTH];
	char a_ans[MAX_LENG_ANS];
	char b_ans[MAX_LENG_ANS];
	char c_ans[MAX_LENG_ANS];
	char d_ans[MAX_LENG_ANS];
	void (*setType)(struct Question *, char *);
	void (*setLevel)(struct Question *, char *);
	void (*setCorrect)(struct Question *, char *);
	void (*setContent)(struct Question *, char *);
	void (*setAnsA)(struct Question *, char *);
	void (*setAnsB)(struct Question *, char *);
	void (*setAnsC)(struct Question *, char *);
	void (*setAnsD)(struct Question *, char *);
	void (*loadQuestion)(struct Question *,int min);
	void (*getQuestionType)(struct Question *);
}
Question;
// Internal method
void setType(Question *, char *);
void setLevel(Question *, char *);
void setCorrect(Question *, char *);
void setContent(Question *, char *);
void setAnsA(Question *, char *);
void setAnsB(Question *, char *);
void setAnsC(Question *, char *);
void setAnsD(Question *, char *);

void getQuestionType (Question *);
// External method
void setQuestion(Question *question, char *type, char *level, char *content, char *a_ans, char *b_ans, char *c_ans, char *d_ans, char *correct);
void loadQuestion(Question *,int min);
int getQuestionTypeID(char *);
int getQuestionLevelID(char *);

Question createQuestion();
#endif
