#pragma once

#include <string>

class CommandManager {
public:
    CommandManager();
    ~CommandManager();
    void executeCommand(const std::string& command);

private:
    enum class COMMAND_TYPE{
        FRAMES = 0,
        EXIT,
        HELP,
        MAX_COMMANDS
    };

    std::string commandList[static_cast<int>(COMMAND_TYPE::MAX_COMMANDS)] = {
        "frames",
        "exit",
        "help"
    };

    COMMAND_TYPE parseCommand(const std::string& command);

    void handleFramesCommand(const std::string& args);
    void handleExitCommand();
    void handleHelpCommand();
};