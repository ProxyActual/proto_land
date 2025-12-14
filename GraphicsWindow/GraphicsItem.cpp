#include "GraphicsItem.h"
#include <iostream>

gItem::gItem(SDL_Point center, SDL_Point size, float rotation)
    : center(center), rotation(rotation) {
    space = new SDL_Rect{center.x - size.x / 2, center.y - size.y / 2, size.x, size.y};
}

gItem::~gItem() {
    delete space;
}

bool gItem::render(SDL_Renderer* renderer   , SDL_Point offset) {
    bool onScreen = !(space->x + space->w < offset.x || space->x > offset.x + 800 ||
                      space->y + space->h < offset.y || space->y > offset.y + 600);
    if(!visible || !onScreen) return false;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Red color for the rectangle
    
    if (pixels != nullptr) {
        if(texture == nullptr){
            texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, space->w, space->h);
            SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        }
        SDL_UpdateTexture(texture, nullptr, pixels, space->w * sizeof(uint32_t));
    }
    SDL_Rect renderRect = {space->x - offset.x, space->y - offset.y, space->w, space->h};
    SDL_RenderCopyEx(renderer, texture, nullptr, &renderRect, rotation, nullptr, SDL_FLIP_NONE);
    //SDL_DestroyTexture(texture);

    return true;
}

SDL_Point gItem::getCenter(){
    return center;
}

bool gItem::setImage(std::string imagePath) {
    SDL_Surface* surface = SDL_LoadBMP(imagePath.c_str());
    if (!surface) {
        return false;
    }
    texture = SDL_CreateTextureFromSurface(SDL_GetRenderer(SDL_GetWindowFromID(1)), surface);
    SDL_FreeSurface(surface);
    return texture != nullptr;
}

bool gItem::setRotation(float rotation) {
    this->rotation = rotation;
    return true;
}


bool gItem::setCenter(SDL_Point center) {
    this->center = center;
    space->x = center.x - space->w / 2;
    space->y = center.y - space->h / 2;
    return true;
}

bool gItem::setPixel(int x, int y, uint32_t color) {
    if(pixels == nullptr){
        pixels = new uint32_t[space->w * space->h];
    }
    if (x >= 0 && x < space->w && y >= 0 && y < space->h) {
        pixels[y * space->w + x] = color;
        return true;
    }
    return false;
}

uint32_t gItem::getPixel(int x, int y) {
    if(pixels == nullptr){
        return 0;
    }
    if (x >= 0 && x < space->w && y >= 0 && y < space->h) {
        return pixels[y * space->w + x];
    }
    return 0;
}

bool gItem::setSize(SDL_Point size) {
    if(pixels != nullptr) {
        delete[] pixels;
        pixels = nullptr;
    }
    space->w = size.x;
    space->h = size.y;
    space->x = center.x - size.x / 2;
    space->y = center.y - size.y / 2;
    return true;
}

void gItem::fillPixels(uint32_t color){
    for(int x = 0; x < space->w; x++){
        for(int y = 0; y < space->h; y++){
            setPixel(x, y, color);
        }
    }
}

void gItem::move(int dx, int dy) {
    center.x += dx;
    center.y += dy;
    space->x += dx;
    space->y += dy;
}

SDL_Rect* gItem::getRect(){
    return space;
}
float gItem::getRotation(){
    return rotation;
}