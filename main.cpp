#include <iostream>
#include <yaml-cpp/yaml.h>
#include "YTSConfig.h"

int main() {
    YTSConfig c;
    //YAML::Node node;

    c.loadConfig("bar.yaml");
    return 0;
}
