#include <sstd/sstd.hpp>
#include "../../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::var

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

//-----------------------------------------------------------------------------------------------------------------------------------------------
// internal interface

TEST(memory_terp, _type){
    sstd::terp::var a;
    ASSERT_TRUE(a.type() == sstd::num_null); // TEST THIS LINE
}
TEST(memory_terp, _is_reference){
    sstd::terp::var a;
    ASSERT_TRUE(a.is_reference() == false); // TEST THIS LINE
}
TEST(memory_terp, _is_pSRCR_tbl_base){
    sstd::terp::var a;
    ASSERT_TRUE(a.is_pSRCR_tbl_base() == true); // TEST THIS LINE
}
TEST(memory_terp, _pSRCR_tbl){
    sstd::terp::var a;
    ASSERT_TRUE(a.pSRCR_tbl() != NULL); // TEST THIS LINE
}
TEST(memory_terp, _p){
    sstd::terp::var a;
    ASSERT_TRUE(a.p() == NULL); // TEST THIS LINE
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// common

// to
TEST(memory_terp, to_SEGV_null_ptr){
    sstd::terp::var a;
    a = sstd::terp::list(1);
    
    testing::internal::CaptureStdout();
    a[0].to<std::string>(); // TEST THIS LINE
    ASSERT_TRUE(sstd::strIn("NULL pointer is detected", testing::internal::GetCapturedStdout()));
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::list

// operator= (copy)
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
TEST(memory_terp, list_ope_assign_with_reference){ // Ope=
    sstd::terp::var a;
    a = sstd::terp::list(2);
    a[0] = sstd::terp::list(3);
    a[0][0] = "a";
    a[0][1] = "b";
    a[0][2] = "c";
    a[1] = &a[0];

    ASSERT_TRUE(a[0].is_reference() == false);
    ASSERT_TRUE(a[1].is_reference() == true );

    sstd::terp::var x = a; // TEST THIS LINE
    
    ASSERT_TRUE(x[0].is_reference() == false);
    ASSERT_TRUE(x[1].is_reference() == true );

    x[0][0]="x";
    ASSERT_STREQ(a[0][0].to<std::string>().c_str(), "a");
    ASSERT_STREQ(a[1][0].to<std::string>().c_str(), "a");
    
    ASSERT_STREQ(x[0][0].to<std::string>().c_str(), "x");
    ASSERT_STREQ(x[1][0].to<std::string>().c_str(), "x");
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
TEST(memory_terp, list_pop_back_avoid_SEGV_0_size){
    sstd::terp::var a;
    a = sstd::terp::list();
    
    a.pop_back(); // TEST THIS LINE
}

// push_back()
TEST(memory_terp, list_push_back_c){
    sstd::terp::var a;
    a = sstd::terp::list();
    a.push_back("test"); // TEST THIS LINE
    
    ASSERT_STREQ(a[0].to<std::string>().c_str(), "test");
}
TEST(memory_terp, list_push_back_var_list){
    // -
    //   - v1
    //   - v2
    
    sstd::terp::var a;
    a = sstd::terp::list();
    a.push_back(sstd::terp::list()); // TEST THIS LINE
    a[0] = sstd::terp::list();
    a[0].push_back("v1");
    a[0].push_back("v2");
    
    ASSERT_STREQ(a[0][0].to<std::string>().c_str(), "v1");
    ASSERT_STREQ(a[0][1].to<std::string>().c_str(), "v2");
}
TEST(memory_terp, list_push_back_var_avoid_SEGV_null_ptr){
    sstd::terp::var a;
    a = sstd::terp::list(1);
    
    testing::internal::CaptureStdout();
    a[0].push_back(""); // TEST THIS LINE
    ASSERT_TRUE(sstd::strIn("NULL pointer is detected", testing::internal::GetCapturedStdout()));
}
TEST(memory_terp, list_push_back_var_avoid_SEGV_push_back_var){
    sstd::terp::var a, tmp;
    a = sstd::terp::list(1);
    
    testing::internal::CaptureStdout();
    a[0].push_back(tmp); // TEST THIS LINE
    ASSERT_TRUE(sstd::strIn("NULL pointer is detected", testing::internal::GetCapturedStdout()));
}
TEST(memory_terp, list_push_back_var){
    // -
    //   - v1
    //   - v2
    
    sstd::terp::var tmp;
    sstd::terp::var a;
    tmp = sstd::terp::list();
    tmp.push_back("v1");
    tmp.push_back("v2");
    a = sstd::terp::list();
    a.push_back(tmp); // TEST THIS LINE
    
    ASSERT_STREQ(a[0][0].to<std::string>().c_str(), "v1");
    ASSERT_STREQ(a[0][1].to<std::string>().c_str(), "v2");
}
TEST(memory_terp, list_push_back_var_move){
    // -
    //   - v1
    //   - v2
    
    sstd::terp::var tmp;
    sstd::terp::var a;
    tmp = sstd::terp::list();
    tmp.push_back("v1");
    tmp.push_back("v2");
    a = sstd::terp::list();
    a.push_back(std::move(tmp)); // TEST THIS LINE
    
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
TEST(memory_terp, list_size_arg_null_REF){
    sstd::terp::var a;
    a = sstd::terp::list();
    sstd::terp::var a_ref;
    a_ref = &a;
    sstd::printn_all(a.type());
    sstd::printn_all(a_ref.type());
    ASSERT_EQ(a_ref.size(), (uint)0);
}
TEST(memory_terp, list_size_arg_10_REF){
    sstd::terp::var a;
    a = sstd::terp::list(10);
    sstd::terp::var a_ref;
    a_ref = &a;
    sstd::printn_all(a.type());
    sstd::printn_all(a_ref.type());
    ASSERT_EQ(a_ref.size(), (uint)10);
}

// typeNum()
TEST(memory_terp, list_typeNum){
    sstd::terp::var a;
    a = sstd::terp::list();
    ASSERT_STREQ(sstd::typeNum2str(a.typeNum()).c_str(), "vec_terp_var"); // TEST THIS LINE
}

// typeStr()
TEST(memory_terp, list_typeStr){
    sstd::terp::var a;
    a = sstd::terp::list();
    ASSERT_STREQ(a.typeStr().c_str(), "vec_terp_var"); // TEST THIS LINE
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// sstd::terp::hash

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
    sstd::sort(v_key, v_val);
    
    ASSERT_EQ(v_key.size(), (uint)3);
    ASSERT_EQ(v_val.size(), (uint)3);
    ASSERT_STREQ(v_key[0].c_str(), "k0");
    ASSERT_STREQ(v_key[1].c_str(), "k1");
    ASSERT_STREQ(v_key[2].c_str(), "k2");
    ASSERT_STREQ(v_val[0].c_str(), "v0");
    ASSERT_STREQ(v_val[1].c_str(), "v1");
    ASSERT_STREQ(v_val[2].c_str(), "v2");
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
    sstd::sort(v_key, v_val);
    
    ASSERT_EQ(v_key.size(), (uint)2);
    ASSERT_EQ(v_val.size(), (uint)2);
    ASSERT_STREQ(v_key[0].c_str(), "k0");
    ASSERT_STREQ(v_key[1].c_str(), "k2");
    ASSERT_STREQ(v_val[0].c_str(), "v0");
    ASSERT_STREQ(v_val[1].c_str(), "v2");
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
    ASSERT_STREQ(sstd::typeNum2str(a.typeNum()).c_str(), "hash_terp_var"); // TEST THIS LINE
}

// typeStr()
TEST(memory_terp, hash_typeStr){
    sstd::terp::var a;
    a = sstd::terp::hash();
    ASSERT_STREQ(a.typeStr().c_str(), "hash_terp_var"); // TEST THIS LINE
}

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

#define TEST_VAR_CONSTRUCTOR_AND_TO(T, in)         \
    T ans = in;                                    \
    sstd::terp::var v = ans;                    \
    T ret = v.to<T>(); /* TEST THIS LINE */        \
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

TEST(memory_terp, var_REF_constructor){
    sstd::terp::var a = "test";
    sstd::terp::var a_ref = &a; // TEST THIS LINE

    ASSERT_EQ(a.is_reference(), false);
    ASSERT_EQ(a_ref.is_reference(), true);
    ASSERT_STREQ(a.to<std::string>().c_str(), "test");
    ASSERT_STREQ(a_ref.to<std::string>().c_str(), "test");

    a = "x";
    ASSERT_EQ(a.is_reference(), false);
    ASSERT_EQ(a_ref.is_reference(), true);
    ASSERT_STREQ(a.to<std::string>().c_str(), "x");
    ASSERT_STREQ(a_ref.to<std::string>().c_str(), "x");
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
    ASSERT_TRUE(sstd::strIn("Ope[](char*) is failed. Unexpedted data type. sstd::terp::var takes type number `119`, but treat as a \"sstd::terp::hash()\".\n", ret.c_str()));

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
// referendce of the `sstd::terp::var` address

TEST(memory_terp, reference_of_sstd_terp_var_01){
    sstd::terp::var x;
    x = sstd::terp::list(2);
    x[0] = sstd::terp::list(3);
    x[0][0] = "a";
    x[0][1] = "b";
    x[0][2] = "c";
    x[1] = &x[0];
    //sstd::printn_all(x);
    
    sstd::terp::var a; // ans
    a = sstd::terp::list(2);
    a[0] = sstd::terp::list(3);
    a[0][0] = "a";
    a[0][1] = "b";
    a[0][2] = "c";
    a[1] = sstd::terp::list(3);
    a[1][0] = "a";
    a[1][1] = "b";
    a[1][2] = "c";
    //sstd::printn_all(a);
    
    ASSERT_TRUE(x==a);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

TEST(memory_terp, var_init_constructor){
    sstd::terp::var a;
    ASSERT_TRUE(a.is_pSRCR_tbl_base() == true );
    ASSERT_TRUE(a.pSRCR_tbl() != NULL );
}
TEST(memory_terp, var_init_list){
    sstd::terp::var a = sstd::terp::list(2); // TEST THIS LINE
    
    ASSERT_TRUE(a.is_pSRCR_tbl_base() == true );
    ASSERT_TRUE(a.pSRCR_tbl() != NULL );
    
    ASSERT_TRUE(a[0].is_pSRCR_tbl_base() == false );
    ASSERT_TRUE(a[0].pSRCR_tbl() != NULL );
    
    ASSERT_TRUE(a[1].is_pSRCR_tbl_base() == false );
    ASSERT_TRUE(a[1].pSRCR_tbl() != NULL );
    
    ASSERT_TRUE( a.pSRCR_tbl() == a[0].pSRCR_tbl() );
    ASSERT_TRUE( a.pSRCR_tbl() == a[1].pSRCR_tbl() );
}

//---

TEST(memory_terp, copy_list){ // operator=(&)
    sstd::terp::var a;
    a = (const sstd::terp::var)sstd::terp::list(2); // TEST THIS LINE
    
    ASSERT_TRUE(a.is_pSRCR_tbl_base() == true );
    ASSERT_TRUE(a.pSRCR_tbl() != NULL );
    
    ASSERT_TRUE(a[0].is_pSRCR_tbl_base() == false );
    ASSERT_TRUE(a[0].pSRCR_tbl() != NULL );
    
    ASSERT_TRUE(a[1].is_pSRCR_tbl_base() == false );
    ASSERT_TRUE(a[1].pSRCR_tbl() != NULL );
    
    ASSERT_TRUE( a.pSRCR_tbl() == a[0].pSRCR_tbl() );
    ASSERT_TRUE( a.pSRCR_tbl() == a[1].pSRCR_tbl() );
}
TEST(memory_terp, copy_hash){ // operator=(&)
}

TEST(memory_terp, move_list){ // operator=(&&)
    sstd::terp::var a;
    a = sstd::terp::list(2); // TEST THIS LINE
    
    ASSERT_TRUE(a.is_pSRCR_tbl_base() == true );
    ASSERT_TRUE(a.pSRCR_tbl() != NULL );
    
    ASSERT_TRUE(a[0].is_pSRCR_tbl_base() == false );
    ASSERT_TRUE(a[0].pSRCR_tbl() != NULL );
    
    ASSERT_TRUE(a[1].is_pSRCR_tbl_base() == false );
    ASSERT_TRUE(a[1].pSRCR_tbl() != NULL );
    
    ASSERT_TRUE( a.pSRCR_tbl() == a[0].pSRCR_tbl() );
    ASSERT_TRUE( a.pSRCR_tbl() == a[1].pSRCR_tbl() );
}
TEST(memory_terp, move_hash){ // operator=(&&)
}

//---

TEST(memory_terp, copy_self_ref_list__obj){
    sstd::terp::var s; // src
    s = sstd::terp::list(2);
    s[0] = sstd::terp::list(3);
    s[0][0] = "a";
    s[0][1] = "b";
    s[0][2] = "c";
    s[1] = &s[0];
    //sstd::printn_all(x);
    
    sstd::terp::var d; // dst
    d = s; // TEST THIS LINE
    
    sstd::terp::var a; // ans
    a = sstd::terp::list(2);
    a[0] = sstd::terp::list(3);
    a[0][0] = "a";
    a[0][1] = "b";
    a[0][2] = "c";
    a[1] = sstd::terp::list(3);
    a[1][0] = "a";
    a[1][1] = "b";
    a[1][2] = "c";
    //sstd::printn_all(a);
    
    ASSERT_TRUE(sstd::terp::equal(s, a, "")); // compares: only actual value
    ASSERT_TRUE(sstd::terp::equal(d, a, "")); // compares: only actual value
}
TEST(memory_terp, copy_self_ref_list__ref){
    sstd::terp::var s; // src
    s = sstd::terp::list(2);
    s[0] = sstd::terp::list(3);
    s[0][0] = "a";
    s[0][1] = "b";
    s[0][2] = "c";
    s[1] = &s[0];
    //sstd::printn_all(x);
    
    sstd::terp::var d; // dst
    d = s; // TEST THIS LINE // TODO: アドレス構造をコピーできるようにして，テストする
    
    sstd::terp::var a; // ans
    a = sstd::terp::list(2);
    a[0] = sstd::terp::list(3);
    a[0][0] = "a";
    a[0][1] = "b";
    a[0][2] = "c";
    a[1] = &a[0];
    //sstd::printn_all(a);
    
    ASSERT_EQ(d[0].is_reference(), s[0].is_reference());
    ASSERT_EQ(d[1].is_reference(), s[1].is_reference());
    ASSERT_EQ(d[0].type(), s[0].type());
    ASSERT_EQ(d[1].type(), s[1].type());

    ASSERT_NE(&d[0], &d[1]);
    ASSERT_EQ(d[0].p(), d[1].p());
}

TEST(memory_terp, copy_self_ref_hash){
}

//---

TEST(memory_terp, equal1__compare_only_value){ // operator==
    // sstd::terp::equal0
}

TEST(memory_terp, equal2__compare_value_and_isReference){
    // sstd::terp::equal1
    
    // sstd::terp::isSame
}

TEST(memory_terp, equal3__compare_all){
    // sstd::terp::equal2
    
    // sstd::terp::isEqualObj
    // sstd::terp::isSameObject
}

//---

/*
TEST(memory_terp, list_ope_assign_with_reference_tmp){ // Ope=
    sstd::terp::var a;
    a = sstd::terp::list(2);
    a[0] = sstd::terp::list(3);
    a[0][0] = "a";
    a[0][1] = "b";
    a[0][2] = "c";
    printf("894\n");
    sstd::printn(a.pSRCR_tbl());
    sstd::printn(a[0].pSRCR_tbl());
    printf("895\n");
    a[1] = &a[0];
    printf("897\n");

    ASSERT_TRUE(a[0].is_reference() == false);
    ASSERT_TRUE(a[1].is_reference() == true );
    printf("899\n");

    sstd::terp::var x = a; // TEST THIS LINE
    
    ASSERT_TRUE(x[0].is_reference() == false);
    ASSERT_TRUE(x[1].is_reference() == true );
    printf("905\n");

    x[0][0]="x";
    ASSERT_TRUE(a[0][0].to<std::string>() == "x");
    ASSERT_TRUE(a[1][0].to<std::string>() == "x");
    printf("910\n");
    
    ASSERT_TRUE(x[0][0].to<std::string>() == "x");
    ASSERT_TRUE(x[1][0].to<std::string>() == "x");
    printf("913\n");
}
*/
TEST(memory_terp, list_ope_assign_with_reference_case_01_delete_src){
    sstd::terp::var dst;
    {
        sstd::terp::var src = "test";
        
        dst = &src;
        
        ASSERT_TRUE(src.is_reference() == false);
        ASSERT_TRUE(src.is_pSRCR_tbl_base() == true);
        ASSERT_TRUE(src.p() != NULL);
        
        ASSERT_TRUE(dst.is_reference() == true);
        ASSERT_TRUE(dst.is_pSRCR_tbl_base() == true);
        ASSERT_TRUE(dst.p() != NULL);

        // A destructor of variable x is called.
    } // Test this line (test destructor)
    
    ASSERT_TRUE(dst.is_reference() == false);
    ASSERT_TRUE(dst.is_pSRCR_tbl_base() == true);
    ASSERT_TRUE(dst.p() == NULL);
}
//TEST(memory_terp, list_ope_assign_with_reference_case_02_delete_dst){
//}

//---

TEST(memory_terp, resolve_double_reference){
    sstd::terp::var s; // src
    s = sstd::terp::list(3);
    s[0] = "a";
    s[1] = &s[0];
    s[2] = &s[1];

    ASSERT_FALSE(s[0].is_reference());
    ASSERT_TRUE(s[1].is_reference());
    ASSERT_TRUE(s[2].is_reference());

    ASSERT_EQ(s[1].type(), s[0].type());
    ASSERT_EQ(s[2].type(), s[0].type());
    ASSERT_EQ(s[1].p(), s[0].p());
    ASSERT_EQ(s[2].p(), s[0].p());
}

//---

TEST(memory_terp, _pSRCR_tbl_case1_1_new_ref_by_hand){
    sstd::terp::var s; // src
    s = sstd::terp::list(2);
    s[0] = "a";
    s[1] = &s[0]; // TEST THIS LINE

    ASSERT_FALSE(s[0].is_reference());
    ASSERT_TRUE(s[1].is_reference());
    ASSERT_EQ(s[1].type(), s[0].type());
    ASSERT_EQ(s[1].p(), s[0].p());

    ASSERT_TRUE(s.is_pSRCR_tbl_base());
    ASSERT_FALSE(s[0].is_pSRCR_tbl_base());
    ASSERT_FALSE(s[1].is_pSRCR_tbl_base());
    
    sstd::terp::srcr_tbl tbl = *s.pSRCR_tbl();
    
    ASSERT_EQ(tbl.size(), (uint)1);
    auto itr = tbl.find( (sstd::terp::var*)s[0].p() ); // TEST THIS LINE
    ASSERT_TRUE(itr!=tbl.end());

    ASSERT_EQ(itr->second.size(), (uint)1);
    auto itr2 = itr->second.find( &s[1] ); // TEST THIS LINE
    ASSERT_TRUE(itr2!=itr->second.end());

//  sstd::printn(s[0].p());
//  sstd::printn(s[1].p());
//  sstd::printn(&s[1]);
//  sstd::printn(*s.pSRCR_tbl());

//  Example of the addresses dependency:
//  
//  s[0].p() = 0x55e9e8d5a570
//  s[1].p() = 0x55e9e8d5a570
//  &s[1] = 0x55e9e8d66e40
//  *s.pSRCR_tbl() = { (key: 0x55e9e8d5a570, value: {0x55e9e8d66e40}) }
//
}
TEST(memory_terp, _pSRCR_tbl_case1_2_new_ref_by_copy){
    sstd::terp::var s; // src
    s = sstd::terp::list(2);
    s[0] = "a";
    s[1] = &s[0];
    
    sstd::terp::var d; // dst
    d = s; // TEST THIS LINE
    
    ASSERT_EQ(d.pSRCR_tbl()->size(), (uint)1);
    auto itr = d.pSRCR_tbl()->find( (sstd::terp::var*) d[0].p() ); // TEST THIS LINE
    ASSERT_TRUE(itr != d.pSRCR_tbl()->end());
    
    ASSERT_EQ(itr->second.size(), (uint)1);
    auto itr2 = itr->second.find( &d[1] ); // TEST THIS LINE
    ASSERT_TRUE(itr2!=itr->second.end());
    
//    sstd::printn(d[0].p());
//    sstd::printn(d[1].p());
//    sstd::printn(&d[1]);
//    sstd::printn(*d.pSRCR_tbl());

//  Example of the addresses dependency:
//
//  d[0].p() = 0x55f911e69ed0
//  d[1].p() = 0x55f911e69ed0
//  &d[1] = 0x55f911e76f00
//  *d.pSRCR_tbl() = { (key: 0x55f911e69ed0, value: {0x55f911e76f00}) }
}

//---

TEST(memory_terp, _pSRCR_tbl_case2_1_overwrite_dependent_object_01){
    sstd::terp::var x; // Precedent object
    x = sstd::terp::list(2);
    x[0] = sstd::terp::list(2);
    x[0][0] = "a";
    x[0][1] = &x[0][0];
    x[1] = sstd::terp::list(2);
    x[1][0] = "b";
    x[1][1] = &x[1][0];

    ASSERT_EQ(x.pSRCR_tbl()->size(), (uint)2);
    
    x[1] = "overwritten"; // TEST THIS LINE
    
    ASSERT_EQ(x.pSRCR_tbl()->size(), (uint)1);

    auto itr = x.pSRCR_tbl()->begin();
    sstd::terp::var*                      key = itr->first;
    std::unordered_set<sstd::terp::var*>& val = itr->second;
    auto val_itr = val.begin();
    
    ASSERT_EQ(key,       x[0][0].p());
    ASSERT_EQ(*val_itr, &x[0][1]    );
}
TEST(memory_terp, _pSRCR_tbl_case2_1_overwrite_dependent_object_02){
    sstd::terp::var x; // Precedent object
    x = "a";
    
    sstd::terp::var y; // Dependent object
    
    sstd::printn_all(x);
    sstd::printn_all(y);
    sstd::printn(*x.pSRCR_tbl());
    sstd::printn(*y.pSRCR_tbl());
    
    y = &x;
    
//    ASSERT_EQ(x.pSRCR_tbl()->size(), (uint)1);
//    ASSERT_EQ(y.pSRCR_tbl()->size(), (uint)0);
//    ASSERT_FALSE(x.is_reference());
//    ASSERT_TRUE (y.is_reference());
//    ASSERT_NE(x.p(), (void*)0);
//    ASSERT_NE(y.p(), (void*)0);

    sstd::printn_all(x);
    sstd::printn_all(y);
    sstd::printn(*x.pSRCR_tbl());
    sstd::printn(*y.pSRCR_tbl());
    sstd::printn(&x);
    sstd::printn(x.is_reference());
    sstd::printn(x.p());
    sstd::printn(&y);
    sstd::printn(y.is_reference());
    sstd::printn(y.p());
    
    y = "overwritten"; // TEST THIS LINE
    
    sstd::printn_all(x);
    sstd::printn_all(y);
    sstd::printn(*x.pSRCR_tbl());
    sstd::printn(*y.pSRCR_tbl());
    sstd::printn(&x);
    sstd::printn(x.is_reference());
    sstd::printn(x.p());
    sstd::printn(&y);
    sstd::printn(y.is_reference());
    sstd::printn(y.p());
    
//    ASSERT_EQ(x.pSRCR_tbl()->size(), (uint)0);
//    ASSERT_EQ(y.pSRCR_tbl()->size(), (uint)0);
//    ASSERT_FALSE(x.is_reference());
//    ASSERT_FALSE(y.is_reference());
//    ASSERT_NE(x.p(), (void*)0);
//    ASSERT_EQ(y.p(), (void*)0);
    
    ASSERT_TRUE(false);
}
TEST(memory_terp, _pSRCR_tbl_case2_2_destructor_of_the_dependent_object_is_called_1_out_of_scope){}
TEST(memory_terp, _pSRCR_tbl_case2_2_destructor_of_the_dependent_object_is_called_2_explicit_delete){}
TEST(memory_terp, _pSRCR_tbl_case2_3_destructor_of_the_dependent_object_is_called_1_list_pop_back){}
TEST(memory_terp, _pSRCR_tbl_case2_3_destructor_of_the_dependent_object_is_called_2_list_resize){}
TEST(memory_terp, _pSRCR_tbl_case2_3_destructor_of_the_dependent_object_is_called_3_hash_erase){}

//---

TEST(memory_terp, _pSRCR_tbl_case3_1_overwrite_precedent_object_01){}
TEST(memory_terp, _pSRCR_tbl_case3_1_overwrite_precedent_object_02){
    sstd::terp::var x; // Precedent object
    x = "a";
    
    sstd::terp::var y; // Dependent object
    
    y = &x;
    
    ASSERT_EQ(x.pSRCR_tbl()->size(), (uint)1);
    ASSERT_EQ(y.pSRCR_tbl()->size(), (uint)0);
    ASSERT_FALSE(x.is_reference());
    ASSERT_TRUE (y.is_reference());
    ASSERT_NE(x.p(), (void*)0);
    ASSERT_NE(y.p(), (void*)0);

    x = "overwritten"; // TEST THIS LINE
    
    ASSERT_EQ(x.pSRCR_tbl()->size(), (uint)0);
    ASSERT_EQ(y.pSRCR_tbl()->size(), (uint)0);
    ASSERT_FALSE(x.is_reference());
    ASSERT_FALSE(y.is_reference());
    ASSERT_NE(x.p(), (void*)0);
    ASSERT_EQ(y.p(), (void*)0);
}
TEST(memory_terp, _pSRCR_tbl_case3_2_destructor_of_the_precedent_object_is_called_1_out_of_scope){
    sstd::terp::var y; // Dependent object

    {
        sstd::terp::var x; // Precedent object
        x = "a";
        y = &x; // Cross variable reference

        ASSERT_TRUE(x.is_reference()==false);
        ASSERT_TRUE(y.is_reference()==true );
        
        ASSERT_STREQ(x.to<std::string>().c_str(), "a");
        ASSERT_STREQ(y.to<std::string>().c_str(), "a");

        ASSERT_NE(y.p(), (void*)NULL);
        
    } // x will be deleted. -> y.p() will be filled with NULL.
    
    ASSERT_EQ(y.p(), (void*)NULL); // checks the y.p() is the null filled.
    ASSERT_TRUE(y.is_reference()==false);
}
TEST(memory_terp, _pSRCR_tbl_case3_2_destructor_of_the_precedent_object_is_called_2_explicit_delete){
    sstd::terp::var y; // Dependent object

    //---

    sstd::terp::var* pX = new sstd::terp::var(); // Precedent object
    (*pX) = "a";
    y = &(*pX); // Cross variable reference
    
    ASSERT_TRUE((*pX).is_reference()==false);
    ASSERT_TRUE(y.is_reference()==true );
        
    ASSERT_STREQ((*pX).to<std::string>().c_str(), "a");
    ASSERT_STREQ(y.to<std::string>().c_str(), "a");

    ASSERT_NE(y.p(), (void*)NULL);
    delete pX; // x will be deleted. -> y.p() will be filled with NULL.

    //---
    
    ASSERT_EQ(y.p(), (void*)NULL); // checks the y.p() is the null filled.
    ASSERT_TRUE(y.is_reference()==false);
}
TEST(memory_terp, _pSRCR_tbl_case3_3_destructor_of_the_precedent_object_is_called_1_list_pop_back){}
TEST(memory_terp, _pSRCR_tbl_case3_3_destructor_of_the_precedent_object_is_called_2_list_resize){}
TEST(memory_terp, _pSRCR_tbl_case3_3_destructor_of_the_precedent_object_is_called_3_hash_erase){}

//---

TEST(memory_terp, _pSRCR_tbl_case1_1_new_ref_by_hand___TMP){
    sstd::terp::var s; // src
    s = sstd::terp::list(2);
    s[0] = "a";
    s[1] = &s[0]; // TEST THIS LINE

  sstd::printn_all(s);
  sstd::printn_all("");
  sstd::printn_all("");
  
  sstd::printn(s[0].p());
  sstd::printn(s[1].p());
  sstd::printn(&s[1]);
  sstd::printn(*s.pSRCR_tbl());
    
    ASSERT_FALSE(s[0].is_reference());
    ASSERT_TRUE(s[1].is_reference());
    ASSERT_EQ(s[1].type(), s[0].type());
    ASSERT_EQ(s[1].p(), s[0].p());

    ASSERT_TRUE(s.is_pSRCR_tbl_base());
    ASSERT_FALSE(s[0].is_pSRCR_tbl_base());
    ASSERT_FALSE(s[1].is_pSRCR_tbl_base());
    
    sstd::terp::srcr_tbl tbl = *s.pSRCR_tbl();
    
    ASSERT_EQ(tbl.size(), (uint)1);
    auto itr = tbl.find( (sstd::terp::var*)s[0].p() ); // TEST THIS LINE
    ASSERT_TRUE(itr!=tbl.end());

    ASSERT_EQ(itr->second.size(), (uint)1);
    auto itr2 = itr->second.find( &s[1] ); // TEST THIS LINE
    ASSERT_TRUE(itr2!=itr->second.end());

//  sstd::printn(s[0].p());
//  sstd::printn(s[1].p());
//  sstd::printn(&s[1]);
//  sstd::printn(*s.pSRCR_tbl());

//  Example of the addresses dependency:
//  
//  s[0].p() = 0x55e9e8d5a570
//  s[1].p() = 0x55e9e8d5a570
//  &s[1] = 0x55e9e8d66e40
//  *s.pSRCR_tbl() = { (key: 0x55e9e8d5a570, value: {0x55e9e8d66e40}) }
//
}

//---

// operator[]
TEST(memory_terp, var_ope_square_brackets_list){
    sstd::terp::var x;
    x = sstd::terp::list(2);
    x[0] = "val1";
    x[1] = "val2";

    ASSERT_EQ(x.size(), 2);
    ASSERT_STREQ(x.ope_sb  (0).to<std::string>().c_str(), "val1"); // TEST Ope[]
    ASSERT_STREQ(x.ope_sb  (1).to<std::string>().c_str(), "val2"); // TEST Ope[]
    ASSERT_STREQ(x.ope_sb_c(0).to<std::string>().c_str(), "val1"); // TEST Ope[] const
    ASSERT_STREQ(x.ope_sb_c(1).to<std::string>().c_str(), "val2"); // TEST Ope[] const
}
TEST(memory_terp, var_ope_square_brackets_hash){
    sstd::terp::var x;
    x = sstd::terp::hash();
    x["key1"] = "val1";
    x["key2"] = "val2";

    ASSERT_EQ(x.size(), 2);
    ASSERT_STREQ(x.ope_sb  ("key1").to<std::string>().c_str(), "val1"); // TEST Ope[]
    ASSERT_STREQ(x.ope_sb  ("key2").to<std::string>().c_str(), "val2"); // TEST Ope[]
    ASSERT_STREQ(x.ope_sb_c("key1").to<std::string>().c_str(), "val1"); // TEST Ope[] const
    ASSERT_STREQ(x.ope_sb_c("key2").to<std::string>().c_str(), "val2"); // TEST Ope[] const
}

// operator[] with REF
TEST(memory_terp, var_ope_square_brackets_list__REF){
    sstd::terp::var x;
    x = sstd::terp::list(2);
    x[0] = "val1";
    x[1] = &x[0];

    ASSERT_EQ(x.size(), 2);
    
    ASSERT_EQ(x.ope_sb  (0).type(), sstd::num_str); // TEST Ope[]
    ASSERT_EQ(x.ope_sb  (1).type(), sstd::num_str); // TEST Ope[]
    ASSERT_EQ(x.ope_sb_c(0).type(), sstd::num_str); // TEST Ope[] const
    ASSERT_EQ(x.ope_sb_c(1).type(), sstd::num_str); // TEST Ope[] const
    
    ASSERT_STREQ(x.ope_sb  (0).to<std::string>().c_str(), "val1"); // TEST Ope[]
    ASSERT_STREQ(x.ope_sb  (1).to<std::string>().c_str(), "val1"); // TEST Ope[]
    ASSERT_STREQ(x.ope_sb_c(0).to<std::string>().c_str(), "val1"); // TEST Ope[] const
    ASSERT_STREQ(x.ope_sb_c(1).to<std::string>().c_str(), "val1"); // TEST Ope[] const
    
    ASSERT_EQ(x.ope_sb  (0).is_reference(), false); // TEST Ope[]
    ASSERT_EQ(x.ope_sb  (1).is_reference(),  true); // TEST Ope[]
    ASSERT_EQ(x.ope_sb_c(0).is_reference(), false); // TEST Ope[] const
    ASSERT_EQ(x.ope_sb_c(1).is_reference(),  true); // TEST Ope[] const
}
TEST(memory_terp, var_ope_square_brackets_hash__REF){
    sstd::terp::var x;
    x = sstd::terp::hash();
    x["key1"] = "val1";
    x["key2"] = &x["key1"];
    
    ASSERT_EQ(x.size(), 2);
    
    ASSERT_EQ(x.ope_sb  ("key1").type(), sstd::num_str); // TEST Ope[]
    ASSERT_EQ(x.ope_sb  ("key2").type(), sstd::num_str); // TEST Ope[]
    ASSERT_EQ(x.ope_sb_c("key1").type(), sstd::num_str); // TEST Ope[] const
    ASSERT_EQ(x.ope_sb_c("key2").type(), sstd::num_str); // TEST Ope[] const
    
    ASSERT_STREQ(x.ope_sb  ("key1").to<std::string>().c_str(), "val1"); // TEST Ope[]
    ASSERT_STREQ(x.ope_sb  ("key2").to<std::string>().c_str(), "val1"); // TEST Ope[]
    ASSERT_STREQ(x.ope_sb_c("key1").to<std::string>().c_str(), "val1"); // TEST Ope[] const
    ASSERT_STREQ(x.ope_sb_c("key2").to<std::string>().c_str(), "val1"); // TEST Ope[] const
    
    ASSERT_EQ(x.ope_sb  ("key1").is_reference(), false); // TEST Ope[]
    ASSERT_EQ(x.ope_sb  ("key2").is_reference(),  true); // TEST Ope[]
    ASSERT_EQ(x.ope_sb_c("key1").is_reference(), false); // TEST Ope[] const
    ASSERT_EQ(x.ope_sb_c("key2").is_reference(),  true); // TEST Ope[] const
}

//---

TEST(memory_terp, list_ope_assign_with_reference__TMP){ // Ope=
    sstd::terp::var a;
    a = sstd::terp::list(2);
    a[0] = sstd::terp::list(3);
    a[0][0] = "a";
    a[0][1] = "b";
    a[0][2] = "c";
    a[1] = &a[0];

    ASSERT_EQ(a[0].is_reference(), false);
    ASSERT_EQ(a[1].is_reference(), true );

    sstd::printn_all("");
    sstd::terp::var x = a; // TEST THIS LINE
    sstd::printn_all("");
    
    sstd::printn_all(a);
    sstd::printn_all(x);
    
    ASSERT_EQ(x[0].is_reference(), false);
    ASSERT_EQ(x[1].is_reference(), true );

    x[0][0]="x";
    sstd::printn_all(a);
    sstd::printn_all(x);
    ASSERT_STREQ(a[0][0].to<std::string>().c_str(), "a");
    ASSERT_STREQ(a[1][0].to<std::string>().c_str(), "a");
    
    ASSERT_STREQ(x[0][0].to<std::string>().c_str(), "x");
    ASSERT_STREQ(x[1][0].to<std::string>().c_str(), "x");
}

//---

EXECUTE_TESTS();
