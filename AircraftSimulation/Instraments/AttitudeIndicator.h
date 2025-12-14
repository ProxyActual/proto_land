#pragma once
#include "../../GraphicsWindow/GraphicsWindow.h"

class AttitudeIndicator{
    public:
        AttitudeIndicator(int x, int y, int width, int height);
        ~AttitudeIndicator();

        void addToWindow(GraphicsWindow* window);

        void setAttitude(float pitch, float roll);

        void updateDisplay();

    private:
        float currentPitch = 0.0f;
        float currentRoll = 0.0f;

        gItem* BlueOverBrown;
};