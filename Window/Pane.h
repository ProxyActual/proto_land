#pragma once

#include <SDL2/SDL.h>
#include <vector>


class Pane{
    public:
        bool visable = false;

        Pane(int x, int y, int w, int h);
        ~Pane();

        bool render(SDL_Renderer* renderer);

        bool addChildPane(Pane* pane);

        bool setParentPane(Pane* pane);

        SDL_Rect* getSetLocation();
    private:
        SDL_Rect* location;
        SDL_Rect* getDisplayLocation();
        std::vector<Pane*> childPanes;
        Pane* parentPane = nullptr;
};