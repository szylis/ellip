#ifndef HitPoint_h
#define HitPoint_h


#include "ComplexNumber.h"
#include "Layer.h"
#include "Ray.h"

class HitPoint {

public:

//constructor
	HitPoint();	//do not how to run test without this constructor, not need it for final product
	HitPoint(Ray, Layer, Ray&, Ray&);
	~HitPoint();

//prototypes


};

//constructors
HitPoint::HitPoint() {
}

HitPoint::HitPoint(Ray rInc, Layer layer, Ray &rRefl, Ray &rRefr) {

	rRefl = rInc;
	rRefr = rInc; 

}

HitPoint::~HitPoint() {
}

//methods

#endif
