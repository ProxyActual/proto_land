#pragma once

#include "../GraphicsWindow/GraphicsWindow.h"
#include "Physics/Object.h"

class Player : public PhysicsObject {
    public:
        Player();
        ~Player();
        void update();
        void addGraphicToWindow(GraphicsWindow* window);

        void updateTextureLocations();

        SDL_Point getPosition(){ return {static_cast<int>(position.x), static_cast<int>(position.y)}; }

    private:
        gItem* playerGraphic;
        gItem* engineFlames;

        float rotation = 0.0f;
        float speed = 0.1f;
        float maxSpeed = 0.0f;
        //Player attributes would go here
};