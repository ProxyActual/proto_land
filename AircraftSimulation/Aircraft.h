#pragma once

#include "../GraphicsWindow/GraphicsWindow.h"

class Aircraft{
    struct attitude{
        float pitch;
        float roll;
        float yaw;
    };

    public:
        Aircraft();
        ~Aircraft();

        void updatePhysics(float deltaTime);
        void updateGraphics();
        void addGraphicsToWindow(GraphicsWindow* window);
    private:
        gItem* aircraftGraphic;

        gItem* attitudeIndecator;
        gItem* whiteBar;

        attitude currentAttitude{90.0f, 0.0f, 0.0f};
        void updateAttitudeIndicator();

        float rudderAngle = 0.0f;
        float elevatorAngle = 0.0f;
        float aileronAngle = 0.0f;


        float pitchUpDirection = 1.0f;
};