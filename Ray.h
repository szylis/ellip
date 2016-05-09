#ifndef Ray_h
#define Ray_h


#include "ComplexNumber.h"

class Ray {

public:

	Ray();
	Ray(double);
	Ray(double, double);
	~Ray();

	double GetPropagationAngle();
	void SetPropagationAngle(double);

	double GetRayAmplitude();
	void SetRayAmplitude(double);

private:
	
	double angle;
	double amplitude;

};

//constructors of ray
Ray::Ray() {
	angle = 0.0;
	amplitude = 1.0;
}

Ray::Ray(double x) {
	angle = x;
	amplitude = 1.0;
}

Ray::Ray(double x, double y) {
	angle = x;
	amplitude = y;
}

Ray::~Ray() {
}

double Ray::GetPropagationAngle() {
	return angle;
}

void Ray::SetPropagationAngle(double x) {
	angle = x;
}

double Ray::GetRayAmplitude() {
	return amplitude;
}

void Ray::SetRayAmplitude(double y) {
	amplitude = y;
}
	
		


#endif
