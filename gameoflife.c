#include "gameoflife.h"

void addAtBeginning(Nod **head, Data linie, Data coloana)
{
    Nod *newNode = (Nod *)malloc(sizeof(Nod));
    newNode->linie = linie;
    newNode->coloana = coloana;
    newNode->next = *head;
    *head = newNode;
}
void addAtEnd(Nod **head, Data linie, Data coloana)
{
    if (*head == NULL)
    {
        addAtBeginning(&*head, linie, coloana);
        return;
    }

    Nod *aux = *head;

    while (aux->next != NULL)
        aux = aux->next;

    Nod *newNode = (Nod *)malloc(sizeof(Nod));
    newNode->linie = linie;
    newNode->coloana = coloana;
    newNode->next = NULL;
    aux->next = newNode;
}

void push(Node **top, Nod *list)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->list = list;
    newNode->next = *top;
    *top = newNode;
}

void printStack(Node *top, FILE *fisier)
{
    if (top == NULL)
    {
        return;
    }
    printStack(top->next, fisier);
    static int g = 1;

    fprintf(fisier, "%d ", g++);

    Nod *aux = top->list;
    while (aux)
    {
        if (aux->next != NULL)
        {
            fprintf(fisier, "%d %d ", aux->linie, aux->coloana);
        }
        else
        {
            fprintf(fisier, "%d %d", aux->linie, aux->coloana);
        }

        aux = aux->next;
    }

    fprintf(fisier, "\n");
    top = top->next;
}

void deleteStack(Node **top)
{
    Node *temp;
    while ((*top) != NULL)
    {
        temp = *top;
        *top = (*top)->next;
        deletelist(temp->list);
        free(temp);
    }
}

void deletelist(Nod *head)
{
    Nod *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int nr_vecini_celula(char **matrice, int N, int M, int i, int j)
{
    // test
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
            {
                matrice_noua[i][j] = '+';
            }
            else if (matrice[i][j] == 'X' && (k == 2 || k == 3))
            {
                matrice_noua[i][j] = 'X';
            }
            else if (matrice[i][j] == '+' && k == 3)
            {
                matrice_noua[i][j] = 'X';
            }
            else
            {
                matrice_noua[i][j] = matrice[i][j];
            }
        }
    }
}

void schimbari(char **matrice, char **matrice_noua, int N, int M, Node **stack)
{

    Nod *lista = NULL;
    int i, j;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            if (matrice[i][j] != matrice_noua[i][j])

            {
                addAtEnd(&lista, i, j);
            }
        }
    }
    push(stack, lista);
}

Tree *insert(Nod *list)
{

    Tree *newNode = (Tree *)malloc(sizeof(Tree));
    newNode->list = list;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void reguli_B(char **matrice, char **matrice_noua, int N, int M)
{
    int i, j;
    int k;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            matrice_noua[i][j] = matrice[i][j];
        }
    }

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            k = nr_vecini_celula(matrice, N, M, i, j);

            if (k == 2)
            {
                matrice_noua[i][j] = 'X';
            }
        }
    }
}

void copie_matrice(char **original, char **copie, int N, int M)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            copie[i][j] = original[i][j];
        }
    }
}

void arbore_creat(Tree *root, char **matrice, int N, int M, int level, int K)
{

    if (level >= K)
    {
        return;
    }

    char **matrice_B = (char **)malloc(N * sizeof(char *));
    char **matrice_standard = (char **)malloc(N * sizeof(char *));

    for (int i = 0; i < N; i++)
    {
        matrice_B[i] = (char *)malloc(M * sizeof(char));
        matrice_standard[i] = (char *)malloc(M * sizeof(char));
    }

    char **matrice_B_noua = (char **)malloc(N * sizeof(char *));
    char **matrice_standard_noua = (char **)malloc(N * sizeof(char *));

    for (int i = 0; i < N; i++)
    {
        matrice_B_noua[i] = (char *)malloc(M * sizeof(char));
        matrice_standard_noua[i] = (char *)malloc(M * sizeof(char));
    }

    copie_matrice(matrice, matrice_B, N, M);
    copie_matrice(matrice, matrice_standard, N, M);

    reguli_B(matrice_B, matrice_B_noua, N, M);
    reguli(matrice_standard, matrice_standard_noua, N, M);

    Nod *lista_B = NULL;
    Nod *lista_standard = NULL;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (matrice_B[i][j] != matrice_B_noua[i][j])
            {
                addAtEnd(&lista_B, i, j);
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (matrice_standard[i][j] != matrice_standard_noua[i][j])
            {
                addAtEnd(&lista_standard, i, j);
            }
        }
    }

    root->left = insert(lista_B);
    root->right = insert(lista_standard);

    arbore_creat(root->left, matrice_B_noua, N, M, level + 1, K);
    arbore_creat(root->right, matrice_standard_noua, N, M, level + 1, K);

    for (int i = 0; i < N; i++)
    {
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

Nod *extrageCeluleVii(char **matrice, int N, int M)
{
    Nod *lista = NULL;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (matrice[i][j] == 'X')
            {
                addAtEnd(&lista, i, j);
            }
        }
    }
    return lista;
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

void deleteTree(Tree *root)
{
    if (root == NULL)
    {
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);
    deletelist(root->list);
    free(root);
}

Vec *createNode(int v)
{
    Vec *newNode = (Vec *)malloc(sizeof(Vec));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph *graph, int u, int v)
{
    // Adăugăm v la lista lui u
    Vec *newNode = createNode(v);
    newNode->next = graph->adj[u];
    graph->adj[u] = newNode;

    // Adăugăm u la lista lui v (deoarece graful e neorientat)
    newNode = createNode(u);
    newNode->next = graph->adj[v];
    graph->adj[v] = newNode;
}

// alocăm și inițializăm graful
Graph *createGraph(Nod *list)
{
    int i = 0;
    Nod *curent = list;
    while (curent != NULL)
    {
        i++;
        curent = curent->next;
    }
    int V = i;

    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->V = V;
    graph->adj = (Vec **)malloc(V * sizeof(Vec *));
    for (int j = 0; j < V; j++)
    {
        graph->adj[j] = NULL;
    }

    // Creez vectorul de noduri
    graph->noduriVector = malloc(V * sizeof(Nod *));
    curent = list;
    for (int idx = 0; idx < V; idx++)
    {
        graph->noduriVector[idx] = curent;
        curent = curent->next;
    }

    // Adaug muchii
    curent = list;
    int index1 = 0;
    while (curent != NULL)
    {
        Nod *urmatorul = curent->next;
        int index2 = index1 + 1;

        while (urmatorul != NULL)
        {
            if (abs(curent->linie - urmatorul->linie) <= 1 &&
                abs(curent->coloana - urmatorul->coloana) <= 1 &&
                !(curent->linie == urmatorul->linie && curent->coloana == urmatorul->coloana))
            {
                addEdge(graph, index1, index2);
            }

            urmatorul = urmatorul->next;
            index2++;
        }

        curent = curent->next;
        index1++;
    }

    return graph;
}

void DFS_scan(Graph *graph, int *visited, int i, int *componente, int *n, int *first)
{
    if (*n == 0)
    {
        *first = i; // doar la primul apel efectiv din componenta
    }

    visited[i] = 1;
    componente[(*n)++] = i;

    Vec *p = graph->adj[i];
    while (p != NULL)
    {
        if (!visited[p->vertex])
        {
            DFS_scan(graph, visited, p->vertex, componente, n, first);
        }
        p = p->next;
    }
}

void backtrackLongestPath(Graph *graph, int current, int *visited, int *lant, int lungime_lant, int *lant_max, int *lungime_lant_max, int *componenta, int n)
{
    visited[current] = 1;
    lant[lungime_lant++] = current;

    if (lungime_lant > *lungime_lant_max)
    {
        *lungime_lant_max = lungime_lant;
        for (int i = 0; i < lungime_lant; i++)
        {
            lant_max[i] = lant[i];
        }
    }

    Vec *p = graph->adj[current];
    while (p)
    {
        // verificăm dacă p->vertex aparține componentei și nu a fost vizitat
        for (int i = 0; i < n; i++)
        {
            if (componenta[i] == p->vertex && !visited[p->vertex])
            {
                backtrackLongestPath(graph, p->vertex, visited, lant, lungime_lant, lant_max, lungime_lant_max, componenta, n);
                break;
            }
        }
        p = p->next;
    }

    visited[current] = 0; // backtrack
}

void printLongestPathToFile(FILE *f, int length, int *path, Nod **noduriVector)
{
    if (length <= 0)
    {
        fprintf(f, "-1\n");
        return;
    }

    fprintf(f, "%d\n", length - 1);

    for (int i = 0; i < length; i++)
    {
        Nod *current = noduriVector[path[i]];
        fprintf(f, "(%d, %d)", current->linie, current->coloana);
    }
}
