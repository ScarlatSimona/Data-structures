#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<dirent.h>
using namespace std;
#include<string>
#include <time.h>

#include <sstream>
#include <windows.h>
#include <sys/stat.h>
/*struct DateAccessed
{
	int day;
	char *month;
	int year;
};
*/


//director sau fisier
struct File
{
	int id;
	char *path;
	char *fileName;
	char* size;
	char *extension;
	//DateAccessed *dateAccesed;
	bool isDirectory;

	

	//FileList *fileList;

};

/*
struct FileList
{
	File *inf;
	FileList *next;
};
*/

struct NodLista
{
	File *inf;
	NodLista *next;
};




struct NodHashTable
{
	File info;

	NodHashTable *next;

};

struct HashTable
{
	NodHashTable **elem;
	int size;
};



struct NodArbore
{
	File informatie;
	NodArbore *left, *right;
};

void log(char* comanda, char mesaj[20])
{
	FILE* file = fopen(".\\log.txt", "a");
	
	time_t rawtime;
	tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	fprintf(file, "\n%s  %s  \n%s", asctime(timeinfo), comanda,mesaj);
	fclose(file);
}

NodArbore* creareNodArbore(File file, NodArbore *l, NodArbore *r)
{
	NodArbore *temp;
	temp = (NodArbore*)malloc(sizeof(NodArbore));
	temp->informatie.fileName = (char*)malloc((strlen(file.fileName) + 1)*sizeof(char));
	strcpy(temp->informatie.fileName, file.fileName);

	temp->informatie.id = file.id;
	temp->informatie.extension = (char*)malloc((strlen(file.extension) + 1)*sizeof(char));
	strcpy(temp->informatie.extension, file.extension);

	temp->informatie.isDirectory = file.isDirectory;
	temp->informatie.path = (char*)malloc((strlen(file.path) + 1)*sizeof(char));
	strcpy(temp->informatie.path, file.path);

	temp->informatie.size = (char*)malloc((strlen(file.size) + 1)*sizeof(char));
	strcpy(temp->informatie.size, file.size);
	temp->left = l;
	temp->right = r;
	return temp;
}


NodArbore* inserareNodInArbore(File f,NodArbore *root)
{
	NodArbore *aux;
	aux = root;

	if (!root)
	{
		aux = creareNodArbore(f, NULL, NULL);
		return aux;
	}
	else
	{
		while (1)
		{
			if (f.id > aux->informatie.id)
			{
				if (aux->right) aux = aux->right;
				else
				{
					aux->right = creareNodArbore(f, NULL, NULL);
					return root;
				}
			}
			else
			{
				if (f.id < aux->informatie.id)
				{
					if (aux->left) aux = aux->left;
					else
					{
						aux->left = creareNodArbore(f, NULL, NULL);
						return root;
					}
				}
				else
				{
					return root;
				}
			}
		}
	}
}



NodLista* InsertInList(NodLista *cap, File *file)
{

	NodLista *newNode = (NodLista*)malloc(sizeof(NodLista));
	newNode->inf = file;
	/*
	newNode->inf->fileName = (char*)malloc((strlen(file->fileName) + 1)*sizeof(char));
	strcpy(newNode->inf->fileName, file->fileName);
	
	newNode->inf->path = (char*)malloc((strlen(file->path) + 1)*sizeof(char));
	strcpy(newNode->inf->path, file->path);

	newNode->inf->extension= (char*)malloc((strlen(file->extension) + 1)*sizeof(char));
	strcpy(newNode->inf->extension, file->extension);

	newNode->inf->size = file->size;
	/*
	newNode->inf->dateAccesed->day = file->dateAccesed->day;
	newNode->inf->dateAccesed->month = (char*)malloc((strlen(file->dateAccesed->month) + 1)*sizeof(char));
	strcpy(newNode->inf->dateAccesed->month, file->dateAccesed->month);
	
	//newNode->inf->dateAccesed->year = file->dateAccesed->year;
	*/
	newNode->next = NULL;
	
	if (cap == NULL)
	{
		cap = newNode;
	}
	else
	{
		NodLista *p;
		for (p = cap; p->next; p = p->next);
		p->next = newNode;
		
	}

	return cap;
}

void afisareListaSimpla(NodLista *cap)
{
	NodLista *p = cap;
	while (p)
	{
		printf("\n%s ", p->inf->fileName);
		p = p->next;
	}
}

NodLista* conversieHashLista(NodLista *cap, HashTable hs)
{
	if (hs.elem != NULL)
	{
		for (int i = 0; i<hs.size; i++)
		{
			if (hs.elem[i] != NULL)
			{
				NodHashTable *t = hs.elem[i];
				while (t != NULL)
				{
					File *f = (File*)malloc(sizeof(File));
					f->fileName = (char*)malloc((strlen(t->info.fileName) + 1)*sizeof(char));
					strcpy(f->fileName, t->info.fileName);
					f->extension=(char*)malloc((strlen(t->info.extension) + 1)*sizeof(char));
					strcpy(f->extension, t->info.extension);

					f->path= (char*)malloc((strlen(t->info.path) + 1)*sizeof(char));
					strcpy(f->path, t->info.path);

					f->size = (char*)malloc((strlen(t->info.size) + 1)*sizeof(char));
					strcpy(f->size, t->info.size);

					f->id = t->info.id;
					cap = InsertInList(cap, f);
					t = t->next;
				}
			}
		}
	}
	return cap;
}





int HashFunction(char *cheie, HashTable hs)
{
	return (cheie[0] + cheie[strlen(cheie)]) % hs.size;
}

HashTable MemoryAllocation()
{
	HashTable hs;
	hs.size = 201;
	hs.elem = new NodHashTable*[hs.size];
	for (int i = 0; i < hs.size; i++)
	{
		hs.elem[i] = NULL;
	}
	return hs;
}






int inserareInHashTable(HashTable hs, File file)
{
	
	int index = -1;

	if (file.fileName == "")
		return index;
	if (hs.elem != NULL)
	{
	     index = HashFunction(file.fileName, hs);
		 NodHashTable *newNode = new NodHashTable;
		 newNode->next = NULL;
		 newNode->info = file;

		 if (hs.elem[index] == NULL)
		 {
			 hs.elem[index] = newNode;
		 }
		 else
		 {
			 NodHashTable *t = hs.elem[index];
			 while (t->next != NULL)
				 t = t->next;
			 t->next = newNode;
		 }

	}
	return index;

	
}



struct nod_coada
{
	char* comanda;
	nod_coada *next;
};

void inserareComandaInCoada(nod_coada **p, nod_coada **u, char* comanda)
{
	nod_coada *temp = (nod_coada*)malloc(sizeof(nod_coada));
	temp->comanda = comanda;
	temp->next = NULL;
	if (*p == NULL && *u == NULL)
	{
		*p = temp;
		*u = temp;
	}
	else
	{
		(*u)->next = temp;
		*u = temp;
	}
}


char* scoateNodDinCoada(nod_coada **p, nod_coada **u, char *valoare)
{
	if (*p == NULL)
	{
		*u = NULL;
		return NULL;
	}
	else if (*p != NULL)
	{
		nod_coada *temp = *p;
		valoare=(char*)malloc((strlen(temp->comanda)+1)*sizeof(char));
		strcpy(valoare, temp->comanda);
		*p = (*p)->next;
		//delete temp;
		return valoare;
	}
}

wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

CHAR wide_to_narrow(WCHAR w)
{
	// simple typecast
	// works because UNICODE incorporates ASCII into itself
	return CHAR(w);
}

void Afiseaza(HashTable hs)
{
	if (hs.elem != NULL)
	{
		for (int i = 0; i<hs.size; i++)
		{
			if (hs.elem[i] != NULL)
			{
				NodHashTable *t = hs.elem[i];
				while (t != NULL)
				{
					printf("\nS-a inserat in pozitia: %d fisierul %s size %s", i, t->info.fileName, t->info.size);
					t = t->next;
				}
			}
		}
	}
}


size_t getFilesize(const char* filename) {
	struct stat st;
	if (stat(filename, &st) != 0) {
		return 0;
	}
	return st.st_size;
}

string convertToString(double num) {
	ostringstream convert;
	convert << num;
	return convert.str();
}

double roundOff(double n) {
	double d = n * 100.0;
	int i = d + 0.5;
	d = (float)i / 100.0;
	return d;
}

string convertSize(size_t size) {
	static const char *SIZES[] = { "B", "KB", "MB", "GB" };
	int div = 0;
	size_t rem = 0;

	while (size >= 1024 && div < (sizeof SIZES / sizeof *SIZES)) {
		rem = (size % 1024);
		div++;
		size /= 1024;
	}

	double size_d = (float)size + (float)rem / 1024.0;
	string result = convertToString(roundOff(size_d)) + " " + SIZES[div];
	return result;
}

int file_size(const char *path) {
	struct stat results;

	if (stat(path, &results) == 0) {
		return results.st_size;
	}
	else {
		return -1;
	}
}

// This is the function that you will call:
string getFileSize(string path) {
	size_t size = file_size((const char *)path.c_str());
	return convertSize(size);
}




void dezalocareHashTable(HashTable hs)
{
	if (hs.elem != NULL)
	{
		for (int i = 0; i<hs.size; i++)
		if (hs.elem[i] != NULL)
		{
			NodHashTable *temp = hs.elem[i];
			NodHashTable *temp2;
			while (temp != NULL)
			{
				temp2 = temp->next;
				free(temp->info.extension);
				free(temp->info.fileName);
				free(temp->info.path);
				//free(temp->info.size);
				free(temp);
				temp = temp2;
			}
		}
		free(hs.elem);
	}
	printf("\nHashTable dezalocat");
}



bool list(HashTable hs, const wchar_t *sDir)
{
	WIN32_FIND_DATA fdFile;
	DWORD dwFileSize;
	HANDLE hFind = NULL;
	HANDLE hFind1 = NULL;

	wchar_t sPath[2048];

	wsprintf(sPath, L"%s\\*.*", sDir);

	if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Path not found: [%s]\n", sDir);
		return false;
	}

	

	do
	{
		
		if (wcscmp(fdFile.cFileName, L".") != 0
			&& wcscmp(fdFile.cFileName, L"..") != 0)
		{
			 
			wsprintf(sPath, L"%s\\%s", sDir, fdFile.cFileName);


			//director
			File f;
			char buffer[500];

		
			wcstombs(buffer, fdFile.cFileName, 500);

		
			//Is the entity a File or Folder? 
			if (fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
			{
				//wprintf(L"Directory: %s\n", sPath);
				f.fileName = (char*)malloc((strlen(buffer) + 1)*sizeof(char));
				strcpy(f.fileName, buffer);

				wcstombs(buffer, sDir, 500);
				f.path = (char*)malloc((strlen(buffer) + 1)*sizeof(char));
				strcpy(f.path, buffer);
				f.extension = (char*)malloc(sizeof(char)* 3);
				f.extension = strcpy(f.extension, "");
				f.size = "";
				f.isDirectory = true;

				inserareInHashTable(hs, f);


				list(hs, sPath); 
			}
			else
			{
				

				f.fileName = (char*)malloc((strlen(buffer) + 1)*sizeof(char));
				strcpy(f.fileName, buffer);

				wcstombs(buffer, sDir, 500);
				f.path = (char*)malloc((strlen(buffer) + 1)*sizeof(char));
				strcpy(f.path, buffer);
				f.extension = (char*)malloc(sizeof(char)* 3);
				strcpy(f.extension, "");
				

				char *cale=new char[100];
				strcpy(cale, f.path);

				strcat(cale, "\\");
				strcat(cale, f.fileName);
				string t = getFileSize(cale);
				
				f.size = (char*)malloc((strlen(t.c_str()) + 1)*sizeof(char));
				strcpy(f.size, t.c_str());


				
				
				f.isDirectory = false;
				//wprintf(L"File: %s\n", sPath);
				inserareInHashTable(hs, f);
				
			
				
			}
		}
	} while (FindNextFile(hFind, &fdFile)); 

	FindClose(hFind); 
	Afiseaza(hs);

	//dezalocareHashTable(hs);
	return true;
}

void dezalocareListaSimpla(NodLista *cap)
{
	NodLista *p = cap,*q;
	
	while (p)
	{
		q = p->next;
		free(p->inf->extension);
		free(p->inf->fileName);
		free(p->inf->path);
		free(p->inf->size);
		free(p);
		p = q;
		
	}
	printf("\nListaDezalocata");

}
bool parsareComandaList(nod_coada *prim,nod_coada *ultim)
{
	bool rezultatExecutie = false;
	HashTable hs;
	hs=MemoryAllocation();
	char *path = NULL;
	NodLista *cap = NULL;
		path=scoateNodDinCoada(&prim, &ultim, path);
	if (path != NULL)
	{
		
		rezultatExecutie = list(hs, convertCharArrayToLPCWSTR(path));
		
		cap=conversieHashLista(cap, hs);
		afisareListaSimpla(cap);
		dezalocareListaSimpla(cap);
		dezalocareHashTable(hs);
	}
	else
	{
		rezultatExecutie = list(hs, convertCharArrayToLPCWSTR("."));
		cap = conversieHashLista(cap, hs);
		afisareListaSimpla(cap);
		dezalocareListaSimpla(cap);
		dezalocareHashTable(hs);
	}

	
	return rezultatExecutie;
}
int random()
{
	int r, a, b;
	for (a = 0; a < 20; a++)
	{
		for (b = 0; b < 5; b++)
		{
			r = rand();
			return r;
		}
	}
}

NodArbore* inserareFisierInArbore(NodArbore *root, const wchar_t *sDir)
{
	WIN32_FIND_DATA fdFile;
	DWORD dwFileSize;
	HANDLE hFind = NULL;
	HANDLE hFind1 = NULL;

	wchar_t sPath[2048];

	wsprintf(sPath, L"%s\\*.*", sDir);

	if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Path not found: [%s]\n", sDir);
		//return false;
	}

	do
	{

		if (wcscmp(fdFile.cFileName, L".") != 0
			&& wcscmp(fdFile.cFileName, L"..") != 0)
		{

			wsprintf(sPath, L"%s\\%s", sDir, fdFile.cFileName);


			//director
			File f;
			char buffer[500];


			wcstombs(buffer, fdFile.cFileName, 500);


			//Is the entity a File or Folder? 
			if (fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
			{
				//wprintf(L"Directory: %s\n", sPath);
				f.id = random();
				f.fileName = (char*)malloc((strlen(buffer) + 1)*sizeof(char));
				strcpy(f.fileName, buffer);

				wcstombs(buffer, sDir, 500);
				f.path = (char*)malloc((strlen(buffer) + 1)*sizeof(char));
				strcpy(f.path, buffer);
				f.extension = (char*)malloc(sizeof(char)* 3);
				f.extension = strcpy(f.extension, "");
				f.size = "";
				f.isDirectory = true;

				root = inserareNodInArbore(f, root);

				root=inserareFisierInArbore(root, sPath);
			}
			else
			{

				f.id = random();
				f.fileName = (char*)malloc((strlen(buffer) + 1)*sizeof(char));
				strcpy(f.fileName, buffer);

				wcstombs(buffer, sDir, 500);
				f.path = (char*)malloc((strlen(buffer) + 1)*sizeof(char));
				strcpy(f.path, buffer);
				f.extension = (char*)malloc(sizeof(char)* 3);
				strcpy(f.extension, "");


				char *cale = new char[100];
				strcpy(cale, f.path);

				strcat(cale, "\\");
				strcat(cale, f.fileName);
				string t = getFileSize(cale);

				f.size = (char*)malloc((strlen(t.c_str()) + 1)*sizeof(char));
				strcpy(f.size, t.c_str());
				



				f.isDirectory = false;
				//wprintf(L"File: %s\n", sPath);
				root = inserareNodInArbore(f, root);


			}
		}
	} while (FindNextFile(hFind, &fdFile));

	FindClose(hFind);
	
	return root;
}



NodArbore* StergeNodDinArbore(NodArbore *root, char *parametru)
{
	if (strcmp(parametru, "-f") == 0)
	{
		// arbore vid
		if (root == NULL) return root;
		// stergere radacina
		if (root->informatie.isDirectory == true)
		{
			
			NodArbore * nod = root;
			// daca avem un subarbore drept
			if (nod->right)
			{
				
				root = nod->right;
				// daca avem si un subarbore stang
				if (nod->left)
				{
					// cautam cel mai mic element din subarborele drept
					NodArbore * temp = nod->right;
					while (temp->left != NULL) temp = temp->left;
					// si adaugam subarborele stang
					temp->left = nod->left;
					//return root;
				}
			}
			else
				// daca avem doar un subarbore stang
			if (nod->left != NULL)
				// facem legatura la acesta
				root = nod->left;
			else
				// daca nu avem nici un subarbore
				root = NULL;
			// stergem vechea radacina
			//delete nod;
			//return root;
		}
		// Cazul 3: stergere nod in arbore nevid
		NodArbore * nodCurent = root;
		while (true && nodCurent!=NULL)
		{
			if (nodCurent->left!=NULL)
			{

				if (nodCurent->left->informatie.isDirectory == true)
					// nodul de sters este descendentul stang
					root=StergeNodDinArbore(nodCurent->left, parametru);
				else
					// continuam cautarea in subarborele stang
					nodCurent = nodCurent->left;
			}
			else if (nodCurent->right!=NULL)
			{
				if (nodCurent->right->informatie.isDirectory == true)
					// nodul de sters este descendentul drept
					root=StergeNodDinArbore(nodCurent->right,parametru);
				else
					// continuam cautarea in subarborele stang
					nodCurent = nodCurent->right;
			}
			
			
		}
		return root;
	}
	else if (strcmp(parametru, "-d")==0)
	{
		// arbore vid
		if (root == NULL) return root;
		// stergere radacina
		if (root->informatie.isDirectory == false)
		{

			NodArbore * nod = root;
			// daca avem un subarbore drept
			if (nod->right)
			{

				root = nod->right;
				// daca avem si un subarbore stang
				if (nod->left)
				{
					// cautam cel mai mic element din subarborele drept
					NodArbore * temp = nod->right;
					while (temp->left != NULL) temp = temp->left;
					// si adaugam subarborele stang
					temp->left = nod->left;
				}
			}
			else
				// daca avem doar un subarbore stang
			if (nod->left != NULL)
				// facem legatura la acesta
				root = nod->left;
			else
				// daca nu avem nici un subarbore
				root = NULL;
			// stergem vechea radacina
			delete nod;
			
		}
		// Cazul 3: stergere nod in arbore nevid
		NodArbore * nodCurent = root;
		while (true)
		{
			if (nodCurent->left)
			{

				if (nodCurent->left->informatie.isDirectory == false)
					// nodul de sters este descendentul stang
					StergeNodDinArbore(nodCurent->left, parametru);
				else
					// continuam cautarea in subarborele stang
					nodCurent = nodCurent->left;
			}
			else if (nodCurent->right)
			{
				if (nodCurent->right->informatie.isDirectory == false)
					// nodul de sters este descendentul drept
					StergeNodDinArbore(nodCurent->right, parametru);
				else
					// continuam cautarea in subarborele stang
					nodCurent = nodCurent->right;
			}


		}
	}
	else
	{
		// arbore vid
		if (root == NULL) 
		// stergere radacina
		if (root->informatie.isDirectory == true)
		{

			NodArbore * nod = root;
			// daca avem un subarbore drept
			if (nod->right)
			{

				root = nod->right;
				// daca avem si un subarbore stang
				if (nod->left)
				{
					// cautam cel mai mic element din subarborele drept
					NodArbore * temp = nod->right;
					while (temp->left != NULL) temp = temp->left;
					// si adaugam subarborele stang
					temp->left = nod->left;
				}
			}
			else
				// daca avem doar un subarbore stang
			if (nod->left != NULL)
				// facem legatura la acesta
				root = nod->left;
			else
				// daca nu avem nici un subarbore
				root = NULL;
			// stergem vechea radacina
			delete nod;
			
		}
		// Cazul 3: stergere nod in arbore nevid
		NodArbore * nodCurent = root;
		while (true)
		{
			if (nodCurent->left)
			{

				if (strcmp(nodCurent->left->informatie.size, parametru) != 0)
					// nodul de sters este descendentul stang
					StergeNodDinArbore(nodCurent->left, parametru);
				else
					// continuam cautarea in subarborele stang
					nodCurent = nodCurent->left;
			}
			else if (nodCurent->right)
			{
				if (strcmp(nodCurent->left->informatie.size, parametru) != 0)
					// nodul de sters este descendentul drept
					StergeNodDinArbore(nodCurent->right, parametru);
				else
					// continuam cautarea in subarborele stang
					nodCurent = nodCurent->right;
			}


		}
	}
}


NodArbore* stergeRad(NodArbore* rad)
{
	NodArbore* aux = rad;
	if (aux->left != NULL)
	{
		rad = aux->left;
		if (aux->right != NULL)
		{
			NodArbore* temp = aux->left;
			while (temp->right != NULL)
				temp = temp->right;
			temp->right = aux->right;
		}
	}
	else
	if (aux->right != NULL)
		rad = aux->right;
	else
		rad = NULL;
	
	
	/*
	free(aux->informatie.fileName);
	free(aux->informatie.extension);
	free(aux->informatie.path);
	free(aux->informatie.size);
	free(aux);
	*/
	delete aux;
	
	return rad;
}

NodArbore* stergeNod(NodArbore* rad, char *parametru)
{
	if (strcmp(parametru, "-f") == 0)
	{

		if (rad == NULL) return NULL;
		else if (rad->informatie.isDirectory == true)
		{
			rad = stergeRad(rad);
			return rad;
		}
		else
		{
			NodArbore *aux = rad;
			while (true)
			{

				if (aux->left == NULL)


					break;

				else
				
					if (aux->left->informatie.isDirectory == true)
						aux->left = stergeRad(aux->left);
					else aux = aux->left;

		
		             if (aux->right == NULL)
						break;

						else
						{
							if (aux->right->informatie.isDirectory == true)
								aux->right = stergeRad(aux->right);
								else aux = aux->right;
					    }


	}

	return rad;
			}

		}
	else if (strcmp(parametru, "-d") == 0)
	{
		if (rad == NULL) return NULL;
		else if (rad->informatie.isDirectory == false)
		{
			rad = stergeRad(rad);
			return rad;
		}
		else
		{
			NodArbore *aux = rad;
			while (true)
			{

				if (aux->left == NULL)


					break;

				else

				if (aux->left->informatie.isDirectory == false)
					aux->left = stergeRad(aux->left);
				else aux = aux->left;


				if (aux->right == NULL)
					break;

				else
				{
					if (aux->right->informatie.isDirectory == false)
						aux->right = stergeRad(aux->right);
					else aux = aux->right;
				}


			}

			return rad;
		}

	}
	
}





void printRLeftRight(NodArbore* root)
{
	if (root != NULL)
	{
		printf("\n %d %s ", root->informatie.id, root->informatie.fileName);
		printRLeftRight(root->left);
		printRLeftRight(root->right);
	}
}

void stergereNod(NodArbore **root, char *parametru)
{
	if (*root != NULL)
	{
		
		if ((*root)->informatie.isDirectory == true)
		{
			*root = stergeNod(*root, parametru);
		}
		stergereNod(&(*root)->left, parametru);
		stergereNod(&(*root)->right, parametru);
	}
}

void dezalocareArbore(NodArbore* rad)
{
	if (rad != NULL)
	{
		NodArbore* st = rad->left;
		NodArbore* dr = rad->right;
		free(rad->informatie.extension);
		free(rad->informatie.fileName);
		free(rad->informatie.path);
		free(rad->informatie.size);
		free(rad);
		
		dezalocareArbore(st);
		dezalocareArbore(dr);
	}
	printf("\nArbore dezalocat");
}

NodArbore* filter(char *parametru,NodArbore *root)
{
	bool rezultatExecutie = false;
	
	if (root == NULL)
	{
		if (strcmp(&parametru[0], "c") == 0 || strcmp(&parametru[0], "C") == 0 || strcmp(&parametru[0], "d") == 0 || strcmp(&parametru[0], "D"))
		{
			root=inserareFisierInArbore(root, convertCharArrayToLPCWSTR(parametru));
			rezultatExecutie = true;
			return root;
		}
		else
		{
			root=inserareFisierInArbore(root, convertCharArrayToLPCWSTR("."));
			rezultatExecutie = true;
			return root;
		}
	}
	if (strcmp(parametru, "-d") == 0 || strcmp(parametru, "-f") == 0)
	{

		stergereNod(&root, parametru);
			

	}
	else
	{
		
	}

	printRLeftRight(root);

	dezalocareArbore(root);

	return root;

}

bool parsareComandaFilter(nod_coada *prim, nod_coada *ultim)
{
	bool rezultatExecutie = false;
	char *numeComanda = NULL;
	NodArbore *root = NULL;
	
	while (numeComanda = scoateNodDinCoada(&prim, &ultim, numeComanda))
	{
		
		root = filter(numeComanda,root);
		rezultatExecutie = true;

	}
	
	return rezultatExecutie;
}

void dezalocare_coada(nod_coada *p, nod_coada *u)
{
	nod_coada *aux = p, *q;
	while (aux)
	{
		q = aux->next;
		delete aux;
		aux = q;
	}
	if (p == NULL) u = NULL;
	printf("\nCoadaDezalocata");
}

bool parsareComanda(nod_coada *prim, nod_coada *ultim)
{
	bool rezultatExecutie = false;
	char mesaj[25] = "Succesful";
	char *numeComanda = NULL;
	numeComanda = scoateNodDinCoada(&prim, &ultim, numeComanda);
	char linie[60];
	strcpy(linie, numeComanda);
	if (strcmp(numeComanda, "list") == 0)
	{
		rezultatExecutie = parsareComandaList(prim, ultim);
		if (rezultatExecutie == true)
		{
			while (numeComanda = scoateNodDinCoada(&prim, &ultim, numeComanda))
			{
				strcat(linie, " ");
				strcat(linie, numeComanda);
				
			}

			log(linie, mesaj);
			
		}


	}

	else if (strcmp(numeComanda, "filter") == 0)
	{
		rezultatExecutie = parsareComandaFilter(prim, ultim);

		if (rezultatExecutie == true)
		{
			while (numeComanda = scoateNodDinCoada(&prim, &ultim, numeComanda))
			{
				strcat(linie, " ");
				strcat(linie, numeComanda);
				
				
				
			}
		
			log(linie,mesaj);
			
		}
	}
	else if (strcmp(numeComanda, "exit") == 0)
	{
		rezultatExecutie = false;
		log(numeComanda,mesaj);

		
		
		printf("\nExecutia s-a oprit");
	}
	else if (strcmp(numeComanda, "get") == 0)
	{
		rezultatExecutie = parsareComandaList(prim, ultim);
	}
	
		
	dezalocare_coada(prim, ultim);
	


	return rezultatExecutie;

}





void main()
{
	bool running = true;
	while (running)
	{
		
		char linie[120];

		fseek(stdin, 0, SEEK_END);
		fflush(stdin);
		printf("\nIntroduceti comanda: ");
		
		gets_s(linie);

		nod_coada *p = NULL;
		nod_coada *u = NULL;

		char *token[100],sep_list[]=" ";
		int nrParametri = 0;
		int i = 0;
		
		token[0] = strtok(linie, sep_list);
		while (token[i]!=NULL)
		{
			i++;
			token[i] = strtok(NULL, sep_list);
			if (token[i] != NULL)
			{	
				nrParametri++;
			}
				
		}

		if (strcmp(token[0], "list") == 0)
		{
			//verificare parametru corect
			if (nrParametri > 1)
			{
				printf("\nParametrii incorecti");
			}
			else
			{
				for (int i = 0; i < nrParametri + 1; i++)
				{
					inserareComandaInCoada(&p, &u, token[i]);
			
				}
			}
			
		}
		else if (strcmp(token[0], "get") == 0)
		{
			if (nrParametri > 3)
			{
				printf("\nParametrii incorecti");
			}
			else
			{
				for (int i = 0; i < nrParametri + 1; i++)
				{
					inserareComandaInCoada(&p, &u, token[i]);

				}
			}

		}
		else if (strcmp(token[0], "filter") == 0)
		{
			for (int i = 0; i < nrParametri + 1; i++)
			{
				inserareComandaInCoada(&p, &u, token[i]);

			}

		}
		else if (strcmp(token[0], "saveget") == 0)
		{

		}
		else if (strcmp(token[0], "exit") == 0)
		{
			inserareComandaInCoada(&p, &u, token[0]);
		}
		else
		{
			printf("\nComanda invalida");
		}
		if (p!=NULL && u!=NULL)
		{
			bool rezultatExecutie = parsareComanda(p, u);
			if (rezultatExecutie == true)
			{
				printf("\nComanda a fost executata cu succes");
			}
			
			running = rezultatExecutie;
			
		}


		
		}

	

	_getch();
}