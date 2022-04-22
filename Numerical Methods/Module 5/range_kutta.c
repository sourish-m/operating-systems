#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double func(double, double);

int main() {
    double y0, x0, y1, n, h, f, k1, k2, k3, k4;
    
    printf("\n ------ Runge-Kutta Method ------");
    printf("\n f(x, y) = xy\n");
    printf("\n Enter the value of x0: ");
    scanf("%lf", &x0);
    printf(" Enter the value of y0: ");
    scanf("%lf", &y0);
    printf(" Enter the value of h: ");
    scanf("%lf", &h);
    printf("\n Enter the value of the last point: ");
    scanf("%lf", &n);
    for(; x0<n; x0+=h) {
        f = func(x0, y0);
        k1 = h * f;
        f = func(x0 + h/2, y0 + k1/2);
        k2 = h * f;
        f = func(x0 + h/2, y0 + k2/2);
        k3 = h * f;
        f = func(x0 + h, y0 + k3);
        k4 = h * f;
        y1 = y0 + (k1 + 2*k2 + 2*k3 + k4) / 6;
        printf("\n\n k1 = %.3lf", k1);
        printf("\n k2 = %.3lf", k2);
        printf("\n k3 = %.3lf", k3);
        printf("\n k4 = %.3lf", k4);
        printf("\n\n y(%.3lf) = %.3lf", x0+h, y1);
        y0 = y1;
    }
    return 0;
}

double func(double x, double y) {return x+y;}