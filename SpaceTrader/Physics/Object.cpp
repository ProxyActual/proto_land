#include "Object.h"
#include <cmath>
#include <iostream>

PhysicsObject::PhysicsObject(){
}

PhysicsObject::~PhysicsObject() {
}

void PhysicsObject::updateVelocity(long frameTime, PhysicsObject** otherObjects, int objectCount) {
    long currentFrameTime = frameTime - lastVelUpdateTime;
    lastVelUpdateTime = frameTime;
    for (int i = 0; i < objectCount; ++i) {
        if (otherObjects[i] != this && otherObjects[i] != nullptr) {
            Vector2 direction = {
                otherObjects[i]->getPosition().x - position.x,
                otherObjects[i]->getPosition().y - position.y
            };
            float distanceSquared = direction.x * direction.x + direction.y * direction.y;
            if (distanceSquared > 10.0f) {
                float forceMagnitude = (mass * otherObjects[i]->getMass()) / distanceSquared;
                float distance = sqrt(distanceSquared);
                acceleration.x += (direction.x / distance) * forceMagnitude / mass;
                acceleration.y += (direction.y / distance) * forceMagnitude / mass;
            }
        }
    }
    velocity.x += acceleration.x * (currentFrameTime / 1000.0f);
    velocity.y += acceleration.y * (currentFrameTime / 1000.0f);
}

void PhysicsObject::updatePosition(long frameTime){
    acceleration = {0.0f, 0.0f};
    long currentFrameTime = frameTime - lastPosUpdateTime;
    lastPosUpdateTime = frameTime;
    position.x += velocity.x * (currentFrameTime / 1000.0f);
    position.y += velocity.y * (currentFrameTime / 1000.0f);
}