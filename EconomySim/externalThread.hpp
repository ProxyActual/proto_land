#pragma once

#include <thread>

class externalThread {
public:
    externalThread() = default;
    ~externalThread() = default;

    void start(){
        running = true;
        thread = std::thread(&externalThread::threadFunction, this);
    }

    void threadFunction(){
        while(running){
            counter++;
        }
    }

    int getCounter() const {
        return counter;
    }

    void stop()
    {
        running = false;
    }
private:
    bool running = false;

    int counter{0};

    std::thread thread;
};