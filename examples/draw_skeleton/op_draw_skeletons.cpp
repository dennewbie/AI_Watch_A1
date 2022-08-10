/ Disegno Body Keypoints con OpenCV a partire da un JSON file
//
//  draw_skeleton.cpp
//  Costruzione Skeletons dato un file JSON prodotto da OpenPose
//
//  Created by Denny Caruso on 11/07/22
//

#include "Skeleton.hpp"
#include <sstream>

const int expected_argc = 7;
const char * expectedUsageMessage = "Usage: sudo ./hello_librealsense2.bin <path/image.jpeg> <path/openpose folder> <./path/openpose.bin> <path/images folder> <path/JSON output folder>  <path/output file.json>";

int main (int argc, char * argv[]) {
    cv::Mat inputImage;
    Json::Value currentJSON;
    
    checkUsage (argc, (const char **) argv, expected_argc, expectedUsageMessage);
    loadImage(std::string(argv[1]), cv::IMREAD_COLOR, inputImage);
    std::stringstream terminalCommand;
    terminalCommand << "cd " << argv[2] << " && " << argv[3] << " --num_gpu 1 --num_gpu_start 2 --display 0 --render_pose 0 --image_dir " << argv[4] << " --write_json " << argv[5];
    
    std::system(terminalCommand.str().c_str());
    std::vector<SingleBodyKeypoint> bodyKeyPoints;
    std::vector<bool> bodyKeyPointsMap;
    cv::imshow("no circle", inputImage);
    
    loadJSON(argv[6], currentJSON);
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