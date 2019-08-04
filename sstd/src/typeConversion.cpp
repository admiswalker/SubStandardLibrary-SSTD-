#include "typeConversion.hpp"

int sstd::str2int(const std::string& rhs){ return std::stoi(rhs); } // 小数点以下，切り捨て

double sstd::str2double(const std::string& rhs){ return std::stod(rhs); }
std::vector<double> sstd::str2double(const std::vector<std::string>& rhs){
	std::vector<double> ret(rhs.size());
	for(uint i=0; i<rhs.size(); i++){
		ret[i]=sstd::str2double(rhs[i]);
	}
	return ret;
}
std::vector<std::vector<double>> sstd::str2double(const std::vector<std::vector<std::string>>& rhs){
	std::vector<std::vector<double>> ret(rhs.size());
	for(uint i=0; i<rhs.size(); i++){
		ret[i]=sstd::str2double(rhs[i]);
	}
	return ret;
}

//---

//std::string sstd::str2int(const int& rhs){ XXXXXXXXXXXX; } // 小数点以下，切り捨て

std::string sstd::double2str(const double& rhs){ return sstd::ssprintf("%lf", rhs); }
std::vector<std::string> sstd::double2str(const std::vector<double>& rhs){
	std::vector<std::string> ret(rhs.size());
	for(uint i=0; i<rhs.size(); i++){
		ret[i] = sstd::double2str(rhs[i]);
	}
	return ret;
}
std::vector<std::vector<std::string>> sstd::double2str(const std::vector<std::vector<double>>& rhs){
	std::vector<std::vector<std::string>> ret(rhs.size());
	for(uint i=0; i<rhs.size(); i++){
		ret[i] = sstd::double2str(rhs[i]);
	}
	return ret;
}

