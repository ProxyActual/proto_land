#pragma once

#include "../GraphicsWindow/GraphicsWindow.h"
#include "Player.h"
#include "Planet.h"

class SpaceTraderCore{
    public:
        SpaceTraderCore();
        ~SpaceTraderCore();

        void run();
    private:
        PhysicsObject* array[3];
        GravitySink* gravitySink;
        GravitySink* gravitySink2;
        GraphicsWindow* mainWindow;
        Player* player;
};