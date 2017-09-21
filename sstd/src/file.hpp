#pragma once

#include <stdio.h>

namespace sstd{
	bool fopen(FILE** fp, const char* FileName, const char* mode);
}

/*
 * How to use this.
 * 
 * FILE* fp;
 * const char* FileName = "./example.txt";
 * if(!sstd::fopen(&fp, FileName, "wb")){ // Enable to open file by the same code between VSC++ and GCC.
 *     // falied
 *     printf("false\n\n");
 * }else{
 *     // success
 *     printf("example.txt was made.\n\n");
 *     fwrite("abc", 3, 1, fp);
 * }
 * fclose(fp);
 */
