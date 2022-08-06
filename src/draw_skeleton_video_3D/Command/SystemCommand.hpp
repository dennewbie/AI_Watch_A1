//
//  SystemCommand.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#ifndef SystemCommand_hpp
#define SystemCommand_hpp

#include "../FacadeSingleton/FacadeSingleton.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include "../Managers/UsageManager.hpp"



class SystemCommand {
private:
    std::string command;
protected:
    virtual void setCommand (int * argc, char *** argv) = 0;
    void setCommand (std::string command);
    std::string getCommand (void);
public:
    virtual ~SystemCommand() = default;
    void executeCommand (int * argc, char *** argv);
};

class CleanCommand : public SystemCommand {
protected:
    void setCommand (int * argc, char *** argv) override;
};

class OpenPoseCommand : public SystemCommand {
protected:
    void setCommand (int * argc, char *** argv) override;
};

class MoveCommand : public SystemCommand {
protected:
    void setCommand (int * argc, char *** argv) override;
};

#endif /* SystemCommand_hpp */
