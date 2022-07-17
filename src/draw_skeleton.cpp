/ Disegno Body Keypoints con OpenCV a partire da un JSON file
//
//  draw_skeleton.cpp
//  Costruzione Skeleton dato un file JSON
//
//  Created by Denny Caruso on 11/07/22
//

#include <iostream>
#include <json/json.h>
#include <json/value.h>
#include <fstream>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>

class SingleBodyKeypoint {
public:
    int x;
    int y;
    float confidence;
    
    SingleBodyKeypoint() {
        this->x = 0;
        this->y = 0;
        this->confidence = 0.0;
    }
    
    SingleBodyKeypoint(int x, int y, float confidence) {
        this->x = x;
        this->y = y;
        this->confidence = confidence;
    }
};

class Skeleton {
private:
    cv::Mat myImage;
    std::vector <SingleBodyKeypoint> bodyKeyPoints;
    std::vector <bool> bodyKeyPointsMap;
    Json::Value skeletonData;
    
    cv::Mat getImage (void) {
        return this->myImage;
    }
   
    std::vector <SingleBodyKeypoint> getBodyKeyPoints (void) {
        return this->bodyKeyPoints;
    }
    
    std::vector <bool> getBodyKeyPointsMap (void) {
        return this->bodyKeyPointsMap;
    }
    
    Json::Value getSkeletonData (void) {
        return this->skeletonData;
    }
    
    void drawBodyKeypoints () {
        int j = 0;
        for (Json::Value::ArrayIndex i = 0; i != skeletonData.size(); i++) {
            bodyKeyPoints.push_back(SingleBodyKeypoint(skeletonData[i].asInt(), skeletonData[i + 1].asInt(), skeletonData[i + 2].asFloat()));
            bodyKeyPointsMap.push_back(bodyKeyPoints.at(j).x > 0 && bodyKeyPoints.at(j).y > 0 && bodyKeyPoints.at(j).confidence > 0.00);
            i += 2;
            j += 1;
        }
    }
    
    void drawBodyEdges () {
        for (int i = 0; i < bodyKeyPoints.size(); i++) {
            if (!bodyKeyPointsMap.at(i)) continue;
            cv::circle(myImage, cv::Point(bodyKeyPoints[i].x, bodyKeyPoints[i].y), 4, cv::Scalar(0, 0, 255), 8, cv::LINE_8, 0);
            if (i >= 24 || (!bodyKeyPointsMap.at(i))) continue;
            
            switch (i) {
                case 0 ... 3:
                case 5 ... 6:
                case 8 ... 10:
                case 12 ... 13:
                case 19:
                case 22:
                    cv::line(myImage, cv::Point(bodyKeyPoints[i].x, bodyKeyPoints[i].y), cv::Point(bodyKeyPoints[i + 1].x, bodyKeyPoints[i + 1].y), cv::Scalar(0, 255, 0), 3, cv::LINE_8, 0);
                    break;
                default:
                    break;
            }
        }

        if (bodyKeyPointsMap.at(1) && bodyKeyPointsMap.at(5)) {
            cv::line(myImage, cv::Point(bodyKeyPoints[1].x, bodyKeyPoints[1].y), cv::Point(bodyKeyPoints[5].x, bodyKeyPoints[5].y), cv::Scalar(0, 255, 0), 3, cv::LINE_8, 0);
        }

        if (bodyKeyPointsMap.at(1) && bodyKeyPointsMap.at(8)) {
            cv::line(myImage, cv::Point(bodyKeyPoints[1].x, bodyKeyPoints[1].y), cv::Point(bodyKeyPoints[8].x, bodyKeyPoints[8].y), cv::Scalar(0, 255, 0), 3, cv::LINE_8, 0);
        }

        if (bodyKeyPointsMap.at(8) && bodyKeyPointsMap.at(12)) {
            cv::line(myImage, cv::Point(bodyKeyPoints[8].x, bodyKeyPoints[8].y), cv::Point(bodyKeyPoints[12].x, bodyKeyPoints[12].y), cv::Scalar(0, 255, 0), 3, cv::LINE_8, 0);
        }

        if (bodyKeyPointsMap.at(15) && bodyKeyPointsMap.at(0)) {
            cv::line(myImage, cv::Point(bodyKeyPoints[15].x, bodyKeyPoints[15].y), cv::Point(bodyKeyPoints[0].x, bodyKeyPoints[0].y), cv::Scalar(0, 255, 0), 3, cv::LINE_8, 0);
        }

        if (bodyKeyPointsMap.at(15) && bodyKeyPointsMap.at(17)) {
            cv::line(myImage, cv::Point(bodyKeyPoints[15].x, bodyKeyPoints[15].y), cv::Point(bodyKeyPoints[17].x, bodyKeyPoints[17].y), cv::Scalar(0, 255, 0), 3, cv::LINE_8, 0);
        }

        if (bodyKeyPointsMap.at(16) && bodyKeyPointsMap.at(0)) {
            cv::line(myImage, cv::Point(bodyKeyPoints[16].x, bodyKeyPoints[16].y), cv::Point(bodyKeyPoints[0].x, bodyKeyPoints[0].y), cv::Scalar(0, 255, 0), 3, cv::LINE_8, 0);
        }

        if (bodyKeyPointsMap.at(16) && bodyKeyPointsMap.at(18)) {
            cv::line(myImage, cv::Point(bodyKeyPoints[16].x, bodyKeyPoints[16].y), cv::Point(bodyKeyPoints[18].x, bodyKeyPoints[18].y), cv::Scalar(0, 255, 0), 3, cv::LINE_8, 0);
        }

        if (bodyKeyPointsMap.at(19) && bodyKeyPointsMap.at(21)) {
            cv::line(myImage, cv::Point(bodyKeyPoints[19].x, bodyKeyPoints[19].y), cv::Point(bodyKeyPoints[21].x, bodyKeyPoints[21].y), cv::Scalar(0, 255, 0), 3, cv::LINE_8, 0);
        }

        if (bodyKeyPointsMap.at(14) && bodyKeyPointsMap.at(21)) {
            cv::line(myImage, cv::Point(bodyKeyPoints[14].x, bodyKeyPoints[14].y), cv::Point(bodyKeyPoints[21].x, bodyKeyPoints[21].y), cv::Scalar(0, 255, 0), 3, cv::LINE_8, 0);
        }

        if (bodyKeyPointsMap.at(11) && bodyKeyPointsMap.at(22)) {
            cv::line(myImage, cv::Point(bodyKeyPoints[15].x, bodyKeyPoints[15].y), cv::Point(bodyKeyPoints[0].x, bodyKeyPoints[0].y), cv::Scalar(0, 255, 0), 3, cv::LINE_8, 0);
        }

        if (bodyKeyPointsMap.at(11) && bodyKeyPointsMap.at(24)) {
            cv::line(myImage, cv::Point(bodyKeyPoints[11].x, bodyKeyPoints[11].y), cv::Point(bodyKeyPoints[24].x, bodyKeyPoints[24].y), cv::Scalar(0, 255, 0), 3, cv::LINE_8, 0);
        }
    }
    
public:
    Skeleton (cv::Mat & myImage, std::vector <SingleBodyKeypoint> & bodyKeyPoints, std::vector <bool> & bodyKeyPointsMap, Json::Value skeletonData) {
        this->myImage = myImage;
        this->bodyKeyPoints = bodyKeyPoints;
        this->bodyKeyPointsMap = bodyKeyPointsMap;
        this->skeletonData = skeletonData;
    }
    
    void drawSkeleton () {
        drawBodyKeypoints();
        drawBodyEdges();
    }
};

int main (int argc, char * argv[]) {
    Json::Value actualJSON;   // will contains the root value after parsing.
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