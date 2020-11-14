/*. Za dvije sortirane liste L1 i L2 (mogu se proèitati iz datoteke ili unijeti ruèno, bitno je
samo da su sortirane), napisati program koji stvara novu vezanu listu tako da raèuna:
a) L1unijaL2,
b) L1presjekL2.*/#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct list;
typedef struct list *Position;
typedef struct list
{
	int number;
	Position next;
}List;

void insertAfter(Position, Position);
void sort1(int, Position);
void sort2(Position);
void readPoly(Position, Position, char*);
void Union(Position, Position, Position);
void Intersection(Position, Position, Position);
void print(Position);
Position create(int);

int main()
{
	List head1, head2, head3, head4;
	head1.next = head2.next = head3.next = head4.next = NULL;
	char name[256];

	printf("\nEnter the name of the document from which you want to read the data(e.g. lista.txt):\t");
	scanf("%s", name);
	readPoly(&head1, &head2, &name);

	printf("\nFirst set of numbers:\n");
	print(&head1);
	printf("\nSecond set of numbers:\n");
	print(&head2);

	printf("\nUnion of sets:\n");
	Union(&head1, &head2, &head3);
	print(&head3);

	printf("\nIntersection of sets:\n");
	Intersection(&head1, &head2, &head4);
	print(&head4);

	system("pause");
	return 0;
}

void insertAfter(Position where, Position what) {

	while (where->next != NULL)
		where = where->next;

	what->next = where->next;
	where->next = what;
}

void sort1(int number, Position where)
{
	Position p;

	while (where->next != NULL && where->next->number < number)
		where = where->next;

	p = create(number);

	p->next = where->next;
	where->next = p;
}

void readPoly(Position where, Position what, char* FileName)
{
	FILE *dat;
	int number = 0;
	char c;
	dat = fopen(FileName, "r");
	if (!dat)
	{
		printf("File failed to open!!");
		return 1;
	}

	while (!feof(dat))
	{
		c = fgetc(dat);
		if (c != '\n') {
			fscanf(dat, " %d", &number);
			sort1(number, where);
		}
		else {
			while (!feof(dat)) {
				fscanf(dat, " %d", &number);
				sort1(number, what);
			}
		}
	}
	fclose(dat);
}

void print(Position head)
{
	Position p = NULL;
	printf("\t");

	for (p = head->next;p != NULL;p = p->next)
	{
		printf("%d  ", p->number);
	}
	puts("");
}


Position create(int number)
{
	Position p = NULL;
	p = (Position)malloc(sizeof(List));

	p->number = number;

	return p;
}

void Union(Position p, Position q, Position head)
{
	Position r = NULL;
	p = p->next;
	q = q->next;
	while (p != NULL || q!= NULL)
	{
		if (p == NULL)
			break;

		if (q == NULL)
			break;

		if (p->number < q->number)
		{
			r = create(p->number);
			insertAfter(head, r);
			p = p->next;
		}
		else if (p->number > q->number)
		{
			r = create(q->number);
			insertAfter(head, r);
			q = q->next;
		}
		else if(p->number==q->number)
		{
			r = create(p->number);
			insertAfter(head, r);
			p = p->next;
			q = q->next;
		}

	}

	if (p == NULL)
	{
		while (q != NULL)
		{	
				r = create(q->number);
				insertAfter(head, r);
				q = q->next;
		}
	}
	else
	{
		while (p != NULL)
		{
				r = create(p->number);
				insertAfter(head, r);
				p = p->next;
	
		}
	}
}

void Intersection(Position p, Position q, Position head)
{
	Position r = NULL, a, b;
	p = p->next;
	q = q->next;
	a = p;
	b = q;
	while (p->next != NULL && q->next != NULL)
	{
		if (p->number < q->number)
		{
			p = p->next;
		}
		else if (p->number > q->number)
		{
			q = q->next;
		}
		else
		{
			r = create(p->number);
			insertAfter(head, r);
			p = p->next;
			q = q->next;
		}
	}
	if (p == NULL)
	{
		p = a;
		while (q->next != NULL && p->next != NULL)
		{
			if (p->number < q->number)
			{
				p = p->next;
			}
			else if (p->number > q->number)
			{
				q = q->next;
			}
			else
			{
				r = create(p->number);
				insertAfter(head, r);
				p = p->next;
				q = q->next;
			}
		}
	}
	else
	{
		q = b;
		while (p->next != NULL && q->next != NULL)
		{
			if (p->number < q->number)
			{
				p = p->next;
			}
			else if (p->number > q->number)
			{
				q = q->next;
			}
			else
			{
				r = create(p->number);
				insertAfter(head, r);
				p = p->next;
				q = q->next;
			}
		}
	}

}