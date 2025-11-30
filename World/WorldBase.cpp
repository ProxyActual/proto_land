#include "WorldBase.h"
#include <limits>
#include <cmath>
#include <iostream>

void WorldBase::init(long timeStamp){
    
    Location loc1(100.0f, 150.0f, "Mine", timeStamp);
    loc1.addResourceAmount("Gold", 0.0f);
    loc1.addResourceAmount("Wood", 0.0f);
    loc1.addResourceAmount("Tools", 0.0f);
    loc1.addResourceAmount("Food", 0.0f);

    loc1.setResourceProduction("Gold", 20.0f); // 2  production   
    loc1.setResourceProduction("Wood", -5.0f); // 5 units
    loc1.setResourceProduction("Tools", -5.0f); // 1 unit
    loc1.setResourceProduction("Food", -3.0f); // Consumes food

    loc1.setDefaultResourceCost("Gold", -40.0f); // Selling price
    loc1.setDefaultResourceCost("Wood", 20.0f); // Buying price
    loc1.setDefaultResourceCost("Tools", 100.0f); // Buying price
    loc1.setDefaultResourceCost("Food", 30.0f); // Buying price
    addLocation(loc1);

    Location loc2(400.0f, 300.0f, "Forest", timeStamp);
    loc2.addResourceAmount("Gold", 0.0f);
    loc2.addResourceAmount("Wood", 0.0f);
    loc2.addResourceAmount("Tools", 0.0f);
    loc2.addResourceAmount("Food", 0.0f);

    loc2.setResourceProduction("Gold", -.5f); // 1 unit
    loc2.setResourceProduction("Wood", 20.0f); // 10 units
    loc2.setResourceProduction("Tools", -10.0f); // 1 unit
    loc2.setResourceProduction("Food", 5.0f); // Produces food (hunting/foraging)

    loc2.setDefaultResourceCost("Gold", 50.0f); // Buying price
    loc2.setDefaultResourceCost("Wood", -10.0f); // Selling price
    loc2.setDefaultResourceCost("Tools", 110.0f); // Buying price
    loc2.setDefaultResourceCost("Food", -20.0f); // Selling price
    addLocation(loc2);

    Location loc3(700.0f, 100.0f, "City", timeStamp);
    loc3.addResourceAmount("Gold", 10000.0f);
    loc3.addResourceAmount("Wood", 0.0f);
    loc3.addResourceAmount("Tools", 0.0f);
    loc3.addResourceAmount("Food", 0.0f);

    loc3.setResourceProduction("Gold", -0.5f); // 0.
    loc3.setResourceProduction("Wood", -3.0f); // 3 units
    loc3.setResourceProduction("Tools", 15.0f); // 5 units
    loc3.setResourceProduction("Food", -8.0f); // Consumes food (large population)

    loc3.setDefaultResourceCost("Gold", 30.0f); // Selling price
    loc3.setDefaultResourceCost("Wood", 20.0f); // Buying price
    loc3.setDefaultResourceCost("Tools", -50.0f); // Selling price
    loc3.setDefaultResourceCost("Food", 35.0f); // Buying price
    addLocation(loc3);

    Location loc4(550.0f, 450.0f, "Church", timeStamp);
    loc4.addResourceAmount("Gold", 0.0f);
    loc4.addResourceAmount("Wood", 0.0f);
    loc4.addResourceAmount("Tools", 0.0f);
    loc4.addResourceAmount("Food", 0.0f);

    loc4.setResourceProduction("Gold", 5.0f);
    loc4.setResourceProduction("Wood", -2.0f);
    loc4.setResourceProduction("Tools", 8.0f);
    loc4.setResourceProduction("Food", -2.0f); // Consumes food

    loc4.setDefaultResourceCost("Gold", -45.0f); // Selling price
    loc4.setDefaultResourceCost("Wood", 15.0f); // Buying price
    loc4.setDefaultResourceCost("Tools", -55.0f); // Selling price
    loc4.setDefaultResourceCost("Food", 32.0f); // Buying price
    addLocation(loc4);

    Location loc5(300.0f, 200.0f, "Village", timeStamp);
        loc5.addResourceAmount("Gold", 0.0f);
        loc5.addResourceAmount("Wood", 0.0f);
        loc5.addResourceAmount("Tools", 0.0f);
        loc5.addResourceAmount("Food", 0.0f);

        loc5.setResourceProduction("Gold", -1.0f);
        loc5.setResourceProduction("Wood", 10.0f);
        loc5.setResourceProduction("Tools", -3.0f);
        loc5.setResourceProduction("Food", 12.0f); // Produces food (small farms)

        loc5.setDefaultResourceCost("Gold", 55.0f);
        loc5.setDefaultResourceCost("Wood", -15.0f);
        loc5.setDefaultResourceCost("Tools", 90.0f);
        loc5.setDefaultResourceCost("Food", -22.0f); // Selling price
        addLocation(loc5);
    
    Location loc6(200.0f, 500.0f, "Port", timeStamp);
        loc6.addResourceAmount("Gold", 0.0f);
        loc6.addResourceAmount("Wood", 0.0f);
        loc6.addResourceAmount("Tools", 0.0f);
        loc6.addResourceAmount("Food", 0.0f);

        loc6.setResourceProduction("Gold", 8.0f);
        loc6.setResourceProduction("Wood", -4.0f);
        loc6.setResourceProduction("Tools", 2.0f);
        loc6.setResourceProduction("Food", 6.0f); // Produces food (fishing)

        loc6.setDefaultResourceCost("Gold", -50.0f);
        loc6.setDefaultResourceCost("Wood", 18.0f);
        loc6.setDefaultResourceCost("Tools", 95.0f);
        loc6.setDefaultResourceCost("Food", -25.0f); // Selling price
        addLocation(loc6);

    Location loc7(600.0f, 200.0f, "Blacksmith", timeStamp);
        loc7.addResourceAmount("Gold", 0.0f);
        loc7.addResourceAmount("Wood", 0.0f);
        loc7.addResourceAmount("Tools", 0.0f);
        loc7.addResourceAmount("Food", 0.0f);

        loc7.setResourceProduction("Gold", -60.0f);
        loc7.setResourceProduction("Wood", -8.0f);
        loc7.setResourceProduction("Tools", 50.0f);
        loc7.setResourceProduction("Food", -2.5f); // Consumes food

        loc7.setDefaultResourceCost("Gold", 65.0f);
        loc7.setDefaultResourceCost("Wood", 22.0f);
        loc7.setDefaultResourceCost("Tools", -40.0f);
        loc7.setDefaultResourceCost("Food", 28.0f); // Buying price
        addLocation(loc7);

    Location loc8(450.0f, 350.0f, "Farm", timeStamp);
        loc8.addResourceAmount("Gold", 10000.0f);
        loc8.addResourceAmount("Wood", 0.0f);
        loc8.addResourceAmount("Tools", 0.0f);
        loc8.addResourceAmount("Food", 0.0f);

        loc8.setResourceProduction("Gold", -1.5f);
        loc8.setResourceProduction("Wood", 5.0f);
        loc8.setResourceProduction("Tools", -6.0f);
        loc8.setResourceProduction("Food", 30.0f); // Major food producer

        loc8.setDefaultResourceCost("Gold", 45.0f);
        loc8.setDefaultResourceCost("Wood", -12.0f);
        loc8.setDefaultResourceCost("Tools", 85.0f);
        loc8.setDefaultResourceCost("Food", -18.0f); // Selling price
        addLocation(loc8);

    Location loc9(350.0f, 50.0f, "Quarry", timeStamp);
        loc9.addResourceAmount("Gold", 0.0f);
        loc9.addResourceAmount("Wood", 0.0f);
        loc9.addResourceAmount("Tools", 0.0f);
        loc9.addResourceAmount("Food", 0.0f);

        loc9.setResourceProduction("Gold", 5.0f);
        loc9.setResourceProduction("Wood", -6.0f);
        loc9.setResourceProduction("Tools", -12.0f);
        loc9.setResourceProduction("Food", -4.0f); // Consumes food

        loc9.setDefaultResourceCost("Gold", -35.0f);
        loc9.setDefaultResourceCost("Wood", 25.0f);
        loc9.setDefaultResourceCost("Tools", 105.0f);
        loc9.setDefaultResourceCost("Food", 33.0f); // Buying price
        addLocation(loc9);

    Location loc10(150.0f, 300.0f, "Mill", timeStamp);
        loc10.addResourceAmount("Gold", 10000.0f);
        loc10.addResourceAmount("Wood", 0.0f);
        loc10.addResourceAmount("Tools", 0.0f);
        loc10.addResourceAmount("Food", 0.0f);

        loc10.setResourceProduction("Gold", -0.5f);
        loc10.setResourceProduction("Wood", 15.0f);
        loc10.setResourceProduction("Tools", -4.0f);
        loc10.setResourceProduction("Food", 12.0f); // Produces food (processes grain)

        loc10.setDefaultResourceCost("Gold", 52.0f);
        loc10.setDefaultResourceCost("Wood", -18.0f);
        loc10.setDefaultResourceCost("Tools", 80.0f);
        loc10.setDefaultResourceCost("Food", -20.0f); // Selling price
        addLocation(loc10);

    Location loc11(500.0f, 550.0f, "Market", timeStamp);
        loc11.addResourceAmount("Gold", 0.0f);
        loc11.addResourceAmount("Wood", 0.0f);
        loc11.addResourceAmount("Tools", 100000.0f);
        loc11.addResourceAmount("Food", 100000.0f);

        loc11.setResourceProduction("Gold", 10.0f);
        loc11.setResourceProduction("Wood", -4.0f);
        loc11.setResourceProduction("Tools", -2.0f);
        loc11.setResourceProduction("Food", -1.5f); // Consumes food

        loc11.setDefaultResourceCost("Gold", -200.0f);
        loc11.setDefaultResourceCost("Wood", 16.0f);
        loc11.setDefaultResourceCost("Tools", 88.0f);
        loc11.setDefaultResourceCost("Food", 27.0f); // Buying price
        addLocation(loc11);

    Location sink(20.0f, 590.0f, "Sink", timeStamp);
        sink.addResourceAmount("Gold", 0.0f);
        sink.addResourceAmount("Wood", 0.0f);
        sink.addResourceAmount("Tools", 0.0f);
        sink.addResourceAmount("Food", 0.0f);

        for(auto& resource : {"Gold", "Wood", "Tools", "Food"}){
            float production = 0;
            for(auto& loc : locations){
                production += loc.getResourceProduction(resource);
            }
            sink.setResourceProduction(resource, -production);
            sink.setDefaultResourceCost(resource, production);
        }
       
        addLocation(sink);
}

void WorldBase::addLocation(const Location& loc){
    locations.push_back(loc);
}

Location* WorldBase::getBestLocationForROI(Location* currentLocation){
    std::string leastExpensive = currentLocation->getCheepestResource();
    float highest = std::numeric_limits<float>::min();
    Location* bestLocation;
    for(auto& loc : locations){
        if(loc.getName() == currentLocation->getName()) continue;
        if(loc.getResourceCost(leastExpensive) > highest){
            highest = loc.getResourceCost(leastExpensive);
            bestLocation = &loc;
        }
    }
    return bestLocation;
}

Location* WorldBase::getClosestLocation(float x, float y){
    Location* closest = nullptr;
    float closestDist = std::numeric_limits<float>::max();

    for(auto& loc : locations){
        float dx = loc.getX() - x;
        float dy = loc.getY() - y;
        float dist = std::sqrt(dx * dx + dy * dy);
        if(dist < closestDist){
            closestDist = dist;
            closest = &loc;
        }
    }
    return closest;
}

std::string WorldBase::getStatus(){
    std::string status = "World Status:\n";
    for(auto& loc : locations){
        status += loc.getStatus() + "\n";
        // Add more details as needed
    }
    return status;
}