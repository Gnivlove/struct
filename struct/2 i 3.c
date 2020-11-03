/*Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
a) dinamièki dodaje novi element na poèetak liste,
b) ispisuje listu,
c) dinamièki dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.
Prethodnom zadatku dodati funkcije:
a) dinamički dodaje novi element iza određenog elementa,
b) dinamički dodaje novi element ispred određenog elementa,
c) sortira listu po prezimenima osoba,
d) upisuje listu u datoteku,
e) čita listu iz datoteke****/

#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define M (256)

struct _student;
typedef struct _student* Position;
typedef struct _student {
	char firstName[M];
	char lastName[M];
	int year;
	Position next;
} Student;

Position createStudent(char*, char*, int);
void delete(char, Position);
void insertAfter(Position, Position);
void insertBefore(Position, Position);
Position find(char*, Position);
Position findPrev(char*, Position);
void printList(Position);
int printfind(char* , Position );
void insertAfterWho(char* , Position , Position );
void insertBeforeWho(char*, Position, Position);
void Sort(Position);
void printInDat(char* ,Position);
void readFromDat(char* , Position);

int main(void) {
	Student head;
	Position p = NULL;
	char firstName[M] = { 0 };
	char lastName[M] = { 0 }, lName[M] = { 0 };
	int year = 0;
	head.next = NULL;
	int persons, i, numb,b;
	char c,name[50];

	printf("\nDo you want to enter a new list or read it from a file?\n");
	printf("\n\nMENU:\nChoose one option:\n\t1->read the list from a file\n");
	printf("\t2->enter new list\n\tOption:\t");
	scanf(" %d", &b);

	if (b == 1)
	{
		printf("\nEnter the name of the document in which you want to save the list (e.g. Student.txt):\t");
		scanf("%s", name);
		readFromDat(name, &head);
		printList(&head);
	}
	else if (b == 2)
	{

		printf("\nHow many students do you want to enter:\t");
		scanf("%d", &persons);

		for (i = 0; i < persons; i++)
		{
			printf("\nPlease insert person:\n");

			printf("First name:\t");
			scanf(" %s", firstName);

			printf("Last name:\t");
			scanf(" %s", lastName);

			printf("Birth year:\t");
			scanf(" %d", &year);

			p = createStudent(firstName, lastName, year);
			insertAfter(&head, p);
			puts("\n");
			printList(&head);
		}
	}

	while (1)
	{
		printf("\n\nMENU:\nChoose one option:\n\tB->insert new person at the beginning of the list\n");
		printf("\tA->insert new person at the end of the list\n\tF->find a person(by last name)\n\tD->delete a person\n");
		printf("\tI->insert new person after choosen one\n\tK->insert new person before choosen one\n");
		printf("\tS->sorting by last name\n\tC->writes the list to a file\n");
		printf("\tE->if you are done with the selection\n\tOption:\t");
		scanf(" %c", &c);

		switch (c)
		{
		case 'b':
		case 'B':
			printf("\nPlease insert person:\n");

			printf("First name:\t");
			scanf(" %s", firstName);

			printf("Last name:\t");
			scanf(" %s", lastName);

			printf("Birth year:\t");
			scanf(" %d", &year);

			p = createStudent(firstName, lastName, year);
			insertBefore(&head, p);
			puts("\n");
			printList(&head);
			break;
		case 'a':
		case 'A':
			printf("\nPlease insert person:\n");

			printf("First name:\t");
			scanf(" %s", firstName);

			printf("Last name:\t");
			scanf(" %s", lastName);

			printf("Birth year:\t");
			scanf(" %d", &year);

			p = createStudent(firstName, lastName, year);
			insertAfter(&head, p);
			puts("\n");
			printList(&head);
			break;
		case 'f':
		case 'F':
			printf("\nPlease insert person last name:");
			scanf(" %s", lastName);
			puts("\n");
			p = find(lastName, &head);
			if (p != NULL)
				printf("\t1. %-15s\t%-15s\t%d\n", p->firstName, p->lastName, p->year);
			break;
		case 'd':
		case 'D':
			printf("\nPlease insert person last name:");
			scanf(" %s", lastName);
			puts("\n");
			delete(lastName, &head);
			printList(&head);
			break;
		case 'i':
		case 'I':
			printf("\nPlease insert new person:\n");

			printf("First name:\t");
			scanf(" %s", firstName);

			printf("Last name:\t");
			scanf(" %s", lastName);

			printf("Birth year:\t");
			scanf(" %d", &year);

			p = createStudent(firstName, lastName, year);
			printf("\nPlease insert person last name:\t");
			scanf(" %s", lName);

			insertAfterWho(lName,&head,p);

			puts("\n");
			printList(&head);
			break;
		case 'k':
		case 'K':
			printf("\nPlease insert new person:\n");

			printf("First name:\t");
			scanf(" %s", firstName);

			printf("Last name:\t");
			scanf(" %s", lastName);

			printf("Birth year:\t");
			scanf(" %d", &year);

			p = createStudent(firstName, lastName, year);
			printf("\nPlease insert person last name:\t");
			scanf(" %s", lName);

			insertBeforeWho(lName, &head, p);

			puts("\n");
			printList(&head);
			break;
		case 's':
		case 'S':
			Sort(&head);
			puts("\n");
			printList(&head);
			break;
		case 'c':
		case 'C':
			printf("\nEnter the name of the document from which you want to read the data(e.g. Student.txt):\t");
			scanf("%s", name);
			printInDat(&name, &head);
			break;
		case 'E':
		case 'e':
			printList(&head);
			return EXIT_SUCCESS;
			break;
		default:
			puts("Input error!!");
		}
	}

	return EXIT_SUCCESS;
}

Position createStudent(char* firstName, char* lastName, int year) {
	Position p = NULL;

	p = (Position)malloc(sizeof(Student));

	if (!p) {
		printf("Memory allocation failed!\r\n");
		return NULL;
	}

	strcpy(p->firstName, firstName);
	strcpy(p->lastName, lastName);
	p->year = year;
	p->next = NULL;

	return p;
}

void insertBefore(Position where, Position what) {
	what->next = where->next;
	where->next = what;
}

void printList(Position head) {
	Position p = NULL;
	int i = 0;

	printf("list content:\n");
	printf("\t  First name\t\tLast name\tBirth year\n");

	for (p = head->next; p != NULL; p = p->next)
	{
		printf("\t%d. %-15s\t%-15s\t%d\n", i + 1, p->firstName, p->lastName, p->year);
		i++;
	}

	printf("\n");
}

void insertAfter(Position where, Position what) {

	while (where->next != NULL)
		where = where->next;

	what->next = where->next;
	where->next = what;
}

Position find(char* who, Position where)
{
	Position p = NULL;
	int i, numb, j = 0;
	i = printfind(who, where);

	if (i == 0)
	{
		printf("\nThat person does not exist!!\n");
		return NULL;
	}
	else if (i == 1)
	{
		for (p = where; p != NULL; p = p->next)
		{
			if (strcmp(p->lastName, who) == 0)
			{
				if (j == 0)
					return p;

				j++;
			}
		}
	}
	else
	{
		printf("\nWhich one are you looking for (enter number):\t");
		scanf("%d", &numb);

		for (p = where; p != NULL; p = p->next)
		{
			if (strcmp(p->lastName, who) == 0)
			{
				if (j == numb - 1)
					return p;

				j++;
			}
		}
	}
}

Position findPrev(char* who, Position where )
{
	Position p = NULL;
	int i, numb, j = 0;
	i = printfind(who, where);

	if (i == 0)
	{
		printf("\nThat person does not exist!!\n");
		return NULL;
	}
	else if (i == 1)
	{
		for (p = where; p != NULL; p = p->next)
		{
			if (strcmp(p->next->lastName, who) == 0)
			{
				if (j == 0)
					return p;

				j++;
			}
		}
	}
	else
	{
		printf("\nWhich one are you looking for (enter number):\t");
		scanf("%d", &numb);

		for (p = where; p != NULL; p = p->next)
		{
			if (strcmp(p->next->lastName, who) == 0)
			{
				if (j == numb - 1)
					return p;

				j++;
			}
		}
	}
}

void delete(char* who, Position where)
{
	Position before;
	int i, numb;

		before = findPrev(who, where);

		if (before != NULL)
		{
			where = before->next;
			before->next = where->next;
			free(where);
		}
}

int printfind(char* who, Position where)
{
	Position p = NULL;
	int i = 0;

	for (p = where->next; p != NULL; p = p->next)
	{
		if (strcmp(p->lastName, who)==0)
		{
			printf("\t%d. %-15s\t%-15s\t%d\n", i + 1, p->firstName, p->lastName, p->year);
			i++;
		}
	}
	return i;
}

void insertAfterWho(char* who, Position where, Position what)
{
	where = find(who, where);

	if (where != 0)
		insertBefore(where, what);
}

void insertBeforeWho(char* who, Position where, Position what)
{
	where = findPrev(who, where);

	if (where != 0)
		insertBefore(where, what);
}

void Sort(Position where)
{
	Position end = NULL, temp, what, prev;

	while (where->next != end)
	{
		prev = where;
		what = where->next;
		while (what->next != end)
		{
			if (strcmp(what->lastName, what->next->lastName) > 0)
			{
				temp = what->next;
				prev->next = temp;
				what->next = temp->next;
				temp->next = what;
				what = temp;
			}
			else if (strcmp(what->lastName, what->next->lastName) == 0)
			{
				if (strcmp(what->firstName, what->next->firstName) > 0)
				{
					temp = what->next;
					prev->next = temp;
					what->next = temp->next;
					temp->next = what;
					what = temp;
				}
			}

			prev = what;
			what = what->next;
		}
		end = what;
	}
}

void printInDat(char* FileName, Position head)
{
	Position p = NULL;
	int i = 0;
	FILE* dat;
	dat = fopen(FileName, "w");

	fprintf(dat,"\t  First name\t\tLast name\tBirth year\n" );
	for (p = head->next; p != NULL; p = p->next)
	{
		fprintf(dat,"\t%d. %-15s\t%-15s\t%d\n", i + 1, p->firstName, p->lastName, p->year);
		i++;
	}

	fclose(dat);

	printf("\n");
}

void readFromDat(char* FileName, Position head)
{
	Position p = NULL;
	char firstName[M] = { 0 };
	char lastName[M] = { 0 };
	int year = 0;
	int i ;
	FILE* dat;
	dat = fopen(FileName, "r");
	p = head->next;

	while (fgetc(dat) != '\n') {};

	while (1)
	{
		fscanf(dat, "%d. %s %s %d", &i, firstName, lastName, &year);
		
		if (feof(dat))
			break;

		p=createStudent(firstName, lastName, year);
		insertAfter(head, p);
		p = p->next;

	}
	fclose(dat);
	printf("\n");
}
