//
//  JSON_Manager.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 21/07/22.
//

#include "JSON_Manager.hpp"



std::string JSON_Manager::stringOutputData;



void JSON_Manager::setStringOutputData (std::string stringOutputData) {
    JSON_Manager::stringOutputData = stringOutputData;
}

std::string JSON_Manager::getStringOutputData (void) {
    return std::string(JSON_Manager::stringOutputData);
}


void JSON_Manager::loadJSON (std::string filePathJSON, Json::Value & currentJSON) {
    Json::Reader readerJSON;
    std::ifstream streamJSON(filePathJSON.c_str(), std::ifstream::binary);
    if (!(readerJSON.parse(streamJSON, currentJSON, false))) {
        std::cout  << "\n" << readerJSON.getFormattedErrorMessages() << "\n";
        CV_Error(LOAD_JSON_ERROR, LOAD_JSON_SCOPE);
    }
}

void JSON_Manager::makeJSON (std::vector <Point3D *> skeletonPoints3D) {
//    Json::Value root, arraySkeletonPoints3D(Json::arrayValue);
//    Json::StyledStreamWriter writer;
//    for (auto singlePoint3D: skeletonPoints3D) {
//        Json::Value singlePoint3D_JSON;
//        singlePoint3D_JSON["x"] = Json::Value(singlePoint3D->getX());
//        singlePoint3D_JSON["y"] = Json::Value(singlePoint3D->getY());
//        singlePoint3D_JSON["z"] = Json::Value(singlePoint3D->getZ());
//        singlePoint3D_JSON["x_rotation"] = Json::Value(0.0);
//        singlePoint3D_JSON["y_rotation"] = Json::Value(0.0);
//        singlePoint3D_JSON["z_rotation"] = Json::Value(0.0);
//        singlePoint3D_JSON["w_rotation"] = Json::Value(1.0);
//        singlePoint3D_JSON["thingId"] = Json::Value(std::string("org.eclipse.ditto:camera01"));
//        arraySkeletonPoints3D.append(singlePoint3D_JSON);
//    }
//
//    root["_Movement"] = arraySkeletonPoints3D;
    std::stringstream outputDataStringStream;
    outputDataStringStream << "{" << std::endl << "\t\"_Movement\":\n\t[";
    short unsigned int bodyKeyPoints = 0;
    for (auto singlePoint3D: skeletonPoints3D) {
        bodyKeyPoints += 1;
        outputDataStringStream << "\n\t\t{\n\t\t\t\"x\": " << singlePoint3D->getX() << ","
        "\n\t\t\t\"y\": " << singlePoint3D->getY() << ","
        "\n\t\t\t\"z\": " << singlePoint3D->getZ() << ","
        "\n\t\t\t\"x_rotation\": 0.0,"
        "\n\t\t\t\"y_rotation\": 0.0,"
        "\n\t\t\t\"z_rotation\": 0.0,"
        "\n\t\t\t\"w_rotation\": 1.0,"
        "\n\t\t\t\"thingId\": \"org.eclipse.ditto:camera01\""
        "\n\t\t}";
        if (bodyKeyPoints < skeletonPoints3D.size()) outputDataStringStream << ",";
    }
    
    outputDataStringStream << "\n\t]\n}";
    JSON_Manager::setStringOutputData(outputDataStringStream.str());
}

void JSON_Manager::saveJSON (std::string filePath) {
    Json::StyledStreamWriter writer;
    std::ofstream outputFile("skeletonPoints3D.json");
    outputFile << JSON_Manager::getStringOutputData();
    outputFile.close();
}

Json::Value JSON_Manager::getValueAt (std::string key, Json::Value currentJSON) {
    return currentJSON[key];
}

Json::Value JSON_Manager::getValueAt (unsigned int i, Json::Value currentJSON) {
    return currentJSON[i];
}

Json::Value JSON_Manager::getValueAt (std::string key, unsigned int i, Json::Value currentJSON) {
    return (currentJSON[i])[key];
}
