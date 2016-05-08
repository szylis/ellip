#ifndef ComplexNumber_h
#define ComplexNumber_h

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
};

#endif
