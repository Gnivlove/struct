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

void summPoly(Position, Position, Position);
void printPoly(Position);
void sort(int,int, Position);
void readPoly(Position,char*);
Position createPoly(int ,int );
Position Max(Position , Position );

int main()
{	
	Poly head1,head2, head3;
	head1.next = NULL;
	head2.next = NULL;
	head3.next = NULL;
	char name1[256], name2[256];

	printf("\nEnter the name of the first document from which you want to read the data(e.g. Poly1.txt):\t");
	scanf("%s", name1);
	readPoly(&head1,&name1 );

	printf("\nEnter the name of the second document from which you want to read the data(e.g. Poly2.txt):\t");
	scanf("%s", name2);
	readPoly(&head2,&name2);

	printPoly(&head1);
	printPoly(&head2);

	summPoly(&head1, &head2, &head3);
	printPoly(&head3);

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

void printPoly(Position head) {
	Position p = NULL;

	printf("\nlist content:\n");
	
	for (p = head->next; p != NULL; p = p->next)
	{
		if(p->coeff>=0)
			printf("+ %dx^%d ", p->coeff, p->exp);
		else
			printf(" %dx^%d ", p->coeff, p->exp);
	}

	printf("\n");
}

Position Max(Position p, Position q)
{
	if (p->exp < q->exp)
		return p;
	else
		return q;

}

void insertAfter(Position where, Position what) {

	while (where->next != NULL)
		where = where->next;

	what->next = where->next;
	where->next = what;
}

void summPoly(Position p, Position q, Position head)
{
	Position r=NULL;
	Position a = NULL;
	int coeff = 0, exp =0 ;
	p = p->next;
	q = q->next;

	while (p != NULL && q != NULL)
	{
		if (p->exp == q->exp)
		{
			coeff = p->coeff + q->coeff;
			if (coeff == 0)
			{
				p = p->next;
				q = q->next;
			}
			else
			{
				exp = p->exp;
				r = createPoly(coeff, exp);
				insertAfter(head, r);

				p = p->next;
				q = q->next;
			}
		}
		else
		{
			a = Max(p, q);
			if (a->coeff == 0);
			else
			{
				r = createPoly(a->coeff, a->exp);
				insertAfter(head, r);
			}
			if (a == p)
				p = p->next;
			else
				q = q->next;
		}
	}
	if (p == NULL)
	{
		while (q!=NULL)
		{
			if (q->coeff == 0)
				q = q->next;
			else
			{
				r = createPoly(q->coeff, q->exp);
				insertAfter(head, r);
				q = q->next;
			}
		}
	}
	else 
	{
		while (p != NULL)
		{
			if (p->coeff == 0)
				p = p->next;
			else
			{
				r = createPoly(p->coeff, p->exp);
				insertAfter(head, r);
				p = p->next;
			}
		}
	}
}
