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

void mulPoly(Position , Position , Position );
void summPoly(Position, Position, Position);
void printPoly(Position);
void sort1(int,int, Position);
void sort2( Position);
void readPoly(Position, Position,char*);
void insertAfter(Position, Position);
Position createPoly(int ,int );
Position Min(Position , Position );

int main()
{	
	Poly head1,head2, head3,head4;
	head1.next = NULL;
	head2.next = NULL;
	head3.next = NULL;
	head4.next = NULL;
	char name[256];

	printf("\nEnter the name of the document from which you want to read the data(e.g. Poly.txt):\t");
	scanf("%s", name);
	readPoly(&head1 ,&head2,&name);

	printf("\nFirst polynomial:\n");
	printPoly(&head1);
	printf("\nSecond polynomial:\n");
	printPoly(&head2);

	printf("\nThe sum of polynomials:\n");
	summPoly(&head1, &head2, &head3);
	printPoly(&head3);

	printf("\nMultiplication of polynomials:\n");
	mulPoly(&head1, &head2, &head4);
	printPoly(&head4);

	return 0;
}

void readPoly(Position where, Position what, char* FileName)
{
	FILE *dat;
	int coeff = 0, exp = 0;
	char c;
	dat = fopen(FileName, "r");
	if(!dat)
	{
		printf("File failed to open!!");
		return 1;
	}
	
	while (!feof(dat))
	{
		c = fgetc(dat);
		if (c != '\n') {
			fscanf(dat, " %d %d", &coeff, &exp);
			sort1(exp, coeff, where);
		}
		else {
			while (!feof(dat)) {
				fscanf(dat, " %d %d", &coeff, &exp);
				sort1(exp, coeff, what);
			}
		}
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

void sort1(int exp,int coeff, Position where)
{
	Position p;

	while (where->next != NULL && where->next->exp < exp)
		where = where->next;

	p = createPoly(coeff, exp);

	p->next = where->next;
	where->next = p;
}

void sort2(Position head)
{
	Position p,what;
	p = head->next;
	while ( p->next != NULL)
	{
		if (p->exp == p->next->exp)
		{
			p->coeff = p->coeff + p->next->coeff;
			what = p->next;
			p->next = what->next;
			free(what);
		}
		else
			p = p->next;
	}
	p = head->next;
	while (p->next != NULL)
	{
		if (p->next->coeff==0)
		{
			what = p->next;
			p->next = what->next;
			free(what);
		}
		else
			p = p->next;
	}
}

void printPoly(Position head) {
	Position p = NULL;
	
	for (p = head->next; p != NULL; p = p->next)
	{
		if(p->coeff>=0)
			printf("+ %dx^%d ", p->coeff, p->exp);
		else 
			printf(" %dx^%d ", p->coeff, p->exp);
	}

	printf("\n");
}

Position Min(Position p, Position q)
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
			a = Min(p, q);
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
	sort2(head);
}

void mulPoly(Position p, Position q, Position head)
{
	Position  r = NULL, a = NULL, b = NULL,c=NULL;
	Poly pivot, pivot1, pivot2;
	pivot.next = NULL;
	pivot1.next = NULL;
	pivot2.next = NULL;
	int coeff = 0, exp = 0;
	int i = 0, j=0,numb;
	p = p->next;
	q = q->next;
	c = q;
	while (p != NULL)
	{
		q = c;
		while (q != NULL)
		{
			
			coeff = p->coeff * q->coeff;
			exp = p->exp + q->exp;
			r = createPoly(coeff, exp);
			insertAfter(&pivot, r);
			q = q->next;
			i++;
		}
		p = p->next;
	}
	numb = i / 2;
	r = pivot.next;
	while (r != NULL)
	{
		if (j < numb)
		{
			sort1(r->exp,r->coeff, &pivot1);
			r=r->next;
		}
		else
		{
			sort1(r->exp, r->coeff, &pivot2);
			r = r->next;
		}
		j++;
	}
	summPoly(&pivot1, &pivot2, head);
}