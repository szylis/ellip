/* Copyright (C) 2016 Szymon Lis			email: szymonlis@yahoo.com
 *							twitter: @drSzymonLis
 *
 * Class holding the physical layer object
 *
 * Layer is characterized by:
 *	- complex refractive index
 *	- thickness
 *	- position number (counting from the top (air -> substrate),
 *		where layer number 0 is assumed to be air)
 *
 * NOTE: If you set a layer at 0 postion the 0.0um thickness is forced
 *
 * This program is distibuteted for free, but WITHOUT ANY WARRANTY
 *
 */

#ifndef Layer_h
#define Layer_h

#include "ComplexNumber.h"

class Layer {

public:

//constructors
	Layer();
	Layer(int, COMPLEX, double);
	~Layer();

//prototypes
	COMPLEX GetRefractiveIndex() const;
	void SetRefractiveIndex(COMPLEX);

	int GetPosition() const;
	void SetPosition(int);

	double GetThickness() const;
	void SetThickness(double);

//members
private:

	COMPLEX refractiveIndex;	//refractive index
	double thickness;		//thickness of layer
	int position;			//number of layer on the layer stack
};


//definition of layer constructors
Layer::Layer() {
	position = 0;
	refractiveIndex = {1.0, 0.0};
	thickness = 0.0;
}

Layer::Layer(int x, COMPLEX y, double z) {
	position = x;
	refractiveIndex = y;
	thickness = z;
	if(position==0) { thickness=0.0; }	//keep the top layer on some 0.0 thickness
}

//deconstructor
Layer::~Layer() {
}


//definition of methods
COMPLEX Layer::GetRefractiveIndex() const {
	return {refractiveIndex.real, refractiveIndex.imag};
}

void Layer::SetRefractiveIndex(COMPLEX x) {
	refractiveIndex = x;
}

int Layer::GetPosition() const {
	return position;
}

void Layer::SetPosition(int x) {
	position = x;
}

double Layer::GetThickness() const {
	return thickness;
}

void Layer::SetThickness(double x) {
	thickness = x;
	if(position==0) { thickness = 0.0; }	//to keep uniform thickness of top layer
}


#endif
