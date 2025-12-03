#include <iostream>
#include <SDL2/SDL.h>
#include "Window/Window.h"

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

    subSubPane.setPixel(0, 0, 0xFFFF0000); // Top-left pixel red
    pane1.setPixel(0, 0, 0xFF0000FF); // Top-left pixel blue

    window.addPane(&pane1);

    int frameCount = 0;
    while(window.isOpen()){
        for(int y = 0; y < pane1.getHeight(); y++){
            for(int i = 0; i < 10; i++){
                uint32_t color = 0x00000000;
                uint8_t opacity = (i / 10.0) * 255;
                color |= (opacity << 24); // Set alpha channel
                color |= 0x00FF0000; // Set red channel
                pane1.setPixel((frameCount + i) % pane1.getWidth(), y, color);
            }
        }
        frameCount++;
        window.clear(0x00000000); // Clear to black

        if(pane1.getSetLocation()->x < 800){
            pane1.getSetLocation()->x += 1;
        }else{
            pane1.getSetLocation()->x = 50;
        }
        window.pollEvents();
        window.update();
    }
}