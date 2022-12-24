#include "file_operations.hpp"

#include "file.hpp"
#include "../print/pdbg.hpp"

bool sstd::file_size(size_t& ret_size, const char* path){
    
    sstd::file fp;
    if(!fp.fopen(path, "rb")){ sstd::pdbg("ERROR: fopen was failed.\n"); printf("This error occurs when sstd::file_size() trying to open \"%s\".", path); return false; }
    ret_size = fp.fsize();
    
    return true;
}
