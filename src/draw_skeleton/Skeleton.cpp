//
//  Skeleton.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 17/07/22.
//

#include "Skeleton.hpp"



void Skeleton::setImage (cv::Mat & myImage) {
    this->myImage = myImage;
}

void Skeleton::setBodyKeyPoints (std::vector <SingleBodyKeypoint> & bodyKeyPoints) {
    this->bodyKeyPoints = bodyKeyPoints;
}

void Skeleton::setBodyKeyPointsMap (std::vector <bool> & bodyKeyPointsMap) {
    this->bodyKeyPointsMap = bodyKeyPointsMap;
}

void Skeleton::setSkeletonData (Json::Value skeletonData) {
    this->skeletonData = skeletonData;
}

cv::Mat Skeleton::getImage() {
    return this->myImage;
}

std::vector <SingleBodyKeypoint> Skeleton::getBodyKeyPoints (void) {
    return this->bodyKeyPoints;
}

std::vector <bool> Skeleton::getBodyKeyPointsMap (void) {
    return this->bodyKeyPointsMap;
}

Json::Value Skeleton::getSkeletonData (void) {
    return this->skeletonData;
}

void Skeleton::drawBodyKeypoints () {
    int j = 0;
    for (Json::Value::ArrayIndex i = 0; i != skeletonData.size(); i++) {
        bodyKeyPoints.push_back(SingleBodyKeypoint(skeletonData[i].asInt(), skeletonData[i + 1].asInt(), skeletonData[i + 2].asFloat()));
        bodyKeyPointsMap.push_back(bodyKeyPoints.at(j).getX() > 0 && bodyKeyPoints.at(j).getY() > 0 && bodyKeyPoints.at(j).getConfidence() > 0.00);
        i += 2;
        j += 1;
    }
}

void Skeleton::drawBodyEdges () {
    for (int i = 0; i < bodyKeyPoints.size(); i++) {
        if (!bodyKeyPointsMap.at(i)) continue;
        cv::circle(getImage(), cv::Point(getBodyKeyPoints().at(i).getX(), getBodyKeyPoints().at(i).getY()), 4, cv::Scalar(0, 0, 255), 8, cv::LINE_8, 0);
        if (i >= 24 || (!getBodyKeyPointsMap().at(i))) continue;
        
        switch (i) {
            case Nose ... RElbow:
            case LShoulder ... LElbow:
            case MidHip ... RKnee:
            case LHip ... LKnee:
            case LBigToe:
            case RBigToe:
                if (!getBodyKeyPointsMap().at(i)) break;
                drawLine(i, i + 1);
                break;
            default:
                break;
        }
    }
    
    drawLine(Neck, LShoulder);
    drawLine(Neck, MidHip);
    drawLine(MidHip, LHip);
    drawLine(REye, Nose);
    drawLine(REye, REar);
    drawLine(LEye, Nose);
    drawLine(LEye, LEar);
    
    drawLine(LAnkle, LBigToe);
    drawLine(LAnkle, LHeel);
    
    drawLine(RAnkle, RBigToe);
    drawLine(RAnkle, RHeel);
}

void Skeleton::drawLine (int start, int end) {
    if (getBodyKeyPointsMap().at(start) && getBodyKeyPointsMap().at(end)) {
        cv::line(myImage, cv::Point(getBodyKeyPoints().at(start).getX(), getBodyKeyPoints().at(start).getY()), cv::Point(getBodyKeyPoints().at(end).getX(), getBodyKeyPoints().at(end).getY()), cv::Scalar(0, 255, 0), 3, cv::LINE_8, 0);
    }
}



Skeleton::Skeleton (cv::Mat & myImage, std::vector <SingleBodyKeypoint> & bodyKeyPoints, std::vector <bool> & bodyKeyPointsMap, Json::Value skeletonData) {
    setImage(myImage);
    setBodyKeyPoints(bodyKeyPoints);
    setBodyKeyPointsMap(bodyKeyPointsMap);
    setSkeletonData(skeletonData);
    this->skeletonData = skeletonData;
}



