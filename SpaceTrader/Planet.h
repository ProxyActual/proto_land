#pragma once

#include <SDL2/SDL.h>
#include "Player.h"
#include "Physics/Object.h"


class GravitySink : public PhysicsObject {
public:
    GravitySink(SDL_FPoint position);
    ~GravitySink();

    void addGraphicsToWindow(GraphicsWindow* window){
        window->addItem(sinkGraphic);
    }

    void updateGraphicsPosition();

    private:
        gItem* sinkGraphic;
        float gravityStrength = 0.05f;
        float influenceRadius = 100.0f;
};