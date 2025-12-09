#pragma once

class PhysicsObject{
    
    public:
        struct Vector2 {
            float x;
            float y;
        };

        PhysicsObject();
        ~PhysicsObject();

        void updatePhysics(long frameTime, PhysicsObject** otherObjects, int objectCount);

        float getMass(){ return mass; }

        Vector2 getVelocity(){ return velocity; }

        void setMass(float m){ mass = m; }

        void addVelocity(Vector2 vel){ velocity.x += vel.x; velocity.y += vel.y; }

        Vector2 getPosition() { return position; }
    
    protected:
        
        Vector2 position = {0.0f, 0.0f};

    private:
        Vector2 velocity = {0.0f, 0.0f};
        Vector2 acceleration = {0.0f, 0.0f};

        float angularVelocity = 0.0f;
        float rotation = 0.0f;

        float mass = 10.0f;

        float lastUpdateTime = 0.0f;
};