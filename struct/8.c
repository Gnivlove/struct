/*Napisati program koji pomoæu vezanih listi (stabala) predstavlja strukturu direktorija.
Omoguæiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Toènije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_LENGTH (256)


struct _dir;
typedef struct _dir* PositionDir;
typedef struct _dir {
	char name[MAX_LENGTH];
	PositionDir sibling;
	PositionDir child;
}Dir;

struct _stack;
typedef struct _stack* PositionStack;
typedef struct _stack {
	PositionDir dir;
	PositionStack next;
}Stack;

PositionDir PopDirectory(PositionStack);
int PushDirectory(PositionStack , PositionDir );
int Delete(PositionDir);
PositionDir CreateDirectory(char*);
int PrintStack(PositionStack );
int PrintDirectories(PositionDir );
PositionDir cd(PositionDir, PositionStack, char*);
int  InsertDirectory(PositionDir , char* );
PositionDir FindDirectory(PositionDir , char* );
PositionDir InsertRecursively(PositionDir , PositionDir );
int menu(PositionStack,PositionDir);


int main()
{
	PositionDir root = CreateDirectory("C:");
	Stack head ;
	head.next = NULL;

	PushDirectory(&head, root);
	menu(&head, root);

	return EXIT_SUCCESS;
}

int menu(PositionStack head, PositionDir root)
{
	PositionDir current = root;
	int i = 1;

	printf("Now you are in the main directory\n");
	printf("Type one of those comands: md (Name of directory),cd (Name of directory),cd.. ,exit\n");
	PrintStack(head->next);

	while (i)
	{
		char UserEnter[MAX_LENGTH];
		char Command[(MAX_LENGTH / 2) - 1] = "";
		char NameOfDir[(MAX_LENGTH / 2) - 1] = "";

		fgets(UserEnter, MAX_LENGTH,stdin);
		sscanf(UserEnter, "%s %s", Command, NameOfDir);

		if (!strcmp(Command, "cd.."))
		{
			if (current == root) {
				printf("\nThis is main directory\n");
				PrintStack(head->next);
			}
			else
			{
				current = PopDirectory(head);
				PrintStack(head->next);
			}
		}
		else if (!strcmp(Command, "cd") && strcmp(NameOfDir, "") != 0)
		{
			PositionDir temp = current;
			current = FindDirectory(current->child, NameOfDir);

			if (current == NULL) {
				printf("\nDirectory '%s' is not found.\n", NameOfDir);
				PrintStack(head->next);
				current = temp;
			}
			else {
				PushDirectory(head, current);
				PrintStack(head->next);
			}
		}
		else if (!strcmp(Command, "dir"))
		{
			PrintDirectories(current);
			PrintStack(head->next);
		}
		else if (!strcmp(Command, "md") && strcmp(NameOfDir,"")!=0)
		{
			InsertDirectory(current, NameOfDir);
			PrintStack(head->next);
		}
		else if (!strcmp(Command, "exit"))
		{
			i = Delete(current);
		}
		else {
			printf("The command '%s' is not defined.Try again.\n", Command);
			PrintStack(head->next);
		}
	}

	return EXIT_SUCCESS;
}

PositionDir PopDirectory(PositionStack head)
{
	PositionStack temp=head;

	while (temp->next != NULL) {
		head = temp;
		temp = temp->next;
	}
	head->next = temp->next;
	free(temp);
	return head->dir;
}

int PushDirectory(PositionStack head, PositionDir element)
{
	PositionStack stack = (PositionStack)malloc(sizeof(Stack));
	stack->next = NULL;
	stack->dir = NULL;

	if (NULL == stack)
		return -1;

	stack->dir = element;

	while (head->next != NULL)
		head = head->next;

	head->next = stack;

	return EXIT_SUCCESS;
}

int Delete(PositionDir current)
{
	if (NULL == current)
		return EXIT_SUCCESS;

	Delete(current->sibling);
	Delete(current->child);
	free(current);

	return EXIT_SUCCESS;
}

PositionDir CreateDirectory(char* name)
{
	PositionDir newDir = (PositionDir)malloc(sizeof(Dir));

	if (NULL == newDir)
		return NULL;;

	newDir->child = NULL;
	newDir->sibling = NULL;
	strcpy(newDir->name, name);

	return newDir;
}

int PrintStack(PositionStack head)
{
	char directory[MAX_LENGTH] = "";

	while (head != NULL)
	{
		strcat(directory, head->dir->name);
		strcat(directory, "\\");
		head = head->next;
	}

	strcat(directory, ">");
	printf("\n%s ", directory);
	return EXIT_SUCCESS;
}

int PrintDirectories(PositionDir head)
{
	if (NULL == head->child)
	{
		printf("\tDirectory %s is empty!!\n\n", head->name);
		return -1;
	}

	printf("\tDirectory of: %s \n\n", head->name);
	head = head->child;
	while (head != NULL)
	{
		printf("\t%s\n", head->name);
		head = head->sibling;
	}

	return EXIT_SUCCESS;
}

PositionDir cd(PositionDir current, PositionStack head, char* name)
{
	PositionDir directory = current->child;

	while (directory != NULL && strcmpi(directory->name, name) != 0)
		directory = directory->sibling;

	if (NULL == directory)
	{
		printf("\nErorr!!\n");
		return current;
	}

	PushDirectory(head, current);

	return directory;
}

int InsertDirectory(PositionDir current, char* name)
{
	PositionDir el=NULL;

	if (NULL != FindDirectory(current->child, name)) {
		printf("\nA file with that name already exists!!\n");
		return 2; 
	}

	el = CreateDirectory(name);

	if (NULL == el) return 1;

	current->child = InsertRecursively(current->child, el);

	return EXIT_SUCCESS;
}

PositionDir InsertRecursively(PositionDir current, PositionDir el)
{
	if (NULL == current) return el;

	if (strcmpi(el->name, current->name) < 0)
	{
		el->sibling = current;
		return el;
	}

	current->sibling= InsertRecursively(current->sibling, el);
	return current;
}

PositionDir FindDirectory(PositionDir el, char* name)
{
	while (el != NULL)
	{
		if (strcmp(el->name, name)==0)
			return el;
		el = el->sibling;
	}
	return NULL;
}