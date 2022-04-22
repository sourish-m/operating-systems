#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void line(int);
void print(double[10], int);
void check(double[][11], int);
void swap(double[][11], int, int, int);
void g_jacobi(double[][11], int);
double x[10], xn[10];
int flag=1;

int main()
{
	int i, j, n, max_itr, itr=0;
	double coef[10][11], e;
	
	cpt:
	printf("\n ---------Gauss Jacobi---------");
	printf("\n Enter number of equations: ");
	scanf("%d", &n);
	
	for(i=0;i<n;i++)
	{
		printf("\n Enter coefficients for equation %d\n", i+1);
		for(j=0;j<n;j++)
		{
			printf(" Coefficient of x%d: ", j+1);
			scanf("%lf", &coef[i][j]);
		}
		printf(" Enter constant: ");
		scanf("%lf", &coef[i][n]);
	}
	
	printf("\n Enter accuracy(dp): ");
	scanf("%lf", &e);
	e = pow(0.1, e+1);
	
	printf("\n Enter max iterations: ");
	scanf("%d", &max_itr);
	
	for(i=0;i<n;i++)
	{
		x[i]=0;
		xn[i]=0;
	}
	
	system("cls");
	check(coef, n);
	if(!flag)
	goto cpt;
	
	printf("\n System of equations:\n");
	for(i=0;i<n;i++)
	{
		printf("\n ");
		for(j=0;j<n;j++)
		{
			printf("%.3lfx%d", coef[i][j], j+1);
			
			if(j<n-1)
			printf(" + ");
		}
		printf(" = %.3lf", coef[i][n]);
	}
	printf("\n");
	
	line(16*n-6);
	printf("\n");
	for(i=0;i<n;i++)
	printf("    x%d\t\t", i+1);
	line(16*n-6);
	
	do
	{
		g_jacobi(coef, n);
		itr++;
	}while(fabs(xn[0]-x[0])>e && itr<max_itr);
	
	printf("\n\n The solution is\n");
	for(i=0;i<n;i++)
	printf("\n x%d = %.3lf", i+1, xn[i]);
}

void line(int x)
{
	printf("\n");
	for(x=x-1;x>=0;x--)
	printf("-");
}

void print(double x[10], int n)
{
	int i;
	
	printf("\n");
	for(i=0;i<n;i++)
	printf(" %lf       ", x[i]);
}

void check(double a[][11], int n)
{
	int i, j, k;
	double sum;
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			sum=0;
			for(k=0;k<n;k++)
			{
				if(j!=k)
				sum+=fabs(a[i][k]);
			}
			if(fabs(a[i][j])>sum && i==j)
			{
				flag=1;
				break;
			}
			else if(fabs(a[i][j])>sum)
			{
				swap(a, n, i, j);
				flag=1;
				break;
			}
			else
			flag=0;
		}
		if(!flag)
		{
			printf("\n The method does not converge for the given system\n Try with other equations\n");
			break;
		}
	}
}

void swap(double a[][11], int k, int m, int n)
{
	int i;
	double t;
	
	for(i=0;i<=k;i++)
	{
		t = a[m][i];
		a[m][i] = a[n][i];
		a[n][i] = t;
	}
}

void g_jacobi(double a[][11], int n)
{
	int i, j, k;
	double sum;
	
	for(i=0;i<n;i++)
	x[i]=xn[i];
	
	for(i=0;i<n;i++)
	{
		sum=0;
		for(j=0;j<n;j++)
		{
			if(i!=j)
			sum+=a[i][j]*x[j];
		}
		xn[i]=(a[i][n]-sum)/a[i][i];
	}
	
	print(x, n);
}
