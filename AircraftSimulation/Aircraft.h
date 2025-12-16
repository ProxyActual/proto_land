#pragma once

#include "../GraphicsWindow/GraphicsWindow.h"
#include "Math/Vector.hpp"


class Aircraft{

    public:
        Aircraft(int x, int y, int width, int height);
        ~Aircraft();

        void updatePhysics(float deltaTime);
        void updateGraphics();
        void addGraphicsToWindow(GraphicsWindow* window);

        float getAirSpeed(); // in knots
        float getAltitude();
        float getPitch();
        float getRoll();

    private:
        gItem* aircraftGraphic;

        vector_3d currentAttitude;
        vector_3d localVelocity;
        vector_3d localAcceleration;
        vector_3d worldPosition; // Start at 1000 meters altitude
        vector_3d worldAcceleration;
};