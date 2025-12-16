#include "Aircraft.h"
#include <iostream>

Aircraft::Aircraft(int x, int y, int width, int height) {
    worldPosition = {0.0f, 0.0f, 1000.0f};
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
    vector_3d worldAcceleration = {0.0f, 0.0f, -9.81f}; // Gravity in local frame]
    localAcceleration = worldAcceleration.convertToWorld(currentAttitude);

    float direction = 1.0f;
    if(getRoll() > 90.0f && getRoll() < 270.0f){
        direction = -1.0f;
    }
    // Handle pitch input from keyboard
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_W]) {
        currentAttitude.y +=50.0f * deltaTime * direction; // Pitch up
    }
    if (keystate[SDL_SCANCODE_S]) {
        currentAttitude.y -=50.0f * deltaTime * direction; // Pitch down
    }
    if (keystate[SDL_SCANCODE_A]) {
        currentAttitude.x += 50.0f * deltaTime; // Roll left
    }
    if (keystate[SDL_SCANCODE_D]) {
        currentAttitude.x -= 50.0f * deltaTime; // Roll right
    }


    if(currentAttitude.y + 90.0f > 180.0f){
        currentAttitude.x += 180.0f;
    }
    currentAttitude.y = std::fmod(currentAttitude.y + 180.0f, 180.0f);
    currentAttitude.x = std::fmod(currentAttitude.x + 360.0f, 360.0f);



    std::cout << "Pitch: " <<  getPitch() << " Roll: " << getRoll() << "Yaw: " << currentAttitude.z << std::endl;
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
    return localVelocity.x * 1.94384f; // Convert m/s to knots
}

float Aircraft::getAltitude() {
    return worldPosition.z;
}

float Aircraft::getPitch() {
    return currentAttitude.y;
}

float Aircraft::getRoll() {
    return currentAttitude.x;
}