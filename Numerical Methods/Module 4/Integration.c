#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double trapezoidal(double, double, int);
double simpson(double, double, int);
//double trapezoidal(double, double, int, FILE*);
//double simpson(double, double, int, FILE*);
double func(double);

int main() {
	int n, opt;
	double a, b;
//	FILE *fptr;
//	fptr=fopen("Integration.txt", "w");
	
	printf("\n Enter lower limit: ");
	scanf("%lf", &a);
	printf("\n Enter upper limit: ");
	scanf("%lf", &b);
	printf("\n Enter number of intervals: ");
	scanf("%d", &n);
	
	printf("\n 1. Tapezoidal rule \n 2. Simpson's 1/3rd rule \n");
	flag:
	printf("\n Enter choice: ");
	scanf("%d", &opt);
	switch(opt) {
		case 1:
//			system("cls");
//			fprintf(fptr, "\n Approx value of integral of the function is %lf \n", trapezoidal(a, b, n, fptr));
			printf("\n Approx. value of integral of the function is %lf \n", trapezoidal(a, b, n));
//			printf("\n File has been edited");
			break;
		case 2:
//			system("cls");
//			fprintf(fptr, "\n Approx value of integral of the function is %lf \n", simpson(a, b, n, fptr));
			printf("\n Approx. value of integral of the function is %lf \n", simpson(a, b, n));
//			printf("\n File has been edited");
			break;
		default:
			printf("\n Wrong input\n");
			goto flag;
	}
//	fclose(fptr);
}

double trapezoidal(double a, double b, int n) {
	int i;
	double h, x[100], y[100], sum=0, I;
	
	h=(b-a)/n;
	
//	fprintf(fptr, "\n Trapezoidal Rule\n");
//	fprintf(fptr, "\n Function: sqrt(cos(x))\n\n   x[i] \t\t\t   y[i]\n");
	printf("\n ------ Trapezoidal Rule ------\n");
	printf("\n Function: 1/(1+x^2)\n\n   x[i] \t\t\t   y[i]\n");
	for(i=0;i<=n;i++) {
		x[i]=a+i*h;
		y[i]=func(x[i]); //function
		sum+=y[i];
//		fprintf(fptr, " %lf  \t\t\t %lf \n", x[i], y[i]);
		printf(" %lf  \t\t\t %lf \n", x[i], y[i]);
	}
	
	I=(h/2)*(y[0]+y[n]+2*(sum-(y[0]+y[n])));
	return I;
}

double simpson(double a, double b, int n) {
	int i;
	double h, x[100], y[100], sumo=0, sume=0, I;
	
	h=(b-a)/n;
	
//	fprintf(fptr, "\n Simpson's 1/3rd Rule\n");
//	fprintf(fptr, "\n Function: sqrt(cos(x))\n\n   x[i] \t\t\t   y[i]\n");
	printf("\n ------ Simpson's 1/3rd Rule ------\n");
	printf("\n Function: x/(1+x)\n\n   x[i] \t\t\t   y[i]\n");
	
	for(i=0;i<=n;i++) {
		x[i]=a+i*h;
		y[i]=func(x[i]);
		
		if(i%2==0 && i!=0 && i!=n)
		sume+=y[i];
		else if(i%2!=0 && i!=0 && i!=n)
		sumo+=y[i];
		
//		fprintf(fptr, " %lf  \t\t\t %lf \n", x[i], y[i]);
		printf(" %lf  \t\t\t %lf \n", x[i], y[i]);
	}
	
	I=(h/3)*(y[0]+y[n]+4*sumo+2*sume);
	return I;
}

double func(double x) {
//	return 1/(1+x*x);
//	return x/(1+x);
	return exp(x);
}
