#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

#include "rk4.h"

#define g 9.81 //acceleration of gravity

void rhsfun(double time, double* variables, double* derivatives)
{
	derivatives[0] = -variables[2] * variables[1] / variables[3] - variables[4] * g;
	derivatives[1] = variables[0];
}

void main()
{
	double variables[5], time, h, derivatives[2], Y1[2], Energy, k1, k2, end;

	printf("enter time frames\n");
	scanf("%lf%lf", &time, &end);
	printf("enter integration step\n");
	scanf("%lf", &h);
	printf("enter initial position and velocity(x0 and v0)\n");
	scanf("%lf%lf", &variables[1], &variables[0]);
	printf("enter spring's factors");
	scanf("%lf%lf", &k1, &k2);
	printf("enter object's mass and friction's factor");
	scanf("%lf%lf", &variables[3], &variables[4]);


	for (time; time < end; time += h)
	{
		variables[2] = k1 + k1 * k2 * variables[1] * variables[1];
		printf("%lf\n", variables[2]);
		vrk4(time, variables, h, 2, rhsfun, Y1);
		variables[0] = Y1[0];
		variables[1] = Y1[1];
	}

}