#include "Pane.h"
#include <iostream>

Pane::Pane(int x, int y, int w, int h){
    location = new SDL_Rect{x, y, w, h};
    pixelBuffer = nullptr;
}
Pane::~Pane(){
    if(location){
        delete location;
    }
}

bool Pane::render(SDL_Renderer* renderer){
    //If we are not visible, do not render
    if((!visable) || (renderer == nullptr))return false;

    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STATIC,
        location->w,
        location->h
    );
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);


    // Load BMP file into texture if available
    if(!baseImagePath.empty()){
        SDL_Surface* bmpSurface = SDL_LoadBMP(baseImagePath.c_str());
        if(bmpSurface != nullptr){
            SDL_Texture* bmpTexture = SDL_CreateTextureFromSurface(renderer, bmpSurface);
            SDL_FreeSurface(bmpSurface);
            if(bmpTexture != nullptr){
                SDL_RenderCopyEx(renderer, bmpTexture, nullptr, getDisplayLocation(), getDisplayRotation(), nullptr, SDL_FLIP_NONE);
                SDL_DestroyTexture(bmpTexture);
            }
        }
    }

    if(pixelBuffer != nullptr){
        SDL_UpdateTexture(texture, nullptr, pixelBuffer, location->w * sizeof(uint32_t));
        SDL_RenderCopyEx(renderer, texture, nullptr, getDisplayLocation(), getDisplayRotation(), nullptr, SDL_FLIP_NONE);
        SDL_DestroyTexture(texture);
    }

    for(auto& child : childPanes){
        child->render(renderer);
    }

    return true;
}

bool Pane::addChildPane(Pane* pane){
    if(pane != nullptr //Insure its valid and fits within the parent
            && pane->location->x+pane->location->w <= location->w 
            && pane->location->y+pane->location->h <= location->h
    ){
        pane->setParentPane(this);
        childPanes.push_back(pane);
        return true;
    }
    return false;
}

bool Pane::setParentPane(Pane* pane){
    if(pane != nullptr //Insure its valid and fits within the parent
        && location->x+location->w <= pane->location->w 
        && location->y+location->h <= pane->location->h
    ){
        parentPane = pane;
        return true;
    }
    return false;
}

SDL_Rect* Pane::getSetLocation(){
    return location;
}

SDL_Rect* Pane::getDisplayLocation(){
    if(parentPane == nullptr){
        return location;
    }else{
        SDL_Rect* parentLoc = parentPane->getDisplayLocation();
        
        SDL_Rect* displayLoc = new SDL_Rect{
            location->x + parentLoc->x,
            location->y + parentLoc->y,
            location->w,
            location->h
        };
        if(parentPane->getDisplayRotation() != 0.0f){
            SDL_Point parentCenter = {
                parentLoc->x + parentLoc->w / 2,
                parentLoc->y + parentLoc->h / 2
            };
            SDL_Point locCenter = {
                displayLoc->x + displayLoc->w / 2,
                displayLoc->y + displayLoc->h / 2
            };
            SDL_Point rotatedCenter;
            float angleRad = parentPane->getDisplayRotation() * (3.14159265f / 180.0f);
            rotatedCenter.x = static_cast<int>(
                cos(angleRad) * (locCenter.x - parentCenter.x) -
                sin(angleRad) * (locCenter.y - parentCenter.y) +
                parentCenter.x
            );
            rotatedCenter.y = static_cast<int>(
                sin(angleRad) * (locCenter.x - parentCenter.x) +
                cos(angleRad) * (locCenter.y - parentCenter.y) +
                parentCenter.y
            );
            displayLoc->x = rotatedCenter.x - displayLoc->w / 2;
            displayLoc->y = rotatedCenter.y - displayLoc->h / 2;
        }
        return displayLoc;
    }
}

float Pane::getDisplayRotation(){
    if(parentPane == nullptr){
        return rotation;
    }else{
        return rotation + parentPane->getDisplayRotation();
    }
}

void Pane::setPixel(int x, int y, uint32_t color){
    if(pixelBuffer == nullptr){
        pixelBuffer = new uint32_t[location->w * location->h];
        //Initialize to transparent
        for(int i = 0; i < location->w * location->h; i++){
            pixelBuffer[i] = 0x00000000;
        }
    }
    if(x >= 0 && x < location->w && y >= 0 && y < location->h){
        pixelBuffer[x + y * location->w] = color;
    }
}

void Pane::setRotation(float angle){
    rotation = angle;
}
