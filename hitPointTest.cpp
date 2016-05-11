#include "gmock/gmock.h"
#include "ComplexNumber.h"
#include "HitPoint.h"
#include "Ray.h"
#include "Layer.h"

using namespace testing;

class RayHitPoint: public testing::Test {
public:

//members:
	Layer air;
	Layer glass;
	Ray inc;
	Ray refl;
	Ray refr;

//construtor:
	RayHitPoint(): air({1.0, 0.0}, 0.0), glass({1.5, 0.0}, 0.2),
			inc(0.0, 1.0, 1.0, 0.0, 0.632, true, 0),
			refl(), refr() {

		HitPoint hitPoint(air, glass, inc, refl, refr);
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

	inc.SetRayPhase(MY_PI*1.4);
	HitPoint hitPoint2(air, glass, inc, refl, refr);

	if(inc.GetRayPhase() > MY_PI) {
		ASSERT_DOUBLE_EQ(refl.GetRayPhase(), inc.GetRayPhase() - MY_PI); }
	else {
		ASSERT_DOUBLE_EQ(refl.GetRayPhase(), inc.GetRayPhase() + MY_PI); }
}

TEST_F(RayHitPoint, ReflectionDirection) {
	ASSERT_EQ(refl.GetRayDirection(), !inc.GetRayDirection());
}

TEST_F(RayHitPoint, ReflectionAmplitudeP0deg) {
	ASSERT_DOUBLE_EQ(refl.GetRayAmp_p(), 0.04*inc.GetRayAmp_p());
}

TEST_F(RayHitPoint, ReflectionAmplitudeP30deg) {
	inc.SetRayAngle(30.0);
	HitPoint hitPoint2(air, glass, inc, refl, refr);
	ASSERT_DOUBLE_EQ(refl.GetRayAmp_p(), 0.025*inc.GetRayAmp_p());
}




