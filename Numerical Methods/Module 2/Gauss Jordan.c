#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void print(double[][11], int);
void g_jordan(double[][11], int);

int main()
{
    int i, j, n;
    double coef[10][11];

    printf("\n ---------Gauss-Jordan Method---------");
    printf("\n Enter number of equations: ");
    scanf("%d", &n);

    for(i=0;i<n; i++)
    {
        printf("\n Enter coefficients for equation %d\n", i+1);
        for(j=0; j<n; j++)
        {
            printf(" Coefficient of x%d: ", j+1);
            scanf("%lf", &coef[i][j]);
        }
        printf(" Enter constant: ");
        scanf("%lf", &coef[i][n]);
    }

    system("cls");
    printf("\n System of equations:\n");
    print(coef, n);
    g_jordan(coef, n);
}

void print(double c[][11], int n)
{
    int i, j;

    for(i=0; i<n; i++)
    {
        printf("\n ");
        for(j=0; j<n; j++)
        {
            printf("%.3fx%d", c[i][j], j+1);

            if(j<n-1)
            printf(" + ");
        }
        printf(" = %.3f", c[i][n]);
    }
    printf("\n");
}

void g_jordan(double c[][11], int n)
{
    int i, j, k;
    double x[10], m;

    for(j=0; j<n; j++)
    {
        for(i=0; i<n; i++)
        {
            if(i!=j)
            {
                m=-c[i][j]/c[j][j];
                for(k=j; k<=n; k++)
                c[i][k]+=m*c[j][k];
            }
        }
    }

    for(i=0; i<n; i++)
    x[i]=c[i][n]/c[i][i];

    printf("\n Final system of equations:\n");
    print(c, n);
    printf("\n\n The solution is\n");
    for(i=0; i<n; i++)
    {
        printf("\n x%d = %.3f", i+1, x[i]);
    }
}
