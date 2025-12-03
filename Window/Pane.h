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

        void setRotation(float angle);

        void setBaseImagePath(const std::string& path){ baseImagePath = path; }
    private:
        uint32_t* pixelBuffer;
        std::string baseImagePath;
        SDL_Rect* location;
        std::vector<Pane*> childPanes;
        Pane* parentPane = nullptr;
        float rotation = 0.0f;

        float getDisplayRotation();
        SDL_Rect* getDisplayLocation();
};