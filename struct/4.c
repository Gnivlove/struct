/*Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
èitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani. */

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct polynom;
typedef struct polynom* Position;
typedef struct polynom {
	int coeff;
	int exp;
	Position next;
}Poly;

void printList(Position);
void sort(int,int, Position);
void readPoly(Position,char*);
Position createPoly(int ,int );

int main()
{	
	Poly head1,head2;
	head1.next = NULL;
	head2.next = NULL;
	char name1[256], name2[256];
	printf("\nEnter the name of the first document from which you want to read the data(e.g. Poly1.txt):\t");
	scanf("%s", name1);
	readPoly(&head1,&name1 );
	printf("\nEnter the name of the second document from which you want to read the data(e.g. Poly2.txt):\t");
	scanf("%s", name2);
	readPoly(&head2,&name2);
	printList(&head1);
	printList(&head2);

	return 0;
}

void readPoly(Position where, char* FileName)
{
	FILE *dat;
	int coeff = 0, exp = 0;
	dat = fopen(FileName, "r");
	if(!dat)
	{
		printf("File failed to open!!");
		return 1;
	}
	
	while (feof(dat) == 0)
	{
		fscanf(dat, "%d %d", &coeff, &exp);
		sort( exp,  coeff,  where);
	}
	fclose(dat);
}

Position createPoly(int coeff, int exp)
{
	Position p=NULL;
	p = (Position)malloc(sizeof(Poly));
	
	p->coeff = coeff;
	p->exp = exp;

	return p;
}

void sort(int exp,int coeff, Position where)
{
	Position p;

	while (where->next != NULL && where->next->exp < exp)
		where = where->next;

	p = createPoly(coeff, exp);

	p->next = where->next;
	where->next = p;
}

void printList(Position head) {
	Position p = NULL;
	int i = 0;

	printf("\nlist content:\n");
	
	for (p = head->next; p != NULL; p = p->next)
	{
		printf("%dx^%d\t", p->coeff, p->exp);
		i++;
	}

	printf("\n");
}