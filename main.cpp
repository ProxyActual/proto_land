#include <iostream>
#include <thread>
#include <vector>
#include "AIElement/AICore.h"
#include "CommandLine/Input.h"
#include "CommandLine/CommandManager.h"
#include "World/WorldBase.h"
#include "Window/Window.h"

#define WIDTH 800
#define HEIGHT 600

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    WorldBase world(WIDTH, HEIGHT);
    world.init(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());

    Input in;
    CommandManager cmdManager;

    std::vector<AiCore*> aiCores;
    for (int i = 0; i < 30000; ++i) {
        AiCore* core = new AiCore(static_cast<float>(std::rand() % WIDTH), static_cast<float>(std::rand() % HEIGHT));
        core->setSpeed(.5f + (rand() % 300) / 100.0f);
        aiCores.push_back(core);
    
    }

    in.startInputThread();

    int value = 0;

    Window window("Input Test", 800, 600);

    while(window.isOpen()) {
        static auto lastTime = std::chrono::high_resolution_clock::now();
        static int frameCount = 0;
        auto currentTime = std::chrono::high_resolution_clock::now();
        frameCount++;
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastTime).count();
        if (elapsed >= 1) {
            frameCount = 0;
            lastTime = currentTime;
        }
        if (in.hasUpdate()) {
            std::string msg = in.getOldestString();

            cmdManager.executeCommand(msg);
        }

        window.clear();
        for(auto& ai : aiCores) {
            ai->update();
            uint32_t color = 0xFF0000FF;

            if(ai->currentItem == "Gold"){
                color = 0xFFD700FF; // Gold color
            }
            if(ai->currentItem == "Wood"){
                color = 0xFF00FFFF; // Magenta color    
            }
            if(ai->currentItem == "Tools"){
                color = 0xC0C0C0FF; // Silver color
            }
            if(ai->currentItem == "Food"){
                color = 0x006400FF; // Dark green color
            }

            window.setPixel(static_cast<int>(ai->getX()), static_cast<int>(ai->getY()), color);

            if(ai->atTarget()) {
                Location* currentLocation = world.getClosestLocation(ai->getX(), ai->getY());
                ai->setTarget(currentLocation->getX(), currentLocation->getY());
                if(currentLocation->withinRange(ai->getX(), ai->getY(), 10.0f) == false || ai->countdown > 10000){
                    ai->countdown = 0;
                    ai->currentItem = "";
                    Location* randomLocation = &world.getLocations()[rand() % world.getLocations().size()];
                    ai->setTarget(randomLocation->getX(), randomLocation->getY());
                    continue;
                }
                if(ai->currentItem != ""){
                    currentLocation->addResourceAmount(ai->currentItem, 1.0f,std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count());
                }
                ai->currentItem = currentLocation->getCheepestResource();
                if(currentLocation->hasResourceAmount(ai->currentItem, 1.0f) == false){
                    ai->currentItem = "";
                    ai->countdown++;
                    continue;
                }
                Location* targetLocation = world.getBestLocationForROI(currentLocation);
                if(targetLocation == nullptr){
                    ai->countdown++;
                    continue;
                }
                currentLocation->addResourceAmount(ai->currentItem, -1.0f,std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count());
                ai->setTarget(targetLocation->getX(), targetLocation->getY());
            }

        }
        world.update(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count());

        for(auto& loc : world.getLocations()){
            loc.draw(window.getRenderer());
        }

        std::cout << world.getStatus() << std::endl;
        value++;
        window.setPixel(value / window.getWidth(), value % window.getHeight(), 0xFF0000FF);

        window.pollEvents();
        window.update();
        // Sleep for a short duration to avoid busy waiting
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
}