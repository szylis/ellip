#include "gmock/gmock.h"
#include "ComplexNumber.h"

using namespace testing;

class ComplexNumberOperations: public testing::Test {
public:
	ComplexNumber complexNumber;
};

TEST_F(ComplexNumberOperations, EqualityOfComplex) {

	COMPLEX complex(5.0, 3.0);

	ASSERT_THAT(complexNumber.Equality(complex).real, Eq(5.0));
	ASSERT_THAT(complexNumber.Equality(complex).imag, Eq(3.0));
}

TEST_F(ComplexNumberOperations, ConjugateOfComplex) {
	
	COMPLEX complex(5.0, 3.0);
	
	ASSERT_THAT(complexNumber.Conjugate(complex).real, Eq(5.0));
	ASSERT_THAT(complexNumber.Conjugate(complex).imag, Eq(-3.0));
}
