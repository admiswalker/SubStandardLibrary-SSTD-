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

bool sstd::file::fclose(){ if(fp!=0){ return ::fclose(fp)==0; }else{ return false; } }
size_t sstd::file::fread(void* ptr, const size_t& size, const size_t& nmemb){ return ::fread(ptr, size, nmemb, this->fp); }
size_t sstd::file::fwrite(const void* ptr, const size_t& size, const size_t& nmemb){ return ::fwrite(ptr, size, nmemb, this->fp); }
int sstd::file::fseek(const long& offset, const int& whence){ return ::fseek(this->fp, offset, whence); }
long sstd::file::ftell(){ return ::ftell(this->fp); }

size_t sstd::file::fsize(){
	size_t size_buf = ::ftell(fp);   // ファイルポインタの位置を記録しておく
	::fseek(fp, 0, SEEK_END);        // ファイルポインタをファイルの最後に移動させる
	size_t size = ::ftell(fp);       // ファイルサイズを取得する        // fgetpos(fp, &size);
	::fseek(fp, size_buf, SEEK_SET); // ファイルポインタを元の位置に戻す
	return size;
}

