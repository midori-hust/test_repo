#include "question.h"
#include <string.h>
#include <stdlib.h>

const char *levelName[] =
{
	"khó",
	"dễ"
};
const char* typeName[] =
{
	"Lịch sử",
	"Địa lý",
	"Văn học",
	"Điện ảnh",
	"Thể thao",
	"Khoa học"
};
Question createQuestion(DbAction *db)
{
	Question newQuestion;
	newQuestion . db = db;
	newQuestion . setType = setType;
	newQuestion . setLevel = setLevel;
	newQuestion . setCorrect = setCorrect;
	newQuestion . setContent = setContent;
	newQuestion . setAnsA = setAnsA;
	newQuestion . setAnsB = setAnsB;
	newQuestion . setAnsC = setAnsC;
	newQuestion . setAnsD = setAnsD;
	newQuestion . loadQuestion = loadQuestion;
	newQuestion . getQuestionType = getQuestionType;
	return newQuestion;
}

void setType(Question *question, char *type)
{
	if (type != NULL)
	strcpy(question -> type, type);
}
void setLevel(Question *question, char *level)
{
	if (level != NULL)
	strcpy(question -> level, level);
}
void setCorrect(Question *question, char *correct)
{
	if (correct != NULL)
	strcpy(question -> correct, correct);
}
void setContent(Question *question, char *content)
{
	if (content != NULL)
	strcpy(question -> content, content);
}

void setAnsA(Question *question, char *a_ans)
{
	if (a_ans != NULL)
	strcpy(question -> a_ans, a_ans);
}

void setAnsB(Question *question, char *b_ans)
{
	if (b_ans != NULL)
	strcpy(question -> b_ans, b_ans);
}

void setAnsC(Question *question, char *c_ans)
{
	if (c_ans != NULL)
	strcpy(question -> c_ans, c_ans);
}

void setAnsD(Question *question, char *d_ans)
{
	if (d_ans != NULL)
	strcpy(question -> d_ans, d_ans);
}

void setQuestion(Question *question, char *type, char *levelname, char *content, char *a_ans, char *b_ans, char *c_ans, char *d_ans, char *correct)
{
	setType(question,type);
	setLevel(question,levelname);
	setContent(question,content);
	setAnsA(question,a_ans);
	setAnsB(question,b_ans);
	setAnsD(question,c_ans);
	setAnsD(question,d_ans);
	setCorrect(question,correct);
}

void displayQuestion(Question *question)
{
	printf("Type id : %d - type name : %s\n",question -> typeID, typeName[question -> typeID]);
	printf("Level ID : %d - Level name : %s\n",question -> levelID, levelName[question -> levelID]);
	//printf("Min : %d\n",)
}
void loadQuestion(Question *question,int min)
{
	displayQuestion(question);
	question -> db -> resetParameter(question ->db);
	question -> db -> bindParameterString(question -> db, 1 , typeName[question -> typeID]);
	question -> db -> bindParameterString(question -> db, 2, levelName[question -> levelID]);
	question -> db -> bindParameterInt(question -> db, 3, min);
	question -> db -> execute(question -> db);
	if (question -> db -> state == ROW_AVAIABLE)
	{
		char *content = question -> db -> getString(question ->db, CONTENT_COLUMN);
		char *a_ans = question -> db -> getString(question -> db, A_ANS_COLUMN);
		char *b_ans = question -> db -> getString(question -> db, B_ANS_COLUMN);
		char *c_ans = question -> db -> getString(question -> db, C_ANS_COLUMN);
		char *d_ans = question -> db -> getString(question -> db, D_ANS_COLUMN);
		char *correct_ans = question -> db -> getString(question -> db, CORRECT_ANS_COLUMN);
		setQuestion(question,typeName[question -> typeID],levelName[question -> levelID],content,a_ans,b_ans,c_ans,d_ans,correct_ans);
		free(content);
		free(a_ans);
		free(b_ans);
		free(c_ans);
		free(d_ans);
		free(correct_ans);
		return;
	}
	else
	{
		printf("No question\n");
		exit(0);
	}
}

void getQuestionType(Question *question)
{
	int i = LICH_SU;
	strcpy(question -> type,typeName[i]);
	question -> typeID = i;
}

