#pragma once

#include <SDL2/SDL.h>
#include <string>

class gItem{
    public:
        gItem(SDL_Point center, SDL_Point size, float rotation);
        ~gItem();
        bool setImage(std::string imagePath);
        bool setRotation(float rotation);
        bool setCenter(SDL_Point center);
        bool setPixel(int x, int y, uint32_t color);
        bool setSize(SDL_Point size);
        bool render(SDL_Renderer* renderer);

        SDL_Point getCenter();

        void (*processEvent)(SDL_Event* event) = nullptr;

    private:
        SDL_Point center;
        SDL_Rect* space;
        SDL_Texture* texture = nullptr;
        uint32_t* pixels = nullptr;
        float rotation;
};