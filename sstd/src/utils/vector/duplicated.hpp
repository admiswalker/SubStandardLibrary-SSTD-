#pragma once
#include <tuple>
#include <unordered_map>
#include <vector>

namespace sstd{
    template<typename T>
    std::vector<std::tuple<T,uint>> duplicated_key_cnt(const std::vector<T>& v){
        std::unordered_map<T,uint> tbl_idx_cnt; // index, count

        for(uint i=0; i<v.size(); ++i){
            auto [itr, inserted] = tbl_idx_cnt.insert({v[i], 1});
            if(!inserted){ ++(itr->second); }
        }
        
        std::vector<std::tuple<T,uint>> res_vDuplicated_val_cnt; // index of `v_in`, count
        for(auto itr=tbl_idx_cnt.begin(); itr!=tbl_idx_cnt.end(); ++itr){
            if(itr->second>=2){
                res_vDuplicated_val_cnt.push_back(std::make_tuple(itr->first, itr->second));
            }
        }
    
        return res_vDuplicated_val_cnt;
    }
}
