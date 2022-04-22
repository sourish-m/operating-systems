#include<stdio.h>
#include<math.h>
#include<stdlib.h>
double func(double, double);

int main() {
    double x0, x1, y0, y1, yn_0, a, n, h, f, f1;
    int i, count, flag;
    
    printf("\n ------ Modified Euler's Method ------");
    printf("\n f(x, y) = x^2 + y\n");
    printf("\n Enter x0: ");
    scanf("%lf", &x0);
    printf("\n Enter y0: ");
    scanf("%lf", &y0);
    printf("\n Enter h: ");
    scanf("%lf", &h);
    printf("\n Enter value of x for which y is to be found: ");
    scanf("%lf", &n);
    for(x1=x0+h, i=1; x1<=n; x1+=h, i++) {
    	count = 0;
    	flag = 0;
    	f = func(x0, y0);
    	yn_0 = y0 + h*f;
    	printf("\n\n y%d_0 = %lf", i, yn_0);
    	do {
    		count++;
    		f = func(x0, y0);
    		f1 = func(x1, yn_0);
    		y1 = y0 + h/2 * (f + f1);
    		printf("\n\n x = %.3lf => y%d_%d = %lf", x1, i, count, y1);
    		if(fabs(y1-yn_0)<0.00001) {
    			printf("\n\n y%d = %lf\n\n", i, y1);
    			flag = 1;
			}
			else
				yn_0 = y1;
		}while(!flag);
		y0 = y1;
	}
	printf("\n\n y(%.2lf): %lf", n, y1);
}

double func(double x, double y) {	return pow(x, 2) + y;}