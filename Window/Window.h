#ifndef WINDOW_H
#define WINDOW_H

#include "Pane.h"

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class Window {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    uint32_t* pixels;

    std::vector<Pane*> panes;

    int width;
    int height;

public:
    Window(const std::string& title, int w, int h);
    ~Window();
    
    void setPixel(int x, int y, uint32_t color);
    void clear(uint32_t color = 0x000000FF);
    void update();
    bool isOpen();
    void pollEvents();

    void setWindow(int x, int y, int w, int h, uint32_t* buffer);

    void addPane(Pane* pane);

    int getWidth();
    int getHeight();

    SDL_Renderer* getRenderer(){ return renderer; }
    
private:
    bool shouldClose;
};

#endif // WINDOW_H