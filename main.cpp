#define DEBUG
//#define use_sstd_pause        // Enable to switch "Pause" or "Not Pause" by "#define UseSysPause".
#define use_sstd_pauseIfWin32    // Enable to switch "Pause" or "Not Pause" by "#define UsePauseIfWin32".
#ifdef _WIN32
    #include "./sstd/sstd.hpp"
#else
    #include <sstd/sstd.hpp>
#endif

#include <gtest/gtest.h>

//-----------------------------------------------------------------------------------------------------------------------------------------------

// Remove comment out when you test it.
#include "./test/c2py.hpp"
#include "./test/csv.hpp"
#include "./test/glob.hpp"
#include "./test/math.hpp"
#include "./test/measureTime.hpp"
#include "./test/print_printn_printn_all.hpp" // void pdbg(){ printf("======p\n"); } // #define DEBUG を定義しない場合でも，マクロでこの名前は使えなくなるので，名前空間を汚しており，本当はよくない．
#include "./test/status.hpp"
#include "./test/stdlib.hpp"
#include "./test/strEdit.hpp"
#include "./test/typeConversion.hpp"
#include "./test/vector_slice.hpp"
#include "./test/vector_stdVector_expansion.hpp" // stdVector_expansion of operators
#include "./test/vector_vvec.hpp"


/*
// Move on to google c++ testing framework sequentially.
void TEST_time();
void TEST_typeDef();
void TEST_pdbg();
void TEST_signal();
void TEST_file();
void TEST_file_c();
void TEST_mkdir();
void TEST_rm();
void TEST_ssprintf();
void TEST_strmatch();
void TEST_path();
void TEST_tinyInterpreter();
void TEST_encode_decode();
void TEST_hashFnc();
void TEST_pause();
//void TEST_getpid(); // <- Needed to write test.

// sstd/src/MatrixStore_mat
void TEST_mat_colMajor();
void TEST_mat_rowMajor();
void TEST_bmat();
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char** argv){
    printf("\n");
    printf("+---------------------------------------------------+\n");
    printf("|                                                   |\n");
    printf("|     Welcome to Sub Standard Library (SSTD) !      |\n");
    printf("|                                                   |\n");
    printf("+---------------------------------------------------+\n");
    printf("\n");
    printf("■ measureTime_start---------------\n\n"); time_m timem; sstd::measureTime_start(timem);
    ::testing::InitGoogleTest(&argc, argv);
    
    auto ret = RUN_ALL_TESTS();

//    TEST_time();
//    TEST_typeDef();
//    TEST_pdbg();
//    TEST_math();
//    TEST_signal();
//    TEST_file();
//    TEST_file_c();
//    TEST_mkdir();
//    TEST_rm();
//    TEST_str2num();
//    TEST_ssprintf();
//    TEST_strmatch();
//    TEST_path();
//    TEST_tinyInterpreter();
//    TEST_encode_decode();
//    TEST_hashFnc();
//    TEST_pause();
    
//    TEST_mat_colMajor(); // TODO: write tests (zeros, Tr) // sstd::print 関数のテストを書くように
//    TEST_mat_rowMajor(); // TODO: write tests (zeros, Tr) // sstd::print 関数のテストを書くように
//    TEST_bmat();
    
    printf("\n");
    printf("■ measureTime_stop----------------\n");
    sstd::measureTime_stop_print(timem);
    sstd::pauseIfWin32();
    return ret;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
/*
void TEST_time(){
    printf("■ time\n");
    time_t      c_time    = time(0); // get current time
    struct tm   c_tm      = sstd::time2tm(c_time);
    time_t      c_time_2  = sstd::tm2time(c_tm);
    double      unixday   = sstd::time2unixday(c_time);
    double      unixday_2 = sstd::tm2unixday(c_tm);
    printf("GMT: %s\n", sstd::tm2str(c_tm).c_str());
    printf("GMT: %s\n", sstd::time2str(c_time_2).c_str());
    printf("unixday: %lf\n", unixday);
    printf("unixday: %lf\n", unixday_2);
    printf("\n");

    struct tm   c_tm_l   = sstd::timeGm2tmLocal(c_time);
    time_t      c_time_3 = sstd::tmLocal2timeGm(c_tm_l);
    printf("local: %s\n",  sstd::tm2str(c_tm_l).c_str());
    printf("GMT: %s\n",    sstd::time2str(c_time_3).c_str());
    printf("\n");
    
    time_t c_time_yday  = sstd::yday2time(c_tm.tm_year+1900, c_tm.tm_yday+1);
    printf("GMT: %s\n",   sstd::time2str(c_time_yday).c_str());
    struct tm c_tm_yday = sstd::yday2tm(c_tm.tm_year+1900, c_tm.tm_yday+1);
    printf("GMT: %s\n",   sstd::tm2str(c_tm_yday).c_str());
    printf("\n");

    struct timeval time_sec_micro = sstd::getTimeval();
    printf("timeval: %lf\n",(time_sec_micro.tv_sec)+(time_sec_micro.tv_usec*1.0E-6));

    sstd::print(c_tm_yday);
    sstd::printn(c_tm_yday);
    sstd::printn_all(c_tm_yday);
}
void TEST_typeDef(){
    printf("■ typeDef\n");
    uchar   uc =  1; printf("uchar:  %u\n",     uc);
    uint    ui =  2; printf("uint:   %u\n",     ui);
    uint8   u8 =  8; printf("uint8:  %u\n",     u8);
    uint16 u16 = 16; printf("uint16: %u\n",    u16);
    uint32 u32 = 32; printf("uint32: %u\n",    u32);
    uint64 u64 = 64; printf("uint64: %lu\n\n", u64);
}
void TEST_pdbg(){
    printf("■ #define DEBUG\n");
    printf("  □ pdbg (printf debugger)\n");
    sstd::pdbg("abc\n");
    printf("true: "); sstd::pdbg_if(true, "print txt"); printf("\n");
    printf("false: "); sstd::pdbg_if(false, "not print txt"); printf("\n");
//    printf("true: "); sstd::pdbg_if_exit(true, "exit");
    printf("false: "); sstd::pdbg_if_exit(false, "not exit"); printf("\n");
//    printf("true: "); sstd::pdbg_if_stop_exit(true, "exit"); printf("\n");
//    printf("false: "); sstd::pdbg_if_stop_exit(false, "not exit"); printf("\n");
    sstd::dbg(printf("run debug code."););
    sstd::ndbg(printf("run ndebug code."););
    printf("\n");
}
void TEST_signal(){
    printf("■ generate signal\n");
    double freq2generate = 3; // Hz
    double freq2sample = 10;  // Hz
    uint len=10;              // 10 Hz 10 sample = 1 sec
    std::vector<double> sin_wave = sstd::sinWave(freq2generate, freq2sample, len);
    std::vector<double> cos_wave = sstd::cosWave(freq2generate, freq2sample, len);
}
//*/
/*
void TEST_file(){
    printf("■ fopen\n");
    
    {
        sstd::file fp;
        const char* fileName = "./test_fopen.txt";

        if(!fp.fopen(fileName, "wb")){ // Enable to open file by the same code between MSVC++ and GCC.
            // falied
            printf("false\n\n");
        }else{
            // success
            printf("test_fopen.txt was made.\n\n");
            std::string buf="abc";
            fp.fwrite(buf.c_str(), 1, buf.size());
        }
    }

    {
        sstd::file fp;
        if(!fp.fopen(std::string("./test_fopen_std_string.txt"), "wb")){ // Enable to open file by the same code between MSVC++ and GCC.
        }
    }
}
void TEST_file_c(){
    // $ sha512sum ./test/test.png
    // 021c3d7da0cedd5aa780ca765f9071f210ed3e19db3c08ee74aa6531aaf6552c3daaa8d0f30abeb10a30793bffbb86d39e3b019b865d54c2793dbd3b62c243e6  ./test/test.png

    const char* pFilePath_c = "./test_file_c.png";
    {
        const char* pFilePath = "./test/test.png";
        std::vector<uint8> data = sstd::readAll_bin(pFilePath);
        
        sstd::file_c fp_c;
        if(!fp_c.fopen_wbp(pFilePath_c)){ sstd::pdbg("ERROR: sstd::file_c::fopen_wbp(%s) was failed.\n", pFilePath); return; }
        if(!fp_c.fwriteAll(data)       ){ sstd::pdbg("ERROR: sstd::file_c::fwriteAll(%s) was failed.\n", pFilePath); return; }
    }
    
    const char* pFilePath_c2f = "./test_file_c2f.png";
    {
        std::vector<uint8> data;
        
        sstd::file_c fp_c;
        if(!fp_c.fopen_rbp(pFilePath_c)){ sstd::pdbg("ERROR: sstd::file_c::fopen_rbp(%s) was failed.\n", pFilePath_c); return; }
        if(!fp_c.freadAll (data)       ){ sstd::pdbg("ERROR: sstd::file_c::freadAll() was failed.\n"); return; }

        if(!sstd::writeAll_bin(pFilePath_c2f, data)){ sstd::pdbg("ERROR: sstd::fwriteAll(%s) was failed.\n", pFilePath_c2f); return; }
    }
}
void TEST_mkdir(){
    printf("■ mkdir\n\n");
    sstd::mkdir("./test_mkdir/abc/def"); // enable to make multilayer directory by one step.
    sstd::mkdir(std::string("./test_mkdir/abc/def")); // enable to make multilayer directory by one step.
}
void TEST_rm(){
    printf("■ rm\n");
    printf("  □ unlink\n");
    { sstd::file fp; fp.fopen("./unlink.txt", "w"); }
    sstd::printn(sstd::unlink("./unlink.txt"));
    printf("\n");

    printf("  □ rmdir\n");
    sstd::mkdir("./test_rmdir");
    sstd::printn(sstd::rmdir("./test_rmdir"));
    printf("\n");
    
    sstd::mkdir("./test_rm/abc/def");
    sstd::mkdir("./test_rm/abc2/def");
    { sstd::file fp; fp.fopen("./test_rm/abc/def/abc.txt", "w"); }
    { sstd::file fp; fp.fopen("./test_rm/abc/abc.txt",     "w"); }
    { sstd::file fp; fp.fopen("./test_rm/abc/xxx",         "w"); }
    { sstd::file fp; fp.fopen("./test_rm/abc2/xxx",        "w"); }
    { sstd::file fp; fp.fopen("./test_rm/123.txt",         "w"); }
    
    printf("  □ getAllInDir\n");
    std::vector<struct sstd::pathAndType> ret;
    sstd::printn(sstd::getAllPath(ret, "./test_rm"));
    for(uint i=0; i<ret.size(); i++){
        if      (ret[i].type=='f'){ sstd::printn(sstd::ssprintf("type: file,      path: %s", ret[i].path.c_str()));
        }else if(ret[i].type=='d'){ sstd::printn(sstd::ssprintf("type: directory, path: %s", ret[i].path.c_str()));
        }          else           { sstd::pdbg("ERROR: sstd::getAllInDir() is failed.\n"); }
    }
    printf("\n");
    
    std::vector<std::string> retStr;
    sstd::printn(sstd::getAllPath(retStr, "./test_rm")); sstd::printn(retStr); printf("\n");
    sstd::printn(sstd::getAllFile(retStr, "./test_rm")); sstd::printn(retStr); printf("\n");
    sstd::printn(sstd::getAllDir (retStr, "./test_rm")); sstd::printn(retStr); printf("\n");
    printf("\n");
    
    printf("  □ rm\n");
    sstd::printn(sstd::rm("./test_rm")); // enable to delete not empty directory by one step.
}
void TEST_str2num(){
    std::string str = "1.5";
    sstd::printn(sstd::str2double(str));
    sstd::printn(sstd::str2int(str));
}
void TEST_ssprintf(){
    printf("■ ssprintf(const char* format, ...)\n");
    printf("%s", sstd::ssprintf("Num: %d, Str: %s\n\n", 1234, "abcd").c_str());
}
void TEST_strmatch(){
    printf("■ strmatch\n");
    const char* str = "abcdefghijk"; // str: 比較する文字列
    const char* WildCard1 = "abc*";
    const char* WildCard2 = "a?cdefghijk";
    const char* WildCard3 = "a?";
    printf("if(\"%s\" == \"%s\") -> %s\n", str, WildCard1, sstd::strmatch(str, WildCard1)?"true":"false");
    printf("if(\"%s\" == \"%s\") -> %s\n", str, WildCard2, sstd::strmatch(str, WildCard2)?"true":"false");
    printf("if(\"%s\" == \"%s\") -> %s\n", str, WildCard3, sstd::strmatch(str, WildCard3)?"true":"false");
    printf("\n");
    printf("■ strmatch_getWC\n");
    bool tf; std::string retWC;
    tf = sstd::strmatch_getWC(str, WildCard1, retWC); printf("if(\"%s\" == \"%s\") -> %s, retWC: %s\n", str, WildCard1, tf?"true":"false", retWC.c_str());
    tf = sstd::strmatch_getWC(str, WildCard2, retWC); printf("if(\"%s\" == \"%s\") -> %s, retWC: %s\n", str, WildCard2, tf?"true":"false", retWC.c_str());
    tf = sstd::strmatch_getWC(str, WildCard3, retWC); printf("if(\"%s\" == \"%s\") -> %s, retWC: %s\n", str, WildCard3, tf?"true":"false", retWC.c_str());
    printf("\n");

    printf("  □ isNum, isAlphabet\n");
    printf("    isNum               ('%c') -> %s\n", '0', sstd::isNum               ('0')?"true":"false");
    printf("    isAlphabet          ('%c') -> %s\n", 'a', sstd::isAlphabet          ('a')?"true":"false");
    printf("    isAlphabet_onlyUpper('%c') -> %s\n", 'A', sstd::isAlphabet_onlyUpper('A')?"true":"false");
    printf("    isAlphabet_onlyLower('%c') -> %s\n", 'a', sstd::isAlphabet_onlyLower('a')?"true":"false");
    printf("\n");
}
//*/

/*
void TEST_path(){
    printf("■ path\n"); // <- 不足する関数を追加する必要がある．
    
    const char* pPath="./abc/def/text.abc.txt\0";
    
    printf("Input pPath: %s\n", pPath);
    printf("Output getPath: %s\n",                     sstd::getPath                     (pPath).c_str());
    printf("Output getFileName: %s\n",                 sstd::getFileName                 (pPath)        );
    printf("Output getFileNameWithoutExtension: %s\n", sstd::getFileName_withoutExtension(pPath).c_str());
    printf("Output getFileExtension: %s\n",            sstd::getExtension                (pPath)        );
    printf("\n");

    sstd::printn(sstd::parsePath(R"(C:\a\b)"));
    sstd::printn(sstd::parsePath(R"(/a/b)"));
    sstd::printn(sstd::parsePath(R"(./a/b)"));
    sstd::printn(sstd::parsePath(R"(../a/b)"));
    sstd::printn(sstd::parsePath(R"(../a/b/)"));
    sstd::printn(sstd::parsePath(R"(a/b/)"));
    printf("\n");

    sstd::printn(sstd::parsePath_withBase(R"(C:\a\b)"));
    sstd::printn(sstd::parsePath_withBase(R"(/a/b)"));
    sstd::printn(sstd::parsePath_withBase(R"(./a/b)"));
    sstd::printn(sstd::parsePath_withBase(R"(../a/b)"));
    sstd::printn(sstd::parsePath_withBase(R"(../a/b/)"));
    sstd::printn(sstd::parsePath_withBase(R"(a/b/)"));
    printf("\n");
    
    printf("  □ isFile\n");
    sstd::printn(sstd::isFile("./main.cpp"));
    sstd::printn(sstd::isFile("./notExist"));
    sstd::printn(sstd::isFile("./sstd"));
    printf("\n");
    
    printf("  □ isDir\n");
    sstd::printn(sstd::isDir("./main.cpp"));
    sstd::printn(sstd::isDir("./notExist"));
    sstd::printn(sstd::isDir("./sstd"));
    printf("\n");
    
    printf("  □ file exist\n");
    sstd::printn(sstd::fileExist("./main.cpp"));
    sstd::printn(sstd::fileExist("./notExist"));
    sstd::printn(sstd::fileExist("./sstd"));
    printf("\n");
    
    printf("  □ dir exist\n");
    sstd::printn(sstd::dirExist("./main.cpp"));
    sstd::printn(sstd::dirExist("./notExist"));
    sstd::printn(sstd::dirExist("./sstd"));
    printf("\n");
    
    printf("  □ path exist\n");
    sstd::printn(sstd::pathExist("./main.cpp"));
    sstd::printn(sstd::pathExist("./notExist"));
    sstd::printn(sstd::pathExist("./sstd"));
    printf("\n");
}
//*/

/*
void TEST_tinyInterpreter(){
    printf("■ tinyInterpreter\n");
    printf("  □ getCommandList & splitByComma\n");
    std::vector<std::string> cmdList = sstd::getCommandList(R"(./test/tinyInterpreter.txt)");
    for(uint i=0; i<cmdList.size(); i++){
        std::vector<std::string> splitCList = sstd::splitByComma(cmdList[i]);
        for(uint n=0; n<splitCList.size(); n++){ printf("[%5s] ", splitCList[n].c_str()); } printf("\n");
    }
    printf("\n");
}
//*/

/*
void TEST_encode_decode(){
    printf("■ encode_decode\n");
    
    //===

    printf("  □ base64_encode\n");
    std::string str_b64  = "#include \"./sstd/sstd.hpp\".+=ABCD";
    printf("    %s ->[base64 encode]-> %s\n", str_b64.c_str(), sstd::base64_encode((uchar*)str_b64.c_str(), str_b64.size()).c_str());
    printf("    %s ->[base64 encode]-> %s\n", str_b64.c_str(), sstd::base64_encode(str_b64).c_str());
    printf("    %s ->[base64 encode]-> %s\n", str_b64.c_str(), sstd::base64_encode(str_b64).c_str());

    printf("  □ base64_decode\n");
    std::string str_b64e = sstd::base64_encode(str_b64);
    printf("    %s ->[base64 decode]-> %s\n", str_b64e.c_str(), sstd::base64_decode((uchar*)str_b64e.c_str(), str_b64e.size()).c_str());
    printf("    %s ->[base64 decode]-> %s\n", str_b64e.c_str(), sstd::base64_decode(str_b64e.c_str()).c_str());
    printf("    %s ->[base64 decode]-> %s\n", str_b64e.c_str(), sstd::base64_decode(str_b64e).c_str());

    printf("  □ make_base64_decode_table\n");
    sstd::print_base64_decode_table(); // for developers
    printf("\n");

    //===

    printf("  □ url_encode\n");
    std::string str_url(256, 0); for(uint i=0; i<str_url.size(); i++){ str_url[i]=i; }
    printf("    [url encode]-> %s\n", sstd::url_encode(str_url.c_str(), str_url.size()).c_str());
    printf("    [url encode]-> %s\n", sstd::url_encode(str_url.c_str()).c_str()); // 先頭が 0 なので、終端だと判断されている。
    printf("    [url encode]-> %s\n", sstd::url_encode(str_url).c_str());
    printf("\n");

    sstd::url_encode_compare_speed(); // for developers
    printf("\n");
    
    printf("  □ url_decode\n");
    std::string str_url_d = sstd::url_encode("#include \"./sstd/sstd.hpp\".+=ABCD");
    printf("    %s ->[url encode]-> %s\n", "#include \"./sstd/sstd.hpp\".+=ABCD", str_url_d.c_str());
    printf("    %s ->[url decode]-> %s\n", str_url_d.c_str(), sstd::url_decode(str_url_d.c_str(), str_url_d.size()).c_str());
    printf("    %s ->[url decode]-> %s\n", str_url_d.c_str(), sstd::url_decode(str_url_d.c_str()).c_str());
    printf("    %s ->[url decode]-> %s\n", str_url_d.c_str(), sstd::url_decode(str_url_d).c_str());
    printf("\n");
    
    printf("  □ make_url_decode_table\n");
    sstd::print_url_decode_table();
    printf("\n");

    //===

    printf("■ utf8 <-> utf16\n");
    printf("  □ unicode escape (utf16) -> utf16 (binary)\n");
    std::string escaped_utf16 = R"(\u30e6\u30cb\u30b3\u30fc\u30c9)"; // "ユニコード"
//    std::string escaped_utf16 = R"(abcd_\u30e6\u30cb\u30b3\u30fc\u30c9)"; // "abcd_ユニコード" // <- これがバグる。 issue
    std::u16string utf16_bin = sstd::unicodeEscape_decode(escaped_utf16);
    for(uint i=0; i<utf16_bin.size(); i++){ printf("%X\n", utf16_bin[i]); }
    
    printf("  □ utf16 (binary) -> utf8\n");
    std::string utf8 = sstd::utf16_to_utf8(utf16_bin);
    printf("%s\n", utf8.c_str());

    std::u32string utf32_bin = sstd::utf8_to_utf32(utf8);
    std::u16string utf16_bin2 = sstd::utf32_to_utf16(utf32_bin);

    printf("  □ utf16 (binary) -> unicode escape (utf16)\n");
    printf("%s\n", sstd::unicodeEscape_encode(utf16_bin2).c_str());

    sstd::unicodeEscape_compare_speed(); // for developers
    printf("\n");

    printf("  □ make_unicodeEscape_decode_table\n");
    sstd::print_unicodeEscape_decode_table();
    printf("\n");
}
//*/

/*
void print_vecUint8_hex(std::vector<uint8>& rhs){ for(uint i=0; i<rhs.size(); i++){ printf("%.2x", rhs[i]); } printf("\n"); }
void TEST_hashFnc(){
    
    const char* pFilePath = "./test/test.png";
    std::vector<uint8> data = sstd::readAll_bin(pFilePath);
    
    printf("fnc_MD5   ( %s ) = ", pFilePath); { std::vector<uint8> hash = sstd::md5   (data); print_vecUint8_hex(hash); }
    printf("fnc_SHA1  ( %s ) = ", pFilePath); { std::vector<uint8> hash = sstd::sha1  (data); print_vecUint8_hex(hash); }
    printf("fnc_SHA224( %s ) = ", pFilePath); { std::vector<uint8> hash = sstd::sha224(data); print_vecUint8_hex(hash); }
    printf("fnc_SHA256( %s ) = ", pFilePath); { std::vector<uint8> hash = sstd::sha256(data); print_vecUint8_hex(hash); }
    printf("fnc_SHA384( %s ) = ", pFilePath); { std::vector<uint8> hash = sstd::sha384(data); print_vecUint8_hex(hash); }
    printf("fnc_SHA512( %s ) = ", pFilePath); { std::vector<uint8> hash = sstd::sha512(data); print_vecUint8_hex(hash); }
}
//*/
// --- hash calculation by command ---
//
// $ md5sum ./test/test.png
// 80764a9c59629dca04ee00c125726a01  ./test/test.png
//
// $ sha1sum ./test/test.png
// 3361cc4368ae3369f3f115df78d186a887ee8b46  ./test/test.png
//
// $ sha224sum ./test/test.png
// b5d2e3bface35276977ededd5941b52c0547ba4aa63a9571a9a81ac7  ./test/test.png
//
// $ sha256sum ./test/test.png
// 58aeaf1a74a46e37bad7d2161d629537440df5e2fcb0ee97837209335cf1fee7  ./test/test.png
//
// $ sha384sum ./test/test.png
// bbc9239c8266ab4b86b7b9435d1ade6f7c47af11ffac78dbb5cdcbe15c3fdaf96e9e720e2c2fa14178d96304ec8185ef  ./test/test.png
//
// $ sha512sum ./test/test.png
// 021c3d7da0cedd5aa780ca765f9071f210ed3e19db3c08ee74aa6531aaf6552c3daaa8d0f30abeb10a30793bffbb86d39e3b019b865d54c2793dbd3b62c243e6  ./test/test.png


/*
void TEST_pause(){
//    printf("■ #define UsePause\n");
    sstd::pause();
//    printf("■ #define UsePauseIfWin32\n");
    sstd::pauseIfWin32(); // win32 の場合のみ停止
//    printf("\n");
}
//*/
//-----------------------------------------------------------------------
/*
void TEST_mat_colMajor(){
    printf("== sstd_src_MatrixStore_mat ==\n\n"); // col-major
    
    printf("■ Init sstd::eye()\n");
    { sstd::mat_c<double> buf(3, 3); sstd::eye(buf); sstd::printn(buf); printf("\n"); }
    { sstd::mat_c<double> buf(3, 2); sstd::eye(buf); sstd::printn(buf); printf("\n"); }
    { sstd::mat_c<double> buf(2, 3); sstd::eye(buf); sstd::printn(buf); printf("\n"); }
        
    printf("■ Init sstd::ones()\n");
    { sstd::mat_c<double> buf(3, 3); sstd::ones(buf); sstd::printn(buf); printf("\n"); }
    { sstd::mat_c<double> buf(3, 2); sstd::ones(buf); sstd::printn(buf); printf("\n"); }
    { sstd::mat_c<double> buf(2, 3); sstd::ones(buf); sstd::printn(buf); printf("\n"); }
        
    printf("■ Init sstd::zeros()\n");
    { sstd::mat_c<double> buf(3, 3); sstd::zeros(buf); sstd::printn(buf); printf("\n"); }
    { sstd::mat_c<double> buf(3, 2); sstd::zeros(buf); sstd::printn(buf); printf("\n"); }
    { sstd::mat_c<double> buf(2, 3); sstd::zeros(buf); sstd::printn(buf); printf("\n"); }

    printf("■ Init sstd::mat_c<type> by \"std::initializer_list<T>\"\n");
    printf("\n");
    
    sstd::mat_c<double> matD_initializer{{1, 2, 3},{4, 5, 6},{7, 8, 9},{10, 11, 12}}; // これは，sstd::mat_c<T> 側にもテストを書くように．
    sstd::printn(matD_initializer);
    printf("\n");
    
    //===
    
    printf("■ Init sstd::mat_c<type>\n");
    printf("\n");
    
    sstd::mat_c<double> Matd(5, 3);
    printf("RowSize: %d\n", Matd.rows());
    printf("ColSize: %d\n", Matd.cols());
    printf("Length:  %d\n", Matd.size());

    printf("Indication of column major\n");
    uint i=0;
    for(uint q=0; q<Matd.cols(); q++){
        for(uint p=0; p<Matd.rows(); p++){
            Matd(p, q) = i; i++;
        }
    }
    sstd::print(Matd);
    printf("\n");
    
    //===
    
    i=0;
    for(uint q=0; q<Matd.size(); q++){ Matd[i] = i; i++; }
    sstd::print(Matd);
    printf("\n");

    //===
    
    sstd::mat_c<double>* pMatd = new sstd::mat_c<double>(5, 3);
    printf("RowSize: %d\n", pMatd->rows());
    printf("ColSize: %d\n", pMatd->cols());
    printf("Length:  %d\n", pMatd->size());

    printf("Indication of column major\n");
    i=0;
    for(uint q=0; q<pMatd->cols(); q++){
        for(uint p=0; p<pMatd->rows(); p++){
            (*pMatd)(p, q) = i; i++;
        }
    }

    sstd::print(*pMatd);
    printf("\n");
    delete pMatd;
    
    //===

    printf("■ copy\n");printf("\n");
    sstd::mat_c<double> Matd_copy = Matd;
    Matd_copy = Matd; // "sstd::copy(Matd_copy, Matd);" is called.
    sstd::print(Matd_copy); printf("\n");

    //===

    printf("■ copy row\n");printf("\n");
    sstd::mat_c<double> Matd_rowCopy(5, 3); sstd::zeros(Matd_rowCopy);
    Matd_rowCopy(1, ':') = Matd(1, ':');
    sstd::print(Matd_rowCopy); printf("\n");
    
    printf("■ copy col\n");printf("\n");
    sstd::mat_c<double> Matd_colCopy(5, 3); sstd::zeros(Matd_colCopy);
    Matd_colCopy(':', 2) = Matd(':', 2);
    sstd::print(Matd_colCopy); printf("\n");

    //===
    sstd::printn(Matd_colCopy); printf("\n");
    sstd::printn_all(Matd_colCopy); printf("\n");

    //===
    
    printf("■ print(type& rhs)\n");printf("\n");
    sstd::mat_c<bool> matB{{true, false, false},{false, true, false},{false, false, true},{true, false, false}};
    sstd::printn(matB);

    printf("■ print(type& rhs)\n");printf("\n");
    sstd::mat_c<std::string> matStr{{"a", "ab", "abc"},{"abcd", "abcde", "abcdef"},{"7", "8", "9"},{"10", "11", "12"}};
    sstd::printn(matStr);
    
    //===

    printf("■ Operators for linearAlgebra\n");printf("\n");
    {
        // このあたりは順次テストを書くこと
        
        sstd::mat_c<double> lhs={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
        sstd::mat_c<double> rhs={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
        
        sstd::mat_c<double> lhs23={{1,2,3}, {4, 5, 6}};
        sstd::mat_c<double> rhs32={{1,2}, {3, 4}, {5, 6}};
        
        sstd::mat_c<int> lhsInt={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
        sstd::mat_c<int> rhsInt={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
        
        printf("  □ plus\n");printf("\n");
        sstd::printn(lhs+rhs); printf("\n");
        sstd::printn(lhs+(uint)1); printf("\n");
        sstd::printn((uint)1+lhs); printf("\n");
        
        sstd::printn(lhs+(int)-1); printf("\n");
        sstd::printn((int)-1+lhs); printf("\n");
        
        printf("  □ minus\n");printf("\n");
        sstd::printn(lhs-rhs); printf("\n");
        
        sstd::printn(lhs-(int)1); printf("\n");
        sstd::printn((int)1-lhs); printf("\n");
        
        printf("  □ multiplication\n");printf("\n");
        sstd::printn(lhs*rhs); printf("\n");
        sstd::printn(lhs23*rhs32); printf("\n");
        sstd::printn(lhs23*(uint)2); printf("\n");
        sstd::printn((uint)2*lhs23); printf("\n");
        
        sstd::printn(lhs()*rhs()); printf("\n");
        sstd::printn(lhs  *rhs()); printf("\n");
        sstd::printn(lhs()*rhs  ); printf("\n");
        sstd::printn(lhs.vec()*rhs.vec()); printf("\n");
        
        printf("  □ division\n");printf("\n");
        sstd::printn(lhs()/rhs()); printf("\n");
        sstd::printn(lhs  /rhs()); printf("\n");
        sstd::printn(lhs()/rhs  ); printf("\n");

        printf("  □ power\n");printf("\n");
        sstd::printn(lhs^(uint32)0); printf("\n");
        sstd::printn(lhs^(uint32)1); printf("\n");
        sstd::printn(lhs^(uint32)2); printf("\n");
        sstd::printn(lhs*lhs); printf("\n");
        sstd::printn(lhs^(uint32)3); printf("\n");
        sstd::printn(lhs*lhs*lhs); printf("\n");

        
        sstd::printn(lhs^(int32)3); printf("\n");
        
        sstd::printn(lhs()^rhs()); printf("\n");
        sstd::printn(lhs  ^rhs()); printf("\n");
        sstd::printn(lhs()^rhs  ); printf("\n");
        
        // 未実装
        //sstd::printn(lhs^(int32)-1); printf("\n");
        //sstd::printn(lhs^(float)-1); printf("\n");
        //sstd::printn(lhs^(double)-1); printf("\n");
        
        printf("  □ modulo\n");printf("\n");
        sstd::printn(lhsInt % 2); printf("\n");
        
        sstd::printn(lhsInt()%rhsInt()); printf("\n");
        sstd::printn(lhsInt  %rhsInt()); printf("\n");
        sstd::printn(lhsInt()%rhsInt  ); printf("\n");
    }
}
//*/
/*
// 実装完了 (処理時間短縮のため，コメントアウト)

TEST(c2py, mat_ope_eq_ne){
    // sstd::mat_c (col-major)
    
    sstd::mat_c<double> matIn(5, 3);
    sstd::mat_c<double> ansT0(5, 3);
    sstd::mat_c<double> ansF0(5, 3);
    sstd::mat_c<double> ansF1(3, 5);
    
    for(uint i=0; i<matIn.size(); i++){
        matIn[i]=i;
        ansT0[i]=i;
        ansF0[i]=i;
        ansF1[i]=i;
    }
    ansF0[0]=(double)999;
    
    ASSERT_TRUE (matIn==ansT0);
    ASSERT_FALSE(matIn==ansF0);
    ASSERT_FALSE(matIn==ansF1);
    
    ASSERT_FALSE(matIn!=ansT0);
    ASSERT_TRUE (matIn!=ansF0);
    ASSERT_TRUE (matIn!=ansF1);
}
//*/
//-----------------------------------------------------------------------
/*
void TEST_mat_rowMajor(){
    printf("== sstd_src_MatrixStore_mat_rowMajor ==\n\n");
    
    printf("■ Init sstd::mat_r<type> by \"std::initializer_list<T>\"\n");
    printf("\n");
    
    sstd::mat_r<double> matD_initializer{{1, 2, 3},{4, 5, 6},{7, 8, 9},{10, 11, 12}}; // これは，sstd::mat<T> 側にもテストを書くように．
    sstd::printn(matD_initializer);
    printf("\n");
    
    //===
    
    printf("■ Init sstd::mat_r<type>\n");
    printf("\n");
    
    sstd::mat_r<double> Matd(5, 3);
    printf("RowSize: %d\n", Matd.rows());
    printf("ColSize: %d\n", Matd.cols());
    printf("Length:  %d\n", Matd.size());

    printf("Indication of row major\n");
    uint i=0;
    for(uint p=0; p<Matd.rows(); p++){
        for(uint q=0; q<Matd.cols(); q++){
            Matd(p, q) = i; i++;
        }
    }
    sstd::print(Matd);
    printf("\n");
    
    //===
    
    i=0;
    for(uint q=0; q<Matd.size(); q++){ Matd[i] = i; i++; }
    sstd::print(Matd);
    printf("\n");

    //===
    
    sstd::mat_r<double>* pMatd = new sstd::mat_r<double>(5, 3);
    printf("RowSize: %d\n", pMatd->rows());
    printf("ColSize: %d\n", pMatd->cols());
    printf("Length:  %d\n", pMatd->size());

    printf("Indication of row major\n");
    i=0;
    for(uint p=0; p<pMatd->rows(); p++){
        for(uint q=0; q<pMatd->cols(); q++){
            (*pMatd)(p, q) = i; i++;
        }
    }

    sstd::print(*pMatd);
    printf("\n");
    delete pMatd;
    
    //===

    printf("■ copy\n");printf("\n");
    sstd::mat_r<double> Matd_copy = Matd;
    Matd_copy = Matd; // "sstd::copy(Matd_copy, Matd);" is called.
    sstd::print(Matd_copy); printf("\n");

    //===

    printf("■ copy row\n");printf("\n");
    sstd::mat_r<double> Matd_rowCopy(5, 3); sstd::zeros(Matd_rowCopy);
    Matd_rowCopy(1, ':') = Matd(1, ':');
    sstd::print(Matd_rowCopy); printf("\n");
    
    printf("■ copy col\n");printf("\n");
    sstd::mat_r<double> Matd_colCopy(5, 3); sstd::zeros(Matd_colCopy);
    Matd_colCopy(':', 2) = Matd(':', 2);
    sstd::print(Matd_colCopy); printf("\n");

    //===

    sstd::printn(Matd_colCopy); printf("\n");
    sstd::printn_all(Matd_colCopy); printf("\n");
    
    //===
    
    printf("■ print(type& rhs)\n");printf("\n");
    sstd::mat_r<bool> mat_rB{{true, false, false},{false, true, false},{false, false, true},{true, false, false}};
    sstd::printn(mat_rB);
    
    printf("■ print(type& rhs)\n");printf("\n");
    sstd::mat_r<std::string> mat_rStr{{"a", "ab", "abc"},{"abcd", "abcde", "abcdef"},{"7", "8", "9"},{"10", "11", "12"}};
    sstd::printn(mat_rStr);
    
    //===

    printf("■ Operators for linearAlgebra\n");printf("\n");
    {
        // このあたりは順次テストを書くこと
        
        sstd::mat_r<double> lhs={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
        sstd::mat_r<double> rhs={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
        
        sstd::mat_r<double> lhs23={{1,2,3}, {4, 5, 6}};
        sstd::mat_r<double> rhs32={{1,2}, {3, 4}, {5, 6}};
        
        sstd::mat_r<int> lhsInt={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
        sstd::mat_r<int> rhsInt={{1,2,3}, {4, 5, 6}, {7, 8, 9}};
        
        printf("  □ plus\n");printf("\n");
        sstd::printn(lhs+rhs); printf("\n");
        sstd::printn(lhs+(uint)1); printf("\n");
        sstd::printn((uint)1+lhs); printf("\n");
        
        sstd::printn(lhs+(int)-1); printf("\n");
        sstd::printn((int)-1+lhs); printf("\n");
        
        printf("  □ minus\n");printf("\n");
        sstd::printn(lhs-rhs); printf("\n");
        
        sstd::printn(lhs-(int)1); printf("\n");
        sstd::printn((int)1-lhs); printf("\n");
        
        printf("  □ multiplication\n");printf("\n");
        sstd::printn(lhs*rhs); printf("\n");
        sstd::printn(lhs23*rhs32); printf("\n");
        sstd::printn(lhs23*(uint)2); printf("\n");
        sstd::printn((uint)2*lhs23); printf("\n");
        
        sstd::printn(lhs()*rhs()); printf("\n");
        sstd::printn(lhs  *rhs()); printf("\n");
        sstd::printn(lhs()*rhs  ); printf("\n");
        sstd::printn(lhs.vec()*rhs.vec()); printf("\n");
        
        printf("  □ division\n");printf("\n");
        sstd::printn(lhs()/rhs()); printf("\n");
        sstd::printn(lhs  /rhs()); printf("\n");
        sstd::printn(lhs()/rhs  ); printf("\n");
        
        printf("  □ power\n");printf("\n");
        sstd::printn(lhs^(uint32)0); printf("\n");
        sstd::printn(lhs^(uint32)1); printf("\n");
        sstd::printn(lhs^(uint32)2); printf("\n");
        sstd::printn(lhs*lhs); printf("\n");
        sstd::printn(lhs^(uint32)3); printf("\n");
        sstd::printn(lhs*lhs*lhs); printf("\n");

        
        sstd::printn(lhs^(int32)3); printf("\n");
        
        sstd::printn(lhs()^rhs()); printf("\n");
        sstd::printn(lhs  ^rhs()); printf("\n");
        sstd::printn(lhs()^rhs  ); printf("\n");
        
        // 未実装
        //sstd::printn(lhs^(int32)-1); printf("\n");
        //sstd::printn(lhs^(float)-1); printf("\n");
        //sstd::printn(lhs^(double)-1); printf("\n");
        
        printf("  □ modulo\n");printf("\n");
        sstd::printn(lhsInt % 2); printf("\n");
        
        sstd::printn(lhsInt()%rhsInt()); printf("\n");
        sstd::printn(lhsInt  %rhsInt()); printf("\n");
        sstd::printn(lhsInt()%rhsInt  ); printf("\n");
    }
}
//*/
/*
// 実装完了 (処理時間短縮のため，コメントアウト)

TEST(c2py, mat_r_ope_eq_ne){
    // sstd::mat (col-major)
    
    sstd::mat_r<double> matIn(5, 3);
    sstd::mat_r<double> ansT0(5, 3);
    sstd::mat_r<double> ansF0(5, 3);
    sstd::mat_r<double> ansF1(3, 5);
    
    for(uint i=0; i<matIn.size(); i++){
        matIn[i]=i;
        ansT0[i]=i;
        ansF0[i]=i;
        ansF1[i]=i;
    }
    ansF0[0]=(double)999;
    
    ASSERT_TRUE (matIn==ansT0);
    ASSERT_FALSE(matIn==ansF0);
    ASSERT_FALSE(matIn==ansF1);
    
    ASSERT_FALSE(matIn!=ansT0);
    ASSERT_TRUE (matIn!=ansF0);
    ASSERT_TRUE (matIn!=ansF1);
}
//*/

//-----------------------------------------------------------------------
/*
void TEST_bmat(){
    // init test
    sstd::bmat bMat4x4(4, 4);
    sstd::eye(bMat4x4);   sstd::printn(bMat4x4);
    sstd::ones(bMat4x4);  sstd::printn(bMat4x4);
    sstd::zeros(bMat4x4); sstd::printn(bMat4x4);
    sstd::print(bMat4x4);     // for print debug
    sstd::print_all(bMat4x4); // for bmat debug // Internaly, the bit matrix is processed as a set of 8x8 matrices.
    //

    sstd::bmat bonded8x8 = sstd::zeros(4, 4) << sstd::eye(4, 4) &&
                           sstd::ones (4, 4) << sstd::eye(4, 4);
    sstd::printn(bonded8x8);

    sstd::bmat bonded8x8_2 = sstd::zeros(5, 5) << sstd::eye(3, 3) &&
                             sstd::ones (3, 5) << sstd::eye(3, 3);
    sstd::printn(bonded8x8_2);
    
    sstd::bmat bonded16x16_horzcat2_2 = sstd::ones(16, 16) << sstd::eye(16, 16);
    sstd::printn(bonded16x16_horzcat2_2);
    
    sstd::bmat bonded16x16_vertcat2_2 = sstd::ones(16, 16) &&
                                        sstd::eye (16, 16);
    sstd::printn(bonded16x16_vertcat2_2);
    
    sstd::bmat bonded16x16 = sstd::zeros(16, 16) << sstd::eye(16, 16) &&
                             sstd::ones (16, 16) << sstd::eye(16, 16);
    sstd::printn(bonded16x16);
    
    //
    sstd::bmat bMat8x9 = sstd::eye(8, 9);
    sstd::printn(bMat8x9);
    sstd::print_all(bMat8x9); // for debug // Internaly, the bit matrix is processed as a set of 8x8 matrices.

    sstd::printn(bMat8x9.rows());
    sstd::printn(bMat8x9.cols());
    printf("\n");

    // access to elements
    sstd::bmat M = sstd::zeros(4, 4);
    M(0, 1) = 1;
    M(1, 2) = 1;
    M(2, 3) = 1;
    M(3, 4) = 1;
    sstd::printn(M);
    sstd::printn(M*M); // multi

    // tranpose
    sstd:: bmat M_tr = M; // copy
    sstd::Tr_myself(M_tr);
    sstd::printn(M_tr);
    sstd::printn(sstd::Tr(M));

    // pow test
    sstd::bmat L1 = sstd::LxShiftMat(16, 1);
    sstd::printn(L1);
    sstd::bmat L7 = L1^((uint64)7); // この計算は後で確認して！！！
    sstd::printn(L7);

    uint N = 32;
    sstd::bmat I(N, N); sstd::eye(I);
    sstd::bmat L15 = sstd::LxShiftMat(N, 15);
    sstd::bmat R17 = sstd::RxShiftMat(N, 17);
    sstd::bmat L13 = sstd::LxShiftMat(N, 13);
    sstd::bmat T = (I + L15)*(I + R17)*(I + L13);
    sstd::printn(T);
    sstd::bmat Tp = T^(4294967296-1); // XORSHIFT
    sstd::printn(Tp);
    
    printf("Tp==I: "); if(Tp==I){ printf("true\n");  }else{ printf("false\n"); }
    printf("Tp!=I: "); if(Tp!=I){ printf("true\n");  }else{ printf("false\n"); }

    printf("I(0, 0): "); if(I(0, 0)){printf("true\n");}else{printf("false\n");}
    printf("I(1, 0): "); if(I(1, 0)){printf("true\n");}else{printf("false\n");}
    printf("I(0, 1): "); if(I(0, 1)){printf("true\n");}else{printf("false\n");}
    printf("I(1, 1): "); if(I(1, 1)){printf("true\n");}else{printf("false\n");}

    I = sstd::eye(4, 4);
    sstd::printn(I);
    I(0, 0) = false;
    I(1, 1) = false;
    I(0, 1) = 1;
    I(0, 2) = 1000;    // "I(0, 2) = 1000;" に同じ．

//    I(1, 0) = I(2, 0) = I(2, 2);
    I(1, 0) = I(2, 0) = I(2, 2) = true;

    sstd::printn(I);

    sstd::printn(I);
    I[0] = false;
    I[1] = true;

    I[2] = I[3] = I[15];
    I[4] = I[5] = true;

    I[6] = I[7] = I(2, 2);
    I(2, 2) = I[0];

    sstd::printn(I);
}//*/


/*
#Include "./MatrixStore/Core/MatrixStore.hpp"


int main(){

    mxs::MatrixStore<double> MatA(3, 3); mxs::zeros(MatA);
    mxs::MatrixStore<double> MatB(3, 3); mxs::zeros(MatB);

    for(uint q=0; q<MatA.cols; q++){
        for(uint p=0; p<MatA.rows; p++){
            MatA(p, q) = (MatA.cols)*p + q;
        }
    }

    printm(MatA); printf("\n");

    MatB(':', 0) = MatA(':', 1);
//    MatB(':', 1) = MatA(':', 2);
//    MatB(':', 2) = MatA(':', 0);

    printm(MatB); printf("\n");

//    MatB(0, ':') = MatA(0, ':');
    MatB(1, ':') = MatB(0, ':') = MatA(0, ':');
//    MatB(1, ':') = MatA(1, ':');
//    MatB(2, ':') = MatA(2, ':');

    //MatA = MatA.array() * MatB.array();
    // MatA = MatA.a() * MatB.a();
    // MatA = MatA.arr() * MatB;
    // MatA = MatA * MatB.arr();

    // MatA = MatA .* MatB;
    // MatA = MatA ,* MatB;
    // MatA = MatA <dot> MatB;
    // MatA = MatA ("dot")* MatB;
    // MatA = MatA *(dot) MatB;
    // MatA.cols;
    // MatB.rows;

    printm(MatB);
}
*/
