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

//conjugation tests
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

//magnitude tests
TEST_F(ComplexNumberOperations, MagnitudeOfComplex) {

	ASSERT_DOUBLE_EQ(complexNumber.Magnitude(COMPLEX(3.2, 4.5)), sqrt(30.49));
}

//phase tests
TEST_F(ComplexNumberOperations, PhaseOfComplex) {

	ASSERT_DOUBLE_EQ(complexNumber.Phase(COMPLEX(2.0, 4.0)), atan(2.0));
	ASSERT_DOUBLE_EQ(complexNumber.Phase(COMPLEX(0.0, 4.0)), 90.0 * (MY_PI/180));
	ASSERT_DOUBLE_EQ(complexNumber.Phase(COMPLEX(0.0, -2.0)), -90 * (MY_PI/180));
}


//addition tests
TEST_F(ComplexNumberOperations, AdditionTwoComplex) {
	
	ASSERT_DOUBLE_EQ(complexNumber.Add(COMPLEX(2.0, 3.0), COMPLEX(1.5, -0.4)).real, 3.5);
	ASSERT_DOUBLE_EQ(complexNumber.Add(COMPLEX(2.0, 3.0), COMPLEX(1.5, -0.4)).imag, 2.6);

	ASSERT_DOUBLE_EQ(complexNumber.Add(COMPLEX(5.4), COMPLEX(2.3, 0.8)).real, 7.7);
	ASSERT_DOUBLE_EQ(complexNumber.Add(COMPLEX(5.4), COMPLEX(2.3, 0.8)).imag, 0.8);

	ASSERT_DOUBLE_EQ(complexNumber.Add(COMPLEX(0.0, -5.0), COMPLEX(3.0)).real, 3.0);
	ASSERT_DOUBLE_EQ(complexNumber.Add(COMPLEX(0.0, -5.0), COMPLEX(3.0)).imag, -5.0); 
}

TEST_F(ComplexNumberOperations, AdditionComplexDouble) {
	
	ASSERT_DOUBLE_EQ(complexNumber.Add(COMPLEX(2.0, 2.0), 4.4).real, 6.4);
	ASSERT_DOUBLE_EQ(complexNumber.Add(COMPLEX(2.0, 2.0), 4.4).imag, 2.0);

	ASSERT_DOUBLE_EQ(complexNumber.Add(3.5, COMPLEX(1.2, -4.0)).real, 4.7);
	ASSERT_DOUBLE_EQ(complexNumber.Add(3.5, COMPLEX(1.2, -4.0)).imag, -4.0);
} 

//substraction tests
TEST_F(ComplexNumberOperations, SubstractionTwoComplex) {
	
	ASSERT_DOUBLE_EQ(complexNumber.Sub(COMPLEX(2.0, 3.0), COMPLEX(1.5, -0.4)).real, 0.5);
	ASSERT_DOUBLE_EQ(complexNumber.Sub(COMPLEX(2.0, 3.0), COMPLEX(1.5, -0.4)).imag, 3.4);

	ASSERT_DOUBLE_EQ(complexNumber.Sub(COMPLEX(5.4), COMPLEX(2.3, 0.8)).real, 3.1);
	ASSERT_DOUBLE_EQ(complexNumber.Sub(COMPLEX(5.4), COMPLEX(2.3, 0.8)).imag, -0.8);

	ASSERT_DOUBLE_EQ(complexNumber.Sub(COMPLEX(0.0, -5.0), COMPLEX(3.0)).real, -3.0);
	ASSERT_DOUBLE_EQ(complexNumber.Sub(COMPLEX(0.0, -5.0), COMPLEX(3.0)).imag, -5.0); 
}

TEST_F(ComplexNumberOperations, SubstractionComplexDouble) {
	
	ASSERT_DOUBLE_EQ(complexNumber.Sub(COMPLEX(2.0, 3.0), 7.5).real, -5.5);
	ASSERT_DOUBLE_EQ(complexNumber.Sub(COMPLEX(2.0, 3.0), 7.5).imag, 3.0);

	ASSERT_DOUBLE_EQ(complexNumber.Sub(3.2, COMPLEX(2.3, 0.8)).real, 0.9);
	ASSERT_DOUBLE_EQ(complexNumber.Sub(3.2, COMPLEX(2.3, 0.8)).imag, -0.8);
}

//multiplication tests
TEST_F(ComplexNumberOperations, MultiplictionTwoComplex) {
	
	ASSERT_DOUBLE_EQ(complexNumber.Mul(COMPLEX(2.0, 3.0), COMPLEX(1.5, -0.4)).real, 4.2);
	ASSERT_DOUBLE_EQ(complexNumber.Mul(COMPLEX(2.0, 3.0), COMPLEX(1.5, -0.4)).imag, 3.7);

	ASSERT_DOUBLE_EQ(complexNumber.Mul(COMPLEX(5.4), COMPLEX(2.3, 0.8)).real, 12.42);
	ASSERT_DOUBLE_EQ(complexNumber.Mul(COMPLEX(5.4), COMPLEX(2.3, 0.8)).imag, 4.32);

	ASSERT_DOUBLE_EQ(complexNumber.Mul(COMPLEX(0.0, -5.0), COMPLEX(3.0)).real, 0.0);
	ASSERT_DOUBLE_EQ(complexNumber.Mul(COMPLEX(0.0, -5.0), COMPLEX(3.0)).imag, -15.0); 
}

TEST_F(ComplexNumberOperations, MultiplictionComplexDouble) {
	
	ASSERT_DOUBLE_EQ(complexNumber.Mul(COMPLEX(2.0, 3.0), 4.0).real, 8.0);
	ASSERT_DOUBLE_EQ(complexNumber.Mul(COMPLEX(2.0, 3.0), 4.0).imag, 12.0);

	ASSERT_DOUBLE_EQ(complexNumber.Mul(-3.2, COMPLEX(5.4, 3.3)).real, -17.28);
	ASSERT_DOUBLE_EQ(complexNumber.Mul(-3.2, COMPLEX(5.4, 3.3)).imag, -10.56);

}

//devision tests
TEST_F(ComplexNumberOperations, DivisionTwoComplex) {

	ASSERT_DOUBLE_EQ(complexNumber.Div(COMPLEX(2.0, 3.0), COMPLEX(1.5, -0.4)).real, 0.74688796680497915);
	ASSERT_DOUBLE_EQ(complexNumber.Div(COMPLEX(2.0, 3.0), COMPLEX(1.5, -0.4)).imag, 2.1991701244813275);

	ASSERT_DOUBLE_EQ(complexNumber.Div(COMPLEX(5.4), COMPLEX(2.3, 0.8)).real, 2.094435075885329);
	ASSERT_DOUBLE_EQ(complexNumber.Div(COMPLEX(5.4), COMPLEX(2.3, 0.8)).imag, -0.72849915682967969);

	ASSERT_DOUBLE_EQ(complexNumber.Div(COMPLEX(0.0, -5.0), COMPLEX(3.0)).real, 0.0);
	ASSERT_DOUBLE_EQ(complexNumber.Div(COMPLEX(0.0, -5.0), COMPLEX(3.0)).imag, -1.6666666666666667); 
}

TEST_F(ComplexNumberOperations, DivisionComplexDouble) {

	ASSERT_DOUBLE_EQ(complexNumber.Div(COMPLEX(2.0, 3.0), 2.3).real, 0.86956521739130434);
	ASSERT_DOUBLE_EQ(complexNumber.Div(COMPLEX(2.0, 3.0), 2.3).imag, 1.30434782608695652);

	ASSERT_DOUBLE_EQ(complexNumber.Div(5.4, COMPLEX(2.3, 0.8)).real, 2.094435075885329);
	ASSERT_DOUBLE_EQ(complexNumber.Div(5.4, COMPLEX(2.3, 0.8)).imag, -0.72849915682967969);

}


//reciprocity tests
TEST_F(ComplexNumberOperations, Reciprocal) {
	
	ASSERT_DOUBLE_EQ(complexNumber.Rec(COMPLEX(2.0, 3.0)).real, 0.1538461538461538);
	ASSERT_DOUBLE_EQ(complexNumber.Rec(COMPLEX(2.0, 3.0)).imag, -0.2307692307692307);

	ASSERT_DOUBLE_EQ(complexNumber.Rec(COMPLEX(5.4)).real, 0.185185185185185185);
	ASSERT_DOUBLE_EQ(complexNumber.Rec(COMPLEX(5.4)).imag, 0.0);

	ASSERT_DOUBLE_EQ(complexNumber.Rec(COMPLEX(0.0, -5.0)).real, 0.0);
	ASSERT_DOUBLE_EQ(complexNumber.Rec(COMPLEX(0.0, -5.0)).imag, 0.2); 
}

//square root tests
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
