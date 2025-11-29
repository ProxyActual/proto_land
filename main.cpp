#include <iostream>
#include <thread>
#include <vector>
#include "AIElement/AICore.h"
#include "CommandLine/Input.h"
#include "Window/Window.h"

int main() {
    Input in;

    std::vector<AiCore*> aiCores;
    for (int i = 0; i < 1000; ++i) {
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
            std::cout << "FPS: " << frameCount / elapsed << std::endl;
            frameCount = 0;
            lastTime = currentTime;
        }
        if (in.hasUpdate()) {
            std::string msg = in.getOldestString();
            std::cout << "Received input: " << msg << std::endl;

            value = std::stoi(msg);

        }

        window.clear();
        for(auto& ai : aiCores) {
            if(ai->atTarget()) {
                float targetX = static_cast<float>(rand() % window.getWidth());
                float targetY = static_cast<float>(rand() % window.getHeight());
                float speed = 0.1f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (4.0f - 0.1f)));
                ai->setSpeed(speed);
                ai->setTarget(targetX, targetY);
            }
            ai->update();
            float speed = ai->getSpeed();
            float normalizedSpeed = (speed - 0.1f) / (4.0f - 0.1f); // Normalize speed to 0-1 range
            normalizedSpeed = std::min(1.0f, std::max(0.0f, normalizedSpeed)); // Clamp to 0-1
            uint8_t red = static_cast<uint8_t>(normalizedSpeed * 255);
            uint32_t color = (red << 24) | 0x000000FF; // Red channel + full alpha
            window.setPixel(static_cast<int>(ai->getX()), static_cast<int>(ai->getY()), color);
            window.setPixel(static_cast<int>(ai->getTargetX()), static_cast<int>(ai->getTargetY()), 0x00FF00FF);
        }
        value++;
        window.setPixel(value / window.getWidth(), value % window.getHeight(), 0xFF0000FF);

        window.pollEvents();
        window.update();
        // Sleep for a short duration to avoid busy waiting
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
}