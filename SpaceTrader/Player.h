#pragma once

#include "../GraphicsWindow/GraphicsWindow.h"

class Player{
    public:
        Player();
        ~Player();
        void update();
        void addGraphicToWindow(GraphicsWindow* window);

        void updateTextureLocations();

    private:
        gItem* playerGraphic;
        gItem* engineFlames;

        float rotation = 0.0f;
        float speed = 0.01f;

        SDL_FPoint velocity;
        SDL_FPoint position;
        //Player attributes would go here
};