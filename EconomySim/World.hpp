#pragma once

#include "Location.hpp"
#include <iostream>

class World{

private:
    Location* rootLocation;

public:

    void init(){
        rootLocation = new Location("World");

        Location* continent1 = new Location("Continent A");
        Location* country1 = new Location("Country X");
        Location* city1 = new Location("City Alpha");

        country1->addSubLocation(city1);
        continent1->addSubLocation(country1);
        rootLocation->addSubLocation(continent1);
    }

    void printWorldInfo() const {
        if (rootLocation) {
            std::cout << rootLocation->getLocationInfo();
        }
    }
};