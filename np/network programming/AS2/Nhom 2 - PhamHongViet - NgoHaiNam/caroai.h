#include<stdio.h>
#include<string.h>

char* table;
int size;
int player, cpu;

void setTable(char* t, int s, int p, int c);

int getCell(int col, int row);

int setCEll(int col, int row, int value);

int isNullCell(int col, int row);

int isWin(int col, int row, int player);

int getRank(int col, int row);

int max(int a, int b);

int playerMove(int col, int row);

int cpuMove(int *col, int *row);
