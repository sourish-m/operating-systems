#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double f(double);
double df(double);
int n;
double x1, x2, t, e;

int main()
{
	printf("\n ---------Newton-Raphson Method---------");
	printf("\n Enter accuracy(dp): ");
	scanf("%lf", &e);
	e = pow(0.1, e+1);
	
	do
	{
		printf("\n Enter initial value of x(n): ");
		scanf("%lf", &x1);
		
		if(df(x1)==0)
		printf("\n Initial approximation is incorrect\n");	
	}while(df(x1)==0);
	
	system("cls");
	
	printf("\n Function: f(x) = x^3-8x-4\n");
	printf("\n -------------------------------------------------------------------\n");
	printf("   n \t   x(n) \t  x(n+1) \t  f(x(n)) \t  f'(x(n))");
	printf("\n -------------------------------------------------------------------\n");
	
	do
	{
		x2=x1-(f(x1)/df(x1));
		printf("   %d \t %lf \t %lf \t %lf \t %lf\n", n, x1, x2, f(x1), df(x1));
		t=x1;
		x1=x2;
		n++;
	}while(fabs(t-x2)>e);
	
	printf("\n Solution converges in iteration: %d\n Approx. root: %.4lf", n-1, x2);
	return 0;
}

double f(double x)
{
	return pow(x, 3)-8*x-4;
}

double df(double x)
{
	return 3*pow(x,2)-8;
}
