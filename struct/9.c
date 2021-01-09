/*. Napisati program koji omoguæava rad s binarnim stablom pretraživanja. Treba
omoguæiti unošenje novog elementa u stablo, ispis elemenata, brisanje i pronalaženje
nekog elementa*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Tree;
typedef struct Tree* Position;
typedef struct Tree {
	int element;
	Position LeftChild;
	Position RightChild;
}BinaryTree;

Position InsertElement(Position, int);
Position FindElement(Position, int);
Position DeleteElement(Position, int);
Position FindMin(Position);
Position DeleteAll(Position);
void PrintTree(Position);
void Menu(Position);

int main()
{
	Position root = NULL;
	Menu(root);

	return EXIT_SUCCESS;
}

Position InsertElement(Position current, int number)
{
	if (NULL == current)
	{
		current = (Position)malloc(sizeof(BinaryTree));
		current->LeftChild = NULL;
		current->RightChild = NULL;
		current->element = number;
	}
	else if (number > current->element)
		current->RightChild = InsertElement(current->RightChild, number);
	else if(number < current->element)
		current->LeftChild = InsertElement(current->LeftChild, number);
	else if (number == current->element)
	{
		printf("\n\tThis element already exists!!\n");
		return current;
	}

	return current;
}

Position FindElement(Position current, int number)
{
	if (NULL == current)
	{
		printf("\n\tThis element does not exist!!\n");
		return NULL;
	}
	else if (number > current->element)
		return FindElement(current->RightChild, number);
	else if (number < current->element)
		return FindElement(current->LeftChild, number);

	return current;
}

Position FindMin(Position current)
{
	while (current->LeftChild != NULL)
		current = current->LeftChild;

	return current;
}

Position DeleteElement(Position current, int number)
{
	Position temp = NULL;

	if (NULL == current)
		printf("\n\tThis element does not exist!!\n");
	else if (number > current->element)
		current->RightChild = DeleteElement(current->RightChild, number);
	else if (number < current->element)
		current->LeftChild = DeleteElement(current->LeftChild, number);
	else 
	{
		if (current->LeftChild && current->RightChild)
		{
			temp = FindMin(current->RightChild);
			current->element = temp->element;
			current->RightChild = DeleteElement(current->RightChild, current->element);
		}
		else
		{
			temp = current;

			if (NULL == current->RightChild)
				current = current->LeftChild;
			else if (NULL == current->LeftChild)
				current = current->RightChild;

			free(temp);
		}
	}
	return current;
}

Position DeleteAll(Position current)
{
	if (current != NULL)
	{
		DeleteAll(current->LeftChild);
		DeleteAll(current->RightChild);
		free(current);
	}
	return NULL;
}

void PrintTree(Position current)
{
	if (current != NULL)
	{
		PrintTree(current->LeftChild);
		printf("%d ", current->element);
		PrintTree(current->RightChild);
	}
}

void Menu(Position current)
{
	Position temp=NULL;
	int option, number;
		
	while (1)
	{
		system("cls");
		printf("\n\tChoose:\n");
		printf("\n\t\t 0->exit ");
		printf("\n\t\t 1->insert new element ");
		printf("\n\t\t 2->find element ");
		printf("\n\t\t 3->delete element ");
		printf("\n\t\t 4->print\n\t--> ");
		scanf(" %d", &option);

		switch (option) {
		case 0:
			DeleteAll(current);
			return EXIT_SUCCESS;
			break;
		case 1:
			printf("\nEnter number to insert: ");
			scanf(" %d", &number);
			current = InsertElement(current, number);
			puts("");
			PrintTree(current);
			puts("");
			system("pause");
			break;
		case 2:
			printf("\nEnter number to find: ");
			scanf(" %d", &number);
			temp = FindElement(current,number);
			if (temp != NULL)
				printf("\nThe element %d is located at %d\n", temp->element, temp);
			puts("");
			system("pause");
			break;
		case 3:
			printf("\nEnter number to delete: ");
			scanf(" %d", &number);

			current = DeleteElement(current, number);
			puts("");
			PrintTree(current);
			puts("");
			system("pause");
			break;
		case 4:
			printf("Current Tree in order: \n");
			PrintTree(current);
			if (current == NULL)
				printf("Binary tree is empty!");
			puts("");
			system("pause");
			break;
		default:
			puts("Choose only numbers from 0-4!\n");
			break;
		}
	}
}