#include "AircraftSimulation.h"
#include <SDL2/SDL.h>
#include <iostream>

AircraftSimulation::AircraftSimulation() {
    mainWindow = new GraphicsWindow("Aircraft Simulation", 800, 600);
    aircraft = new Aircraft();
    altimeter = new Altimeter(600, 400, 201, 201);
    attitudeIndicator = new AttitudeIndicator(50, 50, 201, 201);
    altimeter->addToWindow(mainWindow);
    attitudeIndicator->addToWindow(mainWindow);
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
    if(attitudeIndicator){
        delete attitudeIndicator;
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
        attitudeIndicator->setAttitude( aircraft->getAttitude().pitch, aircraft->getAttitude().roll);

        altimeter->updateDisplay();
        attitudeIndicator->updateDisplay();

        mainWindow->pollEvents();
        aircraft->updateGraphics();
        aircraft->updatePhysics(updateDelta);
        mainWindow->update();
        // Simulation logic would go here
    }
}