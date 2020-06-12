#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

#include "rk4.h"

#define g 9.81 //acceleration of gravity

void rhsfun(double time, double* variables, double* derivatives, double* stables)
{
	if (variables[1] > 0)
		derivatives[1] = (-stables[0] - stables[1] * stables[0] * variables[0] * variables[0]) * variables[0] / stables[2] - stables[3] * g;
	else
		derivatives[1] = (-stables[0] - stables[1] * stables[0] * variables[0] * variables[0]) * variables[0] / stables[2] + stables[3] * g;
	derivatives[0] = variables[1];
}

void main()
{	
	double variables[2], stables [4], time, h, derivatives[2], Y1[2], Energy,end;

	printf("enter time frames\n");
	scanf("%lf%lf", &time, &end);
	printf("enter integration step\n");
	scanf("%lf", &h);
	printf("enter initial position and velocity(x0 and v0)\n");
	scanf("%lf%lf", &variables[0], &variables[1]);
	printf("enter spring's factors");
	scanf("%lf%lf", &stables[0], &stables[1]);
	printf("enter object's mass and friction's factor");
	scanf("%lf%lf", &stables[2], &stables[3]);
	Energy = stables[2] * variables[1] * variables[1] / 2 + (stables[0] + stables[1] * stables[0] * variables[0] * variables[0]) * variables[0] * variables[0] / 2 - stables[3] * stables[2] * g;
	printf("%lf\n", Energy);
	FILE* f;
	f = fopen("wyniki1.txt", "a");
	double a;
	for (time; time < end; time += h)
	{
		//a = stables[0] + stables[1] * stables[0] * variables[0] * variables[0];
		
		vrk4(time, variables, h, 2, rhsfun, Y1, stables);
		variables[0] = Y1[0];
		variables[1] = Y1[1];
		fprintf(f, "%lf\t%lf\t%lf\t%lf\n", time, Y1[0], Y1[1], Energy);
		if(variables[1]>0)
			Energy = stables[2] * variables[1] * variables[1] / 2 + (stables[0] + stables[1] * stables[0] * variables[0] * variables[0]) * variables[0] * variables[0] / 2;
		else
			Energy = stables[2] * variables[1] * variables[1] / 2 - (stables[0] + stables[1] * stables[0] * variables[0] * variables[0]) * variables[0] * variables[0] / 2;

		printf("%lf\n", Energy);
		
	}

}