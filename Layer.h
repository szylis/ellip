//-------------------------------------------------------------------------------------------------------
//
// Class holding the physical layer object
//
// Layer is characterized by:
//	- complex refractive index
//	- thickness
//	- position number (counting from the top (air -> substrate),
//		where layer number 0 is assumed to be air)
// 
// Author: Szymon Lis	twitter: @drSzymonLis	email: szymonlis@yahoo.com
//
//-----------------------------------------------------------------------------------------------------

#ifndef Layer_h
#define Layer_h

#include "ComplexNumber.h"

class Layer {

public:

//constructors
	Layer();
	Layer(COMPLEX);
	Layer(COMPLEX, int);
	Layer(COMPLEX, int, double);
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
	refractiveIndex = {1.0, 0.0};
	position = 0; 
	thickness = 0.0;
}

Layer::Layer(COMPLEX x) {
	refractiveIndex = x;
	position = 0;
	thickness = 0.0;
}

Layer::Layer(COMPLEX x, int y) {
	refractiveIndex = x;
	position = y;
	thickness = 0.0;
}

Layer::Layer(COMPLEX x, int y, double z) {
	refractiveIndex = x;
	position = y;
	thickness = z;
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
}


#endif