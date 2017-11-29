/**
* \file      HeatConduction.cpp
* \author    M Le Clec'h
* \version   1.0
* \date      05 December 2017
* \brief     Different objects to resolve an Heat Conduction problem.
*
* \details   There are 4 schemes which can be use :
*              - The DuFort-Frankel scheme
*              - The Richardson scheme
*              - The Laasonen scheme
*              - The Crank-Nicholson scheme
*			It can also provide the analytical solution.
*/

#include "HeatConduction.h"
#include <cmath>

const double pi = atan(1) * 4; //!< define pi

//
// ...... BASE CLASS ......
//

/**
* \fn HeatConduction::HeatConduction(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt)
* \brief Constructor of the HeatConduction class
*
* \param Tin_0 - initial condition Temperature inside
* \param Text_0 - initial condition Temperature outside
* \param Xmin - the X position far left
* \param Xmax - the X position far right
* \param Tend - the end time of the simulation
* \param D - the difusivity of the wall
* \param dx - the space step
* \param dt - the time step
*/
HeatConduction::HeatConduction(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt){
	this->Tin_0 = Tin_0;
	this->Text_0 = Text_0;
	this->Xmin = Xmin;
	this->Xmax = Xmax;
	this->Tend = Tend;
	this->D = D;
	this->dx = dx;
	this->dt = dt;

	r = (D*dt) / (dx*dx);
	n = int(Tend / dt);
	s = int((Xmax - Xmin) / dx);

	u_nplus1 = std::vector<double>(s+1);
	u_n = std::vector<double>(s+1);
	u_nminus1 = std::vector<double>(s+1);
}

/**
* \fn void HeatConduction::solve()
* \brief Abstract solve
*
* \return void - the result is stored in the vector u_n of the mother Class
*/
void HeatConduction::solve() {}

/**
* \fn std::vector<double> HeatConduction::get_u_n() const
* \brief Get method of the attribute u_n
*
* \return u_n - a vector attribute of the mother Class
*/
std::vector<double> HeatConduction::get_u_n() const {
	return u_n;
}

//
// ...... SUB CLASS ......
//

/**
* \fn AnalyticalSolution::AnalyticalSolution(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt)
* \brief Constructor of the AnalyticalSolution class
*
* \param Tin_0 - initial condition Temperature inside
* \param Text_0 - initial condition Temperature outside
* \param Xmin - the X position far left
* \param Xmax - the X position far right
* \param Tend - the end time of the simulation
* \param D - the difusivity of the wall
* \param dx - the space step
* \param dt - the time step
*/
AnalyticalSolution::AnalyticalSolution(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt) : HeatConduction(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt) {}

/**
* \fn void AnalyticalSolution::solve()
* \brief Solve with the analytical solution
*
* \return void - the result is stored in the vector u_n of the mother Class
*/
void AnalyticalSolution::solve(){
	double x = Xmin;
	double L = Xmax - Xmin;
	for (int i = 0; i < s + 1; i++){
		double somme = 0;
		for (int m = 1; m < 10; m++){
			somme += exp(-D*pow(m*pi / L, 2)*Tend) * ((1 - pow(-1, m)) / (m*pi)) * sin((m*pi*x) / L);
		}
		u_n[i] = Text_0 + 2 * (Tin_0 - Text_0) * somme;
		x += dx;
	}
}

/**
* \fn ExplicitMethod::ExplicitMethod(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt)
* \brief Constructor of the ExplicitMethod class
*
* \param Tin_0 - initial condition Temperature inside
* \param Text_0 - initial condition Temperature outside
* \param Xmin - the X position far left
* \param Xmax - the X position far right
* \param Tend - the end time of the simulation
* \param D - the difusivity of the wall
* \param dx - the space step
* \param dt - the time step
*/
ExplicitMethod::ExplicitMethod(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt) : HeatConduction(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt) {}

/**
* \fn ExplicitMethod::advance(int i)
* \brief Abstract method implemented in the sub sub classes
*
* \param i - the space iteration at which is the solve method
* \return void - the result is stored in the vector u_nplus1 of the mother Class
*/
void ExplicitMethod::advance(int i){}

/**
* \fn void ExplicitMethod::solve()
* \brief Solve regroup the common part of the Explicit Method
*
* \return void - the result is stored in the vector u_n of the mother Class
*/
void ExplicitMethod::solve(){
	/* initialisation n = -1 and n = 0 */
	for (int i = 0; i < s + 1; i++){
		u_nminus1[i] = Tin_0;
		u_n[i] = Tin_0;
	}
	u_n[0] = Text_0;
	u_n[s] = Text_0;

	/* Calculte n = 1 and so on */
	for (int j = 1; j < n + 1; j++){
		u_nplus1[0] = Text_0; //boundaries conditions
		u_nplus1[s] = Text_0; //boundaries conditions
		for (int i = 1; i < s; i++){
			advance(i); // u_nplus1 is define accrding the scheme used
		}
		u_nminus1 = u_n;
		u_n = u_nplus1;
	}
}

/**
* \fn ImplicitMethod::ImplicitMethod(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt)
* \brief Constructor of the ImplicitMethod class
*
* \param Tin_0 - initial condition Temperature inside
* \param Text_0 - initial condition Temperature outside
* \param Xmin - the X position far left
* \param Xmax - the X position far right
* \param Tend - the end time of the simulation
* \param D - the difusivity of the wall
* \param dx - the space step
* \param dt - the time step
*/
ImplicitMethod::ImplicitMethod(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt) : HeatConduction(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt) {
	m = 0;
	a = std::vector<double>(s - 1);
	b = std::vector<double>(s - 1);
	c = std::vector<double>(s - 1);
	d = std::vector<double>(s - 1);

	// initialisation of u_n for n = 0
	for (int i = 1; i < s; i++){
		u_n[i] = Tin_0;
	}
	u_n[0] = Text_0;
	u_n[s] = Text_0;
}

/**
* \fn void ImplicitMethod::solve
* \brief Abstract solve
*
* \return void - the result is stored in the vector u_n of the mother Class
*/
void ImplicitMethod::solve() {}

/**
* \fn void ImplicitMethod::ThomasAlgorith()
* \brief The Thomas Algorith, to solve Tridiagonal matrix problem
*
* \return void - the result is stored in the vector u_n of the mother Class
*/
void ImplicitMethod::ThomasAlgorith() {
	//Forward elimination phase
	for (int k = 1; k < s - 1; k++){
		m = a[k] / b[k - 1];
		b[k] = b[k] - (m*c[k - 1]);
		d[k] = d[k] - (m*d[k - 1]);
	}

	//Backward elimination phase
	u_nplus1[s] = Text_0;
	u_nplus1[0] = Text_0;
	u_nplus1[s - 1] = d[s - 2] / b[s - 2];
	for (int k = s - 3; k > -1; k--){
		u_nplus1[k + 1] = (d[k] - (c[k] * u_nplus1[k + 2])) / b[k];
	}

	u_n = u_nplus1;
}

//
// ...... SUB SUB CLASS ......
//

/**
* \fn DuFort_Frankel::DuFort_Frankel(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt)
* \brief Constructor of the DuFort_Frankel class
*
* \param Tin_0 - initial condition Temperature inside
* \param Text_0 - initial condition Temperature outside
* \param Xmin - the X position far left
* \param Xmax - the X position far right
* \param Tend - the end time of the simulation
* \param D - the difusivity of the wall
* \param dx - the space step
* \param dt - the time step
*/
DuFort_Frankel::DuFort_Frankel(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt) : ExplicitMethod(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt) {}

/**
* \fn DuFort_Frankel::advance(int i)
* \brief Calcul of un_plus1 according to DuFort_Frankel scheme
*
* \param i - the space iteration at which is the solve method
* \return void - the result is stored in the vector u_nplus1 of the mother Class
*/
void DuFort_Frankel::advance(int i){	
	u_nplus1[i] = (u_nminus1[i] + 2*r*(u_n[i+1] - u_nminus1[i] + u_n[i-1])) /  (1 + 2*r);
}

/**
* \fn Richardson::Richardson(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt)
* \brief Constructor of the Richardson class
*
* \param Tin_0 - initial condition Temperature inside
* \param Text_0 - initial condition Temperature outside
* \param Xmin - the X position far left
* \param Xmax - the X position far right
* \param Tend - the end time of the simulation
* \param D - the difusivity of the wall
* \param dx - the space step
* \param dt - the time step
*/
Richardson::Richardson(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt) : ExplicitMethod(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt) {}

/**
* \fn void Richardson::advance(int i)
* \brief Calcul of un_plus1 according to Richardson scheme
*
* \param i - the space iteration at which is the solve method
* \return void - the result is stored in the vector u_nplus1 of the mother Class
*/
void Richardson::advance(int i){
	u_nplus1[i] = u_nminus1[i] + 2 * r * (u_n[i + 1] - (2 * u_n[i] + u_n[i - 1]));
}

/**
* \fn Laasonen::Laasonen(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt)
* \brief Constructor of the Laasonen class
*
* \param Tin_0 - initial condition Temperature inside
* \param Text_0 - initial condition Temperature outside
* \param Xmin - the X position far left
* \param Xmax - the X position far right
* \param Tend - the end time of the simulation
* \param D - the difusivity of the wall
* \param dx - the space step
* \param dt - the time step
*/
Laasonen::Laasonen(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt) : ImplicitMethod(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt) {}

/**
* \fn void Laasonen::solve()
* \brief Solve method. The matrix abc and the vector d are define after the Laasonen scheme
*
* \return void - the result is stored in the vector u_n of the mother Class
*/
void Laasonen::solve(){ 
	for (int i = 0; i < s-1; i++){
		a[i] = -r; // bottom diagonal
		b[i] = 2*r + 1; // central diagonal
		c[i] = -r; // upper diagonal	
		d[i] = u_n[i+1];
	}
	a[0] = 0;
	c[s - 2] = 0;

	for (int j = 1; j < n + 1; j++){
		//Boundaries conditions
		d[0] += Text_0 * r;
		d[s - 2] += Text_0 * r;

		ThomasAlgorith();

		// we set back correctly the vector b
		for (int i = 0; i < s - 1; i++){
			b[i] = 2 * r + 1; // central diagonal
			d[i] = u_n[i + 1];
		}
	}
}

/**
* \fn CrankNicholson::CrankNicholson(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt)
* \brief Constructor of the Laasonen class
*
* \param Tin_0 - initial condition Temperature inside
* \param Text_0 - initial condition Temperature outside
* \param Xmin - the X position far left
* \param Xmax - the X position far right
* \param Tend - the end time of the simulation
* \param D - the difusivity of the wall
* \param dx - the space step
* \param dt - the time step
*/
CrankNicholson::CrankNicholson(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt) : ImplicitMethod(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt) {}

/**
* \fn void CrankNicholson::solve()
* \brief Solve method. The matrix abc and the vector d are define after the Crank-Nicholson scheme
*
* \return void - the result is stored in the vector u_n of the mother Class
*/
void CrankNicholson::solve(){
	for (int i = 0; i < s - 1; i++){
		a[i] = -r/2; // bottom diagonal
		b[i] = r + 1; // central diagonal
		c[i] = -r/2; // upper diagonal
		d[i] = (r/2)*u_n[i+2] + (1-r)*u_n[i+1] + (r/2)*u_n[i]; //vector on the right of the eq
	}
	a[0] = 0;
	c[s - 2] = 0;

	for (int j = 1; j < n + 1; j++){
		//Boundaries conditions
		d[0] += Text_0 * (r/2);
		d[s - 2] += Text_0 * (r/2);

		ThomasAlgorith();

		// we set back correctly the vector b and d
		for (int i = 0; i < s - 1; i++){
			b[i] = r + 1; // central diagonal
			d[i] = (r / 2)*u_n[i + 2] + (1 - r)*u_n[i + 1] + (r / 2)*u_n[i];
		}
	}
}