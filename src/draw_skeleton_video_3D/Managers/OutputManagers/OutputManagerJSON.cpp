//
//  OutputManagerJSON.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 21/07/22.
//

#include "OutputManager.hpp"



void OutputManagerJSON::makeOutputString (std::vector <Point3D *> skeletonPoints3D, std::vector <bool> bodyKeyPointsMap, unsigned int frameID, unsigned int personID) {
    Json::Value root, arraySkeletonPoints3D(Json::arrayValue);
    Json::StyledStreamWriter writer;
    for (unsigned char i = 0; i < skeletonPoints3D.size() - 1; i++) {
        Json::Value singlePoint3D_JSON;
        singlePoint3D_JSON["pointID"] = Json::Value((unsigned int) i);
        singlePoint3D_JSON["confidence"] = Json::Value(((BodyKeyPoint *) skeletonPoints3D.at(i)->getDecorated())->getConfidence());
        singlePoint3D_JSON["x"] = Json::Value((double) skeletonPoints3D.at(i)->getX());
        singlePoint3D_JSON["y"] = Json::Value((double) skeletonPoints3D.at(i)->getY());
        singlePoint3D_JSON["z"] = Json::Value((double) skeletonPoints3D.at(i)->getZ());
        singlePoint3D_JSON["x_rotation"] = Json::Value(0.0);
        singlePoint3D_JSON["y_rotation"] = Json::Value(0.0);
        singlePoint3D_JSON["z_rotation"] = Json::Value(0.0);
        singlePoint3D_JSON["w_rotation"] = Json::Value(1.0);
        singlePoint3D_JSON["thingId"] = Json::Value(std::string("org.eclipse.ditto:camera01"));
        arraySkeletonPoints3D.append(singlePoint3D_JSON);
    }

    root["ID_Frame"] = frameID;
    root["ID_Person"] = personID;
    root["_Movement"] = arraySkeletonPoints3D;
    OutputManager::setStringOutputData(root.toStyledString());
}

bool OutputManagerJSON::loadJSON (std::string filePathJSON, Json::Value & currentJSON) {
    Json::Reader readerJSON;
    std::ifstream streamJSON(filePathJSON.c_str(), std::ifstream::binary);
    return readerJSON.parse(streamJSON, currentJSON, false);
}

void OutputManagerJSON::saveJSON (std::string filePath) {
    Json::StyledStreamWriter writer;
    std::ofstream outputFile(filePath);
    outputFile << OutputManager::getStringOutputData();
    outputFile.close();
}

Json::Value OutputManagerJSON::getValueAt (std::string key, Json::Value currentJSON) {
    return currentJSON[key];
}

Json::Value OutputManagerJSON::getValueAt (unsigned int i, Json::Value currentJSON) {
    return currentJSON[i];
}

Json::Value OutputManagerJSON::getValueAt (std::string key, unsigned int i, Json::Value currentJSON) {
    return (currentJSON[i])[key];
}
