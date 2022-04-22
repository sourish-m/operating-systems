#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void print(double[][11], int);
void arrange(double[][11], int);
void g_elim(double[][11], int);
int opt;

int main()
{
	int i, j, n;
	double coef[10][11];
	
	printf("\n ---------Gauss Elimination---------");
	do
	{
		printf("\n 1. Without partial pivoting \n 2. With partial pivoting \n 3. Exit\n\n Enter choice: ");
		scanf("%d", &opt);
		
		if(opt==3)
		exit(0);
		else if(opt>3)
		printf("\n Wrong choice");
	}while(opt>3);
	
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
	
	system("cls");
	printf("\n System of equations:\n");
	print(coef, n);
	g_elim(coef, n);	
}

void print(double c[][11], int n)
{
	int i, j;
	
	for(i=0;i<n;i++)
	{
		printf("\n ");
		for(j=0;j<n;j++)
		{
			printf("%.3fx%d", c[i][j], j+1);
			
			if(j<n-1)
			printf(" + ");
		}
		printf(" = %.3f", c[i][n]);
	}
	printf("\n");
}

void arrange(double c[][11], int n)
{
	int i, j, k, m;
	double max, t;
	
	for(i=0;i<n-1;i++)
	{
		max=fabs(c[i][i]);
		m=i;
		
		for(j=i+1;j<n;j++)
		{
			if(fabs(c[j][i])>max)
			{
				max=c[j][i];
				m=j;
			}
		}
		
		if(m!=i)
		{
			for(k=0;k<=n;k++)
			{
				t=c[i][k];
				c[i][k]=c[m][k];
				c[m][k]=t;
			}
		}
	}
}

void g_elim(double c[][11], int n)
{
	int i, j, k;
	double x[10], m, sum;
	
	for(j=0;j<n-1;j++)
	{
		if(opt==2)
		arrange(c, n);
		
		for(i=j+1;i<n;i++)
		{
			m=-c[i][j]/c[j][j];
			for(k=j;k<=n;k++)
			c[i][k]+=m*c[j][k];
		}
	}
	x[n-1]=c[n-1][n]/c[n-1][n-1];
	
	for(i=n-2;i>=0;i--)
	{
		sum=0;
		for(j=i+1;j<n;j++)
		sum+=c[i][j]*x[j];
		
		x[i]=(c[i][n]-sum)/c[i][i];
	}
	
	printf("\n Final system of equations:\n");
	print(c, n);
	printf("\n\n The solution is\n");
	for(i=0;i<n;i++)
	{
		printf("\n x%d = %.3f", i+1, x[i]);
	}
}
