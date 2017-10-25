#include "HeatConduction.h"

// abstract base class

HeatConduction::HeatConduction() {}

HeatConduction::HeatConduction(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt){
	this->Tin_0 = Tin_0;
	this->Text_0 = Text_0;
	this->Xmin = Xmin;
	this->Xmax = Xmax;
	this->Tend = Tend;
	this->D = D;
	this->dx = dx;
	this->dt = dt;

	n = Tend / dt;
	s = (Xmax - Xmin) / dx;

	t = std::vector<double>(n+1);
	u_nplus1 = std::vector<double>(s+1);
	u_n = std::vector<double>(s+1);
	u_nminus1 = std::vector<double>(s+1);
}

void HeatConduction::solve() {}

std::vector<double> HeatConduction::get_t() const {
	return t;
}

std::vector<double> HeatConduction::get_u_nplus1() const {
	return u_nplus1;
}

std::vector<double> HeatConduction::get_u_n() const {
	return u_n;
}

std::vector<double> HeatConduction::get_u_nminus1() const {
	return u_nminus1;
}

// sub classes

DuFort_Frankel::DuFort_Frankel() : HeatConduction() {}

DuFort_Frankel::DuFort_Frankel(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt) : HeatConduction(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt) {}

void DuFort_Frankel::solve(){	
	/* define n = 0 and n = 1 */
	for (int i = 0; i < s+1; i++){
		u_nminus1[i] = Tin_0;
		u_n[i] = Tin_0;
	}
	u_n[0] = Text_0;
	u_n[s] = Text_0;

	/* Calculte n = 2 and so on */
	double x;
	double r = (D*dt) / (dx*dx);
	for (int j = 2; j < n+1; j++){
		x = Xmin;
		u_nplus1[0] = Text_0;
		u_nplus1[s] = Text_0;
		for (int i = 1; i < s; i++){
			x += dx;
			u_nplus1[i] = (u_nminus1[i] + 2*r*(u_n[i+1] - u_nminus1[i] + u_n[i-1])) /  (1 + 2*r);
		}
		u_nminus1 = u_n;
		u_n = u_nplus1;
	}
}