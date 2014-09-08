#include "dbaction.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_DATA_LENGTH 200

DbAction createDbAction(char *filename)
{
	DbAction newDb;
	newDb.assignStatement = assignStatement;
	newDb.bindParameterInt = bindParameterInt;
	newDb.bindParameterString = bindParameterString;
	newDb.execute = execute;
	newDb.nextRecord = nextRecord;
	newDb.resetParameter = resetParameter;
	newDb.n_result_row = NO_RESULT;
	newDb.statement[0]  = 0;
	newDb.getInt = getInt;
	newDb.getString = getString;
	newDb.getDouble = getDouble;
	newDb.setPrepareStatement = setPrepareStatement;
	newDb.error = sqlite3_open(filename,&newDb.dbObj);
	newDb.close_db = close_db;
	printf("Reach here 1\n");
	if (newDb.error != SQLITE_OK) newDb . state = NOT_OPEN_CONNECTION;
	else newDb.state = OPEN_CONNECTION;
	return newDb;
}

void setPrepareStatement(DbAction *db, sqlite3_stmt *stmt)
{
	db -> sqlStatement = stmt;
}

void assignStatement(DbAction *db, char* statement)
{
	if (statement != NULL)
	{
		if (db -> statement[0] == 0)
		{
			strcpy(db -> statement,statement);
			db -> error = sqlite3_prepare_v2(db -> dbObj, statement, 50, &(db -> sqlStatement), &(db -> zErrMsg));
			if (db -> error == SQLITE_OK) db -> state = ASSIGN_STATEMENT;
			printf("Reach here 3\n");
		}
	}
	return ;
}

void bindParameterInt(DbAction *db, int index,int value)
{
	if (index < 0 ) return;
	db -> error = sqlite3_bind_int(db -> sqlStatement, index, value);
	if (db -> error == SQLITE_OK) db -> state = BIND_STATEMENT;
}

void bindParameterString(DbAction *db, int index, char *value)
{
	if (index <= 0) return;
	db -> error = sqlite3_bind_text(db -> sqlStatement, index, value, -1,SQLITE_STATIC);
	if (db -> error == SQLITE_OK) db -> state = BIND_STATEMENT;
}

void execute(DbAction *db)
{
	if (db -> statement[0] == 0) return;
	db ->error = sqlite3_step(db -> sqlStatement);
	if (db -> error == SQLITE_ROW) db -> state = ROW_AVAIABLE;
	else
	db -> state = NO_RESULT;
}

void nextRecord(DbAction *db)
{
	if (db -> statement[0] == 0) return;
	db ->error = sqlite3_step(db -> sqlStatement);
	if (db -> error == SQLITE_ROW) db -> state = ROW_AVAIABLE;
	else
	db -> state = NO_RESULT;
}

int getInt(DbAction *db,int index)
{
	return sqlite3_column_int(db -> sqlStatement, index);
}

char* getString(DbAction *db, int index)
{
	char *str = (char*)malloc(sizeof (char) *(MAX_DATA_LENGTH ));
	strcpy(str,sqlite3_column_text(db -> sqlStatement,index));
	return str;
}

double getDouble(DbAction *db, int index)
{
	return sqlite3_column_double(db -> sqlStatement, index);
}

void resetParameter(DbAction *db)
{
	if (db -> statement[0] != 0)
	sqlite3_reset(db -> sqlStatement);
	//sqlite3_clear_bindings(db -> sqlStatement);
}

void close_db(DbAction *db)
{
	if (db -> state >= ROW_AVAIABLE)
	{
		sqlite3_finalize(db -> sqlStatement);
	}
	sqlite3_close(db -> dbObj);
}

