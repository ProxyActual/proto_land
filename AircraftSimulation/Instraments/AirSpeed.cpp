#include "AirSpeed.h"

AirSpeedIndicator::AirSpeedIndicator(int x, int y, int width, int height, float maxSpeed) {
    indicatorGraphic = new gItem((SDL_Point{x + width / 2, y + height / 2}), (SDL_Point{width, height}), 0.0f);
    needleGraphic = new gItem((SDL_Point{x + width / 2, y + height / 2}), (SDL_Point{width, height}), 0.0f);
    maxAirSpeed = maxSpeed;
    // Simple representation of an airspeed indicator (a circle with a needle)
    updateGraphics();
}

AirSpeedIndicator::~AirSpeedIndicator() {
    if (indicatorGraphic) {
        delete indicatorGraphic;
    }
    if (needleGraphic) {
        delete needleGraphic;
    }
}

void AirSpeedIndicator::setAirSpeed(float speed) {
    if(speed > maxAirSpeed) speed = maxAirSpeed;
    currentAirSpeed = speed;
    float angle = (currentAirSpeed / maxAirSpeed) * 300.0f; // Map speed to angle (-135 to 135 degrees)
    needleGraphic->setRotation(angle - 150.0f);
}

void AirSpeedIndicator::addToWindow(GraphicsWindow* window) {
    window->addItem(indicatorGraphic);
    window->addItem(needleGraphic);
}

void AirSpeedIndicator::updateGraphics() {
    // Draw the indicator background (a simple circle)
    int radius = std::min(indicatorGraphic->getRect()->w, indicatorGraphic->getRect()->h) / 2 - 5;
    indicatorGraphic->drawCircle(indicatorGraphic->getRect()->w / 2, indicatorGraphic->getRect()->h / 2, radius, 0xFFFFFFFF); // Black circle outline
    int centerX = needleGraphic->getRect()->w / 2;
    int centerY = needleGraphic->getRect()->h / 2;

    for(int y = centerY * 0.1f; y < centerY; y++){
        needleGraphic->setPixel(centerX, y, 0xff0000FF); // Clear to transparent
    }

    // Draw speed markings around the circle
    int numMarkings = 10; // Number of speed markings
    for (int i = 0; i <= numMarkings; i++) {
        float speed = (maxAirSpeed / numMarkings) * i;
        float angle = (speed / maxAirSpeed) * 300.0f - 150.0f; // Match needle angle mapping
        float radians = angle * M_PI / 180.0f;
        
        // Position text around the circle
        int textRadius = radius - 25;
        int textX = centerX + textRadius * sin(radians);
        int textY = centerY - textRadius * cos(radians);
        
        std::string speedText = std::to_string((int)speed);
        float textWithOffset = speedText.length() * 11.0f / 2.0f;
        indicatorGraphic->drawString(speedText, textX - textWithOffset, textY-5, 0xFFFFFFFF);
    }
}