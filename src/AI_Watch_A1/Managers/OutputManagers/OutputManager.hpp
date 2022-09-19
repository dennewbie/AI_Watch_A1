//
//  OutputManager.hpp
//  AI Watch A1
//
//  Created by Denny Caruso on 23/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#ifndef OutputManager_hpp
#define OutputManager_hpp

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <json/json.h>
#include <json/value.h>
#include <opencv2/core.hpp>
#include "../../Points/Point3D.hpp"
#include "../../Points/BodyKeyPoint.hpp"
#include "../../Skeleton.hpp"



/**
 * @brief OutputManager class is a class that abstracts final output-producing operations.
 * An output format inherits from this class, such as OutputManagerJSON.
 */
class OutputManager {
private:
/**
 * @brief Output file's content.
 */
    std::string stringOutputData;
protected:
    /**
     * @brief Set the output file's content.
     * @param stringOutputData 
     */
    void setStringOutputData                    (std::string stringOutputData);
    /**
     * @brief Get the output file's content.
     * @return std::string 
     */
    std::string getStringOutputData             (void);
    /**
     * @brief This method has to be overridden from OutputManager's subclasses to fill the "stringOutputData" 
     * string with a certain value which will be saved later.
     * @param skeletonPoints3D A vector that contains pointers to Points3D whose coordinates represent the skeleton's junctions in certain space coordinates.
     * @param bodyKeyPointsMap A vector that contains for each body joint retrieved from OpenPose a corresponding boolean that means if that body joint 
     * is a valuable and effective body joint or not.
     * @param frameID current frame ID.
     * @param personID current person ID within the current frame.
     * @return Json::Value 
     */
    virtual Json::Value makeOutputString        (std::vector <Point3D *> skeletonPoints3D, std::vector <bool> bodyKeyPointsMap,
                                                 unsigned int frameID, unsigned int personID) = 0;
public:
    /**
     * @brief Destroy the Output Manager object.
     */
    virtual ~OutputManager() = default;
};



/**
 * @brief OutputManagerJSON class is a class that abstracts final JSON output-producing operations.
 */
class OutputManagerJSON : public OutputManager {    
protected:
    /**
     * @brief This method is specific for saving the output in JSON format.
     * @param skeletonPoints3D A vector that contains pointers to Points3D whose coordinates represent the skeleton's junctions in certain space coordinates.
     * @param bodyKeyPointsMap A vector that contains for each body joint retrieved from OpenPose a corresponding boolean that means if that body joint 
     * is a valuable and effective body joint or not.
     * @param frameID current frame ID.
     * @param personID current person ID within the current frame.
     * @return Json::Value 
     */
    Json::Value makeOutputString                 (std::vector <Point3D *> skeletonPoints3D, std::vector <bool> bodyKeyPointsMap,
                                                  unsigned int frameID, unsigned int personID) override;
public:
    /**
     * @brief Loads a JSON file and returns it as a reference. The JSON file path on disk is given.
     * @param filePathJSON JSON file path on disk.
     * @param currentJSON JSON reference where the JSON file will be load.
     * @return true if the file-loading ends correctly.
     * @return false if the file-loading does not end correctly.
     */
    bool loadJSON                                (std::string filePathJSON, Json::Value & currentJSON);
    /**
     * @brief Saves content present in the "stringOutputData" in a JSON file. The file path where to save the file is given.
     * @param filePath The file path where to save the JSON file.
     */
    void saveJSON                                (std::string filePath);
    


    /**
     * @brief Utility method to get the value at a given key in a given JSON node.
     * @param key Key at which the value in the JSON node will be found.
     * @param currentJSON Reference to JSON node.
     * @return Json::Value 
     */
    Json::Value getValueAt                       (std::string key, Json::Value currentJSON);
    /**
     * @brief Utility method to get i-th value in a given JSON node.
     * @param i Index at which the value in the JSON node will be found.
     * @param currentJSON Reference to JSON node.
     * @return Json::Value 
     */
    Json::Value getValueAt                       (unsigned int i, Json::Value currentJSON);
    /**
     * @brief Utility method to get the value at a given key of the i-th value in a given JSON node.
     * @param key Key at which the value in the JSON node will be found.
     * @param i Index at which the value in the JSON node will be found.
     * @param currentJSON Reference to JSON node.
     * @return Json::Value 
     */
    Json::Value getValueAt                       (std::string key, unsigned int i, Json::Value currentJSON);
    /**
     * @brief This methods take a reference to a JSON node that represents all the people's informations within the frame,
     * color, depth, distance, and skeleton-only frame, the current frame ID, and the output folder's path on disk and for 
     * each person in the people's JSON node, the method extracts, generates, and appends a single Skeleton to the current JSON node.
     * @param people JSON node containing people's informations detected within the frame.
     * @param colorImage color frame.
     * @param distanceImage distance frame.
     * @param skeletonOnlyImage skeleton-only frame.
     * @param nFrame current image ID.
     * @param outputFolder output folder's path on disk.
     * @see Skeleton.hpp
     */
    void createJSON                              (Json::Value & people, cv::Mat & colorImage, cv::Mat & distanceImage, cv::Mat & skeletonOnlyImage,
                                                  unsigned int nFrame, const char * outputFolder);
};

#endif /* OutputManager_hpp */
