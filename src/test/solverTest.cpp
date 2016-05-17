#include "gmock/gmock.h"
#include "../ComplexNumber.h"
#include "../Solver.h"
#include "../Ray.h"
#include "../Layer.h"

using namespace testing;

class Solution: public testing::Test {
public:

//members:
	Layer air;
	Layer glass;
	Layer si;
	Ray inc;

	Solver solver;


//construtor:
	Solution(): air(0, {1.0, 0.0}, 0.0),
		glass(1, {1.5, 0.0}, 0.2),
		si(2, {3.4, 0.0}, 0.0),
		inc(0.0, 1.0, 1.0, 0.0, 0.632, true, 0) {

		solver.SolveReflection(air, glass, si, inc);
		solver.SolveTransmission(air, glass, si, inc);
	};

//deconstructor:
	~Solution() {};


};

// 0 deg
TEST_F(Solution, rs_0deg) {
	ASSERT_NEAR(solver.GetRs().real, -0.53159, 0.0001);
	ASSERT_NEAR(solver.GetRs().imag, -0.10096, 0.0001);
}

TEST_F(Solution, rp_0deg) {
	ASSERT_NEAR(solver.GetRp().real, -0.53159, 0.0001);
	ASSERT_NEAR(solver.GetRp().imag, -0.10096, 0.0001);
}

TEST_F(Solution, ts_0deg) {
	ASSERT_NEAR(solver.GetTs().real, -0.45184, 0.0001);
	ASSERT_NEAR(solver.GetTs().imag, -0.06205, 0.0001);
}

TEST_F(Solution, tp_0deg) {
	ASSERT_NEAR(solver.GetTp().real, -0.45184, 0.0001);
	ASSERT_NEAR(solver.GetTp().imag, -0.06205, 0.0001);
}

// 20 deg
TEST_F(Solution, rs_20deg) {
	inc.SetRayAngle(20.0);
	solver.SolveReflection(air, glass, si, inc);
	ASSERT_NEAR(solver.GetRs().real, -0.53481, 0.0001);
	ASSERT_NEAR(solver.GetRs().imag, -0.14912, 0.0001);
}

TEST_F(Solution, rp_20deg) {
	inc.SetRayAngle(20.0);
	solver.SolveReflection(air, glass, si, inc);
	ASSERT_NEAR(solver.GetRp().real, -0.49379, 0.0001);
	ASSERT_NEAR(solver.GetRp().imag, -0.14843, 0.0001);
}

TEST_F(Solution, ts_20deg) {
	inc.SetRayAngle(20.0);
	solver.SolveTransmission(air, glass, si, inc);
	ASSERT_NEAR(solver.GetTs().real, -0.42953, 0.0001);
	ASSERT_NEAR(solver.GetTs().imag, -0.08753, 0.0001);
}

TEST_F(Solution, tp_20deg) {
	inc.SetRayAngle(20.0);
	solver.SolveTransmission(air, glass, si, inc);
	ASSERT_NEAR(solver.GetTp().real, -0.44188, 0.0001);
	ASSERT_NEAR(solver.GetTp().imag, -0.09316, 0.0001);
}
