#include <vector>

// abstract base class

class HeatConduction {
protected:
	double Tin_0; // initial condition Temperature
	double Text_0; // initial condition Temperature
	double Xmin; // initial condition Position
	double Xmax; // initial condition Position
	double Tend; // initial condition Time
	double D; // initial condition D
	double dx; // space step
	double dt; // time step
	int n; // number of time steps
	int s; // number of space steps
	double r; //simplification for futur calculs
	std::vector<double> u_nplus1; // solution values vector n+1
	std::vector<double> u_n; // solution values vector n
	std::vector<double> u_nminus1; // solution values vector n-1
	
public:
	HeatConduction();
	HeatConduction(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt);
	virtual void solve();
	std::vector<double> get_u_n() const;
};

// sub classes of HeatConduction

class AnalyticalSolution : public HeatConduction{
public:
	AnalyticalSolution();
	AnalyticalSolution(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt);
	virtual void solve();
};

class ExplicitMethod : public HeatConduction{
public:
	ExplicitMethod();
	ExplicitMethod(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt);
	virtual void solve();
	virtual void advance(int i);
};

class Laasonen : public HeatConduction{
public:
	Laasonen();
	Laasonen(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt);
	virtual void solve();
};

// sub classes of ExplicitMethod

class DuFort_Frankel : public ExplicitMethod{
public:
	DuFort_Frankel();
	DuFort_Frankel(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt);
	virtual void advance(int i);
};

class Richardson : public ExplicitMethod{
public:
	Richardson();
	Richardson(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt);
	virtual void advance(int i);
};