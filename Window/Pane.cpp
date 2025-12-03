#include "Pane.h"

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

    if(pixelBuffer != nullptr){
        SDL_Texture* texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STATIC,
            location->w,
            location->h
        );

        SDL_UpdateTexture(texture, nullptr, pixelBuffer, location->w * sizeof(uint32_t));
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_Rect* displayLoc = getDisplayLocation();
        SDL_RenderCopy(renderer, texture, nullptr, displayLoc);
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
        return displayLoc;
    }location; // Render filled rectangle

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
