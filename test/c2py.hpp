#pragma once

// c2py means "C++ to Python". (Running any python function from C++.)

//-----------------------------------------------------------------------------------------------------------------------------------------------

//*
// 実装完了 (処理時間短縮のため，コメントアウト)

void TEST__c2py__empty_args(){
    sstd::c2py<void> py_emptyArg("./tmpDir", "test/c2py_t", "py_emptyArg", "void");
    testing::internal::CaptureStdout();
    py_emptyArg();
    ASSERT_STREQ("* * * Welcome to sstd::c2py<T> ! * * *\n", testing::internal::GetCapturedStdout().c_str());
}
void TEST__c2py__empty_args__same_dir(){
    sstd::c2py<void> py_emptyArg("./tmpDir", "./test_c2py", "py_emptyArg", "void");
    testing::internal::CaptureStdout();
    py_emptyArg();
    ASSERT_STREQ("* * * Welcome to sstd::c2py<T> ! * * *\n", testing::internal::GetCapturedStdout().c_str());
}
//---
void TEST__c2py__bench_withoutInit(){
    uint numOfCall = 5;
    time_m timem; sstd::measureTime_start(timem);
    
    sstd::c2py<void> py_empty("./tmpDir", "test/c2py_t", "py_empty", "void");
    for(uint i=0; i<numOfCall; ++i){ py_empty(); }
    
    double sec = sstd::measureTime_stop_s(timem);
    printf("%.2lf [call/sec]\n", (double)numOfCall/sec);
}
void TEST__c2py__bench_withInit(){
    uint numOfCall = 5;
    time_m timem; sstd::measureTime_start(timem);
    
    for(uint i=0; i<numOfCall; ++i){
        sstd::c2py<void> py_empty("./tmpDir", "test/c2py_t", "py_empty", "void");
        py_empty();
    }
    
    double sec = sstd::measureTime_stop_s(timem);
    printf("%.2lf [call/sec]\n", (double)numOfCall/sec);
}//*/

//-----------------------------------------------------------------------

std::string val2str(const bool& rhs){ return sstd::ssprintf("%s", (rhs ? "T" : "F")); }

std::string val2str(const char& rhs){ return sstd::ssprintf("%c", rhs); }

//std::string val2str(const uchar & rhs){ return sstd::ssprintf("%u",   rhs); } // same as uint8
std::string val2str(const  int8 & rhs){ return sstd::ssprintf("%d",    rhs); }
std::string val2str(const  int16& rhs){ return sstd::ssprintf("%d",    rhs); }
std::string val2str(const  int32& rhs){ return sstd::ssprintf("%d",    rhs); }
std::string val2str(const  int64& rhs){ return sstd::ssprintf("%lld",  rhs); }
std::string val2str(const uint8 & rhs){ return sstd::ssprintf("%u",    rhs); } // same as uchar
std::string val2str(const uint16& rhs){ return sstd::ssprintf("%u",    rhs); }
std::string val2str(const uint32& rhs){ return sstd::ssprintf("%u",    rhs); }
std::string val2str(const uint64& rhs){ return sstd::ssprintf("%llu",  rhs); }
std::string val2str(const  float& rhs){ return sstd::ssprintf("%.4f",  rhs); }
std::string val2str(const double& rhs){ return sstd::ssprintf("%.4lf", rhs); }
std::string val2str(const std::string& rhs){ return rhs.c_str(); }

//std::string num2typeNameInPython(const uchar & rhs){ return std::string( "uint8" ); } // same as uint8
std::string num2typeNameInPython(const  int8 & rhs){ return std::string(  "int8" ); }
std::string num2typeNameInPython(const  int16& rhs){ return std::string(  "int16"); }
std::string num2typeNameInPython(const  int32& rhs){ return std::string(  "int32"); }
std::string num2typeNameInPython(const  int64& rhs){ return std::string(  "int64"); }
std::string num2typeNameInPython(const uint8 & rhs){ return std::string( "uint8" ); } // same as uchar
std::string num2typeNameInPython(const uint16& rhs){ return std::string( "uint16"); }
std::string num2typeNameInPython(const uint32& rhs){ return std::string( "uint32"); }
std::string num2typeNameInPython(const uint64& rhs){ return std::string( "uint64"); }
std::string num2typeNameInPython(const  float& rhs){ return std::string("float32"); }
std::string num2typeNameInPython(const double& rhs){ return std::string("float64"); }

template<typename T>
std::string vec2ansStr(const std::vector<T>& vec){
    std::string ans;
    for(uint i=0; i<vec.size(); ++i){
        ans += val2str(vec[i]);
        ans += '\n';
    }
    return ans;
}
template<typename T>
std::string vvec2ansStr(const std::vector<std::vector<T>>& vvec){
    std::string ans;
    
    for(uint v=0; v<vvec.size(); ++v){
        for(uint i=0; i<vvec[v].size(); ++i){
            ans += val2str(vvec[v][i]);
            ans += '\n';
        }
    }
    return ans;
}

template<typename matRC>
std::string mat2ansStr(const matRC& mat){
    std::string ans;
    for(uint row=0; row<mat.rows(); ++row){
        for(uint col=0; col<mat.cols(); ++col){
            ans += val2str( mat(row, col) );
            ans += '\n';
        }
    }
    return ans;
}

template<typename T>
void vec_rm(std::vector<T>& rhs, const uint index){ rhs.erase(rhs.begin() + index); }

//-----------------------------------------------------------------------------------------------------------------------------------------------
//*
// 実装完了 (処理時間短縮のため，コメントアウト)

void TEST__c2py__builIn_bool(){
    
    const char* tmpDir = "./tmpDir";
    const char* fileName = "test/c2py_t";
    
    bool in     = true;
    bool in_inv = !in;
    std::string ans     = val2str(in    ) + "\n";
    std::string ans_inv = val2str(in_inv) + "\n";
    {
        // bool, ret bool*, bool
        sstd::c2py<bool> pyFn(tmpDir, fileName, "py_bool", "bool, ret bool*, bool");
        bool ret=false;
        testing::internal::CaptureStdout();
        ASSERT_TRUE(pyFn(&ret, in)==in); ASSERT_TRUE(ret==(!in));
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        testing::internal::CaptureStdout();
        ASSERT_TRUE(pyFn(&ret, in_inv)==in_inv); ASSERT_TRUE(ret==(!in_inv));
        ASSERT_STREQ(ans_inv.c_str(), testing::internal::GetCapturedStdout().c_str());
    }
    
    uint arrSize = 6;
    const bool c_arrIn    [] = { true, false,  true, false, false,  true}; const bool* arrIn     = &c_arrIn    [0];
    const bool c_arrIn_inv[] = {false,  true, false,  true,  true, false}; const bool* arrIn_inv = &c_arrIn_inv[0];
    
    std::string ans_arr;
    for(uint i=0; i<arrSize; ++i){ ans_arr += val2str(arrIn    [i])+"\n"; }
    for(uint i=0; i<arrSize; ++i){ ans_arr += val2str(arrIn_inv[i])+"\n"; }
    {
        // const bool*
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pBool", "void, const bool*, len"); // Not writing back
        testing::internal::CaptureStdout();
        pyFn(arrIn, arrSize);
        ASSERT_STREQ(ans_arr.c_str(), testing::internal::GetCapturedStdout().c_str());
    }
    {
        // bool*
        bool arrIn_copy[] = {true, false, true, false, false, true}; bool* arrIn_buf = &arrIn_copy[0];
        
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pBool", "void, bool*, len"); // Writing back
        testing::internal::CaptureStdout();
        pyFn(arrIn_buf, arrSize);
        ASSERT_STREQ(ans_arr.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        for(uint i=0; i<arrSize; ++i){ ASSERT_TRUE(arrIn_buf[i]==(!arrIn[i])); }
    }
    //---
    {
        // bool*|~
        bool arrIn_copy[] = {true, false, true, false, false, true}; bool* arrIn_buf = &arrIn_copy[0];
        
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pBool", "void, bool*|~, len"); // Writing back
        testing::internal::CaptureStdout();
        pyFn(arrIn_buf, arrSize);
        ASSERT_STREQ(ans_arr.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        for(uint i=0; i<arrSize; ++i){ ASSERT_TRUE(arrIn_buf[i]==(!arrIn[i])); }
    }
    {
        // bool*|*~
        bool arrIn_copy[] = {true, false, true, false, false, true}; bool* arrIn_buf = &arrIn_copy[0];
        
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pBool_pBuiltin", "void, bool*|*~, len"); // Writing back
        testing::internal::CaptureStdout();
        pyFn(arrIn_buf, arrSize);
        ASSERT_STREQ(ans_arr.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        for(uint i=0; i<arrSize; ++i){ ASSERT_TRUE(arrIn_buf[i]==(!arrIn[i])); }
    }
    //---
    {
        // bool*|*~
        // checking that returning 0 size array will not chrashe.
        bool arrIn_copy[] = {true, false, true, false, false, true}; bool* arrIn_buf = &arrIn_copy[0];
        
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pBool_pBuiltin_clear", "void, bool*|*~, len"); // Writing back
        pyFn(arrIn_buf, arrSize);
    }
}//*/
//-----------------------------------------------------------------------
//*
// 実装完了 (処理時間短縮のため，コメントアウト)

void TEST__c2py__builIn_char(){
    const char* tmpDir = "./tmpDir";
    const char* fileName = "test/c2py_t";
    
    const char in = 'C';
    std::string ans = "C\n";
    {
        // char, ret char*, char
        char in_buf=in;
        char ret='0';
        
        sstd::c2py<char> pyFn(tmpDir, fileName, "py_char", "char, ret char*, char");
        testing::internal::CaptureStdout();
        ASSERT_TRUE(pyFn(&ret, in_buf)==in);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(ret=='W');
    }
    {
        // print run time error
        const char* pErrMsg = "ERROR: \"const char*\": Previous of a len type can't have \"char*\". Because \"char*\" check its length by \"strlen()\" and doesn't need to be send its length.\n";
        // Hard coding a line number of ERROR MESSAGE occur ASSERT when c2py.cpp has been editted.
        // "src/c2py.cpp: format_str2typeSet(236): ERROR: \"const char*\": Previous of a len type can't have \"char*\". Because \"char*\" check its length by \"strlen()\" and doesn't need to be send its length.\n"
        
        testing::internal::CaptureStdout();
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pChar", "void, const char*, len"); // print run time error
        ASSERT_TRUE(sstd::strIn(pErrMsg, testing::internal::GetCapturedStdout().c_str()));
    }
    {
        // const char*
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pChar", "void, const char*"); // Not writing back
        testing::internal::CaptureStdout();
        pyFn("string");
        ASSERT_STREQ("string\n", testing::internal::GetCapturedStdout().c_str());
    }
    {
        // char*
        std::string str_pChar="string";
        char* pChar=&str_pChar[0];
        
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pChar", "void, char*"); // Writing back // Python says [TypeError: 'str' object does not support item assignment] so, this might be impossible.
        testing::internal::CaptureStdout();
        pyFn(pChar);
        ASSERT_STREQ(sstd::ssprintf("%s\n", pChar).c_str(), testing::internal::GetCapturedStdout().c_str());
    }
    //---
    {
        // char*|~
        std::string str_pChar="string";
        char* pChar=&str_pChar[0];
        
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pChar", "void, char*|~"); // Writing back // Python says [TypeError: 'str' object does not support item assignment] so, this might be impossible.
        testing::internal::CaptureStdout();
        pyFn(pChar);
        ASSERT_STREQ(sstd::ssprintf("%s\n", pChar).c_str(), testing::internal::GetCapturedStdout().c_str());
    }
    {
        // char*|*~
        std::string str_pChar="string";
        char* pChar=&str_pChar[0];
        
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pChar_pBuiltin", "void, char*|*~"); // Writing back // Python says [TypeError: 'str' object does not support item assignment] so, this might be impossible.
        pyFn(pChar);
        ASSERT_STREQ("writeX", pChar);
    }
}
//*/
//-----------------------------------------------------------------------
template<typename T>
void builtIn__builtin_and_retPointer(const char* tmpDir,
                                     const char* fileName,
                                     const T in,
                                     const std::string& ans,
                                     const char* fnName,
                                     const char* fmt
                                     )
{
    sstd::c2py<T> pyFn(tmpDir, fileName, fnName, fmt);
    T ret;
    testing::internal::CaptureStdout();
    ASSERT_TRUE(pyFn(&ret, in) == in);
    ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
    ASSERT_TRUE(ret==in);
}
template<typename T>
void builtIn__fmt(const char* tmpDir, const char* fileName, const std::vector<T>& vecIn, const std::string& ans, const std::vector<T>& vecAns, const char* fnName, const char* fmt){
    std::vector<T> vecIn_buf = vecIn;
    
    sstd::c2py<void> pyFn(tmpDir, fileName, fnName, fmt); // "Not writing back" or "Writing back"
    testing::internal::CaptureStdout();
    pyFn(&vecIn_buf[0], vecIn_buf.size());
    ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
    ASSERT_TRUE(vecIn_buf==vecAns); // "checking that the value is not written back." or "checking the written back value."
}
//---
template<typename T>
void TEST_c2py_builtin(const T in,
                       const std::vector<T>& vecIn,
                       const std::vector<T>& vecIn_WB,
                       const char* tmpDir,
                       const char* fileName,
                       const std::vector<std::string>& vecFnName,
                       const std::vector<std::string>& vecFmt
                       )
{
    // format: fmt
    {
        std::string ans;
        ans += num2typeNameInPython(in) + "\n";
        ans += val2str(in) + "\n";
        
        // fmt: Not writing back
        builtIn__builtin_and_retPointer(tmpDir, fileName, in, ans, vecFnName[0].c_str(), vecFmt[0].c_str());
    }
    {
        std::string ans = vec2ansStr(vecIn) + vec2ansStr(vecIn_WB);
        
        builtIn__fmt(tmpDir, fileName, vecIn, ans, vecIn,    vecFnName[1].c_str(), vecFmt[1].c_str()); // fmt_pConstT:    Not writing back
        builtIn__fmt(tmpDir, fileName, vecIn, ans, vecIn_WB, vecFnName[2].c_str(), vecFmt[2].c_str()); // fmt_pT:         Writing back
        builtIn__fmt(tmpDir, fileName, vecIn, ans, vecIn_WB, vecFnName[3].c_str(), vecFmt[3].c_str()); // fmt_pTBuiltin:  Writing back
        builtIn__fmt(tmpDir, fileName, vecIn, ans, vecIn_WB, vecFnName[4].c_str(), vecFmt[4].c_str()); // fmt_pTpBuiltin: Writing back
    }
}
//---
template<typename T>
void TEST_c2py_integer(const char* tmpDir,
                       const char* fileName,
                       const std::vector<std::string>& vecFnName,
                       const char* fmt_0, const char* fmt_1, const char* fmt_2, const char* fmt_3, const char* fmt_4
                       )
{
    // make input and answer
    T in = (T)0ull; in =~ in;
    const std::vector<T> vecIn={in, (T)(in-1), (T)(in-2), 0, 1, 2};
    std::vector<T> vecIn_WB = vecIn; vecIn_WB[0]=(T)9ull; vecIn_WB[1]=(T)2ull; // for ans of write back
    
    const std::vector<std::string> vecFmt = {fmt_0, fmt_1, fmt_2, fmt_3, fmt_4};
    
    TEST_c2py_builtin<T>(in, vecIn, vecIn_WB, tmpDir, fileName, vecFnName, vecFmt);
}
template<typename T>
void TEST_c2py_floatX(const char* tmpDir,
                       const char* fileName,
                       const std::vector<std::string>& vecFnName,
                       const char* fmt_0, const char* fmt_1, const char* fmt_2, const char* fmt_3, const char* fmt_4
                       )
{
    // make input and answer
    T in = (T)1.2345;
    const std::vector<T> vecIn={1.23, 4.56, 7.0, 0, 1, 2};
    std::vector<T> vecIn_WB = vecIn; for(uint i=0; i<vecIn_WB.size(); ++i){ vecIn_WB[i]*=100; } // for write back
    
    const std::vector<std::string> vecFmt = {fmt_0, fmt_1, fmt_2, fmt_3, fmt_4};
    
    TEST_c2py_builtin<T>(in, vecIn, vecIn_WB, tmpDir, fileName, vecFnName, vecFmt);
}
//---
//*
// 実装完了 (処理時間短縮のため，コメントアウト)

void TEST__c2py__builtIn_num(){
    
    const char* tmpDir = "./tmpDir";
    const char* fileName = "test/c2py_t";
    
    const std::vector<std::string> vecFnName = {"py_integer", "py_pInteger", "py_pInteger", "py_pInteger", "py_pInteger_pCnvBuiltin"};
    TEST_c2py_integer<uchar >(tmpDir, fileName, vecFnName, "uchar , ret uchar* , uchar ", "void, const uchar *, len", "void, uchar *, len", "void, uchar *|~, len", "void, uchar *|*~, len");
    TEST_c2py_integer< int8 >(tmpDir, fileName, vecFnName, "int8  , ret int8*  ,  int8 ", "void, const  int8 *, len", "void,  int8 *, len", "void,  int8 *|~, len", "void,  int8 *|*~, len");
    TEST_c2py_integer< int16>(tmpDir, fileName, vecFnName, "int16 , ret int16* ,  int16", "void, const  int16*, len", "void,  int16*, len", "void,  int16*|~, len", "void,  int16*|*~, len");
    TEST_c2py_integer< int32>(tmpDir, fileName, vecFnName, "int32 , ret int32* ,  int32", "void, const  int32*, len", "void,  int32*, len", "void,  int32*|~, len", "void,  int32*|*~, len");
    TEST_c2py_integer< int64>(tmpDir, fileName, vecFnName, "int64 , ret int64* ,  int64", "void, const  int64*, len", "void,  int64*, len", "void,  int64*|~, len", "void,  int64*|*~, len");
    TEST_c2py_integer<uint8 >(tmpDir, fileName, vecFnName, "uint8 , ret uint8* , uint8 ", "void, const uint8 *, len", "void, uint8 *, len", "void, uint8 *|~, len", "void, uint8 *|*~, len");
    TEST_c2py_integer<uint16>(tmpDir, fileName, vecFnName, "uint16, ret uint16*, uint16", "void, const uint16*, len", "void, uint16*, len", "void, uint16*|~, len", "void, uint16*|*~, len");
    TEST_c2py_integer<uint32>(tmpDir, fileName, vecFnName, "uint32, ret uint32*, uint32", "void, const uint32*, len", "void, uint32*, len", "void, uint32*|~, len", "void, uint32*|*~, len");
    TEST_c2py_integer<uint64>(tmpDir, fileName, vecFnName, "uint64, ret uint64*, uint64", "void, const uint64*, len", "void, uint64*, len", "void, uint64*|~, len", "void, uint64*|*~, len");
    
    const std::vector<std::string> vecFnName_f = {"py_floatX", "py_pFloatX", "py_pFloatX", "py_pFloatX", "py_pFloatX_pCnvBuiltin"};
    TEST_c2py_floatX< float>(tmpDir, fileName, vecFnName_f, "float,  ret float*,  float",  "void, const float*,  len", "void,  float*, len", "void,  float*|~, len", "void,  float*|*~, len");
    TEST_c2py_floatX<double>(tmpDir, fileName, vecFnName_f, "double, ret double*, double", "void, const double*, len", "void, double*, len", "void, double*|~, len", "void, double*|*~, len");
}
//*/
//-----------------------------------------------------------------------

//---
//*
// 実装完了 (処理時間短縮のため，コメントアウト)

void TEST__c2py__str(){
    const char* tmpDir = "./tmpDir";
    const char* fileName = "test/c2py_t";
    
    std::string str="01234abcdABCD";
    
    std::string ans = str + "\n";
    std::string ret_str="0123456789_XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX_ABCD";
    
    {
        // str, ret str*, str
        sstd::c2py<std::string> pyFn(tmpDir, fileName, "py_str", "str, ret str*, str");
        
        testing::internal::CaptureStdout();
        std::string ret;
        ASSERT_STREQ(pyFn(&ret, str).c_str(), str.c_str());
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
    }
    {
        // const str*
        std::string str_buf=str;
        
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pStr", "void, const str*"); // Not writing back
        testing::internal::CaptureStdout();
        pyFn(&str_buf);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_STREQ(str.c_str(), str_buf.c_str());
    }
    {
        // str*
        std::string str_buf=str;
        
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pStr", "void, str*"); // Writing back // Python says "'str' object does not support item assignment".
        testing::internal::CaptureStdout();
        pyFn(&str_buf);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_STREQ(str.c_str(), str_buf.c_str());
    }
    //---
    {
        // str*|~
        std::string str_buf=str;
        
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pStr", "void, str*|~"); // Writing back // Python says "'str' object does not support item assignment".
        testing::internal::CaptureStdout();
        pyFn(&str_buf);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_STREQ(str.c_str(), str_buf.c_str());
    }
    {
        // str*|*~
        std::string str_buf=str;
        
        std::string wb = "writeBack";
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pStr_pCnvBuiltin", "void, str*|*~"); // Writing back
        testing::internal::CaptureStdout();
        pyFn(&str_buf);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_STREQ(wb.c_str(), str_buf.c_str());
    }
}//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
//*
// 実装完了 (処理時間短縮のため，コメントアウト)

void TEST__c2py__vec_bool(){
    const char* tmpDir = "./tmpDir";
    const char* fileName = "test/c2py_t";
    
    const std::vector<bool> vecIn={ true, false,  true, false, false,  true};
    std::vector<bool> vecIn_inv(vecIn.size()); for(uint i=0; i<vecIn.size(); ++i){ vecIn_inv[i]=(!vecIn[i]); }
    
    std::string ans     = vec2ansStr(vecIn    );
    std::string ans_inv = vec2ansStr(vecIn_inv);
    std::string ans_plus = ans + ans_inv;
    {
        // vec<bool>, ret vec<bool>*, vec<bool>
        std::vector<bool> vecIn_buf=vecIn_inv;
        
        sstd::c2py<std::vector<bool>> pyFn(tmpDir, fileName, "py_vecBool", "vec<bool>, ret vec<bool>*, vec<bool>"); // Writing back
        testing::internal::CaptureStdout();
        std::vector<bool> ret = pyFn(&vecIn_buf, vecIn);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(ret==      vecIn);
        ASSERT_TRUE(vecIn_buf==vecIn);
    }
    {
        // const vec<bool>*
        std::vector<bool> vecIn_buf=vecIn;
        
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecBool", "void, const vec<bool>*"); // Not writing back
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf);
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        for(uint i=0; i<vecIn_buf.size(); ++i){ ASSERT_TRUE(vecIn_buf[i]==vecIn[i]); } // check not writing back
    }
    {
        // vec<bool>*
        std::vector<bool> vecIn_buf=vecIn;
        
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecBool", "void, vec<bool>*"); // Writing back
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf);
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(vecIn_buf==vecIn_inv); // check writing back
    }
    
    //---

    {
        // vec<bool>*|~
        std::vector<bool> vecIn_buf=vecIn;
        
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecBool", "void, vec<bool>*|~"); // Writing back
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf);
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(vecIn_buf==vecIn_inv); // check writing back
    }
    {
        // vec<bool>*|*~
        std::vector<bool> vecIn_buf=vecIn;
        
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecBool_pCnvBuiltin", "void, vec<bool>*|*~"); // Writing back
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf);
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        std::vector<bool> vecIn_inv_append = vecIn_inv;
        vecIn_inv_append <<= true;
        vecIn_inv_append <<= true;
        vecIn_inv_append <<= true;
        ASSERT_TRUE(vecIn_buf==vecIn_inv_append); // check writing back
    }
    
    //---
    
    {
        // remove element
        std::vector<bool> vecIn_ans=vecIn; vec_rm(vecIn_ans, 0);
        
        std::vector<bool> vecIn_buf=vecIn;
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecBool_pCnvBuiltin_del", "void, vec<bool>*|*~"); // Writing back
        pyFn(&vecIn_buf);
        ASSERT_TRUE(vecIn_buf.size()+1==vecIn.size());
    }
    {
        // clear element
        std::vector<bool> vecIn_buf=vecIn;
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecBool_pCnvBuiltin_clear", "void, vec<bool>*|*~"); // Writing back
        pyFn(&vecIn_buf);
        ASSERT_TRUE(vecIn_buf.size()==0);
    }

}//*/
//-----------------------------------------------------------------------
//*
// 実装完了 (処理時間短縮のため，コメントアウト)

void TEST__c2py__vec_char(){
    const char* tmpDir = "./tmpDir";
    const char* fileName = "test/c2py_t";
    
    std::vector<char> vecIn   ={'a', 'b', 'c', 'd'};
    std::vector<char> vecIn_WB={'9', 'b', 'c', 'd', '8'};
    std::string ans      = vec2ansStr(vecIn);
    std::string ans_plus = ans + vec2ansStr(vecIn_WB);
    {
        // vec<char>, ret vec<char>*, vec<char>
        std::vector<char> ret0, ret1;
        std::vector<char> vecIn_buf = vecIn;
        sstd::c2py<std::vector<char>> pyFn(tmpDir, fileName, "py_vecChar", "vec<char>, ret vec<char>*, vec<char>");
        
        testing::internal::CaptureStdout();
        ret0 = pyFn(&ret1, vecIn_buf);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        std::vector<char> ans_ret0={'A', 'B', 'C'};
        std::vector<char> ans_ret1={'W', 'X', 'Y', 'Z'};
        ASSERT_TRUE(ret0==ans_ret0);
        ASSERT_TRUE(ret1==ans_ret1);
    }
    {
        // const vec<char>*
        std::vector<char> vecIn_buf = vecIn;
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecChar", "void, const vec<char>*"); // Not writing back
        
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf);
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(vecIn_buf==vecIn);
    }
    {
        // vec<char>*
        std::vector<char> vecIn_buf = vecIn;
        
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecChar", "void, vec<char>*"); // Writing back
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf);
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        ASSERT_TRUE(vecIn_buf==vecIn_WB);
    }
    //---
    {
        // remove element
        std::vector<char> vecIn_ans=vecIn; vec_rm(vecIn_ans, 0);
        
        std::vector<char> vecIn_buf=vecIn;
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecChar_del", "void, vec<char>*"); // Writing back
        pyFn(&vecIn_buf);
        ASSERT_TRUE(vecIn_buf==vecIn_ans);
    }
    {
        // clear element
        std::vector<char> vecIn_buf = vecIn;
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecChar_clear", "void, vec<char>*"); // Writing back
        pyFn(&vecIn_buf);
        ASSERT_TRUE(vecIn_buf.size()==0);
    }
    //---
    {
        // vec<char>*|~
        std::vector<char> vecIn_buf=vecIn;
        
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecChar", "void, vec<char>*|~"); // Writing back
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf);
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(vecIn_buf==vecIn_WB);
    }
    {
        // vec<char>*|*~
        std::vector<char> vecIn_buf=vecIn;
        
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecChar_pCnvBuiltin", "void, vec<char>*|*~"); // Writing back
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf);
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(vecIn_buf==vecIn_WB);
    }
}
//*/
//-----------------------------------------------------------------------
template<typename T>
void TEST_c2py_vecIntegerXX(const char* tmpDir,
                            const char* fileName,
                            const char* fmt_0, const char* fmt_1, const char* fmt_2, const char* fmt_3, const char* fmt_4, const char* fmt_5
                            )
{
    T in = (T)0ull; in =~ in;
    const std::vector<T> vecIn={in, (T)(in-1), (T)(in-2), 0, 1, 2};
    std::vector<T> vecIn_WB=vecIn; vecIn_WB[0]=(T)9; vecIn_WB<<=(T)88;
    
    std::string ans          = vec2ansStr(vecIn   );
    std::string ans_WB       = vec2ansStr(vecIn_WB);
    std::string ans_plus     = ans + ans_WB;
    std::string ans_withType = num2typeNameInPython(in)+'\n' + ans;
    
    std::vector<T> vecIn_WB_woAppend=vecIn; vecIn_WB_woAppend[0]=(T)9;
    std::string ans_woAppend = ans + vec2ansStr(vecIn_WB_woAppend); // wo: without
    
    {
        // "vec<T>, ret vec<T>*, vec<T>"
        sstd::c2py<std::vector<T>> pyFn(tmpDir, fileName, "py_vecX", fmt_0);
        std::vector<T> ret0, ret1;
        
        testing::internal::CaptureStdout();
        ret0 = pyFn(&ret1, vecIn);
        ASSERT_STREQ(ans_withType.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        const std::vector<T> ansRet0={9, 8, 7, 6};
        const std::vector<T> ansRet1={5, 4, 3, 2, 1, 0};
        ASSERT_TRUE(ret0==ansRet0);
        ASSERT_TRUE(ret1==ansRet1);
    }
    {
        // "void, const vec<T>*"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecX_const", fmt_1); // Not writing back
        std::vector<T> vecIn_buf=vecIn;
        
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        ASSERT_TRUE(vecIn_buf==vecIn); // check that the input value was not writted back.
    }
    {
        // "void, vec<T>*"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecX", fmt_2); // Writing back
        std::vector<T> vecIn_buf=vecIn;
        
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf); // numpy array type can not write back appending value, because appending new value to numpy object will change the address of object.
                          // In order to avoid this problem, pseudo-pointer type by python side (that is showed in below the TEST as "vec<T>*|*") can be used.
        // ndarray で渡した場合，numpy が同一オブジェクトのまま配列長を変更できないため，追記を書き戻せない．
        // どうしても書き戻したい場合は，下記の "void, vec<T>*|*" のように，ポインタ代わりの配列に入れてから受け渡すと良い．
        ASSERT_STREQ(ans_woAppend.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        ASSERT_TRUE(vecIn_buf==vecIn_WB_woAppend); // check that the input value was writted back.
    }
    //---
    {
        // "void, vec<T>*|~"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecX_cnvBuiltin", fmt_3); // Writing back
        std::vector<T> vecIn_buf=vecIn;
        
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf); // list type (builtin type) can write back value of ".append()".
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        ASSERT_TRUE(vecIn_buf==vecIn_WB); // check that the input value was writted back.
    }
    {
        // "void, vec<T>*|*~"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecX_pCnvBuiltin", fmt_4); // Writing back
        std::vector<T> vecIn_buf=vecIn;
        
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf);
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        ASSERT_TRUE(vecIn_buf==vecIn_WB); // check that the input value was writted back.
    }
    //---
    {
        // "void, vec<T>*|*"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecX_pCnv", fmt_4); // Writing back
        std::vector<T> vecIn_buf=vecIn;
        
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf); // ndarray で渡した場合は，破壊的追記となり，オブジェクトのアドレスが変わるため書き戻しできない．
                          // しかし，ここでは，配列に入れて渡しているため，配列内のオブジェクトを書き換えても，配列自体のアドレスは同一のため，書き戻しできる
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        ASSERT_TRUE(vecIn_buf==vecIn_WB); // check that the input value was writted back.
    }
}
//---
template<typename T>
void TEST_c2py_vecFolatXX(const char* tmpDir,
                          const char* fileName,
                          const char* fmt_0, const char* fmt_1, const char* fmt_2, const char* fmt_3, const char* fmt_4, const char* fmt_5
                          )
{
    T in = (T)1.2345;
    const std::vector<T> vecIn={-1.23, 4.56, 7.0, 0, 1, 2};
    std::vector<T> vecIn_WB=vecIn; vecIn_WB[0]=(T)9; vecIn_WB<<=(T)88;
    
    std::string ans          = vec2ansStr(vecIn   );
    std::string ans_WB       = vec2ansStr(vecIn_WB);
    std::string ans_plus     = ans + ans_WB;
    std::string ans_withType = num2typeNameInPython(in)+"\n" + ans;
    
    std::vector<T> vecIn_WB_woAppend=vecIn; vecIn_WB_woAppend[0]=(T)9;
    std::string ans_woAppend = ans + vec2ansStr(vecIn_WB_woAppend); // wo: without
    {
        // vec<T>, ret vec<T>*, vec<T>
        sstd::c2py<std::vector<T>> pyFn(tmpDir, fileName, "py_vecFloatX", fmt_0);
        std::vector<T> ret0, ret1;
        
        testing::internal::CaptureStdout();
        ret0 = pyFn(&ret1, vecIn);
        ASSERT_STREQ(ans_withType.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        const std::vector<T> ansRet0={9, 8, 7, 6};
        const std::vector<T> ansRet1={5, 4, 3, 2, 1, 0};
        ASSERT_TRUE(ret0==ansRet0);
        ASSERT_TRUE(ret1==ansRet1);
    }
    {
        // void, const vec<T>*
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecFloatX_const", fmt_1); // Not writing back
        std::vector<T> vecIn_buf = vecIn;
        
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
    }
    {
        // void, vec<T>*
        sstd::c2py<void> pyFn("./tmpDir", "test/c2py_t", "py_pVecFloatX", fmt_2); // Writing back
        std::vector<T> vecIn_buf = vecIn;
        
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf); // numpy array type can not write back appending value, because of the address of object will be changed.
                          // In order to avoid this problem, pseudo-pointer type by python side (that is showed in below the TEST as "vec<T>*|*") can be used.
        ASSERT_STREQ(ans_woAppend.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        ASSERT_TRUE(vecIn_buf==vecIn_WB_woAppend); // check that the input value was writted back.
    }
    //---
    {
        // void, vec<T>*|~
        sstd::c2py<void> pyFn("./tmpDir", "test/c2py_t", "py_pVecFloatX_cnvBuiltin", fmt_3); // Writing back
        std::vector<T> vecIn_buf = vecIn;
        
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf); // list type (builtin type) can write back value of ".append()".
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        ASSERT_TRUE(vecIn_buf==vecIn_WB); // check that the input value was writted back.
    }
    {
        // void, vec<T>*|*~
        sstd::c2py<void> pyFn("./tmpDir", "test/c2py_t", "py_pVecFloatX_pCnvBuiltin", fmt_4); // Writing back
        std::vector<T> vecIn_buf = vecIn;
        
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf);
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        ASSERT_TRUE(vecIn_buf==vecIn_WB); // check that the input value was writted back.
    }
    //---
    {
        // void, vec<T>*|*
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecFloatX_pCnv", fmt_5); // Writing back
        std::vector<T> vecIn_buf=vecIn;
        
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf); // ndarray で渡した場合は，破壊的追記となり，オブジェクトのアドレスが変わるため書き戻しできない．
                          // しかし，ここでは，配列に入れて渡しているため，配列内のオブジェクトを書き換えても，配列自体のアドレスは同一のため，書き戻しできる
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        ASSERT_TRUE(vecIn_buf==vecIn_WB); // check that the input value was writted back.
    }
}
//---
//*
// 実装完了 (処理時間短縮のため，コメントアウト)

void TEST__c2py__vec_builtin(){
    const char* tmpDir   = "./tmpDir";
    const char* fileName = "test/c2py_t";
    
    TEST_c2py_vecIntegerXX<uchar >(tmpDir, fileName, "vec <uchar>, ret vec <uchar>*, vec <uchar>", "void, const vec <uchar>*", "void, vec< uchar>*", "void, vec <uchar>*|~", "void, vec <uchar>*|*~", "void, vec <uchar>*|*");
    TEST_c2py_vecIntegerXX< int8 >(tmpDir, fileName, "vec< int8 >, ret vec< int8 >*, vec< int8 >", "void, const vec< int8 >*", "void, vec< int8 >*", "void, vec< int8 >*|~", "void, vec< int8 >*|*~", "void, vec< int8 >*|*");
    TEST_c2py_vecIntegerXX< int16>(tmpDir, fileName, "vec< int16>, ret vec< int16>*, vec< int16>", "void, const vec< int16>*", "void, vec< int16>*", "void, vec< int16>*|~", "void, vec< int16>*|*~", "void, vec< int16>*|*");
    TEST_c2py_vecIntegerXX< int32>(tmpDir, fileName, "vec< int32>, ret vec< int32>*, vec< int32>", "void, const vec< int32>*", "void, vec< int32>*", "void, vec< int32>*|~", "void, vec< int32>*|*~", "void, vec< int32>*|*");
    TEST_c2py_vecIntegerXX< int64>(tmpDir, fileName, "vec< int64>, ret vec< int64>*, vec< int64>", "void, const vec< int64>*", "void, vec< int64>*", "void, vec< int64>*|~", "void, vec< int64>*|*~", "void, vec< int64>*|*");
    TEST_c2py_vecIntegerXX<uint8 >(tmpDir, fileName, "vec<uint8 >, ret vec<uint8 >*, vec<uint8 >", "void, const vec<uint8 >*", "void, vec<uint8 >*", "void, vec<uint8 >*|~", "void, vec<uint8 >*|*~", "void, vec<uint8 >*|*");
    TEST_c2py_vecIntegerXX<uint16>(tmpDir, fileName, "vec<uint16>, ret vec<uint16>*, vec<uint16>", "void, const vec<uint16>*", "void, vec<uint16>*", "void, vec<uint16>*|~", "void, vec<uint16>*|*~", "void, vec<uint16>*|*");
    TEST_c2py_vecIntegerXX<uint32>(tmpDir, fileName, "vec<uint32>, ret vec<uint32>*, vec<uint32>", "void, const vec<uint32>*", "void, vec<uint32>*", "void, vec<uint32>*|~", "void, vec<uint32>*|*~", "void, vec<uint32>*|*");
    TEST_c2py_vecIntegerXX<uint64>(tmpDir, fileName, "vec<uint64>, ret vec<uint64>*, vec<uint64>", "void, const vec<uint64>*", "void, vec<uint64>*", "void, vec<uint64>*|~", "void, vec<uint64>*|*~", "void, vec<uint64>*|*");
    
    TEST_c2py_vecFolatXX<float> (tmpDir, fileName, "vec< float>, ret vec< float>*, vec< float>", "void, const vec< float>*", "void, vec< float>*", "void, vec< float>*|~", "void, vec< float>*|*~", "void, vec< float>*|*");
    TEST_c2py_vecFolatXX<double>(tmpDir, fileName, "vec<double>, ret vec<double>*, vec<double>", "void, const vec<double>*", "void, vec<double>*", "void, vec<double>*|~", "void, vec<double>*|*~", "void, vec<double>*|*");
}//*/
//-----------------------------------------------------------------------
//*
// 実装完了 (処理時間短縮のため，コメントアウト)

void TEST__c2py__vec_str(){
    const char* tmpDir   = "./tmpDir";
    const char* fileName = "test/c2py_t";
    
    std::vector<std::string> vecIn   ={"ABCD", "EF", "GHIJKLMNO"};
    std::vector<std::string> vecIn_WB={"abcdefg", "EF", "GHIJKLMNO", "0123"};
    
    std::string ans    = vec2ansStr(vecIn   );
    std::string ans_WB = vec2ansStr(vecIn_WB);
    {
        // vec<str>, ret vec<str>*, vec<str>
        sstd::c2py<std::vector<std::string>> pyFn(tmpDir, fileName, "py_vecStr", "vec<str>, ret vec<str>*, vec<str>");
        std::vector<std::string> ret0, ret1;
        
        testing::internal::CaptureStdout();
        ret0 = pyFn(&ret1, vecIn);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        std::vector<std::string> ansRet0={"01234", "ABCDEFGHIJKLMNOPQRRRRRRRRZ", "STUUUUUUUUUUUUUUUUUUUUUUUUZ"};
        std::vector<std::string> ansRet1={"XXXXXXX", "YYYYYY", "ZZ"};
        ASSERT_TRUE(ret0==ansRet0);
        ASSERT_TRUE(ret1==ansRet1);
    }
    {
        // void, const vec<str>*
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecStr_const", "void, const vec<str>*"); // Not writing back
        std::vector<std::string> vecIn_buf = vecIn;
        
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        ASSERT_TRUE(vecIn_buf==vecIn);
    }
    {
        // void, vec<str>*
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecStr", "void, vec<str>*"); // Writing back
        std::vector<std::string> vecIn_buf = vecIn;
        
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        ASSERT_TRUE(vecIn_buf==vecIn_WB);
    }
    //---
    {
        // void, vec<str>*|~
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecStr", "void, vec<str>*|~"); // Writing back
        std::vector<std::string> vecIn_buf = vecIn;
        
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        ASSERT_TRUE(vecIn_buf==vecIn_WB);
    }
    {
        // void, vec<str>*|*~
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVecStr_pCnvBuiltin", "void, vec<str>*|*~"); // Writing back
        std::vector<std::string> vecIn_buf = vecIn;
        
        testing::internal::CaptureStdout();
        pyFn(&vecIn_buf);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        ASSERT_TRUE(vecIn_buf==vecIn_WB);
    }
}//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------

// matRC: "row-major matrix" or "column-major matrix"
template<typename T>
void TEST_c2py_matBool(const char* tmpDir, const char* fileName,
                       const char* fmt_0, const char* fmt_1, const char* fmt_2, const char* fmt_3, const char* fmt_4)
{
    T matIn{{true, false, false},{false, true, false},{false, false, true},{true, false, false}};
    T matIn_WB = matIn; matIn_WB(0, 0)=false;
    std::string ans      = mat2ansStr(matIn   );
    std::string ans_WB   = mat2ansStr(matIn_WB);
    std::string ans_plus = ans + ans_WB;
    {
        // "mat<bool>, ret mat<bool>*, mat<bool>"
        sstd::c2py<T> pyFn(tmpDir, fileName, "py_matBool", fmt_0);
        
        testing::internal::CaptureStdout();
        T ret0, ret1; ret0 = pyFn(&ret1, matIn);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        ASSERT_TRUE(ret0==matIn);
        ASSERT_TRUE(ret1==matIn);
    }
    {
        // "void, const mat<bool>*"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatBool_const", fmt_1); // Not writing back
        
        testing::internal::CaptureStdout();
        pyFn(&matIn);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
    }
    {
        // "void, mat<bool>*"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatBool", fmt_2); // Writing back
        T matIn_buf = matIn;
        
        testing::internal::CaptureStdout();
        pyFn(&matIn_buf); // ndarray で渡した場合は，追記を書き戻せない
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn_WB);
    }
    //---
    {
        // "void, mat<bool>*|~"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatBool", fmt_3); // Writing back
        T matIn_buf = matIn;
        
        testing::internal::CaptureStdout();
        pyFn(&matIn_buf); // ndarray で渡した場合は，追記できない
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn_WB);
    }
    {
        // "void, mat<bool>*|*~"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatBool_pCnvBuiltin", fmt_4); // Writing back
        T matIn_buf = matIn;
        
        testing::internal::CaptureStdout();
        pyFn(&matIn_buf); // ndarray で渡した場合は，追記できない
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn_WB);
    }
}
template<typename T>
void TEST_c2py_matChar(const char* tmpDir, const char* fileName,
                       const char* fmt_0, const char* fmt_1, const char* fmt_2, const char* fmt_3, const char* fmt_4, const char* fmt_5)
{
    T matIn{{'a', 'b', 'c'},{'d', 'e', 'f'},{'g', 'h', 'i'},{'j', 'k', 'l'}};
    T matIn_WB = matIn; matIn_WB(0, 0)='A';
    std::string ans      = mat2ansStr(matIn   );
    std::string ans_WB   = mat2ansStr(matIn_WB);
    std::string ans_plus = ans + ans_WB;
    {
        // "mat<char>, ret mat<char>*, mat<char>"
        sstd::c2py<T> pyFn(tmpDir, fileName, "py_matChar", fmt_0);
        
        testing::internal::CaptureStdout();
        T ret0, ret1; ret0 = pyFn(&ret1, matIn);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        ASSERT_TRUE(ret0==matIn);
        ASSERT_TRUE(ret1==matIn);
    }
    {
        // "void, const mat<char>*"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatChar_const", fmt_1); // Not writing back
        
        testing::internal::CaptureStdout();
        pyFn(&matIn);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
    }
    {
        // "void, mat<char>*"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatChar", fmt_2); // Writing back
        T matIn_buf = matIn;
        
        testing::internal::CaptureStdout();
        pyFn(&matIn_buf); // ndarray で渡した場合は，追記を書き戻せない
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn_WB);
    }
    //---
    {
        // "void, mat<char>*|~"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatChar", fmt_3); // Writing back
        T matIn_buf = matIn;
        
        testing::internal::CaptureStdout();
        pyFn(&matIn_buf); // ndarray で渡した場合は，追記できない
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn_WB);
    }
    {
        // "void, mat<char>*|*~"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatChar_pCnvBuiltin", fmt_4); // Writing back
        T matIn_buf = matIn;
        
        testing::internal::CaptureStdout();
        pyFn(&matIn_buf); // ndarray で渡した場合は，追記できない
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn_WB);
    }
    //---
    {
        // clear element
        T matIn{{'a', 'b', 'c'},{'d', 'e', 'f'},{'g', 'h', 'i'},{'j', 'k', 'l'}};
        
        T matIn_buf = matIn;
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatChar_pCnv_clear", fmt_5); // Writing back
//        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatChar_pCnv_clear", "void, mat<char>*|*"); // Writing back
        pyFn(&matIn_buf);
//        ASSERT_TRUE(matIn_buf.size()==0);
    }
}
template<typename matT, typename T>
void TEST_c2py_matIntX(const char* tmpDir, const char* fileName,
                       const char* fmt_0, const char* fmt_1, const char* fmt_2, const char* fmt_3, const char* fmt_4)
{
    T in = (T)0ull; in =~ in;
    const matT matIn{{in, (T)(in-1), 3},{4, 5, 6},{7, 8, 9},{10, 11, 12}};
    matT matIn_WB=matIn; matIn_WB(0,0)=(T)9;
    std::string ans      = mat2ansStr(matIn   );
    std::string ans_WB   = mat2ansStr(matIn_WB);
    std::string ans_plus = ans + ans_WB;
    {
        // "mat_rc<T>, ret mat_rc<T>*, mat_rc<T>"
        sstd::c2py<matT> pyFn(tmpDir, fileName, "py_matIntX", fmt_0);
        matT matIn_buf = matIn;
        matT ret0, ret1;
        
        testing::internal::CaptureStdout();
        ret0 = pyFn(&ret1, matIn_buf);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn);
    }
    {
        // "void, const mat_rc<T>*"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatIntX_const", fmt_1); // Not writing back
        matT matIn_buf = matIn;
        
        testing::internal::CaptureStdout();
        pyFn(&matIn_buf);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn);
    }
    {
        // "void, mat_rc<T>*"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatIntX", fmt_2); // Writing back
        matT matIn_buf = matIn;
        
        testing::internal::CaptureStdout();
        pyFn(&matIn_buf); // ndarray で渡した場合は，追記できない
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn_WB);
    }
    //--
    {
        // "void, mat_rc<T>*|~"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatIntX", fmt_3); // Writing back
        matT matIn_buf = matIn;
        
        testing::internal::CaptureStdout();
        pyFn(&matIn_buf); // ndarray で渡した場合は，追記できない
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn_WB);
    }
    {
        // "void, mat_rc<T>*|*~"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatIntX_pCnvBuiltin", fmt_4); // Writing back
        matT matIn_buf = matIn;
        
        testing::internal::CaptureStdout();
        pyFn(&matIn_buf); // ndarray で渡した場合は，追記できない
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn_WB);
    }
    //---
    {
        // "void, mat_rc<T>*|*~"
        // write back with change size
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatIntX_pCnvBuiltin_changeSize", fmt_4); // Writing back
        matT matIn_buf = matIn;
        const matT matAns{{1, 2, 3, 4},{5, 6, 7, 8},{9, 10, 11, 12},{13, 14, 15, 16}};
        
        testing::internal::CaptureStdout();
        pyFn(&matIn_buf);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matAns);
    }
}
template<typename matT, typename T>
void TEST_c2py_matFloatX(const char* tmpDir, const char* fileName,
                         const char* fmt_0, const char* fmt_1, const char* fmt_2, const char* fmt_3, const char* fmt_4)
{
    matT matIn{{1, 2, 3},{4, 5, 6},{7, 8, 9},{10, 11, 12}};
    matT matIn_WB=matIn; matIn_WB(0,0)=(T)9;
    std::string ans      = mat2ansStr(matIn   );
    std::string ans_WB   = mat2ansStr(matIn_WB);
    std::string ans_plus = ans + ans_WB;
    {
        // "mat_rc<float>, ret mat_rc<float>*, mat_rc<float>"
        sstd::c2py<matT> pyFn(tmpDir, fileName, "py_matFloatX", fmt_0);
        matT matIn_buf = matIn;
        matT ret0, ret1;
        
        testing::internal::CaptureStdout();
        ret0 = pyFn(&ret1, matIn_buf);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn);
    }
    {
        // "void, const mat_rc<float>*"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatFloatX_const", fmt_1); // Not writing back
        matT matIn_buf = matIn;
        
        testing::internal::CaptureStdout();
        pyFn(&matIn_buf);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn);
    }
    {
        // "void, mat_rc<float>*"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatFloatX", fmt_2); // Writing back
        matT matIn_buf = matIn;
        
        testing::internal::CaptureStdout();
        pyFn(&matIn_buf); // ndarray で渡した場合は，追記できない
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn_WB);
    }
    //---
    {
        // "void, mat_rc<float>*|~"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatFloatX", fmt_3); // Writing back
        matT matIn_buf = matIn;
        
        testing::internal::CaptureStdout();
        pyFn(&matIn_buf); // ndarray で渡した場合は，追記できない
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn_WB);
    }
    {
        // "void, mat_rc<float>*|*~"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatFloatX_pCnvBuiltin", fmt_4); // Writing back
        matT matIn_buf = matIn;
        
        testing::internal::CaptureStdout();
        pyFn(&matIn_buf); // ndarray で渡した場合は，追記できない
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn);
    }
}
template<typename matT>
void TEST_c2py_matStr(const char* tmpDir, const char* fileName,
                      const char* fmt_0, const char* fmt_1, const char* fmt_2, const char* fmt_3, const char* fmt_4)
{
    matT matIn{{"a", "ab", "abc"},{"abcd", "abcde", "abcdef"},{"7", "8", "9"},{"10", "11", "12"}};
    matT matIn_WB=matIn; matIn_WB(0,0)="XXX";
    std::string ans      = mat2ansStr(matIn   );
    std::string ans_WB   = mat2ansStr(matIn_WB);
    std::string ans_plus = ans + ans_WB;
    {
        // "mat<str>, ret mat<str>*, mat<str>*"
        
        // mat<str> 引数は，不可．恐らく，gcc 5.4.0 の可変長引数の実装が，そもそもクラス型を想定していないので，バグを踏む．-> ポインタ渡しなら問題ない．
        // sstd::c2py<sstd::mat<std::string>> py_matStr("./tmpDir", "test/c2py_t", "py_matX", "mat<str>, mat<str>");
        // sstd::printn(py_matStr(matStr));
        sstd::c2py<matT> pyFn(tmpDir, fileName, "py_matStr", fmt_0);
        matT matIn_buf = matIn;
        matT ret0, ret1;
        
        testing::internal::CaptureStdout();
        ret0 = pyFn(&ret1, &matIn_buf);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn);
    }
    {
        // "void, const mat<str>*"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatStr_const", fmt_1); // Not writing back
        matT matIn_buf = matIn;
        
        testing::internal::CaptureStdout();
        pyFn(&matIn_buf);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn);
    }
    {
        // "void, mat<str>*"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatStr", fmt_2); // Writing back
        matT matIn_buf = matIn;
        
        testing::internal::CaptureStdout();
        pyFn(&matIn_buf); // ndarray で渡した場合は，追記できない
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn_WB);
    }
    //---
    {
        // "void, mat<str>*|~"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatStr", fmt_3); // Writing back
        matT matIn_buf = matIn;
        
        testing::internal::CaptureStdout();
        pyFn(&matIn_buf); // ndarray で渡した場合は，追記できない
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn_WB);
    }
    {
        // "void, mat<str>*|*~"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pMatStr_pCnvBuiltin", fmt_4); // Writing back
        matT matIn_buf = matIn;
        
        testing::internal::CaptureStdout();
        pyFn(&matIn_buf); // ndarray で渡した場合は，追記できない
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(matIn_buf==matIn_WB);
    }
}

//---
//*
// 実装完了 (処理時間短縮のため，コメントアウト)

void TEST__c2py__mat_c(){
    const char* tmpDir   = "./tmpDir";
    const char* fileName = "test/c2py_t";
    
    TEST_c2py_matBool<sstd::mat_c<bool>>(tmpDir, fileName, "mat_c<bool>, ret mat_c<bool>*, mat_c<bool>", "void, const mat_c<bool>*", "void, mat_c<bool>*", "void, mat_c<bool>*|~", "void, mat_c<bool>*|*~");
    TEST_c2py_matChar<sstd::mat_c<char>>(tmpDir, fileName, "mat_c<char>, ret mat_c<char>*, mat_c<char>", "void, const mat_c<char>*", "void, mat_c<char>*", "void, mat_c<char>*|~", "void, mat_c<char>*|*~", "void, mat_c<char>*|*");
    
    TEST_c2py_matIntX <sstd::mat_c< int8 >,  int8 >(tmpDir, fileName, "mat_c< int8 >, ret mat_c< int8 >*, mat_c< int8 >", "void, const mat_c< int8 >*", "void, mat_c< int8 >*", "void, mat_c< int8 >*|~", "void, mat_c< int8 >*|*~");
    TEST_c2py_matIntX <sstd::mat_c< int16>,  int16>(tmpDir, fileName, "mat_c< int16>, ret mat_c< int16>*, mat_c< int16>", "void, const mat_c< int16>*", "void, mat_c< int16>*", "void, mat_c< int16>*|~", "void, mat_c< int16>*|*~");
    TEST_c2py_matIntX <sstd::mat_c< int32>,  int32>(tmpDir, fileName, "mat_c< int32>, ret mat_c< int32>*, mat_c< int32>", "void, const mat_c< int32>*", "void, mat_c< int32>*", "void, mat_c< int32>*|~" ,"void, mat_c< int32>*|*~");
    TEST_c2py_matIntX <sstd::mat_c< int64>,  int64>(tmpDir, fileName, "mat_c< int64>, ret mat_c< int64>*, mat_c< int64>", "void, const mat_c< int64>*", "void, mat_c< int64>*", "void, mat_c< int64>*|~", "void, mat_c< int64>*|*~");
    TEST_c2py_matIntX <sstd::mat_c<uint8 >, uint8 >(tmpDir, fileName, "mat_c<uint8 >, ret mat_c<uint8 >*, mat_c<uint8 >", "void, const mat_c<uint8 >*", "void, mat_c<uint8 >*", "void, mat_c<uint8 >*|~", "void, mat_c<uint8 >*|*~");
    TEST_c2py_matIntX <sstd::mat_c<uint16>, uint16>(tmpDir, fileName, "mat_c<uint16>, ret mat_c<uint16>*, mat_c<uint16>", "void, const mat_c<uint16>*", "void, mat_c<uint16>*", "void, mat_c<uint16>*|~", "void, mat_c<uint16>*|*~");
    TEST_c2py_matIntX <sstd::mat_c<uint32>, uint32>(tmpDir, fileName, "mat_c<uint32>, ret mat_c<uint32>*, mat_c<uint32>", "void, const mat_c<uint32>*", "void, mat_c<uint32>*", "void, mat_c<uint32>*|~", "void, mat_c<uint32>*|*~");
    TEST_c2py_matIntX <sstd::mat_c<uint64>, uint64>(tmpDir, fileName, "mat_c<uint64>, ret mat_c<uint64>*, mat_c<uint64>", "void, const mat_c<uint64>*", "void, mat_c<uint64>*", "void, mat_c<uint64>*|~", "void, mat_c<uint64>*|*~");
    
    TEST_c2py_matFloatX<sstd::mat_c<float >, float >(tmpDir, fileName, "mat_c<float >, ret mat_c<float >*, mat_c<float >", "void, const mat_c<float >*", "void, mat_c<float >*", "void, mat_c<float >*|~", "void, mat_c<float >*|*~");
    TEST_c2py_matFloatX<sstd::mat_c<double>, double>(tmpDir, fileName, "mat_c<double>, ret mat_c<double>*, mat_c<double>", "void, const mat_c<double>*", "void, mat_c<double>*", "void, mat_c<double>*|~", "void, mat_c<double>*|*~");
    
    TEST_c2py_matStr<sstd::mat_c<std::string>>(tmpDir, fileName, "mat_c<str>, ret mat_c<str>*, mat_c<str>*", "void, const mat_c<str>*", "void, mat_c<str>*",    "void, mat_c<str>*|~",    "void, mat_c<str>*|*~");
    // "mat<str>, mat<str>" は，C++ の可変長引数で受け渡そうとすると，segmentation fault で落ちる．少なくとも gcc 5.4.0 では対応していないので，ポインタで渡しておく．
}
void TEST__c2py__mat_r(){
    const char* tmpDir   = "./tmpDir";
    const char* fileName = "test/c2py_t";
    
    TEST_c2py_matBool<sstd::mat_r<bool>>(tmpDir, fileName, "mat_r<bool>, ret mat_r<bool>*, mat_r<bool>", "void, const mat_r<bool>*", "void, mat_r<bool>*", "void, mat_r<bool>*|~", "void, mat_r<bool>*|*~");
    TEST_c2py_matChar<sstd::mat_r<char>>(tmpDir, fileName, "mat_r<char>, ret mat_r<char>*, mat_r<char>", "void, const mat_r<char>*", "void, mat_r<char>*", "void, mat_r<char>*|~", "void, mat_r<char>*|*~", "void, mat_r<char>*|*");
    
    TEST_c2py_matIntX <sstd::mat_r< int8 >,  int8 >(tmpDir, fileName, "mat_r< int8 >, ret mat_r< int8 >*, mat_r< int8 >", "void, const mat_r< int8 >*", "void, mat_r< int8 >*", "void, mat_r< int8 >*|~", "void, mat_r< int8 >*|*~");
    TEST_c2py_matIntX <sstd::mat_r< int16>,  int16>(tmpDir, fileName, "mat_r< int16>, ret mat_r< int16>*, mat_r< int16>", "void, const mat_r< int16>*", "void, mat_r< int16>*", "void, mat_r< int16>*|~", "void, mat_r< int16>*|*~");
    TEST_c2py_matIntX <sstd::mat_r< int32>,  int32>(tmpDir, fileName, "mat_r< int32>, ret mat_r< int32>*, mat_r< int32>", "void, const mat_r< int32>*", "void, mat_r< int32>*", "void, mat_r< int32>*|~" ,"void, mat_r< int32>*|*~");
    TEST_c2py_matIntX <sstd::mat_r< int64>,  int64>(tmpDir, fileName, "mat_r< int64>, ret mat_r< int64>*, mat_r< int64>", "void, const mat_r< int64>*", "void, mat_r< int64>*", "void, mat_r< int64>*|~", "void, mat_r< int64>*|*~");
    TEST_c2py_matIntX <sstd::mat_r<uint8 >, uint8 >(tmpDir, fileName, "mat_r<uint8 >, ret mat_r<uint8 >*, mat_r<uint8 >", "void, const mat_r<uint8 >*", "void, mat_r<uint8 >*", "void, mat_r<uint8 >*|~", "void, mat_r<uint8 >*|*~");
    TEST_c2py_matIntX <sstd::mat_r<uint16>, uint16>(tmpDir, fileName, "mat_r<uint16>, ret mat_r<uint16>*, mat_r<uint16>", "void, const mat_r<uint16>*", "void, mat_r<uint16>*", "void, mat_r<uint16>*|~", "void, mat_r<uint16>*|*~");
    TEST_c2py_matIntX <sstd::mat_r<uint32>, uint32>(tmpDir, fileName, "mat_r<uint32>, ret mat_r<uint32>*, mat_r<uint32>", "void, const mat_r<uint32>*", "void, mat_r<uint32>*", "void, mat_r<uint32>*|~", "void, mat_r<uint32>*|*~");
    TEST_c2py_matIntX <sstd::mat_r<uint64>, uint64>(tmpDir, fileName, "mat_r<uint64>, ret mat_r<uint64>*, mat_r<uint64>", "void, const mat_r<uint64>*", "void, mat_r<uint64>*", "void, mat_r<uint64>*|~", "void, mat_r<uint64>*|*~");
    
    TEST_c2py_matFloatX<sstd::mat_r<float >, float >(tmpDir, fileName, "mat_r<float >, ret mat_r<float >*, mat_r<float >", "void, const mat_r<float >*", "void, mat_r<float >*", "void, mat_r<float >*|~", "void, mat_r<float >*|*~");
    TEST_c2py_matFloatX<sstd::mat_r<double>, double>(tmpDir, fileName, "mat_r<double>, ret mat_r<double>*, mat_r<double>", "void, const mat_r<double>*", "void, mat_r<double>*", "void, mat_r<double>*|~", "void, mat_r<double>*|*~");
    
    TEST_c2py_matStr<sstd::mat_r<std::string>>(tmpDir, fileName, "mat_r<str>, ret mat_r<str>*, mat_r<str>*", "void, const mat_r<str>*", "void, mat_r<str>*",    "void, mat_r<str>*|~",    "void, mat_r<str>*|*~");
    // "mat<str>, mat<str>" は，C++ の可変長引数で受け渡そうとすると，segmentation fault で落ちる．少なくとも gcc 5.4.0 では対応していないので，ポインタで渡しておく．
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
//*
// 実装完了 (処理時間短縮のため，コメントアウト)

void TEST__c2py__return_null(){
    const char* tmpDir   = "./tmpDir";
    const char* fileName = "test/c2py_t";
    {
        // "return []"
        sstd::c2py<std::vector<char>> pyFn(tmpDir, fileName, "py_vec_return_null", "vec<char>");
        std::vector<char> ret;
        ret = pyFn();
    }
    {
        // "return [[]]"
        sstd::c2py<sstd::mat_c<char>> pyFn(tmpDir, fileName, "py_mat_return_null", "mat_c<char>");
        sstd::mat_c<char> ret;
        ret = pyFn();
    }
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------

void TEST__c2py__sample_codes(){
    const char* tmpDir   = "./tmpDir";
    const char* fileName = "test/c2py_t";
    {
        //         int                          plusAandB(int a, int b){ return a+b; } // <- you can write this as a python function.
        sstd::c2py<int32> plus_A_B(tmpDir, fileName, "plus_A_B", "int32, int32, int32");
        int32 a = 1, b = 2;
        int32 c = plus_A_B(a, b);
        
        ASSERT_TRUE(c==(a+b));
    }
    {
        sstd::c2py<std::vector<double>> plus_vecA_vecB(tmpDir, fileName, "plus_vecA_vecB", "vec<double>, vec<double>, vec<double>");
        std::vector<double> vecA = {1.0, 2.0, 3.0}, vecB = {4.0, 5.0, 6.0};
        std::vector<double> vecC = plus_vecA_vecB(vecA, vecB);
        
        ASSERT_TRUE(vecC==(vecA+vecB));
    }
    {
        // write back test
        //    sstd::c2py<int> writeBack_vecA(tmpDir, fileName, "writeBack_vecA", "int, const vec<double>*"); // const assignment will not be written back.
        //    sstd::c2py<int> writeBack_vecA(tmpDir, fileName, "writeBack_vecA", "int, vec<double>*");
        sstd::c2py<int> writeBack_vecA(tmpDir, fileName, "writeBack_vecA", "int, vec<double>*");
        std::vector<double> vecA = {1.0, 2.0, 3.0};
        std::vector<double> ans  = {9.0, 9.0, 9.0};
        
        int ret = writeBack_vecA(&vecA);
        
        ASSERT_TRUE(ret==0.0);
        ASSERT_TRUE(vecA==ans);
    }
    //---
    {
        // Because of numpy array is a row-major matrix, passing col-major matrix will be converted to a row-major matrix on python side.
//        sstd::mat_c<double> matA{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}, {11.0, 12.0, 13.0}};
//        sstd::printn(matA);
//        sstd::c2py<int> mat2print(tmpDir, fileName, "mat2print", "int, mat_c<double>");
//        mat2print(matA);
    }
    {
//        sstd::mat_r<double> mat_rA{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}, {11.0, 12.0, 13.0}};
//        sstd::printn(mat_rA);
//        sstd::c2py<int> mat_r2print(tmpDir, fileName, "mat_r2print", "int, mat_r<double>");
//        mat_r2print(mat_rA);
    }
    {
        sstd::mat_c<double> matA{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}, {11.0, 12.0, 13.0}};
        sstd::c2py<sstd::mat_c<double>> ret_mat(tmpDir, fileName, "ret_mat", "mat_c<double>, mat_c<double>");
        
        sstd::mat_c<double> ret = ret_mat(matA);
        
        ASSERT_TRUE(ret==matA);
    }
    {
        sstd::mat_r<double> mat_rA{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}, {11.0, 12.0, 13.0}};
        sstd::c2py<sstd::mat_r<double>> ret_mat_r(tmpDir, fileName, "ret_mat_r", "mat_r<double>, mat_r<double>");
        
        sstd::mat_r<double> ret = ret_mat_r(mat_rA);
        
        ASSERT_TRUE(ret==mat_rA);
    }
    //---
    {
        sstd::c2py<void> py_vecDouble_cnv2builtIn(tmpDir, fileName, "py_vecDouble_cnv2builtIn", "void, vec<double>*|~");
        std::vector<double> inOut={1.0, 2.0, 3.0};
        std::vector<double> ans=inOut; ans<<=88.0;
        
        py_vecDouble_cnv2builtIn(&inOut);
        
        ASSERT_TRUE(inOut==ans);
    }
    {
        sstd::c2py<void> py_vecDouble_pointer(tmpDir, fileName, "py_vecDouble_pointer", "void, vec<double>*|*");
        std::vector<double> inOut={1.0, 2.0, 3.0};
        std::vector<double> ans=inOut; ans<<=88.0;
        
        py_vecDouble_pointer(&inOut);
        
        ASSERT_TRUE(inOut==ans);
    }
    //---
    {
        sstd::c2py<void> py_ret(tmpDir, fileName, "py_ret", "void, ret double*, ret double*, len, ret vec<double>*, vec<double>*|*~");
        double ret1=0.0;
        double ret2[]={0.0, 0.0};
        std::vector<double> ret3;
        std::vector<double> inOut={0.0};
        
        py_ret(&ret1, &ret2, 2, &ret3, &inOut);
        
        ASSERT_TRUE(ret1==1.0);
        ASSERT_TRUE(ret2[0]==2.0);
        ASSERT_TRUE(ret2[1]==3.0);
        ASSERT_TRUE(ret3==std::vector<double>({4.0, 5.0, 6.0, 7.0}));
    }
    //---
    {
        double freq_generate = 0.1; // 0.1 Hz sin wave
        double freq_sample = 10;    // 10 Hz sampling
        uint len=60*10 + 1;         // 60 sec
        std::vector<double> vecY = sstd::sinWave(freq_generate, freq_sample, len);
        std::vector<double> vecX(len); for(uint i=0; i<vecX.size(); ++i){ vecX[i]=(double)i*(1/freq_sample); }
        
        sstd::c2py<void> vec2graph(tmpDir, fileName, "vec2graph", "void, const char*, vec<double>, vec<double>");
        vec2graph("./sin.png", vecX, vecY);
    }
    //---
    {
        double freq_generate = 0.1; // 0.1 Hz sin wave
        double freq_sample = 10;    // 10 Hz sampling
        uint len=60*10 + 1;         // 60 sec
        std::vector<double> sinY = sstd::sinWave(freq_generate, freq_sample, len);
        std::vector<double> sinX(len); for(uint i=0; i<sinX.size(); ++i){ sinX[i]=(double)i*(1/freq_sample); }
        
        std::vector<double> cosY = sstd::cosWave(freq_generate, freq_sample, len);
        std::vector<double> cosX(len); for(uint i=0; i<cosX.size(); ++i){ cosX[i]=(double)i*(1/freq_sample); }
        
        std::vector<std::string> vLabel={"sin", "cos", "-cos"};
        std::vector<std::vector<double>> vvecX={sinX, cosX,    cosX};
        std::vector<std::vector<double>> vvecY={sinY, cosY, -1*cosY};
        
        sstd::c2py<void> vvec2graph(tmpDir, fileName, "vvec2graph", "void, const char*, const vec<str>*, const vvec<double>*, const vvec<double>*");
        vvec2graph("./sin_cos.png", &vLabel, &vvecX, &vvecY);
    }
    //---
    {
        sstd::c2py<void> imgPath2mat_rRGB(tmpDir, fileName, "imgPath2mat_rRGB", "void, ret mat_r<uint8>*, ret mat_r<uint8>*, ret mat_r<uint8>*, const char*");
        sstd::mat_r<uint8> imgR, imgG, imgB;
        imgPath2mat_rRGB(&imgR, &imgG, &imgB, "./test/test.png");
        
        for(uint p=0; p<imgG.rows(); ++p){
            for(uint q=0; q<imgG.cols(); ++q){
                imgG(p, q) = sstd::round2even(0.5*((double)imgG(p, q)));
            }
        }
        
        sstd::c2py<void> mat_rRGB2img(tmpDir, fileName, "mat_rRGB2img", "void, const char*, mat_r<uint8>*, mat_r<uint8>*, mat_r<uint8>*");
        mat_rRGB2img("./test_reCombined.png", &imgR, &imgG, &imgB);
    }
    //---
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
void TEST_c2py_vvecFolatXX(const char* tmpDir,
                           const char* fileName,
                           const char* fmt_0, const char* fmt_1, const char* fmt_2, const char* fmt_3, const char* fmt_4, const char* fmt_5
                           )
{
    const std::vector<std::vector<T>> vvecIn={{-1.23, 4.56}, {0, 1, 2}, {}, {3, 4}, {}};
    std::vector<std::vector<T>> vvecIn_WB=vvecIn; vvecIn_WB[0].resize(1); vvecIn_WB[0][0]=(T)999; vvecIn_WB<<=std::vector<T>{(T)88};
    
    std::string ans          = vvec2ansStr(vvecIn   );
    std::string ans_WB       = vvec2ansStr(vvecIn_WB);
    std::string ans_plus     = ans + ans_WB;
    std::string ans_withType = num2typeNameInPython(vvecIn[0][0])+"\n" + ans;
    {
        // vvec<T>, ret vvec<T>*, vvec<T>
        sstd::c2py<std::vector<std::vector<T>>> pyFn(tmpDir, fileName, "py_vvecFloatX", fmt_0);
        std::vector<std::vector<T>> ret0, ret1;
        std::vector<std::vector<T>> vvecIn_buf = vvecIn;
        
        testing::internal::CaptureStdout();
        ret0 = pyFn(&ret1, vvecIn_buf);
        ASSERT_STREQ(ans_withType.c_str(), testing::internal::GetCapturedStdout().c_str());
        
        const std::vector<std::vector<T>> ansRet0=vvecIn;
        const std::vector<std::vector<T>> ansRet1={{0},{1}};
        ASSERT_TRUE(ret0==ansRet0);
        ASSERT_TRUE(ret1==ansRet1);
    }
    {
        // "void, const vvec<T>*"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVvecFloat_const", fmt_1); // Not writing back
        std::vector<std::vector<T>> vvecIn_buf = vvecIn;
        
        testing::internal::CaptureStdout();
        pyFn(&vvecIn_buf);
        ASSERT_STREQ(ans.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(vvecIn_buf==vvecIn);
    }
    {
        // "void, vvec<T>*"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVvecFloat", fmt_2); // Writing back
        std::vector<std::vector<T>> vvecIn_buf = vvecIn;
        
        testing::internal::CaptureStdout();
        pyFn(&vvecIn_buf); // ndarray で渡した場合は，追記できない
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(vvecIn_buf==vvecIn_WB);
    }
    //---
    {
        // "void, vvec<T>*|~"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVvecFloat", fmt_3); // Writing back
        std::vector<std::vector<T>> vvecIn_buf = vvecIn;
        
        testing::internal::CaptureStdout();
        pyFn(&vvecIn_buf); // ndarray で渡した場合は，追記できない
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(vvecIn_buf==vvecIn_WB);
    }
    {
        // "void, vvec<T>*|*~"
        sstd::c2py<void> pyFn(tmpDir, fileName, "py_pVvecFloat_pCnvBuiltin", fmt_4); // Writing back
        std::vector<std::vector<T>> vvecIn_buf = vvecIn;
        
        testing::internal::CaptureStdout();
        pyFn(&vvecIn_buf); // ndarray で渡した場合は，追記できない
        ASSERT_STREQ(ans_plus.c_str(), testing::internal::GetCapturedStdout().c_str());
        ASSERT_TRUE(vvecIn_buf==vvecIn_WB);
    }
}
//---
void TEST__c2py__vvec_builtin(){
    const char* tmpDir   = "./tmpDir";
    const char* fileName = "test/c2py_t";
    
// not implimented
// not implimented
// not implimented
// not implimented
//    TEST_c2py_vvecIntegerXX<uchar >(tmpDir, fileName, "vvec <uchar>, ret vvec <uchar>*, vvec <uchar>", "void, const vvec <uchar>*", "void, vvec< uchar>*", "void, vvec <uchar>*|~", "void, vvec <uchar>*|*~", "void, vvec <uchar>*|*");
//    TEST_c2py_vvecIntegerXX< int8 >(tmpDir, fileName, "vvec< int8 >, ret vvec< int8 >*, vvec< int8 >", "void, const vvec< int8 >*", "void, vvec< int8 >*", "void, vvec< int8 >*|~", "void, vvec< int8 >*|*~", "void, vvec< int8 >*|*");
//    TEST_c2py_vvecIntegerXX< int16>(tmpDir, fileName, "vvec< int16>, ret vvec< int16>*, vvec< int16>", "void, const vvec< int16>*", "void, vvec< int16>*", "void, vvec< int16>*|~", "void, vvec< int16>*|*~", "void, vvec< int16>*|*");
//    TEST_c2py_vvecIntegerXX< int32>(tmpDir, fileName, "vvec< int32>, ret vvec< int32>*, vvec< int32>", "void, const vvec< int32>*", "void, vvec< int32>*", "void, vvec< int32>*|~", "void, vvec< int32>*|*~", "void, vvec< int32>*|*");
//    TEST_c2py_vvecIntegerXX< int64>(tmpDir, fileName, "vvec< int64>, ret vvec< int64>*, vvec< int64>", "void, const vvec< int64>*", "void, vvec< int64>*", "void, vvec< int64>*|~", "void, vvec< int64>*|*~", "void, vvec< int64>*|*");
//    TEST_c2py_vvecIntegerXX<uint8 >(tmpDir, fileName, "vvec<uint8 >, ret vvec<uint8 >*, vvec<uint8 >", "void, const vvec<uint8 >*", "void, vvec<uint8 >*", "void, vvec<uint8 >*|~", "void, vvec<uint8 >*|*~", "void, vvec<uint8 >*|*");
//    TEST_c2py_vvecIntegerXX<uint16>(tmpDir, fileName, "vvec<uint16>, ret vvec<uint16>*, vvec<uint16>", "void, const vvec<uint16>*", "void, vvec<uint16>*", "void, vvec<uint16>*|~", "void, vvec<uint16>*|*~", "void, vvec<uint16>*|*");
//    TEST_c2py_vvecIntegerXX<uint32>(tmpDir, fileName, "vvec<uint32>, ret vvec<uint32>*, vvec<uint32>", "void, const vvec<uint32>*", "void, vvec<uint32>*", "void, vvec<uint32>*|~", "void, vvec<uint32>*|*~", "void, vvec<uint32>*|*");
//    TEST_c2py_vvecIntegerXX<uint64>(tmpDir, fileName, "vvec<uint64>, ret vvec<uint64>*, vvec<uint64>", "void, const vvec<uint64>*", "void, vvec<uint64>*", "void, vvec<uint64>*|~", "void, vvec<uint64>*|*~", "void, vvec<uint64>*|*");
    
//    TEST_c2py_vvecFolatXX<float> (tmpDir, fileName, "vvec< float>, ret vvec< float>*, vvec< float>", "void, const vvec< float>*", "void, vvec< float>*", "void, vvec< float>*|~", "void, vvec< float>*|*~", "void, vvec< float>*|*");
    TEST_c2py_vvecFolatXX<double>(tmpDir, fileName, "vvec<double>, ret vvec<double>*, vvec<double>", "void, const vvec<double>*", "void, vvec<double>*", "void, vvec<double>*|~", "void, vvec<double>*|*~", "void, vvec<double>*|*");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
//*
TEST(c2py, empty_args             ){ TEST__c2py__empty_args();           }
TEST(c2py, empty_args__other_dir  ){ TEST__c2py__empty_args__same_dir(); }
TEST(c2py, bench_withoutInit      ){ TEST__c2py__bench_withoutInit();    }
TEST(c2py, bench_withInit         ){ TEST__c2py__bench_withInit();       }
TEST(c2py, builIn_bool            ){ TEST__c2py__builIn_bool();          }
TEST(c2py, builIn_char            ){ TEST__c2py__builIn_char();          }
TEST(c2py, builtIn_num            ){ TEST__c2py__builtIn_num();          }
TEST(c2py, str                    ){ TEST__c2py__str();                  }
TEST(c2py, vec_bool               ){ TEST__c2py__vec_bool();             }
TEST(c2py, vec_char               ){ TEST__c2py__vec_char();             }
TEST(c2py, vec_builtin            ){ TEST__c2py__vec_builtin();          }
TEST(c2py, vec_str                ){ TEST__c2py__vec_str();              }
TEST(c2py, mat_c                  ){ TEST__c2py__mat_c();                }
TEST(c2py, mat_r                  ){ TEST__c2py__mat_r();                }
TEST(c2py, return_null            ){ TEST__c2py__return_null();          }
TEST(c2py, sample_codes           ){ TEST__c2py__sample_codes();         }
//*/

//TEST(c2py, vvec_bool              ){ TEST__c2py__vvec_bool();          } // not implimented
//TEST(c2py, vvec_char              ){ TEST__c2py__vvec_char();          } // not implimented
TEST(c2py, vvec_builtin           ){ TEST__c2py__vvec_builtin();        } // under construction #################
//TEST(c2py, vvec_str               ){ TEST__c2py__vvec_str();           } // not implimented

//-----------------------------------------------------------------------------------------------------------------------------------------------

