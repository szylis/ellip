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
	Ray inc;
	Ray refl;
	Ray refr;

//construtor:
	RayHitPoint(): glass({1.45, 0.0}, 0.2),
			inc(30.0, 1.0, 1.0, MY_PI*1.7),
			refl(0), refr() {

		HitPoint hitPoint(inc, glass, refl, refr);
	};

//deconstructor:
	~RayHitPoint() {};


};

TEST_F(RayHitPoint, ReflectionAngleCheck) {
	ASSERT_DOUBLE_EQ(refl.GetRayAngle(), inc.GetRayAngle());
}

TEST_F(RayHitPoint, ReflectionLayerCheck) {
	ASSERT_DOUBLE_EQ(refl.GetRayLayer(), inc.GetRayLayer());
}

TEST_F(RayHitPoint, ReflectionWavelength) {
	ASSERT_DOUBLE_EQ(refl.GetRayWavelength(), inc.GetRayWavelength());
} 

TEST_F(RayHitPoint, ReflectionPhase) {
	if(inc.GetRayPhase() > MY_PI) {
		ASSERT_DOUBLE_EQ(refl.GetRayPhase(), inc.GetRayPhase() - MY_PI); }
	else {
		ASSERT_DOUBLE_EQ(refl.GetRayPhase(), inc.GetRayPhase() + MY_PI); }

	inc.SetRayPhase(MY_PI*0.4);
	HitPoint hitPoint2(inc, glass, refl, refr);

	if(inc.GetRayPhase() > MY_PI) {
		ASSERT_DOUBLE_EQ(refl.GetRayPhase(), inc.GetRayPhase() - MY_PI); }
	else {
		ASSERT_DOUBLE_EQ(refl.GetRayPhase(), inc.GetRayPhase() + MY_PI); }
}



