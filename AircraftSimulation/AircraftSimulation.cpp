#include "AircraftSimulation.h"
#include <SDL2/SDL.h>
#include <iostream>

AircraftSimulation::AircraftSimulation() {
    mainWindow = new GraphicsWindow("Aircraft Simulation", 800, 600);
    aircraft = new Aircraft(50, 300, 300, 300);
    altimeter = new Altimeter(255, 50, 201, 201);
    airSpeedIndicator = new AirSpeedIndicator(460, 50, 201, 201, 200.0f);
    attitudeIndicator = new AttitudeIndicator(50, 50, 201, 201);
    altimeter->addToWindow(mainWindow);
    attitudeIndicator->addToWindow(mainWindow);
    airSpeedIndicator->addToWindow(mainWindow);
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
    if(airSpeedIndicator){
        delete airSpeedIndicator;
    }
}

void AircraftSimulation::run() {
    altimeter->updateDisplay();
    long lastTime = SDL_GetTicks();
    while (mainWindow->isOpen()) {
        long currentTime = SDL_GetTicks();
        float updateDelta = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        altimeter->setAltitude( aircraft->getAltitude());
        attitudeIndicator->setAttitude( aircraft->getPitch(), aircraft->getRoll());

        altimeter->updateDisplay();
        attitudeIndicator->updateDisplay();

        airSpeedIndicator->setAirSpeed( aircraft->getAirSpeed());

        mainWindow->pollEvents();
        aircraft->updateGraphics();
        aircraft->updatePhysics(updateDelta);
        mainWindow->update();
        // Simulation logic would go here
    }
}