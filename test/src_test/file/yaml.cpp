#include <sstd/sstd.hpp>
#include "../../gtest_parallel/test_main.hpp"

//-----------------------------------------------------------------------------------------------------------------------------------------------
// var

TEST(yaml, var_str_1_line){
    std::string s=R"(
a # comment
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = "a";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, var_str_2_lines_err){
    std::string s=R"(
a # comment
b
)";
    testing::internal::CaptureStdout();
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    std::string ret = testing::internal::GetCapturedStdout().c_str();
    ASSERT_TRUE(sstd::strIn("OverWritting the existing data. (String data type can only take one data.)", ret.c_str()));
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = "a";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// list

TEST(yaml, list_depth1){
    std::string s=R"(
- a # comment
- b

- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, list_depth2){
    std::string s=R"(
- a # comment
- b
- 
  - c
  - d
- e
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(4);
    ans[0] = "a";
    ans[1] = "b";
    ans[2] = sstd::terp::list(2);
    ans[2][0] = "c";
    ans[2][1] = "d";
    ans[3] = "e";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// hash

TEST(yaml, hash_depth1){
    std::string s=R"(
k1: v1 # comment
k2: v2

k3: v3
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "v1";
    ans["k2"] = "v2";
    ans["k3"] = "v3";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, hash_depth2){
    std::string s=R"(
k1: v1 # comment
k2: v2
k3: 
  k31: v31
  k32: v32
k4: v4
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "v1";
    ans["k2"] = "v2";
    ans["k3"] = sstd::terp::hash();
    ans["k3"]["k31"] = "v31";
    ans["k3"]["k32"] = "v32";
    ans["k4"] = "v4";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// list and hash

TEST(yaml, list_and_hash__NUM_LIST_AND_HASH){
    std::string s=R"(
- k1: v1
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::hash();
    ans[0]["k1"] = "v1";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// complex test cases

TEST(yaml, list_hash){ // depth2
    std::string s=R"(
- a # comment
- b

- k1: v1
  k2: v2
- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);
    
    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(4);
    ans[0] = "a";
    ans[1] = "b";
    ans[2] = sstd::terp::hash();
    ans[2]["k1"] = "v1";
    ans[2]["k2"] = "v2";
    ans[3] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, hash_list){ // depth2
    std::string s=R"(
k1: v1 # comment
k2: v2
k3: 
  - v31
  - v32
k4: v4
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "v1";
    ans["k2"] = "v2";
    ans["k3"] = sstd::terp::list(2);
    ans["k3"][0] = "v31";
    ans["k3"][1] = "v32";
    ans["k4"] = "v4";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---

TEST(yaml, list_hash_list){ // depth3
    std::string s=R"(
- a # comment
- b

- k1: v1
  k2:
    - v21
    - v22
    - v23
  k3: v3
- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);
    
    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(4);
    ans[0] = "a";
    ans[1] = "b";
    ans[2] = sstd::terp::hash();
    ans[2]["k1"] = "v1";
    ans[2]["k2"] = sstd::terp::list(3);
    ans[2]["k2"][0] = "v21";
    ans[2]["k2"][1] = "v22";
    ans[2]["k2"][2] = "v23";
    ans[2]["k3"] = "v3";
    ans[3] = "c";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, hash_list_hash){ // depth3
    std::string s=R"(
k1: v1 # comment
k2: v2
k3: 
  - v31
  - k32: v321
  - v33
k4: v4
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "v1";
    ans["k2"] = "v2";
    ans["k3"] = sstd::terp::list(3);
    ans["k3"][0] = "v31";
    ans["k3"][1] = sstd::terp::hash();
    ans["k3"][1]["k32"] = "v321";
    ans["k3"][2] = "v33";
    ans["k4"] = "v4";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---

TEST(yaml, list_hash_list_hash){ // depth4
}

//---

TEST(yaml, hash_list_hash_list){ // depth4
    std::string s=R"(
k1: v1 # comment
k2: v2
k3: 
  - v31
  - k32:
    - v321
    - v322
    - v323
  - v33
k4: v4
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "v1";
    ans["k2"] = "v2";
    ans["k3"] = sstd::terp::list(3);
    ans["k3"][0] = "v31";
    ans["k3"][1] = sstd::terp::hash();
    ans["k3"][1]["k32"] = sstd::terp::list(3);
    ans["k3"][1]["k32"][0] = "v321";
    ans["k3"][1]["k32"][1] = "v322";
    ans["k3"][1]["k32"][2] = "v323";
    ans["k3"][2] = "v33";
    ans["k4"] = "v4";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// ignore ! option


//-----------------------------------------------------------------------------------------------------------------------------------------------
// TypeConversion

// to<std::string>

// to<bool>
// to<char>

// to<int>
// to<int8>
// to<int16>
// to<int32>
// to<int64>

// to<uint>
// to<uint8>
// to<uint16>
// to<uint32>
// to<uint64>

// to<float>
// to<double>

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Multi line string for list

TEST(yaml, multi_line_str_by_list_vertical_line){ // - |
    std::string s=R"(
- a # comment
- |
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b1\nb2\nb3\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_list_vertical_line_minus){ // - |-
    std::string s=R"(
- a # comment
- |-
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b1\nb2\nb3";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_list_vertical_line_plus){ // - |+
    std::string s=R"(
- a # comment
- |+
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b1\nb2\nb3\n\n\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

// TEST(yaml, multi_line_str_by_list_vertical_line_num_0){ // - |0 (Can't set 0. Because of the indent under list struct is equal or larger than 1)
// }

TEST(yaml, multi_line_str_by_list_vertical_line_num_1){ // - |1
    std::string s=R"(
- a # comment
- |1
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = " b1\n b2\n b3\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_list_vertical_line_num_1_case02){ // - |1
    std::string s=R"(
- a # comment
- |1
 b1
  b2
 b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b1\n b2\nb3\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_list_vertical_line_num_2){ // - |2
    std::string s=R"(
- a # comment
- |2
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b1\nb2\nb3\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

// TEST(yaml, multi_line_str_by_list_vertical_line_minus_num_0){ // - |-0 (Can't set 0. Because of the indent under list struct is equal or larger than 1)
// }

TEST(yaml, multi_line_str_by_list_vertical_line_minus_num_1){
    std::string s=R"(
- a # comment
- |-1
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = " b1\n b2\n b3";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

// TEST(yaml, multi_line_str_by_list_vertical_line_plus_num_0){ // - |+0 (Can't set 0. Because of the indent under list struct is equal or larger than 1)
// }

TEST(yaml, multi_line_str_by_list_vertical_line_plus_num_1){
    std::string s=R"(
- a # comment
- |+1
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = " b1\n b2\n b3\n\n\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---

TEST(yaml, multi_line_str_by_list_greater){ // - >
    std::string s=R"(
- a # comment
- >
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b1 b2 b3\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_list_greater_minus){ // - >-
    std::string s=R"(
- a # comment
- >-
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b1 b2 b3";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_list_greater_plus){ // - >+
    std::string s=R"(
- a # comment
- >+
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b1 b2 b3\n\n\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

// TEST(yaml, multi_line_str_by_list_greater_num_0){ // - >0 (Can't set 0. Because of the indent under list struct is equal or larger than 1)
// }

TEST(yaml, multi_line_str_by_list_greater_num_1){ // - >1
    std::string s=R"(
- a # comment
- >1
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = " b1\n b2\n b3\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, multi_line_str_by_list_greater_num_1_case02){ // - >1
    std::string s=R"(
- a # comment
- 
  - >1
    b1
    b2
    b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = sstd::terp::list(1);
    ans[1][0] = " b1\n b2\n b3\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_list_greater_num_2){ // - >2
    std::string s=R"(
- a # comment
- >2
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b1 b2 b3\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_list_greater_num_4){ // - >4
    std::string s=R"(
- a # comment
- 
  - >4
      b1
      b2
      b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = sstd::terp::list(1);
    ans[1][0] = "b1 b2 b3\n";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_list_greater_minus_num_1){ // - >-1
    std::string s=R"(
- a # comment
- >-1
  b1
  b2
  b3


- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = " b1\n b2\n b3";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

// TEST(yaml, multi_line_str_by_list_greater_minus_num_2){ // - >-2
// }

// TEST(yaml, multi_line_str_by_list_greater_plus_num_1){ // - >-1
// }

// TEST(yaml, multi_line_str_by_list_greater_plus_num_2){ // - >-2
// }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Multi line string for hash

TEST(yaml, multi_line_str_by_hash_vertical_line){ // : |
    std::string s=R"(
k1: a # comment
k2: |
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = "b1\nb2\nb3\n";
    ans["k3"] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_hash_vertical_line_minus){ // : |-
    std::string s=R"(
k1: a # comment
k2: |-
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = "b1\nb2\nb3";
    ans["k3"] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_hash_vertical_line_plus){ // : |+
    std::string s=R"(
k1: a # comment
k2: |+
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = "b1\nb2\nb3\n\n\n";
    ans["k3"] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

// TEST(yaml, multi_line_str_by_hash_vertical_line_num_0){ // : |0 (Can't set 0. Because of the indent under hash struct is equal or larger than 1)
// }

TEST(yaml, multi_line_str_by_hash_vertical_line_num_1){ // : |1
    std::string s=R"(
k1: a # comment
k2: |1
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = " b1\n b2\n b3\n";
    ans["k3"] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_hash_vertical_line_num_2){ // : |2
    std::string s=R"(
k1: a # comment
k2: |2
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = "b1\nb2\nb3\n";
    ans["k3"] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

// TEST(yaml, multi_line_str_by_hash_vertical_line_minus_num_1){ // : |-1
// }

// TEST(yaml, multi_line_str_by_hash_vertical_line_minus_num_2){ // : |-2
// }

// TEST(yaml, multi_line_str_by_hash_vertical_line_plus_num_1){ // : |+1
// }

// TEST(yaml, multi_line_str_by_hash_vertical_line_plus_num_2){ // : |+2
// }

//---

TEST(yaml, multi_line_str_by_hash_greater){ // : >
    std::string s=R"(
k1: a # comment
k2: >
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = "b1 b2 b3\n";
    ans["k3"] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_hash_greater_minus){ // : >-
    std::string s=R"(
k1: a # comment
k2: >-
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = "b1 b2 b3";
    ans["k3"] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_hash_greater_plus){ // : >+
    std::string s=R"(
k1: a # comment
k2: >+
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = "b1 b2 b3\n\n\n";
    ans["k3"] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

// TEST(yaml, multi_line_str_by_hash_greater_num_0){ // : >0 (Can't set 0. Because of the indent under hash struct is equal or larger than 1)
// }

TEST(yaml, multi_line_str_by_hash_greater_num_1){ // : >1
    std::string s=R"(
k1: a # comment
k2: >1
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = " b1\n b2\n b3\n";
    ans["k3"] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, multi_line_str_by_hash_greater_num_2){ // : >2
    std::string s=R"(
k1: a # comment
k2: >2
  b1
  b2
  b3


k3: c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["k1"] = "a";
    ans["k2"] = "b1 b2 b3\n";
    ans["k3"] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

// TEST(yaml, multi_line_str_by_hash_greater_minus_num_1){ // : >-1
// }

// TEST(yaml, multi_line_str_by_hash_greater_minus_num_2){ // : >-2
// }


// TEST(yaml, multi_line_str_by_hash_greater_plus_num_1){ // : >+1
// }

// TEST(yaml, multi_line_str_by_hash_greater_plus_num_2){ // : >+2
// }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Double quotation ""

//---

TEST(yaml_dependent_fn, _splitByLine_dq_sq__dq){
    std::string s=R"(
"a: b c

def
g"

)";
    std::vector<std::string> l = sstd::_splitByLine_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::vector<std::string> ans;
    ans.push_back("");
    ans.push_back(R"("a: b c

def
g")");
    ans.push_back("");
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_dependent_fn, _splitByLine_dq_sq__dq_escape){
    std::string s=R"(\"
"a: b c\"

def'
g"

)";
    std::vector<std::string> l = sstd::_splitByLine_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::vector<std::string> ans;
    ans.push_back(R"(\")");
    ans.push_back(R"("a: b c\"

def'
g")");
    ans.push_back("");
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}

//---

TEST(yaml_dependent_fn, _splitByLine_dq_sq__sq){
    std::string s=R"(
'a: b c

def
g'

)";
    std::vector<std::string> l = sstd::_splitByLine_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::vector<std::string> ans;
    ans.push_back("");
    ans.push_back(R"('a: b c

def
g')");
    ans.push_back("");
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_dependent_fn, _splitByLine_dq_sq__sq_escape){
    std::string s=R"(\"
'a: b c\'

def"
g'

)";
    std::vector<std::string> l = sstd::_splitByLine_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::vector<std::string> ans;
    ans.push_back(R"(\")");
    ans.push_back(R"('a: b c\'

def"
g')");
    ans.push_back("");
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}

//------------------------------------------------

TEST(yaml_dependent_fn, _strip_dq_sq_0_case01){
    std::string s=R"()";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"()";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_dependent_fn, _strip_dq_sq_0_case02){
    std::string s=R"("")";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"()";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_dependent_fn, _strip_dq_sq_0_case03){
    std::string s=R"('')";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"()";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_dependent_fn, _strip_dq_sq_1_case01){
    std::string s=R"(a)";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(a)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_dependent_fn, _strip_dq_sq_1_case02){
    std::string s=R"(" a ")";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"( a )";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_dependent_fn, _strip_dq_sq_2){
    std::string s=R"(ab)";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(ab)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_dependent_fn, _strip_dq_sq_3){
    std::string s=R"(abc)";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(abc)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}

//---

TEST(yaml_dependent_fn, _strip_dq_sq__non_dq_sq_case01){
    std::string s=R"(abc)";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(abc)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}

//---

TEST(yaml_dependent_fn, _strip_dq_sq__non_dq_sq_case00){
    std::string s=R"("abc")";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(abc)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_dependent_fn, _strip_dq_sq__dq_escape_case01){
    std::string s=R"(  "abc
def
ghi"   )";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(abc def ghi)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_dependent_fn, _strip_dq_sq__dq_escape_case02){
    std::string s=R"("abc\
def
ghi"   )";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(abcdef ghi)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_dependent_fn, _strip_dq_sq__dq_escape_case03){
    std::string s=R"("abc


def
ghi"   )";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(abc

def ghi)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_dependent_fn, _strip_dq_sq__dq_escape_case04){
    std::string s=R"("abc\


def
ghi"   )";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(abc

def ghi)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_dependent_fn, _strip_dq_sq__dq_escape_case05){
    std::string s=R"("\
   abc\
   def")";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(abcdef)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_dependent_fn, _strip_dq_sq__dq_escape_case06){
    std::string s=R"("
   abc
   def")";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"( abc def)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
TEST(yaml_dependent_fn, _strip_dq_sq__dq_escape_case07){
    std::string s=R"("a: b c'

def\"
g"   )";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    //sstd::printn(l);

    //--

    std::string ans=R"(a: b c'
def" g)";
    //sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}

//---
/*
TEST(yaml_dependent_fn, _strip_dq_sq__sq_escape_case07){
    std::string s=R"('a: b c\'

def"
g'   )";
    std::string l = sstd::_strip_dq_sq(s); // TEST THIS LINE
    sstd::printn(l);

    //--

    std::string ans=R"(a: b c\'\ndef" g)";
    sstd::printn(ans);

    //---
    
    ASSERT_TRUE(l==ans);
}
*/
//------------------------------------------------

TEST(yaml, double_quotation_NUM_STR){
    std::string s=R"(
"a: b c\"

def
g"
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans=R"(a: b c"
def g)";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---

TEST(yaml, double_quotation_list_NUM_LIST_case01){
    std::string s=R"(
- "a: b c "
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "a: b c ";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_list_NUM_LIST_case02){ // WIP
    std::string s=R"(
- "\
   abc\
   def"
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "abcdef";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---

TEST(yaml, double_quotation_list_NUM_HASH_dq_case01){
    std::string s=R"(
"key1": "a: b c "
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["key1"] = "a: b c ";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_list_NUM_HASH_dq_case02){ // escape \" and non escape '
    std::string s=R"(
"key1 \"'": " a: b c \"' "
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans[R"(key1 "')"] = R"( a: b c "' )";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_list_NUM_HASH_sq_case01){
    std::string s=R"(
'key1': 'a: b c '
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["key1"] = "a: b c ";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_list_NUM_HASH_sq_case02){ // escape \' and non escape "
    std::string s=R"(
'key1 \'"': ' a: b c \'" '
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::hash();
    ans["key1 '\""] = " a: b c '\" ";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---

TEST(yaml, double_quotation_list_NUM_LIST_AND_HASH_dq_case01){
    std::string s=R"(
- "key1": "a: b c "
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::hash();
    ans[0]["key1"] = "a: b c ";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_list_NUM_LIST_AND_HASH_sq_case01){
    std::string s=R"(
- 'key1': 'a: b c '
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = sstd::terp::hash();
    ans[0]["key1"] = "a: b c ";
    //sstd::printn(ans);
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//---

/*
TEST(yaml, double_quotation_list_case02){
    std::string s=R"(
- "a: b"
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "a: b";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
//*/
/*
TEST(yaml, double_quotation_list_case02){
    std::string s=R"(
- "a b c"
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "a b c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
TEST(yaml, double_quotation_list_case03){
    std::string s=R"(
- "- a"
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(1);
    ans[0] = "- a";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}
*/

// example.yaml
// 
// - "a b c"
// - "a: b"
// - "- a"
// - "key 1": "value 1"
// - "I am a cat.\
//    There is no name yet."
// - key1: "\
//    I am a cat.\
//    There is no name yet."

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Single quotation ''

// example.yaml
// 
// - 'a b c'
// - 'key 1': 'value 1'
// - 'I am a cat.\
//    There is no name yet.'
// - key1: '\
//    I am a cat.\
//    There is no name yet.'

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Multipul list indication

// example.yaml
// 
// - a
// - b
// - - c1 # <- multiple list indication
//   - c2
//   - c3

// example.yaml
// 
// - a
// - b
// - - - c1 # <- multiple list indication
//     - c2
//     - c3

// example.yaml
// 
// - a
// - b
// - - - - c1 # <- multiple list indication
//       - c2
//       - c3

//-----------------------------------------------------------------------------------------------------------------------------------------------
// End marker ...

TEST(yaml, end_marker){
    std::string s=R"(
- a # comment
- b

... # end marker

- c
)";
    sstd::terp::var yml; ASSERT_TRUE(sstd::yaml_load(yml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(2);
    ans[0] = "a";
    ans[1] = "b";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// Split file ---

TEST(yaml, yaml_load_all){
    std::string s=R"(
- a1 # comment
- b1
- c1

--- # separator

- a2 # comment
- b2
- c2
)";
    std::vector<sstd::terp::var> vYml; ASSERT_TRUE(sstd::yaml_load_all(vYml, s)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans1;
    ans1 = sstd::terp::list(3);
    ans1[0] = "a1";
    ans1[1] = "b1";
    ans1[2] = "c1";

    sstd::terp::var ans2;
    ans2 = sstd::terp::list(3);
    ans2[0] = "a2";
    ans2[1] = "b2";
    ans2[2] = "c2";

    //---
    
    ASSERT_EQ(vYml.size(), (uint)2);
    ASSERT_TRUE(vYml[0]==ans1);
    ASSERT_TRUE(vYml[1]==ans2);
}

// TEST(yaml, yaml_load_all_fp){ // Define at yaml_load(fp) section
// }

//-----------------------------------------------------------------------------------------------------------------------------------------------
// yaml_load(fp)

TEST(yaml, yaml_load_fp){
    
    //sstd::printn(sstd::system("pwd"));
    sstd::file fp;
    ASSERT_TRUE(fp.fopen("./test/src_test/file/yaml_test/test.yaml", "r"));
    
    sstd::terp::var yml;
    ASSERT_TRUE(sstd::yaml_load(yml, fp)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans;
    ans = sstd::terp::list(3);
    ans[0] = "a";
    ans[1] = "b";
    ans[2] = "c";
    
    //---
    
    ASSERT_TRUE(yml==ans);
}

TEST(yaml, yaml_load_all_fp){
    //sstd::printn(sstd::system("pwd"));
    sstd::file fp;
    ASSERT_TRUE(fp.fopen("./test/src_test/file/yaml_test/test_yaml_load_all.yaml", "r"));
    
    std::vector<sstd::terp::var> vYml; ASSERT_TRUE(sstd::yaml_load_all(vYml, fp)); // TEST THIS LINE
    //sstd::printn(yml);

    //---
    
    sstd::terp::var ans1;
    ans1 = sstd::terp::list(3);
    ans1[0] = "a1";
    ans1[1] = "b1";
    ans1[2] = "c1";

    sstd::terp::var ans2;
    ans2 = sstd::terp::list(3);
    ans2[0] = "a2";
    ans2[1] = "b2";
    ans2[2] = "c2";

    //---
    
    ASSERT_EQ(vYml.size(), (uint)2);
    ASSERT_TRUE(vYml[0]==ans1);
    ASSERT_TRUE(vYml[1]==ans2);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

EXECUTE_TESTS();
