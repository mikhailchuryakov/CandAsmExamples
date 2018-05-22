#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define cor0(x) ((x) > -1e-10 && (x) < 1e-10 ? 0 : (x))

void swap (double **a, double **b)
{
    double *t = *a;
    *a = *b;
    *b = t;
}

int main()

{
    int n, i, j, k;
    double **A, znam;
    scanf("%d", &n);
    A = (double **) calloc(n, sizeof(double *));
    for (i = 0; i < n; i++)
        A[i] = (double *) calloc(2 * n, sizeof(double));
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%lg", &A[i][j]);
    for (j = 0; j < n; j++)
        A[j][j + n] = 1;
    for (k = 0; k < n; k++)
    {
        if (cor0(A[k][k]) == 0)
        {
            for (j = k + 1; j < n && cor0(A[j][k]) == 0; j++);
            if (j != n)
                swap(&A[k], &A[j]);
            else
            {
                printf("NO\n");
                for (i = 0; i < n; i++)
                    free(A[i]);
                free(A);
                return 0;
            }
        }
        if (cor0(A[k][k]) != 0)
        {
            for (i = 0; i < n; i++)
            {
                if (i != k)
                {
                    znam = A[i][k] / A[k][k];
                    for (j = k; j < 2 * n; j++)
                    {
                        A[i][j] -= A[k][j] * znam;
                    }
                }
            }
        }
    }
    for (k = 0; k < n; k++)
    {
        for (j = n; j < 2 * n; j++)
            A[k][j] /= A[k][k];
    }
    for (i = 0; i < n; i++)
    {
        for (j = n; j < 2 * n; j++)
            printf("%lg ", cor0(A[i][j]));
        printf("\n");
    }
    for (i = 0; i < n; i++)
        free(A[i]);
    free(A);
    return 0;
}
