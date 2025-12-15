#include "Aircraft.h"
#include <iostream>

Aircraft::Aircraft(int x, int y, int width, int height) {
    aircraftGraphic = new gItem((SDL_Point{x + width / 2, y + height / 2}), (SDL_Point{width, height}), 0.0f);
    // Simple representation of an aircraft (a triangle)
    updateGraphics();
}

Aircraft::~Aircraft() {
    if (aircraftGraphic) {
        delete aircraftGraphic;
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

    //TODO: Fix this to use aircraft orientation properly
    float velocityInDirectionOfAircraft = currentVelocity.z * std::cos(currentAttitude.pitch * M_PI / 180.0f);
    float fullVelocity = std::sqrt(currentVelocity.x * currentVelocity.x + currentVelocity.y * currentVelocity.y + currentVelocity.z * currentVelocity.z);

    currentVelocity.z += currentAcceleration.z * deltaTime;
    currentAltitude += currentVelocity.z * deltaTime;




    // Placeholder for physics update logic
}

void Aircraft::updateGraphics() {
    for(int x = 0; x < aircraftGraphic->getRect()->w; x++){
        for(int y = 0; y < aircraftGraphic->getRect()->h; y++){
            aircraftGraphic->setPixel(x, y, 0x00000000); // Clear to transparent
        }
    }
    aircraftGraphic->drawCircle(aircraftGraphic->getRect()->w / 2, aircraftGraphic->getRect()->h / 2, 10, 0xFFFFFFFF); // White circle in center
    aircraftGraphic->drawLine(0, aircraftGraphic->getRect()->h / 2, aircraftGraphic->getRect()->w, aircraftGraphic->getRect()->h / 2, 0xFFFFFFFF); // Horizontal line
}


void Aircraft::addGraphicsToWindow(GraphicsWindow* window) {
    window->addItem(aircraftGraphic);
}

float Aircraft::getAirSpeed() {
    float forwardVelocity = abs(currentVelocity.z) * std::cos(currentAttitude.pitch * M_PI / 180.0f);
    return forwardVelocity * 1.94384f; // Convert m/s to knots
}