#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
double func(double, double);

int main() {
    double x, y, h, n, xf;
    int i;
    
    printf("\n ------ Euler's Method ------");
    printf("\n f(x, y) = x^3 + y\n");
    printf("\n Enter initial x: ");
    scanf("%lf", &x);
    printf("\n Enter initial f(x): ");
    scanf("%lf", &y);
    printf("\n Enter h: ");
    scanf("%lf", &h);
    printf("\n Enter value of x for which y is to be found: ");
    scanf("%lf", &xf);
    n = (xf-x)/h;
    for(i=1; i<=(int)n; i++) {
    	y += (h*func(x, y));
    	x += h;
	}
	printf("\n\n y(%.2lf) = %lf", xf, y);
}

double func(double x, double y) {	return pow(x, 2)*y+1;}