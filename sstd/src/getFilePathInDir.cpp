#include "getFilePathInDir.hpp"

#ifdef _WIN32   //windows環境の場合は「_WIN32」が定義されているので、こちら。

	#include <winsock2.h> // for "struct timeval" // マクロが再定義されました。主な原因は、<WinSock2.h>より先に<windows.h>がインクルードされたことです。Windowsの制約として、windows.hよりも先にwinsock2.hをインクルードすることが必要です。http://www.02.246.ne.jp/~torutk/cxx/socket/win32_socket.html
	#include <windows.h>
	#undef min
	#undef max
#else

	#include <dirent.h>
	#include <sys/stat.h>	//stat(), S_ISDIR
	#include <string.h>		//strcmp()

	#include <stdio.h>		//std::sort
	#include <vector>		//std::sort
	#include <algorithm>	//std::sort
	#include <functional>	//std::sort
#endif

#include <stdexcept>
#include <stdio.h>

#include "strmatch.hpp"
#include "path.hpp"

std::vector<std::string> sstd::getFilePathInDir(const char* DirAndFileName_withWildCard){
#ifdef _WIN32	//windows環境の場合は「_WIN32」が定義されているので、こちら。

	HANDLE hFind;
	WIN32_FIND_DATA fd;
	std::vector<std::string> FileList;

	hFind = FindFirstFileEx(DirAndFileName_withWildCard, FindExInfoStandard, &fd, FindExSearchNameMatch, NULL, 0);

	if(hFind == INVALID_HANDLE_VALUE){
		return FileList;	// No files or directories.
	}

	do{
		if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){ // WIN32_FIND_DATA構造体のdwFileAttributesとFILE_ATTRIBUTE_DIRECTORYのビットの論理積を取り、ファイルかディレクトリかを判断している

			// directory found
			if((strcmp( fd.cFileName, "." )!=0) && (strcmp( fd.cFileName, ".." )!=0)){
				// subdirectory (サブディレクトリ)
//				printf( "subdirectory: %s\n", fd.cFileName );
			}else{
				//  . current directory (カレントディレクトリ)
				// .. parent directory (親ディレクトリ)
//				printf( "current or parent directory: %s\n", fd.cFileName );
			}
		}else{

			// file found
			std::string buf = sstd::getPath(DirAndFileName_withWildCard) + std::string( fd.cFileName );
			FileList.push_back(buf.c_str());
//			FileList.push_back(fd.cFileName);
//			printf("file: %s\n", FileList.back().c_str());
		}
	}while(FindNextFile(hFind, &fd));

	FindClose(hFind);

	return FileList;

#else			//Linux環境の場合は、「_WIN32」が定義されていないので、こちら。

	DIR *pDir;
	struct dirent *pEnt;
	struct stat Stat;
	std::string PathName;
	std::vector<std::string> FileList;

	std::string DirPath = getPath(DirAndFileName_withWildCard);

	// ディレクトリを開く
	pDir = opendir(DirPath.c_str());
	if ( NULL == pDir ) {
		printf( "Error: in %s directory\n", DirPath.c_str() );
		return FileList;
	}

	for(pEnt=readdir(pDir); pEnt!=0; pEnt=readdir(pDir)){

		// ファイルの情報を取得
		PathName = DirPath + pEnt->d_name;
		if( stat( PathName.c_str(), &Stat ) ){
			printf( "ERROR: Failed to get stat %s\n", PathName.c_str() );
			break;
		}

		if (S_ISDIR(Stat.st_mode)){

			// directory found
			if((strcmp( pEnt->d_name, "." )!=0) && (strcmp( pEnt->d_name, ".." )!=0)){
				// subdirectory (サブディレクトリ)
//		   		printf( "subdirectory: %s\n", pEnt->d_name );
			}else{
				//  . current directory (カレントディレクトリ)
				// .. parent directory (親ディレクトリ)
//	   			printf( "current or parent directory: %s\n", pEnt->d_name );
			}
		}else{
			if(strmatch( pEnt->d_name, getFileName(DirAndFileName_withWildCard))){
				// マッチした場合に true を返します。
				FileList.push_back( PathName );
			}
		}
	}

	// ハンドルを閉じる
	closedir(pDir);

	std::sort(FileList.begin(), FileList.end());//昇順ソート
	return FileList;
#endif
}
