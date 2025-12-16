#include "AttitudeIndicator.h"

AttitudeIndicator::AttitudeIndicator(int x, int y, int width, int height) {
    BlueOverBrown = new gItem({x + width / 2, y + height / 2}, {width, height}, 0.0f);
}

AttitudeIndicator::~AttitudeIndicator() {
    if (BlueOverBrown) {
        delete BlueOverBrown;
    }
}

void AttitudeIndicator::addToWindow(GraphicsWindow* window) {
    window->addItem(BlueOverBrown);
}

void AttitudeIndicator::setAttitude(float pitch, float roll) {
    currentPitch = pitch;
    currentRoll = roll;
}

void AttitudeIndicator::updateDisplay() {
    BlueOverBrown->fillPixels(0x00000000); // Clear to transparent

    int width = BlueOverBrown->getRect()->w;
    int height = BlueOverBrown->getRect()->h;

    for(int x = 0; x < width; ++x){
        for (int y = 0; y < height; ++y)
        {
            if((x-width/2) * (x-width/2) + (y-height/2) * (y-height/2) >= (width/2) * (width/2)){
                continue; // Outside circle
            }
            else if(y <= (height/2) + (currentPitch) * (height / 180.0f) )
            {
                BlueOverBrown->setPixel(x, y, 0xff0000ff); // Blue sky
            }
            else{
                BlueOverBrown->setPixel(x, y, 0xff964B00); // Brown ground
            }

        }
    }
    BlueOverBrown->setRotation(-currentRoll);
}

