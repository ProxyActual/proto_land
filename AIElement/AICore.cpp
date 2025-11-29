#include "AICore.h"
#include <random>
#include <iostream>

AiCore::AiCore(float x, float y) : posX(x), posY(y) {
    setTarget(x, y);
}

AiCore::~AiCore() {
}

void AiCore::setTarget(float x, float y) {
    targetX = x;
    targetY = y;
}

void AiCore::update() {
    if(delay != 100){
        delay--;
        if(delay <= 0) {
            delay = 100;
            std::cout<< "New target set to (" << targetX << ", " << targetY << ")\n";
        }
    }
    else if(atTarget()) {
        delay--;
        
    }else{
        float dirX = targetX - posX;
        float dirY = targetY - posY;
        float length = std::sqrt(dirX * dirX + dirY * dirY);
        if (length > 0.0f) {
            dirX /= length;
            dirY /= length;

            posX += dirX * speed;
            posY += dirY * speed;
        }
    }
}

float AiCore::getX() {
    return posX;
}

float AiCore::getY() {
    return posY;
}

bool AiCore::atTarget() {
    return (std::abs(posX - targetX) < speed) && (std::abs(posY - targetY) < speed);
}
