#include "read_write.hpp"
#include "file.hpp"

#include "../string/strEdit.hpp"
#include "../pdbg.hpp"
#include <string.h>


//--------------------------------------------------------------------------------------------------------
// read all data in a file as a binary

std::vector<uint8> sstd::read_bin(const char* path){
    sstd::file fp; if(!fp.fopen(path, "rb")){ sstd::pdbg_err("fopen was failed.\n"); return std::vector<uint8>(); }
    size_t size = fp.fsize(); // ファイルサイズを取得
    std::vector<uint8> raw(size, 0); //0で初期化
    if(fp.fread((uchar*)&raw[0], sizeof(char), size)!=size){ sstd::pdbg_err("fread was failed.\n"); return std::vector<uint8>(); }
    return raw;
}
std::vector<uint8> sstd::read_bin(const std::string& path){ return sstd::read_bin(path.c_str()); }

//--------------------------------------------------------------------------------------------------------
// write all data to a file as a binary

bool sstd::write_bin(const char* path, std::vector<uint8>& rhs){
    sstd::file fp;
    if(!fp.fopen(path, "wb")){ sstd::pdbg_err("sstd::file::fopen(%s) was failed.\n", path); return false; }
    if(!fp.fwrite(&rhs[0], sizeof(char), rhs.size())){ sstd::pdbg_err("sstd::file::fwrite(%s) was failed.\n", path); return false; }
    return true;
}
bool sstd::write_bin(const std::string& path, std::vector<uint8>& rhs){ return sstd::write_bin(path.c_str(), rhs); }

//--------------------------------------------------------------------------------------------------------
// read

std::string sstd::read(const char* path){
    sstd::file fp; if(!fp.fopen(path, "rb")){ sstd::pdbg_err("fopen was failed.\n"); return std::string(); }
    size_t size = fp.fsize();
    std::string str(size, 0);
    if(fp.fread((uchar*)&str[0], sizeof(char), size)!=size){ sstd::pdbg_err("fread was failed.\n"); return std::string(); }
    return str;
}
std::string sstd::read(const std::string& path){ return sstd::read(path.c_str()); }

void ignoreBOM(uchar* str, uint& r){

    // UTF-8 以外の場合は，UTF-8 に変換するコードを追加するとよい．
    // it will be better to add functions which will translate to UTF-8 while input file is not UTF-8.
    
    if      (str[0]==0xEF && str[1]==0xBB && str[2]==0xBF){ r+=3;                 // UTF-8
    }else if(str[0]==0xFE && str[1]==0xFF){ r+=2;                                 // UTF-16 BE (Big endian): Not compatible with ASCII code
    }else if(str[0]==0xFF && str[1]==0xFE){ r+=2;                                 // UTF-16 LE (Little endian): Not compatible with ASCII code
    }else if(str[0]==0x00 && str[1]==0x00 && str[2]==0xFE && str[3]==0xFF){ r+=4; // UTF-32 BE (Big endian): Not compatible with ASCII code
    }else if(str[0]==0xFF && str[1]==0xFE && str[2]==0x00 && str[3]==0x00){ r+=4; // UTF-32 LE (Little endian): Not compatible with ASCII code
    }else if(str[0]==0x2B && str[1]==0x2F && str[2]==0x76){ r+=3;                 // UTF-7: Not compatible with ASCII code
    }else if(str[0]==0x2B && str[1]==0x2F && str[2]==0x38){ r+=3;                 // UTF-7: Not compatible with ASCII code
    }else if(str[0]==0x2B && str[1]==0x2F && str[2]==0x39){ r+=3;                 // UTF-7: Not compatible with ASCII code
    }else if(str[0]==0x2B && str[1]==0x2F && str[2]==0x2B){ r+=3;                 // UTF-7: Not compatible with ASCII code
    }else if(str[0]==0x2B && str[1]==0x2F && str[2]==0x2F){ r+=3;                 // UTF-7: Not compatible with ASCII code
    }else{
        // UTF-8N (UTF-8 without BOM), 
        // UTF-16BE (UTF-16 without BOM), 
        // UTF-16LE (UTF-32 without BOM), 
        // UTF-32BE (UTF-32 without BOM), 
        // UTF-32LE (UTF-32 without BOM), 
        // or the other encoding.
    }
}
bool read_woBOM_base(std::string& ret_str, const char* path){

    sstd::file fp;
    if(!fp.fopen(path, "rb")){ sstd::pdbg_err("fopen was failed.\n  File path: %s\n", path); return false; }

    // check BOM (Byte Order Mark)
    uint BOM_len=0;
    uchar check_BOM[4];
    fp.fread(&check_BOM[0], sizeof(uchar), 4);
    ignoreBOM(check_BOM, BOM_len);

    size_t size = fp.fsize() - BOM_len;
    fp.fseek(BOM_len, SEEK_SET);    //ファイルポインタを先頭 + BOM_len に戻す。

    ret_str.resize(size, 0);
    
    if(fp.fread(&ret_str[0], sizeof(char), size)!=size){ sstd::pdbg_err("fread was failed.\n  File path: %s\n", path); return false; }

    return true;
}
std::string sstd::read_withoutBOM(const        char* path){ std::string ret; read_woBOM_base(ret, path        ); return ret; }
std::string sstd::read_withoutBOM(const std::string& path){ std::string ret; read_woBOM_base(ret, path.c_str()); return ret; }
bool sstd::read_woBOM(std::string& ret_str, const char*        path){ return read_woBOM_base(ret_str, path        ); }
bool sstd::read_woBOM(std::string& ret_str, const std::string& path){ return read_woBOM_base(ret_str, path.c_str()); }

//--------------------------------------------------------------------------------------------------------
// write

size_t sstd::write(const char* path, const void* ptr, const size_t type_size, const size_t num){ // (1)
    size_t w_size = 0;
    sstd::file fp; if(! fp.fopen(path, "wb") ){ return w_size; }
    w_size = fp.fwrite(ptr, type_size, num);
    return w_size;
}
size_t sstd::write(const std::string& path, const void* ptr, const size_t type_size, const size_t num){ // (2)
    return sstd::write(path.c_str(), ptr, type_size, num);
}
size_t sstd::write(const char* path, const std::string& s){ // (3)
    return sstd::write(path, &s[0], sizeof(char), s.size());
}
size_t sstd::write(const std::string& path, const char* s){ // (4)
    return sstd::write(path.c_str(), s, sizeof(char), strlen(s));
}
size_t sstd::write(const std::string& path, const std::string& s){ // (5)
    return sstd::write(path.c_str(), &s[0], sizeof(char), s.size());
}

//--------------------------------------------------------------------------------------------------------
