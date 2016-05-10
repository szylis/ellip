#include "gmock/gmock.h"
#include "ComplexNumber.h"
#include "HitPoint.h"
#include "Ray.h"
#include "Layer.h"

using namespace testing;

class RayHitPoint: public testing::Test {
public:
	HitPoint hitPoint;
};

TEST_F(RayHitPoint, Constructor) {

	Layer glass({1.45, 0.0}, 0.2);
	Ray laser(30.0);
	Ray reflection;
	Ray refraction;
	
	HitPoint hit(laser, glass, reflection, refraction);

	ASSERT_DOUBLE_EQ(reflection.GetRayAngle(), 30.0); 
}

