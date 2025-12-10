#include "Player.h"
#include <iostream>
#include <cmath>

Player::Player(){
    position = {200, 300};
    playerGraphic = new gItem({400, 300}, {10, 30}, 0.0f);
    engineFlames = new gItem({400, 350}, {5, 10}, 0.0f);
    engineFlames->fillPixels(0xFFFFA500);
    playerGraphic->fillPixels(0xFFFF0000);
    //Initialize player attributes here
}

Player::~Player(){
    delete playerGraphic;
    delete engineFlames;
}

void Player::update(){
    //std::cout << "Current Velocity Sum: (" << sqrt(getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y) << ") " << maxSpeed   << "\n";
    
    if(sqrt(getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y) > maxSpeed){
        maxSpeed = sqrt(getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y);
    }

    Uint8 const* state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_W]){
        float rad = rotation * M_PI / 180.0f;
        std::cout << "Applying thrust at angle: " << rotation << " degrees (" << rad << " radians)\n";
        addVelocity({sin(rad) * speed, -cos(rad) * speed});
        engineFlames->visible = true;        
    }
    else {
        engineFlames->visible = false;
    }
    if(state[SDL_SCANCODE_S]){
        //Fill this later
    }
    if(state[SDL_SCANCODE_A]){
        rotation = fmod(rotation - 5.0f, 360.0f);
    }
    if(state[SDL_SCANCODE_D]){
        rotation = fmod(rotation + 5.0f, 360.0f);
    }
    if(state[SDL_SCANCODE_SPACE]){
        position = {100, 100};
        addVelocity({-getVelocity().x, -getVelocity().y});
        rotation = 0.0f;
    }
    updateTextureLocations();
}

void Player::updateTextureLocations(){
    playerGraphic->setRotation(rotation);
    engineFlames->setRotation(rotation);
    playerGraphic->setCenter({static_cast<int>(position.x), static_cast<int>(position.y)});
    float rad = rotation * M_PI / 180.0f;
    SDL_Point engineFlamesPos = {
        static_cast<int>(position.x - sin(rad) * 20),
        static_cast<int>(position.y + cos(rad) * 20)
    };
    engineFlames->setCenter(engineFlamesPos);
}

void Player::addGraphicToWindow(GraphicsWindow* window){
    window->addItem(playerGraphic);
    window->addItem(engineFlames);
}