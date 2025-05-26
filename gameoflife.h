#include <stdio.h>
#include <stdlib.h>

typedef int Data;
typedef struct Nod {
    Data linie;
    Data coloana;
    struct Nod* next;
} Nod;

typedef struct Node {
    Nod* list;
    struct Node* next;
} Node;

typedef struct Tree {
    Nod* list;
    struct Tree* left;
    struct Tree* right;
} Tree;

typedef struct Vec {
    int vertex;
    struct Vec* next;
} Vec;

typedef struct Graph {
    int V;        
    Vec** adj;
    Nod **noduriVector;   // vector de liste 
} Graph;

int nr_vecini_celula(char** matrice, int N, int M, int i, int j);
void reguli(char** matrice, char** matrice_noua, int N, int M);
void schimbari(char** matrice, char** matrice_noua, int N, int M, Node** stack);
void addAtBeginning(Nod** head, Data linie, Data coloana);
void addAtEnd(Nod** head, Data linie, Data coloana);
void push(Node** top, Nod* list);
void printStack(Node* top, FILE* fisier);
void deletelist(Nod* head);
void deleteStack(Node** top);
void reguli_B(char** matrice, char** matrice_noua, int N, int M);
Tree* insert(Nod* list);
void arbore_creat(Tree* root, char** matrice, int N, int M, int level, int K);
void preordine(Tree* root, char** matrice, int N, int M, FILE* fisier);
void deleteTree(Tree* root);
void copie_matrice(char** original, char** copie, int N, int M);
void backtrackLongestPath(Graph *graph, int current, int *visited, int *lant, int lungime_lant, int *lant_max, int *lungime_lant_max, int *componenta, int n);
void DFS_scan(Graph *graph, int *visited, int i, int *componente, int *n, int *first);
Graph *createGraph(Nod *list);
void addEdge(Graph *graph, int u, int v);
Vec *createNode(int v);
