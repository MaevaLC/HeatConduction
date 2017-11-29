/**
* \file      Norms.cpp
* \author    M Le Clec'h
* \version   1.0
* \date      05 December 2017
* \brief     Functions to calculates norms
*
* \details   There are 3 norms which can be calculated : 
*              - The norm one
*              - The norm two
*              - The uniform norm
*/

#include "Norms.h"

/**
* \fn norm_one(std::vector<double> solution)
* \brief Function to calculate the first norm.
*
* \param solution Vector object on which we need to calculate the norm one.
* \return sum The result of the calculation.
*/
double norm_one(std::vector<double> solution) {
	int n = solution.size();
	double sum = 0.0;
	for (int i = 0; i < n; i++)
		sum = sum + fabs(solution[i]);
	return sum;
}

/**
* \fn norm_two(std::vector<double> solution)
* \brief Function to calculate the Euclidean norm.
*
* \param solution Vector object on which we need to calculate the second one.
* \return sum The result of the calculation.
*/
double norm_two(std::vector<double> solution) {
	int n = solution.size();
	double sum = 0.0;
	for (int i = 0; i < n; i++)
		sum = sum + (solution[i] * solution[i]);
	return sqrt(sum);
}

/**
* \fn norm_uniform(std::vector<double> solution)
* \brief Function to calculate the Infinite norm.
*
* \param solution Vector object on which we need to calculate the uniform one.
* \return sum The result of the calculation.
*/
double norm_uniform(std::vector<double> solution) {
	int n = solution.size();
	double max = fabs(solution[0]);
	for (int i = 1; i < n; i++){
		if (fabs(solution[i]) > max) {
			max = fabs(solution[i]);
		}
	}
	return max;
}