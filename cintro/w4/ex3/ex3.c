#include <stdio.h>

#define MAXLENGTH 100

int main() {
	int quantity, price, isbn;
	char title[MAXLENGTH] = "This is a book";

	printf("Please enter the information of the book:\n");
	printf("Title: ");
	gets(title);
	printf("The quantity: ");
	scanf("%d", &quantity);
	while(getchar() != '\n');
	printf("The isbn: ");
	scanf("%d", &isbn);
	while(getchar() != '\n');
	printf("The price: ");
	scanf("%d", &price);
	while(getchar() != '\n');


	printf("Qty %-7dISBN %-7dTitle %-25sPrice %-10dTotal %-10d\n", quantity, isbn, title, price, quantity * price);
	printf("_________________________________________________________________________________________________________________________\n");
	printf("VAT\t\t%d\n", quantity * price * 4 / 100);
	printf("You pay\t\t%d\n", quantity * price * 104 / 100);
	return 0;
}