#include "file.hpp"


#ifdef _WIN32
	inline bool sstd_file_fopen_win32(FILE** fp, const char*& fileName, const char*& mode){
		return (fopen_s(fp, fileName, mode)==NULL);
	}
#else
	inline bool sstd_file_fopen_linux(FILE** fp, const char*& fileName, const char*& mode){
		*fp = fopen(fileName, mode);
		return (*fp!=NULL);
	}
#endif
bool sstd::file::fopen(const char* fileName, const char* mode){
	#ifdef _WIN32
		return sstd_file_fopen_win32(&fp, fileName, mode);
	#else
		return sstd_file_fopen_linux(&this->fp, fileName, mode);
	#endif
}
bool sstd::file::fopen(const std::string& fileName, const char* mode){ return sstd::file::fopen(fileName.c_str(), mode); }

bool sstd_file_fclose(FILE*& stream){ if(fclose(stream)==0){return true;}else{return false;} }
bool sstd::file::fclose(){ if(fp!=0){ return sstd_file_fclose(fp); }else{ return false; } }

inline size_t sstd_file_fread(void*& ptr, const size_t& size, const size_t& nmemb, FILE*& fp){ return fread(ptr, size, nmemb, fp); }
size_t sstd::file::fread(void* ptr, const size_t& size, const size_t& nmemb){ return sstd_file_fread(ptr, size, nmemb, this->fp); }

inline size_t sstd_file_fwrite(const void*& ptr, const size_t& size, const size_t& nmemb, FILE*& fp){ return fwrite(ptr, size, nmemb, fp); }
size_t sstd::file::fwrite(const void* ptr, const size_t& size, const size_t& nmemb){ return sstd_file_fwrite(ptr, size, nmemb, this->fp); }

long sstd_file_fseek(FILE*& fp, const long& offset, const int& whence){ return fseek(fp, offset, whence); }
int sstd::file::fseek(const long& offset, const int& whence){ return sstd_file_fseek(this->fp, offset, whence); }

long sstd_file_ftell(FILE*& fp){ return ftell(fp); }
long sstd::file::ftell(){ return sstd_file_ftell(this->fp); }

size_t sstd::file::fsize(){
	size_t size_buf = sstd_file_ftell(fp); // ファイルポインタの位置を記録しておく．
	sstd_file_fseek(fp, 0, SEEK_END);      // ファイルポインタをファイルの最後に移動させる．
	size_t size = sstd_file_ftell(fp);     // ファイルサイズを取得する．        // fgetpos(fp, &size);
	sstd_file_fseek(fp, 0, size_buf);      // ファイルポインタを元の位置に戻す．// fseek(fp, 0L, SEEK_SET); ファイルポインタを先頭に戻す．
	return size;
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
