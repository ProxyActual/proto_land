#include "Altimeter.h"

Altimeter::Altimeter(int x, int y, int width, int height){
    AltimeterFace = new gItem({x + width / 2, y + height / 2}, {width, height}, 0.0f);

    AltimeterNeedle100 = new gItem({x + width / 2, y + height / 2}, {width, height}, 0.0f);
    AltimeterNeedle1k = new gItem({x + width / 2, y + height / 2}, {width, height}, 0.0f);
    AltimeterNeedle10k = new gItem({x + width / 2, y + height / 2}, {width, height}, 0.0f);
}

Altimeter::~Altimeter(){
    delete AltimeterFace;
    delete AltimeterNeedle100;
    delete AltimeterNeedle1k;
    delete AltimeterNeedle10k;
}

void Altimeter::addToWindow(GraphicsWindow* window) {
    window->addItem(AltimeterFace);
    window->addItem(AltimeterNeedle10k);
    window->addItem(AltimeterNeedle1k);
    window->addItem(AltimeterNeedle100);

}

void Altimeter::setAltitude(float altitude){
    currentAltitude = altitude;

    float oneHundredFootAngle = fmod((altitude / 100.0f) * 36.0f, 360.0f); // 36 degrees per 100 feet
    float oneThousandFootAngle = fmod((altitude / 1000.0f) * 36.0f, 360.0f); // 36 degrees per
    float tenThousandFootAngle = fmod((altitude / 10000.0f) * 36.0f, 360.0f); // 36 degrees per 10,000 feet

    AltimeterNeedle100->setRotation(oneHundredFootAngle);
    AltimeterNeedle1k->setRotation(oneThousandFootAngle);
    AltimeterNeedle10k->setRotation(tenThousandFootAngle);

}

void Altimeter::updateDisplay(){
    AltimeterFace->fillPixels(0x00000000); // Black background
    // Draw numbers 0-9 around the outer edge
    const char* numbers[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    int centerX = AltimeterFace->getRect()->w / 2;
    int centerY = AltimeterFace->getRect()->h / 2;
    int radius = std::min(centerX, centerY) - 10; // Offset from edge

    for (int i = 0; i < 10; i++) {
        // Draw 4 tick marks between numbers (evenly spaced in the 36-degree span)
        for (int j = 1; j <= 4; j++) {
            float tickAngle = ((i * 36.0f + j * 7.2f) - 90.0f) * M_PI / 180.0f;
            int tickStartRadius = radius - 5;
            int tickEndRadius = radius + 9;
            int tickStartX = centerX + tickStartRadius * cos(tickAngle);
            int tickStartY = centerY + tickStartRadius * sin(tickAngle);
            int tickEndX = centerX + tickEndRadius * cos(tickAngle);
            int tickEndY = centerY + tickEndRadius * sin(tickAngle);
            AltimeterFace->drawLine(tickStartX, tickStartY, tickEndX, tickEndY, 0x7FFFFFFF); // 50% transparent white
        }
        float angle = (i * 36.0f - 90.0f) * M_PI / 180.0f; // 36 degrees apart, start at top
        int textX = centerX + radius * cos(angle);
        int textY = centerY + radius * sin(angle);
        AltimeterFace->drawString(numbers[i], textX - 5, textY - 5, 0xFFFFFFFF); // White text
    }

    // Draw outer circle
    AltimeterFace->drawCircle(centerX, centerY, radius+9, 0xFFFFFFFF); // White circle

    //Drawing the needles
    float smallNeedleHeight = radius * 0.6f;
    float largeNeedleHeight = radius * 0.9f;

    for(int y = 0; y < AltimeterNeedle100->getRect()->h; ++y){
        for (int x = 0; x < AltimeterNeedle100->getRect()->w; ++x)
        {
            AltimeterNeedle100->setPixel(x,y,0x00000000); // Transparent
            AltimeterNeedle1k->setPixel(x,y,0x00000000); // Transparent
            if(x == centerX && y < centerY){
                AltimeterNeedle100->setPixel(x, y, 0xFF888888); // Grey center post
                AltimeterNeedle1k->setPixel(x, y, 0xFF888888); // Grey center post
                AltimeterNeedle10k->setPixel(x, y, 0xFF888888); // Grey center post
            }
            if(x < centerX + 2 && x > centerX - 2 && y < centerY && y > centerY - smallNeedleHeight){
                AltimeterNeedle100->setPixel(x, y, 0xFFFF0000); // Red small needle
            }
            if(x < centerX + 3 && x > centerX - 3 && y < centerY && y > centerY - largeNeedleHeight){
                AltimeterNeedle1k->setPixel(x, y, 0xFF0000FF); // Blue large needle
            }
            
            if(x < centerX + 2 && x > centerX - 2 && y < AltimeterNeedle10k->getRect()->h * .1f){
                AltimeterNeedle10k->setPixel(x, y, 0xFF00FF00); // Green very large needle
            }
        }
    }
}
