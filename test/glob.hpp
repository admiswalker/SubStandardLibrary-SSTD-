#pragma once

TEST(glob, glob_f){
    const char* path = R"(./sstd/src/*.hpp)";
    sstd::printn(path);
    std::vector<std::string> vecPath = sstd::glob_f(path);
    for(uint i=0; i<vecPath.size(); ++i){
        sstd::print(vecPath[i]);
    }
    printf("\n");
}

