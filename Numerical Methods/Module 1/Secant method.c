#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define e 0.0001
void root(double, double);
double func(double);
int n=0;
double a, b, h, x, t;
double fa, fb, fx;

int main()
{
	flag:
	printf("\n Function: f(x) = e^(-x)-x\n");
	printf("\n Enter lower limit: ");
	scanf("%lf", &a);
	
	printf("\n Enter upper limit: ");
	scanf("%lf", &b);
	
	fa=func(a);
	fb=func(b);
	system("cls");
	
	if(fa*fb>0)
	{
		printf("\n There is no real root between %.2f and %.2f\n", a, b);
		goto flag;
	}
	printf("\n Function: f(x) = e^(-x)-x\n\n f(%.2f) = %.2f\n\n f(%.2f) = %.2f\n", a, fa, b, fb);
	printf("\n ----------------------------------------------------------------\n");
	printf("   n \t   a(n) \t   b(n) \t   f(a) \t   f(b)");
	printf("\n ----------------------------------------------------------------\n");
	
	do
	{
		root(a, b);
		n++;
	}while(fabs(b-a)>e);
	root(a,b);
	printf("\n Approx. root: %.3lf", b);
}

void root(double a1, double b1)
{
	fa=func(a1);
	fb=func(b1);
	a=b;
	b=b1-(b1-a1)/(fb-fa)*fb;
	
	printf("   %d \t %lf \t %lf \t %lf \t%lf\n", n, a1, b1, fa, fb);
}

double func(double x)
{
	return 1/exp(x)-x;
}
