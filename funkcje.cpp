#include<stdlib.h>
#include<stdio.h>
#include"funkcje.h"
#include"Particle.h"
#include<cmath>
#define M_PI 3.14159265358979323846
double function(double x, double y)
{
	return x * x + y * y - 20 * (cos(M_PI*x) + cos(M_PI*y) - 2);
}