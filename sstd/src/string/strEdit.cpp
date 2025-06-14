#include "strEdit.hpp"

#include "strmatch.hpp"
#include "../file/file.hpp"
#include "../print/pdbg.hpp"
#include <string.h>


//-----------------------------------------------------------------------------------------------------------------------------------------------

bool sstd::extract_quoted(std::vector<std::string>& ret_v, const        char* str){
    std::string ret_s;
    
    bool is_escaped=false;
    bool in_d_quate=false; // double quate
    bool in_s_quate=false; // single quate
    for(uint r=0; str[r]!='\0'; ++r){ // r: read place
        if(str[r]=='\\'){ ret_s+=str[r]; is_escaped=true; continue; }
        
        if(!is_escaped && !in_s_quate && str[r]=='"' ){ if(in_d_quate){ret_v.push_back(ret_s);ret_s.clear();} in_d_quate=!in_d_quate; continue; }
        if(!is_escaped && !in_d_quate && str[r]=='\''){ if(in_s_quate){ret_v.push_back(ret_s);ret_s.clear();} in_s_quate=!in_s_quate; continue; }
        is_escaped=false;
        
        if(!(in_s_quate || in_d_quate)){ continue; }
        ret_s += str[r];
    }
    if(in_d_quate){ return false; }
    if(in_s_quate){ return false; }

    return true;
}
bool sstd::extract_quoted(std::vector<std::string>& ret, const std::string& str){ return sstd::extract_quoted(ret, str.c_str()); }


bool sstd::extract_unquoted(std::string& ret, const char* str){
    bool is_escaped=false;
    bool in_d_quate=false; // double quate
    bool in_s_quate=false; // single quate
    for(uint r=0; str[r]!='\0'; ++r){ // r: read place
        if(str[r]=='\\'){ ret+=str[r]; is_escaped=true; continue; }
        
        if(!is_escaped && !in_s_quate && str[r]=='"' ){ in_d_quate = !in_d_quate; continue; }
        if(!is_escaped && !in_d_quate && str[r]=='\''){ in_s_quate = !in_s_quate; continue; }
        is_escaped=false;
        
        if(in_s_quate || in_d_quate){ continue; }
        ret += str[r];
    }
    if(in_d_quate){ return false; }
    if(in_s_quate){ return false; }

    return true;
}
bool sstd::extract_unquoted(std::string& ret, const std::string& str){ return sstd::extract_unquoted(ret, str.c_str()); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

std::vector<std::string> sstd::splitByLine(const char* str){

    std::vector<std::string> ret;
    
    std::string buf;
    for(uint r=0; str[r]!=0;){ // r: read place
        buf.clear();
        for(; str[r]!=0; ++r){
            if(str[r]==0x0A                  ){ r+=1; break; } // Uinx
            if(str[r]==0x0D && str[r+1]==0x0A){ r+=2; break; } // Windows
            buf += str[r];
        }
        ret.push_back(std::move(buf));
    }
    
    return ret;
}
std::vector<std::string> sstd::splitByLine(const std::string& str){
    return sstd::splitByLine(str.c_str());
}

//---

bool sstd::splitByLine_quotes(std::vector<std::string>& ret, const char* str){
    
    bool is_escaped=false;
    bool in_d_quate=false; // double quate
    bool in_s_quate=false; // single quate
    std::string buf;
    for(uint r=0; str[r]!=0;){ // r: read place
        buf.clear();
        for(; str[r]!='\0'; ++r){
            if(str[r]=='\\'){ is_escaped=true; buf+=str[r]; ++r; if(str[r]=='\0'){break;} }
            
            if(!is_escaped && !in_s_quate && str[r]=='"' ){ in_d_quate = !in_d_quate; }
            if(!is_escaped && !in_d_quate && str[r]=='\''){ in_s_quate = !in_s_quate; }
            
            if(!in_d_quate && !in_s_quate && str[r]==0x0A                  ){ r+=1; break; } // Uinx
            if(!in_d_quate && !in_s_quate && str[r]==0x0D && str[r+1]==0x0A){ r+=2; break; } // Windows
            buf += str[r];
            
            is_escaped=false;
        }
        ret.push_back(std::move(buf));
    }
    if(in_d_quate){ ret.clear(); return false; }
    if(in_s_quate){ ret.clear(); return false; }
    
    return true;
}
bool sstd::splitByLine_quotes(std::vector<std::string>& ret, const std::string& str){
    return sstd::splitByLine_quotes(ret, str.c_str());
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

std::vector<std::string> _asAX_rmSpace(const char* str, const char X, const int maxsplit){
    if(maxsplit==0){ return std::vector<std::string>({str}); }
    std::vector<std::string> splitList;
    
    std::string buf;
    uint i=0;
    
    while(str[i]!='\0'){ if(str[i]==' '){++i;}else{break;} } // skip space
    while(str[i]!='\0'){
        if(maxsplit>=0 && splitList.size()==(uint)maxsplit){
            buf += (const char*)&str[i];
            break;
        }
        
        if(X==str[i]){
            sstd::rstrip_ow(buf); splitList.push_back(buf); buf.clear();
            ++i;
            while(str[i]!=0){ if(' '==str[i]){++i;}else{break;} } // skip space
        }else{
            buf+=str[i];
            ++i;
        }
    }
    if(buf.size()!=0){ sstd::rstrip_ow(buf); splitList.push_back(buf); }
//    if(i>=1 && str[i-1]==X){ splitList.push_back(std::string()); }
    return splitList;
}
std::vector<std::string> _asAX(const char* str, const char X){
    std::vector<std::string> splitList;
    
    std::string buf;
    uint i=0;
//    while(str[i]!='\0'){ if(' '==str[i]){++i;}else{break;} } // skip space
    while(str[i]!='\0'){
        if(X==str[i]){
//            sstd::rstrip_ow(buf); splitList.push_back(buf); buf.clear();
            splitList.push_back(buf); buf.clear();
            ++i;
//            while(str[i]!=0){ if(' '==str[i]){++i;}else{break;} } // skip space
        }else{
            buf+=str[i];
            ++i;
        }
    }
//    if(buf.size()!=0){ sstd::rstrip_ow(buf); splitList.push_back(buf); }
    if(buf.size()!=0){ splitList.push_back(buf); }
    if(i>=1 && str[i-1]==X){ splitList.push_back(std::string()); }
    return splitList;
}
std::vector<std::string> sstd::split(const        char* str              ){ return _asAX_rmSpace(str,         ' ',       -1); }
std::vector<std::string> sstd::split(const std::string& str              ){ return _asAX_rmSpace(str.c_str(), ' ',       -1); }
std::vector<std::string> sstd::split(const char*        str, int maxsplit){ return _asAX_rmSpace(str,         ' ', maxsplit); }
std::vector<std::string> sstd::split(const std::string& str, int maxsplit){ return _asAX_rmSpace(str.c_str(), ' ', maxsplit); }
std::vector<std::string> sstd::split(const        char* str, const char X){ return _asAX(str,          X ); }
std::vector<std::string> sstd::split(const std::string& str, const char X){ return _asAX(str.c_str(),  X ); }

std::vector<std::string> _split_ss_base(const char* str, const uint str_len, const char* X, const uint X_len){
    if(X_len==0){ return std::vector<std::string>({str}); }
    if(X_len==1){ return sstd::split(str, X[0]); }
    
    std::vector<std::string> splitList;
    std::string buf;
    for(uint i=0; i<str_len; ++i){
        if(::strncmp(&str[i], X, X_len)==0){
            i += X_len-1;
            splitList.push_back(buf);
            buf.clear();

            if(i+1==str_len){ splitList.push_back(std::string()); }
        }else{
            buf += str[i];
        }
    }
    if(buf.size()!=0){ splitList.push_back(buf); }
    return splitList;
}
std::vector<std::string> sstd::split(const char*        str, const char*        X){ return _split_ss_base(str        , ::strlen(str), X        , ::strlen(X)); }
std::vector<std::string> sstd::split(const std::string& str, const std::string& X){ return _split_ss_base(str.c_str(),    str.size(), X.c_str(),    X.size()); }

//---

std::vector<std::string> _split_all_base(const char* str, const uint str_len, const char* X, const uint X_len){
    if(X_len==0){ return std::vector<std::string>({str}); }
    
    std::vector<std::string> splitList;
    std::string buf;
    for(uint i=0; str[i]!='\0'; ++i){
        if(!sstd::charIn(str[i], X)){
            buf += str[i];
        }else{
            splitList.push_back(buf);
            buf.clear();
        }
    }
    if((str_len>=1 && sstd::charIn(str[str_len-1], X)) || buf.size()!=0){ splitList.push_back(buf); }
    return splitList;
}
std::vector<std::string> sstd::splitAll(const char*        str, const char*        X){ return _split_all_base(str,         ::strlen(str), X,         ::strlen(X)); }
std::vector<std::string> sstd::splitAll(const std::string& str, const char*        X){ return _split_all_base(str.c_str(),    str.size(), X,         ::strlen(X)); }
std::vector<std::string> sstd::splitAll(const char*        str, const std::string& X){ return _split_all_base(str,         ::strlen(str), X.c_str(),    X.size()); }
std::vector<std::string> sstd::splitAll(const std::string& str, const std::string& X){ return _split_all_base(str.c_str(),    str.size(), X.c_str(),    X.size()); }

//---

std::vector<std::string> sstd::split_rmSpace(const        char* str              ){ return _asAX_rmSpace(str,         ' ', -1); }
std::vector<std::string> sstd::split_rmSpace(const std::string& str              ){ return _asAX_rmSpace(str.c_str(), ' ', -1); }
std::vector<std::string> sstd::split_rmSpace(const        char* str, const char X){ return _asAX_rmSpace(str        ,  X , -1); }
std::vector<std::string> sstd::split_rmSpace(const std::string& str, const char X){ return _asAX_rmSpace(str.c_str(),  X , -1); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool sstd::split_quotes(std::vector<std::string>& ret, const        char* str){
    bool is_escaped=false;
    bool in_d_quate=false; // double quate
    bool in_s_quate=false; // single quate
    std::string buf;
    uint i=0;
    while(str[i]!='\0'){ if(str[i]==' '){++i;}else{break;} } // skip space
    while(str[i]!='\0'){ // r: read place
        if(str[i]=='\\'){ is_escaped=true; buf+=str[i]; ++i; if(str[i]=='\0'){break;} }
        
        if(!is_escaped && !in_s_quate && str[i]=='"' ){ in_d_quate = !in_d_quate; }
        if(!is_escaped && !in_d_quate && str[i]=='\''){ in_s_quate = !in_s_quate; }
        
        if(!in_d_quate && !in_s_quate && str[i]==' '){
            ret.push_back(buf); buf.clear();
            ++i;
            while(str[i]!='\0'){ if(str[i]==' '){++i;}else{break;} } // skip space
        }else{
            buf += str[i];
            ++i;
        }
        
        is_escaped=false;
    }
    if(in_d_quate){ ret.clear(); return false; }
    if(in_s_quate){ ret.clear(); return false; }
    if(buf.size()!=0){ ret.push_back(buf); }
//    if(r==0 || (r>=1 && str[r-1]==X)){ ret.push_back(std::string()); }
//    if(r>=1 && str[r-1]==X){ ret.push_back(std::string()); }
    
    return true;
}
bool sstd::split_quotes(std::vector<std::string>& ret, const std::string& str){
    return sstd::split_quotes(ret, str.c_str());
}

//---

bool sstd::split_quotes(std::vector<std::string>& ret, const char* str, const char X){
    bool is_escaped=false;
    bool in_d_quate=false; // double quate
    bool in_s_quate=false; // single quate
    std::string buf;
    uint i=0;
    // while(str[i]!='\0'){ if(str[i]==' '){++i;}else{break;} } // skip space
    while(str[i]!='\0'){ // r: read place
        if(str[i]=='\\'){ is_escaped=true; buf+=str[i]; ++i; if(str[i]=='\0'){break;} }

        if(!is_escaped && !in_s_quate && str[i]=='"' ){ in_d_quate = !in_d_quate; }
        if(!is_escaped && !in_d_quate && str[i]=='\''){ in_s_quate = !in_s_quate; }

        if(!in_d_quate && !in_s_quate && str[i]==X){
            ret.push_back(buf); buf.clear();
            ++i;
            // while(str[i]!='\0'){ if(str[i]==' '){++i;}else{break;} } // skip space
        }else{
            buf += str[i];
            ++i;
        }

        is_escaped=false;
    }
    if(in_d_quate){ ret.clear(); return false; }
    if(in_s_quate){ ret.clear(); return false; }
    if(buf.size()!=0){ ret.push_back(buf); }
    // if(i==0 || (i>=1 && str[i-1]==X)){ ret.push_back(std::string()); } // compatible with Python split()
    if(i>=1 && str[i-1]==X){ ret.push_back(std::string()); }

    return true;
}
bool sstd::split_quotes(std::vector<std::string>& ret, const std::string& str, const char X){
    return sstd::split_quotes(ret, str.c_str(), X);
}

//---

bool _split_quotes_base(std::vector<std::string>& ret, const char* str, const uint str_len, const char* X, const uint X_len){
    bool is_escaped=false;
    bool in_d_quate=false; // double quate
    bool in_s_quate=false; // single quate
    std::string buf;
    uint i=0;
    // while(str[i]!='\0'){ if(str[i]==' '){++i;}else{break;} } // skip space
    while(i<str_len){ // r: read place
        if(str[i]=='\\'){ is_escaped=true; buf+=str[i]; ++i; if(i>=str_len){break;} }
        
        if(!is_escaped && !in_s_quate && str[i]=='"' ){ in_d_quate = !in_d_quate; }
        if(!is_escaped && !in_d_quate && str[i]=='\''){ in_s_quate = !in_s_quate; }
        
        if(!in_d_quate && !in_s_quate && sstd::startswith(&str[i], X)){
            ret.push_back(buf); buf.clear();
            i += X_len;
            // while(str[i]!='\0'){ if(str[i]==' '){++i;}else{break;} } // skip space
        }else{
            buf += str[i];
            ++i;
        }
        
        is_escaped=false;
    }
    if(in_d_quate){ ret.clear(); return false; }
    if(in_s_quate){ ret.clear(); return false; }
    if(buf.size()!=0){ ret.push_back(buf); }
    // if(i==0 || (i>=X_len && sstd::startswith(&str[i-X_len], X))){ ret.push_back(std::string()); } // compatible with Python split()
    if(i>=X_len && sstd::startswith(&str[i-X_len], X)){ ret.push_back(std::string()); }
    
    return true;
}
bool sstd::split_quotes(std::vector<std::string>& ret, const        char* str, const char*        X){
    return _split_quotes_base(ret, str, strlen(str), X, strlen(X));
}
bool sstd::split_quotes(std::vector<std::string>& ret, const std::string& str, const std::string& X){
    return _split_quotes_base(ret, str.c_str(), str.size(), X.c_str(), X.size());
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

std::string lstrip_base(const uchar* str){
    std::string ret;
    
    uint r=0;
    for(; str[r]!=0; ++r){
        if(str[r]==' ' || str[r]=='\t'){
        }             else             { break; }
    }
    for(; str[r]!=0; ++r){ ret+=str[r]; }
    
    return ret;
}
std::string              sstd::lstrip(const                    char * str){ return lstrip_base((const uchar*)str        ); }
std::string              sstd::lstrip(const             std::string & str){ return lstrip_base((const uchar*)str.c_str()); }
std::vector<std::string> sstd::lstrip(const std::vector<std::string>& vec){
    std::vector<std::string> ret_vec(vec.size());
    for(uint i=0; i<vec.size(); ++i){ ret_vec[i]=lstrip_base((const uchar*)vec[i].c_str()); }
    return ret_vec;
}

void sstd::lstrip_ow(std::string& str){
    std::string sre_ret = sstd::lstrip(str);
    str = std::move(sre_ret);
}
void sstd::lstrip_ow(std::vector<std::string>& vec){ for(uint i=0;i<vec.size();++i){sstd::lstrip_ow(vec[i]);} }

std::string rstrip_base(const uchar* str, int len){
    int r=len-1;
    for(; r>=0; --r){
        if(str[r]==' ' || str[r]=='\t'){
        }             else             { break; }
    }
    return std::string((const char*)str, r+1);
}
std::string              sstd::rstrip(const                    char * str){ return rstrip_base((const uchar*)str,         strlen(str)); }
std::string              sstd::rstrip(const             std::string & str){ return rstrip_base((const uchar*)str.c_str(), str.size() ); }
std::vector<std::string> sstd::rstrip(const std::vector<std::string>& vec){
    std::vector<std::string> ret_vec(vec.size());
    for(uint i=0; i<vec.size(); ++i){ ret_vec[i]=rstrip_base((const uchar*)vec[i].c_str(), vec[i].size()); }
    return ret_vec;
}

void sstd::rstrip_ow(std::string& str){
    for(int r=str.size()-1; r>=0; --r){
        if(str[r]==' ' || str[r]=='\t'){ str.erase(r);
        }             else             { break; }
    }
}
void sstd::rstrip_ow(std::vector<std::string>& vec){ for(uint i=0;i<vec.size();++i){sstd::rstrip_ow(vec[i]);} }

std::string strip_base(const uchar* str){
    std::string ret = lstrip_base(str);
    sstd::rstrip_ow(ret);
    return ret;
}
std::string sstd::strip(const        char* str){ return strip_base((const uchar*)str        ); }
std::string sstd::strip(const std::string& str){ return strip_base((const uchar*)str.c_str()); }

std::vector<std::string> sstd::strip(const std::vector<std::string>& vec){
    std::vector<std::string> ret(vec.size()); ret.clear();
    
    for(uint i=0; i<vec.size(); ++i){
        ret.push_back(strip_base((const uchar*)vec[i].c_str()));
    }
    
    return ret;
}

void sstd::strip_ow(std::string& str){
    str = lstrip_base((const uchar*)str.c_str());
    sstd::rstrip_ow(str);
}
void sstd::strip_ow(std::vector<std::string>& v){
    for(uint i=0; i<v.size(); ++i){
        sstd::strip_ow(v[i]);
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

std::string lstrip_base(const char* str, const uint len, const char c){
    uint i=0;
    while(i<len && str[i]==c){ ++i; }
    
    return std::string(&str[i], len-i);
}
std::string sstd::lstrip   (const        char* str, const char c){ return lstrip_base(str,         strlen(str), c); }
std::string sstd::lstrip   (const std::string& str, const char c){ return lstrip_base(str.c_str(),  str.size(), c); }
void        sstd::lstrip_ow(      std::string& str, const char c){
    uint i=0;
    while(i<str.size() && str[i]==c){ ++i; }

    uint r=0;
    for(; i<str.size(); ++r, ++i){
        str[r] = str[i];
    }
    str.resize(r);
}

//---

std::string rstrip_base(const char* str, const uint len, const char c){
    int i=len-1;
    while(i>=0 && str[i]==c){ --i; }
    
    return std::string(&str[0], i+1);
}
std::string sstd::rstrip   (const        char* str, const char c){ return rstrip_base(str,         strlen(str), c); }
std::string sstd::rstrip   (const std::string& str, const char c){ return rstrip_base(str.c_str(),  str.size(), c); }
void        sstd::rstrip_ow(      std::string& str, const char c){
    int i=str.size()-1;
    while(i>=0 && str[i]==c){ --i; }
    
    str.resize(i+1);
}

//---

std::string strip_base(const char* str, uint len, const char c){
    uint b=0; // begin
    while(b<len && str[b]==c){ ++b; }
    if(b==len){ return std::string(); }
    
    int e=len-1; // end
    while(e>=0 && str[e]==c){ --e; }
    
//    if(e<(int)b){ return std::string(); }
    return std::string(&str[b], e-b+1);
}
std::string sstd::strip   (const        char* str, const char c){ return strip_base(str,         strlen(str), c); }
std::string sstd::strip   (const std::string& str, const char c){ return strip_base(str.c_str(),  str.size(), c); }
void        sstd::strip_ow(      std::string& str, const char c){
    uint b=0; // begin
    while(b<str.size() && str[b]==c){ ++b; }
    if(b==str.size()){ str.resize(0); return; }
    
    int e=str.size()-1; // end
    while(e>=0 && str[e]==c){ --e; }

    uint r=0;
    for(uint i=b; i<(uint)e+1; ++r, ++i){
        str[r] = str[i];
    }
    str.resize(e-b+1);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

std::string stripAll_base(const char* str, const uint len, const char c){
    std::string ret('0', len); ret.clear();
    
    for(uint i=0; i<len; ++i){
        if(str[i]==c){ continue; }
        ret += str[i];
    }
    return ret;
}
std::string sstd::stripAll(const        char* str, const char c){ return stripAll_base(str,         strlen(str), c); }
std::string sstd::stripAll(const std::string& str, const char c){ return stripAll_base(str.c_str(),  str.size(), c); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

void sstd::stripAll_ow(std::string& str, const char c){
    uint r=0;
    
    for(uint i=0; i<str.size(); ++i){
        if(str[i]==c){ continue; }
        str[r] = str[i]; ++r;
    }
    
    str.resize(r);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

std::string stripAll_base(const char* str, const uint len, const char* stripList, const uint sLen){
    std::string ret('0', len); ret.clear();
    
    if(len * sLen <= 256){
        for(uint i=0; i<len; ++i){
            if(sstd::charIn(str[i], stripList)){ continue; }
            ret += str[i];
        }
    }else{
        bool sTbl[256]={false};
        for(uint si=0; si<sLen; ++si){ sTbl[ (uchar)stripList[si] ] = true; }
        
        for(uint i=0; i<len; ++i){
            if( sTbl[ (uchar)str[i] ] ){ continue; }
            ret += str[i];
        }
    }
    
    return ret;
}
std::string sstd::stripAll   (const        char* str, const        char* stripList){ return stripAll_base(str,         strlen(str), stripList,         strlen(stripList)); }
std::string sstd::stripAll   (const std::string& str, const        char* stripList){ return stripAll_base(str.c_str(),  str.size(), stripList,         strlen(stripList)); }
std::string sstd::stripAll   (const        char* str, const std::string& stripList){ return stripAll_base(str,         strlen(str), stripList.c_str(),  stripList.size()); }
std::string sstd::stripAll   (const std::string& str, const std::string& stripList){ return stripAll_base(str.c_str(),  str.size(), stripList.c_str(),  stripList.size()); }

//---

void lstripAll_ow_base(std::string& str, const char* stripList, const uint sLen){
    const uint len = str.size();
    uint r=0;
    
    if(len * sLen <= 256){
        for(; r<len;){
            if(!sstd::charIn(str[r], stripList)){ break; }
            ++r;
        }
    }else{
        bool sTbl[256]={false};
        for(uint si=0; si<sLen; ++si){ sTbl[ (uchar)stripList[si] ] = true; }
        
        for(; r<len;){
            if(! sTbl[ (uchar)str[r] ] ){ break; }
            ++r;
        }
    }
    
    int r_len=(int)len-(int)r;
    std::string tmp; tmp.resize(r_len);
    ::memcpy(&tmp[0], &str[r], r_len);
    std::swap(tmp, str);
    return;
}
void sstd::lstripAll_ow(      std::string& str, const        char* stripList){ lstripAll_ow_base(str, stripList,         strlen(stripList)); return; }
void sstd::lstripAll_ow(      std::string& str, const std::string& stripList){ lstripAll_ow_base(str, stripList.c_str(),  stripList.size()); return; }

void rstripAll_ow_base(std::string& str, const char* stripList, const uint sLen){
    const int len = str.size();
    int r=len-1;
    
    if(len * sLen <= 256){
        for(; r>=0;){
            if(!sstd::charIn(str[r], stripList)){ break; }
            --r;
        }
    }else{
        bool sTbl[256]={false};
        for(uint si=0; si<sLen; ++si){ sTbl[ (uchar)stripList[si] ] = true; }
        
        for(; r>=0;){
            if(! sTbl[ (uchar)str[r] ] ){ break; }
            --r;
        }
    }
    
    str.resize(r+1);
    return;
}
void sstd::rstripAll_ow(      std::string& str, const        char* stripList){ rstripAll_ow_base(str, stripList,         strlen(stripList)); return; }
void sstd::rstripAll_ow(      std::string& str, const std::string& stripList){ rstripAll_ow_base(str, stripList.c_str(),  stripList.size()); return; }

void stripAll_ow_base(std::string& str, const char* stripList, const uint sLen){
    const uint len = str.size();
    uint r=0;
    
    if(len * sLen <= 256){
        for(uint i=0; i<len; ++i){
            if(sstd::charIn(str[i], stripList)){ continue; }
            str[r] = str[i]; ++r;
        }
    }else{
        bool sTbl[256]={false};
        for(uint si=0; si<sLen; ++si){ sTbl[ (uchar)stripList[si] ] = true; }
        
        for(uint i=0; i<len; ++i){
            if( sTbl[ (uchar)str[i] ] ){ continue; }
            str[r] = str[i]; ++r;
        }
    }
    
    str.resize(r);
    return;
}
void        sstd::stripAll_ow(      std::string& str, const        char* stripList){ stripAll_ow_base(str, stripList,         strlen(stripList)); return; }
void        sstd::stripAll_ow(      std::string& str, const std::string& stripList){ stripAll_ow_base(str, stripList.c_str(),  stripList.size()); return; }

//-----------------------------------------------------------------------------------------------------------------------------------------------

std::string sstd::strip_quotes(bool& ret_sq, bool& ret_dq, const        char* str){
    return sstd::strip_quotes(ret_sq, ret_dq, std::string(str));
}
std::string sstd::strip_quotes(bool& ret_sq, bool& ret_dq, const std::string& str){
    ret_dq=false;
    ret_sq=false;
    
    // remove head and tail ' ' and '\t'
    int li=0, ri=((int)str.size())-1;
    while(li<(int)str.size()){
        if(str[li]!=' ' && str[li]!='\t'){ break; } // remove head ' ' and '\t'
        ++li;
    }
    while(ri>=li){
        if(str[ri]!=' ' && str[ri]!='\t'){ break; } // remove tail ' ' and '\t'
        --ri;
    }
    
    // remove head and tail '"' or '\''
    std::string tmp;
    {
        if((ri+1 - li)<= 0){ return std::string(); }
        
        char c_head = str[li];
        char c_tail = str[ri];
        
        // rm '"'
        if(c_head=='"' && c_tail=='"'){
            ++li;
            --ri;
            ret_dq=true;
        }
        
        // rm '\''
        if(c_head=='\'' && c_tail=='\''){
            ++li;
            --ri;
            ret_sq=true;
        }
        
        tmp = str.substr(li, ri-li+1);
    }

    return tmp;
}
std::string sstd::strip_quotes(const        char* str){ bool ret_sq, ret_dq; return sstd::strip_quotes(ret_sq, ret_dq, str); }
std::string sstd::strip_quotes(const std::string& str){ bool ret_sq, ret_dq; return sstd::strip_quotes(ret_sq, ret_dq, str); }

//-----------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
std::string _join(const std::vector<std::string>& v, T delimiter){
    std::string ret;
    if(v.size()==0){ return ret; }
    
    ret += v[0];
    for(uint i=1; i<v.size(); ++i){
        ret += delimiter + v[i];
    }
    
    return ret;
}

std::string sstd::join(const std::vector<std::string>& v, const char delimiter){
    return _join<const char>(v, delimiter);
}
std::string sstd::join(const std::vector<std::string>& v, const char* delimiter){
    return _join<const char*>(v, delimiter);
}
std::string sstd::join(const std::vector<std::string>& v, const std::string& delimiter){
    return sstd::join(v, delimiter.c_str());
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

