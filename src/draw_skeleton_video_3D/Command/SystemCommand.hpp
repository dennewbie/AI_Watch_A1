//
//  SystemCommand.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#ifndef SystemCommand_hpp
#define SystemCommand_hpp

#include <string>
#include <sstream>
#include "FacadeSingleton.hpp"



class SystemCommand {
protected:
    std::string command;
    virtual void setCommand (void) = 0;
    std::string getCommand (void);
public:
    void executeCommand (void);
};

class CleanCommand : public SystemCommand {
protected:
    void setCommand (void) override;
};

class OpenPoseCommand : public SystemCommand {
protected:
    void setCommand (void) override;
};

class MoveCommand : public SystemCommand {
protected:
    void setCommand (void) override;
};

#endif /* SystemCommand_hpp */
