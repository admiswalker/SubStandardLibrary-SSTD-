#pragma once


TEST(tinyInterpreter, getCommandList){
    // reading "tinyInterpreter.txt" to vv_ret
    std::vector<std::string> v_line = sstd::getCommandList(R"(./test/file/tinyInterpreter.txt)");
    sstd::vvec<std::string> vv_ret(v_line.size());
    
    for(uint i=0; i<v_line.size(); i++){
        std::vector<std::string> v_cmd = sstd::splitByComma(v_line[i]);
	for(uint n=0; n<v_cmd.size(); ++n){
	    vv_ret[i] <<= v_cmd[n];
	}
    }

    // compareing vv_ret with vv_ans
    sstd::vvec<std::string> vv_ans={{"cmd01", "cmd02",      "", "cmd04"},
				    {"cmd05", "cmd06", "cmd07"         },
				    {"cmd09", "cmd10", "cmd11", "cmd12"}};
    ASSERT_EQ(vv_ret.size(), vv_ans.size());
    for(uint l=0; l<vv_ans.size(); ++l){
	ASSERT_EQ(vv_ret[l].size(), vv_ans[l].size());
	for(uint i=0; i<vv_ans[l].size(); ++i){
	    ASSERT_STREQ(vv_ret[l][i].c_str(), vv_ans[l][i].c_str());
	}
    }
}

