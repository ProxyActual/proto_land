#include "Pane.h"

Pane::Pane(int x, int y, int w, int h){
    location = new SDL_Rect{x, y, w, h};
}
Pane::~Pane(){
    if(location){
        delete location;
    }
}

bool Pane::render(SDL_Renderer* renderer){
    //If we are not visible, do not render
    if((!visable) || (renderer == nullptr))return false;

    SDL_SetRenderDrawColor(renderer, rand()%255, rand()%255, rand()%255, 255); // Set draw color to red
    SDL_RenderFillRect(renderer, getDisplayLocation()); // Render filled rectangle

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