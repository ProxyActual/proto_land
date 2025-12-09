#include "Core.h"
#include <iostream>

SpaceTraderCore::SpaceTraderCore(){
    mainWindow = new GraphicsWindow("Space Trader", 800, 600);
    gravitySink = new GravitySink({400.0f, 300.0f});
    gravitySink->addVelocity({-0.0f, 0.0f});
    gravitySink->setMass(500000.0f);
    gravitySink->addGraphicsToWindow(mainWindow);
    gravitySink2 = new GravitySink({600.0f, 300.0f});
    gravitySink2->addVelocity({0.0f, -40.0f});
    gravitySink2->setMass(5000.0f);
    gravitySink2->addGraphicsToWindow(mainWindow);
    player = new Player();
    player->setMass(5.0f);
    player->addGraphicToWindow(mainWindow);
    array[0] = gravitySink;
    array[1] = gravitySink2;
    array[2] = player;
}

SpaceTraderCore::~SpaceTraderCore(){
    if(mainWindow){
        delete mainWindow;
    }
    if(player){
        delete player;
    }
    if(gravitySink){
        delete gravitySink;
    }
}

void SpaceTraderCore::run(){
    while(mainWindow->isOpen()){
        long frameStartTime = SDL_GetTicks();
        mainWindow->pollEvents();
        mainWindow->update();
        PhysicsObject::Vector2 planet1 = gravitySink->getPosition();
        gravitySink->updateVelocity(frameStartTime, array, 3);
        gravitySink2->updateVelocity(frameStartTime, array, 3);
        
        player->updateVelocity(frameStartTime, array, 3);


        player->updatePosition(frameStartTime);
        gravitySink->updatePosition(frameStartTime);
        gravitySink2->updatePosition(frameStartTime);

        player->update();
        gravitySink2->updateGraphicsPosition();
        gravitySink->updateGraphicsPosition();


    }
}