//
// Created by John Rushford on 7/28/18.
//

#pragma once

#include <yaml-cpp/yaml.h>
#include <unordered_set>

#define Error(fmt, ...) fprintf(stderr, "[%s:%d] %s(): " fmt, __FILE__, __LINE__    , __func__, ##__VA_ARGS__)

static const uint BUFSIZE = 8192;

class YTSConfig {
    YAML::Node root;
    bool loadFile(const std::string fileName, std::stringstream& buf, std::unordered_set<std::string>& include_once);
public:
    YTSConfig(){};
    ~YTSConfig(){};
    bool loadConfig(const char *filename);
};
