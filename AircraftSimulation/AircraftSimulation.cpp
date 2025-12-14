#include "AircraftSimulation.h"
AircraftSimulation::AircraftSimulation() {
    mainWindow = new GraphicsWindow("Aircraft Simulation", 800, 600);
    aircraft = new Aircraft();
    aircraft->addGraphicsToWindow(mainWindow);
}

AircraftSimulation::~AircraftSimulation() {
    if( aircraft) {
        delete aircraft;
    }
    if (mainWindow) {
        delete mainWindow;
    }
}

void AircraftSimulation::run() {
    while (mainWindow->isOpen()) {
        mainWindow->pollEvents();
        aircraft->updateGraphics();
        aircraft->updatePhysics(0.016f); // Assuming ~60 FPS, so ~16ms per frame
        mainWindow->update();
        // Simulation logic would go here
    }
}