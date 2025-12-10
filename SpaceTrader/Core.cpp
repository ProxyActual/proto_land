#include "Core.h"
#include "Planet.h"
#include <iostream>

SpaceTraderCore::SpaceTraderCore(){
    mainWindow = new GraphicsWindow("Space Trader", 800, 600);
    bg = new gItem({400, 300}, {800, 600}, 0.0f);
    bg->fillPixels(0x00000000);
    mainWindow->addItem(bg);
    GravitySink* centerPlanet = new GravitySink({400.0f, 300.0f});
    centerPlanet->setMass(5000e4f);
    centerPlanet->updateGraphics();
    centerPlanet->addGraphicsToWindow(mainWindow);
    array.push_back(centerPlanet);
    /*player = new Player();
    player->setMass(10000.0f);

        float dx = player->getPosition().x - centerPlanet->getPosition().x;
        float dy = player->getPosition().y - centerPlanet->getPosition().y;
        float distance = std::sqrt(dx * dx + dy * dy);
        float orbitalSpeed = std::sqrt(centerPlanet->getMass() / distance);
        float vx = -orbitalSpeed * dy / distance;
        float vy = orbitalSpeed * dx / distance;
        player->addVelocity({vx, vy});
    player->addGraphicToWindow(mainWindow);
    array.push_back(player);*/
    for(int i = 0; i < 1500; i++){
        float angle = static_cast<float>(rand() % 360);
        float dist = static_cast<float>(rand() % 200) + 100.0f;
        GravitySink* planet = new GravitySink(
            {
                static_cast<float>(centerPlanet->getPosition().x + dist * (float)sin(angle * M_PI / 180.0f)),
                static_cast<float>(centerPlanet->getPosition().y + dist * (float)cos(angle * M_PI / 180.0f))
            }
        );
        planet->setMass(10.0f + static_cast<float>(rand() % 51));
        planet->updateGraphics();

        float dx = planet->getPosition().x - centerPlanet->getPosition().x;
        float dy = planet->getPosition().y - centerPlanet->getPosition().y;
        float distance = std::sqrt(dx * dx + dy * dy);
        float orbitalSpeed = std::sqrt(centerPlanet->getMass() / distance);
        orbitalSpeed *= (0.95f + static_cast<float>(rand() % 11) / 100.0f); //Add some variation
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
            if(!obj->remove){
                obj->updateVelocity(frameStartTime, array.data(), static_cast<int>(array.size()));
            }
        }
        for(auto& obj : array){
            obj->updatePosition(frameStartTime);
            GravitySink* planet = dynamic_cast<GravitySink*>(obj);

            if(planet){
                    planet->updateGraphicsPosition();
                    if(planet->getMass() > 500.0f)
                    {
                        bg->setPixel(
                        static_cast<int>(obj->getPosition().x),
                        static_cast<int>(obj->getPosition().y),
                        0xFF00FF00);
                    }
                    if(planet->getPosition().x < 0 || planet->getPosition().x > 800 || 
                        planet->getPosition().y < 0 || planet->getPosition().y > 600 ||
                        planet->remove
                    ){
                        array.erase(array.begin() + (&obj - &array[0]));
                        mainWindow->removeItem(planet->getGraphic());
                        //delete obj;
                        std::cout << "Shrinking array to size: " << array.size() << "\n";
                    }
                
            }
            else{
                bg->setPixel(
                    static_cast<int>(obj->getPosition().x),
                    static_cast<int>(obj->getPosition().y),
                    0xFf0000ff
                );
            }
        }

        if(frameStartTime - lastFrameTime > 5000){
            lastFrameTime = frameStartTime;
            for(int x = 0; x < 800; x++){
                for(int y = 0; y < 600; y++){
                    uint32_t pixel = bg->getPixel(x, y);
                    uint8_t alpha = (pixel >> 24) & 0xFF;
                    if(alpha > 0){
                        alpha = alpha - 1;
                        pixel = (pixel & 0x00FFFFFF) | (alpha << 24);
                        bg->setPixel(x, y, pixel);
                    }
                }
            }
        }


        //player->update();
        //mainWindow->offsetX = static_cast<int>(player->getPosition().x) - 400;
        //mainWindow->offsetY = static_cast<int>(player->getPosition().y) - 300;
        //std::cout << "Player Position: (" << player->getPosition().x << ", " << player->getPosition().y << ")\n";
    }
}

