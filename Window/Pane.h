#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <string>


class Pane{
    public:
        bool visable = false;

        Pane(int x, int y, int w, int h);
        ~Pane();

        bool render(SDL_Renderer* renderer);

        bool addChildPane(Pane* pane);

        bool setParentPane(Pane* pane);

        SDL_Rect* getSetLocation();

        void setPixel(int x, int y, uint32_t color);

        int getWidth(){ return location->w; }
        int getHeight(){ return location->h; }
    private:
        uint32_t* pixelBuffer;
        SDL_Rect* location;
        SDL_Rect* getDisplayLocation();
        std::vector<Pane*> childPanes;
        Pane* parentPane = nullptr;
};