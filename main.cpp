#include <iostream>
#include <cstdio>
#include <cmath>
#include "ComplexNumber.h"
#include "Ray.h"
#include "Layer.h"
#include "HitPoint.h"

using namespace std;

int main()
{

	//stac of layers
	Layer air(0, {1.0, 0.0}, 0.0);
	Layer glass(1, {1.5, 0.0}, 1.0);;

	//light beams
	Ray laser(0.0, 1.0, 1.0, 0.0, 0.632, true, 0);
	Ray refl;
	Ray tran;

	//interface
	HitPoint hit;

	printf("Angle:\tRp:\tRs:\t\n");


	for(unsigned int i=0; i < 15; i++) 
	{
		laser.SetRayAngle(5.0*i);
		hit.Solve(air, glass, laser, refl, tran);
		printf("%.5f %.5f %.5f\n", laser.GetRayAngle(), refl.GetRayAmp_p(), refl.GetRayAmp_s());
	}

	return 0;
}
