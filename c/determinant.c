#include <stdio.h>
#include <stdlib.h>
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
    double **A, znam, det = 1;
    scanf("%d", &n);
    A = (double **) malloc(n * sizeof(double *));
    for (i = 0; i < n; i++)
        A[i] = (double *) malloc(n * sizeof(double));
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%lg", &A[i][j]);
    for (k = 0; k < n - 1; k++)
    {
        if (cor0(A[k][k]) == 0)
        {
            for (j = k + 1; j < n && cor0(A[j][k]) == 0; j++);
            if (j != n)
            {
                swap(&A[k], &A[j]);
                det = -det;
            }
        }
        if (cor0(A[k][k]) != 0)
        {
            for (i = k + 1; i < n; i++)
            {
                znam = A[i][k] / A[k][k];
                for (j = k; j < n; j++)
                {
                    A[i][j] -= A[k][j] * znam;
                }
            }
        }
    }
    for (i = 0; i < n; i++)
        det *= A[i][i];
    printf("%lg\n", cor0(det));
    for (i = 0; i < n; i++)
        free(A[i]);
    free(A);
    return 0;
}
