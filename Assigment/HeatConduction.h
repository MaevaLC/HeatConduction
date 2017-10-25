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
	std::vector<double> t; // time steps vector
	std::vector<double> u_nplus1; // solution values vector n+1
	std::vector<double> u_n; // solution values vector n
	std::vector<double> u_nminus1; // solution values vector n-1
	
public:
	HeatConduction();
	HeatConduction(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt);
	virtual void solve();
	std::vector<double> get_t() const;
	std::vector<double> get_u_nplus1() const;
	std::vector<double> get_u_n() const;
	std::vector<double> get_u_nminus1() const;
};

// sub classes

class DuFort_Frankel : public HeatConduction{
public:
	DuFort_Frankel();
	DuFort_Frankel(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt);
	virtual void solve();
};