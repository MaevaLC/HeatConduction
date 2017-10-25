#include "HeatConduction.h"
#include <cmath>

const double pi = atan(1) * 4;

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
	double r = (D*dt) / (dx*dx);
	for (int j = 2; j < n+1; j++){
		u_nplus1[0] = Text_0;
		u_nplus1[s] = Text_0;
		for (int i = 1; i < s; i++){
			u_nplus1[i] = (u_nminus1[i] + 2*r*(u_n[i+1] - u_nminus1[i] + u_n[i-1])) /  (1 + 2*r);
		}
		u_nminus1 = u_n;
		u_n = u_nplus1;
	}
}

AnalyticalSolution::AnalyticalSolution() : HeatConduction() {}

AnalyticalSolution::AnalyticalSolution(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt) : HeatConduction(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt) {}

void AnalyticalSolution::solve(){
	double x = Xmin;
	double L = Xmax - Xmin;
	for (int i = 0; i < s+1; i++){
		double somme = 0;
		for (int m = 1; m < 50; m++){
			somme += exp(-D*pow(m*pi/L,2)*Tend) * ((1-pow(-1,m))/(m*pi)) * sin((m*pi*x)/L);
		}
		u_n[i] = Text_0 + 2 * (Tin_0 - Text_0) * somme;
		x += dx;
	}
}

Richardson::Richardson() : HeatConduction() {}

Richardson::Richardson(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt) : HeatConduction(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt) {}

void Richardson::solve(){
	/* define n = 0 and n = 1 */
	for (int i = 0; i < s + 1; i++){
		u_nminus1[i] = Tin_0;
		u_n[i] = Tin_0;
	}
	u_n[0] = Text_0;
	u_n[s] = Text_0;

	/* Calculte n = 2 and so on */
	double r = (D*dt) / (dx*dx);
	for (int j = 2; j < n + 1; j++){
		u_nplus1[0] = Text_0;
		u_nplus1[s] = Text_0;
		for (int i = 1; i < s; i++){
			u_nplus1[i] = u_nminus1[i] + 2 * r * (u_n[i + 1] - (2 * u_n[i] + u_n[i - 1]));
		}
		u_nminus1 = u_n;
		u_n = u_nplus1;
	}
}