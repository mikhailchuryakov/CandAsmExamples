#include <stdio.h>
#include <stdlib.h>
#define cor0(x) ((x) > -1e-10 && (x) < 1e-10 ? 0 : (x))


void swap (double **a, double **b)
{
    double *t = *a;
    *a = *b;
    *b = t;
}

double determinant (int n, double **A)
{
    int i, j, k;
    double znam, det = 1;
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
    return cor0(det);
}


int main()
{
    int n, i, j, k;
    double **A, **B, determ, a;
    scanf("%d", &n);
    A = (double **) malloc((n + 1) * sizeof(double *));
    B = (double **) malloc((n + 1) * sizeof(double *));
    for (i = 0; i < n + 1; i++)
    {
        A[i] = (double *) malloc(n * sizeof(double));
        B[i] = (double *) malloc(n * sizeof(double));
    }
    for (i = 0; i < n; i++)
        for (j = 0; j < n + 1; j++)
        {
            scanf("%lg", &A[j][i]);
            B[j][i] = A[j][i];
        }
    determ = determinant(n, A);
    if (determ)
    {
        for (k = 0; k < n; k++)
        {
            for (i = 0; i < n; i++)
                for (j = 0; j < n + 1; j++)
                    A[j][i] = B[j][i];
            swap(&A[k], &A[n]);
            a = determinant(n, A) / determ;
            printf("%lg\n", cor0(a));
        }
    }
    else
        printf("NO\n");
    for (i = 0; i < n + 1; i++)
    {
        free(A[i]);
        free(B[i]);
    }
    free(A);
    free(B);
    return 0;
}
