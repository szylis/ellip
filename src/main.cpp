

#include <iostream>
#include <cstdio>
#include <cmath>
#include "ComplexNumber.h"
#include "Ray.h"
#include "Layer.h"
#include "Solver.h"

using namespace std;

int main()
{

	//creat a stac of layers
	Layer air(0, {1.0, 0.0}, 0.0);
	Layer glass(1, {1.5, 0.0}, 0.0);
	Layer si(2, {3.4, -0.04}, 1.0);

	//incidence light beam
	Ray laser(60.0, 1.0, 1.0, 0.0, 0.632, true, 0);

	//initialization of solver
	Solver solver;


	//output file
	FILE *output;
	output = fopen("../output/data.out", "w");
	if (output == NULL) {
		printf("Error opening file data.out\n");
		return 0;
	}

	//header in the file
	fprintf(output, "Thick:\tDEL:\tPSI:\t\n");

	//glass thickness investiagation
	for(unsigned int i=0; i<=800; i++)
	{
		glass.SetThickness(0.001*i);
		solver.SolveEllipsometry(air, glass, si, laser);
		fprintf(output, "%6.3f\t", glass.GetThickness());
		fprintf(output, "%6.3f\t", solver.GetDel());
		fprintf(output, "%6.3f\n", solver.GetPsi());
	}

	//close the output stream
	fclose(output);


	return 0;
}
