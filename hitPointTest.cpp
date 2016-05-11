#include "gmock/gmock.h"
#include "ComplexNumber.h"
#include "HitPoint.h"
#include "Ray.h"
#include "Layer.h"

using namespace testing;

class RayHitPoint: public testing::Test {
public:

//members:
	Layer glass;
	Ray rInc;
	Ray rRefl;
	Ray rRefr;

//construtor:
	RayHitPoint(): glass({1.45, 0.0}, 0.2), rInc(30.0), rRefl(45.0), rRefr() {

		HitPoint hitPoint(rInc, glass, rRefl, rRefr);
	};

//deconstructor:
	~RayHitPoint() {};


};

TEST_F(RayHitPoint, Constructor) {
	ASSERT_DOUBLE_EQ(rInc.GetRayAngle(), rRefl.GetRayAngle());
}

