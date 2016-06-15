#include<stdio.h>
#include<conio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

struct DataNasterii
{
	int zi;
	char *luna;
	int an;
};

struct Student
{
	int nrMatricol;
	char *numeStudent;
	DataNasterii dataNasterii;
	char *facultate;
	int anStudii;
	int grupa;
};


struct nod_LS
{
	Student inf;
	nod_LS *next;
};


struct nod_arboreBinar
{
	Student info;
	nod_arboreBinar *left, *right;

};





void afisare_LS(nod_LS *cap)
{
	nod_LS *aux = cap;
	
	while (aux)
	{
		printf("\nNrMatricol=%d NumeStudent=%s DataNasterii=%d.%s.%d Facultate=%s AnStudii=%d Grupa=%d", aux->inf.nrMatricol, aux->inf.numeStudent, aux->inf.dataNasterii.zi, aux->inf.dataNasterii.luna, aux->inf.dataNasterii.an, aux->inf.facultate, aux->inf.anStudii, aux->inf.grupa);
		aux = aux->next;
	}
}

nod_LS* inserareNodInLista(nod_LS *cap, Student s)
{
	nod_LS *nou = (nod_LS*)malloc(sizeof(nod_LS));
	nou->inf.nrMatricol = s.nrMatricol;
	nou->inf.numeStudent = (char*)malloc((strlen(s.numeStudent) + 1)*sizeof(char));
	strcpy(nou->inf.numeStudent, s.numeStudent);
	nou->inf.dataNasterii = s.dataNasterii;
	nou->inf.facultate = (char*)malloc((strlen(s.facultate) + 1)*sizeof(char));
	strcpy(nou->inf.facultate, s.facultate);
	nou->inf.anStudii = s.anStudii;
	nou->inf.grupa = s.grupa;
	nou->next = NULL;
	if (cap == NULL)
	{
		cap = nou;
		return cap;
	}
	else
	{
		nod_LS *aux = cap;
		for (aux = cap; aux->next; aux = aux->next);
		aux->next = nou;

	}
	return cap;
}


void cautaStudent(nod_LS *cap, char zodie[25])
{
	FILE *f = fopen("cautaStudent.txt", "w");

	nod_LS *aux = cap;
	if (f)
	{

		while (aux)
		{

			if ((strcmp(zodie,"berbec")==0) && ((aux->inf.dataNasterii.zi >= 20 && strcmp(aux->inf.dataNasterii.luna,"03")==0) || (aux->inf.dataNasterii.zi < 21 && strcmp(aux->inf.dataNasterii.luna,"04")==0)))
				fprintf(f, "%s", aux->inf.numeStudent);
			else if ((strcmp(zodie, "taur") == 0) && ((aux->inf.dataNasterii.zi > 21 && strcmp(aux->inf.dataNasterii.luna,"04")==0) || (aux->inf.dataNasterii.zi <=20 && strcmp(aux->inf.dataNasterii.luna,"05")==0)))
				fprintf(f, "%s", aux->inf.numeStudent);
			else if	((strcmp(zodie, "gemeni") == 0) && ((aux->inf.dataNasterii.zi >= 21 && strcmp(aux->inf.dataNasterii.luna,"05")==0) || (aux->inf.dataNasterii.zi < 21 && strcmp(aux->inf.dataNasterii.luna,"06")==0)))
				fprintf(f, "%s", aux->inf.numeStudent);
			else if ((strcmp(zodie, "rac") == 0) && ((aux->inf.dataNasterii.zi >= 22 && strcmp(aux->inf.dataNasterii.luna,"06")==0) || (aux->inf.dataNasterii.zi < 22 && strcmp(aux->inf.dataNasterii.luna,"07")==0)))
				fprintf(f, "%s", aux->inf.numeStudent);
			else if ((strcmp(zodie, "leu") == 0) && ((aux->inf.dataNasterii.zi >= 23 && strcmp(aux->inf.dataNasterii.luna,"07")==0) || (aux->inf.dataNasterii.zi <= 22 && strcmp(aux->inf.dataNasterii.luna,"08")==0)))
				fprintf(f, "%s", aux->inf.numeStudent);
			else if ((strcmp(zodie, "fecioara") == 0) && ((aux->inf.dataNasterii.zi >= 23 && strcmp(aux->inf.dataNasterii.luna,"08")==0) || (aux->inf.dataNasterii.zi < 22 && strcmp(aux->inf.dataNasterii.luna,"09")==0)))
				fprintf(f, "%s", aux->inf.numeStudent);
			else if ((strcmp(zodie, "balanta") == 0) && ((aux->inf.dataNasterii.zi >= 23 && strcmp(aux->inf.dataNasterii.luna,"09")==0) || (aux->inf.dataNasterii.zi < 22 && strcmp(aux->inf.dataNasterii.luna,"10")==0)))
				fprintf(f, "%s", aux->inf.numeStudent);
			else if ((strcmp(zodie, "scorpion") == 0) && ((aux->inf.dataNasterii.zi >= 23 && strcmp(aux->inf.dataNasterii.luna,"10")==0) || (aux->inf.dataNasterii.zi < 21 && strcmp(aux->inf.dataNasterii.luna,"11")==0)))
				fprintf(f, "%s", aux->inf.numeStudent);
			else if ((strcmp(zodie, "sagetator") == 0) && ((aux->inf.dataNasterii.zi >= 22 && strcmp(aux->inf.dataNasterii.luna,"11")==0) || (aux->inf.dataNasterii.zi < 20 && strcmp(aux->inf.dataNasterii.luna,"12")==0)))
				fprintf(f, "%s", aux->inf.numeStudent);
			else if ((strcmp(zodie, "capricorn") == 0) && ((aux->inf.dataNasterii.zi >= 21 && strcmp(aux->inf.dataNasterii.luna,"12")==0) || (aux->inf.dataNasterii.zi < 19 && strcmp(aux->inf.dataNasterii.luna,"01")==0)))
				fprintf(f, "%s", aux->inf.numeStudent);
			else if ((strcmp(zodie, "varsator") == 0) && ((aux->inf.dataNasterii.zi >= 20 && strcmp(aux->inf.dataNasterii.luna,"01")==0) || (aux->inf.dataNasterii.zi < 18 && strcmp(aux->inf.dataNasterii.luna,"02")==0)))
				fprintf(f, "%s", aux->inf.numeStudent);
			else if (strcmp(zodie, "pesti") == 0)
				fprintf(f, "%s", aux->inf.numeStudent);

			aux = aux->next;
		}
		fclose(f);
	}
}


nod_LS* stergeStudent(nod_LS *cap, char nume[25])
{
	nod_LS *aux = cap;

	Student s;
	
	if (aux)
	{
		if (strcmp(cap->inf.numeStudent, nume) == 0)
		{
			nod_LS *aux = cap;
			cap = aux->next;
				delete aux;
				aux = NULL;
			return cap;
		}
		else
		{
			nod_LS *t = cap;
			while (t->next != NULL && strcmp(t->next->inf.numeStudent, nume) != 0)
				t = t->next;
			if (t->next == NULL)
				printf("\nStudentul nu a fost gasit");
			else
			{
				nod_LS *p = t->next;
				if (p->next == NULL)
				{
					t->next = NULL;
					delete p;
				}
				else
				{
					t->next = p->next;
					delete p;
				}

			}						
		}				
	}
	
	return cap;
}

nod_arboreBinar* creareNodArbore(Student stud, nod_arboreBinar *l, nod_arboreBinar *r)
{
	nod_arboreBinar *temp;
	temp = (nod_arboreBinar*)malloc(sizeof(nod_arboreBinar));
	temp->info.nrMatricol = stud.nrMatricol;
	temp->info.numeStudent = (char*)malloc((strlen(stud.numeStudent) + 1)*sizeof(char));
	strcpy(temp->info.numeStudent, stud.numeStudent);
	temp->info.dataNasterii.zi = stud.dataNasterii.zi;
	temp->info.dataNasterii.luna = (char*)malloc((strlen(stud.dataNasterii.luna) + 1)*sizeof(char));
	strcpy(temp->info.dataNasterii.luna, stud.dataNasterii.luna);
	temp->info.dataNasterii.an = stud.dataNasterii.an;
	temp->info.facultate = (char*)malloc((strlen(stud.facultate) + 1)*sizeof(char));
	strcpy(temp->info.facultate, stud.facultate);
	temp->info.anStudii = stud.anStudii;
	temp->info.grupa = stud.grupa;

	temp->left = l;
	temp->right = r;

	return temp;
}




nod_arboreBinar* inserareNodInArbore(nod_arboreBinar *root, Student s)
{

	nod_arboreBinar *aux;
	aux = root;


	if (!root)
	{
		aux = creareNodArbore(s, NULL, NULL);
		return aux;
	}
	else
	{
		while (1){

			
			if (s.nrMatricol > aux->info.nrMatricol)
			{
				if (aux->right)  //daca mai exista ceva in dreapta
					aux = aux->right;
				else
				{
					//daca nu mai e nimic in drepata
					aux->right = creareNodArbore(s, NULL, NULL);
					return root;
				}
			}
			else
			{
				if (s.nrMatricol < aux->info.nrMatricol)
				{
					if (aux->left)
						aux = aux->left;
					else
					{
						aux->left = creareNodArbore(s, NULL, NULL);
						return root;

					}
				}
				else
				{
					printf("Nod existent");
					return root;
				}
			}
		}
	}

}
		



//parcurgere preordine arbore
void parcurgereRootLeftRight(nod_arboreBinar *root)
{
	if (root != NULL)
	{
		printf("\nNrMatricol=%d NumeStudent=%s DataNasterii=%d.%s.%d Facultate=%s AnStudii=%d Grupa=%d ", root->info.nrMatricol, root->info.numeStudent, root->info.dataNasterii.zi, root->info.dataNasterii.luna, root->info.dataNasterii.an, root->info.facultate, root->info.anStudii, root->info.grupa);
		parcurgereRootLeftRight(root->left);
		parcurgereRootLeftRight(root->right);
	}
}


void main()
{
	nod_LS *cap = NULL;
	Student s;


	nod_arboreBinar *root = NULL;
	
	FILE *f = fopen("preluareDate.txt", "r");
	
	char *token[100], linie[120], sep_list[] = ",";
	while (fgets(linie, sizeof(linie), f))
	{
		token[0] = strtok(linie, sep_list);
		for (int i = 1; i < 6; i++)
		{
			token[i] = strtok(NULL, sep_list);
		}

		s.nrMatricol = atoi(token[0]);

		s.numeStudent = (char*)malloc((strlen(token[1]) + 1)*sizeof(char));
		strcpy(s.numeStudent, token[1]);

		s.dataNasterii.zi = atoi(strtok(token[2], "."));

		char *luna;
		luna = strtok(NULL, ".");
		s.dataNasterii.luna = (char*)malloc((strlen(luna) + 1)*sizeof(char));
		strcpy(s.dataNasterii.luna, luna);
		s.dataNasterii.an = atoi(strtok(NULL, "\n"));

		s.facultate = (char*)malloc((strlen(token[3]) + 1)*sizeof(char));
		strcpy(s.facultate, token[3]);

		s.anStudii = atoi(token[4]);

		s.grupa = atoi(token[5]);
		cap = inserareNodInLista(cap, s);

	}
	afisare_LS(cap);
	

	printf("\nCautare student dupa o zodie specificata: ");
	char buffer[25],zodie[25];
	printf("\nZodie=");
	scanf("%s", buffer);
	strcpy(zodie, buffer);
	cautaStudent(cap, zodie);

	char numeStudent[256];
	fseek(stdin, 0, SEEK_END);
	fflush(stdin);
	printf("\nSterge student dupa un nume specificat: ");

	gets_s(numeStudent);


	
	cap=stergeStudent(cap, numeStudent);

	afisare_LS(cap);

	printf("\nConversie lista-arbore ");
	nod_LS *aux = cap;

	//?? trecerea listei in ABC
	while (aux)
	{
		root = inserareNodInArbore(root, aux->inf);
		aux = aux->next;
	}
	printf("\nAfisare arbore: ");
	parcurgereRootLeftRight(root);

	_getch();
}