#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

int determinant (int n, double **B)
{
    int i, j, k;
    double znam, det = 1, **A;
    A = (double **) malloc(n * sizeof(double *));
    for (i = 0; i < n; i++)
        A[i] = (double *) malloc(n * sizeof(double));
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            A[i][j] = B[i][j];
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
    for (i = 0; i < n; i++)
        free(A[i]);
    free(A);
    return round(det);
}


int main()
{
    int n, i, j, k;
    double **A;
    scanf("%d", &n);
    A = (double **) malloc(n * sizeof(double *));
    for (i = 0; i < n; i++)
        A[i] = (double *) malloc((n + 1) * sizeof(double));
    for (i = 0; i < n; i++)
        for (j = 0; j < n + 1; j++)
            scanf("%lg", &A[i][j]);
    for (k = 0; k < n + 1; k++)
    {
        for (i = k; i < n; i++)
            for (j = 0; j < n; j++)
                swapb(&A[j][i], &A[j][i + 1]);
        if (k % 2 == 0)
            printf("%d ", determinant(n, A));
        else
            printf("%d ", -determinant(n, A));
        for (i = n - 1; i >= k; i--)
            for (j = n - 1; j >= 0; j--)
                swapb(&A[j][i], &A[j][i + 1]);
    }
    printf("\n");
    for (i = 0; i < n; i++)
        free(A[i]);
    free(A);
    return 0;
}
