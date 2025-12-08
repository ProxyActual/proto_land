#pragma once

#include "../GraphicsWindow/GraphicsWindow.h"
#include "Player.h"

class SpaceTraderCore{
    public:
        SpaceTraderCore();
        ~SpaceTraderCore();

        void run();
    private:
        GraphicsWindow* mainWindow;
        Player* player;
};