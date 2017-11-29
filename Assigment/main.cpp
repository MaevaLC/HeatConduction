#include "HeatConduction.h"
#include "Norms.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

//
// ...... DEMONSTRATION OF THE USE OF THE DIFFERENT CLASSES ......
//

/**
* \fn void assigment(double Tend)
* \brief Function to calculate the problem gave in the Computational Methods & C++ assigment with the 4 different schemes
*
* \param Tend - the time at which the simulation end (in hours)
* \return void - print files with the data
*/
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
	std::ofstream norms; // file to store data

	// creation of all the object corresponding to the different methods
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

	// creation of the different files to store the data
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

	// collection of the data calculated in ours objects
	std::vector<double> solutionAN = (*problemAN).get_u_n();
	std::vector<double> solutionDFF = (*problemDFF).get_u_n();
	std::vector<double> solutionRI = (*problemRI).get_u_n();
	std::vector<double> solutionLSI = (*problemLSI).get_u_n();
	std::vector<double> solutionCN = (*problemCN).get_u_n();

	// error points by points
	std::vector<double> errorDFF = std::vector<double>(1 + int((Xmax - Xmin) / dx));
	std::vector<double> errorRI = std::vector<double>(1 + int((Xmax - Xmin) / dx));
	std::vector<double> errorLSI = std::vector<double>(1 + int((Xmax - Xmin) / dx));
	std::vector<double> errorCN = std::vector<double>(1 + int((Xmax - Xmin) / dx));

	for (int i = 0; i < int(solutionAN.size()); i++){
		errorDFF[i] = solutionDFF[i] - solutionAN[i];
		errorRI[i] = solutionRI[i] - solutionAN[i];
		errorLSI[i] = solutionLSI[i] - solutionAN[i];
		errorCN[i] = solutionCN[i] - solutionAN[i];
	}

	// print in the files the solutions and the p by p erros
	double x = Xmin;
	for (int i = 0; i < int(solutionAN.size()); i++){
		ofAN << x << " " << solutionAN[i] <<  "\n";
		ofDFF << x << " " << solutionDFF[i] << " " << errorDFF[i] << "\n";
		ofRI << x << " " << solutionRI[i] << " " << errorRI[i] << "\n";
		ofLSI << x << " " << solutionLSI[i] << " " << errorLSI[i] << "\n";
		ofCN << x << " " << solutionCN[i] << " " << errorCN[i] << "\n";
		x += dx;
	}

	// close the files once printed
	ofAN.close();
	ofDFF.close();
	ofRI.close();
	ofLSI.close();
	ofCN.close();

	// calcul of norms, and printing
	norms.open("Norms.txt", std::fstream::app);
	norms << std::fixed << std::setprecision(2);
	norms << "Scheme @" << TendS << " : Norm One " << "//" << " Norm Two " << "//" << " Uniform Norm" << "\n";
	norms << "DFF : " << norm_one(errorDFF) << " " << norm_two(errorDFF) << " " << norm_uniform(errorDFF) << "\n";
	norms << "RI : " << norm_one(errorRI) << " " << norm_two(errorRI) << " " << norm_uniform(errorRI) << "\n";
	norms << "LSI : " << norm_one(errorLSI) << " " << norm_two(errorLSI) << " " << norm_uniform(errorLSI) << "\n";
	norms << "CN : " << norm_one(errorCN) << " " << norm_two(errorCN) << " " << norm_uniform(errorCN) << "\n";

	// free the memory
	delete problemAN;
	delete problemDFF;
	delete problemRI;
	delete problemLSI;
	delete problemCN;
}

/**
* \fn void LassWithDifferentDT(double dt)
* \brief Function to calculate the problem gave in the Computational Methods & C++ assigment with the Laasonen scheme
*
* \param dt - the time step which should be used
* \return void - print files with the data
*/
void LassWithDifferentDT(double dt){
	double Tin_0 = 100; // initial temperature inside : 100°F
	double Text_0 = 300; // initial temperature outside : 300°F
	double Xmin = 0; // position at the left : 0 ft
	double Xmax = 1; // position at the right : 1 ft
	double Tend = 0.5; // end time
	double D = 0.1; // coefficient D = 0.1 ft²/h
	double dx = 0.05; // space step = 0.05;
	std::ofstream ofLSI; // file to store data
	std::ofstream norms; // file to store data

	// creation of all the object corresponding to the different methods
	HeatConduction *problemAN;
	problemAN = new AnalyticalSolution(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt);
	(*problemAN).solve();

	HeatConduction *problemLSI;
	problemLSI = new Laasonen(Tin_0, Text_0, Xmin, Xmax, Tend, D, dx, dt);
	(*problemLSI).solve();

	// creation of the file to store the data
	std::string dtS = std::to_string(dt);
	ofLSI.open("dt_Laasonen-" + dtS + ".txt");
	ofLSI << std::fixed << std::setprecision(2);

	// collection of the data calculated in ours objects
	std::vector<double> solutionAN = (*problemAN).get_u_n();
	std::vector<double> solutionLSI = (*problemLSI).get_u_n();

	// error points by points
	std::vector<double> errorLSI = std::vector<double>(1 + int((Xmax - Xmin) / dx));

	for (int i = 0; i < int(solutionAN.size()); i++){
		errorLSI[i] = solutionLSI[i] - solutionAN[i];
	}

	// print in the files the solutions and the p by p erros
	double x = Xmin;
	for (int i = 0; i < int(solutionAN.size()); i++){
		ofLSI << x << " " << solutionLSI[i] << " " << errorLSI[i] << "\n";
		x += dx;
	}

	// calcul of norms, and printing
	norms.open("NormsLaas.txt", std::fstream::app);
	norms << std::fixed << std::setprecision(2);
	norms << "Scheme @" << dtS << " : Norm One " << "//" << " Norm Two " << "//" << " Uniform Norm" << "\n";
	norms << "LSI : " << norm_one(errorLSI) << " " << norm_two(errorLSI) << " " << norm_uniform(errorLSI) << "\n";

	// close the files once printed, and delete objects
	ofLSI.close();
	delete problemAN;
	delete problemLSI;

}

/**
* \fn int main()
* \brief Function to launch the 2 other fonctions of the main with differents arguments 
*
* \param none
* \return 0 - return a 0 if everything went ok.
*/
int main(){
	// clear the two files norms and normsLaas at each new launch of the program
	std::ofstream norms;
	std::ofstream norms1;
	norms.open("Norms.txt");
	norms1.open("NormsLaas.txt");

	// create all the scheme with differents end time of simulation : 0.1h -> 0.5h
	for (int i = 1; i < 6; i++){
		assigment(double(i)/10.0);
	}

	// create the Lassonen scheme with specifics dt
	double dtArray[4] = { 0.01, 0.025, 0.05, 0.1 };
	for (int i = 0; i < 4; i++){
		auto t1 = Clock::now();
		LassWithDifferentDT(dtArray[i]);
		auto t2 = Clock::now();
		std::cout << "Delta t2-t1: " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " nanoseconds" << std::endl;
	}

	system("PAUSE");
	return 0;
}