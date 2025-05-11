#include "gameoflife.h"

void addAtBeginning(Nod ** head, Data linie, Data coloana) {
    Nod * newNode = (Nod * ) malloc(sizeof(Nod));
    newNode -> linie = linie;
    newNode -> coloana = coloana;
    newNode -> next = * head;
    * head = newNode;
}
void addAtEnd(Nod ** head, Data linie, Data coloana) {
    if ( * head == NULL) {
        addAtBeginning( & * head, linie, coloana);
        return;
    }

    Nod * aux = * head;

    while (aux -> next != NULL)
        aux = aux -> next;

    Nod * newNode = (Nod * ) malloc(sizeof(Nod));
    newNode -> linie = linie;
    newNode -> coloana = coloana;
    newNode -> next = NULL;
    aux -> next = newNode;

}

void push(Node ** top, Nod * list) {
    Node * newNode = (Node * ) malloc(sizeof(Node));
    newNode -> list = list;
    newNode -> next = * top;
    * top = newNode;
}

void printStack(Node * top, FILE * fisier) {
    if (top == NULL) {
        return;
    }
    printStack(top -> next, fisier);
    static int g = 1;

    fprintf(fisier, "%d ", g++);

    Nod * aux = top -> list;
    while (aux) {
        if (aux -> next != NULL) {
            fprintf(fisier, "%d %d ", aux -> linie, aux -> coloana);
        } else {
            fprintf(fisier, "%d %d", aux -> linie, aux -> coloana);
        }

        aux = aux -> next;
    }

    fprintf(fisier, "\n");
    top = top -> next;

}

void deleteStack(Node ** top) {
    Node * temp;
    while (( * top) != NULL) {
        temp = * top;
        * top = ( * top) -> next;
        deletelist(temp -> list);
        free(temp);
    }
}

void deletelist(Nod * head) {
    Nod * temp;
    while (head != NULL) {
        temp = head;
        head = head -> next;
        free(temp);
    }

}

int nr_vecini_celula(char ** matrice, int N, int M, int i, int j) {
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

void reguli(char ** matrice, char ** matrice_noua, int N, int M) {
    int i, j;
    int k;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            k = nr_vecini_celula(matrice, N, M, i, j);

            if (matrice[i][j] == 'X' && (k < 2 || k > 3)) {
                matrice_noua[i][j] = '+';

            } else if (matrice[i][j] == 'X' && (k == 2 || k == 3)) {
                matrice_noua[i][j] = 'X';

            } else if (matrice[i][j] == '+' && k == 3) {
                matrice_noua[i][j] = 'X';

            } else {
                matrice_noua[i][j] = matrice[i][j];
            }
        }
    }

}

void schimbari(char ** matrice, char ** matrice_noua, int N, int M, Node ** stack) {

    Nod * lista = NULL;
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (matrice[i][j] != matrice_noua[i][j])

            {
                addAtEnd( & lista, i, j);

            }
        }
    }
    push(stack, lista);

}

Tree* insert(Nod* list) {

    Tree* newNode = (Tree*)malloc(sizeof(Tree));
    newNode->list = list;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void reguli_B(char** matrice, char** matrice_noua, int N, int M) {
    int i, j;
    int k;

   
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            matrice_noua[i][j] = matrice[i][j];
        }
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            k = nr_vecini_celula(matrice, N, M, i, j);
            
            if (k == 2) {
                matrice_noua[i][j] = 'X'; 
            }
        }
    }
}

void copie_matrice(char** original, char** copie, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            copie[i][j] = original[i][j];
        }
    }
}

void arbore_creat(Tree* root, char** matrice, int N, int M, int level, int K) {

    if (level >= K) {
        return;
    }
    

    char** matrice_B = (char**)malloc(N * sizeof(char*));
    char** matrice_standard = (char**)malloc(N * sizeof(char*));
    
    for (int i = 0; i < N; i++) {
        matrice_B[i] = (char*)malloc(M * sizeof(char));
        matrice_standard[i] = (char*)malloc(M * sizeof(char));
    }
    
    
    char** matrice_B_noua = (char**)malloc(N * sizeof(char*));
    char** matrice_standard_noua = (char**)malloc(N * sizeof(char*));
    
    for (int i = 0; i < N; i++) {
        matrice_B_noua[i] = (char*)malloc(M * sizeof(char));
        matrice_standard_noua[i] = (char*)malloc(M * sizeof(char));
    }
    
  
    copie_matrice(matrice, matrice_B, N, M);
    copie_matrice(matrice, matrice_standard, N, M);
    
   
    reguli_B(matrice_B, matrice_B_noua, N, M);
    reguli(matrice_standard, matrice_standard_noua, N, M);
    
   
    Nod* lista_B = NULL;
    Nod* lista_standard = NULL;
    
   
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (matrice_B[i][j] != matrice_B_noua[i][j]) {
                addAtEnd(&lista_B, i, j);
            }
        }
    }
    
  
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (matrice_standard[i][j] != matrice_standard_noua[i][j]) {
                addAtEnd(&lista_standard, i, j);
            }
        }
    }
    
    
    root->left = insert(lista_B);
    root->right = insert(lista_standard);
    
    
    arbore_creat(root->left, matrice_B_noua, N, M, level + 1, K);
    arbore_creat(root->right, matrice_standard_noua, N, M, level + 1, K);

    for (int i = 0; i < N; i++) {
        free(matrice_B[i]);
        free(matrice_standard[i]);
        free(matrice_B_noua[i]);
        free(matrice_standard_noua[i]);
    }
    free(matrice_B);
    free(matrice_standard);
    free(matrice_B_noua);
    free(matrice_standard_noua);
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
            if (matrice_left[current->linie][current->coloana] == 'X') {
                matrice_left[current->linie][current->coloana] = '+';
            } else {
                matrice_left[current->linie][current->coloana] = 'X';
            }
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