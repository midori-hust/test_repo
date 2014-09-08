#ifndef DBACTION
#define DBACTION

#include "sqlite3.h"
#define MAX_STATEMENT_LENGTH 100
#define DB_PATH_LENGTH 1000
#define QUERY_SUCCESS 0
#define QUERY_FAILURE 1

// Define state
typedef enum
{
	NOT_OPEN_CONNECTION,
	OPEN_CONNECTION,
	ASSIGN_STATEMENT,
	BIND_STATEMENT,
	ROW_AVAIABLE,
	INVALID_TYPE,
	NO_RESULT
}DbState;


typedef struct DbAction
{
	sqlite3 *dbObj;
	sqlite3_stmt *sqlStatement;
	char source[DB_PATH_LENGTH];
	char statement[MAX_STATEMENT_LENGTH];
	int n_result_row;
	DbState state;
	int error;
	char *zErrMsg;
	void (*assignStatement)(struct DbAction *, char *);
	void (*resetParameter)(struct DbAction *);
	void (*bindParameterInt)(struct DbAction *, int , int);
	void (*bindParameterString)(struct DbAction *, int , char *);
	void (*execute)(struct DbAction *);
	void (*nextRecord)(struct DbAction *);
	int (*getInt)(struct DbAction *, int);
	char* (*getString) (struct DbAction *, int);
	double (*getDouble) (struct DbAction *, int );
	void (*close_db)(struct DbAction*);
	void (*setPrepareStatement)(struct DbAction *, sqlite3_stmt *);
}DbAction;

void assignStatement(DbAction *db, char *);
void bindParameterInt(DbAction *, int ,int);
void bindParameterString(DbAction *, int,  char*);
void execute(DbAction *);
void nextRecord(DbAction *);
int getInt(DbAction *, int);
char *getString(DbAction *, int );
double getDouble(DbAction *, int);
void resetParameter(DbAction *);
void close_db(DbAction *);
void setPrepareStatement(DbAction *, sqlite3_stmt *);

DbAction createDbAction(char *dbfile);

#endif
