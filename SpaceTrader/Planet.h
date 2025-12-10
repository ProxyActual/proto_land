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

    void updateGraphics();
    gItem* getGraphic(){ return sinkGraphic; }


    private:
        gItem* sinkGraphic;
        float gravityStrength = 0.05f;
        float influenceRadius = 10.0f;
};