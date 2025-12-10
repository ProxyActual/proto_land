#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "GraphicsItem.h"

class GraphicsWindow {
public:
    GraphicsWindow(const std::string& title, int width, int height);
    ~GraphicsWindow();
    bool isOpen();
    void update();
    void pollEvents();
    void addItem(gItem* item);
    void removeItem(gItem* item);

    int offsetX = 0;
    int offsetY = 0;
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<gItem*> items;
    bool shouldClose = false;
    int width;
    int height;
};