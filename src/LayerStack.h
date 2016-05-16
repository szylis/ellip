/* Copyright (C) 2016 Szymon Lis		email: szymonlis@yahoo.com
 *						twitter: @drSzymonLis
 *
 * Class holding the stack of layers
 *
 */

#ifndef LayerStack_h
#define LayerStack_h

#include "ComplexNumber.h"
#include "Ray.h"
#include "Layer.h"
#include "HitPoint.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include <iostream>

using namespace std;
using namespace boost;

class LayerStack {

//constructor
public:
	LayerStack();
	~LayerStack();

//methods:
	void Solve(ptr_vector<Layer>, Ray&, double&, double&);

};



//constructor
LayerStack::LayerStack() {
}

LayerStack::~LayerStack() {
}

//methods
void LayerStack::Solve(ptr_vector<Layer> vStc, Ray& rIn, double& rRp, double& rRs) {

	unsigned int N = vStc.size();

	HitPoint hitPoint;

	ptr_vector<Ray> vTran;		//vector with all transmitted beams
	ptr_vector<Ray> vRefl;		//vector with reflected beam used to find Rp and Rs

	vTran.push_back(new Ray{rIn});	//first elemnt is the incidence laser beam

	Ray tRefl;		//temporary Ray object
	Ray tTran;		//temporary Ray object

	//check if there any interface if not return 0.0
	if(N<2) {
		rRp = 0.0;
		rRs = 0.0;
		return;
	}

	//loop over all layers
	for(unsigned int i=0; i<N-1; i++)
	{
		hitPoint.Solve(vStc[i], vStc[i+1], vTran[i], tRefl, tTran);

		vTran.push_back(new Ray{tTran});	//add transmitted beam
		vRefl.push_back(new Ray{tRefl});	//add reflected beam
	}


	//Backwards rays need to be transmitted to the top
	unsigned int M = vRefl.size();

	for(unsigned int i=1; i<M; i++) {
		hitPoint.Solve(vStc[1], vStc[0], vRefl[1], tRefl, tTran);
//		cout << tTran.GetRayAmp_p() << endl;
		vRefl[i] = tTran;
	}


	rRp = 0.0;
	rRs = 0.0;

	double phsFactor;
	ComplexNumber cplx;
	COMPLEX phsCplx;

	COMPLEX rp_cplx;
	COMPLEX rs_cplx;

	unsigned int m = 0;
//	while(m < M) {

		double a = vTran[1].GetRayAmp_p() * cos(vTran[1].GetRayPhase());
		double b = vTran[1].GetRayAmp_s() * sin(vTran[1].GetRayPhase());
		

		cout << "a = " << a << endl;
		cout << "ib = " << b << endl;
//		cout << "r23 = " << vRefl[1].GetRayAmp_p() << endl;

//		double y = cos(vTran[1].GetRayPhase());
//		cout << "cos(t0.phase) = " << y << endl;
//		cout << "t0 = " << vTran[1].GetRayAmp_p() << endl;

//		phsFactor = cplx.Magnitude(phsCplx);
//		phsFactor *= phsFactor;

//		rRp = rRp + vRefl[m].GetRayAmp_p() * phsFactor;
//		rRs = rRs + vRefl[m].GetRayAmp_s() * phsFactor;

		
//		m++;
//	}

	return;
}

#endif
