#pragma once
#include <string>
#include <vector>

namespace sstd{
	struct pathAndType{
		std::string path;
		char type;        // 'f': file, 'd': directory
	};
	
	bool unlink(const char*        pPath); // delete file
	bool unlink(const std::string&  path); // delete file

	bool rmdir (const char*        pPath); // delete empty directory
	bool rmdir (const std::string&  path); // delete empty directory

	bool getAllPath(std::vector<struct sstd::pathAndType>& ret, const char* pPath); // get all path in the directory
	bool getAllPath(std::vector<std::string>& ret, const char* pPath); // get all path in the directory
	bool getAllFile(std::vector<std::string>& ret, const char* pPath); // get all file path in the directory
	bool getAllDir (std::vector<std::string>& ret, const char* pPath); // get all directory path in the directory
	bool rm    (const char*        pPath); // delete all under the pPath
	bool rm    (const std::string&  path); // delete all under the path
}
