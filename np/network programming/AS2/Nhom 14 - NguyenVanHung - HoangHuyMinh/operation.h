#include<stdio.h>
#include"user.h"
#include"creatbtdic.h"
#include"soundex.h"

int searchWord(BTA* btDic,BTA* btSoundex,
	    dict* foundWord,dictsd* hintWord,char word[]);
int editWord(BTA* btDic,BTA* btSoundex,dict* edittedWord,dict* word, int right);
int deleteWord(BTA* btDic,BTA* btSoundex,char word[], int right);
int addWord(BTA* btDic,BTA* btSoundex,dict* newWord, int right);
