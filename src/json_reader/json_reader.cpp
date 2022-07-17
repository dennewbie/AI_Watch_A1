//
//  json_reader.cpp
//  Lettura di un file JSON in C++
//
//  Created by Denny Caruso on 10/07/22
//

#include <iostream>
#include <json/json.h>
#include <json/value.h>
#include <fstream>
#include <string>

int main (int argc, char * argv[]) {
    Json::Value actualJSON;   // will contains the root value after parsing.
    Json::Reader readerJSON;
    std::ifstream streamJSON("cavani_keypoints.json", std::ifstream::binary);
    if (!(readerJSON.parse(streamJSON, actualJSON, false))) std::cout  << readerJSON.getFormattedErrorMessages() << "\n";
    std::cout << actualJSON;
    return EXIT_SUCCESS;
}