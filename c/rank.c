#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define min(a,b) ((a) < (b) ? (a) : (b))
#define cor0(x) ((x) > -1e-10 && (x) < 1e-10 ? 0 : (x))

void swapb (double *a, double *b)
{
    double t = *a;
    *a = *b;
    *b = t;
}

void swap (double **a, double **b)
{
    double *t = *a;
    *a = *b;
    *b = t;
}

int main()
{
    int n, m, i, j, k, fox = 0;
    double **A, znam;
    scanf("%d %d", &n, &m);
    A = (double **) malloc(n * sizeof(double *));
    for (i = 0; i < n; i++)
        A[i] = (double *) malloc(m * sizeof(double));
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%lg", &A[i][j]);
    for (k = 0; k < min(n, m); k++)
    {
        if (cor0(A[k][k]) == 0)
        {
            for (j = k; j < n && cor0(A[j][k]) == 0; j++);
            if (j != n)
                swap(&A[k], &A[j]);
            if (cor0(A[k][k]) == 0)
            {
                for (j = k; j < m && cor0(A[k][j]) == 0; j++);
                if (j != m)
                    for (i = 0; i < n; i++)
                        swapb(&A[i][k], &A[i][j]);
            }
        }
        if (cor0(A[k][k]) != 0)
        {
            for (i = k + 1; i < n; i++)
            {
                znam = A[i][k] / A[k][k];
                for (j = k; j < m; j++)
                {
                    A[i][j] -= A[k][j] * znam;
                }
            }
        }
    }
    for (i = 0; i < min(n, m); i++)
        if (cor0(A[i][i]) == 0)
            fox++;
    printf("%d\n", i - fox);
    for (i = 0; i < n; i++)
        free(A[i]);
    free(A);
    return 0;
}

