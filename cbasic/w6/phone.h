#ifndef __PHONE_H__
#define __PHONE_H__

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXLENGTH 100

typedef struct phone_information_
{
  char name[MAXLENGTH];
  long int price;
  float rating;
} PhoneInfo;

char menu();
void nhapThongTin(FILE *f);
void sortPhoneName(PhoneInfo *phoneList, int n);
void swap(PhoneInfo *phone1, PhoneInfo *phone2);


#endif
