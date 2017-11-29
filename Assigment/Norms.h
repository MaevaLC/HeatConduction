/**
* \file      Norms.h
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

#include <vector>

double norm_one(std::vector<double> solution);
double norm_two(std::vector<double> solution);
double norm_uniform(std::vector<double> solution);