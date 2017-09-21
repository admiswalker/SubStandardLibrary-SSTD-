#include "pathNameExtractor.hpp"
#include "typeDef.h"
#include <string.h>


std::string sstd::getPath(const char* pPath){

	std::string result;
	char* pStartPathAdd = sstd::getFileName(pPath);

	for(const char* pPathBuf=pPath; pPathBuf<pStartPathAdd; pPathBuf++){
		result += *pPathBuf;
	}
	return result;
}


char* sstd::getFileName(const char* pPath){

	char* pStartPathAdd = (char*)&pPath[0];

	for(int i=0; pPath[i]!='\0'; i++){
		if(pPath[i]=='/'||pPath[i]=='\\'){
			pStartPathAdd = (char*)&pPath[i];
			pStartPathAdd++;
		}
	}

	return pStartPathAdd;
}


std::string sstd::getFileName_withoutExtension(const char* pPath){

	std::string FileName;

	char* pStartPathAdd = sstd::getFileName(pPath);

	size_t len = strlen(pStartPathAdd);

	uint End=len;
	for(uint i=len; pStartPathAdd[i]!='.'&&i>0; i--){
		End--;
	}
	if(End==0){ End=len; }

	for(uint i=0; i<End; i++){
		FileName += pStartPathAdd[i];
	}

	return FileName;
}


char* sstd::getExtension(const char* pPath){

	char* pStartPathAdd=(char*)&pPath[0]; // avoid warning
	size_t len = strlen(pPath);

	for(uint i=len; pPath[i]!='.'&&len>=0; i--){
		if(pPath[i]=='/'||pPath[i]=='\\'){pStartPathAdd=0;break;}
		pStartPathAdd = (char*)&pPath[i];
	}
	return pStartPathAdd;
}
