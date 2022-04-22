#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double fact(int);

void main() {
	int i, j, n;
	double h, sum, x_un, r, temp;
	
	printf("\n -------- Newton Forward --------");
	printf("\n Enter number of entries: ");
	scanf("%d", &n);
	
	double x[n], y[n][n];
	
	printf("\n Enter x[0]: ");
	scanf("%lf", &x[0]);
	printf("\n Enter interval length: ");
	scanf("%lf", &h);
	printf("\n Enter values of f(x): \n");
	for(i=0; i<n; i++) {
		x[i] = x[0] + h*i;
		printf(" f(%.2lf) = ", x[i]);
		scanf("%lf", &y[0][i]);
	}
	
	printf("\n Enter value of x for which f(x) is to be found: ");
	scanf("%lf", &x_un);
	
	for(i=1; i<n; i++)
		for(j=0; j<n; j++)
			y[i][j] = y[i-1][j+1] - y[i-1][j];
	
	printf("\n ____________________________________________________\n");
	printf("\n  x(i)\t   y(i)\t    y1(i)    y2(i)    y3(i)    y4(i)");
	printf("\n ____________________________________________________\n");
	for(i=0; i<n; i++) {
		printf("\n  %-8.3lf", x[i]);
		for(j=0; j<n-i; j++)
			printf(" %-8.3lf", y[j][i]);
			
		printf("\n");
	}
	printf("\n ____________________________________________________\n");
	
	r = (x_un - x[0])/h;
	printf("\n\n r = (x - x[0])/h = %.3lf", r);
	sum = y[0][0];
	
	for(i=1; i<n; i++) {
		temp = r;
		for(j=1; j<i; j++)
			temp *= (r - j);
		
		sum += (temp * y[i][0]/fact(i));
	}
	printf("\n\n f(%.2lf) = %.4lf", x_un, sum);
}

double fact(int a) {
	double f = 1;
	
	for(int i=2; i<=a; i++)
		f *= i;
	
	return f;
}
