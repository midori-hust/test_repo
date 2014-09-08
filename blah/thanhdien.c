#include <stdio.h>
#include <string.h>

#define MAXLENGTH 100

void ThanhDienRatLaCool(char *thanhdien);
void isThatGirlStupid(char *girlName);

int main(int argc, char const *argv[])
{
	char thanhdien[MAXLENGTH];
	char girlName[MAXLENGTH];

	strcpy(girlName, "Phan Thao");
	isThatGirlStupid(girlName);
	strcpy(thanhdien, "wakaka");
	printf("Thanh dien da tung o day %s\n", thanhdien);
	if(thanhdien != NULL)
	{
		printf("Thanh dien van tue!\n");
		ThanhDienRatLaCool(thanhdien);
	}
	return 0;
}

void ThanhDienRatLaCool(char *thanhdien)
{
	printf("%s thanh dien so cool!\n", thanhdien);
}

void isThatGirlStupid(char *girlName) {

if(strcmp(girlName, "Phan Thao") != 0)
	printf("Yes, she is.\n");
else
	printf("No, she is not.\n");
}