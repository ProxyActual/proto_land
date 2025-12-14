#include "Aircraft.h"
#include <iostream>

Aircraft::Aircraft() {
    aircraftGraphic = new gItem({400, 300}, {50, 50}, 0.0f);
    attitudeIndecator = new gItem({100, 100}, {201, 201}, 0.0f);
    whiteBar = new gItem({100, 100}, {201, 201}, 0.0f);
    // Simple representation of an aircraft (a triangle)
    updateGraphics();
}

Aircraft::~Aircraft() {
    if (aircraftGraphic) {
        delete aircraftGraphic;
    }
    if (attitudeIndecator) {
        delete attitudeIndecator;
    }
    if (whiteBar) {
        delete whiteBar;
    }
}

void Aircraft::updatePhysics(float deltaTime) {

    const Uint8* keyState = SDL_GetKeyboardState(NULL);

        if(currentAttitude.pitch > 180.0f || currentAttitude.pitch < 0.0f){
            pitchUpDirection *= -1.0f;
            currentAttitude.roll -=180.0f;
        }
        if (keyState[SDL_SCANCODE_W]) {
            currentAttitude.pitch -= 50.0f * deltaTime * pitchUpDirection; // Increase pitch
        }
        if (keyState[SDL_SCANCODE_A]) {
            currentAttitude.roll += 50.0f * deltaTime; // Increase roll
        }
        if (keyState[SDL_SCANCODE_S]) {
            currentAttitude.pitch += 50.0f * deltaTime * pitchUpDirection; // Decrease pitch
        }
        if (keyState[SDL_SCANCODE_D]) {
            currentAttitude.roll -= 50.0f * deltaTime; // Decrease roll
        }

        currentAttitude.roll = std::fmod(currentAttitude.roll + 360.0f, 360.0f);

    currentVelocity.z += currentAcceleration.z * deltaTime;
    currentAltitude += currentVelocity.z * deltaTime;

    // Placeholder for physics update logic
}

void Aircraft::updateGraphics() {
    for (int y = 0; y < 50; ++y) {
        for (int x = 0; x < 50; ++x) {
            if (x > 25 - y / 2 && x < 25 + y / 2 && y < 25) {
                aircraftGraphic->setPixel(x,y,0xff0000ff); // Red color
            } else {
                aircraftGraphic->setPixel(x,y,0x00000000); // Transparent
            }
        }
    }

}

void Aircraft::updateAttitudeIndicator() {
    std::cout << "Current Attitude - Pitch: " << currentAttitude.pitch << " Roll: " << currentAttitude.roll << std::endl;
    // Clear the indicator
    attitudeIndecator->fillPixels(0x00000000); // Transparent
    
    int width = attitudeIndecator->getRect()->w;
    int height = attitudeIndecator->getRect()->h;

    for(int x = 0; x < width; ++x){
        for (int y = 0; y < height; ++y)
        {
            if(y == height / 2){
                whiteBar->setPixel(x, y, 0xffffffff); // White horizon line
            }

            if((x-width/2) * (x-width/2) + (y-height/2) * (y-height/2) >= (width/2) * (width/2)){
                continue; // Outside circle
            }
            else if(y <= (height/2) + (currentAttitude.pitch - 90) * (height / 180.0f) )
            {
                attitudeIndecator->setPixel(x, y, 0xff0000ff); // Blue sky
            }
            else{
                attitudeIndecator->setPixel(x, y, 0xff964B00); // Brown ground
            }

        }
    }
    attitudeIndecator->setRotation(-currentAttitude.roll);
}

void Aircraft::addGraphicsToWindow(GraphicsWindow* window) {
    window->addItem(aircraftGraphic);
    window->addItem(attitudeIndecator);
    window->addItem(whiteBar);
}