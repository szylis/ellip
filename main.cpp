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


	FILE *output;
	output = fopen("data.out", "w");
	if (output == NULL) {
		printf("Error opening file data.out\n");
		return 0;
	}


	fprintf(output, "Angle:\tRp:\tRs:\t\n");

	for(unsigned int i=0; i <= 90; i++) 
	{
		laser.SetRayAngle(i);
		hit.Solve(air, glass, laser, refl, tran);
		fprintf(output, "%7.3f %7.5f %7.5f\n", laser.GetRayAngle(), refl.GetRayAmp_p(), refl.GetRayAmp_s());
	}

	fclose(output);

	return 0;
}
