#include "Location.h"
#include <limits>
#include <iostream>
#include <thread>
#include <chrono>

void Location::update(long timeStamp){
    long deltaTime = timeStamp - lastUpdateTime;
    float TargetAmount = 100.0f;
    for(auto& production : resourceProduction){
        
        std::string resource = production.first;
        float rate = production.second; // units per second
        float amountProduced = rate * (deltaTime / 100.0f); // Convert ms to seconds
        bool isProducing = (rate > 0);
        if(!canManufacture()){
            if(isProducing){
                amountProduced = amountProduced * 0.01f; // Reduce production to 10% if cannot manufacture
            }else{
                amountProduced = 0.0f; // No consumption if cannot manufacture
            }
        }
        goods[resource] += amountProduced;

        if(goods[resource] < 0){
            goods[resource] = 0;
        }

        float currentAmount = goods[resource];

        if(isProducing){
            //TargetAmount = rate * 5.0f;
            if(currentAmount > TargetAmount){
                goodCosts[resource] *= 0.95f; // Decrease cost by 5%
            }
            if(currentAmount < TargetAmount){
                goodCosts[resource] *= 1.00005f;
            }
        }else{
            //TargetAmount = -rate * 10.0f;
            if(currentAmount > TargetAmount * 5.0f && goodCosts[resource] > 0){
                goodCosts[resource] = -goodCosts[resource] * 1.1f; // Switch to selling price and increase by 10%
            }
            else if(currentAmount < TargetAmount && goodCosts[resource] < 0){
                goodCosts[resource] = -goodCosts[resource] * 0.9f; // Switch to buying price and decrease by 10%
            }
            else if(currentAmount < TargetAmount){
                goodCosts[resource] *= (1+(timeStamp -lastShipment[resource])/100000000.0f); // Increase cost by 5%
            }
            else if(currentAmount > TargetAmount && goodCosts[resource] > 0){
                goodCosts[resource] *= .9999f; // Decrease cost slightly
            }
        }


        if(abs(goodCosts[resource]) > 1000.0f){
            goodCosts[resource] = (!isProducing) ? 1000.0f : -1000.0f;
        }
        if(abs(goodCosts[resource]) < 1.0f){
            goodCosts[resource] = (!isProducing) ? 1.0f : -1.0f;
        }
    }
    lastUpdateTime = timeStamp;
}

float Location::getResourceCost(const std::string& resource){
    if(goodCosts.find(resource) != goodCosts.end()){
        return goodCosts[resource];
    }
    return 0.0f; // Resource not found
}

std::string Location::getCheepestResource(){
    std::string cheapestResource;
    float lowestCost = std::numeric_limits<float>::min();

    for(auto& good : goodCosts){
        if(getResourceCost(good.first) >= 0.0f) continue; // Skip resources that are not for sale
        if(good.first == "") continue; // Skip invalid resource names
        if(goods[good.first] <= 10.0f) continue; // Skip resources with no available goods
        if(good.second > lowestCost || cheapestResource == ""){
            lowestCost = good.second;
            cheapestResource = good.first;
        }
    }
    return cheapestResource;
}

std::string Location::getStatus(){
    std::string status = "Location: " + name + "\n";
    status += "Coordinates: (" + std::to_string(x) + ", " + std::to_string(y) + ")\n";
    status += "Resources:\n";
    for(const auto& good : goods){
        status += " - " + good.first + ": " + std::to_string(good.second) + " units, Cost: " + std::to_string(getResourceCost(good.first)) + " prod : " + std::to_string(getResourceProduction(good.first)) + "\n";
    }
    return status;
}

bool Location::hasResourceAmount(const std::string& resource, float amount){
    return goods[resource] >= amount;
}

bool Location::canManufacture(){
    for(const auto& production : resourceProduction){
        if(production.second < 0){ // Negative production rate indicates consumption
            std::string resource = production.first;
            if(goods[resource] <= 0){
                return false; // Not enough resources to manufacture
            }
        }
    }
    return true; // All required resources are available
}

bool Location::withinRange(float px, float py, float range){
    float dx = x - px;
    float dy = y - py;
    float distSquared = dx * dx + dy * dy;
    return distSquared <= range * range;
}

void Location::draw(){
    // Clear buffer
    // Draw circle with center at (25, 25)
    const int centerX = 25;
    const int centerY = 25;
    const int radius = 5;
    
    for(int dy = -radius; dy <= radius; dy++){
        for(int dx = -radius; dx <= radius; dx++){
            if(dx*dx + dy*dy <= radius*radius){
                buffer[(centerY + dy) * 50 + (centerX + dx)] = 0x00FF00FF; // Green color
            }
        }
    }
}