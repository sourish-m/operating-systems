#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void root(double, double);
double func(double);
void print(double, double);
int n=0, i, opt;
double a, b, x, e;
double fa, fb, fx;

int main()
{
	printf("\n ---------Bisection Method---------");
	printf("\n a: ");
	scanf("%lf", &a);
	printf("\n b: ");
	scanf("%lf", &b);
	
//	printf("\n Enter accuracy(dp): ");
//	scanf("%lf", &e);
	e = 0.0001;
	
	/*flag:
	printf("\n Function: f(x) = x^3-4x-9\n");
	printf("\n Enter lower limit: ");
	scanf("%lf", &a);
	
	printf("\n Enter upper limit: ");
	scanf("%lf", &b);*/
	
	fa=func(a);
	fb=func(b);
	system("cls");
	
	/*if(fa*fb>=0)
	{
		printf("\n There is no real root between %.2f and %.2f\n", a, b);
		goto flag;
	}*/
	printf("\n Function: f(x) = 10^x+sin(x)+2x\n\n f(%.2lf) = %.2lf\n\n f(%.2lf) = %.2lf\n", a, fa, b, fb);
	printf("\n ---------------------------------------------------------------------------------------------------\n");
	printf("  n \t\t   a(n) \t\t   b(n) \t\t   x(n+1) \t\t  f(x(n+1))");
	printf("\n ---------------------------------------------------------------------------------------------------\n");
	
	do
	{
		root(a, b);
		n++;
	}while(fabs(b-a)>e);
	printf("\n Solution converges in iteration: %d\n Approx. root: %.3lf", n-1, x);
	return 0;
}

void root(double a1, double b1)
{
	x=(a1+b1)/2;
	fa=func(a1);
	fb=func(b1);
	fx=func(x);
	
	if(fx<0)
		a=x;
	else
	{
		b=x;
	}
	
	print(a1, b1);
}

void print(double a1, double b1)
{
	printf("  %d \t\t %lf \t\t %lf \t\t  %lf \t\t  %lf\n", n, a1, b1, x, fx);
}

double func(double x)
{
	return cos(x) - exp(-x);
}
