#pragma once

#include <string>
#include <vector>
#include "../typeDef.h"


namespace sstd{
    
    std::string  path2basePath              (const char* pPath);
    std::string  path2basePath_woWC        (const char* pPath); // _woWC: without wild card
    
    std::string  path2dirName               (const char* pPath);
    uint         path2dirName_begin_idx    (const char* pPath);
    uint         path2dirName_end_idx      (const char* pPath);
    uint         path2dirName_end_idx_woWC(const char* pPath); // _woWC: without wild card
    
           char* path2fileName             (const        char* pPath);
    std::string  path2fileName             (const std::string&  path); // new
    std::string  path2fileName             (const std::string&& path); // new
    std::string  path2fileName_woExt      (const        char* pPath);
           char* path2fileExt              (const        char* pPath);
    std::string  path2fileExt              (const std::string&  path); // new
    
    std::vector<std::string> parsePath           (const char* pPath);
    std::vector<std::string> parsePath_wBasePath(const char* pPath); // _wBasePath: with base path
    
    bool isFile(const char*        pPath);
    bool isFile(const std::string&  path);
    bool isDir (const char*        pPath);
    bool isDir (const std::string&  path);
    
    bool fileExist(const char*        pPath);
    bool fileExist(const std::string&  path);
    bool  dirExist(const char*        pPath);
    bool  dirExist(const std::string&  path);
    bool pathExist(const char*        pPath);
    bool pathExist(const std::string&  path);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Below functions are the not recommended to use. (Below functions will be delete on sstd ver 3.x.x).

namespace sstd{
    
    std::string  getPath                     (const char* pPath); // new name: path2basePath()
    std::string  getPath_woWC                (const char* pPath); // new name: path2basePath_woWC()
    
    std::string  getDirName                  (const char* pPath); // new name: path2dirName()
    uint         getDirName_begin_idx        (const char* pPath); // new name: path2dirName_begin_idx()
    uint         getDirName_end_idx          (const char* pPath); // new name: path2dirName_end_idx()
    uint         getDirName_end_idx_woWC     (const char* pPath); // new name: path2dirName_end_idx_woWC()
    
           char* getFileName                 (const char* pPath); // new name: path2fileName()
    std::string  getFileName_withoutExtension(const char* pPath); // new name: path2fileName_woExt()
    
           char* getExtension                (const char* pPath); // new name: path2fileExt()
    
    std::vector<std::string> parsePath_withBase(const char* pPath); // new name: parsePath_wBasePath()
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

// memo:
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
// Directory.GetDirectoryRoot    ボリューム、ルート情報の取得
// Directory.GetParent    親ディレクトリの取得


