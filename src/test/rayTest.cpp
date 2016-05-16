#include "gmock/gmock.h"
#include "../ComplexNumber.h"
#include "../Ray.h"

using namespace testing;

class PropagatedRay: public testing::Test {
public:
	Ray ray;
};


TEST_F(PropagatedRay, DISABLE_Constructor_0) {
	ASSERT_DOUBLE_EQ(ray.GetRayAngle(), 0.0);
	ASSERT_DOUBLE_EQ(ray.GetRayAmp_p(), 1.0);
	ASSERT_DOUBLE_EQ(ray.GetRayAmp_s(), 1.0);
	ASSERT_DOUBLE_EQ(ray.GetRayPhase(), 0.0);
	ASSERT_DOUBLE_EQ(ray.GetRayWavelength(), 1.0);
	ASSERT_EQ(ray.GetRayDirection(), true);
	ASSERT_EQ(ray.GetRayLayer(), 0);
}

TEST_F(PropagatedRay, Constructor_6) {

	Ray laser(30.0, 0.6, 0.8, MY_PI, 0.632, false, 3);
	ASSERT_DOUBLE_EQ(laser.GetRayAngle(), 30.0);
	ASSERT_DOUBLE_EQ(laser.GetRayAmp_p(), 0.6);
	ASSERT_DOUBLE_EQ(laser.GetRayAmp_s(), 0.8);
	ASSERT_DOUBLE_EQ(laser.GetRayPhase(), MY_PI);
	ASSERT_DOUBLE_EQ(laser.GetRayWavelength(), 0.632);
	ASSERT_EQ(laser.GetRayDirection(), false);
	ASSERT_EQ(laser.GetRayLayer(), 3);
}


TEST_F(PropagatedRay, SetRayAngle) {
	ray.SetRayAngle(28.8);
	ASSERT_DOUBLE_EQ(ray.GetRayAngle(), 28.8);
}

TEST_F(PropagatedRay, SetRayAmp_p) {
	ray.SetRayAmp_p(0.77);
	ASSERT_DOUBLE_EQ(ray.GetRayAmp_p(), 0.77);
}

TEST_F(PropagatedRay, SetRayAmp_s) {
	ray.SetRayAmp_s(0.55);
	ASSERT_DOUBLE_EQ(ray.GetRayAmp_s(), 0.55);
}

TEST_F(PropagatedRay, SetRayPhase) {
	ray.SetRayPhase(MY_PI/2);
	ASSERT_DOUBLE_EQ(ray.GetRayPhase(), MY_PI/2);
}

TEST_F(PropagatedRay, SetRayWavelength) {
	ray.SetRayWavelength(0.350);
	ASSERT_DOUBLE_EQ(ray.GetRayWavelength(), 0.350);
}

TEST_F(PropagatedRay, SetRayDirection) {
	ray.SetRayDirection(false);
	ASSERT_EQ(ray.GetRayDirection(), false);
}

TEST_F(PropagatedRay, SetRayLayer) {
	ray.SetRayLayer(2);
	ASSERT_EQ(ray.GetRayLayer(), 2);
}

