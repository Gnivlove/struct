/*Napisati kod koji za zadane podatke studenata (matièni broj, ime i prezime) pravi
hash tablicu sa zasebnim redovima. Tablica ima 11 mjesta, a funkcija za preslikavanje
kljuè raèuna da se zbraja ASCII vrijednost prvih pet slova prezimena i zatim raèuna
ostatak cjelobrojnog dijeljenja te vrijednosti s velièinom tablice. Studenti s istim
kljuèem se pohranjuju u vezanu listu sortiranu po prezimenima i imenima.
Kada se tablica izgradi treba ispisati cijelu tablicu (naglasiti na kojem kljuèu se nalaze
koji podaci) te ponuditi moguænost da se za odreðenog studenta (prezime i ime) ispiše
njegov matièni broj.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define HASH_MAX 11
#define LENGTH 1024

struct _List;
typedef struct _List* PositionL;
typedef struct _List {
	int mat_br;
	char name[LENGTH];
	char surname[LENGTH];
	PositionL next;
}List;


int CreateKey(char * );
PositionL CreatStudent( char*, char*, int);
PositionL InSort(PositionL, PositionL);
int InHashtable(PositionL, char* , char* , int );


int main()
{
	List hash[HASH_MAX];
	int i = 0;

	for (i = 0;i < HASH_MAX;i++)
		hash[i].next = NULL;
	
	return EXIT_SUCCESS;
}

int CreateKey(char *surname) {
	int sum = 0;

	sum += tolower(*surname++);

	return sum % HASH_MAX;
}

PositionL CreatStudent( char* name, char* surname, int mat_br)
{
	PositionL Student=NULL;

	Student = (PositionL)malloc(sizeof( List));

	if (!Student)
	{
		printf("Memory allocation failed!!\n");
		return NULL;
	}

	strcpy(Student->name, name);
	strcpy(Student->surname, surname);
	Student->mat_br = mat_br;

	Student->next = NULL;

	return Student;
}

PositionL InSort(PositionL current, PositionL object) {

	if (current->next == NULL && strcmp(object->surname, current->surname) < 0 || strcmp(object->surname, current->surname) == 0 && strcmp(object->name, current->name) < 0)
		current = current->next;
	
	return current;
}

int InHashtable(PositionL head[], char* name, char* surname, int mat_br) {
	PositionL current = NULL;
	PositionL object = NULL;
	int i = 0;
	int key = 0;

	key = CreateKey(surname);

	object = CreatStudent(name, surname, mat_br);

	if (NULL == object)
		return -1;

	current = head[key]->next;

	current = InSort(current, object);

	object->next = current->next;
	current->next = object;

	return 0;
}