/ Disegno Body Keypoints con OpenCV a partire da un JSON file
//
//  draw_skeleton.cpp
//  Costruzione Skeleton dato un file JSON
//
//  Created by Denny Caruso on 11/07/22
//

#include <iostream>
#include <fstream>
#include <string>
#include "Skeleton.hpp"
    

int main (int argc, char * argv[]) {
    Json::Value actualJSON;
    Json::Reader readerJSON;
    std::ifstream streamJSON("op_output/cavani_keypoints.json", std::ifstream::binary);
    if (!(readerJSON.parse(streamJSON, actualJSON, false))) std::cout  << readerJSON.getFormattedErrorMessages() << "\n";
    std::cout << "\nBODY KEYPOINTS:\n";
    cv::Mat myImage = cv::imread("rs_images/cavani.jpeg", cv::IMREAD_COLOR);
    if (myImage.empty()) { std::cout << "\nError reading image"; return EXIT_FAILURE; }
    
    std::vector<SingleBodyKeypoint> bodyKeyPoints;
    std::vector<bool> bodyKeyPointsMap;
    cv::imshow("cavani no circle", myImage);
    Json::Value people = actualJSON["people"], singlePerson = (people[0])["pose_keypoints_2d"];
    Skeleton singlePersonSkeleton = Skeleton(myImage, bodyKeyPoints, bodyKeyPointsMap, singlePerson);
    singlePersonSkeleton.drawSkeleton();
    
    cv::imshow("cavani circle w/lines", myImage);
    cv::waitKey(0);
    return EXIT_SUCCESS;
}