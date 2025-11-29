#pragma once

#include <string>
#include <vector>
#include <mutex>

class Input{
    public:
        Input(){
            messages = std::vector<std::string>();
        }

        void startInputThread();

        bool hasUpdate();

        std::string getOldestString();

    private:
        void runFunc();

        std::vector<std::string> messages;   
        
        std::mutex messagesMutex;

        bool running = true;
};