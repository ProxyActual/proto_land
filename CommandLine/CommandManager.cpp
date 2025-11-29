#include "CommandManager.h"
#include <iostream>

CommandManager::CommandManager() {
}

CommandManager::~CommandManager() {
}

void CommandManager::executeCommand(const std::string& command) {
    COMMAND_TYPE cmdType = parseCommand(command);
    switch (cmdType) {
        case COMMAND_TYPE::FRAMES:
            // Handle frames command
            break;
        case COMMAND_TYPE::EXIT:
            // Handle exit command
            break;
        case COMMAND_TYPE::HELP:
        default:
            handleHelpCommand();
            break;
    }
}

CommandManager::COMMAND_TYPE CommandManager::parseCommand(const std::string& command) {
    std::string cmd = command.substr(0, command.find(' '));
    
    if (cmd == "frames") {
        return COMMAND_TYPE::FRAMES;
    } else if (cmd == "exit") {
        return COMMAND_TYPE::EXIT;
    }
    
    return COMMAND_TYPE::HELP;
}

void CommandManager::handleFramesCommand(const std::string& args) {
    // Implementation for handling frames command
}

void CommandManager::handleExitCommand() {
    // Implementation for handling exit command
}

void CommandManager::handleHelpCommand() {
    std::cout << "Available commands:\n";
    for (const auto& cmd : commandList) {
        std::cout << " - " << cmd << "\n";
    }
}

