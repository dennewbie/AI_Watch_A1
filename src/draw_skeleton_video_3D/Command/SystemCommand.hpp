//
//  SystemCommand.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 23/07/22.
//

#ifndef SystemCommand_hpp
#define SystemCommand_hpp

#include <sstream>
#include "../Managers/UsageManager.hpp"



class SystemCommand {
private:
    std::string command;
protected:
    virtual void setCommand (void) = 0;
    void setCommand (std::string command);
    std::string getCommand (void);
public:
    virtual ~SystemCommand() = default;
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
