#pragma once

#include "../GraphicsWindow/GraphicsWindow.h"

class Aircraft{
    struct attitude{
        float pitch;
        float roll;
        float yaw;
    };

    struct vector3{
        float x;
        float y;
        float z;
    };

    public:
        Aircraft(int x, int y, int width, int height);
        ~Aircraft();

        void updatePhysics(float deltaTime);
        void updateGraphics();
        void addGraphicsToWindow(GraphicsWindow* window);
        attitude getAttitude() const { return currentAttitude; }
        float getCurrentAltitude() const { return currentAltitude; }


    private:
        gItem* aircraftGraphic;

        attitude currentAttitude{90.0f, 0.0f, 0.0f};
        vector3 currentVelocity{0.0f, 0.0f, 0.0f};
        vector3 currentAcceleration{0.0f, 0.0f, -9.8f};

        float currentAltitude = 10000.0f;

        float rudderAngle = 0.0f;
        float elevatorAngle = 0.0f;
        float aileronAngle = 0.0f;


        float pitchUpDirection = 1.0f;
};