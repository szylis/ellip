/* Copyright (C) 2016 Szymon Lis	email: szymonlis@yahoo.com
 * 					twitter: @drSzymonLis
 *
 * This class is designed to solve the Fresnel equation at interface of two mediums 
 *
 * To solve equations run the SOLVE public method, the necessary list of argument include:
 *	- Layer - reference to Layer class holding material where from light is coming
 *	- Layer - reference to Layer class holding material where the light is traveling
 *	- Ray - reference to Ray class holding the incident light beam
 *	- Ray - reference to Ray class holding the reflected light beam
 *	- Ray - reference to Ray class holding the refracted light beam
 *
 */

#ifndef HitPoint_h
#define HitPoint_h

#include "ComplexNumber.h"
#include "Layer.h"
#include "Ray.h"

#include <iostream>

class HitPoint {

//constructor
public:
	HitPoint();
	HitPoint(Layer&, Layer&, Ray&, Ray&, Ray&);

	~HitPoint();

//prototypes
public:
	void Solve(Layer&, Layer&, Ray&, Ray&, Ray&);

private:
	void ReflectionPhaseShift(Ray&);
	void Reflection(Layer&, Layer&, Ray&, Ray&);

	void RefractionAngle(Layer&, Layer&, Ray&, Ray&);
	void Transmission(Layer&, Layer&, Ray&, Ray&);

	void AlterPhase(Layer&, Ray&);

	double FindRp(Layer&, Layer&, Ray&);
	double FindRs(Layer&, Layer&, Ray&);
};

//constructor
HitPoint::HitPoint() {
}

HitPoint::HitPoint(Layer& rTopLayer, Layer& rBottomLayer, Ray& rInc, Ray& rRefl, Ray& rRefr) {

	Solve(rTopLayer, rBottomLayer, rInc, rRefl, rRefr);
}

HitPoint::~HitPoint() {
}


//public method

//method for solving the hit point
void HitPoint::Solve(Layer& rTopLayer, Layer& rBottomLayer, Ray& rInc, Ray& rRefl, Ray& rRefr) {

// -------- reflection -------

//1) reflection angle, wavelength and layer position are the same as for incidence ray
//2) invert direction of propagation
//3) shift phase by 180 deg when hitted denser medium
//4) alter the phrase according to thickness of the layer
//5) find the reflectance for p- and s- type polarization


	rRefl = rInc;
	rRefl.SetRayDirection(!rInc.GetRayDirection());

	if(rInc.GetRayDirection()) {	//top-down propagation

		if(rBottomLayer.GetRefractiveIndex().real > rTopLayer.GetRefractiveIndex().real) {
			ReflectionPhaseShift(rRefl); }
		AlterPhase(rTopLayer, rRefl);
		Reflection(rTopLayer, rBottomLayer, rInc, rRefl);
	}
	else {	//bottom-up propagation
		if(rTopLayer.GetRefractiveIndex().real > rBottomLayer.GetRefractiveIndex().real) {
			ReflectionPhaseShift(rRefl); }
		AlterPhase(rBottomLayer, rRefl);
		Reflection(rBottomLayer, rTopLayer, rInc, rRefl);
	}


// ------- refraction ---------

//1) wavelength is the same as for incidence ray
//2) change the position of the ray
//3) find refraction angle
//4) change phase according to thickness of the layer
//5) find the amplitude of the ray for p- and s- type of polarization

	rRefr = rInc;

	if(rInc.GetRayDirection()) {	//top-down propagation
		rRefr.SetRayLayer(rInc.GetRayLayer()+1);
		RefractionAngle(rTopLayer, rBottomLayer, rInc, rRefr);
		AlterPhase(rBottomLayer, rRefr);
		Transmission(rTopLayer, rBottomLayer, rInc, rRefr);
	}
	else {	//bottom-up propagation
		rRefr.SetRayLayer(rInc.GetRayLayer()-1);
		RefractionAngle(rBottomLayer, rTopLayer, rInc, rRefr);
		AlterPhase(rTopLayer, rRefr);
		Transmission(rBottomLayer, rTopLayer, rInc, rRefr);
	}
}

//private methods

//180 deg phase shift during reflection at denser metarial
//keep the value between 0-2pi
void HitPoint::ReflectionPhaseShift(Ray& rRay) {
	if(rRay.GetRayPhase() > MY_PI) {
		rRay.SetRayPhase(rRay.GetRayPhase() - MY_PI);
	}
	else {
		rRay.SetRayPhase(rRay.GetRayPhase() + MY_PI);
	}
}

//change phase according to the distance traveled by light
void HitPoint::AlterPhase(Layer& rLayer, Ray& rRay) {

	double x = rLayer.GetThickness()/(cos((DEG_TO_RAD(rRay.GetRayAngle()))));
	double kVector = (2*MY_PI*rLayer.GetRefractiveIndex().real)/rRay.GetRayWavelength();

	rRay.SetRayPhase(kVector * x + rRay.GetRayPhase());
}

//find the angle of refraction Snell's Law
void HitPoint::RefractionAngle(Layer& rA, Layer& rB, Ray& rI, Ray& rR) {

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

//reflectance coefficient
void HitPoint::Reflection(Layer& rTop, Layer& rBottom, Ray& rInc, Ray& rR) {

	rR.SetRayAmp_p( rInc.GetRayAmp_p() * sqrt(FindRp(rTop, rBottom, rInc)) );
	rR.SetRayAmp_s( rInc.GetRayAmp_s() * sqrt(FindRs(rTop, rBottom, rInc)) );

}
//transmittance coefficient
void HitPoint::Transmission(Layer& rTop, Layer& rBottom, Ray& rInc, Ray& rR) {

	rR.SetRayAmp_p( rInc.GetRayAmp_p() * (1.0 - sqrt(FindRp(rTop, rBottom, rInc))) );
	rR.SetRayAmp_s( rInc.GetRayAmp_s() * (1.0 - sqrt(FindRs(rTop, rBottom, rInc))) );
}

//reflectance of p-type polarization
double HitPoint::FindRp(Layer& rTop, Layer& rBottom, Ray& rInc) {

	ComplexNumber cplx;

	COMPLEX cX = cplx.Div(rTop.GetRefractiveIndex(), rBottom.GetRefractiveIndex());	// (n1/n2)

	cX = cplx.Mul(cX, sin(DEG_TO_RAD(rInc.GetRayAngle())));			// (n1/n2)*sin(theta)
	cX = cplx.Mul(cX, cX);							// ((n1/n2)*sin(theta))^2
	cX = cplx.Sqr(cplx.Sub(1.0, cX));					// ( sqrt(1 - ((n1/n2)*sin(theta))^2)

	COMPLEX cYp = cplx.Mul(rBottom.GetRefractiveIndex(), cos(DEG_TO_RAD(rInc.GetRayAngle())));	// n2*cos(theta)
	COMPLEX cZp = cplx.Mul(rTop.GetRefractiveIndex(), cX);

	//reflectance p- polarization
	double rp = cplx.Magnitude(cplx.Div(cplx.Sub(cZp, cYp), cplx.Add(cZp, cYp)));
	return rp * rp;
}

//reflectance of s-type polarization
double HitPoint::FindRs(Layer& rTop, Layer& rBottom, Ray& rInc) {

	ComplexNumber cplx;

	COMPLEX cX = cplx.Div(rTop.GetRefractiveIndex(), rBottom.GetRefractiveIndex());	// (n1/n2)

	cX = cplx.Mul(cX, sin(DEG_TO_RAD(rInc.GetRayAngle())));			// (n1/n2)*sin(theta)
	cX = cplx.Mul(cX, cX);							// ((n1/n2)*sin(theta))^2
	cX = cplx.Sqr(cplx.Sub(1.0, cX));					// ( sqrt(1 - ((n1/n2)*sin(theta))^2)

	COMPLEX cYs = cplx.Mul(rTop.GetRefractiveIndex(), cos(DEG_TO_RAD(rInc.GetRayAngle())));	// n1*cos(theta)
	COMPLEX cZs = cplx.Mul(rBottom.GetRefractiveIndex(), cX);

	//reflectance s- polarization
	double rs = cplx.Magnitude(cplx.Div(cplx.Sub(cYs, cZs), cplx.Add(cYs, cZs)));
	return rs * rs;
}


#endif
