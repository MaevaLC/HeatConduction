#include "HeatConduction.h"
#include <fstream>
#include <iomanip>
#include <sstream>

void assigment(double Tend){
	double Tin_0 = 100; // initial temperature inside : 100°F
	double Text_0 = 300; // initial temperature outside : 300°F
	double Xmin = 0; // position at the left : 0 ft
	double Xmax = 1; // position at the right : 1 ft
	double D = 0.1; // coefficient D = 0.1 ft²/h
	double dx = 0.05; // space step = 0.05;
	double dt = 0.01; // time step = 0.01;
	std::ofstream ofAN; // file to store data
	std::ofstream ofDFF; // file to store data
	std::ofstream ofRI; // file to store data
	std::ofstream ofLSI; // file to store data
	std::ofstream ofCN; // file to store data

	HeatConduction *problemAN;
	problemAN = new AnalyticalSolution(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt);
	(*problemAN).solve();

	HeatConduction *problemDFF;
	problemDFF = new DuFort_Frankel(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt);
	(*problemDFF).solve();

	HeatConduction *problemRI;
	problemRI = new Richardson(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt);
	(*problemRI).solve();

	HeatConduction *problemLSI;
	problemLSI = new Laasonen(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt);
	(*problemLSI).solve();

	HeatConduction *problemCN;
	problemCN = new CrankNicholson(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt);
	(*problemCN).solve();

	std::string TendS = std::to_string(Tend);
	ofAN.open("Analytical-" + TendS + ".txt");
	ofDFF.open("DuFort_Frankel-"+TendS+".txt");
	ofRI.open("Richardson-" + TendS + ".txt");
	ofLSI.open("Laasonen-" + TendS + ".txt");
	ofCN.open("CrankNicholson-" + TendS + ".txt");
	ofAN << std::fixed << std::setprecision(2);
	ofDFF << std::fixed << std::setprecision(2);
	ofRI << std::fixed << std::setprecision(2);
	ofLSI << std::fixed << std::setprecision(2);
	ofCN << std::fixed << std::setprecision(2);
	double x = Xmin;
	std::vector<double> solutionAN = (*problemAN).get_u_n();
	std::vector<double> solutionDFF = (*problemDFF).get_u_n();
	std::vector<double> solutionRI = (*problemRI).get_u_n();
	std::vector<double> solutionLSI = (*problemLSI).get_u_n();
	std::vector<double> solutionCN = (*problemCN).get_u_n();
	for (int i = 0; i < ((Xmax - Xmin) / dx) + 1; i++){
		ofAN << x << " " << solutionAN[i] <<  "\n";
		ofDFF << x << " " << solutionDFF[i] << " " << solutionDFF[i]-solutionAN[i] << "\n";
		ofRI << x << " " << solutionRI[i] << " " << solutionRI[i]-solutionAN[i] << "\n";
		ofLSI << x << " " << solutionLSI[i] << " " << solutionLSI[i]-solutionAN[i] << "\n";
		ofCN << x << " " << solutionCN[i] << " " << solutionCN[i]-solutionAN[i] << "\n";
		x += dx;
	}
	ofAN.close();
	ofDFF.close();
	ofRI.close();
	ofLSI.close();
	ofCN.close();

	delete problemAN;
	delete problemDFF;
	delete problemRI;
	delete problemLSI;
	delete problemCN;
}

int main(){
	for (int i = 1; i < 6; i++){
		assigment(double(i)/10.0);
	}
	return 0;
}