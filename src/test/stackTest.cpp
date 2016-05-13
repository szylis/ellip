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

	double rp, rs;

	LayerStack layerStack;

//constructor:
	OpticStack(): air(0, {1.0, 0.0}, 0.0),
			glass(1, {1.5, 0.0}, 0.1),
			si(2, {3.4, 0.4}, 1.0), 
			laser(0.0, 1.0, 1.0, 0.0, 0.632, true, 0) {

		boost::ptr_vector<Layer> vStack;
		vStack.push_back(new Layer{air});
		vStack.push_back(new Layer{glass});
		vStack.push_back(new Layer{si});

		layerStack.Solve(vStack, laser, rp, rs);
};

//deconstructor:
	~OpticStack() {};
};

TEST_F(OpticStack, FirstTest) {
	ASSERT_DOUBLE_EQ(rp, laser.GetRayAmp_p());
}

TEST_F(OpticStack, See) {
	ASSERT_DOUBLE_EQ(rs, laser.GetRayAmp_s());
}
