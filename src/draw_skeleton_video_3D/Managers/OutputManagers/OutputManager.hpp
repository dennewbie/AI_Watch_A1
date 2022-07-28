//
//  OutputManager.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

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
#include "../../constants.hpp"
#include "../../Points/Point3D.hpp"
#include "../../Points/BodyKeyPoint.hpp"



class OutputManager {
private:
    std::string stringOutputData;
protected:
    void setStringOutputData                    (std::string stringOutputData);
    std::string getStringOutputData             (void);
public:
    virtual ~OutputManager() = default;
    virtual void makeOutputString               (std::vector <Point3D *> skeletonPoints3D, std::vector <bool> bodyKeyPointsMap,
                                                 unsigned int frameID, unsigned int personID) = 0;
};

class OutputManagerJSON : public OutputManager {
public:
    void makeOutputString                        (std::vector <Point3D *> skeletonPoints3D, std::vector <bool> bodyKeyPointsMap,
                                                  unsigned int frameID, unsigned int personID) override;
    bool loadJSON                                (std::string filePathJSON, Json::Value & currentJSON);
    void saveJSON                                (std::string filePath);
    Json::Value getValueAt                       (std::string key, Json::Value currentJSON);
    Json::Value getValueAt                       (unsigned int i, Json::Value currentJSON);
    Json::Value getValueAt                       (std::string key, unsigned int i, Json::Value currentJSON);
};

#endif /* OutputManager_hpp */
