#include "AircraftSimulation.h"
#include <SDL2/SDL.h>
#include <iostream>

AircraftSimulation::AircraftSimulation() {
    mainWindow = new GraphicsWindow("Aircraft Simulation", 800, 600);
    aircraft = new Aircraft();
    altimeter = new Altimeter(600, 400, 200, 200);
    altimeter->addToWindow(mainWindow);
    aircraft->addGraphicsToWindow(mainWindow);
}

AircraftSimulation::~AircraftSimulation() {
    if( aircraft) {
        delete aircraft;
    }
    if (mainWindow) {
        delete mainWindow;
    }
    if (altimeter) {
        delete altimeter;
    }
}

void AircraftSimulation::run() {
    altimeter->updateDisplay();
    long lastTime = SDL_GetTicks();
    while (mainWindow->isOpen()) {
        long currentTime = SDL_GetTicks();
        float updateDelta = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        
        altimeter->setAltitude( aircraft->getCurrentAltitude());

        mainWindow->pollEvents();
        aircraft->updateGraphics();
        aircraft->updatePhysics(updateDelta);
        mainWindow->update();
        // Simulation logic would go here
    }
}