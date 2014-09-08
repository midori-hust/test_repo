#include "library.h"

int getInt() {
  int result;

  while(scanf("%d",&result) != 1) {
    printf("This is not an integer number. Please retype the input: ");
    while(getchar() != '\n');
  }

  return result;
}

float getFloat() {
  float result;

  while(scanf("%f",&result) != 1) {
    printf("This is not a float number. Please retype the input: ");
    while(getchar() != '\n');
  }

  return result;
}

int canTileTheLs() {
	
}