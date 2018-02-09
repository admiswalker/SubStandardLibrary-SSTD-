#pragma once
#include <vector>
#include "typeDef.h"

namespace sstd{
	std::vector<double> sinWave(double freq2generate, double freq2sample, uint len);
	std::vector<double> cosWave(double freq2generate, double freq2sample, uint len);
}
