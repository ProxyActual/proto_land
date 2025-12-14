#pragma once

#include "../../GraphicsWindow/GraphicsWindow.h"

class Altimeter{
    public:
        Altimeter(int x, int y, int width, int height);
        ~Altimeter();

        void addToWindow(GraphicsWindow* window);

        void setAltitude(float altitude);

        void updateDisplay();

    private:
        float currentAltitude = 0.0f;

        gItem* AltimeterFace;
        gItem* AltimeterNeedle100;
        gItem* AltimeterNeedle1k;
        gItem* AltimeterNeedle10k;
};