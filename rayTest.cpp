#include "gmock/gmock.h"
#include "ComplexNumber.h"
#include "Ray.h"

using namespace testing;

class PropagatedRay: public testing::Test {
public:
	Ray ray;
};

TEST_F(PropagatedRay, GetPropagationAngle) {

	Ray incRay(47.5, 1.0);
	ASSERT_DOUBLE_EQ(incRay.GetPropagationAngle(), 47.5);
}

TEST_F(PropagatedRay, SetPropagationAngle) {

	ray.SetPropagationAngle(30.0);
	ASSERT_DOUBLE_EQ(ray.GetPropagationAngle(), 30.0);
}

TEST_F(PropagatedRay, GetRayAmplitude) {

	Ray incRay(47.5, 0.88);
	ASSERT_DOUBLE_EQ(incRay.GetRayAmplitude(), 0.88);
}

TEST_F(PropagatedRay, SetRayAmplitude) {

	ray.SetRayAmplitude(0.77);
	ASSERT_DOUBLE_EQ(ray.GetRayAmplitude(), 0.77);
}
