#include <iostream>
#include <SDL2/SDL.h>
#include "Window/Window.h"

bool movePane = false;

int main(int argc, char* argv[]) {
    std::cout << "GraphicsEngine WindowCore test" << std::endl;

    Window window("Test Window", 800, 600);
    Pane pane1(50, 50, 200, 150);
    Pane subPane1(20, 20, 100, 75);
    Pane subSubPane(10, 10, 50, 30);
    subSubPane.visable = true;
    pane1.visable = true;
    subPane1.visable = true;
    pane1.addChildPane(&subPane1);
    subPane1.addChildPane(&subSubPane);

    subSubPane.setBaseImagePath("TestImage/Untitled.bmp");

    for(int x = 0; x < subPane1.getWidth(); x++){
        for(int y = 0; y < subPane1.getHeight(); y++){
            subPane1.setPixel(x, y, 0x8000FF00); // Semi-transparent green

            if(x == subPane1.getWidth()/2 || y == subPane1.getHeight()/2){
                subPane1.setPixel(x, y, 0xFFFF00FF); // Opaque magenta crosshair
            }
        }
    }

    for(int x = 0; x < subSubPane.getWidth(); x++){
        for(int y = 0; y < subSubPane.getHeight(); y++){
            if(x == subSubPane.getWidth()/2 || y == subSubPane.getHeight()/2){
                subSubPane.setPixel(x, y, 0xFFFFFF00); // Opaque yellow crosshair
            }
        }
    }

    subSubPane.setPixel(0, 0, 0xFFFF0000); // Top-left pixel red
    pane1.setPixel(0, 0, 0xFF0000FF); // Top-left pixel blue

    window.addPane(&pane1);

    int frameCount = 0;
    while(window.isOpen()){
        for(int y = 0; y < pane1.getHeight(); y++){
            for(int x = 0; x < pane1.getWidth(); x++){
                uint32_t color = 0x00000000;
                uint8_t opacity = (x / static_cast<float>(pane1.getWidth())) * 255;
                color |= (opacity << 24); // Set alpha channel
                color |= 0x00FF0000; // Set red channel
                pane1.setPixel((frameCount + x) % pane1.getWidth(), y, color);
            }
        }
        frameCount++;
        window.clear(0x00000000); // Clear to black

        subPane1.setRotation(frameCount % 360);
        pane1.setRotation((frameCount / 2) % 360);

        if(movePane){
            if(pane1.getSetLocation()->x < 800){
                pane1.getSetLocation()->x += 1;
            }else{
                pane1.getSetLocation()->x = 50;
            }
        }
        window.pollEvents();
        window.update();
    }
}