/*Napisati program koji iz datoteke èita postfiks izraz i zatim korištenjem stoga raèuna
rezultat. Stog je potrebno realizirati preko vezane liste.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

struct stog;
typedef struct stog* Position;
typedef struct stog
{
	int el;
	Position next;
}Stog;

void Read(char*, char*);
void Push(Position , int );
int Pop(Position);
int Postfix(Position, char*,int);

int main()
{
	Stog head;
	head.next = NULL;
	int number;
	char name[256];
	char* buffer = NULL;
	buffer = (char*)malloc(1000 * sizeof(char));
	memset(buffer, '\0', 1000);


	printf("\nEnter the name of the document from which you want to read the data(e.g. postfix.txt):\t");
	scanf("%s", name);

	/*number =*/ Read(&name, buffer);
	number = strlen(buffer);
	printf(" =  %d", Postfix(&head, buffer, number));
	puts("");
	puts("");
	system("pause");
	return 0;
}

void Read(char* FileName, char* buffer)
{
	FILE *dat;
	int i = 0, n;

	dat = fopen(FileName, "r");
	if (!dat)
	{
		printf("File failed to open!!");
		return 1;
	}
	fgets(buffer,1000,dat);

		/*while (!feof(dat))
		{
			c[i] = fgetc(dat);
			i++;
		}*/
	fclose(dat);
	//n = i - 1;

	/*for (i = 0;i < n;i++)
		printf("%c", c[i]);*/

	//return n;
}

void Push(Position p, int a)
{
	Position q = NULL;

	while (p->next != NULL)
		p = p->next;

	q = (Position)malloc(sizeof(Stog));
	q->el = a;
	q->next = p->next;
	p->next = q;
}

int Pop(Position p)
{
	Position temp;
	int element;
	temp = p;

	while (temp->next != NULL)
	{
		p = temp;
		temp = temp->next;
	}
	element = temp->el;
	p->next = temp->next;
	free(temp);

	return element;
}

int Postfix(Position head, char* buffer,int n)
{
	int i,number;
	int value;
	//for (i = 0;i < n; i++)

	

	for(i=0;i=<n;i++)
	{
		(c, " %s", a);

		if ((a + i) == ' ')
			continue;
		else if (isdigit(*(a + i)))
		{
			number = 0;

			while (isdigit(*(a + i)))
			{
				number = number * 10 + (int)(*(a + i) - '0');
				i++;
			}
			i--;
			Push(head, number);
		}
		else
		{
			int el1 = Pop(head);
			int el2 = Pop(head);

			switch (c[i])
			{
			case'+':Push(head, el2 + el1);break;
			case'-':Push(head, el2 - el1);break;
			case'*':Push(head, el2 * el1);break;
			case'/':Push(head, el2 / el1);break;
			}
		}
	}
	return Pop(head);
}