#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void root(double, double);
double func(double);
int n=0, i, opt;
double a, b, x, e;
double fa, fb, fx;

int main()
{
	printf("\n ---------Regula-Falsi Method---------");
	printf("\n 1. Positive root\n 2. Negative root\n 3. Exit\n\n Enter choice: ");
	scanf("%d", &opt);
	
	switch(opt)
	{
		case 1:
			for(i=1;;i++)
			{
				if(func(i)>0 && func(i-1)<0)
				{
					a=i-1;
					b=i;
					break;
				}
			}
			break;
		case 2:
			for(i=-1;;i--)
			{
				if(func(i)<0 && func(i+1)>0)
				{
					a=i;
					b=i+1;
					break;
				}
			}
			break;
		case 3:
			exit(0);
	}
	
	printf("\n Enter accuracy(dp): ");
	scanf("%lf", &e);
	e = pow(0.1, e+1);
	
	/*flag:
	printf("\n Function: f(x) = 2x-log10(x)-7\n");
	printf("\n Enter lower limit: ");
	scanf("%lf", &a);
	
	printf("\n Enter upper limit: ");
	scanf("%lf", &b);*/
	
	fa=func(a);
	fb=func(b);
	system("cls");
	
	/*if(fa*fb>0)
	{
		printf("\n There is no real root between %.2f and %.2f\n", a, b);
		goto flag;
	}*/
	printf("\n Function: f(x) = 3x-cos(x)-1\n\n f(%.2lf) = %.2lf\n\n f(%.2lf) = %.2lf\n", a, fa, b, fb);
	printf("\n ----------------------------------------------------------------------------------------------------\n");
	printf("  n \t   a(n) \t   b(n) \t   f(a) \t   f(b) \t   x(n+1) \t   f(x(n+1))");
	printf("\n ----------------------------------------------------------------------------------------------------\n");
	
	do
	{
		root(a, b);
		n++;
	}while(fabs(fx)>e);
	
	printf("\n Solution converges in iteration: %d\n Approx. root: %.3lf", n-1, x);
	
	return 0;
}

void root(double a1, double b1)
{
	fa=func(a1);
	fb=func(b1);
	x = (a1*fb-b1*fa)/(fb-fa);
	fx=func(x);
	
	if(fx*fb<0)
	a=x;
	else
	b=x;
	
	printf("  %d \t %lf \t %lf \t %lf \t %lf \t  %lf \t   %lf\n", n, a1, b1, fa, fb, x, fx);
}

double func(double x)
{
	return x*log(x)-1.2;
}
