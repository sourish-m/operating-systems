#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void dline(int);

void main() {
	int i, j, n, flag=0, z;
	double h, x0, fdx=0;
	printf("\n\t----------Numerical Differentiation using Newton forward interpolation----------\n");
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
	printf("\n Enter the value of x for which f'(x) is to be found: ");
	scanf("%lf", &x0);
	
	for(i=0;i<n;i++) {
		if(fabs(x0 - x[i])<0.0001) {
			z = i;
			flag = 1;
			break;
		}
	}
	if(!flag) {
		printf("\n Invalid calculation point. Exiting...");
		exit(0);
	}
	
	for(i=1; i<n; i++)
		for(j=0; j<n; j++)
			y[i][j] = y[i-1][j+1] - y[i-1][j];
	
	dline(20*n);
	printf("  x\t\ty");
	for(i=0;i<n-1;i++)
		printf("\t\t%c^%d y", 30, i+1);
	dline(20*n);
	for(i=0;i<n;i++) {
		printf(" %lf  \t", x[i]);
		for(j=0;j<n-i;j++)
			printf("%lf  \t", y[j][i]);
		
		printf("\n");
	}
	
	for(i=1;i<n-z;i++)
		fdx += (pow(-1, i+1)*y[i][z]/i);
	
	fdx /= h;
	
	printf("\n f'(%.2lf) = %.4lf (approx.) ", x0, fdx);
}

void dline(int x) {
	printf("\n ");
	while(x>0) {
		printf("-");
		x--;
	}
	printf("\n");
}