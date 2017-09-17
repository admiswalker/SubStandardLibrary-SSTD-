#pragma once

#ifdef _WIN32   //windows環境の場合は「_WIN32」が定義されているので、こちら。

	#include <Windows.h>
#else

	#include <dirent.h>
	#include <sys/stat.h>	//stat(), S_ISDIR
	#include <string.h>		//strcmp()

	#include <stdio.h>		//std::sort
	#include <vector>		//std::sort
	#include <algorithm>	//std::sort
	#include <functional>	//std::sort
#endif

#include <vector>
#include <string>
#include <stdexcept>

#include <stdio.h>

#include "strmatch.hpp"
#include "pathNameExtractor.hpp"

namespace sstd{
	std::vector<std::string> getFilePathInDir(const char* DirAndFileName_withWildCard);
}
