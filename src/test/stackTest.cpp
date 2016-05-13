#include "gmock/gmock.h"
#include "../ComplexNumber.h"
#include "../Ray.h"
#include "../Layer.h"
#include "../HitPoint.h"
#include "../LayerStack.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include <iostream>

using namespace testing;
//using namespace std;

class OpticStack: public testing::Test {
public:

//members:
	Layer air;
	Layer glass;
	Layer si;

	Ray laser;
	Ray laser25deg;

	double rpOne, rsOne, rpOne25deg, rsOne25deg;
	double rpTwo, rsTwo, rpTwo25deg, rsTwo25deg;
	double rpThree, rsThree, rpThree25deg, rsThree25deg;

	LayerStack singleLayer;
	LayerStack twoLayers;
	LayerStack threeLayers;

//constructor:
	OpticStack(): air(0, {1.0, 0.0}, 0.0),
			glass(1, {1.5, 0.0}, 0.1),
			si(2, {3.4, 0.4}, 1.0),
			laser(0.0, 1.0, 1.0, 0.0, 0.632, true, 0),
			laser25deg(25.0, 1.0, 1.0, 0.0, 0.632, true, 0) {

		boost::ptr_vector<Layer> vStack;

//first layer
		vStack.push_back(new Layer{air});
		singleLayer.Solve(vStack, laser, rpOne, rsOne);
		singleLayer.Solve(vStack, laser25deg, rpOne25deg, rsOne25deg);

//second layer
		vStack.push_back(new Layer{glass});
		twoLayers.Solve(vStack, laser, rpTwo, rsTwo);
		twoLayers.Solve(vStack, laser25deg, rpTwo25deg, rsTwo25deg);

//third layer
		vStack.push_back(new Layer{si});
		threeLayers.Solve(vStack, laser, rpThree, rsThree);
		threeLayers.Solve(vStack, laser, rpThree25deg, rsThree25deg);
};

//deconstructor:
	~OpticStack() {};
};

TEST_F(OpticStack, ReflectionRp0degLayersLessThan2) {
	ASSERT_DOUBLE_EQ(rpOne, 0.0);
}

TEST_F(OpticStack, ReflectionRs0degLayersLessThan2) {
	ASSERT_DOUBLE_EQ(rsOne, 0.0);
}

TEST_F(OpticStack, ReflectionRp25degLayersLessThan2) {
	ASSERT_DOUBLE_EQ(rpOne25deg, 0.0);
}

TEST_F(OpticStack, ReflectionRs25degLayersLessThan2) {
	ASSERT_DOUBLE_EQ(rsOne25deg, 0.0);
}

TEST_F(OpticStack, ReflectionRp0degTwoLayers) {
	ASSERT_DOUBLE_EQ(rpTwo, 0.04);
}

TEST_F(OpticStack, ReflectionRs0degTwoLayers) {
	ASSERT_DOUBLE_EQ(rsTwo, 0.04);
}

TEST_F(OpticStack, ReflectionRp25degTwoLayers) {
	ASSERT_NEAR(rpTwo25deg, 0.0297493, 0.0000001);
}

TEST_F(OpticStack, ReflectionRs25degTwoLayers) {
	ASSERT_NEAR(rsTwo25deg, 0.0516235, 0.0000001);
}

TEST_F(OpticStack, ReflectionRp0degThreeLayers) {
	ASSERT_NEAR(rpThree, 0.04332, 0.00001);
}

TEST_F(OpticStack, ReflectionRs0degThreeLayers) {
	ASSERT_NEAR(rsThree,  0.04332, 0.0001);
}

TEST_F(OpticStack, ReflectionRp25degThreeLayers) {
	ASSERT_NEAR(rpThree25deg, 0.04452, 0.0001);
}

TEST_F(OpticStack, ReflectionRs25degThreeLayers) {
	ASSERT_NEAR(rsThree25deg, 0.05109, 0.0001);
}
