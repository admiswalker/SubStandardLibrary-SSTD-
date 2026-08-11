#pragma once
#include <string>
#include <vector>
#include "../definitions/typeDef.h"

namespace sstd{
    bool str2val(                 bool   & return_val, const                    char*  s);
    bool str2val(                 char   & return_val, const                    char*  s);
    bool str2val(                  int8  & return_val, const                    char*  s);
    bool str2val(                  int16 & return_val, const                    char*  s);
    bool str2val(                  int32 & return_val, const                    char*  s);
    bool str2val(                  int64 & return_val, const                    char*  s);
    bool str2val(                 uint8  & return_val, const                    char*  s);
    bool str2val(                 uint16 & return_val, const                    char*  s);
    bool str2val(                 uint32 & return_val, const                    char*  s);
    bool str2val(                 uint64 & return_val, const                    char*  s);
    bool str2val(                  float & return_val, const                    char*  s);
    bool str2val(                 double & return_val, const                    char*  s);
    bool str2val(            std::string & return_val, const                    char*  s);

    bool str2val(                 bool   & return_val, const             std::string & s);
    bool str2val(                 char   & return_val, const             std::string & s);
    bool str2val(                  int8  & return_val, const             std::string & s);
    bool str2val(                  int16 & return_val, const             std::string & s);
    bool str2val(                  int32 & return_val, const             std::string & s);
    bool str2val(                  int64 & return_val, const             std::string & s);
    bool str2val(                 uint8  & return_val, const             std::string & s);
    bool str2val(                 uint16 & return_val, const             std::string & s);
    bool str2val(                 uint32 & return_val, const             std::string & s);
    bool str2val(                 uint64 & return_val, const             std::string & s);
    bool str2val(                  float & return_val, const             std::string & s);
    bool str2val(                 double & return_val, const             std::string & s);
    bool str2val(            std::string & return_val, const             std::string & s);

    bool str2val(                 bool   & return_val, const std::vector<std::string>& v);
    bool str2val(                 char   & return_val, const std::vector<std::string>& v);
    bool str2val(                  int8  & return_val, const std::vector<std::string>& v);
    bool str2val(                  int16 & return_val, const std::vector<std::string>& v);
    bool str2val(                  int32 & return_val, const std::vector<std::string>& v);
    bool str2val(                  int64 & return_val, const std::vector<std::string>& v);
    bool str2val(                 uint8  & return_val, const std::vector<std::string>& v);
    bool str2val(                 uint16 & return_val, const std::vector<std::string>& v);
    bool str2val(                 uint32 & return_val, const std::vector<std::string>& v);
    bool str2val(                 uint64 & return_val, const std::vector<std::string>& v);
    bool str2val(                 float  & return_val, const std::vector<std::string>& v);
    bool str2val(                 double & return_val, const std::vector<std::string>& v);
    bool str2val(            std::string & return_val, const std::vector<std::string>& v);

    bool str2val(std::vector<     bool  >& return_val, const std::vector<std::string>& v);
    bool str2val(std::vector<     char  >& return_val, const std::vector<std::string>& v);
    bool str2val(std::vector<      int8 >& return_val, const std::vector<std::string>& v);
    bool str2val(std::vector<      int16>& return_val, const std::vector<std::string>& v);
    bool str2val(std::vector<      int32>& return_val, const std::vector<std::string>& v);
    bool str2val(std::vector<      int64>& return_val, const std::vector<std::string>& v);
    bool str2val(std::vector<     uint8 >& return_val, const std::vector<std::string>& v);
    bool str2val(std::vector<     uint16>& return_val, const std::vector<std::string>& v);
    bool str2val(std::vector<     uint32>& return_val, const std::vector<std::string>& v);
    bool str2val(std::vector<     uint64>& return_val, const std::vector<std::string>& v);
    bool str2val(std::vector<     float >& return_val, const std::vector<std::string>& v);
    bool str2val(std::vector<     double>& return_val, const std::vector<std::string>& v);
    bool str2val(std::vector<std::string>& return_val, const std::vector<std::string>& v);
}
