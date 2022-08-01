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

void Skeleton::setSkeleton_Image (cv::Mat & myImage) {
    this->skeleton_Image = myImage;
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

void Skeleton::setSkeletonPoints3D_RS (std::vector <Point3D *> skeletonPoints3D_RS) {
    this->skeletonPoints3D_RS = skeletonPoints3D_RS;
}

void Skeleton::setSkeletonPoints3D (std::vector <Point3D *> * skeletonPoints3D) {
    this->skeletonPoints3D = skeletonPoints3D;
}



cv::Mat Skeleton::getRGB_Image(void) {
    return this->rgb_Image;
}

cv::Mat Skeleton::getDistance_Image(void) {
    return this->distance_Image;
}

cv::Mat Skeleton::getSkeleton_Image(void) {
    return this->skeleton_Image;
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

// Don't change following method, otherwise error
void Skeleton::calcBodyKeypoints (void) {
    int j = 0;
    unsigned char counterBodyKeyPointsMap = 0;
    FacadeSingleton * facadeSingletonInstance = FacadeSingleton::getInstance();
    if (facadeSingletonInstance == nullptr) CV_Error(FACADE_SINGLETON_NULLPTR_ERROR, FACADE_SINGLETON_NULLPTR_SCOPE);
    OutputManagerJSON * outputManagerJSON = (OutputManagerJSON *) facadeSingletonInstance->getOutputManager();
    for (Json::Value::ArrayIndex i = 0; i < skeletonData.size(); i++) {
        bodyKeyPoints.push_back(BodyKeyPoint(
                                 outputManagerJSON->getValueAt((unsigned int) i, getSkeletonData()).asInt(),
                                 outputManagerJSON->getValueAt((unsigned int) i + 1, getSkeletonData()).asInt(),
                                 outputManagerJSON->getValueAt((unsigned int) i + 2, getSkeletonData()).asFloat())
                                );
        
        bodyKeyPointsMap.push_back(bodyKeyPoints.at(j).getX() > 0 && bodyKeyPoints.at(j).getY() > 0 && bodyKeyPoints.at(j).getConfidence() > 0.00);
        if (bodyKeyPointsMap.back()) counterBodyKeyPointsMap += 1;
        i += 2;
        j += 1;
    }
}

void Skeleton::calcBodyEdges (void) {
    for (unsigned char i = 0; i < getBodyKeyPoints().size(); i++) {
        if (i >= openPoseBodyKeyPointsNumber || (!getBodyKeyPointsMap().at(i))) continue;
        drawCircle(cv::Point(getBodyKeyPoints().at(i).getX(), getBodyKeyPoints().at(i).getY()));
        
        switch (i) {
            case Nose ... RElbow:
            case LShoulder ... LElbow:
            case MidHip ... RKnee:
            case LHip ... LKnee:
            case LBigToe:
            case RBigToe:
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

void Skeleton::drawLine (unsigned char start, unsigned char end) {
    if (getBodyKeyPointsMap().at(start) && getBodyKeyPointsMap().at(end)) {
        cv::line(getRGB_Image(), cv::Point(getBodyKeyPoints().at(start).getX(), getBodyKeyPoints().at(start).getY()),
                 cv::Point(getBodyKeyPoints().at(end).getX(), getBodyKeyPoints().at(end).getY()), cv::Scalar(0, 255, 0), 3, cv::LINE_8, 0);
        cv::line(getSkeleton_Image(), cv::Point(getBodyKeyPoints().at(start).getX(), getBodyKeyPoints().at(start).getY()),
                 cv::Point(getBodyKeyPoints().at(end).getX(), getBodyKeyPoints().at(end).getY()), cv::Scalar(0, 255, 0), 3, cv::LINE_8, 0); // remove in future
    }
}

void Skeleton::drawCircle (cv::Point center) {
    cv::circle(getRGB_Image(), center, 4, cv::Scalar(0, 0, 255), 8, cv::LINE_8, 0);
    cv::circle(getSkeleton_Image(), center, 4, cv::Scalar(0, 0, 255), 8, cv::LINE_8, 0); // remove
}

void Skeleton::deprojectSkeletonPoints3D () {
    FacadeSingleton * facadeSingletonInstance = FacadeSingleton::getInstance();
    if (facadeSingletonInstance == nullptr) CV_Error(FACADE_SINGLETON_NULLPTR_ERROR, FACADE_SINGLETON_NULLPTR_SCOPE);
    struct rs2_intrinsics color_intrin = facadeSingletonInstance->getCameraManager()->get_color_intrin();
    drawCircle(cv::Point(848, 480));
    for (unsigned char i = 0; i < getBodyKeyPoints().size(); i++) {
        float * pixel = new (std::nothrow) float [2], * point = new (std::nothrow) float [3], distance = 0;
        if (!pixel || !point) CV_Error(CALLOC_ERROR, CALLOC_SCOPE);
        
        if (!getBodyKeyPointsMap().at(i)) {
            point[0] = point[1] = point[2] = pixel[0] = pixel[1] = 0;
        } else {
            pixel[0] = getBodyKeyPoints().at(i).getX();
            pixel[1] = getBodyKeyPoints().at(i).getY();
            distance = getDistance_Image().at<float>(pixel[1], pixel[0]);
            rs2_deproject_pixel_to_point(point, & color_intrin, pixel, distance);
        }

        Point3D * point3D = new Point3D(point[0], point[1], point[2], new BodyKeyPoint(0, 0, getBodyKeyPoints().at(i).getConfidence()));
        skeletonPoints3D_RS.push_back(point3D);
        delete [] pixel;
        delete [] point;
    }
}

void Skeleton::writeCoordinates (void) {
    for (unsigned char i = 0; i < getSkeletonPoints3D()->size(); i++) {
        std::stringstream labelTextX, labelTextY, labelTextZ, labelTextConfidence;
        labelTextX << getSkeletonPoints3D()->at(i)->getX();
        labelTextY << getSkeletonPoints3D()->at(i)->getY();
        labelTextZ << getSkeletonPoints3D()->at(i)->getZ();
        labelTextConfidence << ((BodyKeyPoint *) getSkeletonPoints3D()->at(i)->getDecorated())->getConfidence();
        
        if (i == 0) {
            cv::putText(getRGB_Image(), labelTextX.str(), cv::Point(getBodyKeyPoints().at(i).getX() + 10, getBodyKeyPoints().at(i).getY() + 10), cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(255, 0, 0), 1, cv::LINE_8);
            cv::putText(getRGB_Image(), labelTextY.str(), cv::Point(getBodyKeyPoints().at(i).getX() + 10, getBodyKeyPoints().at(i).getY() + 25), cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(255, 0, 0), 1, cv::LINE_8);
            cv::putText(getRGB_Image(), labelTextZ.str(), cv::Point(getBodyKeyPoints().at(i).getX() + 10, getBodyKeyPoints().at(i).getY() + 40), cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar(255, 0, 0), 1, cv::LINE_8);
        }
        
    }
}



Skeleton::Skeleton (cv::Mat & rgbImage, cv::Mat & dImage, cv::Mat & skeleton_Image, Json::Value skeletonData) {
    setRGB_Image(rgbImage);
    setDistance_Image(dImage);
    setSkeleton_Image(skeleton_Image);
    setSkeletonData(skeletonData);
}

Skeleton::~Skeleton(void) {
    for (auto & point: * getSkeletonPoints3D()) delete point;
    for (auto & point: getSkeletonPoints3D_RS()) delete point;
    getSkeletonPoints3D()->clear();
    if (getSkeletonPoints3D() != nullptr) delete getSkeletonPoints3D();
    getSkeletonPoints3D_RS().clear();
}

void Skeleton::drawSkeleton () {
    calcBodyKeypoints();
    calcBodyEdges();
    deprojectSkeletonPoints3D();
    FacadeSingleton * facadeSingletonInstance = FacadeSingleton::getInstance();
    if (facadeSingletonInstance == nullptr) CV_Error(FACADE_SINGLETON_NULLPTR_ERROR, FACADE_SINGLETON_NULLPTR_SCOPE);
    setSkeletonPoints3D(facadeSingletonInstance->getCoordinateMappingManager()->mapToMeters(getSkeletonPoints3D_RS(), getBodyKeyPointsMap(), zOriginUnity, xOriginUnity));
    writeCoordinates();
}

std::vector <Point3D *> Skeleton::getSkeletonPoints3D_RS (void) {
    return this->skeletonPoints3D_RS;
}

std::vector <Point3D *> * Skeleton::getSkeletonPoints3D (void) {
    return this->skeletonPoints3D;
}
