//
//  main.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 06/07/22.
//

#include "FacadeSingleton.hpp"
//#include "Managers/CoordinateMappingManager.hpp"



const int expected_argc = 5;
const char * expectedUsageMessage = "Usage: sudo ./hello_librealsense2.bin <path/openpose folder/> <./path/openpose.bin> "
                                    "<path/images folder/> <path/JSON output folder/>";



int main (int argc, const char * argv[]) {
//    CoordinateMappingManager manager = CoordinateMappingManager();
//    std::vector <Point3D *> points;
//    points.push_back(new Point3D(-0.69, 0.27, 2.215));
//    points.push_back(new Point3D(-0.69, -0.77, 2.215));
//    points.push_back(new Point3D(-0.69, -1.1, 2.215));
//    points.push_back(new Point3D(-0.69, 1.1, 2.215));
//    points.push_back(new Point3D(-0.69, 0.9, 2.215));
//    points.push_back(new Point3D(-0.69, 0.8, 2.215));
//    points.push_back(new Point3D(-0.69, 0.7, 2.215));
//    std::vector <Point3D *> newPoints = manager.mapToMeters(points);
//    for (auto singlePoint: newPoints) {
//        std::cout << "X: " << singlePoint->getX() << "\nY: " << singlePoint->getY() << "\nZ: " << singlePoint->getZ() << "\n\n";
//    }
    rs2::pipeline pipelineStream;
    Json::Value currentJSON;
    float scale;
    unsigned int user_nFrame = 50, resX = 848, resY = 480;
    struct rs2_intrinsics color_intrin;
    FacadeSingleton * myUtility = FacadeSingleton::getInstance(argc, argv, expected_argc, expectedUsageMessage);
    myUtility->startEnvironment(pipelineStream, color_intrin, & scale, resX, resY);

    while (true) {
        myUtility->getVideoFrames(user_nFrame, pipelineStream, scale);
//        myUtility->getVideoBodyKeyPoints();
        myUtility->showSkeleton(user_nFrame, currentJSON);
    }
    return EXIT_SUCCESS;
}

