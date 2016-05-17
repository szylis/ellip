/* Copyright (C) 2016 Szymon Lis	email: szymonlis@yahoo.com
 * 					twitter: @drSzymonLis
 *
 * This class is designed to solve the reflection and transmiision for optical film
 *
 * To solve the problem, use the public method SolveReflection:
 *	- Layer - reference to Layer class holding material where from light is coming
 *	- Layer - reference to Layer class holding material where the light is traveling
 *	- Layer - reference to Layer Class holding the substrate
 *	- Ray - reference to Ray class holding the incident light beam
 *
 *	This program is distibuteted for free, but WITHOUT ANY WARRANTY
 */

#ifndef Solver_h
#define Solver_h

#include "ComplexNumber.h"
#include "Layer.h"
#include "Ray.h"

#include <iostream>

class Solver {

//constructor
public:
	Solver();
	~Solver();

//prototypes
public:
	void SolveReflection(Layer&, Layer&, Layer&, Ray&);
	void SolveTransmission(Layer&, Layer&, Layer&, Ray&);
	void SolveEllipsometry(Layer&, Layer&, Layer&, Ray&);

	COMPLEX Get_rs() const { return rs; }
	COMPLEX Get_rp() const { return rp; }
	COMPLEX Get_ts() const { return ts; }
	COMPLEX Get_tp() const { return tp; }

	double GetPsi() const { return psi; }
	double GetDel() const { return del; }

	double GetReflectanceS() const { return Rs; }
	double GetReflectanceP() const { return Rp; }
	double GetTransmittanceS() const { return Ts.real; }
	double GetTransmittanceP() const { return Tp.real; }

//methods
private:

	void RefractionAngle(Layer&, Layer&, Ray&, Ray&);
	double PhaseDifference(Layer&, Ray&);

	COMPLEX Find_rs(Layer&, Layer&, Ray&);
	COMPLEX Find_rp(Layer&, Layer&, Ray&);
	COMPLEX Find_ts(Layer&, Layer&, Ray&);
	COMPLEX Find_tp(Layer&, Layer&, Ray&);

	void SolveFilmReflection(COMPLEX (&)[2], COMPLEX (&)[2], double&);
	void SolveFilmTransmission(COMPLEX (&)[2], COMPLEX (&)[2], COMPLEX (&)[2], COMPLEX (&)[2], double&, COMPLEX&);

	void FindReflectance();
	void FindTransmittance(COMPLEX&);

//members
private:
	COMPLEX rs, rp, ts, tp;
	double Rs, Rp;
	COMPLEX Ts, Tp;

	double psi, del;
};

//constructor
Solver::Solver() {
}

Solver::~Solver() {
}


//public method

void Solver::SolveEllipsometry(Layer& rLay1, Layer& rLay2, Layer& rLay3, Ray& rInc) {

	ComplexNumber cplx;
	SolveReflection(rLay1, rLay2, rLay3, rInc);

//PSI
	psi = RAD_TO_DEG(atan((cplx.Magnitude(rp)) / (cplx.Magnitude(rs))));

//DEL
	del = RAD_TO_DEG(cplx.Phase(cplx.Div(rp, rs)));
	if(del < 0.0) del += 180.0;		// <--- NEED TO CHECK IT
}


//method for solving the structure in terms of reflection
void Solver::SolveReflection(Layer& rLay1, Layer& rLay2, Layer& rLay3, Ray& rInc) {

	COMPLEX rs[2];		//0 - rs12, 1 - rs23
	COMPLEX rp[2];		//0 - rp12, 1 - rp23
	double phs;

//setup refracted ray
	Ray refr;
	refr = rInc;
	RefractionAngle(rLay1, rLay2, rInc, refr);

//find the reflection coefficient
	rs[0] = Find_rs(rLay1, rLay2, rInc);
	rp[0] = Find_rp(rLay1, rLay2, rInc);

	rs[1] = Find_rs(rLay2, rLay3, refr);
	rp[1] = Find_rp(rLay2, rLay3, refr);

//optical length difference
	phs = PhaseDifference(rLay2, refr);

//find the total reflectivity of optical film
	SolveFilmReflection(rs, rp, phs);

}

//find rp and rs for total stack of layers
void Solver::SolveFilmReflection(COMPLEX (&rRs)[2], COMPLEX (&rRp)[2], double& rPhs) {

//complex represtation of phase difference
	COMPLEX phasor;
	phasor.real = cos(rPhs);
	phasor.imag = sin(rPhs)*-1.0;


//solve the reflection of film
	ComplexNumber cplx;
	COMPLEX cXrp, cXrs, cYrp, cYrs;

	cXrs = cplx.Mul(rRs[1], phasor);
	cXrp = cplx.Mul(rRp[1], phasor);

	cYrs = cplx.Add(1.0, cplx.Mul(rRs[0], cXrs));
	cYrp = cplx.Add(1.0, cplx.Mul(rRp[0], cXrp));

	cXrs = cplx.Add(rRs[0], cXrs);
	cXrp = cplx.Add(rRp[0], cXrp);

	rs = cplx.Div(cXrs, cYrs);
	rp = cplx.Div(cXrp, cYrp);

	FindReflectance();
}

//reflectance as real number assuming the input intensity of light for both polarzation equal 1
void Solver::FindReflectance() {

	ComplexNumber cplx;
	Rp = cplx.Magnitude(rp);
	Rp = Rp * Rp;

	Rs = cplx.Magnitude(rs);
	Rs = Rs * Rs;
}

//method for solving the structure in terms of transmission
void Solver::SolveTransmission(Layer& rLay1, Layer& rLay2, Layer& rLay3, Ray& rInc) {

	COMPLEX ts[2], tp[2];
	COMPLEX rs[2], rp[2];
	double phs;

//setup refracted ray
	Ray refr;
	refr = rInc;
	RefractionAngle(rLay1, rLay2, rInc, refr);

//find the transmission coefficient
	ts[0] = Find_ts(rLay1, rLay2, rInc);
	tp[0] = Find_tp(rLay1, rLay2, rInc);

	ts[1] = Find_ts(rLay2, rLay3, refr);
	tp[1] = Find_tp(rLay2, rLay3, refr);

//find the reflection coefficient
	rs[0] = Find_rs(rLay1, rLay2, rInc);
	rp[0] = Find_rp(rLay1, rLay2, rInc);

	rs[1] = Find_rs(rLay2, rLay3, refr);
	rp[1] = Find_rp(rLay2, rLay3, refr);

//optical length difference
	phs = PhaseDifference(rLay2, refr);

//find transmittance factor
	Ray tran;
	tran = refr;
	RefractionAngle(rLay2, rLay3, refr, tran);

	ComplexNumber cplx;
	COMPLEX tCX, tCY, tFactor;

	tCX = cplx.Mul(rLay3.GetRefractiveIndex(), cos(DEG_TO_RAD(tran.GetRayAngle())));
	tCY = cplx.Mul(rLay1.GetRefractiveIndex(), cos(DEG_TO_RAD(rInc.GetRayAngle())));

	tFactor = cplx.Div(tCX, tCY);

//find the total transmission coefficient of an optical film
	SolveFilmTransmission(ts, tp, rs, rp, phs, tFactor);

}

//find tp and ts for total stack of layers
void Solver::SolveFilmTransmission(COMPLEX (&rTs)[2], COMPLEX (&rTp)[2], COMPLEX (&rRs)[2], COMPLEX (&rRp)[2], double& rPhs, COMPLEX& rTfactor) {

//complex representation of phase difference
	COMPLEX phasor;
	phasor.real = cos(rPhs);
	phasor.imag = sin(rPhs)*-1.0;

	COMPLEX phrDiv2;
	phrDiv2.real = cos(rPhs/2.0);
	phrDiv2.imag = sin(rPhs/2.0) * -1.0;

	ComplexNumber cplx;
	COMPLEX cXtp, cXts, cYtp, cYts;

	cXts = cplx.Mul(rTs[0], cplx.Mul(rTs[1], phrDiv2));
	cXtp = cplx.Mul(rTp[0], cplx.Mul(rTp[1], phrDiv2));

	cYts = cplx.Add(1.0, cplx.Mul(rRs[0], cplx.Mul(rRs[1], phasor)));
	cYtp = cplx.Add(1.0, cplx.Mul(rRp[0], cplx.Mul(rRp[1], phasor)));

	ts = cplx.Div(cXts, cYts);
	tp = cplx.Div(cXtp, cYtp);

	FindTransmittance(rTfactor);
}

//transmittance as real number assuming the input intensity of light for both polarzation equal 1
void Solver::FindTransmittance(COMPLEX& rTfactor) {

	ComplexNumber cplx;
	Tp = cplx.Magnitude(tp);
	Tp = cplx.Mul(rTfactor, cplx.Mul(Tp, Tp));

	Ts = cplx.Magnitude(ts);
	Ts = cplx.Mul(rTfactor, cplx.Mul(Ts, Ts));
}

// ----- PRIVATE METHODS -----
//change phase according to the distance traveled by light
double Solver::PhaseDifference(Layer& rLayer, Ray& rRay) {

	double x = 2.0*rLayer.GetThickness()*cos((DEG_TO_RAD(rRay.GetRayAngle())));
	double kVector = (2*MY_PI*rLayer.GetRefractiveIndex().real)/rRay.GetRayWavelength();

	return kVector*x;
}


//find the angle of refraction Snell's Law
void Solver::RefractionAngle(Layer& rA, Layer& rB, Ray& rI, Ray& rR) {

	ComplexNumber cplx;
	COMPLEX cX;
	cX = cplx.Div(rA.GetRefractiveIndex(), rB.GetRefractiveIndex());
	cX = cplx.Mul(cX, sin(DEG_TO_RAD(rI.GetRayAngle())));

	//when the total internal reflection
	if(cX.real > 1.0) {
		rR.SetRayAngle(90.0);
	}
	else {
		rR.SetRayAngle(RAD_TO_DEG(asin(cX.real)));
	}
}

//reflection coefficient of p-type polarization
COMPLEX Solver::Find_rp(Layer& rTop, Layer& rBottom, Ray& rInc) {

	ComplexNumber cplx;

	COMPLEX cX = cplx.Div(rTop.GetRefractiveIndex(), rBottom.GetRefractiveIndex());	// (n1/n2)

	cX = cplx.Mul(cX, sin(DEG_TO_RAD(rInc.GetRayAngle())));			// (n1/n2)*sin(theta)
	cX = cplx.Mul(cX, cX);							// ((n1/n2)*sin(theta))^2
	cX = cplx.Sqr(cplx.Sub(1.0, cX));					// ( sqrt(1 - ((n1/n2)*sin(theta))^2)

	COMPLEX cYp = cplx.Mul(rBottom.GetRefractiveIndex(), cos(DEG_TO_RAD(rInc.GetRayAngle())));	// n2*cos(theta)
	COMPLEX cZp = cplx.Mul(rTop.GetRefractiveIndex(), cX);

	return cplx.Div(cplx.Sub(cZp, cYp), cplx.Add(cZp, cYp));
}

//transmission coefficient of p-type polarization
COMPLEX Solver::Find_tp(Layer& rTop, Layer& rBottom, Ray& rInc) {

	ComplexNumber cplx;

	COMPLEX cX = cplx.Div(rTop.GetRefractiveIndex(), rBottom.GetRefractiveIndex());	// (n1/n2)

	cX = cplx.Mul(cX, sin(DEG_TO_RAD(rInc.GetRayAngle())));			// (n1/n2)*sin(theta)
	cX = cplx.Mul(cX, cX);							// ((n1/n2)*sin(theta))^2
	cX = cplx.Sqr(cplx.Sub(1.0, cX));					// ( sqrt(1 - ((n1/n2)*sin(theta))^2)

	COMPLEX cYp = cplx.Mul(rBottom.GetRefractiveIndex(), cos(DEG_TO_RAD(rInc.GetRayAngle())));	// n2*cos(theta)
	COMPLEX cWp = cplx.Mul(rTop.GetRefractiveIndex(), cos(DEG_TO_RAD(rInc.GetRayAngle())));		// n1*cos(theta)
	COMPLEX cZp = cplx.Mul(rTop.GetRefractiveIndex(), cX);

	return cplx.Div(cplx.Mul(2.0, cWp), cplx.Add(cZp, cYp));
}


//reflection coefficient of s-type polarization
COMPLEX Solver::Find_rs(Layer& rTop, Layer& rBottom, Ray& rInc) {

	ComplexNumber cplx;

	COMPLEX cX = cplx.Div(rTop.GetRefractiveIndex(), rBottom.GetRefractiveIndex());	// (n1/n2)

	cX = cplx.Mul(cX, sin(DEG_TO_RAD(rInc.GetRayAngle())));			// (n1/n2)*sin(theta)
	cX = cplx.Mul(cX, cX);							// ((n1/n2)*sin(theta))^2
	cX = cplx.Sqr(cplx.Sub(1.0, cX));					// ( sqrt(1 - ((n1/n2)*sin(theta))^2)

	COMPLEX cYs = cplx.Mul(rTop.GetRefractiveIndex(), cos(DEG_TO_RAD(rInc.GetRayAngle())));	// n1*cos(theta)
	COMPLEX cZs = cplx.Mul(rBottom.GetRefractiveIndex(), cX);

	return cplx.Div(cplx.Sub(cYs, cZs), cplx.Add(cYs, cZs));
}

//transmission coefficient of s-type polarization
COMPLEX Solver::Find_ts(Layer& rTop, Layer& rBottom, Ray& rInc) {

	ComplexNumber cplx;

	COMPLEX cX = cplx.Div(rTop.GetRefractiveIndex(), rBottom.GetRefractiveIndex());	// (n1/n2)

	cX = cplx.Mul(cX, sin(DEG_TO_RAD(rInc.GetRayAngle())));			// (n1/n2)*sin(theta)
	cX = cplx.Mul(cX, cX);							// ((n1/n2)*sin(theta))^2
	cX = cplx.Sqr(cplx.Sub(1.0, cX));					// ( sqrt(1 - ((n1/n2)*sin(theta))^2)

	COMPLEX cYs = cplx.Mul(rTop.GetRefractiveIndex(), cos(DEG_TO_RAD(rInc.GetRayAngle())));	// n1*cos(theta)
	COMPLEX cZs = cplx.Mul(rBottom.GetRefractiveIndex(), cX);

	return cplx.Div(cplx.Mul(2.0, cYs), cplx.Add(cYs, cZs));
}


#endif
