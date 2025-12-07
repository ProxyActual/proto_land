#include <iostream>
#include "GraphicsWindow/GraphicsWindow.h"

gItem* testItem;

void moveTestItem(SDL_Event* event){
    if(event->type == SDL_KEYDOWN){
        switch(event->key.keysym.sym){
            case SDLK_w:
                testItem->setCenter({testItem->getCenter().x, testItem->getCenter().y - 10});
                break;
            case SDLK_a:
                testItem->setCenter({testItem->getCenter().x - 10, testItem->getCenter().y});
                break;
            case SDLK_s:
                testItem->setCenter({testItem->getCenter().x, testItem->getCenter().y + 10});
                break;
            case SDLK_d:
                testItem->setCenter({testItem->getCenter().x + 10, testItem->getCenter().y});
                break;
        }
    }
}

class GameCore{
    private:
        gItem* testItem;
        
        static void processItemStatic(SDL_Event* event) {
            // This will be called by the event system
            // We need access to testItem, so we'll use the global pointer
            if(event->type == SDL_KEYDOWN && ::testItem != nullptr){
                switch(event->key.keysym.sym){
                    case SDLK_w:
                        ::testItem->setCenter({::testItem->getCenter().x, ::testItem->getCenter().y - 10});
                        break;
                    case SDLK_a:
                        ::testItem->setCenter({::testItem->getCenter().x - 10, ::testItem->getCenter().y});
                        break;
                    case SDLK_s:
                        ::testItem->setCenter({::testItem->getCenter().x, ::testItem->getCenter().y + 10});
                        break;
                    case SDLK_d:
                        ::testItem->setCenter({::testItem->getCenter().x + 10, ::testItem->getCenter().y});
                        break;
                }
            }
        }
        
    public:
        void run(){
            GraphicsWindow graphicsWindow("Space Trader", 800, 600);
            testItem = new gItem({200, 200}, {100, 100}, 0.0f);
            ::testItem = testItem; // Set global pointer
            
            // Link the event handler
            testItem->processEvent = processItemStatic;
            
            graphicsWindow.addItem(testItem);
            
            for(int x = 0; x < 100; x++){
                for(int y = 0; y < 100; y++){
                    testItem->setPixel(x, y, 0xff00ffff);
                }
            }

            while(graphicsWindow.isOpen()) {
                graphicsWindow.pollEvents();
                graphicsWindow.update();
                // Game loop logic goes here
            }
        }
};

int main() {
    std::cout << "Space Trader Game Initialized!" << std::endl;

    GameCore gc;
    gc.run();

    return 0;
}