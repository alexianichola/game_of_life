
#include "gameoflife.h"

int nr_vecini_celula(char **matrice, int N, int M, int i, int j)
{
//test
    int k = 0;

    if (j + 1 < M && matrice[i][j + 1] == 'X')
        k++;
    if (i + 1 < N && matrice[i + 1][j] == 'X')
        k++;
    if (i + 1 < N && j + 1 < M && matrice[i + 1][j + 1] == 'X')
        k++;
    if (i - 1 >= 0 && matrice[i - 1][j] == 'X')
        k++;
    if (i - 1 >= 0 && j - 1 >= 0 && matrice[i - 1][j - 1] == 'X')
        k++;
    if (j - 1 >= 0 && matrice[i][j - 1] == 'X')
        k++;
    if (i - 1 >= 0 && j + 1 < M && matrice[i - 1][j + 1] == 'X')
        k++;
    if (i + 1 < N && j - 1 >= 0 && matrice[i + 1][j - 1] == 'X')
        k++;

    return k;
}

void reguli(char **matrice, char **matrice_noua, int N, int M)
{
    int i, j;
    int k;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            k = nr_vecini_celula(matrice, N, M, i, j);

            if (matrice[i][j] == 'X' && (k < 2 || k > 3))
                matrice_noua[i][j] = '+';

            else if (matrice[i][j] == 'X' && (k == 2 || k == 3))
                matrice_noua[i][j] = 'X';

            else if (matrice[i][j] == '+' && k == 3)
                matrice_noua[i][j] = 'X';
            else
                matrice_noua[i][j] = matrice[i][j];
        }
    }
}
void addAtBeginning(Nod** head, Data linie, Data coloana) {
    Nod *newNode = (Nod*)malloc(sizeof(Nod));
        newNode->linie = linie;
        newNode->coloana = coloana;
        newNode->next = *head;
        *head = newNode;
}
void addAtEnd(Nod** head,  Data linie, Data coloana) {
    if (*head == NULL) {
    addAtBeginning(&*head, linie, coloana);
    return; }


    Nod *aux = *head;


     while (aux->next != NULL)
            aux = aux->next;

    Nod *newNode = (Nod*)malloc(sizeof(Nod));
    newNode->linie = linie;
    newNode->coloana = coloana;
    newNode->next = NULL;
    aux->next = newNode;


}

void push(Node** top, Nod *list) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->list = list;
    newNode->next = *top;
    *top = newNode;
}

void printStack(Node* top, FILE* fisier) {
    if (top == NULL) {
        return;
    }
    printStack(top->next, fisier);
    static int g = 1;

        fprintf(fisier, "%d ", g++);

        Nod* aux = top->list;
         while (aux) {
            if(aux->next != NULL){
                fprintf(fisier, "%d %d ", aux->linie, aux->coloana);}
            else{
                fprintf(fisier, "%d %d", aux->linie, aux->coloana);}

            aux = aux->next;
        }

        fprintf(fisier,"\n");
        top = top->next;

}




void deleteStack(Node** top) {
    Node* temp;
    while ((*top) != NULL) {
        temp = *top;
        *top = (*top)->next;
        deletelist(temp->list);
        free(temp);
    }
}

void deletelist(Nod* head){
    Nod* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free (temp);
    }

}

int celule_vii(Nod* lista, int l, int c) {
    while (lista) {
        if (lista->linie == l && lista->coloana == c)
            return 1;
        lista = lista->next;
    }
    return 0;
}

Nod* copie_lista(Nod* original) {
    Nod* copie = NULL;
    Nod* aux = original;
    while (aux) {
        addAtEnd(&copie, aux->linie, aux->coloana);
        aux = aux->next;
    }
    return copie;
}

Nod* generatii( int N, int M,  Nod* lista_intermediara){
  
   Nod *lista_noua = NULL;

    int i = 0, j = 0, vecini = 0;
    for ( i = 0; i < N; i++) {
        for ( j = 0; j < M; j++) {
            vecini = 0;
    
            if (i > 0 && j > 0 && celule_vii(lista_intermediara, i - 1, j - 1)) vecini++;
            if (i > 0 && celule_vii(lista_intermediara, i - 1, j)) vecini++;
            if (i > 0 && j < M - 1 && celule_vii(lista_intermediara, i - 1, j + 1)) vecini++;
    
            if (j > 0 && celule_vii(lista_intermediara, i, j - 1)) vecini++;
            if (j < M - 1 && celule_vii(lista_intermediara, i, j + 1)) vecini++;
    
            if (i < N - 1 && j > 0 && celule_vii(lista_intermediara, i + 1, j - 1)) vecini++;
            if (i < N - 1 && celule_vii(lista_intermediara, i + 1, j)) vecini++;
            if (i < N - 1 && j < M - 1 && celule_vii(lista_intermediara, i + 1, j + 1)) vecini++;
    
            int eVie = celule_vii(lista_intermediara, i, j);
    
            if ( (!eVie && vecini == 3) || (eVie && (vecini < 2)) ||  (eVie && (vecini > 3 ))) {
                addAtEnd(&lista_noua, i, j); 
            }                           
        }                              
    }


   return lista_noua;
}

