#include "HeatConduction.h"
#include <fstream>
#include <iomanip>

int main(){
	double Tin_0 = 100; // initial temperature inside : 100°F
	double Text_0 = 300; // initial temperature outside : 300°F
	double Xmin = 0; // position at the left : 0 ft
	double Xmax = 1; // position at the right : 1 ft
	double Tend = 0.5; // end time of simulation : 0.5h
	double D = 0.1; // coefficient D = 0.1 ft²/h
	double dx = 0.05; // space step = 0.05;
	double dt = 0.01; // time step = 0.01;
	std::ofstream ofDFF; // file to store data
	std::ofstream ofAN; // file to store data
	std::ofstream ofRI; // file to store data

	HeatConduction *problemDFF;
	problemDFF = new DuFort_Frankel(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt);
	(*problemDFF).solve();

	HeatConduction *problemAN;
	problemAN = new AnalyticalSolution(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt);
	(*problemAN).solve();

	HeatConduction *problemRI;
	problemRI = new Richardson(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt);
	(*problemRI).solve();

	ofDFF.open("DuFort_Frankel.txt");
	ofAN.open("Analytical.txt");
	ofRI.open("Richardson.txt");
	ofDFF << std::fixed << std::setprecision(2);
	ofAN << std::fixed << std::setprecision(2);
	ofRI << std::fixed << std::setprecision(2);
	double x = Xmin;
	std::vector<double> solutionDFF = (*problemDFF).get_u_n();
	std::vector<double> solutionAN = (*problemAN).get_u_n();
	std::vector<double> solutionRI = (*problemRI).get_u_n();
	for (int i = 0; i < ((Xmax - Xmin) / dx) + 1; i++){
		ofDFF << x << " " << solutionDFF[i] << "\n";
		ofAN << x << " " << solutionAN[i] << "\n";
		ofRI << x << " " << solutionRI[i] << "\n";
		x += dx;
	}
	ofDFF.close();
	ofAN.close();
	ofRI.close();

	delete problemDFF;
	delete problemAN;
	delete problemRI;

	return 0;
}