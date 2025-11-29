#include <iostream>
#include <thread>
#include <vector>
#include "AIElement/AICore.h"
#include "CommandLine/Input.h"
#include "CommandLine/CommandManager.h"
#include "World/POI.h"
#include "Window/Window.h"

int main() {
    std::vector<POI> pois;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < 10; ++i) {
        float x = static_cast<float>(rand() % 800);
        float y = static_cast<float>(rand() % 600);
        pois.emplace_back(x, y);
    }
    Input in;
    CommandManager cmdManager;

    std::vector<AiCore*> aiCores;
    for (int i = 0; i < 2; ++i) {
        aiCores.push_back(new AiCore(800 / 2.0f, 600 / 2.0f));
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
            if(ai->atTarget()) {
                int randPOI = rand() % pois.size();
                ai->setTarget(pois[randPOI].x, pois[randPOI].y);
            }
            ai->update();   
            uint8_t red = static_cast<uint8_t>(255);
            uint32_t color = (red << 24) | 0x000000FF; // Red channel + full alpha
            window.setPixel(static_cast<int>(ai->getX()), static_cast<int>(ai->getY()), color);
        }
        for(const auto& poi : pois) {
            window.setPixel(static_cast<int>(poi.x), static_cast<int>(poi.y), 0x00FF00FF);
        }
        value++;
        window.setPixel(value / window.getWidth(), value % window.getHeight(), 0xFF0000FF);

        window.pollEvents();
        window.update();
        // Sleep for a short duration to avoid busy waiting
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
}