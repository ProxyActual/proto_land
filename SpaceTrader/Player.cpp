#include "Player.h"
#include <iostream>
#include <cmath>

Player::Player(){
    position = {400, 300};
    velocity = {0, 0};
    playerGraphic = new gItem({400, 300}, {25, 50}, 0.0f);
    engineFlames = new gItem({400, 350}, {10, 20}, 0.0f);
    engineFlames->fillPixels(0xFFFFA500);
    playerGraphic->fillPixels(0xFFFF0000);
    //Initialize player attributes here
}

Player::~Player(){
    delete playerGraphic;
    delete engineFlames;
}

void Player::update(){
    Uint8 const* state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_W]){
        float rad = rotation * M_PI / 180.0f;
        velocity.x += sin(rad) * speed;
        velocity.y -= cos(rad) * speed;
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

    position.x += velocity.x;
    position.y += velocity.y;

    updateTextureLocations();
}

void Player::updateTextureLocations(){
    playerGraphic->setRotation(rotation);
    engineFlames->setRotation(rotation);
    playerGraphic->setCenter({static_cast<int>(position.x), static_cast<int>(position.y)});
    float rad = rotation * M_PI / 180.0f;
    SDL_Point engineFlamesPos = {
        static_cast<int>(position.x - sin(rad) * 35),
        static_cast<int>(position.y + cos(rad) * 35)
    };
    engineFlames->setCenter(engineFlamesPos);
}

void Player::addGraphicToWindow(GraphicsWindow* window){
    window->addItem(playerGraphic);
    window->addItem(engineFlames);
}