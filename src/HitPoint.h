/* Copyright (C) 2016 Szymon Lis	email: szymonlis@yahoo.com
 * 					twitter: @drSzymonLis
 *
 * This class is designed to solve the Fresnel equation at two mediums interface
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
	void Reflectance(Layer&, Layer&, Ray&, Ray&);

	void RefractionAngle(Layer&, Layer&, Ray&, Ray&);
	void Transmittance(Layer&, Layer&, Ray&, Ray&);

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

// --- reflection ---
//1) reflection angle, wavelength, layer position -> the same as incidence
	rRefl = rInc;

//2) invers direction of propagation
	rRefl.SetRayDirection(!rInc.GetRayDirection());

//3) shift phase by 180deg
	ReflectionPhaseShift(rRefl);

//4) calculate phase for new reflected beam
	AlterPhase(rTopLayer, rRefl);

//5) find the reflectance for p- and s- type polarization
	Reflectance(rTopLayer, rBottomLayer, rInc, rRefl);


// --- refraction ---
//1) wavelength the same as incidence
	rRefr = rInc;

//2) change the postion of ray
	if(rRefr.GetRayDirection()) {
		rRefr.SetRayLayer(rInc.GetRayLayer()+1);
	}
	else {
		rRefr.SetRayLayer(rInc.GetRayLayer()-1);
	}

//3) find refraction angle
	RefractionAngle(rTopLayer, rBottomLayer, rInc, rRefr);

//4) change phase according to thickness of the layer
	AlterPhase(rBottomLayer, rRefr);

//5) find the amplitude of the ray for p- and s- type of polarization
	Transmittance(rTopLayer, rBottomLayer, rInc, rRefr);
}

//private methods

//phase shift 180deg after reflecion
//keep the value between 0-2pi
void HitPoint::ReflectionPhaseShift(Ray& rRay) {
	if(rRay.GetRayPhase() > MY_PI) {
		rRay.SetRayPhase(rRay.GetRayPhase() - MY_PI);
	}
	else {
		rRay.SetRayPhase(rRay.GetRayPhase() + MY_PI);
	}
}

void HitPoint::AlterPhase(Layer& rLayer, Ray& rRay) {

	double x = rLayer.GetThickness()/cos(rRay.GetRayAngle()*MY_PI/180);
	double kVector = 2*MY_PI*rLayer.GetRefractiveIndex().real/rRay.GetRayWavelength();

	rRay.SetRayPhase(kVector * x + rRay.GetRayPhase());
}


void HitPoint::RefractionAngle(Layer& rT, Layer& rB, Ray& rI, Ray& rR) {

	ComplexNumber cplx;

	COMPLEX cX = cplx.Div(rT.GetRefractiveIndex(), rB.GetRefractiveIndex());
	cX = cplx.Mul(cX, sin(rI.GetRayAngle()*MY_PI/180));

	//when the total internal reflection
	if(cX.real > 1.0) {
		rR.SetRayAngle(90.0);
	}
	else {
		rR.SetRayAngle(asin(cX.real)*180/MY_PI);
	}
}

void HitPoint::Reflectance(Layer& rTop, Layer& rBottom, Ray& rInc, Ray& rR) {

	rR.SetRayAmp_p(FindRp(rTop, rBottom, rInc));
	rR.SetRayAmp_s(FindRs(rTop, rBottom, rInc));

}

void HitPoint::Transmittance(Layer& rTop, Layer& rBottom, Ray& rInc, Ray& rR) {

	rR.SetRayAmp_p(1.0 - FindRp(rTop, rBottom, rInc));
	rR.SetRayAmp_s(1.0 - FindRs(rTop, rBottom, rInc));
}

double HitPoint::FindRp(Layer& rTop, Layer& rBottom, Ray& rInc) {

	ComplexNumber cplx;

	COMPLEX cX = cplx.Div(rTop.GetRefractiveIndex(), rBottom.GetRefractiveIndex());	// (n1/n2)

	cX = cplx.Mul(cX, sin(rInc.GetRayAngle()*MY_PI/180));			// (n1/n2)*sin(theta)
	cX = cplx.Mul(cX, cX);							// ((n1/n2)*sin(theta))^2
	cX = cplx.Sqr(cplx.Sub(1.0, cX));					// ( sqrt(1 - ((n1/n2)*sin(theta))^2)

	COMPLEX cYp = cplx.Mul(rBottom.GetRefractiveIndex(), cos(rInc.GetRayAngle()*MY_PI/180));	// n2*cos(theta)
	COMPLEX cZp = cplx.Mul(rTop.GetRefractiveIndex(), cX);

	//reflectance p- polarization
	double rp = cplx.Magnitude(cplx.Div(cplx.Sub(cZp, cYp), cplx.Add(cZp, cYp)));
	return rp * rp;
}

double HitPoint::FindRs(Layer& rTop, Layer& rBottom, Ray& rInc) {

	ComplexNumber cplx;

	COMPLEX cX = cplx.Div(rTop.GetRefractiveIndex(), rBottom.GetRefractiveIndex());	// (n1/n2)

	cX = cplx.Mul(cX, sin(rInc.GetRayAngle()*MY_PI/180));			// (n1/n2)*sin(theta)
	cX = cplx.Mul(cX, cX);							// ((n1/n2)*sin(theta))^2
	cX = cplx.Sqr(cplx.Sub(1.0, cX));					// ( sqrt(1 - ((n1/n2)*sin(theta))^2)

	COMPLEX cYs = cplx.Mul(rTop.GetRefractiveIndex(), cos(rInc.GetRayAngle()*MY_PI/180));	// n1*cos(theta)
	COMPLEX cZs = cplx.Mul(rBottom.GetRefractiveIndex(), cX);

	//reflectance s- polarization
	double rs = cplx.Magnitude(cplx.Div(cplx.Sub(cYs, cZs), cplx.Add(cYs, cZs)));
	return rs * rs;
}


#endif
