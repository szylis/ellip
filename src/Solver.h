/* Copyright (C) 2016 Szymon Lis	email: szymonlis@yahoo.com
 * 					twitter: @drSzymonLis
 *
 * This class is designed to solve the reflection and transmiision
 *
 * To solve equations run the SOLVE public method, the necessary list of argument include:
 *	- Layer - reference to Layer class holding material where from light is coming
 *	- Layer - reference to Layer class holding material where the light is traveling
 *	- Ray - reference to Ray class holding the incident light beam
 *	- Ray - reference to Ray class holding the reflected light beam
 *	- Ray - reference to Ray class holding the refracted light beam
 *
 */

#ifndef Solver_h
#define Solver_h

#include "ComplexNumber.h"
#include "Layer.h"
#include "Ray.h"

#include <iostream>

class Solver {

//constructor
public:
	Solver();
	~Solver();

//prototypes
public:
	void SolveReflection(Layer&, Layer&, Layer&, Ray&);
	void SolveTransmission(Layer&, Layer&, Layer&, Ray&);

	COMPLEX GetRs() const { return rs; }
	COMPLEX GetRp() const { return rp; }
	COMPLEX GetTs() const { return ts; }
	COMPLEX GetTp() const { return tp; }


//methods
private:

	void RefractionAngle(Layer&, Layer&, Ray&, Ray&);
	double PhaseDifference(Layer&, Ray&);

	COMPLEX FindRs(Layer&, Layer&, Ray&);
	COMPLEX FindRp(Layer&, Layer&, Ray&);
	COMPLEX FindTs(Layer&, Layer&, Ray&);
	COMPLEX FindTp(Layer&, Layer&, Ray&);

//members
private:
	COMPLEX rs, rp, ts, tp;
};

//constructor
Solver::Solver() {
}

Solver::~Solver() {
}


//public method

//method for solving the structure
void Solver::SolveReflection(Layer& rLay1, Layer& rLay2, Layer& rLay3, Ray& rInc) {


	COMPLEX rs12, rp12, ts12, tp12;
	COMPLEX rs23, rp23, ts23, tp23;
	COMPLEX phasor;
	double phs;

/*
//setup refractiona ray
	Ray refr;
	refr = rInc;
	RefractionAngle(rLay1, rLay2, rInc, refr);

//find the reflection coefficinete
	rs12 = FindRs(rLay1, rLay2, rInc);
	rp12 = FindRp(rLay1, rLay2, rInc);
	ts12 = FindTs(rLay1, rLay2, rInc);
	tp12 = FindTp(rLay1, rLay2, rInc);

	rs23 = FindRs(rLay2, rLay3, refr);
	rp23 = FindRp(rLay2, rLay3, refr);
	ts23 = FindTs(rLay2, rLay3, refr);
	tp23 = FindTp(rLay2, rLay3, refr);

//phasor - optical length difference
	phs = PhaseDifference(rLay2, refr);
	phasor.real = cos(phs);
	phasor.imag = sin(phs)*-1.0;

//complex math
	ComplexNumber cplx;
	COMPLEX cXrp, cXrs, cYrp, cYrs;

	cXrs = cplx.Mul(rs23, phasor);
	cXrp = cplx.Mul(rp23, phasor);

	cYrs = cplx.Add(1.0, cplx.Mul(rs12, cXrs));
	cYrp = cplx.Add(1.0, cplx.Mul(rp12, cXrp));

	cXrs = cplx.Add(rs12, cXrs);
	cXrp = cplx.Add(rp12, cXrp);

	rs = cplx.Div(cXrs, cYrs);
	rp = cplx.Div(cXrp, cYrp);
*/
}

//method for solving the structure
void Solver::SolveTransmission(Layer& rLay1, Layer& rLay2, Layer& rLay3, Ray& rInc) {

/*
	COMPLEX rs12, rp12, ts12, tp12;
	COMPLEX rs23, rp23, ts23, tp23;
	COMPLEX phasor;
	double phs;


//setup refractiona ray
	Ray refr;
	refr = rInc;
	RefractionAngle(rLay1, rLay2, rInc, refr);

//find the reflection coefficinete
	rs12 = FindRs(rLay1, rLay2, rInc);
	rp12 = FindRp(rLay1, rLay2, rInc);
	ts12 = FindTs(rLay1, rLay2, rInc);
	tp12 = FindTp(rLay1, rLay2, rInc);

	rs23 = FindRs(rLay2, rLay3, refr);
	rp23 = FindRp(rLay2, rLay3, refr);
	ts23 = FindTs(rLay2, rLay3, refr);
	tp23 = FindTp(rLay2, rLay3, refr);

//phasor - optical length difference
	phs = PhaseDifference(rLay2, refr);
	phasor.real = cos(phs);
	phasor.imag = sin(phs)*-1.0;

//complex math
	ComplexNumber cplx;
	COMPLEX cXrp, cXrs, cYrp, cYrs;

	cXrs = cplx.Mul(rs23, phasor);
	cXrp = cplx.Mul(rp23, phasor);

	cYrs = cplx.Add(1.0, cplx.Mul(rs12, cXrs));
	cYrp = cplx.Add(1.0, cplx.Mul(rp12, cXrp));

	cXrs = cplx.Add(rs12, cXrs);
	cXrp = cplx.Add(rp12, cXrp);

	rs = cplx.Div(cXrs, cYrs);
	rp = cplx.Div(cXrp, cYrp);
*/
}



//private methods

//change phase according to the distance traveled by light
double Solver::PhaseDifference(Layer& rLayer, Ray& rRay) {

	double x = 2.0*rLayer.GetThickness()*cos((DEG_TO_RAD(rRay.GetRayAngle())));
	double kVector = (2*MY_PI*rLayer.GetRefractiveIndex().real)/rRay.GetRayWavelength();

	return kVector*x;
}


//find the angle of refraction Snell's Law
void Solver::RefractionAngle(Layer& rA, Layer& rB, Ray& rI, Ray& rR) {

	ComplexNumber cplx;
	COMPLEX cX;
	cX = cplx.Div(rA.GetRefractiveIndex(), rB.GetRefractiveIndex());
	cX = cplx.Mul(cX, sin(DEG_TO_RAD(rI.GetRayAngle())));

	//when the total internal reflection
	if(cX.real > 1.0) {
		rR.SetRayAngle(90.0);
	}
	else {
		rR.SetRayAngle(RAD_TO_DEG(asin(cX.real)));
	}
}

//reflectance of p-type polarization
COMPLEX Solver::FindRp(Layer& rTop, Layer& rBottom, Ray& rInc) {

	ComplexNumber cplx;

	COMPLEX cX = cplx.Div(rTop.GetRefractiveIndex(), rBottom.GetRefractiveIndex());	// (n1/n2)

	cX = cplx.Mul(cX, sin(DEG_TO_RAD(rInc.GetRayAngle())));			// (n1/n2)*sin(theta)
	cX = cplx.Mul(cX, cX);							// ((n1/n2)*sin(theta))^2
	cX = cplx.Sqr(cplx.Sub(1.0, cX));					// ( sqrt(1 - ((n1/n2)*sin(theta))^2)

	COMPLEX cYp = cplx.Mul(rBottom.GetRefractiveIndex(), cos(DEG_TO_RAD(rInc.GetRayAngle())));	// n2*cos(theta)
	COMPLEX cZp = cplx.Mul(rTop.GetRefractiveIndex(), cX);

	//reflectance p- polarization
	return cplx.Div(cplx.Sub(cZp, cYp), cplx.Add(cZp, cYp));
}

//transmittance of p-type polarization
COMPLEX Solver::FindTp(Layer& rTop, Layer& rBottom, Ray& rInc) {

	ComplexNumber cplx;

	COMPLEX cX = cplx.Div(rTop.GetRefractiveIndex(), rBottom.GetRefractiveIndex());	// (n1/n2)

	cX = cplx.Mul(cX, sin(DEG_TO_RAD(rInc.GetRayAngle())));			// (n1/n2)*sin(theta)
	cX = cplx.Mul(cX, cX);							// ((n1/n2)*sin(theta))^2
	cX = cplx.Sqr(cplx.Sub(1.0, cX));					// ( sqrt(1 - ((n1/n2)*sin(theta))^2)

	COMPLEX cYp = cplx.Mul(rBottom.GetRefractiveIndex(), cos(DEG_TO_RAD(rInc.GetRayAngle())));	// n2*cos(theta)
	COMPLEX cWp = cplx.Mul(rTop.GetRefractiveIndex(), cos(DEG_TO_RAD(rInc.GetRayAngle())));		// n1*cos(theta)
	COMPLEX cZp = cplx.Mul(rTop.GetRefractiveIndex(), cX);

	//reflectance p- polarization
	return cplx.Div(cplx.Mul(2.0, cWp), cplx.Add(cZp, cYp));
}


//reflectance of s-type polarization
COMPLEX Solver::FindRs(Layer& rTop, Layer& rBottom, Ray& rInc) {

	ComplexNumber cplx;

	COMPLEX cX = cplx.Div(rTop.GetRefractiveIndex(), rBottom.GetRefractiveIndex());	// (n1/n2)

	cX = cplx.Mul(cX, sin(DEG_TO_RAD(rInc.GetRayAngle())));			// (n1/n2)*sin(theta)
	cX = cplx.Mul(cX, cX);							// ((n1/n2)*sin(theta))^2
	cX = cplx.Sqr(cplx.Sub(1.0, cX));					// ( sqrt(1 - ((n1/n2)*sin(theta))^2)

	COMPLEX cYs = cplx.Mul(rTop.GetRefractiveIndex(), cos(DEG_TO_RAD(rInc.GetRayAngle())));	// n1*cos(theta)
	COMPLEX cZs = cplx.Mul(rBottom.GetRefractiveIndex(), cX);

	//reflectance s- polarization
	return cplx.Div(cplx.Sub(cYs, cZs), cplx.Add(cYs, cZs));
}

//transmittance of s-type polarization
COMPLEX Solver::FindTs(Layer& rTop, Layer& rBottom, Ray& rInc) {

	ComplexNumber cplx;

	COMPLEX cX = cplx.Div(rTop.GetRefractiveIndex(), rBottom.GetRefractiveIndex());	// (n1/n2)

	cX = cplx.Mul(cX, sin(DEG_TO_RAD(rInc.GetRayAngle())));			// (n1/n2)*sin(theta)
	cX = cplx.Mul(cX, cX);							// ((n1/n2)*sin(theta))^2
	cX = cplx.Sqr(cplx.Sub(1.0, cX));					// ( sqrt(1 - ((n1/n2)*sin(theta))^2)

	COMPLEX cYs = cplx.Mul(rTop.GetRefractiveIndex(), cos(DEG_TO_RAD(rInc.GetRayAngle())));	// n1*cos(theta)
	COMPLEX cZs = cplx.Mul(rBottom.GetRefractiveIndex(), cX);


	//reflectance s- polarization
	return cplx.Div(cplx.Mul(2.0, cYs), cplx.Add(cYs, cZs));
}


#endif
