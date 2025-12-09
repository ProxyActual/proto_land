#include "Core.h"
#include <iostream>

SpaceTraderCore::SpaceTraderCore(){
    mainWindow = new GraphicsWindow("Space Trader", 800, 600);
    gravitySink = new GravitySink({400.0f, 300.0f});
    gravitySink->addVelocity({-0.0f, 0.0f});
    gravitySink->setMass(500.0f);
    gravitySink->addGraphicsToWindow(mainWindow);
    gravitySink2 = new GravitySink({500.0f, 300.0f});
    gravitySink2->addVelocity({0.0f, -2.0f});
    gravitySink2->addGraphicsToWindow(mainWindow);
    player = new Player();
    player->setMass(5.0f);
    player->addGraphicToWindow(mainWindow);
    array[0] = gravitySink;
    array[1] = nullptr;
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
        gravitySink->updatePhysics(frameStartTime, array, 3);
        gravitySink2->updatePhysics(frameStartTime, array, 3);
        
        player->updatePhysics(frameStartTime, array, 3);
        player->update();

        gravitySink->updatePosition();
        gravitySink2->updatePosition();
    }
}