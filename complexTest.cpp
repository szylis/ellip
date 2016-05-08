#include "gmock/gmock.h"
#include "ComplexNumber.h"

using namespace testing;

class ComplexNumberOperations: public testing::Test {
public:
	ComplexNumber complexNumber;
};

TEST_F(ComplexNumberOperations, EqualityOfComplex) {

	ASSERT_DOUBLE_EQ(complexNumber.Equality(COMPLEX(5.0, 3.0)).real, 5.0);
	ASSERT_DOUBLE_EQ(complexNumber.Equality(COMPLEX(5.0, 3.0)).imag, 3.0);
}

TEST_F(ComplexNumberOperations, ConjugateOfComplex) {
	
	ASSERT_DOUBLE_EQ(complexNumber.Conjugate(COMPLEX(5.0, 3.0)).real, 5.0);
	ASSERT_DOUBLE_EQ(complexNumber.Conjugate(COMPLEX(5.0, 3.0)).imag, -3.0);
}

TEST_F(ComplexNumberOperations, ConjugateOfReal) {
	
	ASSERT_DOUBLE_EQ(complexNumber.Conjugate(COMPLEX(-5.0)).real, -5.0);
	ASSERT_DOUBLE_EQ(complexNumber.Conjugate(COMPLEX(-5.0)).imag, 0.0);
}

TEST_F(ComplexNumberOperations, ConjugateOfImag) {
	
	ASSERT_DOUBLE_EQ(complexNumber.Conjugate(COMPLEX(0.0, -7.3)).real, 0.0);
	ASSERT_DOUBLE_EQ(complexNumber.Conjugate(COMPLEX(0.0, -7.3)).imag, 7.3);
}

TEST_F(ComplexNumberOperations, MagnitudeOfComplex) {

	ASSERT_DOUBLE_EQ(complexNumber.Magnitude(COMPLEX(3.2, 4.5)), sqrt(30.49));
}

TEST_F(ComplexNumberOperations, PhaseOfComplex) {

	ASSERT_DOUBLE_EQ(complexNumber.Phase(COMPLEX(2.0, 4.0)), atan(2.0));
	ASSERT_DOUBLE_EQ(complexNumber.Phase(COMPLEX(0.0, 4.0)), 90.0 * (MY_PI/180));
	ASSERT_DOUBLE_EQ(complexNumber.Phase(COMPLEX(0.0, -2.0)), -90 * (MY_PI/180));
}

TEST_F(ComplexNumberOperations, Addition) {
	
	ASSERT_DOUBLE_EQ(complexNumber.Add(COMPLEX(2.0, 3.0), COMPLEX(1.5, -0.4)).real, 3.5);
	ASSERT_DOUBLE_EQ(complexNumber.Add(COMPLEX(2.0, 3.0), COMPLEX(1.5, -0.4)).imag, 2.6);

	ASSERT_DOUBLE_EQ(complexNumber.Add(COMPLEX(5.4), COMPLEX(2.3, 0.8)).real, 7.7);
	ASSERT_DOUBLE_EQ(complexNumber.Add(COMPLEX(5.4), COMPLEX(2.3, 0.8)).imag, 0.8);

	ASSERT_DOUBLE_EQ(complexNumber.Add(COMPLEX(0.0, -5.0), COMPLEX(3.0)).real, 3.0);
	ASSERT_DOUBLE_EQ(complexNumber.Add(COMPLEX(0.0, -5.0), COMPLEX(3.0)).imag, -5.0); 
}

TEST_F(ComplexNumberOperations, Substraction) {
	
	ASSERT_DOUBLE_EQ(complexNumber.Sub(COMPLEX(2.0, 3.0), COMPLEX(1.5, -0.4)).real, 0.5);
	ASSERT_DOUBLE_EQ(complexNumber.Sub(COMPLEX(2.0, 3.0), COMPLEX(1.5, -0.4)).imag, 3.4);

	ASSERT_DOUBLE_EQ(complexNumber.Sub(COMPLEX(5.4), COMPLEX(2.3, 0.8)).real, 3.1);
	ASSERT_DOUBLE_EQ(complexNumber.Sub(COMPLEX(5.4), COMPLEX(2.3, 0.8)).imag, -0.8);

	ASSERT_DOUBLE_EQ(complexNumber.Sub(COMPLEX(0.0, -5.0), COMPLEX(3.0)).real, -3.0);
	ASSERT_DOUBLE_EQ(complexNumber.Sub(COMPLEX(0.0, -5.0), COMPLEX(3.0)).imag, -5.0); 
}

TEST_F(ComplexNumberOperations, Multipliction) {
	
	ASSERT_DOUBLE_EQ(complexNumber.Mul(COMPLEX(2.0, 3.0), COMPLEX(1.5, -0.4)).real, 4.2);
	ASSERT_DOUBLE_EQ(complexNumber.Mul(COMPLEX(2.0, 3.0), COMPLEX(1.5, -0.4)).imag, 3.7);

	ASSERT_DOUBLE_EQ(complexNumber.Mul(COMPLEX(5.4), COMPLEX(2.3, 0.8)).real, 12.42);
	ASSERT_DOUBLE_EQ(complexNumber.Mul(COMPLEX(5.4), COMPLEX(2.3, 0.8)).imag, 4.32);

	ASSERT_DOUBLE_EQ(complexNumber.Mul(COMPLEX(0.0, -5.0), COMPLEX(3.0)).real, 0.0);
	ASSERT_DOUBLE_EQ(complexNumber.Mul(COMPLEX(0.0, -5.0), COMPLEX(3.0)).imag, -15.0); 
}

TEST_F(ComplexNumberOperations, Division) {
	
	ASSERT_DOUBLE_EQ(complexNumber.Div(COMPLEX(2.0, 3.0), COMPLEX(1.5, -0.4)).real, 0.74688796680497915);
	ASSERT_DOUBLE_EQ(complexNumber.Div(COMPLEX(2.0, 3.0), COMPLEX(1.5, -0.4)).imag, 2.1991701244813275);

	ASSERT_DOUBLE_EQ(complexNumber.Div(COMPLEX(5.4), COMPLEX(2.3, 0.8)).real, 2.094435075885329);
	ASSERT_DOUBLE_EQ(complexNumber.Div(COMPLEX(5.4), COMPLEX(2.3, 0.8)).imag, -0.72849915682967969);

	ASSERT_DOUBLE_EQ(complexNumber.Div(COMPLEX(0.0, -5.0), COMPLEX(3.0)).real, 0.0);
	ASSERT_DOUBLE_EQ(complexNumber.Div(COMPLEX(0.0, -5.0), COMPLEX(3.0)).imag, -1.6666666666666667); 
}

TEST_F(ComplexNumberOperations, Reciprocal) {
	
	ASSERT_DOUBLE_EQ(complexNumber.Rec(COMPLEX(2.0, 3.0)).real, 0.1538461538461538);
	ASSERT_DOUBLE_EQ(complexNumber.Rec(COMPLEX(2.0, 3.0)).imag, -0.2307692307692307);

	ASSERT_DOUBLE_EQ(complexNumber.Rec(COMPLEX(5.4)).real, 0.185185185185185185);
	ASSERT_DOUBLE_EQ(complexNumber.Rec(COMPLEX(5.4)).imag, 0.0);

	ASSERT_DOUBLE_EQ(complexNumber.Rec(COMPLEX(0.0, -5.0)).real, 0.0);
	ASSERT_DOUBLE_EQ(complexNumber.Rec(COMPLEX(0.0, -5.0)).imag, 0.2); 
}

TEST_F(ComplexNumberOperations, SquareRoot) {
	
	ASSERT_DOUBLE_EQ(complexNumber.Sqr(COMPLEX(2.0, 3.0)).real, 1.674149228035540040);
	ASSERT_DOUBLE_EQ(complexNumber.Sqr(COMPLEX(2.0, 3.0)).imag, 0.895977476129838124);

	ASSERT_DOUBLE_EQ(complexNumber.Sqr(COMPLEX(-2.0, -3.0)).real, 0.895977476129838124);
	ASSERT_DOUBLE_EQ(complexNumber.Sqr(COMPLEX(-2.0, -3.0)).imag, -1.674149228035540040);

	ASSERT_DOUBLE_EQ(complexNumber.Sqr(COMPLEX(9.0)).real, 3.0);
	ASSERT_DOUBLE_EQ(complexNumber.Sqr(COMPLEX(9.0)).imag, 0.0);

	ASSERT_DOUBLE_EQ(complexNumber.Sqr(COMPLEX(-5.4)).real, 0.0);
	ASSERT_DOUBLE_EQ(complexNumber.Sqr(COMPLEX(-5.4)).imag, 2.3237900077244501311);

	ASSERT_DOUBLE_EQ(complexNumber.Sqr(COMPLEX(0.0, -5.0)).real, 1.581138830084189665);
	ASSERT_DOUBLE_EQ(complexNumber.Sqr(COMPLEX(0.0, -5.0)).imag, -1.581138830084189665); 
}
