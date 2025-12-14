#pragma once

#include "../GraphicsWindow/GraphicsWindow.h"
#include "Aircraft.h"
#include "Instraments/Altimeter.h"

class AircraftSimulation {
public:
    AircraftSimulation();
    ~AircraftSimulation();
    void run();
private:
    GraphicsWindow* mainWindow;
    Aircraft* aircraft;
    Altimeter* altimeter;
};