#pragma once

#include "../GraphicsWindow/GraphicsWindow.h"
#include "Player.h"
#include "Planet.h"
#include <vector>

class SpaceTraderCore{
    public:
        SpaceTraderCore();
        ~SpaceTraderCore();

        void run();
    private:
        std::vector<PhysicsObject*> array;
        GraphicsWindow* mainWindow;
        Player* player;
        gItem* bg;
};