#pragma once

#include <vector>
#include "Location.h"

class WorldBase{
    private:
        std::vector<Location> locations;
        int worldSizeX;
        int worldSizeY;

    public:
        WorldBase(int worldSizeX, int worldSizeY){
            locations = std::vector<Location>();
            this->worldSizeX = worldSizeX;
            this->worldSizeY = worldSizeY;
        }

        void init(long timeStamp);

        void update(long timeStamp){
            for(auto& loc : locations){
                loc.update(timeStamp);
            }
        }

        void addLocation(const Location& loc);

        Location* getBestLocationForROI(Location* currentLocation);

        Location* getClosestLocation(float x, float y);

        std::vector<Location>& getLocations(){
            return locations;
        }

        std::string getStatus();
};