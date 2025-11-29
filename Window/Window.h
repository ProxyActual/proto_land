#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string>

class Window {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    uint32_t* pixels;
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

    int getWidth();
    int getHeight();
    
private:
    bool shouldClose;
};

#endif // WINDOW_H