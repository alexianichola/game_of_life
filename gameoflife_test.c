

#include "gameoflife.h"

int main(int argc, const char *argv[])
{
    for (int i = 1; i < argc; i = i + 2)
    {
        FILE *input_file = fopen(argv[i], "r");
        FILE *output_file = fopen(argv[i + 1], "w");

        if (input_file == NULL || output_file == NULL)
        {

            printf("File could not open");

            if (input_file == NULL)
            {
                fclose(output_file);
            }
            else if (output_file == NULL)
            {

                fclose(input_file);
            }

            return 1;
        }

        int T, M, N, K, j, p;
        char **matrice, **matrice_noua, **aux;
        Node *stack = NULL;
        Nod *lista = NULL;

        fscanf(input_file, "%d %d %d %d ", &T, &N, &M, &K);

        matrice = (char **)malloc(N * sizeof(char *));
        if (matrice == NULL)
        {
            printf("Eroare la alocarea memoriei pentru matrice.\n");
            return 1;
        }
        for (i = 0; i < N; i++)
        {
            matrice[i] = (char *)malloc(M * sizeof(char));
            if (matrice[i] == NULL)
            {
                printf("Eroare la alocarea memoriei pentru matrice.\n");
                return 1;
            }
        }

        matrice_noua = (char **)malloc(N * sizeof(char *));
        if (matrice_noua == NULL)
        {
            printf("Eroare la alocarea memoriei pentru matrice.\n");
            return 1;
        }

        for (i = 0; i < N; i++)
        {
            matrice_noua[i] = (char *)malloc(M * sizeof(char));
            if (matrice_noua[i] == NULL)
            {
                printf("Eroare la alocarea memoriei pentru matrice.\n");
                return 1;
            }
        }
        // task 1

        if (T == 1)
        {

            for (i = 0; i < N; i++)
            {
                for (j = 0; j < M; j++)
                {
                    fscanf(input_file, " %c", &matrice[i][j]);
                    fprintf(output_file, "%c", matrice[i][j]);
                }

                fprintf(output_file, "\n");
            }
            fprintf(output_file, "\n");

            for (p = 0; p < K; p++)
            {
                if (p > 0)
                {
                    fprintf(output_file, "\n");
                }

                reguli(matrice, matrice_noua, N, M);

                for (i = 0; i < N; i++)
                {
                    for (j = 0; j < M; j++)
                    {
                        fprintf(output_file, "%c", matrice_noua[i][j]);
                    }

                    fprintf(output_file, "\n");
                }

                aux = matrice;
                matrice = matrice_noua;
                matrice_noua = aux;
            }
            fprintf(output_file, "\n");
        }

        // task  2

        if (T == 2)
        {
            for (i = 0; i < N; i++)
            {
                for (j = 0; j < M; j++)
                {
                    fscanf(input_file, " %c", &matrice[i][j]);
                }
            }
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

            Nod *stare_curenta = copie_lista(lista); // lista celule vii
            Nod *diferente = NULL;

            for (p = 0; p < K; p++)
            {

                diferente = generatii(N, M, stare_curenta); // modificari dupa aplicarea regulilor
                push(&stack, copie_lista(diferente));

                Nod *modificari = diferente; // parcurgere lista diferente fara modificare
                while (modificari)
                {
                    if (celule_vii(stare_curenta, modificari->linie, modificari->coloana))
                    {                                  // verificam daca celula exista in ambele stari
                        Nod *prev = NULL;              // daca exista aceasta inseamna ca era vie si acum moare
                        Nod *elemente = stare_curenta; // parcurgere lista elemente vii
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
                                    stare_curenta = elemente->next; // cazul in care e primul element
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

                        addAtEnd(&stare_curenta, modificari->linie, modificari->coloana); // daca nu exista o adaugam inseamna ca era moarta si a inviat
                    }
                    modificari = modificari->next; // verificam fiecare element din lista
                }

                deletelist(diferente); // pregatim lista pentru urmatoarea modificare si ramanem in stare curenta cu celulele din generatia urmatoare
            }

            printStack(stack, output_file);
            deletelist(stare_curenta);
            deletelist(lista);

            // // cum as introduce eu bonusul in game_of_life
            // char **matrice_bonus, **matrice_bonus_rezultat;
            // Nod *lista_matrice = NULL;

            // matrice_bonus = (char **)malloc(N * sizeof(char *));
            // if (matrice_bonus == NULL)
            // {
            //     printf("Eroare la alocarea memoriei pentru matrice.\n");
            //     return 1;
            // }
            // for (i = 0; i < N; i++)
            // {
            //     matrice_bonus[i] = (char *)malloc(M * sizeof(char));
            //     if (matrice_bonus[i] == NULL)
            //     {
            //         printf("Eroare la alocarea memoriei pentru matrice.\n");
            //         return 1;
            //     }
            // }

            // matrice_bonus_rezultat = (char **)malloc(N * sizeof(char *));
            // if (matrice_bonus_rezultat == NULL)
            // {
            //     printf("Eroare la alocarea memoriei pentru matrice.\n");
            //     return 1;
            // }
            // for (i = 0; i < N; i++)
            // {
            //     matrice_bonus_rezultat[i] = (char *)malloc(M * sizeof(char));
            //     if (matrice_bonus_rezultat[i] == NULL)
            //     {
            //         printf("Eroare la alocarea memoriei pentru matrice.\n");
            //         return 1;
            //     }
            // }

            // for (i = 0; i < N; i++)
            // {
            //     for (j = 0; j < M; j++)
            //     {
            //         fscanf(input_file, " %c", &matrice_bonus[i][j]);
            //         matrice_bonus_rezultat[i][j] = matrice_bonus[i][j];
            //     }
            // }

            // matrice_bonus_rezultat = bonus(matrice_bonus, stack, N, M);

            // for (i = 0; i < N; i++)
            // {
            //     for (j = 0; j < M; j++)
            //     {
            //         fprintf(output_file, "%c ", matrice_bonus_rezultat[i][j]);
            //     }

            //     fprintf(output_file, "\n");
            // }
        }

        // bonus separat implementat cu fisiere
        Node *stack_bonus = NULL;
        // Lista 1: (1,2); (3,2); (3,3)
        Nod *lista1 = NULL;
        addAtEnd(&lista1, 1, 2);
        addAtEnd(&lista1, 3, 2);
        addAtEnd(&lista1, 3, 3);

        // Lista 2: (2,1); (2,2); (2,3); (3,1)
        Nod *lista2 = NULL;
        addAtEnd(&lista2, 2, 1);
        addAtEnd(&lista2, 2, 2);
        addAtEnd(&lista2, 2, 3);
        addAtEnd(&lista2, 3, 1);

        push(&stack_bonus, lista1);
        push(&stack_bonus, lista2);

        FILE *matrice_bonus_FILE = fopen("matrice_bonus.txt", "r");
        if (matrice_bonus_FILE == NULL)
        {
            printf("Eroare la deschiderea fisierului de input\n");
            return 0;
        }

        FILE *matrice_bonus_rezultat_FILE = fopen("matrice_bonus_rezultat.txt", "w");
        if (matrice_bonus_rezultat_FILE == NULL)
        {
            printf("Eroare la deschiderea fisierului de output\n");
            return 0;
        }
        fscanf(matrice_bonus_FILE, "%d %d", &N, &M);
        char **matrice_bonus, **matrice_bonus_rezultat;
        Nod *lista_matrice = NULL;

        matrice_bonus = (char **)malloc(N * sizeof(char *));
        if (matrice_bonus == NULL)
        {
            printf("Eroare la alocarea memoriei pentru matrice.\n");
            return 1;
        }
        for (i = 0; i < N; i++)
        {
            matrice_bonus[i] = (char *)malloc(M * sizeof(char));
            if (matrice_bonus[i] == NULL)
            {
                printf("Eroare la alocarea memoriei pentru matrice.\n");
                return 1;
            }
        }

        matrice_bonus_rezultat = (char **)malloc(N * sizeof(char *));
        if (matrice_bonus_rezultat == NULL)
        {
            printf("Eroare la alocarea memoriei pentru matrice.\n");
            return 1;
        }
        for (i = 0; i < N; i++)
        {
            matrice_bonus_rezultat[i] = (char *)malloc(M * sizeof(char));
            if (matrice_bonus_rezultat[i] == NULL)
            {
                printf("Eroare la alocarea memoriei pentru matrice.\n");
                return 1;
            }
        }

        int k = 0;
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < M; j++)
            {
                fscanf(matrice_bonus_FILE, " %c", &matrice_bonus[i][j]);
                matrice_bonus_rezultat[i][j] = matrice_bonus[i][j];
            }
        }

        for (i = 0; i < N; i++)
        {
            for (j = 0; j < M; j++)
            {

                addAtEnd(&lista_matrice, i, j);
            }
        }
        Nod *lista_bonus = lista_matrice;
        while (lista_bonus != NULL)
        {
            k = 0;
            Node *stack_copie = stack_bonus;
            while (stack_copie != NULL)
            {
                Nod *lista_din_stack = stack_copie->list;

                while (lista_din_stack != NULL)
                {
                    if (lista_din_stack->linie == lista_bonus->linie && lista_din_stack->coloana == lista_bonus->coloana)
                    {
                        k++;
                    }
                    lista_din_stack = lista_din_stack->next;
                }
                stack_copie = stack_copie->next;
            }
            if (k % 2 == 1)
            {
                if (matrice_bonus[lista_bonus->linie][lista_bonus->coloana] == 'X')
                {
                    matrice_bonus_rezultat[lista_bonus->linie][lista_bonus->coloana] = '+';
                }
                else
                {
                    matrice_bonus_rezultat[lista_bonus->linie][lista_bonus->coloana] = 'X';
                }
            }

            lista_bonus = lista_bonus->next;
        }

        for (i = 0; i < N; i++)
        {
            for (j = 0; j < M; j++)
            {
                fprintf(matrice_bonus_rezultat_FILE, "%c ", matrice_bonus_rezultat[i][j]);
            }

            fprintf(matrice_bonus_rezultat_FILE, "\n");
        }

        for (i = 0; i < N; i++)
        {

            free(matrice_bonus_rezultat[i]);
            free(matrice_bonus[i]);
        }

        free(matrice_bonus_rezultat);
        free(matrice_bonus);

        fclose(matrice_bonus_FILE);
        fclose(matrice_bonus_rezultat_FILE);

        for (i = 0; i < N; i++)
        {
            free(matrice[i]);
            free(matrice_noua[i]);
        }

        free(matrice);
        free(matrice_noua);

        deleteStack(&stack);

        fclose(input_file);
        fclose(output_file);
    }
}
