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

	COMPLEX n;	//refractive index
	double t;	//thickness of layer
};


//constrtuctors of layers
Layer::Layer() {
	n = {1.0, 0.0}; 
	t = 0.0;
}

Layer::Layer(COMPLEX refractiveIndex) {
	n = refractiveIndex;
	t = 0.0;
}

Layer::Layer(COMPLEX refractiveIndex, double thickness) {
	n = refractiveIndex;
	t = thickness;
}

Layer::~Layer() {
}

COMPLEX Layer::GetRefractiveIndex() {	
	return {n.real, n.imag};
}

void Layer::SetRefractiveIndex(COMPLEX refractiveIndex) {
	n = refractiveIndex;
}

double Layer::GetThickness() {
	return t;
}

void Layer::SetThickness(double thickness) {
	t = thickness;
}


#endif
