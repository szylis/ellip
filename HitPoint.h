#ifndef HitPoint_h
#define HitPoint_h


#include "ComplexNumber.h"
#include "Layer.h"
#include "Ray.h"
#include <iostream>

class HitPoint {

public:

//constructor
	HitPoint(Layer, Layer, Ray,  Ray&, Ray&);
	~HitPoint();

//prototypes
private:
	void ReflectionPhaseShift(Ray&);
	void Reflectance(Layer, Layer, Ray, Ray&);
};

//constructor
HitPoint::HitPoint(Layer topLayer, Layer bottomLayer, Ray inc, Ray &rRefl, Ray &rRefr) {

	rRefl = inc;
	rRefl.SetRayDirection(!inc.GetRayDirection());  //invers diretion of propagation
	ReflectionPhaseShift(rRefl);			//phase shift for reflection ray
	Reflectance(topLayer, bottomLayer, inc, rRefl);	//find the reflectance for p- and s- polarization
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

void HitPoint::Reflectance(Layer top, Layer bottom, Ray inc, Ray& rR) {

	ComplexNumber cplx;

	COMPLEX cX = cplx.Div(top.GetRefractiveIndex(), bottom.GetRefractiveIndex());	// (n1/n2)

	cX = cplx.Mul(cX, sin(inc.GetRayAngle()*MY_PI/180));			// (n1/n2)*sin(theta)
	cX = cplx.Mul(cX, cX);							// ((n1/n2)*sin(theta))^2
	cX = cplx.Sqr(cplx.Sub(1.0, cX));					// ( sqrt(1 - ((n1/n2)*sin(theta))^2)


	COMPLEX cYp = cplx.Mul(bottom.GetRefractiveIndex(), cos(inc.GetRayAngle()*MY_PI/180));	// n2*cos(theta)
	COMPLEX cYs = cplx.Mul(top.GetRefractiveIndex(), cos(inc.GetRayAngle()*MY_PI/180));	// n1*cos(theta)

	COMPLEX cZp = cplx.Mul(top.GetRefractiveIndex(), cX);
	COMPLEX cZs = cplx.Mul(bottom.GetRefractiveIndex(), cX);

	//reflectance p- polarization
	double rp = cplx.Magnitude(cplx.Div(cplx.Sub(cZp, cYp), cplx.Add(cZp, cYp)));
	rp = rp * rp;

	//reflectance s- polarization
	double rs = cplx.Magnitude(cplx.Div(cplx.Sub(cYs, cZs), cplx.Add(cYs, cZs)));
	rs = rs * rs;

	rR.SetRayAmp_p(rp);
	rR.SetRayAmp_s(rs);
}

#endif
