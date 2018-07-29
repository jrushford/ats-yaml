/** @file
 *
 *  Configuration file parsing.
 *
 *  @section license License
 *
 *  Licensed to the Apache Software Foundation (ASF) under one
 *  or more contributor license agreements.  See the NOTICE file
 *  distributed with this work for additional information
 *  regarding copyright ownership.  The ASF licenses this file
 *  to you under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in compliance
 *  with the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "YTSConfig.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <unordered_set>

bool
YTSConfig::loadConfig(const char *fileName)
{
    bool result = true;
    std::stringstream doc;
    std::unordered_set<std::string> include_once;

    result = loadFile(fileName, doc, include_once);

    try {
        root = YAML::Load(doc);
    } catch (std::exception &ex) {
        Error("%s", ex.what());
        result = false;
    }

    std::cout << doc.str() << "\n";

    return result;
}

bool
YTSConfig::loadFile(const std::string fileName, std::stringstream& doc, std::unordered_set<std::string>& include_once) {
    bool result = true;
    const char *sep = " \t";
    char *tok, *last;
    char line[BUFSIZE];

    std::ifstream file(fileName);
    if (file.is_open()) {
        while (file.getline(line, BUFSIZE-1)) {
            if(line[0] == '#') {
                tok = strtok_r(line, sep, &last);
                if (tok != nullptr && strcmp(tok, "#include") == 0) {
                    std::string f = strtok_r(nullptr, sep, &last);
                    if (include_once.find(f) == include_once.end()) {
                        include_once.insert(f);
                        result = loadFile(f, doc, include_once);
                        if (!result) {
                            Error("error processing %s", tok);
                            break;
                        }
                    }
                }
            } else {
                doc << line << "\n";
            }
        }
        file.close();
    } else {
        Error("unable to load %s", fileName.c_str());
        result = false;
    }
    return result;
}