//
//  Skeleton.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 17/07/22.
//

#include "Skeleton.hpp"



void Skeleton::setRGB_Image (cv::Mat & myImage) {
    this->rgb_Image = myImage;
}

void Skeleton::setDistance_Image (cv::Mat & myImage) {
    this->distance_Image = myImage;
}

void Skeleton::setBodyKeyPoints (std::vector <BodyKeyPoint> & bodyKeyPoints) {
    this->bodyKeyPoints = bodyKeyPoints;
}

void Skeleton::setBodyKeyPointsMap (std::vector <bool> & bodyKeyPointsMap) {
    this->bodyKeyPointsMap = bodyKeyPointsMap;
}

void Skeleton::setSkeletonData (Json::Value skeletonData) {
    this->skeletonData = skeletonData;
}

void Skeleton::set_color_intrin (struct rs2_intrinsics & color_intrin) {
    this->color_intrin = color_intrin;
}

void Skeleton::setSkeletonPoints3D (std::vector <Point3D *> skeletonPoints3D) {
    this->skeletonPoints3D = skeletonPoints3D;
}



cv::Mat Skeleton::getRGB_Image(void) {
    return this->rgb_Image;
}

cv::Mat Skeleton::getDistance_Image(void) {
    return this->distance_Image;
}

std::vector <BodyKeyPoint> Skeleton::getBodyKeyPoints (void) {
    return this->bodyKeyPoints;
}

std::vector <bool> Skeleton::getBodyKeyPointsMap (void) {
    return this->bodyKeyPointsMap;
}

Json::Value Skeleton::getSkeletonData (void) {
    return this->skeletonData;
}

struct rs2_intrinsics & Skeleton::get_color_intrin (void) {
    return this->color_intrin;
}

std::vector <Point3D *> Skeleton::getSkeletonPoints3D (void) {
    return this->skeletonPoints3D;
}



void Skeleton::calcBodyKeypoints (void) {
    int j = 0;
    for (Json::Value::ArrayIndex i = 0; i < skeletonData.size(); i++) {
        bodyKeyPoints.push_back(BodyKeyPoint(skeletonData[i].asInt(), skeletonData[i + 1].asInt(), skeletonData[i + 2].asFloat()));
        bodyKeyPointsMap.push_back(bodyKeyPoints.at(j).getX() > 0 && bodyKeyPoints.at(j).getY() > 0 && bodyKeyPoints.at(j).getConfidence() > 0.00);
        i += 2;
        j += 1;
    }
}

void Skeleton::calcBodyEdges (void) {
    for (int i = 0; i < getBodyKeyPoints().size(); i++) {
        if (!getBodyKeyPointsMap().at(i)) continue;
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

void Skeleton::drawLine (int start, int end) {
    if (getBodyKeyPointsMap().at(start) && getBodyKeyPointsMap().at(end)) {
        cv::line(getRGB_Image(), cv::Point(getBodyKeyPoints().at(start).getX(), getBodyKeyPoints().at(start).getY()),
                 cv::Point(getBodyKeyPoints().at(end).getX(), getBodyKeyPoints().at(end).getY()), cv::Scalar(0, 255, 0), 3, cv::LINE_8, 0);
    }
}

void Skeleton::writeCoordinates (void) {
    for (int i = 0; i < getSkeletonPoints3D().size(); i++) {
        // here
//        if ((getBodyKeyPoints().at(i).getX() == 0 && getBodyKeyPoints().at(i).getY() == 0) || !getBodyKeyPointsMap().at(i)) continue;
        if (!getBodyKeyPointsMap().at(i)) continue;
        std::stringstream labelText1, labelText2, labelText3;
        labelText1 << getSkeletonPoints3D().at(i)->getX();
        labelText2 << getSkeletonPoints3D().at(i)->getY();
        labelText3 << getSkeletonPoints3D().at(i)->getZ();
        cv::putText(getRGB_Image(), labelText1.str(), cv::Point(getBodyKeyPoints().at(i).getX() + 10, getBodyKeyPoints().at(i).getY() + 10), cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(255, 0, 0), 1, cv::LINE_8);
        cv::putText(getRGB_Image(), labelText2.str(), cv::Point(getBodyKeyPoints().at(i).getX() + 10, getBodyKeyPoints().at(i).getY() + 25), cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(255, 0, 0), 1, cv::LINE_8);
        cv::putText(getRGB_Image(), labelText3.str(), cv::Point(getBodyKeyPoints().at(i).getX() + 10, getBodyKeyPoints().at(i).getY() + 40), cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(255, 0, 0), 1, cv::LINE_8);
    }
}

void Skeleton::deprojectSkeletonPoints3D () {
    for (int i = 0; i < getBodyKeyPoints().size(); i++) {
        if (getBodyKeyPoints().at(i).getX() == 0 && getBodyKeyPoints().at(i).getY() == 0 && getBodyKeyPoints().at(i).getConfidence() == 0) continue;
        if (!getBodyKeyPointsMap().at(i)) continue;
        float * pixel = new float [2];
        float * point = new float [3];
        if (!pixel || !point) CV_Error(CALLOC_ERROR, CALLOC_SCOPE);
        
        pixel[0] = getBodyKeyPoints().at(i).getX();
        pixel[1] = getBodyKeyPoints().at(i).getY();
        float distance = getDistance_Image().at<float>(pixel[1], pixel[0]);
        rs2_deproject_pixel_to_point(point, & get_color_intrin(), pixel, distance);
        Point3D * point3D = new Point3D(point[0], point[1], point[2]);
        skeletonPoints3D.push_back(point3D);
        delete [] pixel;
        delete [] point;
    }
}



Skeleton::Skeleton (cv::Mat & rgbImage, cv::Mat & dImage, Json::Value skeletonData, struct rs2_intrinsics & color_intrin) {
    setRGB_Image(rgbImage);
    setDistance_Image(dImage);
    setSkeletonData(skeletonData);
    set_color_intrin(color_intrin);
}

Skeleton::~Skeleton(void) {
    for (auto & point: getSkeletonPoints3D()) delete point;
    getSkeletonPoints3D().clear();
}

void Skeleton::drawSkeleton () {
    calcBodyKeypoints();
    calcBodyEdges();
    deprojectSkeletonPoints3D();
    writeCoordinates();
}
