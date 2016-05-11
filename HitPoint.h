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
		COMPLEX cX = cplx.Mul(bottom.GetRefractiveIndex(), cos(inc.GetRayAngle()*MY_PI/180));

		std::cout << cX.real << std::endl;
		std::cout << cX.imag << std::endl;
		rR.SetRayAmp_p(0.04);
}

#endif
