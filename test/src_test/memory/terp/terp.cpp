#include <sstd/sstd.hpp>
#include "../../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::var
//*
TEST(memory_terp, var_constructor){
    sstd::terp::var a;
}
TEST(memory_terp, var_ope_assign_str){
    sstd::terp::var a;
    a = "test";
    ASSERT_STREQ(a.to<std::string>().c_str(), "test");
}
TEST(memory_terp, var_ope_assign_list){
    sstd::terp::var a;
    a = sstd::terp::list(1);
    a[0] = "test"; // TEST THIS LINE
    
    ASSERT_STREQ(a[0].to<std::string>().c_str(), "test");
}
TEST(memory_terp, var_ope_assign_list_case02){
    sstd::terp::var a;
    a = sstd::terp::list();
    a.resize(1);
    a[0] = "test"; // TEST THIS LINE
    
    ASSERT_STREQ(a[0].to<std::string>().c_str(), "test");
}

// typeNum()
TEST(memory_terp, var_typeNum_null){
    sstd::terp::var a;
    ASSERT_STREQ(sstd::typeNum2str(a.typeNum()).c_str(), "null"); // TEST THIS LINE
}
TEST(memory_terp, var_typeNum_c){
    sstd::terp::var a;
    a = "test";
    ASSERT_STREQ(sstd::typeNum2str(a.typeNum()).c_str(), "str"); // TEST THIS LINE
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::list
//*

// operator=
TEST(memory_terp, list_ope_assign){
    sstd::terp::var a;
    a = sstd::terp::list(1); // TEST THIS LINE
    //a = sstd::terp::list(); a.resize(1); // same as above
    a[0] = sstd::terp::list(); // TEST THIS LINE
    a[0].push_back("v1");
    a[0].push_back("v2");
    
    ASSERT_STREQ(a[0][0].to<std::string>().c_str(), "v1");
    ASSERT_STREQ(a[0][1].to<std::string>().c_str(), "v2");
}

// operator==
TEST(memory_terp, list_ope_eq_true_type){
    sstd::terp::var lhs; lhs = sstd::terp::list();
    sstd::terp::var rhs; rhs = sstd::terp::list();
    ASSERT_TRUE(lhs==rhs); // TEST THIS LINE
}
TEST(memory_terp, list_ope_eq_true_size_0){
    sstd::terp::var lhs; lhs = sstd::terp::list(0);
    sstd::terp::var rhs; rhs = sstd::terp::list(0);
    ASSERT_TRUE(lhs==rhs); // TEST THIS LINE
}
TEST(memory_terp, list_ope_eq_true_size_3){
    sstd::terp::var lhs; lhs = sstd::terp::list(3);
    sstd::terp::var rhs; rhs = sstd::terp::list(3);
    ASSERT_TRUE(lhs==rhs); // TEST THIS LINE
}
TEST(memory_terp, list_ope_eq_true){
    sstd::terp::var lhs;
    lhs = sstd::terp::list(3);
    lhs[0] = "v0";
    lhs[1] = "v1";
    lhs[2] = "v2";

    sstd::terp::var rhs;
    rhs = sstd::terp::list(3);
    rhs[0] = "v0";
    rhs[1] = "v1";
    rhs[2] = "v2";

    ASSERT_TRUE(lhs==rhs); // TEST THIS LINE
}
TEST(memory_terp, list_ope_eq_false_type){
    sstd::terp::var lhs; lhs = sstd::terp::list();
    sstd::terp::var rhs; rhs = sstd::terp::hash();
    ASSERT_FALSE(lhs==rhs); // TEST THIS LINE
}
TEST(memory_terp, list_ope_eq_false_size){
    sstd::terp::var lhs; lhs = sstd::terp::list(0);
    sstd::terp::var rhs; rhs = sstd::terp::list(3);
    ASSERT_FALSE(lhs==rhs); // TEST THIS LINE
}
TEST(memory_terp, list_ope_eq_false){
    sstd::terp::var lhs;
    lhs = sstd::terp::list(3);
    lhs[0] = "v0";
    lhs[1] = "v1";
    lhs[2] = "v2";

    sstd::terp::var rhs;
    rhs = sstd::terp::list(3);
    rhs[0] = "v0";
    rhs[1] = "v1";
    rhs[2] = "NotEqualStr";

    ASSERT_FALSE(lhs==rhs); // TEST THIS LINE
}

// operator!=
TEST(memory_terp, list_ope_neq){
    sstd::terp::var lhs; lhs = sstd::terp::list();
    sstd::terp::var rhs; rhs = sstd::terp::list();
    ASSERT_FALSE(lhs!=rhs); // TEST THIS LINE
}

// begin(), end()
TEST(memory_terp, list_begin_end){
    sstd::terp::var a;
    
    auto tmp_b = a.begin();
    auto tmp_e = a.end();
}
TEST(memory_terp, list_begin_end_with_objects){
    sstd::terp::var a;
    a = sstd::terp::list(3);
    a[0] = "v0";
    a[1] = "v1";
    a[2] = "v2";

    std::vector<std::string> v_ret;

    for(auto itr=a.begin(); itr!=a.end(); ++itr){      // TEST THIS LINE
        std::string tmp = itr.first_to<std::string>(); // TEST THIS LINE
        v_ret.push_back(tmp);
    }
    
    ASSERT_STREQ(v_ret[0].c_str(), "v0");
    ASSERT_STREQ(v_ret[1].c_str(), "v1");
    ASSERT_STREQ(v_ret[2].c_str(), "v2");
}

// erase()
TEST(memory_terp, list_erase){
    sstd::terp::var a;
    a = sstd::terp::list(3);
    a[0] = "v0";
    a[1] = "v1";
    a[2] = "v2";

    a.erase(a.begin()); // erase 'a[0] = "v0";' // TEST THIS LINE
    //a.erase(a.begin()+1); // erase 'a[1] = "v1";'

    ASSERT_EQ(a.size(), (uint)2);
    ASSERT_STREQ(a[0].to<std::string>().c_str(), "v1");
    ASSERT_STREQ(a[1].to<std::string>().c_str(), "v2");
}
TEST(memory_terp, list_erase_index){
    sstd::terp::var a;
    a = sstd::terp::list(3);
    a[0] = "v0";
    a[1] = "v1";
    a[2] = "v2";

    //a.erase(a.begin()); // erase 'a[0] = "v0";'
    a.erase(a.begin()+1); // erase 'a[1] = "v1";' // TEST THIS LINE

    ASSERT_EQ(a.size(), (uint)2);
    ASSERT_STREQ(a[0].to<std::string>().c_str(), "v0");
    ASSERT_STREQ(a[1].to<std::string>().c_str(), "v2");
}

// pop_back()
TEST(memory_terp, list_pop_back){
    sstd::terp::var a;
    a = sstd::terp::list(3);
    a[0] = "v0";
    a[1] = "v1";
    a[2] = "v2";

    a.pop_back(); // TEST THIS LINE

    ASSERT_EQ(a.size(), (uint)2);
    ASSERT_STREQ(a[0].to<std::string>().c_str(), "v0");
    ASSERT_STREQ(a[1].to<std::string>().c_str(), "v1");
}

// push_back()
TEST(memory_terp, list_push_back_c){
    sstd::terp::var a;
    a = sstd::terp::list();
    a.push_back("test"); // TEST THIS LINE
    
    ASSERT_STREQ(a[0].to<std::string>().c_str(), "test");
}
TEST(memory_terp, list_push_back_list){
    // -
    //   - v1
    //   - v2
    
    sstd::terp::var a;
    a = sstd::terp::list();
    a.push_back(sstd::terp::list()); // TEST THIS LINE
    a[0].push_back("v1");
    a[0].push_back("v2");
    
    ASSERT_STREQ(a[0][0].to<std::string>().c_str(), "v1");
    ASSERT_STREQ(a[0][1].to<std::string>().c_str(), "v2");
}

// resize()
TEST(memory_terp, list_resize){
    sstd::terp::var a;
    a = sstd::terp::list();
    ASSERT_EQ(a.size(), (uint)0);
    a.resize(10);
    ASSERT_EQ(a.size(), (uint)10);
}

// size()
TEST(memory_terp, list_size_arg_null){
    sstd::terp::var a;
    a = sstd::terp::list();
    ASSERT_EQ(a.size(), (uint)0);
}
TEST(memory_terp, list_size_arg_10){
    sstd::terp::var a;
    a = sstd::terp::list(10);
    ASSERT_EQ(a.size(), (uint)10);
}

// typeNum()
TEST(memory_terp, list_typeNum){
    sstd::terp::var a;
    a = sstd::terp::list();
    ASSERT_STREQ(sstd::typeNum2str(a.typeNum()).c_str(), "vec_void_ptr"); // TEST THIS LINE
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::hash
//*
// operator=
TEST(memory_terp, hash_ope_assign){
    sstd::terp::var a;
    a = sstd::terp::hash(0); // TEST THIS LINE
    a["k1"] = sstd::terp::hash(); // TEST THIS LINE
    a["k1"]["k11"] = "v1";
    a["k1"]["k12"] = "v2";
    
    ASSERT_STREQ(a["k1"]["k11"].to<std::string>().c_str(), "v1");
    ASSERT_STREQ(a["k1"]["k12"].to<std::string>().c_str(), "v2");
}

// operator==
TEST(memory_terp, hash_ope_eq_true_type){
    sstd::terp::var lhs; lhs = sstd::terp::hash();
    sstd::terp::var rhs; rhs = sstd::terp::hash();
    ASSERT_TRUE(lhs==rhs); // TEST THIS LINE
}
TEST(memory_terp, hash_ope_eq_true_0_keys){
    sstd::terp::var lhs; lhs = sstd::terp::hash();
    sstd::terp::var rhs; rhs = sstd::terp::hash();
    ASSERT_TRUE(lhs==rhs); // TEST THIS LINE
}
TEST(memory_terp, hash_ope_eq_true_3_keys){
    sstd::terp::var lhs; lhs = sstd::terp::hash();
    sstd::terp::var rhs; rhs = sstd::terp::hash();
    lhs["k1"] = "v1";
    lhs["k2"] = "v2";
    lhs["k3"] = "v3";
    
    rhs["k1"] = "v1";
    rhs["k2"] = "v2";
    rhs["k3"] = "v3";
    
    ASSERT_TRUE(lhs==rhs); // TEST THIS LINE
}
/*
TEST(memory_terp, hash_ope_eq_true){
    sstd::terp::var lhs;
    lhs = sstd::terp::list(3);
    lhs[0] = "v0";
    lhs[1] = "v1";
    lhs[2] = "v2";

    sstd::terp::var rhs;
    rhs = sstd::terp::list(3);
    rhs[0] = "v0";
    rhs[1] = "v1";
    rhs[2] = "v2";

    ASSERT_TRUE(lhs==rhs); // TEST THIS LINE
}
*/
TEST(memory_terp, hash_ope_eq_false_type){
    sstd::terp::var lhs; lhs = sstd::terp::list();
    sstd::terp::var rhs; rhs = sstd::terp::hash();
    ASSERT_FALSE(lhs==rhs); // TEST THIS LINE
}
TEST(memory_terp, hash_ope_eq_false_2_3_keys){
    sstd::terp::var lhs; lhs = sstd::terp::hash();
    sstd::terp::var rhs; rhs = sstd::terp::hash();
    lhs["k1"] = "v1";
    lhs["k2"] = "v2";
    lhs["k3"] = "v3";
    
    rhs["k1"] = "v1";
    rhs["k2"] = "v2";
    
    ASSERT_FALSE(lhs==rhs); // TEST THIS LINE
}
/*
TEST(memory_terp, hash_ope_eq_false){
    sstd::terp::var lhs;
    lhs = sstd::terp::list(3);
    lhs[0] = "v0";
    lhs[1] = "v1";
    lhs[2] = "v2";

    sstd::terp::var rhs;
    rhs = sstd::terp::list(3);
    rhs[0] = "v0";
    rhs[1] = "v1";
    rhs[2] = "NotEqualStr";

    ASSERT_FALSE(lhs==rhs); // TEST THIS LINE
}
*/

// begin(), end()
TEST(memory_terp, hash_begin_end_with_objects){
    sstd::terp::var a;
    a = sstd::terp::hash();
    a["k0"] = "v0";
    a["k1"] = "v1";
    a["k2"] = "v2";

    std::vector<std::string> v_key;
    std::vector<std::string> v_val;

    for(auto itr=a.begin(); itr!=a.end(); ++itr){      // TEST THIS LINE
        std::string key = itr.first_to<std::string>(); // TEST THIS LINE
        std::string val = itr.second_to<std::string>(); // TEST THIS LINE
        v_key.push_back(key);
        v_val.push_back(val);
    }
    
    ASSERT_STREQ(v_key[0].c_str(), "k2");
    ASSERT_STREQ(v_key[1].c_str(), "k1");
    ASSERT_STREQ(v_key[2].c_str(), "k0");
    ASSERT_STREQ(v_val[0].c_str(), "v2");
    ASSERT_STREQ(v_val[1].c_str(), "v1");
    ASSERT_STREQ(v_val[2].c_str(), "v0");
}

// erase()
TEST(memory_terp, hash_erase){
    sstd::terp::var a;
    a = sstd::terp::hash();
    a["k0"] = "v0";
    a["k1"] = "v1";
    a["k2"] = "v2";

    a.erase("k1"); // TEST THIS LINE

    std::vector<std::string> v_key;
    std::vector<std::string> v_val;

    for(auto itr=a.begin(); itr!=a.end(); ++itr){       // TEST THIS LINE
        std::string key = itr.first_to <std::string>(); // TEST THIS LINE
        std::string val = itr.second_to<std::string>(); // TEST THIS LINE
        v_key.push_back(key);
        v_val.push_back(val);
    }
    
    ASSERT_STREQ(v_key[0].c_str(), "k2");
    ASSERT_STREQ(v_key[1].c_str(), "k0");
    ASSERT_STREQ(v_val[0].c_str(), "v2");
    ASSERT_STREQ(v_val[1].c_str(), "v0");
}

// find()
TEST(memory_terp, hash_find_true){
    sstd::terp::var a;
    a = sstd::terp::hash();
    a["k0"] = "v0";

    auto itr = a.find("k0"); // TEST THIS LINE
    ASSERT_TRUE( itr!=a.end() );
    
    ASSERT_STREQ(itr.first_to<std::string>().c_str(),  "k0");
    ASSERT_STREQ(itr.second_to<std::string>().c_str(), "v0");
}
TEST(memory_terp, hash_find_false){
    sstd::terp::var a;
    a = sstd::terp::hash();

    auto itr = a.find("k0"); // TEST THIS LINE
    ASSERT_FALSE( itr!=a.end() );
}

// size()
TEST(memory_terp, hash_size_arg_null){
    sstd::terp::var a;
    a = sstd::terp::hash();
    ASSERT_EQ(a.size(), (uint)0);
    
    a["k1"] = "v1"; // TEST THIS LINE
    
    ASSERT_EQ(a.size(), (uint)1);
    ASSERT_STREQ(a["k1"].to<std::string>().c_str(), "v1");
}
TEST(memory_terp, hash_size_arg_14){
    sstd::terp::var a;
    a = sstd::terp::hash(14);
    ASSERT_EQ(a.bucket_count(), (uint)17); // std::unordered_map allocates the prime number size, equal or nearest larger than the allocating size.
}

// typeNum()
TEST(memory_terp, hash_typeNum){
    sstd::terp::var a;
    a = sstd::terp::hash();
    ASSERT_STREQ(sstd::typeNum2str(a.typeNum()).c_str(), "hash_str_void_ptr"); // TEST THIS LINE
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
