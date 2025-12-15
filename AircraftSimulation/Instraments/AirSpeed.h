#pragma once

#include "../../GraphicsWindow/GraphicsWindow.h"

class AirSpeedIndicator {
    public:
        AirSpeedIndicator(int x, int y, int width, int height, float maxSpeed);
        ~AirSpeedIndicator();

        void setAirSpeed(float speed); // in knots

        void updateGraphics();

        void addToWindow(GraphicsWindow* window);

    private:
        gItem* indicatorGraphic;
        gItem* needleGraphic;

        float maxAirSpeed = 200.0f; // in knots
        float currentAirSpeed = 0.0f; // in knots
};