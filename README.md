# ellip
Single-wavelength null type ellipsometer solver

Copyright (C) 2016 Szymon Lis
email: szymonlis@yahoo.com
twitter: @drSzymonLis

This program is distibuteted for free, but WITHOUT ANY WARRANTY

1. Description

Script design to a solve three layers stack in terms of reflectance, transmittance and ellipsometry parameters (DEL, PSI).

2. Compilation

Modify the main.cpp according to your needs, then compile it using standard c++11 compiler:

	g++ -std=c++11 -pthread ${SRC_DIR}/main.cpp -o ellip 

3. Limitations

Results can be obtained for single-wavelength;
Only there layers stack can be solved;
The complex refractive index was not fully tested yet;

4. Further work

	Implementation of a layer refractive index dependence on the wavelength;
	Testing the complex refractive index and plasmon behaviour for metal layers;
	Increment the capability of solving more than three layers (Transfer-matrix method)

