
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
    addAtBeginning(head, linie, coloana);
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
        if (lista->linie == l && lista->coloana == c){
            return 1;
        }
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

Nod* generatii_B( int N, int M,  Nod* lista_intermediara){

    Nod *lista_noua = copie_lista(lista_intermediara);;
 
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
     
             
     
             if (vecini == 2 && !celule_vii(lista_intermediara, i, j)) {
                 addAtEnd(&lista_noua, i, j); 
             }                           
         }                              
     }
 
 
    return lista_noua;
 }



Tree* insert(Nod* lista, int nivel) {
   
        
     Tree* arbore = (Tree*)malloc(sizeof(Tree));
     arbore->list = lista;
     arbore->nivel = nivel;
     arbore ->left = arbore->right = NULL;  
     return arbore;
              
}

Nod* aplica_diferente(Nod* stare_veche, Nod* diferente) {
    Nod* stare_noua = copie_lista(stare_veche); // pornim de la vechea stare

    Nod *modificari = diferente; // parcurgere lista diferente fara modificare
    while (modificari)
    {
        if (celule_vii(stare_noua, modificari->linie, modificari->coloana))
        {                                  // verificam daca celula exista in ambele stari
            Nod *prev = NULL;              // daca exista aceasta inseamna ca era vie si acum moare
            Nod *elemente = stare_noua; // parcurgere lista elemente vii
            while (elemente)
            { // cautam ce se repeta in ambele
                if (elemente->linie == modificari->linie && elemente->coloana == modificari->coloana)
                {
                    if (prev)
                    {
                        prev->next = elemente->next; // stabilim legatura sarind peste ce e in ambele
                    }
                    else
                    {
                        stare_noua = elemente->next; // cazul in care e primul element
                    }
                    free(elemente);
                    break;
                }
                prev = elemente;
                elemente = elemente->next;
            }
        }
        else
        {

            addAtEnd(&stare_noua, modificari->linie, modificari->coloana); // daca nu exista o adaugam inseamna ca era moarta si a inviat
        }
        modificari = modificari->next; // verificam fiecare element din lista
    }

    return stare_noua;
}

Tree* construiesteArbore(Nod* stare_curenta, int nivel, int N, int M, int K) {
    if (nivel > K) return NULL;

    Tree* arbore = insert(copie_lista(stare_curenta), nivel);
    
     // regula alternativa → copil stanga
    Nod* generatia_alternativa = generatii_B(N, M, stare_curenta);
    arbore->left = construiesteArbore(generatia_alternativa, nivel + 1, N, M, K);
    deletelist(generatia_alternativa);
    
    // regula standard → copil dreapta
    Nod* generatia_standard = generatii(N, M, stare_curenta);
    Nod* stare_dreapta = aplica_diferente(stare_curenta, generatia_standard);
    arbore->right = construiesteArbore(stare_dreapta, nivel + 1, N, M, K);
    deletelist(generatia_standard);
    deletelist(stare_dreapta);

    return arbore;
}

void preordine(Tree* root, char** matrice, int N, int M, FILE* fisier) {
    if (root == NULL) {
        return;
    }


    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fprintf(fisier, "%c", matrice[i][j]);
        }
        fprintf(fisier, "\n");
    }
    fprintf(fisier, "\n");


    char** matrice_left = (char**)malloc(N * sizeof(char*));
    char** matrice_right = (char**)malloc(N * sizeof(char*));

    for (int i = 0; i < N; i++) {
        matrice_left[i] = (char*)malloc(M * sizeof(char));
        matrice_right[i] = (char*)malloc(M * sizeof(char));
        for (int j = 0; j < M; j++) {
            matrice_left[i][j] = matrice[i][j];
            matrice_right[i][j] = matrice[i][j];
        }
    }


    if (root->left) {
        Nod* current = root->left->list;
        while (current != NULL) {
            
            matrice_left[current->linie][current->coloana] = 'X';
            current = current->next;
        }
        preordine(root->left, matrice_left, N, M, fisier);
    }


    if (root->right) {
        Nod* current = root->right->list;
        while (current != NULL) {
            if (matrice_right[current->linie][current->coloana] == 'X') {
                matrice_right[current->linie][current->coloana] = '+';
            } else {
                matrice_right[current->linie][current->coloana] = 'X';
            }
            current = current->next;
        }
        preordine(root->right, matrice_right, N, M, fisier);
    }

    for (int i = 0; i < N; i++) {
        free(matrice_left[i]);
        free(matrice_right[i]);
    }
    free(matrice_left);
    free(matrice_right);
}

void deleteTree(Tree* root) {
    if (root == NULL) {
        return;
    }


    deleteTree(root->left);
    deleteTree(root->right);
    deletelist(root->list);
    free(root);
}
