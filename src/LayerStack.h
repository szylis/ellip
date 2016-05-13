/* Copyright (C) 2016 Szymon Lis		email: szymonlis@yahoo.com
 *						twitter: @drSzymonLis
 *
 * Class holding the stack of layers
 *
 */

#ifndef LayerStack_h
#define LayerStack_h

#include "ComplexNumber.h"
#include "Ray.h"
#include "Layer.h"
#include "HitPoint.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include <iostream>

using namespace std;
using namespace boost;
class LayerStack {

//constructor
public:
	LayerStack();
	LayerStack(unsigned int);
	~LayerStack();

//methods:
	void Solve(ptr_vector<Layer>, Ray&, double&, double&);

};



//constructor
LayerStack::LayerStack() {
}

LayerStack::LayerStack(unsigned int m) {
	cout << m << endl;
} 

LayerStack::~LayerStack() {
}

//methods
void LayerStack::Solve(ptr_vector<Layer> vStc, Ray& rIn, double& rRp, double& rRs) {

	rRp = rIn.GetRayAmp_p();
	rRs = rIn.GetRayAmp_s();
}

#endif
