/*	
Write a program that uses random number generation to create sentences. The program should use four arrays of strings called article, noun, verb and preposition. The program should create a sentence by selecting a word at random from each array in the following order: article, noun, verb, preposition, article and noun. As each word is picked, it should be concatenated to the previous words in an array that is large enough to hold the entire sentence. The words should be separated by spaces. When the final sentence is output, it should start with a capital letter and end with a period. The program should generate 10 such sentences.
	The article array should contain the articles "the", "a", "one", "some" and "any";
	The noun array should contain the nouns "boy", "girl", "dog", "town" and "car";
	The verb array should contain the verbs "drove", "jumped", "ran", "walked" and "skipped";
	The preposition array should contain the prepositions "to", "from", "over", "under" and "on".
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define narticle 3
#define nnoun 30
#define nverb 50
#define nprep 23

char* st(char *array[], int n)
{
  return array[rand() % n];
}

main()
{
  char *noun[nnoun] = {"boy", "girl", "worker", "teacher", "nurse", "doctor", "cat", "mouse", "cell phone", "book", "speaker", "pen", "pencil", "lamp", "computer", "laptop", "calculator", "bottle", "shirt", "sip", "student", "pupil", "house", "town", "bus", "desk", "table", "waiter", "boss", "gay"};
  char *verb[nverb] = {"drove", "draws", "writes", "wrote", "reads", "presses", "pressed", "passes", "passed", "ran", "runs", "teaches", "teached", "talks", "talked", "sends", "sent", "receives", "received", "calls", "called", "knows", "finds", "found", "fucks", "fucked", "touches", "taught", "remembers", "remembered", "forgets", "forgot", "admires", "admired", "feeds", "needs", "shoots", "shot", "chooses", "shares", "shared", "sees", "saw", "hits", "got", "get", "makes", "made", "chats", "chated"};
  char *prep[nprep] = {"on", "in", "at", "up", "down", "into", "onto", "upto", "upon", "from", "to", "under", "over", "with", "by", "beside", "byside", "after", "before", "behind", "of", "near", "nearby"};
  char *article[narticle] = {"The", "A(n)", "One"};

  int i;
  srand((unsigned)time(NULL));
  
  printf("\n\tRandom text program\n");
  for(i = 1; i <= 10; i++)
    printf("\n%d. %s %s %s %s %s %s.\n", i, st(article, narticle), st(noun, nnoun), st(verb, nverb), st(prep, nprep), st(article, narticle), st(noun, nnoun));
  printf("\n");
  return 0;
}
