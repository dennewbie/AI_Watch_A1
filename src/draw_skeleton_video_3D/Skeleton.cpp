//
//  Skeleton.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 17/07/22.
//

#include "Skeleton.hpp"



void Skeleton::setRGB_Image (cv::Mat & myImage) {
    this->rgbImage = myImage;
}

void Skeleton::setD_Image (cv::Mat & myImage) {
    this->dImage = myImage;
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

cv::Mat Skeleton::getRGB_Image() {
    return this->rgbImage;
}

cv::Mat Skeleton::getD_Image() {
    return this->dImage;
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

void Skeleton::setSkeletonPoints3D (std::vector <SinglePoint3D *> skeletonPoints3D) {
    this->skeletonPoints3D = skeletonPoints3D;
}

std::vector <SinglePoint3D *> Skeleton::getSkeletonPoints3D (void) {
    return this->skeletonPoints3D;
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
        cv::circle(getRGB_Image(), cv::Point(getBodyKeyPoints().at(i).getX(), getBodyKeyPoints().at(i).getY()), 4, cv::Scalar(0, 0, 255), 8, cv::LINE_8, 0);
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

void Skeleton::writeCoordinates () {
    for (int i = 0; i < getSkeletonPoints3D().size(); i++) {
        if (getBodyKeyPoints().at(i).getX() == 0 && getBodyKeyPoints().at(i).getY() == 0) continue;
        std::stringstream labelText1, labelText2, labelText3;
        labelText1 << getSkeletonPoints3D().at(i)->getX();
        labelText2 << getSkeletonPoints3D().at(i)->getY();
        labelText3 << getSkeletonPoints3D().at(i)->getZ();
        cv::putText(getRGB_Image(), labelText1.str(), cv::Point(getBodyKeyPoints().at(i).getX() + 10, getBodyKeyPoints().at(i).getY() + 10), cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(255, 0, 0), 1, cv::LINE_8);
        cv::putText(getRGB_Image(), labelText2.str(), cv::Point(getBodyKeyPoints().at(i).getX() + 10, getBodyKeyPoints().at(i).getY() + 25), cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(255, 0, 0), 1, cv::LINE_8);
        cv::putText(getRGB_Image(), labelText3.str(), cv::Point(getBodyKeyPoints().at(i).getX() + 10, getBodyKeyPoints().at(i).getY() + 40), cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(255, 0, 0), 1, cv::LINE_8);
    }
}

void Skeleton::drawLine (int start, int end) {
    if (getBodyKeyPointsMap().at(start) && getBodyKeyPointsMap().at(end)) {
        cv::line(rgbImage, cv::Point(getBodyKeyPoints().at(start).getX(), getBodyKeyPoints().at(start).getY()), cv::Point(getBodyKeyPoints().at(end).getX(), getBodyKeyPoints().at(end).getY()), cv::Scalar(0, 255, 0), 3, cv::LINE_8, 0);
    }
}

void Skeleton::deprojectSkeletonPoints3D (struct rs2_intrinsics & color_intrin) {
    for (auto singleBodyKeyPoint: getBodyKeyPoints()) {
        if (singleBodyKeyPoint.getX() == 0 && singleBodyKeyPoint.getY() == 0) continue;
        float * pixel =  (float *) calloc(2, sizeof(float));
        float * point = (float *) calloc(3, sizeof(float));
        pixel[0] = singleBodyKeyPoint.getX();
        pixel[1] = singleBodyKeyPoint.getY();
        float distance = getD_Image().at<float>(pixel[1], pixel[0]);
        
        rs2_deproject_pixel_to_point(point, & color_intrin, pixel, distance);
        SinglePoint3D * point3D = new SinglePoint3D(point[0], point[1], point[2]);
        skeletonPoints3D.push_back(point3D);
        free(pixel);
        free(point);
    }
}



Skeleton::Skeleton (cv::Mat & rgbImage, cv::Mat & dImage, std::vector <SingleBodyKeypoint> & bodyKeyPoints, std::vector <bool> & bodyKeyPointsMap, Json::Value skeletonData) {
    setRGB_Image(rgbImage);
    setD_Image(dImage);
    setBodyKeyPoints(bodyKeyPoints);
    setBodyKeyPointsMap(bodyKeyPointsMap);
    setSkeletonData(skeletonData);
}

void Skeleton::drawSkeleton (struct rs2_intrinsics & color_intrin) {
    drawBodyKeypoints();
    drawBodyEdges();
    deprojectSkeletonPoints3D(color_intrin);
    writeCoordinates();
}
