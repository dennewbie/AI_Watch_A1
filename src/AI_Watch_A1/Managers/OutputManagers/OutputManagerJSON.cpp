//
//  OutputManagerJSON.cpp
//  AI Watch A1
//
//  Created by Denny Caruso on 21/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#include "OutputManager.hpp"



Json::Value OutputManagerJSON::makeOutputString (std::vector <Point3D *> skeletonPoints3D, std::vector <bool> bodyKeyPointsMap, unsigned int frameID, unsigned int personID) {
    Json::Value root, arraySkeletonPoints3D(Json::arrayValue);
    Json::StyledStreamWriter writer;
    
    // For each OpenPose's skeleton body joint point
    for (unsigned char i = 0; i < skeletonPoints3D.size(); i++) {
        if (i >= 24) continue;
        Json::Value singlePoint3D_JSON;
        // Build JSON node for i-th body joint point
        singlePoint3D_JSON["pointID"] = Json::Value((unsigned int) i);
        singlePoint3D_JSON["confidence"] = Json::Value(((BodyKeyPoint *) skeletonPoints3D.at(i)->getDecorated())->getConfidence());
        singlePoint3D_JSON["x"] = Json::Value((double) skeletonPoints3D.at(i)->getZ());
        singlePoint3D_JSON["y"] = Json::Value((double) skeletonPoints3D.at(i)->getY());
        singlePoint3D_JSON["z"] = Json::Value((double) skeletonPoints3D.at(i)->getX());
        singlePoint3D_JSON["x_rotation"] = Json::Value(0.0);
        singlePoint3D_JSON["y_rotation"] = Json::Value(0.0);
        singlePoint3D_JSON["z_rotation"] = Json::Value(0.0);
        singlePoint3D_JSON["w_rotation"] = Json::Value(1.0);
        singlePoint3D_JSON["thingId"] = Json::Value(std::string("org.eclipse.ditto:camera01"));
        arraySkeletonPoints3D.append(singlePoint3D_JSON);
    }

    root["personID"] = Json::Value((unsigned int) personID);
    root["skeleton"] = arraySkeletonPoints3D;
    OutputManager::setStringOutputData(root.toStyledString());
    return root;
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

void OutputManagerJSON::createJSON (Json::Value & people, cv::Mat & colorImage, cv::Mat & distanceImage, cv::Mat & skeletonOnlyImage, unsigned int nFrame, const char * outputFolder, const float skeletonThreshold) {
    Json::Value root, peopleArray(Json::arrayValue);
    std::stringstream outputJsonFilePath;
    root["ID_Frame"] = nFrame;

    // For each OpenPose's detected skeleton 
    for (Json::Value::ArrayIndex i = 0; i < people.size(); i++) {
        Json::Value singlePerson = getValueAt("pose_keypoints_2d", i, people);
        Skeleton singlePersonSkeleton = Skeleton(colorImage, distanceImage, skeletonOnlyImage, singlePerson);
        singlePersonSkeleton.generateSkeleton();
        // Discard Skeleton with low consistency value
        if (singlePersonSkeleton.getConsistency() > skeletonThreshold) {
            peopleArray.append(makeOutputString(* singlePersonSkeleton.getSkeletonPoints3D(), singlePersonSkeleton.getBodyKeyPointsMap(), nFrame, (unsigned int) i));
        }
    }
    
    root["People"] = peopleArray;
    OutputManager::setStringOutputData(root.toStyledString());
    outputJsonFilePath << outputFolder << "movement/frame" << nFrame << "_" << JSON_FILE_PATH;
    saveJSON(std::string(outputJsonFilePath.str()));
    outputJsonFilePath.str(std::string());
    outputJsonFilePath.clear();
}
