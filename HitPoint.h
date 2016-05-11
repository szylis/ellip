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


};

//constructor
HitPoint::HitPoint(Ray rInc, Layer layer, Ray &rRefl, Ray &rRefr) {

	rRefl.SetRayAngle(30.0);
}

HitPoint::~HitPoint() {
}

//methods

#endif
