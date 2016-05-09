#ifndef Layer_h
#define Layer_h


#include "ComplexNumber.h"

class Layer {

public:

	Layer();
	Layer(COMPLEX);
	Layer(COMPLEX, double);
	~Layer();

	COMPLEX GetRefractiveIndex();
	void SetRefractiveIndex(COMPLEX);

	double GetThickness();
	void SetThickness(double);


private:

	COMPLEX refractiveIndex;	//refractive index
	double thickness;		//thickness of layer
};


//constrtuctors of layers
Layer::Layer() {
	refractiveIndex = {1.0, 0.0}; 
	thickness = 0.0;
}

Layer::Layer(COMPLEX x) {
	refractiveIndex = x;
	thickness = 0.0;
}

Layer::Layer(COMPLEX x, double y) {
	refractiveIndex = x;
	thickness = y;
}

Layer::~Layer() {
}

COMPLEX Layer::GetRefractiveIndex() {	
	return {refractiveIndex.real, refractiveIndex.imag};
}

void Layer::SetRefractiveIndex(COMPLEX x) {
	refractiveIndex = x;
}

double Layer::GetThickness() {
	return thickness;
}

void Layer::SetThickness(double x) {
	thickness = x;
}


#endif
