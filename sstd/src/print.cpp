#include "./print.hpp"
#include "./ssprintf.hpp"
//#include <stdio.h>

//-----------------------------------------------------------------------------------------------------------------------------------------------

namespace sstd_print{ // This namespace is for internal processing
	std::string val2str(const        bool  rhs){ return sstd::ssprintf("%c", (rhs ? 'T' : 'F')); }
	std::string val2str(const        char  rhs){ return sstd::ssprintf("'%c'", rhs); }
//	std::string val2str(const       uchar  rhs){ return sstd::ssprintf("%u",   rhs); } // same as uint8
	std::string val2str(const       int8   rhs){ return sstd::ssprintf("%d",    rhs); }
	std::string val2str(const       int16  rhs){ return sstd::ssprintf("%d",    rhs); }
	std::string val2str(const       int32  rhs){ return sstd::ssprintf("%d",    rhs); }
	std::string val2str(const       int64  rhs){ return sstd::ssprintf("%lld",  rhs); }
	std::string val2str(const      uint8   rhs){ return sstd::ssprintf("%u",    rhs); } // same as uchar
	std::string val2str(const      uint16  rhs){ return sstd::ssprintf("%u",    rhs); }
	std::string val2str(const      uint32  rhs){ return sstd::ssprintf("%u",    rhs); }
	std::string val2str(const      uint64  rhs){ return sstd::ssprintf("%llu",  rhs); }
//	std::string val2str(const       float  rhs){ return sstd::ssprintf("%.4f",  rhs); }
	std::string val2str(const       float  rhs){
		std::string ret = sstd::ssprintf("%g", rhs);
		for(uint64 i=0; i<ret.size(); i++){ if(ret[i]=='.'){return ret;} }
		return ret+'.';
	}
//	std::string val2str(const      double  rhs){ return sstd::ssprintf("%.4lf", rhs); }
	std::string val2str(const      double  rhs){
		std::string ret = sstd::ssprintf("%g", rhs);
		for(uint64 i=0; i<ret.size(); i++){ if(ret[i]=='.'){return ret;} }
		return ret+'.';
	}
	std::string val2str(const std::string& rhs){ return '\"'+rhs+'\"'; }
	
	                      void print(const bool  rhs); // specealization
	                      void print(const char* rhs); // specealization
	template <typename T> void print(const                         T  & rhs);
	template <typename T> void print(const             std::vector<T> & rhs);
	template <typename T> void print(const std::vector<std::vector<T>>& rhs);
	
	                      void for_printn(const bool  rhs); // specealization
	                      void for_printn(const char* rhs); // specealization
	template <typename T> void for_printn(const                         T  & rhs);
	template <typename T> void for_printn(const             std::vector<T> & rhs);
	template <typename T> void for_printn(const std::vector<std::vector<T>>& rhs);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

                      void sstd_print::print(const bool  rhs){ printf("%s\n", (rhs ? "true" : "false"));   }
                      void sstd_print::print(const char* rhs){ printf("\"%s\"\n", rhs);                    }
template <typename T> void sstd_print::print(const             T & rhs){ printf("%s\n", sstd_print::val2str(rhs).c_str()); }
template <typename T> void sstd_print::print(const std::vector<T>& rhs){
	printf("[");
	if(rhs.size()>=1){
		for(uint i=0; i<rhs.size()-1; i++){ printf("%s ", sstd_print::val2str(rhs[i]).c_str()); }
		printf("%s", sstd_print::val2str(rhs[rhs.size()-1]).c_str());
	}
	printf("]\n");
}
//---
                      void sstd_print::for_printn(const bool  rhs){ printf(" = %s\n", (rhs ? "true" : "false"));   }
                      void sstd_print::for_printn(const char* rhs){ printf(" = \"%s\"\n", rhs);                    }
template <typename T> void sstd_print::for_printn(const             T & rhs){ printf(" = %s\n", sstd_print::val2str(rhs).c_str()); }
template <typename T> void sstd_print::for_printn(const std::vector<T>& rhs){
	printf(" = [");
	if(rhs.size()>=1){
		for(uint i=0; i<rhs.size()-1; i++){ printf("%s ", sstd_print::val2str(rhs[i]).c_str()); }
		printf("%s", sstd_print::val2str(rhs[rhs.size()-1]).c_str());
	}
	printf("]\n");
}
//---
template <typename T>
void sstd_vvprint_internal(const std::vector<T>& rhs){
	if(rhs.size()<=0){ return; }
	
	for(uint i=0; i<rhs.size()-1; i++){ printf("%s ", sstd_print::val2str(rhs[i]).c_str()); }
	printf("%s", sstd_print::val2str(rhs[rhs.size()-1]).c_str());
}
template <typename T>
void sstd_print::print(const std::vector<std::vector<T>>& rhs){
	if(rhs.size()==0){ printf("[[]]\n"); return; }
	
	printf("[");
	for(uint64 i=0; i<rhs.size()-1; i++){
		printf("[");
		sstd_vvprint_internal(rhs[i]);
		printf("] ");
	}
	{
		printf("[");
		sstd_vvprint_internal(rhs[rhs.size()-1]);
		printf("]");
	}
	printf("]\n");
}
template <typename T>
void sstd_print::for_printn(const std::vector<std::vector<T>>& rhs){
	if(rhs.size()==0){ printf(" = [[]]\n"); return; }
	
	printf(" = [");
	for(uint64 i=0; i<rhs.size()-1; i++){
		printf("[");
		sstd_vvprint_internal(rhs[i]);
		printf("] ");
	}
	{
		printf("[");
		sstd_vvprint_internal(rhs[rhs.size()-1]);
		printf("]");
	}
	printf("]\n");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------

// Because of complex data type speculation of template is not possible in the other .cpp file,
// function instances are listed below.

void sstd::print(const                               bool     rhs){ sstd_print::print(rhs); }
void sstd::print(const                               char     rhs){ sstd_print::print(rhs); }
void sstd::print(const                               int8     rhs){ sstd_print::print(rhs); }
void sstd::print(const                               int16    rhs){ sstd_print::print(rhs); }
void sstd::print(const                               int32    rhs){ sstd_print::print(rhs); }
void sstd::print(const                               int64    rhs){ sstd_print::print(rhs); }
void sstd::print(const                              uint8     rhs){ sstd_print::print(rhs); }
void sstd::print(const                              uint16    rhs){ sstd_print::print(rhs); }
void sstd::print(const                              uint32    rhs){ sstd_print::print(rhs); }
void sstd::print(const                              uint64    rhs){ sstd_print::print(rhs); }
void sstd::print(const                               float    rhs){ sstd_print::print(rhs); }
void sstd::print(const                              double    rhs){ sstd_print::print(rhs); }
void sstd::print(const                                char  * rhs){ sstd_print::print(rhs); }
void sstd::print(const                         std::string  & rhs){ sstd_print::print(rhs); }

void sstd::print(const std::vector<                  bool  >& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<                  char  >& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<                  int8  >& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<                  int16 >& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<                  int32 >& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<                  int64 >& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<                 uint8  >& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<                 uint16 >& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<                 uint32 >& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<                 uint64 >& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<                  float >& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<                 double >& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<            std::string >& rhs){ sstd_print::print(rhs); }

void sstd::print(const std::vector<std::vector<      bool >>& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<std::vector<      char >>& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<std::vector<      int8 >>& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<std::vector<      int16>>& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<std::vector<      int32>>& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<std::vector<      int64>>& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<std::vector<     uint8 >>& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<std::vector<     uint16>>& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<std::vector<     uint32>>& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<std::vector<     uint64>>& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<std::vector<      float>>& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<std::vector<     double>>& rhs){ sstd_print::print(rhs); }
void sstd::print(const std::vector<std::vector<std::string>>& rhs){ sstd_print::print(rhs); }

//---

void sstd::for_printn(const                               bool     rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const                               char     rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const                               int8     rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const                               int16    rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const                               int32    rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const                               int64    rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const                              uint8     rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const                              uint16    rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const                              uint32    rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const                              uint64    rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const                               float    rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const                              double    rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const                                char  * rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const                         std::string  & rhs){ sstd_print::for_printn(rhs); }

void sstd::for_printn(const std::vector<                  bool  >& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<                  char  >& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<                  int8  >& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<                  int16 >& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<                  int32 >& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<                  int64 >& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<                 uint8  >& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<                 uint16 >& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<                 uint32 >& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<                 uint64 >& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<                  float >& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<                 double >& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<            std::string >& rhs){ sstd_print::for_printn(rhs); }

void sstd::for_printn(const std::vector<std::vector<      bool >>& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<std::vector<      char >>& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<std::vector<      int8 >>& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<std::vector<      int16>>& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<std::vector<      int32>>& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<std::vector<      int64>>& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<std::vector<     uint8 >>& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<std::vector<     uint16>>& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<std::vector<     uint32>>& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<std::vector<     uint64>>& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<std::vector<      float>>& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<std::vector<     double>>& rhs){ sstd_print::for_printn(rhs); }
void sstd::for_printn(const std::vector<std::vector<std::string>>& rhs){ sstd_print::for_printn(rhs); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

