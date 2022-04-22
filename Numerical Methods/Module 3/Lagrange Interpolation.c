#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main()
{
	int i, j, n;
	double sum, x_un, temp;
	
	printf("\n -------- Lagrange's Interpolation --------");
	printf("\n Enter number of entries: ");
	scanf("%d", &n);
	
	double x[n], y[n];
	
	printf("\n Enter values:");
	for(i=0; i<n; i++) {
		printf("\n x%d = ", i);
		scanf("%lf", &x[i]);
		printf(" f(%.2lf) = ", x[i]);
		scanf("%lf", &y[i]);
	}
	
	printf("\n Enter value of x for which f(x) is to be found: ");
	scanf("%lf", &x_un);
	
	for(i=0; i<n; i++) {
		temp = 1;
		for(j=0; j<n; j++) {
			if(i==j)
				continue;
			else
				temp *= ((x_un - x[j])/(x[i] - x[j]));
		}
		sum += (y[i]*temp);
	}
	printf("\n\n f(%.2lf) = %.4lf", x_un, sum);
}
