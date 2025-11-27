#include <iostream>
#include "externalThread.hpp"

int main() {
    externalThread thread;
    thread.start();

    while(true){
        std::string input;
        std::getline(std::cin, input);
        std::cout << "Count: " << thread.getCounter() << std::endl;
    }

    return 0;
}