/* Copyright (C) 2016 Szymon Lis		email: szymonlis@yahoo.com
 *						Twitter: @drSzymonLis
 *
 * This class is designed to solve complex number arithmetics
 *
 *
 * This program is distibuteted for free, but WITHOUT ANY WARRANTY
 */


#ifndef ComplexNumber_h
#define ComplexNumber_h


#ifndef MY_PI
#define MY_PI 3.141592653589793238
#endif

#ifndef DEG_TO_RAD
#define DEG_TO_RAD(x) (x*MY_PI)/(180)
#endif

#ifndef RAD_TO_DEG
#define RAD_TO_DEG(x) (x*180)/(MY_PI)
#endif

struct COMPLEX {

public:
	double real, imag;

	COMPLEX() { real = 0.0; imag = 0.0; }
	COMPLEX(double x) { real = x; imag = 0.0; }
	COMPLEX(double x, double y) { real = x, imag = y; }
};


class ComplexNumber {

public:

//copy equal value
	COMPLEX Equality(COMPLEX complex) const {
		return complex;
	}

//conjugation
	COMPLEX Conjugate(COMPLEX complex) const {
		return COMPLEX(complex.real, -1.0*complex.imag);
	}

//magnitude
	double Magnitude(COMPLEX complex) const {
		return  sqrt(complex.real*complex.real + complex.imag*complex.imag);
	}

//phase
	double Phase(COMPLEX complex) const {
		if(complex.real == 0.0 && complex.imag == 0.0)
			return 0.0;

		if(complex.real == 0.0 && complex.imag > 0.0)
			return DEG_TO_RAD(90);

		if(complex.real == 0.0 && complex.imag < 0.0)
			return DEG_TO_RAD(-90);

		return atan(complex.imag/complex.real);
	}

//addition
	COMPLEX Add(COMPLEX a, double b) {
		return COMPLEX(a.real + b, a.imag);
	}

	COMPLEX Add(double a, COMPLEX b) {
		return COMPLEX(a + b.real, b.imag);
	}

	COMPLEX Add(COMPLEX a, COMPLEX b) {
		return COMPLEX(a.real + b.real, a.imag + b.imag);
	}

//substraction
	COMPLEX Sub(COMPLEX a, double b) {
		return COMPLEX(a.real - b, a.imag);
	}

	COMPLEX Sub(double a, COMPLEX b) {
		return COMPLEX(a - b.real, -b.imag);
	}

	COMPLEX Sub(COMPLEX a, COMPLEX b) {
		return COMPLEX(a.real - b.real, a.imag - b.imag);
	}


//multiplication
	COMPLEX Mul(COMPLEX a, COMPLEX b) {
		COMPLEX complex;
		complex.real = a.real * b.real - a.imag * b.imag;
		complex.imag = a.imag * b.real + a.real * b.imag;
		return complex;
	}

	COMPLEX Mul(COMPLEX a, double b) {
		return Mul(a, {b, 0.0});
	}

	COMPLEX Mul(double a, COMPLEX b) {
		return Mul({a, 0.0}, b);
	}

//devision
	COMPLEX Div(COMPLEX a, COMPLEX b) {
		COMPLEX complex;
		double  denominator;

		denominator = b.real * b.real + b.imag * b.imag;
		complex.real = (a.real * b.real + a.imag * b.imag)/denominator;
		complex.imag = (a.imag * b.real - a.real * b.imag)/denominator;

		return complex;
	}

	COMPLEX Div(COMPLEX a, double b) {
		return Div(a, {b, 0.0});
	}

	COMPLEX Div(double a, COMPLEX b) {
		return Div({a, 0.0}, b);
	}

//reciprocity
	COMPLEX Rec(COMPLEX a) {
		return Div(1.0, a);
	}


//squre root
	COMPLEX Sqr(COMPLEX a) {

		COMPLEX complex;
		complex.real = sqrt( (a.real + Magnitude(a))/2 );
		complex.imag = sqrt( (-a.real + Magnitude(a))/2 );
		if(a.imag<0.0) complex.imag *= -1.0;
		return complex;
	}
};

#endif
