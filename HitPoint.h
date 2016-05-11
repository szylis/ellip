#ifndef HitPoint_h
#define HitPoint_h


#include "ComplexNumber.h"
#include "Layer.h"
#include "Ray.h"
#include <iostream>

class HitPoint {

public:

//constructor
	HitPoint(Ray, Layer, Ray&, Ray&);
	~HitPoint();

//prototypes
private:
	void ReflectionPhaseShift(Ray&);
};

//constructor
HitPoint::HitPoint(Ray inc, Layer layer, Ray &rRefl, Ray &rRefr) {

	rRefl = inc;
	ReflectionPhaseShift(rRefl);			//phase shift for reflection ray
	rRefl.SetRayDirection(!inc.GetRayDirection());  //invers diretion of propagation
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


#endif
