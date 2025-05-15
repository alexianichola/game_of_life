#include <stdio.h>
#include <stdlib.h>

typedef int Data;
typedef struct Nod {
    Data linie;
    Data coloana;
    struct Nod* next;

}Nod;

typedef struct Node {
    Nod* list;
    struct Node* next;

}Node;



int nr_vecini_celula(char **matrice, int N, int M, int i, int j);
void reguli(char **matrice, char **matrice_noua, int N, int M);
Nod* generatii( int N, int M,  Nod* lista_intermediara);
int celule_vii(Nod* lista, int l, int c);
void addAtBeginning(Nod** head, Data linie, Data coloana);
void addAtEnd(Nod** head,  Data linie, Data coloana);
void push(Node** top, Nod* list);
void printStack(Node* top, FILE* fisier);
void deletelist(Nod* head);
void deleteStack(Node** top);
Nod* copie_lista(Nod* original);
