#include <iostream>
#include <SDL2/SDL.h>

#include "Window/Window.h"

int frameCount = 0;
void drawUpdateLine(Window& window) {
    frameCount++;
    if(frameCount >= window.getHeight()) {
        frameCount = 0;
    }
    for (int x = 0; x < window.getWidth(); x++) {
        int y = (frameCount + x) % window.getHeight();
        window.setPixel(x, y, 0xFFFFFFFF); // White pixel
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    Window window("Test Window", 400, 300);

    int gridSize = 100;

    //Color pattern test
    uint32_t test[gridSize * gridSize];
    for(int i = 0; i < gridSize; i++){
        for(int j = 0; j < gridSize; j++){
            if((i + j) % 2 == 0){
                test[i + j * gridSize] = 0xFF00FFFF; // Cyan
            }else{
                test[i + j * gridSize] = 0xFFFF00FF; // Yellow
            }
        }
    }

    uint32_t opacity_test[gridSize * gridSize];
    for(int i = 0; i < gridSize; i++){
        for(int j = 0; j < gridSize; j++){
            uint8_t alpha = static_cast<uint8_t>((((float)i)/(float)gridSize) * 256);
            opacity_test[i + j * gridSize] = (alpha) | 0x00FF0000; // Green with varying opacity
        }
    }

    //Opacity Test



    while(window.isOpen()) {
        window.pollEvents();
        window.clear(0x000000FF);

        drawUpdateLine(window);


        window.setWindow(gridSize * 0, gridSize * 0, gridSize, gridSize, test);

        window.setWindow(gridSize * 1, gridSize * 0, gridSize, gridSize, opacity_test);

        window.setPixel(200, 150, 0xFF0000FF); // Red pixel in center
        window.update();
    }
    return 0;
}