#include "Core.h"

SpaceTraderCore::SpaceTraderCore(){
    mainWindow = new GraphicsWindow("Space Trader", 800, 600);
    player = new Player();
    player->addGraphicToWindow(mainWindow);
}

SpaceTraderCore::~SpaceTraderCore(){
    if(mainWindow){
        delete mainWindow;
    }
    if(player){
        delete player;
    }
}

void SpaceTraderCore::run(){
    while(mainWindow->isOpen()){
        mainWindow->pollEvents();
        mainWindow->update();
        player->update();
    }
}