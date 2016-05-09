#ifndef Ray_h
#define Ray_h


#include "ComplexNumber.h"

class Ray {

public:

//constructor prototypes
	Ray();
	Ray(double);
	Ray(double, double);
	Ray(double, double, double);
	Ray(double, double, double, double);
	Ray(double, double, double, double, bool);
	Ray(double, double, double, double, bool, int); 
	~Ray();

//methods
	double GetRayAngle();
	void SetRayAngle(double);

	double GetRayAmplitude();
	void SetRayAmplitude(double);

	double GetRayPhase();
	void SetRayPhase(double);

	double GetRayWavelength();
	void SetRayWavelength(double);

	bool GetRayDirection();
	void SetRayDirection(bool);

	int GetRayLayer();
	void SetRayLayer(int);

private:
	
	double angle;
	double amplitude;
	double phase;
	double wavelength;
	bool direction;
	int layer;
};

//constructors of ray
Ray::Ray() {
	angle = 0.0;
	amplitude = 1.0;
	phase = 0.0;
	wavelength = 1.0;
	direction = true;
	layer = 0;
}

Ray::Ray(double x) {
	angle = x;
	amplitude = 1.0;
	phase = 0.0;
	wavelength = 1.0;
	direction = true;
	layer = 0;
}

Ray::Ray(double x, double y) {
	angle = x;
	amplitude = y;
	phase = 0.0;
	wavelength = 1.0;
	direction = true;
	layer = 0;
}

Ray::Ray(double x, double y, double p) {
	angle = x;
	amplitude = y;
	phase = p;
	wavelength = 1.0;
	direction = true;
	layer = 0;
}

Ray::Ray(double x, double y, double p, double w) {
	angle = x;
	amplitude = y;
	phase = p;
	wavelength = w;
	direction = true;
	layer = 0;
}

Ray::Ray(double x, double y, double p, double w, bool d) {
	angle = x;
	amplitude = y;
	phase = p;
	wavelength = w;
	direction = d;
	layer = 0;
}

Ray::Ray(double x, double y, double p, double w, bool d, int l) {
	angle = x;
	amplitude = y;
	phase = p;
	wavelength = w;
	direction = d;
	layer = l;
}

Ray::~Ray() {
}

double Ray::GetRayAngle() {
	return angle;
}

void Ray::SetRayAngle(double x) {
	angle = x;
}

double Ray::GetRayAmplitude() {
	return amplitude;
}

void Ray::SetRayAmplitude(double x) {
	amplitude = x;
}

double Ray::GetRayPhase() {
	return phase;
}

void Ray::SetRayPhase(double x) {
	phase = x;
}

double Ray::GetRayWavelength() {
	return wavelength;
}

void Ray::SetRayWavelength(double x) {
	wavelength = x;
}

bool Ray::GetRayDirection() {
	return direction;
}

void Ray::SetRayDirection(bool x) {
	direction = x;
}

int Ray::GetRayLayer() {
	return layer;
}

void Ray::SetRayLayer(int x) {
	layer = x;
}



#endif
