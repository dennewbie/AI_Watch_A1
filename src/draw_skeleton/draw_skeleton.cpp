/ Disegno Body Keypoints con OpenCV a partire da un JSON file
//
//  draw_skeleton.cpp
//  Costruzione Skeleton dato un file JSON
//
//  Created by Denny Caruso on 11/07/22
//

#include "Skeleton.hpp"

const int expected_argc = 3;
const char * expectedUsageMessage = "Usage: sudo ./hello_librealsense2.bin <path/image.jpeg> <path/file.json>";

int main (int argc, char * argv[]) {
    cv::Mat inputImage;
    Json::Value currentJSON;
    
    checkUsage (argc, (const char **) argv, expected_argc, expectedUsageMessage);
    loadImage(std::string(argv[1]), cv::IMREAD_COLOR, inputImage);
    loadJSON(argv[2], currentJSON);
    
    std::vector<SingleBodyKeypoint> bodyKeyPoints;
    std::vector<bool> bodyKeyPointsMap;
    cv::imshow("no circle", inputImage);
    
    Json::Value people = currentJSON["people"];
    for (Json::Value::ArrayIndex i = 0; i != people.size(); i++) {
        Json::Value singlePerson = (people[i])["pose_keypoints_2d"];
        Skeleton singlePersonSkeleton = Skeleton(inputImage, bodyKeyPoints, bodyKeyPointsMap, singlePerson);
        singlePersonSkeleton.drawSkeleton();
    }
    
    cv::imshow("circle w/lines", inputImage);
    cv::waitKey(0);
    return EXIT_SUCCESS;
}