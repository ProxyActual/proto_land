#include <iostream>
#include "SpaceTrader/Core.h"

int main() {
    std::cout << "Space Trader Game Initialized!" << std::endl;

    SpaceTraderCore core;
    core.run();

    return 0;
}