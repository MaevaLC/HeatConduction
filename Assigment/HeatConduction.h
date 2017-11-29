/**
* \file      HeatConduction.h
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

#include <vector>

/**
* \class HeatConduction
* \brief Base abstract Class which include all the parameters to solve the problem
*
* Heat Conduction is an object, in which attributes is a paramaters of the problem,
* and also have vectors which will be used to store the solution. It includes an 
* abstract method solve, which will call the solve methods corresponding to the
* type of scheme the user need.
*/
class HeatConduction {
protected:
	double Tin_0; //!< initial condition Temperature
	double Text_0; //!< initial condition Temperature
	double Xmin; //!< initial condition Position
	double Xmax; //!< initial condition Position
	double Tend; //!< initial condition Time
	double D; //!< initial condition D
	double dx; //!< space step
	double dt; //!< time step
	int n; //!< number of time steps
	int s; //!< number of space steps
	double r; //!< calculation made once instead of multiple time
	std::vector<double> u_nplus1; //!< solution values vector n+1
	std::vector<double> u_n; //!< solution values vector n
	std::vector<double> u_nminus1; //!< solution values vector n-1	
public:
	HeatConduction(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt);
	virtual void solve();
	std::vector<double> get_u_n() const;
};

/**
* \class AnalyticalSolution
* \brief Sub Class used to calculate the analytical solution
*
* AnalyticalSolution is a sub class of HeatConduction. It use the attribut of the
* mother class to calculate the analytical solution.
*/
class AnalyticalSolution : public HeatConduction{
public:
	AnalyticalSolution(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt);
	virtual void solve();
};

/**
* \class ExplicitMethod
* \brief Sub Abstract Class used to calculate the Explicit scheme
*
* ExplicitMethod is a sub class of HeatConduction. Both explicit method share the
* same solve method, which is implemented in this class. The advance method is an 
* abstract method implemented in the sub sub classes.
*/
class ExplicitMethod : public HeatConduction{
public:
	ExplicitMethod(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt);
	virtual void solve();
	virtual void advance(int i);
};

/**
* \class ImplicitMethod
* \brief Sub Abstract Class used to calculate the Implicit scheme
*
* ImplicitMethod is a sub class of HeatConduction. Both implicit method share the
* Thomas Algorith, which is implemented in this class. The solve method is an
* abstract method implemented in the sub sub classes.
*/
class ImplicitMethod : public HeatConduction{
protected:
	double m; //!< var needed in the Thomas Algorithm
	std::vector<double> a; //!< lower tridiagonal vector of the matrix
	std::vector<double> b; //!< middle tridiagonal vector of the matrix
	std::vector<double> c; //!< upper tridiagonal vector of the matrix
	std::vector<double> d; //!< vector on the right of the equation
public:
	ImplicitMethod(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt);
	virtual void solve();
	void ThomasAlgorith();
};

/**
* \class DuFort_Frankel
* \brief Sub sub Class used to calculate the DuFort_Frankel scheme
*
* DuFort_Frankel is a sub class of ExplicitMethod. It use the 
* DuFort-Frankel scheme, a second order explicit scheme to calculate
* an Heat Conduction problem of a wall which have a temperature imposed
* at the extremities.
*/
class DuFort_Frankel : public ExplicitMethod{
public:
	DuFort_Frankel(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt);
	virtual void advance(int i);
};

/**
* \class Richardson
* \brief Sub sub Class used to calculate the Richardson scheme
*
* Richardson is a sub class of ExplicitMethod. It use the
* Richardson scheme, a second order explicit scheme to calculate
* an Heat Conduction problem of a wall which have a temperature imposed
* at the extremities.
*/
class Richardson : public ExplicitMethod{
public:
	Richardson(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt);
	virtual void advance(int i);
};

/**
* \class Laasonen
* \brief Sub sub Class used to calculate the Laasonen scheme
*
* Laasonen is a sub class of ImplicitMethod. It use the
* Laasonen scheme, an implicit scheme to calculate
* an Heat Conduction problem of a wall which have a temperature imposed
* at the extremities.
*/
class Laasonen : public ImplicitMethod{
public:
	Laasonen(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt);
	virtual void solve();
};

/**
* \class CrankNicholson
* \brief Sub sub Class used to calculate the Crank-Nicholson scheme
*
* CrankNicholson is a sub class of ImplicitMethod. It use the
* Crank-Nicholson scheme, an implicit scheme to calculate
* an Heat Conduction problem of a wall which have a temperature imposed
* at the extremities.
*/
class CrankNicholson : public ImplicitMethod{
public:
	CrankNicholson(double Tin_0, double Text_0, double Xmin, double Xmax, double Tend, double D, double dx, double dt);
	virtual void solve();
};