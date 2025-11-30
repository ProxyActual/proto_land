#pragma once

#include <string>

class AiCore{
    public:
        AiCore(float x, float y);
        ~AiCore();

        void setTarget(float x, float y);


        void update();
        float getX();
        float getY();

        bool atTarget();

        void setSpeed(float s) { speed = s; }
        float getSpeed() { return speed; }

        float getTargetX() { return targetX; }
        float getTargetY() { return targetY; }

        std::string currentItem = "";

        int countdown = 0;

    private:
        float posX;
        float posY;

        float targetX;
        float targetY;

        float speed = 1.0f;
};