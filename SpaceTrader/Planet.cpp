#include "Planet.h"

GravitySink::GravitySink(SDL_FPoint position){
    PhysicsObject::position = {position.x, position.y};
    sinkGraphic = new gItem({static_cast<int>(position.x), static_cast<int>(position.y)}, {static_cast<int>(influenceRadius * 2), static_cast<int>(influenceRadius * 2)}, 0.0f);
    for(int x = 0; x < influenceRadius * 2; x++){
        for(int y = 0; y < influenceRadius * 2; y++){
            float distFromCenter = sqrt(pow(x - influenceRadius, 2) + pow(y - influenceRadius, 2));
            if(distFromCenter <= influenceRadius){
                sinkGraphic->setPixel(x, y, 0xFF0000FF);
            }
        }
    }
}

GravitySink::~GravitySink(){
    delete sinkGraphic;
}

void GravitySink::updateGraphicsPosition(){
    sinkGraphic->setCenter({static_cast<int>(position.x), static_cast<int>(position.y)});
}
