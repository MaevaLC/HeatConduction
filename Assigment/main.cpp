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
	std::ofstream of; // file to store data

	HeatConduction *problem;
	problem = new DuFort_Frankel(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt);
	(*problem).solve();

	of.open("DuFort_Frankel.txt");
	of << std::fixed << std::setprecision(2);
	double x = Xmin;
	std::vector<double> solution = (*problem).get_u_n();
	for (int i = 0; i < ((Xmax - Xmin) / dx) + 1; i++){
		of << x << " " << solution[i] << "\n";
		x += dx;
	}
	of.close();

	delete problem;

	return 0;
}