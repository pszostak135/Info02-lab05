#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "winbgi2.h"
#include "rk4.h"

double g=9.81;
double l=5;
double m=1;

void rhs_fun(double t, double *X, double *F)
{
	F[0]= X[1];
	F[1]= -g/l*sin(X[0]);
}

void veuler(double t, double *X, double h, int n, void (*rhs_fun)(double, double *,double *), double *X1)
{
	    double F[2];		
		rhs_fun(t, X,F);
		X1[0]=X[0]+h*F[0];
		X1[1]=X[1]+h*F[1];
		X[0]=X1[0];
		X[1]=X1[1];
}

void main()
{
	double h=0.0001;
	double X[2];
	double X1[2];
	X[0]=3.14/2;
	X[1]=0;
	double kat;
	double E;

	graphics(800,800);
	scale(-3,-7,3,7);

	for(double i=0;i<10+h;i+=h)
	{
		
		veuler(0,X, h, 2, rhs_fun, X1);
		kat=X1[0]*360/(2*3.14);
		E=(m*pow(l,2)*pow(X1[1],2))/2+m*g*l*(1-cos(X1[0]));
		point(X1[0],X1[1]);
		printf( "%.2lf\t %.2lf\t %.2lf\n ", kat, X1[1], E);	
	}

	X[0]=3.14/2;
	X[1]=0;

		for(double i=0;i<10+h;i+=h)
	{
		vrk4(0,X, h, 2, rhs_fun, X1);
		X[0]=X1[0];
		X[1]=X1[1];
		kat=X1[0]*360/(2*3.14);
		//E=(m*pow(l,2)*pow(X1[1],2))/2+m*g*l*(1-cos(X1[0]));
		//point(X1[0],X1[1]);
		printf( "%.2lf\t %.2lf\t %.2lf\n ", kat, X1[1], E);
	}
		
	wait();
}