#include "file.hpp"


#ifdef _WIN32
	inline bool fopen_win32(FILE**& fp, const char*& FileName, const char*& mode){
		return (fopen_s(fp, FileName, mode)==NULL);
	}
#else
	inline bool fopen_linux(FILE**& fp, const char*& FileName, const char*& mode){
		*fp = fopen(FileName, mode);
		return (fp!=NULL);
	}
#endif


bool sstd::fopen(FILE** fp, const char* FileName, const char* mode){
#ifdef _WIN32
	return fopen_win32(fp, FileName, mode);
#else
	return fopen_linux(fp, FileName, mode);
#endif
}

/*
 * How to use this.
 *
 * printf("■ fopen\n");
 *
 * FILE* fp;
 * const char* FileName = "./test_fopen.txt";
 *
 * if(!sstd::fopen(&fp, FileName, "wb")){ // Enable to open file by the same code between MSVC++ and GCC.
 *     // falied
 *     printf("false\n\n");
 * }else{
 *     // success
 *     printf("example.txt was made.\n\n");
 *     fwrite("abc", 3, 1, fp);
 * }
 * fclose(fp);
 */
