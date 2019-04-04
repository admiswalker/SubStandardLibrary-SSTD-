#include "rm.hpp"
#include "typeDef.h"
#include "path.hpp"
#include "pdbg.hpp"

#include <vector>
#ifdef _WIN32
	#include <Shlwapi.h>                // PathFileExists
	#pragma comment(lib, "shlwapi.lib") // PathFileExists
#else

	#include <dirent.h>
	#include <sys/stat.h> // stat(), S_ISDIR()
	#include <string.h>   // strcmp()
	#include <unistd.h>   // rmdir(), unlink()
#endif

//-------------------------------------------------------------------------------------------------------

bool sstd::unlink(const char* pPath){
	#ifdef _WIN32
		return DeleteFile(pPath);
	#else
		if(::unlink(pPath)==0){ return true; }else{ sstd::pdbg("ERROR: sstd::unlink(): %s.\n", strerror(errno)); return false; };
	#endif
}
bool sstd::unlink(const std::string& path){ return sstd::unlink(path.c_str()); }

//--------------------------------------------------------------------------------------------------------

bool sstd::rmdir(const char* pPath){
	#ifdef _WIN32
		return RemoveDirectory(pPath);
	#else
		return ::rmdir(pPath)==0;
	#endif
}
bool sstd::rmdir(const std::string& path){ return sstd::rmdir(path.c_str()); }


//--------------------------------------------------------------------------------------------------------

// -> ヘッダへ移動．
//
//struct pathAndType{
//	std::string path;
//	char type;        // 'f': file, 'd': directory
//};

//--------------------------------------------------------------------------------------------------------

#ifdef _WIN32

// getFilePathInDir.cpp を参考に実装する
std::vector<std::string> fileInASingleDir(std::vector<struct pathAndType>& ret, const char* pPath){
	std::string path_WC = pPath + std::string(R"(/*)"); // path with wild card

	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFileEx(path_WC.c_str(), FindExInfoStandard, &fd, FindExSearchNameMatch, NULL, 0 );
	if(hFind==INVALID_HANDLE_VALUE){ return std::vector<std::string>(); } // No files or directories.

	std::vector<std::string> dirList;
	do{
		if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){ // WIN32_FIND_DATA構造体のdwFileAttributesとFILE_ATTRIBUTE_DIRECTORYのビットの論理積を取り、ファイルかディレクトリかを判断している
			// directory found

			if ((strcmp( fd.cFileName, "." )!=0) && (strcmp( fd.cFileName, ".." )!=0)){
				// subdirectory (サブディレクトリ)
//				printf( "subdirectory: %s\n", fd.cFileName );

				std::string pathBuf = pPath+std::string(R"(/)")+fd.cFileName;

				struct pathAndType retBuf;
				retBuf.path = pathBuf;
				retBuf.type = 'd';
				ret.push_back(retBuf);

				dirList.push_back(pathBuf);
			}else{
				//  . current directory (カレントディレクトリ)
				// .. parent directory (親ディレクトリ)
//				printf( "current or parent directory: %s\n", fd.cFileName );
			}
		}else{
			// file found
//			printf("file: %s\n", fd.cFileName);

			struct pathAndType retBuf;
			retBuf.path = pPath+std::string(R"(/)")+fd.cFileName;
			retBuf.type = 'f';
			ret.push_back(retBuf);
		}
	}while( FindNextFile(hFind, &fd) );

	FindClose(hFind);
	return dirList;
}
#else

//----------------------------------------------------

std::vector<std::string> fileInASingleDir(bool& result, std::vector<struct sstd::pathAndType>& ret, const char* pPath){

	// ディレクトリを開く
	DIR *pDir = opendir(pPath);
	if(NULL==pDir){ sstd::pdbg("ERROR: opendir() was failed.\n"); result=false; return std::vector<std::string>(); } // there is no file or directory.

	std::vector<std::string> dirList;
	for(struct dirent* pEnt=readdir(pDir); pEnt!=0; pEnt=readdir(pDir)){

		// ファイルの情報を取得
//		printf("pEnt->d_name: %s\n", pEnt->d_name);
//		std::string pathName = pPath;// + std::string(pEnt->d_name);
		std::string pathName = pPath+std::string(R"(/)")+std::string(pEnt->d_name);
//		printf("pathName: %s\n", pathName.c_str());
		struct stat st;
		if(stat(pathName.c_str(), &st)){ sstd::pdbg("ERROR: Failed to get stat \"%s\"\n", pathName.c_str()); result=false; break; }

		if(S_ISDIR(st.st_mode)){
			// directory found

			if((strcmp(pEnt->d_name, ".")!=0) && (strcmp(pEnt->d_name, "..")!=0)){
				// subdirectory (サブディレクトリ)
//				printf("subdirectory: %s\n", pEnt->d_name);

				std::string pathBuf = pPath+std::string(R"(/)")+pEnt->d_name;

				struct sstd::pathAndType retBuf;
				retBuf.path = pathBuf;
				retBuf.type = 'd';
				ret.push_back(retBuf);
				
				dirList.push_back(pathBuf);
				
				//printf("retBuf.path.c_str(): %s\n", retBuf.path.c_str());
			}else{
				//  . current directory (カレントディレクトリ)
				// .. parent directory (親ディレクトリ)
//	   			printf("current or parent directory: %s\n", pEnt->d_name);
			}
		}else{
			// file found
//			printf("file: %s\n", pEnt->d_name);

			struct sstd::pathAndType retBuf;
			retBuf.path = pPath+std::string(R"(/)")+pEnt->d_name; 
			retBuf.type = 'f';
			ret.push_back(retBuf);

			//printf("retBuf.path.c_str(): %s\n", retBuf.path.c_str());
		}
	}
	
	closedir(pDir);
	return dirList;
}
#endif

//--------------------------------------------------------------------------------------------------------

bool sstd::getAllPath(std::vector<struct sstd::pathAndType>& ret, const char* pPath){
	if(!sstd::pathExist(pPath)){ return false; } // there is no file or directory.
	
	struct pathAndType retBuf;
	retBuf.path = pPath;
	if(!sstd::isDir(pPath)){
		retBuf.type='f';
		ret.push_back(retBuf);
		return true;
	}
	retBuf.type = 'd';
	ret.push_back(retBuf);
	
	bool result=true;
	std::vector<std::string> dirList;
	dirList.push_back(pPath);
	for(uint i=0; i<dirList.size(); i++){
		std::vector<std::string> buf = fileInASingleDir(result, ret, dirList[i].c_str());
		dirList.insert(dirList.end(), buf.begin(), buf.end());
	}
	return result;
}
bool sstd::getAllPath(std::vector<std::string>& ret, const char* pPath){
	ret.clear();
	uint rSize=0;
	
	std::vector<struct sstd::pathAndType> allPath;
	if(!sstd::getAllPath(allPath, pPath)){ sstd::pdbg("ERROR: getAllInDir() is failed\n"); return false; }
	
	// In order to avoid directory traversal
	for(uint i=0; i<allPath.size(); i++){
		ret.push_back(std::string());
		ret[rSize].swap(allPath[i].path); rSize++;
	}
	return true;
}
bool sstd::getAllFile(std::vector<std::string>& ret, const char* pPath){
	ret.clear();
	uint rSize=0;
	
	std::vector<struct sstd::pathAndType> allPath;
	if(!sstd::getAllPath(allPath, pPath)){ sstd::pdbg("ERROR: getAllInDir() is failed\n"); return false; }
	
	// In order to avoid directory traversal
	for(uint i=0; i<allPath.size(); i++){
		if(allPath[i].type!='f'){ continue; } // remove directory
		ret.push_back(std::string());
		ret[rSize].swap(allPath[i].path); rSize++;
	}
	return true;
}
bool sstd::getAllDir(std::vector<std::string>& ret, const char* pPath){
	ret.clear();
	uint rSize=0;
	
	std::vector<struct sstd::pathAndType> allPath;
	if(!sstd::getAllPath(allPath, pPath)){ sstd::pdbg("ERROR: getAllInDir() is failed\n"); return false; }
	
	// In order to avoid directory traversal
	for(uint i=0; i<allPath.size(); i++){
		if(allPath[i].type!='d'){ continue; } // remove directory
		ret.push_back(std::string());
		ret[rSize].swap(allPath[i].path); rSize++;
	}
	return true;
}

//--------------------------------------------------------------------------------------------------------

bool sstd::rm(const char* pPath){
	std::vector<struct sstd::pathAndType> fileList;
	if(!sstd::getAllPath(fileList, pPath)){ return false; } // there is no file or directory.

	bool retVal = true;
	for(int i=fileList.size()-1; i>=0; i--){
		if      ('f'==fileList[i].type){ if(!sstd::unlink(fileList[i].path)){ retVal=false; } //ファイルの消去
		}else if('d'==fileList[i].type){ if(!sstd::rmdir (fileList[i].path)){ retVal=false; } //ディレクトリの消去 // remove なら，ファイルかディレクトリか自動で判別して，呼び出す関数をスイッチしてくれるらしい
		}             else             { sstd::pdbg("ERROR: sstd::rm\n"); retVal=false;         }
	}

	return retVal;
}
bool sstd::rm(const std::string& path){ return sstd::rm(path.c_str()); }

//--------------------------------------------------------------------------------------------------------

