#ifndef ComplexNumber_h
#define ComplexNumber_h


#ifndef MY_PI
#define MY_PI 3.141592653589793238
#endif 

//#include <math.h>

struct COMPLEX {
	double real, imag;

	COMPLEX() {
		real = 0; imag = 0;
	}

	COMPLEX(double x) {
		real = x; imag = 0;
	}

	COMPLEX(double x, double y) {
		real = x, imag = y;
	}
};

class ComplexNumber {

public:

	COMPLEX Equality(COMPLEX complex) const {
		return complex;
	}

	COMPLEX Conjugate(COMPLEX complex) const {
		return COMPLEX(complex.real, -1.0*complex.imag);
	}

	double Magnitude(COMPLEX complex) const {
		return  sqrt(complex.real*complex.real + complex.imag*complex.imag);
	}

	double Phase(COMPLEX complex) const {
		if(complex.real == 0 && complex.imag == 0)
			return 0;

		if(complex.real == 0 && complex.imag > 0)
			return 90 * (MY_PI/180);

		if(complex.real == 0 && complex.imag < 0)
			return -90 * (MY_PI/180);

		return atan(complex.imag/complex.real);
	}

	COMPLEX Add(COMPLEX a, COMPLEX b) {
		return COMPLEX(a.real + b.real, a.imag + b.imag);
	}

	COMPLEX Sub(COMPLEX a, COMPLEX b) {
		return COMPLEX(a.real - b.real, a.imag - b.imag);
	}

	COMPLEX Mul(COMPLEX a, COMPLEX b) {
		COMPLEX complex;
		complex.real = a.real * b.real - a.imag * b.imag;
		complex.imag = a.imag * b.real + a.real * b.imag;
		return complex;
	}

	COMPLEX Div(COMPLEX a, COMPLEX b) {
		COMPLEX complex;
		double  denominator;

		denominator = b.real * b.real + b.imag * b.imag;
		complex.real = (a.real * b.real + a.imag * b.imag)/denominator;
		complex.imag = (a.imag * b.real - a.real * b.imag)/denominator;

		return complex;
	}

	COMPLEX Rec(COMPLEX a) {
		return Div(COMPLEX(1.0), a);
	}

	COMPLEX Sqr(COMPLEX a) {

		COMPLEX complex;
		complex.real = sqrt( (a.real + Magnitude(a))/2 );
		complex.imag = sqrt( (-a.real + Magnitude(a))/2 );
		if(a.imag<0) complex.imag *= -1.0;
		return complex;
	}
};

#endif
