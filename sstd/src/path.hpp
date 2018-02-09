#pragma once

#include <string>
#include <vector>

namespace sstd{
	std::string  getPath                     (const char* pPath);
	       char* getFileName                 (const char* pPath);
	std::string  getFileName_withoutExtension(const char* pPath);
	       char* getExtension                (const char* pPath);

	std::vector<std::string> parsePath         (const char* pPath);
	std::vector<std::string> parsePath_withBase(const char* pPath);
}

/*
		How to use this?
*/
/*
int main() {

	printf("■ DirPathAndNameSolver\n");

	const char* pPath="./abc/def/text.abc.txt\0";

	printf("Output getPath: %s\n",                     sstd::getPath(pPath).c_str());
	printf("Output getFileName: %s\n",                 sstd::getFileName(pPath));
	printf("Output getFileNameWithoutExtension: %s\n", sstd::getFileNameWithoutExtension(pPath).c_str());
	printf("Output getFileExtension: %s\n",            sstd::getExtension(pPath));
	printf("\n");
 
	return 0;
}
*/
/*
Input pPath: ./abc/def/text.abc.txt
Output GetPath: ./abc/def/
Output GetFileName: text.abc.txt
Output GetFileNameWithoutExtension: text.abc
Output GetFileExtension: txt
*/



// http://dobon.net/vb/dotnet/file/pathclass.html
//
// ■: 実装済み
//
// GetDirectoryName: ディレクトリ名の取得
// ■GetPath: パスの取得
// ■GetFileName: ファイル名の取得
// ■GetFileNameWithoutExtension: ファイル名 (拡張子なし) の取得
// ■GetExtension: 拡張子の取得
// GetPathRoot: ルートディレクトリ名の取得
// GetFullPath: 絶対パスの取得
// HasExtension: 拡張子を持っているか
// IsPathRooted: ルートが含まれているか (詳細)
// Directory.GetDirectoryRoot	ボリューム、ルート情報の取得
// Directory.GetParent	親ディレクトリの取得


