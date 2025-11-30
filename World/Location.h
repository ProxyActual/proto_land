#pragma once

#include <map>
#include <string>

class Location{
    private:
        float x;
        float y;
        std::string name;

        std::map<std::string, float> resourceProduction;
        std::map<std::string, float> goods;
        std::map<std::string, float> goodCosts;
        std::map<std::string, long> lastShipment;

        long lastUpdateTime = 0;


    public:
        Location(float px, float py, std::string pname, long timeStamp = 0) :
            x(px), y(py), name(pname), lastUpdateTime(timeStamp) {
                goods = std::map<std::string, float>();
                resourceProduction = std::map<std::string, float>();
                goodCosts = std::map<std::string, float>();
            }

        float getX() const { return x; }
        float getY() const { return y; }

        void update(long timeStamp);

        void addResourceAmount(const std::string& resource, float amount, long timestamp){
            lastShipment[resource] = timestamp;
            if(goods[resource] + amount < 0){
                goods[resource] = 0;
                return;
            }
            goods[resource] += amount;
        }

        float getResourceCost(const std::string& resource);

        void setResourceProduction(const std::string& resource, float rate){
            resourceProduction[resource] = rate;
        }
        float getResourceProduction(const std::string& resource){
            return resourceProduction[resource];
        }

        void setDefaultResourceCost(const std::string& resource, float cost){
            goodCosts[resource] = cost;
        }

        std::string getCheepestResource();

        std::string getName() const { return name; }

        std::string getStatus();

        bool hasResourceAmount(const std::string& resource, float amount);

        bool canManufacture();

        bool withinRange(float px, float py, float range);
};