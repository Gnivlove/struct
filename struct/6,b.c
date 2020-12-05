
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

struct red;
typedef struct red* Position;
typedef struct red
{
	int el;
	Position next;
}Red;

void Print(Position);
void Push(Position);
void Pop(Position);
int Sort(Position);

int main()
{
	srand(time(0));
	Red head;
	head.next = NULL;
	int d;

	while (1)
	{
		printf("\n\tMENU:\n");
		printf("\t1-PUSH\n");
		printf("\t2-POP\n");
		printf("\t0-END \n\tEnter number:\t");
		scanf("%d", &d);
		switch (d)
		{
		case 1:
			Push(&head);
			Print(&head);
			puts("");
			break;
		case 2:
			Pop(&head);
			Print(&head);
			puts("");
			break;
		case 0:
			Print(&head);
			return 0;
			break;
		default:
			puts("Input error!!");
		}
	}
	return 0;
}

void Print(Position p)
{
	int i = 0;
	p = p->next;
	printf("\n\tList content:\n");
	while (p != NULL)
	{
		printf("\t\t%d.   %d\n", i + 1, p->el);
		p = p->next;
		i++;
	}
}

void Push(Position p)
{
	Position q = NULL;
	int a;
	a= Sort(p);

	while (p->next != NULL)
		p = p->next;

	//a = 10 + rand() % 91;

	q = (Position)malloc(sizeof(Red));
	q->el = a;
	q->next = p->next;
	p->next = q;
}

void Pop(Position p)
{
	Position temp;

	temp = p->next;
	p->next = temp->next;
	free(temp);
}

int Sort(Position p)   // sortira niz tako da se u stog ne spremu dva ista rendum broja
{
	Position restart = p;   // varijabla za restartirat virjednost p
	int a;
	int True = 1;			// predpostavka koje ja tocna ako nema istih elemenata u redu
	a = 10 + rand() % 91;

	while (1)
	{
		if (p->el == a)
		{
			a = 10 + rand() % 91;			//ako ima istih elemenata predpostavka je kriva 
			True = 0;						// te generiraj opet neki rendum broj
		}

		if (p->next == NULL && True == 1)		// uvet stajanja ove petlje je ako se dodjemo na kraj liste
			break;								// te predpostavka je istinita ona to znaci da je taj element jedinstven

		if (p->next == NULL)
		{
			p = restart;					// ako smo dosli do kraja liste i predpostavka nije tocna 
			True = 1;						// resetiraj vrijednosti p i resetiraj vrijednost prepostavke
		}

		p = p->next;
	}

	return a;
}