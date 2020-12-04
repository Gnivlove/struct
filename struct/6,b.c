
#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct red;
typedef struct red *Position;
typedef struct red {
	int el;
	Position next;
}Red;

void Push(Position);
void Print(Position);
void Pop(Position);

int main()
{
	Red head;
	head.next = NULL;
	int d;
	srand(time(0));
	while (1)
	{
		printf("\n\tMENU:\n");
		printf("\t1-PUSH\n");
		printf("\t2-POP\n");
		printf("\t0-END\n\tEnter number:  ");
		scanf(" %d", &d);

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
			puts("");
			return 0;
		default:
			puts("\nInput Eror!!\n");
			break;
		}
	}
	system("pause");
	return 0;
}

void Print(Position p)
{
	int i = 0;
	p = p->next;
	puts("List content:\n\n");
	while (p != NULL)
	{
		printf("\t\t%d.  %d\n", i + 1, p->el);
		i++;
	}
}

void Push(Position p)
{
	Position q = NULL;
	static Position last;
	int a;
	a = 10 + rand() % 91;

	//while (p->next != NULL)
	//	p = p->next;

	q = (Position)malloc(sizeof(Red));
	q->el = a;

	if (p->next == NULL)
		last = p;

	q->next = last->next;
	last->next = q;
	last = q;
}

void Pop(Position p)
{
	Position temp = p->next;

	p->next = temp->next;
	free(temp);
}
