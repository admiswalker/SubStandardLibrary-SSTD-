#pragma once


std::string vecUint8_to_hexString(std::vector<uint8>& rhs){
    std::string ret;
    for(uint i=0; i<rhs.size(); i++){
        ret += sstd::ssprintf("%.2x", rhs[i]);
    }
    return ret;
}

TEST(hashFnc_of_MD5_SHA1_SHA2, md5){
    const char* pFilePath = "./test/test.png";
    std::vector<uint8> data = sstd::read_bin(pFilePath);
    
    std::vector<uint8> hash = sstd::md5(data);
    std::string s = vecUint8_to_hexString(hash);
    
    std::string hash_ans_s = sstd::system_stdout(sstd::ssprintf("md5sum %s | cut -d ' ' -f 1", pFilePath)); sstd::stripAll_ow(hash_ans_s, "\r\n");
    ASSERT_STREQ(s.c_str(), hash_ans_s.c_str());
}
TEST(hashFnc_of_MD5_SHA1_SHA2, sha1){
    const char* pFilePath = "./test/test.png";
    std::vector<uint8> data = sstd::read_bin(pFilePath);
    
    std::vector<uint8> hash = sstd::sha1(data);
    std::string s = vecUint8_to_hexString(hash);
    
    std::string hash_ans_s = sstd::system_stdout(sstd::ssprintf("sha1sum %s | cut -d ' ' -f 1", pFilePath)); sstd::stripAll_ow(hash_ans_s, "\r\n");
    ASSERT_STREQ(s.c_str(), hash_ans_s.c_str());
}
TEST(hashFnc_of_MD5_SHA1_SHA2, sha224){
    const char* pFilePath = "./test/test.png";
    std::vector<uint8> data = sstd::read_bin(pFilePath);
    
    std::vector<uint8> hash = sstd::sha224(data);
    std::string s = vecUint8_to_hexString(hash);
    
    std::string hash_ans_s = sstd::system_stdout(sstd::ssprintf("sha224sum %s | cut -d ' ' -f 1", pFilePath)); sstd::stripAll_ow(hash_ans_s, "\r\n");
    ASSERT_STREQ(s.c_str(), hash_ans_s.c_str());
}
TEST(hashFnc_of_MD5_SHA1_SHA2, sha256){
    const char* pFilePath = "./test/test.png";
    std::vector<uint8> data = sstd::read_bin(pFilePath);
    
    std::vector<uint8> hash = sstd::sha256(data);
    std::string s = vecUint8_to_hexString(hash);
    
    std::string hash_ans_s = sstd::system_stdout(sstd::ssprintf("sha256sum %s | cut -d ' ' -f 1", pFilePath)); sstd::stripAll_ow(hash_ans_s, "\r\n");
    ASSERT_STREQ(s.c_str(), hash_ans_s.c_str());
}
TEST(hashFnc_of_MD5_SHA1_SHA2, sha384){
    const char* pFilePath = "./test/test.png";
    std::vector<uint8> data = sstd::read_bin(pFilePath);
    
    std::vector<uint8> hash = sstd::sha384(data);
    std::string s = vecUint8_to_hexString(hash);
    
    std::string hash_ans_s = sstd::system_stdout(sstd::ssprintf("sha384sum %s | cut -d ' ' -f 1", pFilePath)); sstd::stripAll_ow(hash_ans_s, "\r\n");
    ASSERT_STREQ(s.c_str(), hash_ans_s.c_str());
}
TEST(hashFnc_of_MD5_SHA1_SHA2, sha512){
    const char* pFilePath = "./test/test.png";
    std::vector<uint8> data = sstd::read_bin(pFilePath);
    
    std::vector<uint8> hash = sstd::sha512(data);
    std::string s = vecUint8_to_hexString(hash);
    
    std::string hash_ans_s = sstd::system_stdout(sstd::ssprintf("sha512sum %s | cut -d ' ' -f 1", pFilePath)); sstd::stripAll_ow(hash_ans_s, "\r\n");
    ASSERT_STREQ(s.c_str(), hash_ans_s.c_str());
}
