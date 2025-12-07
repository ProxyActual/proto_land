#include <iostream>
#include "GraphicsWindow/GraphicsWindow.h"

int main() {
    std::cout << "Space Trader Game Initialized!" << std::endl;
    // Game initialization logic goes here
    GraphicsWindow graphicsWindow("Space Trader", 800, 600);

    gItem* testItem = new gItem({200, 200}, {100, 100}, 0.0f);
    
    for(int x = 0; x < 100; x++){
        for(int y = 0; y < 100; y++){
            testItem->setPixel(x, y, 0xfff000ff);
        }
    }
    
    graphicsWindow.addItem(testItem);

    int frameCount = 0;

    while(graphicsWindow.isOpen()) {
        frameCount++;
        graphicsWindow.pollEvents();
        graphicsWindow.update();
        testItem->setRotation((frameCount + rand()) % 360);
        // Game loop logic goes here
    }

    return 0;
}