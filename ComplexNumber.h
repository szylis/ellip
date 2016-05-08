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

	COMPLEX Addition() {
		return COMPLEX();
	}

	COMPLEX Subtraction() {
		return COMPLEX();
	}

	COMPLEX Multiplication() {
		return COMPLEX ();
	}

	COMPLEX Division() {
		return COMPLEX ();
	}

	COMPLEX Reciprocal() {
		return COMPLEX ();
	}

	COMPLEX SquareRoot() {
		return COMPLEX ();
	}
};

#endif
