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



/**
 * SystemCommand class is a class that represents a command given by the program to the system. 
 * Examples of commands are the following: start and run OpenPose, move files, and clean the build folder 
 * by deleting old files. SystemCommand implements a variant of the Command design pattern. 
 * Each concrete command is realized by a specific subclass that implements the parent abstract method.
 * @brief SystemCommand class is a class that represents a command given by the program to the system. 
 */
class SystemCommand {
private:
    /**
     * @brief The final command given to the system by the program.
     */
    std::string command;
protected:
    /**
     * @brief Set the string command. The method is inherited from the subclasses and overridden in order to express a specific behavior.
     * @param argc pointer to argc based on what program reads from configuration file.
     * @param argv pointer to argv based on what program reads from configuration file.
     */
    virtual void setCommand (int * argc, char *** argv) = 0;
    /**
     * @brief Set the string command with a particularly given string passed as a parameter.
     * @param command 
     */
    void setCommand (std::string command);
    /**
     * @brief Get the string command.
     * @return std::string 
     */
    std::string getCommand (void);
public:
    /**
     * @brief Destroy the SystemCommand object.
     */
    virtual ~SystemCommand() = default;
    /**
     * @brief This method is responsible for executing commands on the system based on the filled command string.
     * If the string is empty, then no command is executed.
     * @param argc pointer to argc from the main function or based on what the program reads from the configuration file.
     * @param argv pointer to argv from the main function or based on what the program reads from the configuration file.
     */
    void executeCommand (int * argc, char *** argv);
};



/**
 * The CleanCommand class is a class that implements a command to clean the build folder by deleting old files. 
 * It deletes all the images captured and computed when the current "JSONs's sending session with Kafka" 
 * is completed, as well as it deletes all the JSONs files produced in the meanwhile.
 * @brief The CleanCommand class is a class that implements a command to clean the build folder by deleting old files. 
 */
class CleanCommand : public SystemCommand {
protected:
    /**
     * @brief Set the string command to a cleaning command.
     * @param argc pointer to argc based on what the program reads from the configuration file.
     * @param argv pointer to argv based on what the program reads from the configuration file.
     */
    void setCommand (int * argc, char *** argv) override;
};



/**
 * @brief The OpenPoseCommand class is a class that implements a command to start and run OpenPose.
 */
class OpenPoseCommand : public SystemCommand {
protected:
    /**
     * @brief Set the string command to an OpenPose properly formatted command.
     * @param argc pointer to argc from the main function.
     * @param argv pointer to argv from the main function.
     */
    void setCommand (int * argc, char *** argv) override;
};



/**
 * @brief The MoveCommand class is a class that implements a command to move files through specific directories.
 */
class MoveCommand : public SystemCommand {
protected:
    /**
     * @brief Set the string command to moving files through the directories command.
 * @param argc pointer to argc based on what the program reads from the configuration file.
     * @param argv pointer to argv based on what the program reads from the configuration file.
     */
    void setCommand (int * argc, char *** argv) override;
};

#endif /* SystemCommand_hpp */
