
#include "GraphicsWindow.h"
#include <stdexcept>
#include <iostream>


GraphicsWindow::GraphicsWindow(const std::string& title, int width, int height) {
    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );
    this->width = width;
    this->height = height;

    if (!window) {
        throw std::runtime_error(std::string("Failed to create window: ") + SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        throw std::runtime_error(std::string("Failed to create renderer: ") + SDL_GetError());
    }
}

GraphicsWindow::~GraphicsWindow() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

void GraphicsWindow::update() {
    SDL_RenderClear(renderer);
    SDL_Point center = {offsetX, offsetY};
    float scale = 1.0f;
    for(auto& item : items){
        item->render(renderer, center);
    }
    SDL_RenderSetScale(renderer, scale, scale);

    SDL_RenderPresent(renderer);
}

bool GraphicsWindow::isOpen() {
    return !shouldClose;
}

void GraphicsWindow::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            shouldClose = true;
        }
    }
}

void GraphicsWindow::addItem(gItem* item) {
    items.push_back(item);
}