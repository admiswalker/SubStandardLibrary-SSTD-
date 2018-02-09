#include "signal.hpp"
#define _USE_MATH_DEFINES
#include <math.h>


std::vector<double> sstd::sinWave(double freq2generate, double freq2sample, uint len){

	std::vector<double> lhs(len, 0);
	double coef = 2.0*M_PI*freq2generate/freq2sample;
	for(uint i=0; i<len; i++){
		lhs[i] = sin(coef*i);
	}
	return lhs;
}
std::vector<double> sstd::cosWave(double freq2generate, double freq2sample, uint len){

	std::vector<double> lhs(len, 0);
	double coef = 2.0*M_PI*freq2generate/freq2sample;
	for(uint i=0; i<len; i++){
		lhs[i] = cos(coef*i);
	}
	return lhs;
}
