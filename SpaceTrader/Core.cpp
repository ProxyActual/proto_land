#include "Core.h"
#include "Planet.h"
#include <iostream>

SpaceTraderCore::SpaceTraderCore(){
    mainWindow = new GraphicsWindow("Space Trader", 800, 600);
    bg = new gItem({400, 300}, {800, 600}, 0.0f);
    bg->fillPixels(0x00000000);
    mainWindow->addItem(bg);
    GravitySink* centerPlanet = new GravitySink({400.0f, 300.0f});
    centerPlanet->setMass(500000.0f);
    centerPlanet->updateGraphics();
    centerPlanet->addGraphicsToWindow(mainWindow);
    array.push_back(centerPlanet);
    player = new Player();
    player->setMass(0.005f);

        float dx = player->getPosition().x - centerPlanet->getPosition().x;
        float dy = player->getPosition().y - centerPlanet->getPosition().y;
        float distance = std::sqrt(dx * dx + dy * dy);
        float orbitalSpeed = std::sqrt(centerPlanet->getMass() / distance);
        float vx = -orbitalSpeed * dy / distance;
        float vy = orbitalSpeed * dx / distance;
        player->addVelocity({vx, vy});
    player->addGraphicToWindow(mainWindow);
    array.push_back(player);
    for(int i = 0; i < 1000; i++){
        GravitySink* planet = new GravitySink(
            {(float)(rand() % 700) + 50, (float)(rand() % 500) + 50}
        );
        planet->setMass(10.0f + static_cast<float>(rand() % 501));
        planet->updateGraphics();

        float dx = planet->getPosition().x - centerPlanet->getPosition().x;
        float dy = planet->getPosition().y - centerPlanet->getPosition().y;
        float distance = std::sqrt(dx * dx + dy * dy);
        float orbitalSpeed = std::sqrt(centerPlanet->getMass() / distance);
        float vx = -orbitalSpeed * dy / distance;
        float vy = orbitalSpeed * dx / distance;
        planet->addVelocity({vx, vy});

        std::cout << "adding planet at position: (" << planet->getPosition().x << ", " << planet->getPosition().y << ") with mass: " << planet->getMass() << "\n";
        planet->addGraphicsToWindow(mainWindow);
        array.push_back(planet);
    }
}

SpaceTraderCore::~SpaceTraderCore(){
    if(mainWindow){
        delete mainWindow;
    }
    if(player){
        delete player;
    }
    for(auto& obj : array){
        if(obj){
            delete obj;
        }
    }
}

void SpaceTraderCore::run(){
    long lastFrameTime = SDL_GetTicks();
    while(mainWindow->isOpen()){
        long frameStartTime = SDL_GetTicks();
        mainWindow->pollEvents();
        mainWindow->update();        

        for(auto& obj : array){
            obj->updateVelocity(frameStartTime, array.data(), static_cast<int>(array.size()));
        }
        for(auto& obj : array){
            obj->updatePosition(frameStartTime);
            GravitySink* planet = dynamic_cast<GravitySink*>(obj);
            if(planet){
                planet->updateGraphicsPosition();
            bg->setPixel(
                static_cast<int>(obj->getPosition().x),
                static_cast<int>(obj->getPosition().y),
                0xFF00FF00
            );
            }
            else{
                bg->setPixel(
                    static_cast<int>(obj->getPosition().x),
                    static_cast<int>(obj->getPosition().y),
                    0xFFFFFF00
                );
            }

            if(obj->getPosition().x < 0 || obj->getPosition().x > 800 || 
                obj->getPosition().y < 0 || obj->getPosition().y > 600){
                 if(obj != player && dynamic_cast<GravitySink*>(obj) != array[0]){
                      array.erase(array.begin() + (&obj - &array[0]));
                 }
            }
        }

        for(int x = 0; x < 800; x++){
            for(int y = 0; y < 600; y++){
                uint32_t pixel = bg->getPixel(x, y);
                uint8_t alpha = (pixel >> 24) & 0xFF;
                if(alpha > 0){
                    alpha = alpha - (((frameStartTime - lastFrameTime) > 2000) ? 1: 0);
                    pixel = (pixel & 0x00FFFFFF) | (alpha << 24);
                    bg->setPixel(x, y, pixel);
                }
            }
        }


        player->update();
        //mainWindow->offsetX = static_cast<int>(player->getPosition().x) - 400;
        //mainWindow->offsetY = static_cast<int>(player->getPosition().y) - 300;
        //std::cout << "Player Position: (" << player->getPosition().x << ", " << player->getPosition().y << ")\n";
    }
}

