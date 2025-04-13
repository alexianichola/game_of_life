
#include "task1.h"

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