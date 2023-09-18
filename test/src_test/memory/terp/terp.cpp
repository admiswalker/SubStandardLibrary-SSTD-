#include <sstd/sstd.hpp>
#include "../../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::var
//*
TEST(memory_terp, var_constructor){
    sstd::terp::var a;
}

// operator=
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

// typeStr()
TEST(memory_terp, var_typeStr_null){
    sstd::terp::var a;
    ASSERT_STREQ(a.typeStr().c_str(), "null"); // TEST THIS LINE
}
TEST(memory_terp, var_typeStr_c){
    sstd::terp::var a;
    a = "test";
    ASSERT_STREQ(a.typeStr().c_str(), "str"); // TEST THIS LINE
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::list
//*

// operator=
TEST(memory_terp, list_ope_assign){ // Ope=
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

// typeStr()
TEST(memory_terp, list_typeStr){
    sstd::terp::var a;
    a = sstd::terp::list();
    ASSERT_STREQ(a.typeStr().c_str(), "vec_void_ptr"); // TEST THIS LINE
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
    lhs["k1"] = "v1";
    lhs["k2"] = "v2";
    lhs["k3"] = "v3";
    
    sstd::terp::var rhs; rhs = sstd::terp::hash();
    rhs["k1"] = "v1";
    rhs["k2"] = "v2";
    rhs["k3"] = "v3";
    
    ASSERT_TRUE(lhs==rhs); // TEST THIS LINE
}
TEST(memory_terp, hash_ope_eq_true){
    sstd::terp::var lhs; lhs = sstd::terp::hash();
    lhs["k1"] = "v1";
    lhs["k2"] = "v2";
    lhs["k3"] = "v3";
    
    sstd::terp::var rhs; rhs = sstd::terp::hash();
    rhs["k1"] = "v1";
    rhs["k2"] = "v2";
    rhs["k3"] = "v3";
    
    ASSERT_TRUE(lhs==rhs); // TEST THIS LINE
}
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
TEST(memory_terp, hash_ope_eq_false){
    sstd::terp::var lhs; lhs = sstd::terp::hash();
    lhs["k1"] = "v1";
    lhs["k2"] = "v2";
    lhs["k3"] = "v3";
    
    sstd::terp::var rhs; rhs = sstd::terp::hash();
    rhs["k1"] = "v1";
    rhs["k2"] = "v2";
    rhs["k3"] = "NotEqualStr";
    
    ASSERT_FALSE(lhs==rhs); // TEST THIS LINE
}

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

// typeStr()
TEST(memory_terp, hash_typeStr){
    sstd::terp::var a;
    a = sstd::terp::hash();
    ASSERT_STREQ(a.typeStr().c_str(), "hash_str_void_ptr"); // TEST THIS LINE
}
//*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
// complex test cases

// operator==
TEST(memory_terp, var_ope_eq_true_list_hash_list){
    sstd::terp::var lhs;
    lhs = sstd::terp::list(3);
    lhs[0] = "v0";
    lhs[1] = "v1";
    lhs[2] = sstd::terp::hash();
    lhs[2]["k20"] = "v0";
    lhs[2]["k21"] = "v1";
    lhs[2]["k22"] = sstd::terp::list(3);
    lhs[2]["k22"][0] = "v220";
    lhs[2]["k22"][1] = "v221";
    lhs[2]["k22"][2] = "v222";

    sstd::terp::var rhs;
    rhs = sstd::terp::list(3);
    rhs[0] = "v0";
    rhs[1] = "v1";
    rhs[2] = sstd::terp::hash();
    rhs[2]["k20"] = "v0";
    rhs[2]["k21"] = "v1";
    rhs[2]["k22"] = sstd::terp::list(3);
    rhs[2]["k22"][0] = "v220";
    rhs[2]["k22"][1] = "v221";
    rhs[2]["k22"][2] = "v222";

    ASSERT_TRUE(lhs==rhs); // TEST THIS LINE
}
TEST(memory_terp, var_ope_eq_true_hash_list_hash){
    sstd::terp::var lhs;
    lhs = sstd::terp::hash();
    lhs["k0"] = "v0";
    lhs["k1"] = "v1";
    lhs["k2"] = sstd::terp::list(3);
    lhs["k2"][0] = "v20";
    lhs["k2"][1] = "v21";
    lhs["k2"][2] = sstd::terp::hash();
    lhs["k2"][2]["k220"] = "v220";
    lhs["k2"][2]["k221"] = "v221";
    lhs["k2"][2]["k222"] = "v222";

    sstd::terp::var rhs;
    rhs = sstd::terp::hash();
    rhs["k0"] = "v0";
    rhs["k1"] = "v1";
    rhs["k2"] = sstd::terp::list(3);
    rhs["k2"][0] = "v20";
    rhs["k2"][1] = "v21";
    rhs["k2"][2] = sstd::terp::hash();
    rhs["k2"][2]["k220"] = "v220";
    rhs["k2"][2]["k221"] = "v221";
    rhs["k2"][2]["k222"] = "v222";

    ASSERT_TRUE(lhs==rhs); // TEST THIS LINE
}
TEST(memory_terp, var_ope_eq_false_list_hash_list){
    sstd::terp::var lhs;
    lhs = sstd::terp::list(3);
    lhs[0] = "v0";
    lhs[1] = "v1";
    lhs[2] = sstd::terp::hash();
    lhs[2]["k20"] = "v0";
    lhs[2]["k21"] = "v1";
    lhs[2]["k22"] = sstd::terp::list(3);
    lhs[2]["k22"][0] = "v220";
    lhs[2]["k22"][1] = "v221";
    lhs[2]["k22"][2] = "v222";

    sstd::terp::var rhs;
    rhs = sstd::terp::list(3);
    rhs[0] = "v0";
    rhs[1] = "v1";
    rhs[2] = sstd::terp::hash();
    rhs[2]["k20"] = "v0";
    rhs[2]["k21"] = "v1";
    rhs[2]["k22"] = sstd::terp::list(3);
    rhs[2]["k22"][0] = "v220";
    rhs[2]["k22"][1] = "NotEqualStr";
    rhs[2]["k22"][2] = "v222";

    ASSERT_FALSE(lhs==rhs); // TEST THIS LINE
}
TEST(memory_terp, var_ope_eq_false_hash_list_hash){
    sstd::terp::var lhs;
    lhs = sstd::terp::hash();
    lhs["k0"] = "v0";
    lhs["k1"] = "v1";
    lhs["k2"] = sstd::terp::list(3);
    lhs["k2"][0] = "v20";
    lhs["k2"][1] = "v21";
    lhs["k2"][2] = sstd::terp::hash();
    lhs["k2"][2]["k220"] = "v220";
    lhs["k2"][2]["k221"] = "v221";
    lhs["k2"][2]["k222"] = "v222";

    sstd::terp::var rhs;
    rhs = sstd::terp::hash();
    rhs["k0"] = "v0";
    rhs["k1"] = "v1";
    rhs["k2"] = sstd::terp::list(3);
    rhs["k2"][0] = "v20";
    rhs["k2"][1] = "v21";
    rhs["k2"][2] = sstd::terp::hash();
    rhs["k2"][2]["k220"] = "v220";
    rhs["k2"][2]["k221"] = "v221";
    rhs["k2"][2]["k222"] = "NotEqualStr";

    ASSERT_FALSE(lhs==rhs); // TEST THIS LINE
}

TEST(memory_terp, var_ope_eq_false_different_type){
    sstd::terp::var lhs;
    lhs = sstd::terp::hash();
    lhs["k0"] = "v0";
    lhs["k1"] = "v1";
    lhs["k2"] = sstd::terp::list(3);
    lhs["k2"][0] = "v20";
    lhs["k2"][1] = "v21";
    lhs["k2"][2] = sstd::terp::hash();
    lhs["k2"][2]["k220"] = "v220";
    lhs["k2"][2]["k221"] = "v221";
    lhs["k2"][2]["k222"] = "v222";

    sstd::terp::var rhs;
    rhs = sstd::terp::hash();
    rhs["k0"] = "v0";
    rhs["k1"] = "v1";
    rhs["k2"] = sstd::terp::list(3);
    rhs["k2"][0] = "v20";
    rhs["k2"][1] = "v21";
    rhs["k2"][2] = sstd::terp::list(3);
    rhs["k2"][2][0] = "v220";
    rhs["k2"][2][1] = "v221";
    rhs["k2"][2][2] = "NotEqualStr";

    ASSERT_FALSE(lhs==rhs); // TEST THIS LINE
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Type Conversion

#define TEST_VAR_CONSTRUCTOR_AND_TO(T, in)      \
    T ans = in;                                 \
    sstd::terp::var v = ans;                    \
    T ret = v.to<T>(); /* TEST THIS LINE */     \
    ASSERT_TRUE(ret==ans);

TEST(memory_terp, var_constructor_and_to_bool_true){ TEST_VAR_CONSTRUCTOR_AND_TO(bool, true); }
TEST(memory_terp, var_constructor_and_to_bool_false){ TEST_VAR_CONSTRUCTOR_AND_TO(bool, false); }
TEST(memory_terp, var_constructor_and_to_char){ TEST_VAR_CONSTRUCTOR_AND_TO(char, 'c'); }

TEST(memory_terp, var_constructor_and_to_int8_min){ TEST_VAR_CONSTRUCTOR_AND_TO(int8, -128); }
TEST(memory_terp, var_constructor_and_to_int8_max){ TEST_VAR_CONSTRUCTOR_AND_TO(int8,  127); }
TEST(memory_terp, var_constructor_and_to_int16_min){ TEST_VAR_CONSTRUCTOR_AND_TO(int16, -32768); }
TEST(memory_terp, var_constructor_and_to_int16_max){ TEST_VAR_CONSTRUCTOR_AND_TO(int16,  32767); }
TEST(memory_terp, var_constructor_and_to_int32_min){ TEST_VAR_CONSTRUCTOR_AND_TO(int32, -2147483648); }
TEST(memory_terp, var_constructor_and_to_int32_max){ TEST_VAR_CONSTRUCTOR_AND_TO(int32,  2147483647); }
TEST(memory_terp, var_constructor_and_to_int64_min){ TEST_VAR_CONSTRUCTOR_AND_TO(int64, -9223372036854775808); }
TEST(memory_terp, var_constructor_and_to_int64_max){ TEST_VAR_CONSTRUCTOR_AND_TO(int64,  9223372036854775807); }
TEST(memory_terp, var_constructor_and_to_uint8_min){ TEST_VAR_CONSTRUCTOR_AND_TO(uint8, 0); }
TEST(memory_terp, var_constructor_and_to_uint8_max){ TEST_VAR_CONSTRUCTOR_AND_TO(uint8, 255); }
TEST(memory_terp, var_constructor_and_to_uint16_min){ TEST_VAR_CONSTRUCTOR_AND_TO(uint16, 0); }
TEST(memory_terp, var_constructor_and_to_uint16_max){ TEST_VAR_CONSTRUCTOR_AND_TO(uint16, 65535); }
TEST(memory_terp, var_constructor_and_to_uint32_min){ TEST_VAR_CONSTRUCTOR_AND_TO(uint32, 0); }
TEST(memory_terp, var_constructor_and_to_uint32_max){ TEST_VAR_CONSTRUCTOR_AND_TO(uint32, 4294967295); }
TEST(memory_terp, var_constructor_and_to_uint64_min){ TEST_VAR_CONSTRUCTOR_AND_TO(uint64, 0); }
TEST(memory_terp, var_constructor_and_to_uint64_max){ TEST_VAR_CONSTRUCTOR_AND_TO(uint64, 18446744073709551615); }

TEST(memory_terp, var_constructor_and_to_float_case01){ TEST_VAR_CONSTRUCTOR_AND_TO(float, 0.12345); }
TEST(memory_terp, var_constructor_and_to_float_case02_01){ TEST_VAR_CONSTRUCTOR_AND_TO(float, 123456); }
TEST(memory_terp, var_constructor_and_to_float_case02_02){ TEST_VAR_CONSTRUCTOR_AND_TO(float, 12345678); }
TEST(memory_terp, var_constructor_and_to_double_case01){ TEST_VAR_CONSTRUCTOR_AND_TO(double, 0.123456789012345); }
TEST(memory_terp, var_constructor_and_to_double_case02_01){ TEST_VAR_CONSTRUCTOR_AND_TO(double, 123456789012345); }
TEST(memory_terp, var_constructor_and_to_double_case02_02){ TEST_VAR_CONSTRUCTOR_AND_TO(double, 12345678901234567); }

TEST(memory_terp, var_constructor_and_to_pchar){
    const char* ans = "char";
    sstd::terp::var v = ans;
    const char* ret = v.to<const char*>(); // TEST THIS LINE
    ASSERT_TRUE(std::string(ret)==std::string(ans));
}
TEST(memory_terp, var_constructor_and_to_string){ TEST_VAR_CONSTRUCTOR_AND_TO(std::string, "string"); }

#undef TEST_VAR_CONSTRUCTOR_AND_TO

TEST(memory_terp, var_constructor_and_to_bool_err){
    sstd::terp::var v = "invalid string";
    
    testing::internal::CaptureStdout();
    bool ret = v.to<bool>(); // TEST THIS LINE
    std::string ret_str = testing::internal::GetCapturedStdout().c_str();
    
    ASSERT_TRUE(ret==false);
    ASSERT_TRUE(sstd::strIn("input string is not bool type.", ret_str.c_str()));
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// check error messages

// operator[]
TEST(memory_terp, var_ope_subscript_insert_char_to_list_type){
    sstd::terp::var a;
    a = sstd::terp::list();

    testing::internal::CaptureStdout();
    a["k0"] = "v0"; // TEST THIS LINE
    std::string ret = testing::internal::GetCapturedStdout().c_str();
    ASSERT_TRUE(sstd::strIn("Ope[](char*) is failed. Unexpedted data type. sstd::terp::var takes \"sstd::terp::list()\" type, but treat as a \"sstd::terp::hash()\".\n", ret.c_str()));
}
TEST(memory_terp, var_ope_subscript_insert_number_to_hash_type){
    sstd::terp::var a;
    a = sstd::terp::hash();

    testing::internal::CaptureStdout();
    a[0] = "v0"; // TEST THIS LINE
    std::string ret = testing::internal::GetCapturedStdout().c_str();
    ASSERT_TRUE(sstd::strIn("Ope[](char*) is failed. Unexpedted data type. sstd::terp::var takes \"sstd::terp::hash()\" type, but treat as a \"sstd::terp::list()\".\n", ret.c_str()));
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// type check

// isHash()
TEST(memory_terp, isHash_true01){
    sstd::terp::var a;
    a = sstd::terp::hash();
    ASSERT_TRUE(sstd::terp::isHash(a));
}
TEST(memory_terp, isHash_true02){
    sstd::terp::var a;
    a = sstd::terp::hash();
    a["k1"] = "v1";
    ASSERT_TRUE(sstd::terp::isHash(a));
}
TEST(memory_terp, isHash_true03){
    sstd::terp::var a;
    a = sstd::terp::hash();
    a["k1"] = sstd::terp::list();
    ASSERT_TRUE(sstd::terp::isHash(a));
}
TEST(memory_terp, isHash_false){
    sstd::terp::var a;
    a = sstd::terp::list();
    ASSERT_TRUE(!sstd::terp::isHash(a));
}

// isList()
TEST(memory_terp, isList_true){
    sstd::terp::var a;
    a = sstd::terp::list();
    ASSERT_TRUE(sstd::terp::isList(a));
}
TEST(memory_terp, isList_false){
    sstd::terp::var a;
    a = sstd::terp::hash();
    ASSERT_TRUE(!sstd::terp::isList(a));
}

// isNull()
TEST(memory_terp, isNull_true){
    sstd::terp::var a;
    ASSERT_TRUE(sstd::terp::isNull(a));
}
TEST(memory_terp, isNull_false){
    sstd::terp::var a;
    a = sstd::terp::hash();
    ASSERT_TRUE(!sstd::terp::isNull(a));
}

// isValue()
TEST(memory_terp, isValue_true){
    sstd::terp::var a;
    a = "str";
    ASSERT_TRUE(sstd::terp::isValue(a));
}
TEST(memory_terp, isValue_false){
    sstd::terp::var a;
    a = sstd::terp::hash();
    ASSERT_TRUE(!sstd::terp::isValue(a));
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
