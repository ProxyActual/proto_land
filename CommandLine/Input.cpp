#include "Input.h"

#include <thread>
#include <iostream>
#include <string>
#include <mutex>

void Input::startInputThread(){
    running = true;
    std::cout << "Starting input thread..." << std::endl;
    std::thread inputThread(&Input::runFunc, this);
    inputThread.detach();
}

bool Input::hasUpdate(){
    std::lock_guard<std::mutex> lock(messagesMutex);
    return messages.size() > 0;
}


void Input::runFunc(){
    while(running){
        std::string line;
        std::cout << "> ";
        if (std::getline(std::cin, line)) {
            std::lock_guard<std::mutex> lock(messagesMutex);
            messages.push_back(line);
        }
    }
}

std::string Input::getOldestString(){
    std::lock_guard<std::mutex> lock(messagesMutex);
    if (messages.empty()) {
        return "";
    }
    std::string oldest = messages.front();
    messages.erase(messages.begin());
    return oldest;
}