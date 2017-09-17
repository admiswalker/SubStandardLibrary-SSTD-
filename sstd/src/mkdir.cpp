#include "mkdir.hpp"

// 再帰的にディレクトリを生成できるように，改良すること．

#ifdef _WIN32
	#include <direct.h>	//_mkdir();用
	void mkdir_win32(const char* path){ _mkdir(path); }
#else
	#include <sys/stat.h>
	void mkdir_linux(const char* path){ mkdir(path, 0777); }
#endif

void sstd::mkdir(const char* path){
#ifdef _WIN32
	mkdir_win32(path);
#else
	mkdir_linux(path);
#endif
}

