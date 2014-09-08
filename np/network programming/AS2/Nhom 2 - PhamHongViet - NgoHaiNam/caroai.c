#include<stdio.h>
#include<string.h>
#include"caroai.h"

char* table;
int size;
int player, cpu;

void setTable(char* t, int s, int p, int c){
  table = t;
  size = s;
  player = p;
  cpu = c;
}

int getCell(int col, int row){
  if(col < 0 || col >= size)
    return -1;
  if(row < 0 || row >= size)
    return -1;
  return table[row * size + col];		
}

int setCEll(int col, int row, int value){
  if(col < 0 || col >= size)
    return -1;
  if(row < 0 || row >= size)
    return -1;
  table[row * size + col] = value;	
  return 0;	
}

int isNullCell(int col, int row){
  if(col < 0 || col >= size)
    return 0;
  if(row < 0 || row >= size)
    return 0;
  return table[row * size + col] != player && table[row * size + col] != cpu;
}

int isWin(int col, int row, int player){
  int i, j;
  for(i = 1; getCell(col - i, row) == player; i++);
  for(j = 1; getCell(col + j, row) == player; j++);
  if(i + j >= 6 && (isNullCell(col - i, row) || isNullCell(col + j, row)))
    return 1;
  
  for(i = 1; getCell(col, row - i) == player; i++);
  for(j = 1; getCell(col, row + j) == player; j++);
  if(i + j >= 6 && (isNullCell(col, row - i) || isNullCell(col, row + j)))
    return 1;		
  
  for(i = 1; getCell(col - i, row - i) == player; i++);
  for(j = 1; getCell(col + j, row + j) == player; j++);
  if(i + j >= 6 && (isNullCell(col - i, row - i) || isNullCell(col + j, row + j)))
    return 1;	
  
  for(i = 1; getCell(col - i, row + i) == player; i++);
  for(j = 1; getCell(col + j, row - j) == player; j++);
  if(i + j >= 6 && (isNullCell(col - i, row + i) || isNullCell(col + j, row - j)))
    return 1;	
  return 0;	
}

int getRank(int col, int row){
  int rank = 0;
  if(isNullCell(col, row))
    rank += getCell(col, row);
  if(isNullCell(col - 1, row))
    rank += getCell(col - 1, row);
  if(isNullCell(col + 1, row))
    rank += getCell(col + 1, row);	
  if(isNullCell(col, row - 1))
    rank += getCell(col, row - 1);	
  if(isNullCell(col, row + 1))
    rank += getCell(col, row + 1);	
  if(isNullCell(col - 1, row - 1))
    rank += getCell(col - 1, row - 1);	
  if(isNullCell(col + 1, row - 1))
    rank += getCell(col + 1, row - 1);	
  if(isNullCell(col - 1, row + 1))
    rank += getCell(col - 1, row + 1);	
  if(isNullCell(col + 1, row + 1))
    rank += getCell(col + 1, row + 1);				
  return rank;
}

int max(int a, int b){
  if(a > b)
    return a;
  return b;	
}

int min(int a, int b){
  if(a < b)
    return a;
  return b;	
}

int playerMove(int col, int row){
  int i, j;
  int count;
  table[row * size + col] = player;
  //check if win
  if(isWin(col, row, player))
    return 1;	
   
  for(i = 1; getCell(col - i, row) == cpu; i++);
  if(isNullCell(col - i, row) && getCell(col - i, row) > 0)
    setCEll(col - i, row, max(getCell(col - i, row) - 1, 0));
  for(i = i + 1; getCell(col - i, row) == cpu; i++);	
  if(isNullCell(col - i, row) && getCell(col - i, row) > 0)
    setCEll(col - i, row, max(getCell(col - i, row) - 1, 0));
	
  for(i = 1; getCell(col + i, row) == cpu; i++);
  if(isNullCell(col + i, row) && getCell(col + i, row) > 0)
    setCEll(col + i, row, max(getCell(col + i, row) - 1, 0));
  for(i = i + 1; getCell(col + i, row) == cpu; i++);
  if(isNullCell(col + i, row) && getCell(col + i, row) > 0)
    setCEll(col + i, row, max(getCell(col + i, row) - 1, 0));
		
  for(i = 1; getCell(col, row - i) == cpu; i++);
  if(isNullCell(col, row - i) && getCell(col, row - i) > 0)
    setCEll(col, row - i, max(getCell(col, row - i) - 1, 0));
  for(i = i + 1; getCell(col, row - i) == cpu; i++);
  if(isNullCell(col, row - i) && getCell(col, row - i) > 0)
    setCEll(col, row - i, max(getCell(col, row - i) - 1, 0));
		
  for(i = 1; getCell(col, row + i) == cpu; i++);
  if(isNullCell(col, row + i) && getCell(col, row + i) > 0)
    setCEll(col, row + i, max(getCell(col, row + i) - 1, 0));
  for(i = i + 1; getCell(col, row + i) == cpu; i++);
  if(isNullCell(col, row + i) && getCell(col, row + i) > 0)
    setCEll(col, row + i, max(getCell(col, row + i) - 1, 0));
		
  for(i = 1; getCell(col - i, row - i) == cpu; i++);
  if(isNullCell(col - i, row - i) && getCell(col - i, row - i) > 0)
    setCEll(col - i, row - i, max(getCell(col - i, row - i) - 1, 0));
  for(i = i + 1; getCell(col - i, row - i) == cpu; i++);
  if(isNullCell(col - i, row - i) && getCell(col - i, row - i) > 0)
    setCEll(col - i, row - i, max(getCell(col - i, row - i) - 1, 0));
		
  for(i = 1; getCell(col + i, row - i) == cpu; i++);
  if(isNullCell(col + i, row - i) && getCell(col + i, row - i) > 0)
    setCEll(col + i, row - i, max(getCell(col + i, row - i) - 1, 0));
  for(i = i + 1; getCell(col + i, row - i) == cpu; i++);
  if(isNullCell(col + i, row - i) && getCell(col + i, row - i) > 0)
    setCEll(col + i, row - i, max(getCell(col + i, row - i) - 1, 0));
		
  for(i = 1; getCell(col - i, row + i) == cpu; i++);
  if(isNullCell(col - i, row + i) && getCell(col - i, row + i) > 0)
    setCEll(col - i, row + i, max(getCell(col - i, row + i) - 1, 0));
  for(i = i + 1; getCell(col - i, row + i) == cpu; i++);
  if(isNullCell(col - i, row + i) && getCell(col - i, row + i) > 0)
    setCEll(col - i, row + i, max(getCell(col - i, row + i) - 1, 0));
		
  for(i = 1; getCell(col + i, row + i) == cpu; i++);
  if(isNullCell(col + i, row + i) && getCell(col + i, row + i) > 0)
    setCEll(col + i, row + i, max(getCell(col + i, row + i) - 1, 0));	
  for(i = i + 1; getCell(col + i, row + i) == cpu; i++);
  if(isNullCell(col + i, row + i) && getCell(col + i, row + i) > 0)
    setCEll(col + i, row + i, max(getCell(col + i, row + i) - 1, 0));  
    
  count = 0;		
  for(i = 0; getCell(col - i, row) == player; i++)
    count++;
  for(j = 1; getCell(col + j, row) == player; j++)
    count++;			
  if(isNullCell(col - i, row)){
    if(count == 1)
      setCEll(col - i, row, min(20 + getCell(col - i, row) % 10, getCell(col - i, row) + 10));
    else	
      setCEll(col - i, row, max(count * 10 + getCell(col - i, row) % 10, getCell(col - i, row) + 10));
    for(i = i + 1; getCell(col - i, row) == player; i++);	
    if(isNullCell(col - i, row))
      if(count == 1)
	setCEll(col - i, row, min(20 + getCell(col - i, row) % 10, getCell(col - i, row) + 10));
      else
	setCEll(col - i, row, max(count * 10 + getCell(col - i, row) % 10, getCell(col - i, row) + 10));
  }			
  if(isNullCell(col + j, row)){
    if(count == 1)
      setCEll(col + j, row, min(20 + getCell(col + j, row) % 10, getCell(col + j, row) + 10));
    else
      setCEll(col + j, row, max(count * 10 + getCell(col + j, row) % 10, getCell(col + j, row) + 10));
    for(j = j + 1; getCell(col + j, row) == player; j++);	
    if(isNullCell(col + j, row))
      if(count == 1)
	setCEll(col + j, row, min(20 + getCell(col + j, row) % 10, getCell(col + j, row) + 10));
      else
	setCEll(col + j, row, max(count * 10 + getCell(col + j, row) % 10, getCell(col + j, row) + 10));
  }
		
		
  count = 0;	
  for(i = 0; getCell(col, row - i) == player; i++)
    count++;
  for(j = 1; getCell(col, row + j) == player; j++)
    count++;
  if(isNullCell(col, row - i)){
    if(count == 1)
      setCEll(col, row - i, min(20 + getCell(col, row - i) % 10, getCell(col, row - i) + 10));
    else
      setCEll(col, row - i, max(count * 10 + getCell(col, row - i) % 10, getCell(col, row - i) + 10));
    for(i = i + 1; getCell(col, row - i) == player; i++);	
    if(isNullCell(col, row - i))
      if(count == 1)
	setCEll(col, row - i, min(20 + getCell(col, row - i) % 10, getCell(col, row - i) + 10));
      else
	setCEll(col, row - i, max(count * 10 + getCell(col, row - i) % 10, getCell(col, row - i) + 10));
  }
  if(isNullCell(col, row + j)){
    if(count == 1)
      setCEll(col, row + j, min(20 + getCell(col, row + j) % 10, getCell(col, row + j) + 10));
    else
      setCEll(col, row + j, max(count * 10 + getCell(col, row + j) % 10, getCell(col, row + j) + 10));
    for(j = j + 1; getCell(col, row + j) == player; j++);	
    if(isNullCell(col, row + j))
      if(count == 1)
	setCEll(col, row + j, min(20 + getCell(col, row + j) % 10, getCell(col, row + j) + 10));
      else
	setCEll(col, row + j, max(count * 10 + getCell(col, row + j) % 10, getCell(col, row + i) + 10));
  }
  
		
  count = 0;	
  for(i = 0; getCell(col - i, row - i) == player; i++)
    count++;
  for(j = 1; getCell(col + j, row + j) == player; j++)
    count++;		
  if(isNullCell(col - i, row - i)){
    if(count == 1)
      setCEll(col - i, row - i, min(20 + getCell(col - i, row - i) % 10, getCell(col - i, row - i) + 10));
    else	
      setCEll(col - i, row - i, max(count * 10 + getCell(col - i, row - i) % 10, getCell(col - i, row - i) + 10));
    for(i = i + 1; getCell(col - i, row - i) == player;	i++);	
    if(isNullCell(col - i, row - i))
      if(count == 1)
	setCEll(col - i, row - i, min(20 + getCell(col - i, row - i) % 10, getCell(col - i, row - i) + 10));
      else
	setCEll(col - i, row - i, max(count * 10 + getCell(col - i, row - i) % 10, getCell(col - i, row - i) + 10));
  }
  if(isNullCell(col + j, row + j)){
    if(count == 1)
      setCEll(col + j, row + j, min(20 + getCell(col + j, row + j) % 10, getCell(col + j, row + j) + 10));
    else  	
      setCEll(col + j, row + j, max(count * 10 + getCell(col + j, row + j) % 10, getCell(col + j, row + j) + 10));
    for(j = j + 1; getCell(col + j, row + j) == player;	j++);	
    if(isNullCell(col + j, row + j))
      if(count == 1)
	setCEll(col + j, row + j, min(20 + getCell(col + j, row + j) % 10, getCell(col + j, row + j) + 10));
      else 
	setCEll(col + j, row + j, max(count * 10 + getCell(col + j, row + j) % 10, getCell(col + j, row + j) + 10));
  }
			
	
  count = 0;	
  for(i = 0; getCell(col - i, row + i) == player; i++)
    count++;
  for(j = 1; getCell(col + j, row - j) == player; j++)
    count++;
  if(isNullCell(col - i, row + i)){
    if(count == 1)
      setCEll(col - i, row + i, min(20 + getCell(col - i, row + i) % 10, getCell(col - i, row + i) + 10));
    else
      setCEll(col - i, row + i, max(count * 10 + getCell(col - i, row + i) % 10, getCell(col - i, row + i) + 10));
    for(i = i + 1; getCell(col - i, row + i) == player;	i++);	
    if(isNullCell(col - i, row + i))
      if(count == 1)
	setCEll(col - i, row + i, min(20 + getCell(col - i, row + i) % 10, getCell(col - i, row + i) + 10));
      else
	setCEll(col - i, row + i, max(count * 10 + getCell(col - i, row + i) % 10, getCell(col - i, row + i) + 10));
  }
  if(isNullCell(col + j, row - j)){
    if(count == 1)
      setCEll(col + j, row - j, min(20 + getCell(col + j, row - j) % 10, getCell(col + j, row - j) + 10));
    else	 
      setCEll(col + j, row - j, max(count * 10 + getCell(col + j, row - j) % 10, getCell(col + j, row - j) + 10));
    for(j = j + 1; getCell(col + j, row - j) == player;	j++);	
    if(isNullCell(col + j, row - j))
      if(count == 1)
	setCEll(col + j, row - j, min(20 + getCell(col + j, row - j) % 10, getCell(col + j, row - j) + 10));
      else
	setCEll(col + j, row - j, max(count * 10 + getCell(col + j, row - j) % 10, getCell(col + j, row - j) + 10));
  }
  return 0;
}

int cpuMove(int *col, int *row){
  int i, j;
  int memoC = 0, memoR = 0;
  int count;
  for(i = 0; i < size; i++)
    for(j = 0; j < size; j++)
      if(isNullCell(j, i)){
	if(getCell(j, i) / 10 > getCell(memoC, memoR) / 10){
	  memoR = i;
	  memoC = j;
	}
	else if(getCell(j, i) / 10==  getCell(memoC, memoR) / 10 && getRank(j, i) > getRank(memoC, memoR)){
	  memoR = i;
	  memoC = j;
	}
      }
  
  if(getCell(memoC, memoR) >= 30){
    *col = memoC;
    *row = memoR;	
    table[(*row) * size + (*col)] = cpu;
  }
  else{
    *col = 0;
    *row = 0;
    for(i = 0; i < size; i++)
      for(j = 0; j < size; j++)
      	if(isNullCell(j, i)){
	  if(getCell(j, i) % 10 > getCell(*col, *row) % 10){
	    *row = i;
	    *col = j;
	  }
	  else if(getCell(j, i) % 10 ==  getCell(*col, *row) % 10 && getRank(j, i) > getRank(*col, *row)){
	    *row = i;
	    *col = j;
	  }
      	}
    
    if(!isNullCell(*col, *row)){
      *col = memoC;
      *row = memoR;	
    }
    table[(*row) * size + (*col)] = cpu;	
  }

  //check if win
  if(isWin(*col, *row, cpu))
    return 1;
	
  for(i = 1; getCell(*col - i, *row) == player;	i++);
  if(isNullCell(*col - i, *row) && getCell(*col - i, *row) > 0)
    setCEll(*col - i, *row, max(getCell(*col - i, *row) - 10, 0));
  for(i = i + 1; getCell(*col - i, *row) == player; i++);	
  if(isNullCell(*col - i, *row) && getCell(*col - i, *row) > 0)
    setCEll(*col - i, *row, max(getCell(*col - i, *row) - 10, 0));
	
  for(i = 1; getCell(*col + i, *row) == player;	i++);
  if(isNullCell(*col + i, *row) && getCell(*col + i, *row) > 0)
    setCEll(*col + i, *row, max(getCell(*col + i, *row) - 10, 0));
  for(i = i + 1; getCell(*col + i, *row) == player; i++);
  if(isNullCell(*col + i, *row) && getCell(*col + i, *row) > 0)
    setCEll(*col + i, *row, max(getCell(*col + i, *row) - 10, 0));
		
  for(i = 1; getCell(*col, *row - i) == player;	i++);
  if(isNullCell(*col, *row - i) && getCell(*col, *row - i) > 0)
    setCEll(*col, *row - i, max(getCell(*col, *row - i) - 10, 0));
  for(i = i + 1; getCell(*col, *row - i) == player;	i++);
  if(isNullCell(*col, *row - i) && getCell(*col, *row - i) > 0)
    setCEll(*col, *row - i, max(getCell(*col, *row - i) - 10, 0));
		
  for(i = 1; getCell(*col, *row + i) == player;	i++);
  if(isNullCell(*col, *row + i) && getCell(*col, *row + i) > 0)
    setCEll(*col, *row + i, max(getCell(*col, *row + i) - 10, 0));
  for(i = i + 1; getCell(*col, *row + i) == player; i++);
  if(isNullCell(*col, *row + i) && getCell(*col, *row + i) > 0)
    setCEll(*col, *row + i, max(getCell(*col, *row + i) - 10, 0));
		
  for(i = 1; getCell(*col - i, *row - i) == player; i++);
  if(isNullCell(*col - i, *row - i) && getCell(*col - i, *row - i) > 0)
    setCEll(*col - i, *row - i, max(getCell(*col - i, *row - i) - 10, 0));
  for(i = i + 1; getCell(*col - i, *row - i) == player; i++);
  if(isNullCell(*col - i, *row - i) && getCell(*col - i, *row - i) > 0)
    setCEll(*col - i, *row - i, max(getCell(*col - i, *row - i) - 10, 0));
		
  for(i = 1; getCell(*col + i, *row - i) == player; i++);
  if(isNullCell(*col + i, *row - i) && getCell(*col + i, *row - i) > 0)
    setCEll(*col + i, *row - i, max(getCell(*col + i, *row - i) - 10, 0));
  for(i = i + 1; getCell(*col + i, *row - i) == player; i++);
  if(isNullCell(*col + i, *row - i) && getCell(*col + i, *row - i) > 0)
    setCEll(*col + i, *row - i, max(getCell(*col + i, *row - i) - 10, 0));
		
  for(i = 1; getCell(*col - i, *row + i) == player; i++);
  if(isNullCell(*col - i, *row + i) && getCell(*col - i, *row + i) > 0)
    setCEll(*col - i, *row + i, max(getCell(*col - i, *row + i) - 10, 0));
  for(i = i + 1; getCell(*col - i, *row + i) == player; i++);
  if(isNullCell(*col - i, *row + i) && getCell(*col - i, *row + i) > 0)
    setCEll(*col - i, *row + i, max(getCell(*col - i, *row + i) - 10, 0));
		
  for(i = 1; getCell(*col + i, *row + i) == player; i++);
  if(isNullCell(*col + i, *row + i) && getCell(*col + i, *row + i) > 0)
    setCEll(*col + i, *row + i, max(getCell(*col + i, *row + i) - 10, 0));	
  for(i = i + 1; getCell(*col + i, *row + i) == player; i++);
  if(isNullCell(*col + i, *row + i) && getCell(*col + i, *row + i) > 0)
    setCEll(*col + i, *row + i, max(getCell(*col + i, *row + i) - 10, 0));
    
  count = 0;		
  for(i = 0; getCell(*col - i, *row) == cpu; i++)
    count++;
  for(j = 1; getCell(*col + j, *row) == cpu; j++)
    count++;			
  if(isNullCell(*col - i, *row)){
    if(count == 1)
      setCEll(*col - i, *row, min(2 + (getCell(*col - i, *row) / 10) * 10, getCell(*col - i, *row) + 1));
    else	
      setCEll(*col - i, *row, max(count + (getCell(*col - i, *row) / 10) * 10, getCell(*col - i, *row) + 1));
    for(i = i + 1; getCell(*col - i, *row) == cpu; i++);	
    if(isNullCell(*col - i, *row))
      if(count == 1)
	setCEll(*col - i, *row, min(2 + (getCell(*col - i, *row) / 10) * 10, getCell(*col - i, *row) + 1));
      else
	setCEll(*col - i, *row, max(count + (getCell(*col - i, *row) / 10) * 10, getCell(*col - i, *row) + 1));
  }			
  if(isNullCell(*col + j, *row)){
    if(count == 1)
      setCEll(*col + j, *row, min(2 + (getCell(*col + j, *row) / 10) * 10, getCell(*col + j, *row) + 1));
    else
      setCEll(*col + j, *row, max(count + (getCell(*col + j, *row) / 10) * 10, getCell(*col + j, *row) + 1));
    for(j = j + 1; getCell(*col + j, *row) == cpu; j++);	
    if(isNullCell(*col + j, *row))
      if(count == 1)
	setCEll(*col + j, *row, min(2 + (getCell(*col + j, *row) / 10) * 10, getCell(*col + j, *row) + 1));
      else
	setCEll(*col + j, *row, max(count + (getCell(*col + j, *row) / 10) * 10, getCell(*col + j, *row) + 1));
  }
  
  
  count = 0;	
  for(i = 0; getCell(*col, *row - i) == cpu; i++)
    count++;
  for(j = 1; getCell(*col, *row + j) == cpu; j++)
    count++;
  if(isNullCell(*col, *row - i)){
    if(count == 1)
      setCEll(*col, *row - i, min(2 + (getCell(*col, *row - i) / 10) * 10, getCell(*col, *row - i) + 1));
    else
      setCEll(*col, *row - i, max(count + (getCell(*col, *row - i) / 10) * 10, getCell(*col, *row - i) + 1));
    for(i = i + 1; getCell(*col, *row - i) == cpu; i++);	
    if(isNullCell(*col, *row - i))
      if(count == 1)
	setCEll(*col, *row - i, min(2 + (getCell(*col, *row - i) / 10) * 10, getCell(*col, *row - i) + 1));
      else
	setCEll(*col, *row - i, max(count + (getCell(*col, *row - i) / 10) * 10, getCell(*col, *row - i) + 1));
  }
  if(isNullCell(*col, *row + j)){
    if(count == 1)
      setCEll(*col, *row + j, min(2 + (getCell(*col, *row + j) / 10) * 10, getCell(*col, *row + j) + 1));
    else
      setCEll(*col, *row + j, max(count + (getCell(*col, *row + j) / 10) * 10, getCell(*col, *row + j) + 1));
    for(j = j + 1; getCell(*col, *row + j) == cpu; j++);	
    if(isNullCell(*col, *row + j))
      if(count == 1)
	setCEll(*col, *row + j, min(2 + (getCell(*col, *row + j) / 10) * 10, getCell(*col, *row + j) + 1));
      else
	setCEll(*col, *row + j, max(count + (getCell(*col, *row + j) / 10) * 10, getCell(*col, *row + i) + 1));
  }
  
  
  count = 0;	
  for(i = 0; getCell(*col - i, *row - i) == cpu; i++)
    count++;
  for(j = 1; getCell(*col + j, *row + j) == cpu; j++)
    count++;		
  if(isNullCell(*col - i, *row - i)){
    if(count == 1)
      setCEll(*col - i, *row - i, min(2 + (getCell(*col - i, *row - i) / 10) * 10, getCell(*col - i, *row - i) + 1));
    else	
      setCEll(*col - i, *row - i, max(count + (getCell(*col - i, *row - i) / 10) * 10, getCell(*col - i, *row - i) + 1));
    for(i = i + 1; getCell(*col - i, *row - i) == cpu; i++);	
    if(isNullCell(*col - i, *row - i))
      if(count == 1)
	setCEll(*col - i, *row - i, min(2 + (getCell(*col - i, *row - i) / 10) * 10, getCell(*col - i, *row - i) + 1));
      else
	setCEll(*col - i, *row - i, max(count + (getCell(*col - i, *row - i) / 10) * 10, getCell(*col - i, *row - i) + 1));
  }
  if(isNullCell(*col + j, *row + j)){
    if(count == 1)
      setCEll(*col + j, *row + j, min(2 + (getCell(*col + j, *row + j) / 10) * 10, getCell(*col + j, *row + j) + 1));
    else  	
      setCEll(*col + j, *row + j, max(count + (getCell(*col + j, *row + j) / 10) * 10, getCell(*col + j, *row + j) + 1));
    for(j = j + 1; getCell(*col + j, *row + j) == cpu; j++);	
    if(isNullCell(*col + j, *row + j))
      if(count == 1)
	setCEll(*col + j, *row + j, min(2 + (getCell(*col + j, *row + j) / 10) * 10, getCell(*col + j, *row + j) + 1));
      else 
	setCEll(*col + j, *row + j, max(count + (getCell(*col + j, *row + j) / 10) * 10, getCell(*col + j, *row + j) + 1));
  }
  
  
  count = 0;	
  for(i = 0; getCell(*col - i, *row + i) == cpu; i++)
    count++;
  for(j = 1; getCell(*col + j, *row - j) == cpu; j++)
    count++;
  if(isNullCell(*col - i, *row + i)){
    if(count == 1)
      setCEll(*col - i, *row + i, min(2 + (getCell(*col - i, *row + i) / 10) * 10, getCell(*col - i, *row + i) + 1));
    else
      setCEll(*col - i, *row + i, max(count + (getCell(*col - i, *row + i) / 10) * 10, getCell(*col - i, *row + i) + 1));
    for(i = i + 1; getCell(*col - i, *row + i) == cpu; i++);	
    if(isNullCell(*col - i, *row + i))
    	if(count == 1)
	  setCEll(*col - i, *row + i, min(2 + (getCell(*col - i, *row + i) / 10) * 10, getCell(*col - i, *row + i) + 1));
	else
	  setCEll(*col - i, *row + i, max(count + (getCell(*col - i, *row + i) / 10) * 10, getCell(*col - i, *row + i) + 1));
  }
  if(isNullCell(*col + j, *row - j)){
  	if(count == 1)
	  setCEll(*col + j, *row - j, min(2 + (getCell(*col + j, *row - j) / 10) * 10, getCell(*col + j, *row - j) + 1));
  	else	 
	  setCEll(*col + j, *row - j, max(count + (getCell(*col + j, *row - j) / 10) * 10, getCell(*col + j, *row - j) + 1));
	for(j = j + 1; getCell(*col + j, *row - j) == cpu; j++);	
	if(isNullCell(*col + j, *row - j))
	  if(count == 1)
	    setCEll(*col + j, *row - j, min(2 + (getCell(*col + j, *row - j) / 10) * 10, getCell(*col + j, *row - j) + 1));
	  else
	    setCEll(*col + j, *row - j, max(count + (getCell(*col + j, *row - j) / 10) * 10, getCell(*col + j, *row - j) + 1));
  }  
  return 0;
}
