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
        uint32_t getPixel(int x, int y);
        bool setSize(SDL_Point size);
        bool render(SDL_Renderer* renderer, SDL_Point offset);

        SDL_Rect* getRect();
        float getRotation();
        SDL_Point getCenter();

        void fillPixels(uint32_t color);
        void move(int dx, int dy);

        bool visible = true;

    private:
        SDL_Point center;
        SDL_Rect* space;
        SDL_Texture* texture = nullptr;
        uint32_t* pixels = nullptr;
        float rotation;
};