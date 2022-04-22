#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define e 0.0001
int expo, i, n=0;
int coef[10];
float x1=0, x2=0, t=0;
float fx=0, fdx=0;

int main()
{
	printf("\n Enter highest power of polynomial: ");
	scanf("%d", &expo);
	
	for(i=0;i<=expo;i++)
	{
		printf("\n Coeff. x^%d: ", i);
		scanf("%d", &coef[i]);
	}
	
	printf("\n Enter initial value of x(n): ");
	scanf("%f", &x1);
	
	system("cls");
	printf("\n The polynomial is: ");
	for(i=expo;i>0;i--)
	{
		printf("%+dx^%d", coef[i], i);
	}
	printf("%+d", coef[0]);
	
	printf("\n\n -----------------------------------------------------------------\n");
	printf("   n \t   x(n) \t   x(n+1) \t   f(x) \t   f'(x)");
	printf("\n -----------------------------------------------------------------\n");
	
	do
	{
		fx=fdx=0;
		for(i=expo;i>=1;i--)
		{
			fx+=coef[i]*pow(x1, i);
		}
		fx+=coef[0];
		for(i=expo;i>=0;i--)
		{
			fdx+=coef[i]*(i*pow(x1, (i-1)));
		}
		t=x2;
		x2=x1-(fx/fdx);
		printf("   %d \t %f \t %f \t %f \t %f\n", n, x1, x2, fx, fdx);
		x1=x2;
		n++;
	}while(fabs(t-x1)>e);
	
	printf("\n Approx. root: %.4f", x2);
}
