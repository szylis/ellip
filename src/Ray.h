/* Copyright (C) 2016 Szymon Lis			email: szymonlis@yahoo.com
 *							twitter: @drSzymonLis
 *
 * Class holding the light ray object
 *
 * Ray is characterised by:
 *	- angle of ray propagation in reference to layer stack normal
 *	- amp_p amplitude of 'p' type polarization
 *	- amp_s amplitude of 's' type polarization
 *	- phase of the ray [rad]
 *	- wavelength of the ray [um]
 *	- direction (true: for transmission towards substrate; false: towards air)
 *	- layer where ray is at particular moment
 *
 */

#ifndef Ray_h
#define Ray_h


#include "ComplexNumber.h"

class Ray {

public:

//constructor prototypes
	Ray();
	Ray(double, double, double, double, double);
	Ray(double, double, double, double, double, bool, int);
	~Ray();

//prototypes
	double GetRayAngle() const;
	void SetRayAngle(double);

	double GetRayAmp_p() const;
	void SetRayAmp_p(double);

	double GetRayAmp_s() const;
	void SetRayAmp_s(double);

	double GetRayPhase() const;
	void SetRayPhase(double);

	double GetRayWavelength() const;
	void SetRayWavelength(double);

	bool GetRayDirection() const;
	void SetRayDirection(bool);

	int GetRayLayer() const;
	void SetRayLayer(int);

//members
private:

	double angle;		//angle of propagation
	double amp_p;		//'p' type polarization amplitude
	double amp_s;		//'s' type polarization amplitude
	double phase;		//phase [rad]
	double wavelength;	//wavelength [um]
	bool direction;		//true when ray travels towards substrate
	int layer;		//number of layer where ray is
};

//definition of ray constructors
Ray::Ray() {
	angle = 0.0;
	amp_p = 1.0;
	amp_s = 1.0;
	phase = 0.0;
	wavelength = 1.0;
	direction = true;
	layer = 0;
}

Ray::Ray(double x, double p, double s, double y, double w) {
	angle = x;
	amp_p = p;
	amp_s = s;
	phase = y;
	wavelength = w;
	direction = true;
	layer = 0;
}

Ray::Ray(double x, double p, double s, double y, double w, bool d, int l) {
	angle = x;
	amp_p = p;
	amp_s = s;
	phase = y;
	wavelength = w;
	direction = d;
	layer = l;
}

//deconstructor
Ray::~Ray() {
}

//definition of methods
double Ray::GetRayAngle() const {
	return angle;
}

void Ray::SetRayAngle(double x) {
	angle = x;
}

double Ray::GetRayAmp_p() const {
	return amp_p;
}

void Ray::SetRayAmp_p(double x) {
	amp_p = x;
}

double Ray::GetRayAmp_s() const {
	return amp_s;
}

void Ray::SetRayAmp_s(double x) {
	amp_s = x;
}

double Ray::GetRayPhase() const {
	return phase;
}

void Ray::SetRayPhase(double x) {
	phase = x;
}

double Ray::GetRayWavelength() const {
	return wavelength;
}

void Ray::SetRayWavelength(double x) {
	wavelength = x;
}

bool Ray::GetRayDirection() const {
	return direction;
}

void Ray::SetRayDirection(bool x) {
	direction = x;
}

int Ray::GetRayLayer() const {
	return layer;
}

void Ray::SetRayLayer(int x) {
	layer = x;
}

#endif
