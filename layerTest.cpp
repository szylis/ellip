#include "gmock/gmock.h"
#include "ComplexNumber.h"
#include "Layer.h"

using namespace testing;

class OpticLayer: public testing::Test {
public:
	Layer layer;

};

TEST_F(OpticLayer, GetRefractiveIndex) {

	Layer glass(1, {1.45, 0.0}, 0.2);

	ASSERT_DOUBLE_EQ(glass.GetRefractiveIndex().real, 1.45);
	ASSERT_DOUBLE_EQ(glass.GetRefractiveIndex().imag, 0.0);
}

TEST_F(OpticLayer, SetRefractiveIndex) {

	layer.SetRefractiveIndex({2.1, 0.2});
	
	ASSERT_DOUBLE_EQ(layer.GetRefractiveIndex().real, 2.1);
	ASSERT_DOUBLE_EQ(layer.GetRefractiveIndex().imag, 0.2);
}

TEST_F(OpticLayer, GetPositionNumber) {

	Layer glass(3, {1.45, 0.0}, 0.4);
	ASSERT_EQ(glass.GetPosition(), 3);
}

TEST_F(OpticLayer, SetPositionNumber) {
	
	layer.SetPosition(1);
	ASSERT_EQ(layer.GetPosition(), 1);
}

TEST_F(OpticLayer, GetThickness) {

	Layer glass(2, {1.45, 0.0}, 0.2);

	ASSERT_DOUBLE_EQ(glass.GetThickness(), 0.2);
}

TEST_F(OpticLayer, SetThickness) {
	
	layer.SetThickness(0.5);

	ASSERT_DOUBLE_EQ(layer.GetThickness(), 0.5);
}
