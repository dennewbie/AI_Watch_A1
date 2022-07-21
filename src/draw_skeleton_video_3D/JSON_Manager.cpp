//
//  JSON_Manager.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 21/07/22.
//

#include "JSON_Manager.hpp"

// da fare con stringstream


void JSON_Manager::makeJSON (std::vector <Point3D *> skeletonPoints3D) {
    Json::Value root;
    std::stringstream outputDataStringStream;
    
    Json::Value singlePoint3D_JSON;
//    for (auto singlePoint3D: skeletonPoints3D) {
        singlePoint3D_JSON["x"] = Json::Value(skeletonPoints3D.at(0)->getX());
        singlePoint3D_JSON["y"] = Json::Value(skeletonPoints3D.at(0)->getX());
        singlePoint3D_JSON["z"] = Json::Value(skeletonPoints3D.at(0)->getX());
        singlePoint3D_JSON["x_rotation"] = Json::Value(0.0);
        singlePoint3D_JSON["y_rotation"] = Json::Value(0.0);
        singlePoint3D_JSON["z_rotation"] = Json::Value(0.0);
        singlePoint3D_JSON["w_rotation"] = Json::Value(0.0);
        singlePoint3D_JSON["thingId"] = Json::Value(std::string("org.eclipse.ditto:camera01"));
//    }


    root["_Movement"] = singlePoint3D_JSON;
//   root["competitors"]["away"]["code"] = 89223;
//   root["competitors"]["away"]["name"] = "Aston Villa";
//   root["competitors"]["away"]["code"]=vec;
    
    std::cout << "\n" << root << "\n";
}

std::string JSON_Manager::getStringOutputData (void) {
    return this->outputData;
}
