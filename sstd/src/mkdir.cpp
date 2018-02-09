#include "mkdir.hpp"
#include "path.hpp"
#include "typeDef.h"

#ifdef _WIN32
	#include <direct.h>	//_mkdir();用
	void sstd_mkdir(const char* pPath){ _mkdir(pPath); }
#else
	#include <sys/stat.h>
	void sstd_mkdir(const char* pPath){ mkdir(pPath, 0700); }
#endif

void sstd::mkdir(const char* pPath){
	std::vector<std::string> pathList = parsePath_withBase(pPath);
	for(uint i=0; i<pathList.size(); i++){ sstd_mkdir(pathList[i].c_str()); }
}
void sstd::mkdir(const std::string& path){ sstd::mkdir(path.c_str()); }
