
#include "task1.h"
int nr_vecini_celula(char **matrice, int N, int M, int i, int j)
{
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