#include "Planet.h"

GravitySink::GravitySink(SDL_FPoint position){
    PhysicsObject::position = {position.x, position.y};
    sinkGraphic = new gItem({static_cast<int>(position.x), static_cast<int>(position.y)}, {static_cast<int>(influenceRadius * 2), static_cast<int>(influenceRadius * 2)}, 0.0f);
}

GravitySink::~GravitySink(){
    delete sinkGraphic;
}

void GravitySink::updateGraphics(){
    for(int x = 0; x < static_cast<int>(influenceRadius * 2); x++){
        for(int y = 0; y < static_cast<int>(influenceRadius * 2); y++){
            float dx = x - influenceRadius;
            float dy = y - influenceRadius;
            float distance = sqrt(dx * dx + dy * dy);
            if(distance <= getMass()/200.0f){
                if(getMass() / 200.0f > influenceRadius){
                    if(distance < influenceRadius){
                        uint32_t color = 0xFFFF0000;
                        sinkGraphic->setPixel(x, y, color);
                    }
                }else{                
                    uint8_t intensity = 255;
                    uint32_t color = 0x008B4513 | (intensity << 24);
                    sinkGraphic->setPixel(x, y, color);
                }

                //uint8_t intensity = static_cast<uint8_t>(255 * (1.0f - (distance / (getMass() / 10.0f))));

            } else {
                sinkGraphic->setPixel(x, y, 0x00000000);
            }

        }
    }
}

void GravitySink::updateGraphicsPosition(){
    if(updatedMass){
        updateGraphics();
        updatedMass = false;
    }
    sinkGraphic->setCenter({static_cast<int>(position.x), static_cast<int>(position.y)});
}
