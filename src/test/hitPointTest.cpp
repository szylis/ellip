#include "gmock/gmock.h"
#include "../ComplexNumber.h"
#include "../HitPoint.h"
#include "../Ray.h"
#include "../Layer.h"

using namespace testing;

class RayHitPoint: public testing::Test {
public:

//members:
	Layer air;
	Layer glass;
	Ray inc;
	Ray refl;
	Ray refr;
	HitPoint hitPoint;

//construtor:
	RayHitPoint(): air(0, {1.0, 0.0}, 0.0), glass(1, {1.5, 0.0}, 0.2),
			inc(0.0, 1.0, 1.0, 0.0, 0.632, true, 0),
			refl(), refr() {

		hitPoint.Solve(air, glass, inc, refl, refr);
	};

//deconstructor:
	~RayHitPoint() {};


};


//constructor test
TEST_F(RayHitPoint, ConstructorAllArgs) {
	inc.SetRayAngle(30.0);
	HitPoint hitPoint2(air, glass, inc, refl, refr);
	ASSERT_DOUBLE_EQ(refl.GetRayAngle(), inc.GetRayAngle());
}

//---- reflection tests ----
TEST_F(RayHitPoint, ReflectionAngleCheck) {
	ASSERT_DOUBLE_EQ(refl.GetRayAngle(), inc.GetRayAngle());
}

TEST_F(RayHitPoint, ReflectionLayerCheck) {
	ASSERT_EQ(refl.GetRayLayer(), inc.GetRayLayer());
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
	hitPoint.Solve(air, glass, inc, refl, refr);

	if(inc.GetRayPhase() > MY_PI) {
		ASSERT_DOUBLE_EQ(refl.GetRayPhase(), inc.GetRayPhase() - MY_PI); }
	else {
		ASSERT_DOUBLE_EQ(refl.GetRayPhase(), inc.GetRayPhase() + MY_PI); }
}

TEST_F(RayHitPoint, ReflectionDirection) {
	ASSERT_EQ(refl.GetRayDirection(), !inc.GetRayDirection());
}

TEST_F(RayHitPoint, ReflectionAmplitudeP0deg) {
	ASSERT_NEAR(refl.GetRayAmp_p(), 0.04*inc.GetRayAmp_p(), 0.0000001);
}

TEST_F(RayHitPoint, ReflectionAmplitudeP30deg) {
	inc.SetRayAngle(30.0);
	hitPoint.Solve(air, glass, inc, refl, refr);
	ASSERT_NEAR(refl.GetRayAmp_p(), 0.0252491*inc.GetRayAmp_p(), 0.0000001);
}

TEST_F(RayHitPoint, ReflectionAmplitudeS0deg) {
	ASSERT_NEAR(refl.GetRayAmp_s(), 0.04*inc.GetRayAmp_p(), 0.0000001);
}

TEST_F(RayHitPoint, ReflectionAmplitudeS30deg) {
	inc.SetRayAngle(30.0);
	hitPoint.Solve(air, glass, inc, refl, refr);
	ASSERT_NEAR(refl.GetRayAmp_s(), 0.0577961*inc.GetRayAmp_p(), 0.0000001);
}

//---- end reflection tests ----

//---- refraction tests ----
TEST_F(RayHitPoint, RefractionDirection) {
	ASSERT_EQ(refr.GetRayDirection(), inc.GetRayDirection());
}

TEST_F(RayHitPoint, RefractionWavelength) {
	ASSERT_DOUBLE_EQ(refr.GetRayWavelength(), inc.GetRayWavelength());
}

TEST_F(RayHitPoint, RefractionPhaseChange0deg) {
	ASSERT_NEAR(refr.GetRayPhase(), 2*MY_PI*glass.GetThickness()/0.421333, 0.0001);
}

////
TEST_F(RayHitPoint, RefractionPhaseChange30deg) {
	inc.SetRayAngle(30.0);
	hitPoint.Solve(air, glass, inc, refl, refr);
	double x = asin(0.5/glass.GetRefractiveIndex().real);
	ASSERT_NEAR(refr.GetRayPhase(), 2*MY_PI*(0.2/cos(x))/0.421333, 0.001);
}


TEST_F(RayHitPoint, RefractionLayerCheck) {
	ASSERT_EQ(refr.GetRayLayer(), inc.GetRayLayer()+1);
}


TEST_F(RayHitPoint, RefractionAmplitudeP0deg) {
	ASSERT_NEAR(refr.GetRayAmp_p(), 1.0 - 0.04*inc.GetRayAmp_p(), 0.0000001);
}

TEST_F(RayHitPoint, RefractionAmplitudeP30deg) {
	inc.SetRayAngle(30.0);
	hitPoint.Solve(air, glass, inc, refl, refr);
	ASSERT_NEAR(refr.GetRayAmp_p(), 1.0 - 0.0252491*inc.GetRayAmp_p(), 0.0000001);
}

TEST_F(RayHitPoint, RefractionAmplitudeS0deg) {
	ASSERT_NEAR(refr.GetRayAmp_s(), 1.0 - 0.04*inc.GetRayAmp_p(), 0.0000001);
}

TEST_F(RayHitPoint, RefractionAmplitudeS30deg) {
	inc.SetRayAngle(30.0);
	hitPoint.Solve(air, glass, inc, refl, refr);
	ASSERT_NEAR(refr.GetRayAmp_s(), 1.0 - 0.0577961*inc.GetRayAmp_p(), 0.0000001);
}

TEST_F(RayHitPoint, RefrectionAngle0deg) {
	ASSERT_DOUBLE_EQ(refr.GetRayAngle(), 0.0);
}

TEST_F(RayHitPoint, RefractionAngle30deg) {
	inc.SetRayAngle(30.0);
	hitPoint.Solve(air, glass, inc, refl, refr);
	ASSERT_NEAR(refr.GetRayAngle(), 19.4712, 0.0001);
}

//---- end refraction tests ----

//Brewster's Angle
TEST_F(RayHitPoint, BrewstersAngle) {
	inc.SetRayAngle(56.3);
	hitPoint.Solve(air, glass, inc, refl, refr);
	ASSERT_NEAR(refl.GetRayAmp_p(), 0.0, 0.000001);
	ASSERT_NEAR(refl.GetRayAmp_s(), 0.147861, 0.000001);
}

//Light travles from glass to air (Total Internal Refrlection)
TEST_F(RayHitPoint, FromGlassToAirAngle20deg) {
	inc.SetRayAngle(20.0);
	glass.SetPosition(0);
	air.SetPosition(1);
	hitPoint.Solve(glass, air, inc, refl, refr);
	ASSERT_NEAR(refl.GetRayAngle(), 20.0, 0.01);
	ASSERT_NEAR(refr.GetRayAngle(), 30.86, 0.01);
	ASSERT_NEAR(refl.GetRayAmp_p(), 0.0243938, 0.0000001);
	ASSERT_NEAR(refl.GetRayAmp_s(), 0.0590632, 0.0000001);
}

TEST_F(RayHitPoint, FromGlassToAirBrewstersAngle) {
	inc.SetRayAngle(33.69);
	glass.SetPosition(0);
	air.SetPosition(1);
	hitPoint.Solve(glass, air, inc, refl, refr);
	ASSERT_NEAR(refl.GetRayAngle(), 33.69, 0.01);
	ASSERT_NEAR(refr.GetRayAngle(), 56.30, 0.01);
	ASSERT_NEAR(refl.GetRayAmp_p(), 0.0, 0.0000001);
	ASSERT_NEAR(refl.GetRayAmp_s(), 0.147928, 0.0000001);
}

TEST_F(RayHitPoint, FromGlassToAirAngle50deg) {
	inc.SetRayAngle(50.0);
	glass.SetPosition(0);
	air.SetPosition(1);
	hitPoint.Solve(glass, air, inc, refl, refr);
	ASSERT_NEAR(refl.GetRayAngle(), 50.0, 0.01);
	ASSERT_NEAR(refr.GetRayAngle(), 90.0, 0.01);
	ASSERT_NEAR(refl.GetRayAmp_p(), 1.0, 0.0000001);
	ASSERT_NEAR(refl.GetRayAmp_s(), 1.0, 0.0000001);
}

//ray is travelling backwards
TEST_F(RayHitPoint, BackwardRayRefrRayDirection) {
	inc.SetRayAngle(30.0);
	inc.SetRayLayer(1);
	inc.SetRayDirection(false);
	hitPoint.Solve(air, glass, inc, refl, refr);

	ASSERT_FALSE(refr.GetRayDirection());
}

TEST_F(RayHitPoint, BackwardRayReflRayDirection) {
	inc.SetRayAngle(30.0);
	inc.SetRayLayer(1);
	inc.SetRayDirection(false);
	hitPoint.Solve(air, glass, inc, refl, refr);

	ASSERT_TRUE(refl.GetRayDirection());
}

TEST_F(RayHitPoint, BackwardRayRefrRayLayer) {
	inc.SetRayAngle(30.0);
	inc.SetRayLayer(1);
	inc.SetRayDirection(false);
	hitPoint.Solve(air, glass, inc, refl, refr);

	ASSERT_THAT(refr.GetRayLayer(), inc.GetRayLayer()-1);
}


TEST_F(RayHitPoint, BackwardRayReflRayLayer) {
	inc.SetRayAngle(30.0);
	inc.SetRayLayer(1);
	inc.SetRayDirection(false);
	hitPoint.Solve(air, glass, inc, refl, refr);

	ASSERT_THAT(refl.GetRayLayer(), inc.GetRayLayer());
}

TEST_F(RayHitPoint, BackwardRayWavelength) {
	inc.SetRayAngle(30.0);
	inc.SetRayLayer(1);
	inc.SetRayDirection(false);
	hitPoint.Solve(air, glass, inc, refl, refr);

	ASSERT_THAT(refl.GetRayWavelength(), inc.GetRayWavelength());
	ASSERT_THAT(refr.GetRayWavelength(), inc.GetRayWavelength());
}

TEST_F(RayHitPoint, BackwardRayReflAngle) {
	inc.SetRayAngle(30.0);
	inc.SetRayLayer(1);
	inc.SetRayDirection(false);
	hitPoint.Solve(air, glass, inc, refl, refr);

	ASSERT_THAT(refl.GetRayAngle(), inc.GetRayAngle());
}

TEST_F(RayHitPoint, BackwardRayRefractionAngleTest) {
	inc.SetRayAngle(30.0);
	inc.SetRayLayer(1);
	inc.SetRayDirection(false);
	hitPoint.Solve(air, glass, inc, refl, refr);

	double b = asin((glass.GetRefractiveIndex().real/air.GetRefractiveIndex().real)*(sin(inc.GetRayAngle() * MY_PI/180)));
	ASSERT_THAT(refr.GetRayAngle(), b*180/MY_PI);
}


TEST_F(RayHitPoint, BackwardRayRefractionPhase) {
	inc.SetRayAngle(30.0);
	inc.SetRayLayer(1);
	inc.SetRayDirection(false);
	inc.SetRayPhase(0.0);

	Layer TiO2(2, {2.4, 0.0}, 1.0);

	hitPoint.Solve(glass, TiO2, inc, refl, refr);

	double kvec = (2*MY_PI)/(inc.GetRayWavelength()/glass.GetRefractiveIndex().real);
	double x = glass.GetThickness()/cos(refr.GetRayAngle()*MY_PI/180);

	ASSERT_THAT(refr.GetRayPhase(), kvec*x);
}


TEST_F(RayHitPoint, BackwardRayReflectionPhase) {
	inc.SetRayAngle(30.0);
	inc.SetRayLayer(1);
	inc.SetRayDirection(false);
	inc.SetRayPhase(0.0);

	Layer TiO2(2, {2.4, 0.0}, 1.0);

	hitPoint.Solve(glass, TiO2, inc, refl, refr);

	double kvec = (2*MY_PI)/(inc.GetRayWavelength()/TiO2.GetRefractiveIndex().real);
	double x = TiO2.GetThickness()/cos(refl.GetRayAngle()*MY_PI/180);

	ASSERT_NEAR(refl.GetRayPhase(), kvec*x+MY_PI, 0.001);
}

/*

TEST_F(RayHitPoint, BackwardRayRefractionPhaseNotAir) {

	Layer TiO2(2, {2.4, 0.0}, 1.0);
	glass.SetPosition(1);
	inc.SetRayAngle(30.0);
	inc.SetRayLayer(1);
	inc.SetRayDirection(false);
	hitPoint.Solve(glass, TiO2, inc, refl, refr);

	double x = glass.GetThickness()/cos( asin(0.5*(TiO2.GetRefractiveIndex().real/glass.GetRefractiveIndex().real)) );

	ASSERT_THAT(refr.GetRayPhase(), 2*MY_PI*x/0.4213333);
}

*/
