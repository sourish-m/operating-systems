#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void result();
float coef[3][4], x1, x2, x3, m;
int i, j;

int main()
{
	for(i=0;i<3;i++)
	{
		printf("\n Enter coefficients for equation %d\n", i+1);
		for(j=0;j<3;j++)
		{
			printf(" Coefficient of x%d: ", j+1);
			scanf("%f", &coef[i][j]);
		}
		printf(" Enter constant: ");
		scanf("%f", &coef[i][3]);
	}
	
	system("cls");
	printf("\n System of equations:\n");
	for(i=0;i<3;i++)
	{
		printf("\n ");
		for(j=0;j<3;j++)
		{
			printf("%.0fx%d", coef[i][j], j+1);
			
			if(j<2)
			printf(" + ");
		}
		printf(" = %.0f", coef[i][3]);
	}
	
	result();
	printf("\n\n The solution is:\n x1 = %.3f\n x2 = %.3f\n x3 = %.3f", x1, x2, x3);
}

void result()
{
	for(i=1;i<3;i++)
	{
		m=-(coef[i][0]/coef[0][0]);
		for(j=0;j<4;j++)
		{
			coef[i][j]+=m*coef[0][j];
		}
	}
	
	m=-(coef[2][1]/coef[1][1]);
	for(j=1;j<4;j++)
	{
		coef[2][j]+=m*coef[1][j];
	}
	
	x3=coef[2][3]/coef[2][2];
	x2=(coef[1][3]-coef[1][2]*x3)/coef[1][1];
	x1=(coef[0][3]-coef[0][2]*x3-coef[0][1]*x2)/coef[0][0];
}
