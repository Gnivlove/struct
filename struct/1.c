/*Napisati program koji prvo proèita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i uèitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime,apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
	char ime[50];
	char prezime[50];
	int bodovi;

}studenti;

int BroRed(char* FileName)
{
	FILE* File;
	char *baf=malloc(1024*sizeof(char));
	int br = 0;
	File = fopen(FileName, "r");

	if (File == NULL)
	{
		printf("Greska pri otvaranju datoteka!\n");
		return 1;
	}

	while (1)
	{
		if (fgets(baf, 100, File) == NULL)
			break;
		br++;
	}

	free(baf);
	fclose(File);
	return br;
}

int ispis(char* FileName, int brojStud)
{
	int i, maxbr;
	double *reBr,temp;
	studenti* stud ;
	FILE* File;
	File = fopen(FileName, "r");

	if (File == NULL)
	{
		puts("Greska u otvaranju datoteke!\n");
		return 1;
	}

	printf("Unesite ukupni brod bodova na kolokviju:");
	scanf("%d",&maxbr);

	stud = (studenti*)malloc(brojStud * sizeof(studenti));
	reBr = (double*)malloc(brojStud * sizeof(double));

	printf("\nIme\tPrezime\t\tAps.br.bodova\t\tRel.br.bodova\n");
	for (i = 0; i < brojStud; i++)
	{
		fscanf(File, "%s %s %d", stud[i].ime, stud[i].prezime, &stud[i].bodovi);
		temp = (double)stud[i].bodovi / maxbr;
		*(reBr+i) = temp*100;
		printf("%s\t%s\t\t%d\t\t\t%.2f\n", stud[i].ime, stud[i].prezime, stud[i].bodovi, *(reBr+i));
	}

	fclose(File);

	return 0;
}


int main()
{
	int brojr;
	char* ime[20];
	printf("Unesite ime dokumenta iz kojeg zelite citat podatke: ");
	scanf("%s",ime );

	brojr = BroRed(ime);

	ispis(ime, brojr);

	return 0;
}