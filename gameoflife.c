
#include "gameoflife.h"

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

int isEmpty(Node* top) {
    return top == NULL;
}

Nod* pop(Node** top) {
   
    if (isEmpty(*top)) 
        return NULL; 

    Node *temp = (*top);
    Nod* lista = temp->list;
    *top = (*top)->next;
    free(temp);

    
    return lista;
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


void preorder(Tree* root, FILE* fisier, char **matrice_afisata, int N, int M) {
    int i = 0, j = 0, linie = 0, coloana = 0;

    if (root) {
       Nod* aux = root->lista;

       
        while (aux!=NULL) { 

            linie = aux->linie;
            coloana = aux->coloana;
            if(matrice_afisata[linie][coloana] == '+'){
                matrice_afisata[linie][coloana] = 'X'; }
            else{
                matrice_afisata[linie][coloana] = '+';
            } 
            aux = aux->next;
       }   
       
       for (i = 0; i < N; i++)
       {
           for (j = 0; j < M; j++)
           {  fprintf(fisier, "%c", matrice_afisata[i][j]);
          
        }
              fprintf(fisier,"\n");
       }
      
         fprintf(fisier,"\n");

        preorder(root->left, fisier, matrice_afisata, N, M);    

        preorder(root->right, fisier, matrice_afisata, N, M);        
    }
}


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

            if (matrice[i][j] == 'X' && (k < 2 || k > 3)){
                matrice_noua[i][j] = '+';
                
            }
                
            else if (matrice[i][j] == 'X' && (k == 2 || k == 3)){
                matrice_noua[i][j] = 'X';
            
            }

            else if (matrice[i][j] == '+' && k == 3){
                matrice_noua[i][j] = 'X';
            
                
            }

            else{
                matrice_noua[i][j] = matrice[i][j];
            }
        }
    }
 
}

void reguli_B(char **matrice, char **matrice_noua, int N, int M)
{   
    int i, j;
    int k;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            k = nr_vecini_celula(matrice, N, M, i, j);

             if (k == 2){
                matrice_noua[i][j] = 'X';
            
            }
            else{
                matrice_noua[i][j] = matrice[i][j];
            }
        }
    }
}

Tree* insert(Tree* arbore, Nod* lista, int ok) {
  
        if (arbore == NULL){
                arbore = (Tree*)malloc(sizeof(Tree));
                arbore->lista = lista;
                arbore->height = 0; 
                arbore ->left = arbore->right = NULL;  
                return arbore;
              
        }
        else {
    
         if(ok==1){
                
                arbore->left=insert(arbore->left, lista,  ok);
                
            }
            else {
              
                arbore->right=insert(arbore->right, lista, ok);
            }
        }
    return arbore;
}

 void schimbari(char **matrice, char **matrice_noua, int N, int M,  Node **stack){
    
    Nod* lista=NULL;
    int i,j;

     for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
         {  
            if( matrice[i][j] != matrice_noua[i][j] )

            {    
                addAtEnd(&lista, i, j);
                

            }      
          }
   }
   push(stack, lista);

 }



 void arborele(char **matrice, char **matrice_noua, int N, int M, Tree** arbore, Node **stack, int ok, int level, int K)
 {  int i, j;
    Nod* lista=NULL;
    Nod* lista_schimbari = NULL;
    

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            if (matrice[i][j] == 'X')
            {
                addAtEnd(&lista, i, j);
            }
        }
    }

    *arbore = insert(*arbore, lista,  0);

    reguli(matrice, matrice_noua,  N,  M);
    schimbari(matrice, matrice_noua,  N,  M,  stack);
    lista_schimbari = pop(stack);
    *arbore = insert(*arbore, lista_schimbari, 0);



     for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrice_noua[i][j] = '+';  
        }
    }
    
    reguli_B(matrice, matrice_noua,  N,  M);
    schimbari(matrice, matrice_noua,  N,  M,  stack);
    lista_schimbari = pop(stack);
    *arbore = insert(*arbore, lista_schimbari, 1);
    
    // arborele(matrice_noua, matrice, N, M, &((*arbore)->left), stack, 1, level + 1); // Stânga pentru regula B
    // arborele(matrice, matrice_noua, N, M, &((*arbore)->right), stack, 0, level + 1); // Dreapta pentru regulile standard
    

   

 }
