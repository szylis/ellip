#ifndef HitPoint_h
#define HitPoint_h


#include "ComplexNumber.h"
#include "Layer.h"
#include "Ray.h"
#include <iostream>

class HitPoint {

public:

//constructor
	HitPoint(Layer&, Layer&, Ray&, Ray&, Ray&);
	~HitPoint();

//prototypes
private:
	void ReflectionPhaseShift(Ray&);
	void Reflectance(Layer&, Layer&, Ray&, Ray&);
	
	double FindRp(Layer&, Layer&, Ray&);
	double FindRs(Layer&, Layer&, Ray&);
};

//constructor
HitPoint::HitPoint(Layer& rTopLayer, Layer& rBottomLayer, Ray& rInc, Ray& rRefl, Ray& rRefr) {

	//reflection
	rRefl = rInc;

	rRefl.SetRayDirection(!rInc.GetRayDirection());  	//invers diretion of propagation
	ReflectionPhaseShift(rRefl);				//phase shift for reflection ray
	Reflectance(rTopLayer, rBottomLayer, rInc, rRefl);	//find the reflectance for p- and s- polarization

	//refraction
	rRefr = rInc;
}

HitPoint::~HitPoint() {
}


//methods

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

void HitPoint::Reflectance(Layer& rTop, Layer& rBottom, Ray& rInc, Ray& rR) {

	rR.SetRayAmp_p(FindRp(rTop, rBottom, rInc));
	rR.SetRayAmp_s(FindRs(rTop, rBottom, rInc));

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
