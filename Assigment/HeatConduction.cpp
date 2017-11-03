#include "HeatConduction.h"
#include <cmath>

const double pi = atan(1) * 4;

// base class

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

void HeatConduction::solve() {}

std::vector<double> HeatConduction::get_u_n() const {
	return u_n;
}

// sub classes of HeatConduction

AnalyticalSolution::AnalyticalSolution(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt) : HeatConduction(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt) {}

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

ExplicitMethod::ExplicitMethod(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt) : HeatConduction(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt) {}

void ExplicitMethod::advance(int i) {}

void ExplicitMethod::solve(){
	/* define n = -1 and n = 0 */
	for (int i = 0; i < s + 1; i++){
		u_nminus1[i] = Tin_0;
		u_n[i] = Tin_0;
	}
	u_n[0] = Text_0;
	u_n[s] = Text_0;

	/* Calculte n = 1 and so on */
	for (int j = 1; j < n + 1; j++){
		u_nplus1[0] = Text_0;
		u_nplus1[s] = Text_0;
		for (int i = 1; i < s; i++){
			advance(i);
		}
		u_nminus1 = u_n;
		u_n = u_nplus1;
	}
}

ImplicitMethod::ImplicitMethod(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt) : HeatConduction(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt) {
	m = 0;
	a = std::vector<double>(s - 1);
	b = std::vector<double>(s - 1);
	c = std::vector<double>(s - 1);
	d = std::vector<double>(s - 1);

	for (int i = 1; i < s; i++){
		u_n[i] = Tin_0;
	}
	u_n[0] = Text_0;
	u_n[s] = Text_0;
}

void ImplicitMethod::solve() {}

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

// sub classes of ExplicitMethod

DuFort_Frankel::DuFort_Frankel(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt) : ExplicitMethod(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt) {}

void DuFort_Frankel::advance(int i){	
	u_nplus1[i] = (u_nminus1[i] + 2*r*(u_n[i+1] - u_nminus1[i] + u_n[i-1])) /  (1 + 2*r);
}

Richardson::Richardson(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt) : ExplicitMethod(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt) {}

void Richardson::advance(int i){
	u_nplus1[i] = u_nminus1[i] + 2 * r * (u_n[i + 1] - (2 * u_n[i] + u_n[i - 1]));
}

// sub classes of ImplicitMethod

Laasonen::Laasonen(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt) : ImplicitMethod(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt) {}

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

CrankNicholson::CrankNicholson(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt) : ImplicitMethod(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt) {}

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