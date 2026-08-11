#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(duplicated, duplicated_key_cnt){
    std::vector<std::string> vs = {"0", "0", "0", "1", "2", "3", "3"};

    std::vector<std::tuple<std::string,uint>> vDuplicated_key_cnt = sstd::duplicated_key_cnt(vs);

    sstd::sort( vDuplicated_key_cnt );
    ASSERT_EQ(vDuplicated_key_cnt.size(), (uint)2);
    ASSERT_EQ( std::get<0>(vDuplicated_key_cnt[0]), "0");
    ASSERT_EQ( std::get<1>(vDuplicated_key_cnt[0]), (uint)3 );
    ASSERT_EQ( std::get<0>(vDuplicated_key_cnt[1]), "3");
    ASSERT_EQ( std::get<1>(vDuplicated_key_cnt[1]), (uint)2 );
}
TEST(duplicated, use_case_of_duplicated_key_cnt){
    std::vector<char> vTEXT;
    for(uint i=0; (uint)'a'+i<=(uint)'z'; ++i){ vTEXT.push_back( 'a'+i ); }
//    sstd::printn_all(vTEXT);

    std::string text = "exampletext"; // some of large data
    std::vector<uint> vIdx; // the index for the large data
    for(uint i=0; i<text.size(); ++i){ vIdx.push_back(text[i]-'a'); }
//    sstd::printn_all(vIdx);
    
    std::vector<std::tuple<uint,uint>> vDuplicated_key_cnt = sstd::duplicated_key_cnt(vIdx);
    sstd::sort( vDuplicated_key_cnt );

//    sstd::printn_all( vDuplicated_key_cnt );
    uint idx_1 = std::get<0>( vDuplicated_key_cnt[0] ); // key as an index
    uint cnt_1 = std::get<1>( vDuplicated_key_cnt[0] );
    uint idx_2 = std::get<0>( vDuplicated_key_cnt[1] ); // key as an index
    uint cnt_2 = std::get<1>( vDuplicated_key_cnt[1] );
    uint idx_3 = std::get<0>( vDuplicated_key_cnt[2] ); // key as an index
    uint cnt_3 = std::get<1>( vDuplicated_key_cnt[2] );

    std::string msg;
    msg += vTEXT[idx_1];
    msg += std::to_string(cnt_1);
    msg += ",";
    msg += vTEXT[idx_2];
    msg += std::to_string(cnt_2);
    msg += ",";
    msg += vTEXT[idx_3];
    msg += std::to_string(cnt_3);
//    sstd::printn_all(msg);
    
    ASSERT_STREQ(msg.c_str(), "e3,t2,x2");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
