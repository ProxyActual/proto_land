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



    window.addPane(&pane1);

    while(window.isOpen()){
        if(pane1.getSetLocation()->x < 600){
            pane1.getSetLocation()->x += 1;
        }else{
            pane1.getSetLocation()->x = 50;
        }
        window.pollEvents();
        window.update();
    }
}