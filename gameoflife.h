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

typedef struct Tree{
    int height; 
    Nod* lista;      
    struct  Tree *left,*right; 
}Tree;




int nr_vecini_celula(char **matrice, int N, int M, int i, int j);
void reguli(char **matrice, char **matrice_noua, int N, int M);
void schimbari(char **matrice, char **matrice_noua, int N, int M, Node** stack);
void addAtBeginning(Nod** head, Data linie, Data coloana);
void push(Node** top, Nod* list);
void printStack(Node* top, FILE* fisier);
void deletelist(Nod* head);
void deleteStack(Node** top);
Tree* insert(Tree* arbore, Nod* lista, int ok);
void arborele(char **matrice, char **matrice_noua, int N, int M, Tree** arbore, Node **stack, int ok, int level,int K);
int isEmpty(Node* top);
Nod* pop(Node** top);
void preorder(Tree* root, FILE* fisier,char **matrice_afisata, int N, int M);