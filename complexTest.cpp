#include "gmock/gmock.h"
#include "ComplexNumber.h"

using namespace testing;

class ComplexNumberOperations: public testing::Test {
public:
	ComplexNumber complexNumber;
};

TEST_F(ComplexNumberOperations, EqualityOfComplex) {

	ASSERT_THAT(complexNumber.Equality(COMPLEX(5.0, 3.0)).real, Eq(5.0));
	ASSERT_THAT(complexNumber.Equality(COMPLEX(5.0, 3.0)).imag, Eq(3.0));
}

TEST_F(ComplexNumberOperations, ConjugateOfComplex) {
	
	ASSERT_THAT(complexNumber.Conjugate(COMPLEX(5.0, 3.0)).real, Eq(5.0));
	ASSERT_THAT(complexNumber.Conjugate(COMPLEX(5.0, 3.0)).imag, Eq(-3.0));
}

TEST_F(ComplexNumberOperations, ConjugateOfReal) {
	
	ASSERT_THAT(complexNumber.Conjugate(COMPLEX(-5.0)).real, Eq(-5.0));
	ASSERT_THAT(complexNumber.Conjugate(COMPLEX(-5.0)).imag, Eq(0.0));
}

TEST_F(ComplexNumberOperations, ConjugateOfImag) {
	
	ASSERT_THAT(complexNumber.Conjugate(COMPLEX(0.0, -7.3)).real, Eq(0.0));
	ASSERT_THAT(complexNumber.Conjugate(COMPLEX(0.0, -7.3)).imag, Eq(7.3));
}

TEST_F(ComplexNumberOperations, MagnitudeOfComplex) {

	ASSERT_THAT(complexNumber.Magnitude(COMPLEX(3.2, 4.5)), Eq(sqrt(30.49)));
}

TEST_F(ComplexNumberOperations, PhaseOfComplex) {

	ASSERT_THAT(complexNumber.Phase(COMPLEX(2.0, 4.0)), Eq(atan(2.0)));
	ASSERT_THAT(complexNumber.Phase(COMPLEX(0.0, 4.0)), Eq(90.0 * (MY_PI/180)));
	ASSERT_THAT(complexNumber.Phase(COMPLEX(0.0, -2.0)), Eq(-90 * (MY_PI/180)));
}
