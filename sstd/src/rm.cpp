#include "rm.hpp"
#include "typeDef.h"
#include "pdbg.hpp"
//#include "path.hpp"
//#include "strmatch.hpp"
//#include "path.hpp"



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


struct pathAndType{
	std::string path;
	char type;        // 'f': file, 'd': directory
};

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

bool getAllInDir(std::vector<struct pathAndType>& ret, const char* pPath){
	if(!PathFileExists(pPath)){ return false; } // there is no file or directory.

	struct pathAndType retBuf;
	retBuf.path = pPath;
	if(!PathIsDirectory(pPath)){
		retBuf.type='f';
		ret.push_back(retBuf);
		return true;
	}
	retBuf.type = 'd';
	ret.push_back(retBuf);
	
	std::vector<std::string> dirList;
	dirList.push_back(pPath);
	for(uint i=0; i<dirList.size(); i++){
		std::vector<std::string> buf = fileInASingleDir(ret, dirList[i].c_str());
		dirList.insert(dirList.end(), buf.begin(), buf.end());
	}
	return true;
}

bool sstd::rm(const char* pPath){
	std::vector<struct pathAndType> fileList;
	if(!getAllInDir(fileList, pPath)){ return false; } // there is no file or directory.

	bool retVal = true;
	for(int i=fileList.size()-1; i>=0; i--){
		if      ('f'==fileList[i].type){ if(!     DeleteFile(fileList[i].path.c_str())){ retVal=false; } //ファイルの消去
		}else if('d'==fileList[i].type){ if(!RemoveDirectory(fileList[i].path.c_str())){ retVal=false; } //ディレクトリの消去 // _rmdir(path_of_erase_file_or_directory);//を使ってもokのはず
		}             else             { sstd::pdbg_always("ERROR: sstd::rm\n"); retVal=false;         }
	}
	return retVal;
}

#else

std::vector<std::string> fileInASingleDir(bool& result, std::vector<struct pathAndType>& ret, const char* pPath){

	// ディレクトリを開く
	DIR *pDir = opendir(pPath);
	if(NULL==pDir){ sstd::pdbg_always("ERROR: opendir() was failed.\n"); result=false; return std::vector<std::string>(); } // there is no file or directory.

	std::vector<std::string> dirList;
	for(struct dirent* pEnt=readdir(pDir); pEnt!=0; pEnt=readdir(pDir)){

		// ファイルの情報を取得
//		printf("pEnt->d_name: %s\n", pEnt->d_name);
//		std::string pathName = pPath;// + std::string(pEnt->d_name);
		std::string pathName = pPath+std::string(R"(/)")+std::string(pEnt->d_name);
//		printf("pathName: %s\n", pathName.c_str());
		struct stat st;
		if(stat(pathName.c_str(), &st)){ sstd::pdbg_always("ERROR: Failed to get stat \"%s\"\n", pathName.c_str()); result=false; break; }

		if(S_ISDIR(st.st_mode)){
			// directory found

			if((strcmp(pEnt->d_name, ".")!=0) && (strcmp(pEnt->d_name, "..")!=0)){
				// subdirectory (サブディレクトリ)
//				printf("subdirectory: %s\n", pEnt->d_name);

				std::string pathBuf = pPath+std::string(R"(/)")+pEnt->d_name;

				struct pathAndType retBuf;
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

			struct pathAndType retBuf;
			retBuf.path = pPath+std::string(R"(/)")+pEnt->d_name; 
			retBuf.type = 'f';
			ret.push_back(retBuf);

			//printf("retBuf.path.c_str(): %s\n", retBuf.path.c_str());
		}
	}

	closedir(pDir);
	return dirList;
}

bool getAllInDir(std::vector<struct pathAndType>& ret, const char* pPath){
	struct stat st;
	if(stat(pPath, &st)!=0){ return false; } // there is no file or directory.

	struct pathAndType retBuf;
	retBuf.path = pPath;
	if(!S_ISDIR(st.st_mode)){
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

bool sstd::rm(const char* pPath){
	std::vector<struct pathAndType> fileList;
	if(!getAllInDir(fileList, pPath)){ return false; } // there is no file or directory.

	bool retVal = true;
	for(int i=fileList.size()-1; i>=0; i--){
		if      ('f'==fileList[i].type){ if(unlink(fileList[i].path.c_str())!=0){ retVal=false; } //ファイルの消去
		}else if('d'==fileList[i].type){ if( rmdir(fileList[i].path.c_str())!=0){ retVal=false; } //ディレクトリの消去 // remove なら，ファイルかディレクトリか自動で判別して，呼び出す関数をスイッチしてくれるらしい
		}             else             { sstd::pdbg_always("ERROR: sstd::rm\n"); retVal=false;         }
	}

	return retVal;
}
#endif

bool sstd::rm(const std::string& path){ return sstd::rm(path.c_str()); }
